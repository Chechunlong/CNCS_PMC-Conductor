#include "precomp.h"
#pragma hdrstop

#ifdef _WIN32
#include <pmckey.h>
#pragma comment(linker, "/base:0x69000000")
#endif

static int g_iInitCount;
static CLock * _g_InitLock;
#define g_InitLock (*(CLock*)_g_InitLock)
__r4	g_fltTagLife;
__int g_NodeLife;
__int g_QueryInterval=1000;
CProxyWorker * g_Worker;
static RTDB_DISPATCH_TABLE g_DBDispatchTable;
static int g_iInitFlag;

/*
	If a rtdb network packet contains some tags not present
	locally, then a maximum number of MAX_MISSING_PERMITED
	tags will be checked and reloaded from corresponding servers,
	this helps reduce network overhead on system startup.
	
*/
#define MAX_MISSING_PERMITED 128

/*
*/
PROXY_API __uint PMC_API update_changed_data(
	PCRTK_PACKET packet,
	__bool bThisIsAServer
	)
{
	CHANGED_DATA_ENTRY * t;
	CHANGED_DATA	* cd;
	__uint		i, nMissing;
	RTK_CURSOR	hNode, hGroup, hTag;
	TAG_NAME	name;
	PRTK_TAG	pTag;
	__uint		retcount = 0;
	TAG_NAME	missing[MAX_MISSING_PERMITED];

	if(packet->data_size <= sizeof(CHANGED_DATA)){
		return 0;
	}
	cd = (CHANGED_DATA*)packet->data;
	t = (CHANGED_DATA_ENTRY*)&cd[1];
	if(packet->data_size != cd->count * sizeof(CHANGED_DATA_ENTRY)
		+ sizeof(CHANGED_DATA)
	){
		return 0;
	}

#if 0
	for(i=0; i<cd->count; i++){
		utils_debug("%s.%s.%s=%f\n", 
			(char*)CHostName(packet->src.host),
			(char*)CGroupName(cd->group),
			(char*)CTagName(t[i].name),
			t[i].value.Value.fltValue
			);
	}
#endif

	memset(&name, 0, sizeof(name));
	host_to_node(&packet->src.host, &name.node);
	name.sname.group = cd->group;
	if(!lock_rtdb(__false, 100)){
		return 0;
	}
	if(bThisIsAServer){
		if(!(packet->src.host == g_ThisNode->key)){
			unlock_rtdb();
			return 0;
		}
		hNode = HNODE_LOCAL_MACHINE;
	}else{
		hNode = open_node(&name.node);
	}
	if(!hNode){
		unlock_rtdb();
		return 0;
	}
	hGroup = open_group(hNode, &cd->group);
	if(!hGroup){
		if(!bThisIsAServer){
			close_handle(hNode);
		}		
		unlock_rtdb();
		if(g_Worker){
			g_Worker->inform_load(&name, 1);
		}
		// 2003/5/27, in current implementation all following
		// tags are guaranteed to be in the same group, so there
		// is no need to proceed.
		return 0;
	}
	nMissing = 0;
	for(i=0; i<cd->count; i++){
		hTag = open_tag_g(hGroup, &t[i].name);
		if(hTag){
			pTag = (PRTK_TAG)cursor_get_item(hTag);
			pTag->d.Value = t[i].value;
			// pTag->d.Value.Flags = t[i].value.Flags;
			mark_fresh(pTag);
			close_handle(hTag);
			retcount++;
		}else{
			if(g_Worker && nMissing < MAX_MISSING_PERMITED){
				name.sname.tag = t[i].name;
				missing[nMissing] = name;
				nMissing++;				
			}
		}
	}
	close_handle(hGroup);
	if(!bThisIsAServer){
		close_handle(hNode);
	}
	unlock_rtdb();
	if(nMissing && g_Worker){
		if(nMissing > 16){
			memset(&missing[0].sname.tag, 0, sizeof(TAG_KEY));
			g_Worker->inform_load(missing, 1);
		}else{
			g_Worker->inform_load(missing, nMissing);
		}
	}

	return retcount;
}

__uint _on_add_edit_groups(PCRTK_PACKET p, bool /* bGenerateEvents */)
{
	RTK_CURSOR hNode, hGroup;
	NODE_KEY nk;
	PRTK_GROUP png, pg=0;
	__uint count;

	if(p->data_size % sizeof(RTK_GROUP)){
		return 0;
	}
	if(!lock_rtdb(__true, 100)){
		return 0;
	}
	host_to_node(&p->src.host, &nk);
	hNode = open_node(&nk);
	if(!hNode){
		unlock_rtdb();
		return 0;
	}
	
	count = p->data_size / sizeof(RTK_GROUP);
	png = (PRTK_GROUP)p->data;
	for(__uint i=0; i<count; i++, png++){
		hGroup = open_group(hNode, &png->key);
		pg = (PRTK_GROUP)cursor_get_item(hGroup);
		if(pg){
			memcpy(
				pg->description, 
				png->description, 
				sizeof(pg->description)
				);
			pg->period = png->period;			
		}else{
			hGroup = create_group(hNode, png);
			pg = (PRTK_GROUP)cursor_get_item(hGroup);
		}
		if(pg){
			pg->d.flags = png->d.flags;
		}
		DEBUG_PRINTF((
			"Got group %s, flag=%08x\n", 
			(char *)CGroupName(png->key), 
			png->d.flags
			));
		close_handle(hGroup);
		if(pg /* && bGenerateEvents */){
			TAG_NAME name;
			name.node = nk;
			name.sname.group = png->key;
			rtk_queue_event(
				PT_AddGroup,
				&name,
				&p->src
				);
		}
	}
	close_handle(hNode);
	unlock_rtdb();

	return count;
}

__uint _on_add_edit_tags(PCRTK_PACKET p, bool bGenerateEvents)
{
	ONLINE_CONFIG::reload_tags_ack *ack;
	RTK_CURSOR	hNode, hTag, hGroup;
	RTK_TAG		*pTag;
	NODE_KEY	nodekey;
	TAG_NAME	name;
	RTK_GROUP	grp;
	__bool bEditing;
	
	__uint tagcount, i;

	ack = (ONLINE_CONFIG::reload_tags_ack *)p->data;
	tagcount = p->data_size / sizeof(*ack);
	if(p->data_size % sizeof(*ack)){
		return 0;
	}
	if(!tagcount){
		return 0;
	}
	ZeroMemory(&grp, sizeof(grp));

	if((PACKET_TYPE(p) == PT_DiscoverTags) && g_Worker){
		TAG_NAME tn;
		memset(&tn, 0, sizeof(tn));
		tn.node = ack[0].tag.node;
		tn.sname.group = ack[0].tag.group;
		g_Worker->cancel_load(&tn);
	}

	if(!lock_rtdb(__true, 100)){
		return 0;
	}

	host_to_node(&p->src.host, &nodekey);
	hNode = create_node(&nodekey, 0);
	hTag = hGroup = 0;
	name.node = nodekey;
	grp.node = nodekey;
	if(hNode){
		for(i=0; i<tagcount; i++){
			hGroup = open_group(hNode, &ack[i].tag.group);
			grp.key = ack[i].tag.group;
			if(!hGroup){
				hGroup = create_group(hNode, &grp);
			}
			if(hGroup){
				bEditing = query_tag_g(hGroup, &ack[i].tag.key)? __true : __false;
				hTag = create_tag(hGroup, &ack[i].tag.key, &ack[i].tag.s);
				pTag  = (RTK_TAG*)cursor_get_item(hTag);
				if(pTag){
					*pTag = ack[i].tag;
					/*
						2003/5/27, leave tag's dynamic flags as they were
						2003/6/24, mark tag as newly received, but the valid flag
						is kept as set by server
					*/
					mark_fresh(pTag);
					close_handle(hTag);
					if(bGenerateEvents){
						name.sname.group = ack[i].tag.group;
						name.sname.tag   = ack[i].tag.key;
						rtk_queue_event(PT_AddTag, &name, &p->src);
					}
					if(bEditing){
						fire_rtdb_event(EV_ModifyTag, pTag);
					}
				}					
			}
			close_handle(hGroup);
		}
		close_handle(hNode);
	}

	unlock_rtdb();

	return tagcount;
}

__uint PMC_API _on_drop_groups(PCRTK_PACKET packet)
{
	__uint count, i, ret=0;
	RTK_CURSOR hNode, hGroup;
	PGROUP_KEY pgk;
	TAG_NAME name;
	NODE_KEY nk;

	count = packet->data_size / sizeof(GROUP_KEY);
	if(packet->data_size % sizeof(GROUP_KEY)){
		return 0;
	}
	if( !lock_rtdb(true, 100) ){
		return 0;
	}
	host_to_node(&packet->src.host, &nk);
	name.node = nk;
	hNode = open_node(&nk);
	if(hNode){
		for(i=0, pgk=(PGROUP_KEY)packet->data; i<count; i++, pgk++){
			name.sname.group = *pgk;
			hGroup = open_group(hNode, pgk);
			if(hGroup){
				cursor_delete(hGroup);
				rtk_queue_event(PT_DropGroup, &name, &packet->src);
				ret++;
			}
		}
		close_handle(hNode);
	}
	unlock_rtdb();
	return ret;
}

void PMC_API _on_drop_tags(PCRTK_PACKET packet)
{
	__uint		count, i;
	PTAG_NAME	name;

	count = packet->data_size / sizeof(TAG_NAME);
	if(packet->data_size % sizeof(TAG_NAME)){
		return;
	}
	if( !lock_rtdb(true, 100) ){
		return;
	}
	for(i=0, name=(PTAG_NAME)packet->data; i<count; i++, name++){
		RTK_CURSOR hTag;
		hTag = open_tag_f(name);
		if(hTag){
			cursor_delete(hTag);
		}
		rtk_queue_event(PT_DropTag, name, &packet->src);
	}
	unlock_rtdb();
}

void _on_add_device(PCRTK_PACKET p)
{
	if(p->packet_type & PF_Failed){
		return;
	}
	rtk_queue_event(PT_AddDevice, &p->src, p->data);
}

void _on_edit_device(PCRTK_PACKET p)
{
	if(p->packet_type & PF_Failed){
		return;
	}
	rtk_queue_event(PT_EditDevice, &p->src, p->data);
}

void _on_del_device(PCRTK_PACKET p)
{
	if(p->packet_type & PF_Failed){
		return;
	}
	rtk_queue_event(PT_DelDevice, &p->src, p->data);
}

__uint _fastcall _read_tags(
	__uint count, 
	PCTAG_NAME names, 
	Ppmc_value_t values,
	__uint & existed
	)
{
	RTK_CURSOR	hNode, hTag;
	NODE_KEY	cachedNode;
	RTK_TAG		*pTag;
	__uint		i, valids;

	valids = 0;
	existed = 0;
	ZeroMemory(values, sizeof(values[0]) * count);
	if(!lock_rtdb(false, 1000)){
		return 0;
	}
	hNode = 0;
	hTag = 0;
	RTK_TIME now;
	rtk_time_mark(&now);
	hNode = 0;
	memset(&cachedNode, 0, sizeof(cachedNode));
	for(i=0; i<count; i++){
		if(!(cachedNode == names[i].node)){
			close_handle(hNode);
			hNode = 0;			
		}
		if(!hNode){
			hNode = open_node(&names[i].node);
			cachedNode = names[i].node;
		}
		if(!hNode){
			values[i].Flags &= ~TF_Valid;
			continue;
		}		
		hTag = open_tag(hNode, &names[i].sname);
		if(hTag){
			existed++;
			pTag = (RTK_TAG*)cursor_get_item(hTag);
			double diff;
			diff = rtk_time_diff(&now, &pTag->d.CachedTime);
			if(diff > (g_fltTagLife*2)){
				mark_expired(pTag);
			}
			values[i] = pTag->d.Value;
			valids++;
			close_handle(hTag);
		}else{
			values[i].Flags &= ~TF_Valid;
		}		
	}
	close_handle(hNode);
	unlock_rtdb();
	return valids;
}

void _load_settings(__bool bSilent)
{
	char buf[32];

	if(!bSilent){
		utils_trace("Loading proxy settings...\n");
	}

	g_NodeLife = GetPrivateProfileInt(
		"PMC",
		"NodeLife",
		rtkm_default_node_life,
		get_config_file()
		);
	if(g_NodeLife < 200 || g_NodeLife > 60000){
		g_NodeLife = rtkm_default_node_life;
	}
	if(!bSilent){
		utils_trace(
			"Node will be kicked after idle for %d ms.\n", 
			g_NodeLife
			);
	}
	
	*buf = 0;
	GetPrivateProfileString(
		"PMC",
		"TagLife",
		"120",
		buf,
		sizeof(buf),
		get_config_file()
		);
	g_fltTagLife = (__r4)atof(buf);
	if(g_fltTagLife < 5){
		utils_error(
			"TagLife=%.1fs is not valid, reset to %.1fs.\n", 
			g_fltTagLife,
			rtkm_default_tag_life
			);
		g_fltTagLife = rtkm_default_tag_life;
	}else{
		if(!bSilent){
			utils_trace("TagLife is set to %.1fs\n", g_fltTagLife);
		}
	}

	CProxyWorker::m_MaxBgLoads = GetPrivateProfileInt(
		"PMC",
		"MaxBgLoad",
		256,
		get_config_file()
		);
	if(!bSilent){
		utils_trace("BGLoader's queue length is %d entries.\n", CProxyWorker::m_MaxBgLoads);
	}
	
	g_QueryInterval = GetPrivateProfileInt(
		"PMC",
		"QueryInterval",
		1000,
		get_config_file()
		);
	if(g_QueryInterval < 1000 || g_QueryInterval > 30000){
		if(!bSilent){
			utils_error("QueryInterval=%d is invalid, setting to default.");
		}
		g_QueryInterval = 1000;
	}
	if(!bSilent){
		utils_trace("Query interval set to %d.\n", g_QueryInterval);
	}
}

/*
	proxy's RTDB hook, when a node is added into the database.
	reset its watch dog counter to full life.
*/
static void _on_add_node(PRTK_NODE node)
{
	node->dogcount = g_NodeLife;
}

static void _on_del_node(PRTK_NODE node)
{
	if(g_Worker){
		g_Worker->purge_load_queue(&node->key);
	}
}

__uint _on_queried_data(PCRTK_PACKET p)
{
	RTK_CURSOR	hNode, hTag, hGroup;
	RTK_TAG		*pTag;
	TAG_NAME	name;
	TAG_NAME	missing[MAX_MISSING_PERMITED];
	__uint		nMissing;
	
	QUERY_DATA_ENTRY *t;
	__uint tagcount, retcount, i;

	t = (QUERY_DATA_ENTRY *)p->data;
	tagcount = p->data_size / sizeof(*t);
	if(p->data_size % sizeof(QUERY_DATA_ENTRY)){
		return 0;
	}
	retcount = 0;
	if(!lock_rtdb(__false, 100)){
		return 0;
	}
	memset(&name, 0, sizeof(name));
	host_to_node(&p->src.host, &name.node);
	hNode = open_node(&name.node);
	hTag = hGroup = 0;
	
	if(!hNode){		
		unlock_rtdb();
		if(g_Worker){			
			g_Worker->inform_load(&name, 1);
		}
		return 0;
	}

	nMissing = 0;
	for(i=0; i<tagcount; i++){
		hGroup = open_group(hNode, &t[i].name.group);
		if(hGroup){
			hTag = open_tag_g(hGroup, &t[i].name.tag);
			if(hTag){
				pTag = (RTK_TAG*)cursor_get_item(hTag);
				pTag->d.Value = t[i].value;
				mark_fresh(pTag);
				close_handle(hTag);
				retcount++;
			}else{
				if(g_Worker){
					name.sname = t[i].name;
					missing[nMissing] = name;
					nMissing++;
				}
			}
			close_handle(hGroup);
		}else{
			if(g_Worker){
				missing[nMissing].node = name.node;
				missing[nMissing].sname.group = t[i].name.group;
				memset(&missing[nMissing].sname.tag, 0, sizeof(TAG_KEY));
				nMissing++;
			}
		}
	}
	close_handle(hNode);
	unlock_rtdb();
	if(g_Worker && nMissing){
		g_Worker->inform_load(missing, nMissing);
	}
	return retcount;
}

PROXY_API __bool PMC_API init_proxy(HWND hWnd, __uint flags)
{
	char * szWarning = "没有找到软件狗，进入演示状态，数据库最大规模32点";

	if(!_g_InitLock){
		_g_InitLock = new CLock;
	}
	
	g_InitLock.Lock();
	if(g_iInitCount){
		g_iInitCount++;
		g_InitLock.UnLock();
		return __true;
	}

	g_iInitCount++;

	g_iInitFlag = flags;
	
	_load_settings(__false);
	
	g_DBDispatchTable.OnAddNode = _on_add_node;
	g_DBDispatchTable.OnDropNode = _on_del_node;
	hook_rtdb_events(&g_DBDispatchTable);
	
	if(!(g_iInitFlag & PROXY_INIT_AS_SERVER)){
		unsigned char run, dev;
		int runLevel, devLevel;
		init_key();
		get_key(&run, &runLevel, &dev, &devLevel);
		if(!dev){
			/* no dog is attached*/
			/* create_group(0x12345678,xxx) is a loophole */
			create_group((RTK_CURSOR)0x12345678, (PRTK_GROUP)32);
			if(!(flags & PROXY_SILENT)){
				MessageBox(
					hWnd,
					szWarning,
					"PMC Error",
					MB_OK
					);
			}
		}else{
			/* yes, dog is attached, set database limit */
			create_group((RTK_CURSOR)0x12345678, (PRTK_GROUP)devLevel);
		}
	}
	init_powermgr();
	init_network(0);
	init_rtdb();
	connect_vbus(BUSID_RTDB, 0, _on_rtdb, default_client_filter);
	connect_vbus(BUSID_CONFIG, 0, _on_config, default_client_filter);
	connect_vbus(BUSID_ALARM, 0, _on_alarm, default_client_filter);
	connect_vbus(BUSID_SYSTEM, 0, _on_system, default_client_filter);
	connect_vbus(BUSID_OPERATION, 0, 0, default_client_filter);
	if(flags & PROXY_ENABLE_DISPATCHER){
		start_dispatcher();
	}	

	g_Worker = new CProxyWorker(flags);
	if(!g_Worker){
		g_InitLock.UnLock();
		return __false;		
	}
	g_Worker->start();

#if defined(_WIN32) && 1
	SetThreadPriority(g_Worker->handle(), THREAD_PRIORITY_BELOW_NORMAL);
#endif
		
	g_InitLock.UnLock();
	return __true;
}

PROXY_API void PMC_API uninit_proxy()
{
	g_InitLock.Lock();

	g_iInitCount--;
	
	if(g_iInitCount){
		g_InitLock.UnLock();
		return;
	}

	if(g_Worker){
		if(g_Worker->stop(3000)){
			delete g_Worker;
		}		
		g_Worker = 0;
	}

	stop_dispatcher();
	uninit_network();
	uninit_rtdb();
	unhook_rtdb_events(&g_DBDispatchTable);

	g_iInitFlag = 0;
		
	g_InitLock.UnLock();

	delete _g_InitLock;
	_g_InitLock = 0;
}

