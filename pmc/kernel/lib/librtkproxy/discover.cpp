#include "precomp.h"

class CDiscoverNodes : public CWaitableTransaction
{
public:
	CDiscoverNodes(__uint timeout)
	{
		c_nodes = 0;
		add_transaction(vbus_config, this);		
		broadcast_rtk_data(
			vbus_config, 
			PORT_ALL_SERVER, 
			PT_DiscoverNodes, 
			(void *)&this->Guid, 
			sizeof(this->Guid)
			);
		Wait(timeout);
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		__uint i;
		if(c_nodes >= 128){
			return;
		}
		for(i=0; i<c_nodes; i++){
			if(is_same_key(&nodes[i], &packet->src.host)){
				return;
			}
		}
		host_to_node(&packet->src.host, &nodes[c_nodes++]);
	}
public:
	NODE_KEY	nodes[128];
	__uint		c_nodes;
};

/*
	generate a packet to discovery all running PMC servers.
*/
PROXY_API __uint PMC_API discover_nodes(__uint timeout)
{
	return discover_nodes_ex(timeout, NULL, __true); 
}

class CDiscoverGroups : public CWaitableTransaction
{
public:
	CDiscoverGroups(PCNODE_KEY node, __uint timeout)
	{
		RTK_ADDR dest;
		
		c_items = 0;
		add_transaction(vbus_config, this);		
		node_to_host(node, &dest.host);
		dest.port = PORT_ALL_SERVER;
		send_rtk_data(
			vbus_config, 
			&dest,
			PT_DiscoverGroups, 
			(void *)&this->Guid, 
			sizeof(this->Guid)
			);
		Wait(timeout);
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		c_items = _on_add_edit_groups(packet, true);
		SetEvent();
	}
public:
	__uint		c_items;
};

PROXY_API __uint PMC_API discover_groups(PCNODE_KEY key, __uint timeout)
{
	return discover_groups_ex(key, timeout, NULL, __true);
}

class CDiscoverTags : public CWaitableTransaction
{
public:
	CDiscoverTags(PCNODE_KEY node, PCGROUP_KEY grp, __uint timeout)
	{
		RTK_ADDR dest;
		ONLINE_CONFIG oc;
		oc.d_tags.ack_guid = Guid;
		oc.d_tags.group = *grp;

		c_items = 0;
		add_transaction(vbus_config, this);		
		node_to_host(node, &dest.host );
		dest.port = PORT_ALL_SERVER;
		gk = *grp;
		nk = *node;
		hint = std::string("正在接收 ") + 
			(char*)CNodeName(nk) + "." + (char*)CGroupName(gk) +
			" 上的数据库标签信息...";
		send_rtk_data(
			vbus_config, 
			&dest,
			PT_DiscoverTags, 
			&oc.d_tags,
			sizeof(oc.d_tags)
			);
		Wait(timeout, TRUE);
		if(!c_items){
			OnTimeout();
		}
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		c_items = packet->data_size / (sizeof(ONLINE_CONFIG::reload_tags_ack));
		SetEvent();
		_on_add_edit_tags(packet, false);
		std::string s;
		s = std::string((char*)CNodeName(nk)) + "." + (char*)CGroupName(gk) +
			" 上的数据库标签信息接收完成.";
		rtk_queue_event(PT_Progress, packet->total_frag, 0, s.data());
	}
	virtual void OnProgress(__uint total, __uint completed, PCRTK_PACKET p){
		rtk_queue_event(PT_Progress, total, completed, hint.data());
		if(total == completed){
			SetEvent();
		}
	}
	virtual void OnTimeout()
	{
		if(!WaitResult()){
			std::string s;
			s = std::string((char*)CNodeName(nk)) + "." + 
				(char*)CGroupName(gk) +
				" 上的数据库标签信息接收超时.";
			rtk_queue_event(PT_Progress, 1, 0, s.data());
		}
	}
	__uint c_items;
protected:
	NODE_KEY  nk;
	GROUP_KEY gk;
	std::string	  hint;
};

PROXY_API __uint PMC_API discover_tags(PCNODE_KEY node, PCGROUP_KEY key, __uint timeout)
{
	return discover_tags_ex(node, key, timeout, NULL, __true);
}

class CDiscoverDevices : public CWaitableTransaction
{
public:
	CDiscoverDevices(PCNODE_KEY node, __uint timeout)
	{
		RTK_ADDR dest;
		
		c_items = 0;
		add_transaction(vbus_config, this);		
		node_to_host(node, &dest.host );
		dest.port = PORT_ALL_SERVER;
		send_rtk_data_with_guid(
			vbus_config, 
			&dest,
			&Guid,
			PT_DiscoverDevices
			);
		Wait(timeout);
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		c_items = packet->data_size / sizeof(items[0]);
		if(c_items > 256){
			c_items = 256;
		}
		memcpy(items, packet->data, sizeof(items[0])*c_items);
		SetEvent();
	}
public:
	DEVICE_INFO	items[256];
	__uint		c_items;
};

PROXY_API __uint PMC_API discover_devices(
	PCNODE_KEY node, 
	DEVICE_INFO *buffer, 
	__uint *maxcount,
	__uint timeout
	)
{
	__uint count;
	CDiscoverDevices *eye =  new CDiscoverDevices(node, timeout);
	if(!eye){
		return __false;
	}
	count = min(*maxcount, eye->c_items);
	if(*maxcount < eye->c_items){
		*maxcount = eye->c_items;
	}	
	memcpy(buffer, eye->items, count*sizeof(buffer[0]));
	return count;
}

class CDiscoverPictures : public CWaitableTransaction
{
public:
	CDiscoverPictures(PCNODE_KEY node, __uint timeout)
	{
		RTK_ADDR dest;
		
		c_items = 0;
		add_transaction(vbus_config, this);		
		node_to_host(node, &dest.host);
		dest.port = PORT_ALL_SERVER;
		send_rtk_data_with_guid(
			vbus_config, 
			&dest,
			&Guid,
			PT_DiscoverPictures
			);
		Wait(timeout);
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		c_items = packet->data_size / sizeof(items[0]);
		if(c_items > 256){
			c_items = 256;
		}
		memcpy(items, packet->data, sizeof(items[0])*c_items);
		SetEvent();
	}
public:
	PICT_KEY	items[256];
	__uint		c_items;
};

PROXY_API __uint PMC_API discover_pictures(
	PCNODE_KEY node,
	PPICT_KEY buffer,
	__uint *maxcount,
	__uint timeout
	)
{
	CDiscoverPictures *eye = new CDiscoverPictures(node, timeout);
	if(!eye){
		return __false;
	}
	__uint count = min(*maxcount, eye->c_items);
	if(*maxcount < eye->c_items){
		*maxcount = eye->c_items;
	}	
	memcpy(buffer, eye->items, count*sizeof(buffer[0]));
	return count;
}

class CDiscoverConfigFiles : public CWaitableTransaction
{
public:
	CDiscoverConfigFiles(PCNODE_KEY node, char * b, __uint s, __uint timeout)
	{
		RTK_ADDR dest;
		
		ok = false;
		bufsize = s;
		buf = b;
		*buf = '\0';
		add_transaction(vbus_config, this);		
		node_to_host(node, &dest.host);
		dest.port = PORT_ALL_SERVER;
		send_rtk_data_with_guid(
			vbus_config, 
			&dest,
			&Guid,
			PT_DiscoverConfigFiles
			);
		Wait(timeout);
	}
	virtual void OnEvent(PCRTK_PACKET packet)
	{
		if(packet->data_size > bufsize){
			ok = false;
			SetEvent();
			return;
		}
		memcpy(buf, packet->data, packet->data_size);
		ok = true;
		SetEvent();
	}
public:
	__uint		bufsize;
	char		*buf;
	bool		ok;
};

PROXY_API __uint PMC_API discover_configfiles(
	PCNODE_KEY node,
	char *buffer,
	__uint buffersize,
	__uint timeout
	)
{
	CDiscoverConfigFiles *eye = new CDiscoverConfigFiles(node, buffer, buffersize, timeout);
	if(!eye){
		return 0;
	}
	if(!eye->ok){
		return 0;
	}
	char *p;
	p = buffer;
	__uint i=0;
	while(*p){
		i++;
		p += strlen(p) + 1;
	}
	return i;
}

PROXY_API __bool PMC_API discover_nodes_ex(
	__uint timeout, 
	__uint * count,
	__bool bDiscardOld
	)
{
	__uint i;
	if(count){
		*count = 0;
	}
	CDiscoverNodes *eye = new CDiscoverNodes(timeout);
	if(!eye){
		return __false;
	}
	if(!eye->WaitResult()){
		return __false;
	}
	
	if(bDiscardOld){
		// clear database
		if( !lock_rtdb(__true, timeout) ){
			return __false;
		}
		
		RTK_CURSOR	cursor;
		cursor = open_first_node();
		while(cursor){
			cursor_delete(cursor);
			cursor = open_first_node();
		}
		for(i=0; i<eye->c_nodes; i++){
			cursor = create_node(&eye->nodes[i], 0);
			close_handle(cursor);
		}
		unlock_rtdb();
	}

	if(count){
		*count = eye->c_nodes;
	}
	return __true;
}

PROXY_API __bool PMC_API discover_groups_ex(
	PCNODE_KEY key, 
	__uint timeout,
	__uint * count,
	__bool bDiscardOld
	)
{
	if(count){
		*count = 0;
	}
	if(bDiscardOld){
		// clean database
		if(!lock_rtdb(__true, timeout/2)){
			return 0;
		}
		RTK_CURSOR crNode;
		crNode = open_node(key);
		if(crNode){
			cursor_clear_subitems(crNode);
			close_handle(crNode);
		}
		unlock_rtdb();
	}
	
	CDiscoverGroups *eye = new CDiscoverGroups(key, timeout);
	if(!eye){
		return __false;
	}
	if(!eye->WaitResult()){
		return __false;
	}
	if(count){
		*count = eye->c_items;
	}
	return __true;
}

PROXY_API __bool PMC_API discover_tags_ex(
	PCNODE_KEY node, 
	PCGROUP_KEY group, 
	__uint timeout,
	__uint * count,
	__bool bDiscardOld
	)
{
	RTK_CURSOR crGroup;
	if(count){
		*count = 0;
	}
	if(bDiscardOld){
		if(!lock_rtdb(__true, timeout/2)){
			return __false;
		}
		crGroup = open_group_f(node, group);
		if(crGroup){
			cursor_clear_subitems(crGroup);
			close_handle(crGroup);
		}
		unlock_rtdb();
	}
	
	CDiscoverTags *eye;
	eye = new CDiscoverTags(node, group, timeout);
	if(!eye){
		return __false;
	}
	if(!eye->WaitResult()){
		return __false;
	}
	if(count){
		*count = eye->c_items;
	}
	return __true;
}

