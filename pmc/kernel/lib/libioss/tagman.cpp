#include "precomp.h"

__bool CChangedTagManager::init(__uint maxitems, PCGROUP_KEY gk)
{
	if(this->maxitems < maxitems){
		buffer = realloc(
			buffer, 
			maxitems * sizeof(CHANGED_DATA_ENTRY) + 
			sizeof(RTK_PACKET) - 
			sizeof(packet->data) +
			sizeof(CHANGED_DATA)
			);
		if(!buffer){
			cds = 0;
			return __false;
		}
	}
	cds = (CHANGED_DATA*)
		((char*)buffer + sizeof(RTK_PACKET) - sizeof(packet->data));
	cds->group = *gk;
	cds->count = 0;
	entries = (CHANGED_DATA_ENTRY*)&cds[1];
	packet = (RTK_PACKET*)buffer;
	this->maxitems = maxitems;
	return __true;
}

void CChangedTagManager::add_tag(
	PCGROUP_KEY gk, 
	PCRTK_TAG tte, 
	PCpmc_value_t tv
	)
{
	if(!buffer){
		return;
	}
	__uint items = cds->count;
	if(items>=maxitems){
		return;
	}
	entries[items].name	 = tte->key;
	entries[items].value = *tv;
	cds->count++;
}

__bool CChangedTagManager::broadcast()
{
	__uint byteCount;
	if(!buffer){
		return __false;
	}
	if(!cds->count){
		return __false;
	}
	packet->guid.create();
	mk_bcast_addr(&packet->dest.host);
	packet->dest.port = PORT_ALL_CLIENT;
	packet->packet_type = PT_ChangedData;
	packet->data_size = cds->count*sizeof(CHANGED_DATA_ENTRY) 
		+ sizeof(CHANGED_DATA);
	packet->offset = 0;	
	packet->frgmt_id = 0;	
	packet->total_frag = 1;
	packet->grp_id = 0;
	byteCount = send_rtk_packet(vbus_rtdb, packet);
	return byteCount >= 0? __true : __false;
}

void CChangedTagManager::destroy()
{
	if(buffer){
		free(buffer);
		buffer   = 0;
		entries  = 0;
		maxitems = 0;
		cds      = 0;
	}
}


