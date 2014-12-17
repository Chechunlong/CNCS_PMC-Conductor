/*
	Database refresher
	2003/5/22 master/slave supported added

	REvision:
	2003/7/20, Jackie, found bug : tag is not invalidated immediately
	after failure in updation, corrected.
*/
#include "precomp.h"

static RTDB_DISPATCH_TABLE s_Handler;
static int	last_phase;

CDBRefresher g_Refresher;

CDBRefresher::CDBRefresher()
{
	m_dwPeriod = rtkm_refresh_quantum;
	m_bMsgLoops = __false;	
}

CDBRefresher::~CDBRefresher()
{
}

void CDBRefresher::post_db_init()
{
	RTK_CURSOR handle;
	PRTK_GROUP p;

	handle = cursor_open_first_subitem(HNODE_LOCAL_MACHINE);
	while(!cursor_is_end(handle)){
		p = (PRTK_GROUP)cursor_get_item(handle);
		OnAddGroup(p);
		RTK_CURSOR hTag;
		PRTK_TAG   pTag;
		hTag = cursor_open_first_subitem(handle);
		while(pTag = (PRTK_TAG)cursor_get_item(hTag)){
			OnAddTag(pTag);
			cursor_move_next(hTag);
		}
		close_handle(hTag);
		cursor_move_next(handle);
	}
	close_handle(handle);
}

__bool CDBRefresher::init()
{
	if(!lock_rtdb(__false, 1000)){
		return __false;
	}

	post_db_init();

	s_Handler.OnAddGroup = OnAddGroup;
	s_Handler.OnDropGroup = OnDropGroup;
	s_Handler.OnAddTag = OnAddTag;
	s_Handler.OnModifyTag = OnAddTag;
	s_Handler.OnModifyGroup = OnEditGroup;
	s_Handler.OnDropTag	= OnDropTag;

	hook_rtdb_events(&s_Handler);

	__bool ret = g_Refresher.start();
	utils_trace(
		"DB Refresher started(0x%08x)...%s\n", 
		g_Refresher.id(), 
		ret? "Ok" : "Failed."
		);
	unlock_rtdb();
	
	return ret;
}

__bool CDBRefresher::uninit()
{
	unhook_rtdb_events(&s_Handler);
	if (g_Refresher.stop(5000)){
		utils_trace("DB refresher stopped.\n");
	}else{
		utils_trace("DB refresher stopping timeout.\n");
	}
	g_Refresher.rlist.clear();	
	return __true;
}

/*
	update a tag's value in database according the
	recently acquisited value(by device driver), and
	queue the tag and its value into the tag manager's
	broadcast list if necessary.
*/
void CDBRefresher::check_exception(
	const GROUP_KEY *gk, 
	PRTK_TAG tte, 
	pmc_value_t *tv, 
	PCRTK_TIME now
	)
{
	get_exception(gk, tte, tv, now);

	tte->d.Value.Value = tv->Value;
	tte->d.Value.Flags &= ~TF_Valid;
	tte->d.Value.Flags |= (tv->Flags & TF_Valid);

	if(tv->Flags & TF_Valid){
		// clear the first-unavailable flag
		tte->d.Value.Flags &= ~TF_Shutdown;
	}
	
	tte->d.Time = *now;
	tv->Flags = tte->d.Value.Flags;

	if(tte->d.Value.Flags & (TF_Rate | TF_Expired)){
		tte->d.BroadcastTime = *now;
		tte->d.BroadcastedValue = tte->d.Value.Value;
#if 0
		if(tte->s.Type == DT_Real4){
			DEBUG_PRINTF((
				"%s.%s=%f.\n", 
				(char*)CGroupName(*gk),
				(char*)CTagName(tte->key),
				tv->Value.fltValue
				));
		}else{
			DEBUG_PRINTF((
				"%s.%s=%s.\n", 
				(char*)CGroupName(*gk),
				(char*)CTagName(tte->key),
				tv->Value.iValue? "On" : "Off"
				));
		}
#endif
		ctm.add_tag(gk, tte, tv);
	}
}

/*
	2004/8/4
	we should use the tag level coloring scheme to smooth 
	server-side load. for now, the group-level coloring is 
	used, it seems inadequate for lage amout of tag data.
*/
void CDBRefresher::task()
{
	if(!rlist.size()) {
		return;
	}
	RTK_CURSOR		hGroup;
	RTK_CURSOR		hTag;
	PRTK_TAG		pTag;
	R_LIST::iterator it;
	GROUP_R_EXT		*ge;
	RTK_TIME		now;	
	__uint			count;
	pmc_value_t tv;

	if(get_power_state() != PWR_RUNNING){
		return;
	}

	if( !lock_rtdb(__false, 100) ){
		return;
	}

	for(it=rlist.begin(); it!=rlist.end(); it++){
		ge = &(*it);
		ge->phase++;
		if(ge->phase < ge->max_quantums){
			continue;
		}
		ge->phase = 0;
		ge->refresh_count++;				
		hGroup = open_group(HNODE_LOCAL_MACHINE, &ge->key);
		if(!hGroup){
			continue;
		}
		hTag = cursor_open_first_subitem(hGroup);
		if(!hTag){
			close_handle(hGroup);
			continue;
		}
		rtk_time_mark(&now);
#if 0
		UTILS_TIME		start_time;
		time_mark(&start_time);
#endif
		count = cursor_get_subitem_count(hGroup);
		ctm.init(count, &ge->key);
		while(pTag = (PRTK_TAG)cursor_get_item(hTag)){			
			if((pTag->d.Value.Flags & (TF_Translated | TF_ConfigOk))
				==
				(TF_Translated | TF_ConfigOk)
			){
				assert(get_value_type(pTag->d.Value.Flags) ==
					get_value_type(pTag->s.Flags));								
				io_update_tag(pTag, &tv, &now);
			}else{
				tv.Flags = 0;
				set_value_type(tv.Flags, get_value_type(pTag->s.Flags));
			}
			check_exception(&ge->key, pTag, &tv, &now);
			cursor_move_next(hTag);
		}
		close_handle(hTag);
		close_handle(hGroup);

		ctm.broadcast();
#if 0
		UTILS_TIME e;
		time_mark(&e);
		DEBUG_PRINTF((
			">>G %s : %d tags flushed in %.3f ms, %d broadcasted.\n",
			(char*)CGroupName(ge->key),
			count,
			time_diff(&e, &start_time)*1000,
			ctm.get_items()
			));
#endif
	}

	unlock_rtdb();
}

void  CDBRefresher::OnAddGroup(PRTK_GROUP pgrp)
{
	GROUP_R_EXT ext;
	R_LIST & rlist = g_Refresher.rlist;
	R_LIST::iterator it;

	for(it = rlist.begin(); it != rlist.end(); it++){
		if(is_same_key(&it->key, &pgrp->key)){
			// editing existing group
			it->max_quantums = pgrp->period / rtkm_refresh_quantum;
			if(0 >= it->max_quantums){
				it->max_quantums = 1;
			}
			it->phase = last_phase % it->max_quantums;
			last_phase++;
			return;
		}
	}
	ZeroMemory(&ext, sizeof(ext));
	ext.key = pgrp->key;
	ext.max_quantums = (int)ceil((double)pgrp->period / rtkm_refresh_quantum);
	if(0 >= ext.max_quantums){
		ext.max_quantums = 1;
	}
	ext.phase = last_phase % ext.max_quantums;
	last_phase++;
	rlist.insert(rlist.end(), ext);
}

void  CDBRefresher::OnEditGroup(PRTK_GROUP grp)
{
	R_LIST & rlist = g_Refresher.rlist;
	R_LIST::iterator it;

	for(it = rlist.begin(); it != rlist.end(); it++){
		if(is_same_key(&it->key, &grp->key)){
			it->max_quantums = grp->period / rtkm_refresh_quantum;
			if(0 >= it->max_quantums){
				it->max_quantums = 1;
			}
			it->phase = last_phase % it->max_quantums;
			last_phase++;
			break;
		}
	}
}

void  CDBRefresher::OnDropGroup(PRTK_GROUP grp)
{
	R_LIST & rlist = g_Refresher.rlist;
	R_LIST::iterator it;

	for(it = rlist.begin(); it != rlist.end(); it++){
		if(is_same_key(&it->key, &grp->key)){
			rlist.erase(it);
			break;
		}
	}
}

void  CDBRefresher::OnAddTag(PRTK_TAG tag)
{
	PDEVICE_INFO d;

	if(!tag->d.DeviceObj){
		RtkInitializeListHead(&tag->d.DeviceLink);
	}else{
		assert(!RtkIsListEmpty(&tag->d.DeviceLink));
	}

	// preset dynamic portion
	set_value_type(tag->d.Value.Flags, get_value_type(tag->s.Flags));
	
	// re-validate the static configuration
	if(validate_tag(tag) == 0){
		tag->d.Value.Flags |= TF_ConfigOk;
	}else{
		tag->d.Value.Flags &= ~TF_ConfigOk;
	}

	// handling refresh coloring
	//
	
	d = io_open_device(&tag->s.Device);
	
	if(tag->d.DeviceObj){
		detach_tag_from_device(tag);
	}

	if(d){
		attach_tag_to_device(tag, d);
	}

	tag->d.Value.Flags |= TF_Shutdown;
}

void CDBRefresher::OnDropTag(PRTK_TAG tag)
{
	// BUGBUG: commented out temporarily, 2003/12/11, Jackie
	// FIXED: 2004/8/18
	detach_tag_from_device(tag);
}

