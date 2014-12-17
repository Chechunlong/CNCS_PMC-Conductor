#include "precomp.h"

class CWriteTagTransaction : public CWaitableTransaction
{
public:
	CWriteTagTransaction()
	{
		add_transaction(vbus_operation, this);
	}
	__bool Query(
		PCTAG_NAME name, 
		PCTAG_VALUE value,
		__uint timeout
		)
	{
		char heap[sizeof(TAG_NAME) + sizeof(TAG_VALUE)];
		__uint heapsize;
		RTK_ADDR addr;
		
		heapsize = sizeof(*name) + sizeof(*value);
		memcpy(heap, name, sizeof(*name));
		memcpy(heap + sizeof(*name), value, sizeof(*value));

		node_to_host(&name->node, &addr.host);
		addr.port = PORT_ALL_SERVER;
		
		send_rtk_data_with_guid(
			vbus_operation,
			&addr,
			&Guid,
			PT_Operation,
			heap,
			heapsize
			);
		return Wait(timeout);
	}
private:
	virtual void OnEvent(PCRTK_PACKET p)
	{
		SetEvent();
	}
};

/*
	proxy_write_tags
	description : inform the DB server to output a value to the corresponding
	device.
*/
PROXY_API __uint PMC_API proxy_write_tags(
	__uint count, 
	PCTAG_NAME names, 
	PCTAG_VALUE values
	)
{
	__uint i;
	__uint j;
	__uint ok;

	ok = 0;
	for(i=0; i<count; i++, names++, values++){
		CWriteTagTransaction * tr;
		tr = new CWriteTagTransaction();
		if(!tr){
			continue;
		}
		for(j=0; j<3; j++){
			tr->life = 20;
			if(tr->Query(names, values, 1000)){
				ok++;
				break;
			}
			rtk_sleep(200);
		}		
	}

	return ok;
}

class CWriteTagTransaction2 : public CWaitableTransaction
{
public:
	CWriteTagTransaction2()
	{
		add_transaction(vbus_operation, this);
	}
	__bool Query(
		PCTAG_NAME name, 
		PCpmc_value_t value,
		__uint timeout
		)
	{
		char heap[sizeof(TAG_NAME) + sizeof(pmc_value_t)];
		__uint heapsize;
		RTK_ADDR addr;
		
		heapsize = sizeof(*name) + sizeof(*value);
		memcpy(heap, name, sizeof(*name));
		memcpy(heap + sizeof(*name), value, sizeof(*value));

		node_to_host(&name->node, &addr.host);
		addr.port = PORT_ALL_SERVER;
		
		send_rtk_data_with_guid(
			vbus_operation,
			&addr,
			&Guid,
			PT_Operation2,
			heap,
			heapsize
			);
		return Wait(timeout);
	}
private:
	virtual void OnEvent(PCRTK_PACKET p)
	{
		SetEvent();
	}
};


PROXY_API __uint PMC_API proxy_write_tags_ex(
	__uint count,
	PCTAG_NAME names, 
	PCpmc_value_t values
	)
{
	__uint i;
	__uint j;
	__uint ok;
	CWriteTagTransaction2 * tr;

	ok = 0;
	for(i=0; i<count; i++, names++, values++){
		switch(get_value_type(values->Flags)){
		case dt_bool:
		case dt_int8:
		case dt_int16:
		case dt_int32:
		case dt_int64:
		case dt_uint64:
		case dt_uint8:
		case dt_uint16:
		case dt_uint32:
		case dt_real4:
		case dt_real8:		
			tr = new CWriteTagTransaction2();
			if(!tr){
				continue;
			}
			for(j=0; j<3; j++){
				tr->life = 10;
				if(tr->Query(names, values, 1000)){
					ok++;
					break;
				}
				rtk_sleep(200);
			}
			break;
		default:
			// non-numeric types cannot be written
			;
		}
	}

	return ok;
}

