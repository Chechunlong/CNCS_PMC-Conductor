/********************************************************************
	PC-Based monitoring & controlling system source
	prodoct version : 2.03
	filename: 	e:\vss\pmc2\src\rtkproxy\add_groups.cpp
	file path:	e:\vss\pmc2\src\rtkproxy
	author:		Jackie Pan, jhunter@tsinghua.org.cn
	
	purpose:	Add groups to running DCS	
	history:
	created:	11/8/2002   17:19
*********************************************************************/
#include "precomp.h"

class CAddEditGroupsTransaction : public CWaitableTransaction
{
public:
	CAddEditGroupsTransaction(
		__uint count, 
		PCNODE_KEY nodes, 
		PCRTK_GROUP groups,
		__uint timeout, 
		__bool bEdit=false
		)
	{
		void	*buf;
		left = count;
		
		m_bEdit = bEdit;
		buf = alloc_buffer_v(
			nodes, sizeof(nodes[0])*count, 
			groups, sizeof(groups[0])*count, 
			0
			);
		if(!buf){
			return;
		}
		add_transaction(vbus_config, this);
		broadcast_rtk_data_with_guid(
			vbus_config,
			PORT_ALL_SERVER,
			&Guid,
			bEdit? PT_EditGroup : PT_AddGroup,
			buf,
			(sizeof(nodes[0]) + sizeof(groups[0]))*count
			);
		free_buffer(buf);
		Wait(timeout);
	}
private:
	virtual void OnEvent(PCRTK_PACKET p)
	{
		left -= _on_add_edit_groups(p, true);
		if(left <= 0){
			SetEvent();
		}
	}
public:
	__uint	left;
	__bool	m_bEdit;
};

PROXY_API __uint PMC_API add_groups(
	__uint count,
	PCNODE_KEY nodes,
	PCRTK_GROUP groups,
	__uint timeout
	)
{
	CAddEditGroupsTransaction * trans = new 
		CAddEditGroupsTransaction(count, nodes, groups, timeout, false);
	if(!trans){
		return 0;
	}
	trans->life = 30;
	return count - trans->left;
}

PROXY_API __uint PMC_API edit_groups(
	__uint count,
	PCNODE_KEY nodes,
	PCRTK_GROUP groups,
	__uint timeout
	)
{
	CAddEditGroupsTransaction * trans = new 
		CAddEditGroupsTransaction(count, nodes, groups, timeout, true);
	if(!trans){
		return 0;
	}
	trans->life = 30;
	return count - trans->left;
}
