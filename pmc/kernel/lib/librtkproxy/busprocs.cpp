#include "precomp.h"
#pragma hdrstop

void PMC_API _on_rtdb(PCRTK_PACKET packet, HVBUS bus)
{
	// check for unknown node
	TAG_NAME	tn;
	PRTK_NODE pNode;

#if 0
	if(get_power_state() != PWR_RUNNING){
		return;
	}
#endif

	if(g_Worker){
		if(lock_rtdb(__false, 100)){
			RTK_CURSOR hNode;
			host_to_node(&packet->src.host, &tn.node);
			hNode = open_node(&tn.node);
			pNode = (PRTK_NODE)cursor_get_item(hNode);
			if(pNode){
				pNode->dogcount = g_NodeLife;
			}
			close_handle(hNode);
			unlock_rtdb();
			if(!hNode){
				memset(&tn.sname, 0, sizeof(tn.sname));
				// unknown node
				g_Worker->inform_load(&tn, 1);
			}			
			if(!hNode){
				return;
			}
		}
	}

	switch(PACKET_TYPE(packet)){
	case PT_ChangedData:
		update_changed_data(packet, __false);
		break;
	case PT_QueryData:
		_on_queried_data(packet);
		break;
	}
}

void PMC_API _on_config(PCRTK_PACKET packet, HVBUS bus)
{
#if 0
	if(get_power_state() != PWR_RUNNING){
		return;
	}
#endif

#define HANDLE_IT(type, func)\
	case type:\
		func(packet);\
		break
	switch(packet->packet_type){
	case PT_AddTag | PF_ACK:
	case PT_EditTag | PF_ACK:
		_on_add_edit_tags(packet, true);
		break;
	case PT_DropTag | PF_ACK:
		_on_drop_tags(packet);
		break;
	case PT_AddGroup | PF_ACK:
	case PT_EditGroup | PF_ACK:
		_on_add_edit_groups(packet, true);
		break;
	case PT_DropGroup | PF_ACK:
		_on_drop_groups(packet);
		break;
	HANDLE_IT(PT_AddDevice, _on_add_device);
	HANDLE_IT(PT_EditDevice, _on_edit_device);
	HANDLE_IT(PT_DelDevice, _on_del_device);
	HANDLE_IT(PT_DiscoverTags | PF_ACK, _on_add_edit_tags);
	}
}

void PMC_API _on_alarm(PCRTK_PACKET packet, HVBUS bus)
{
	TAG_NAME	tn;
	RTK_ALARM_PACKET *p;
	//RTK_CURSOR crNode;

#if 0
	if(get_power_state() != PWR_RUNNING){
		return;
	}
#endif

	switch(packet->packet_type){
	case PT_Alarm:
		p = (RTK_ALARM_PACKET*)packet->data;
		if(p->Class == AC_Online){
			host_to_node(&packet->src.host, &tn.node);
			DEBUG_PRINTF((
				"Got online broadcast from %s.\n",
				(char*)CNodeName(tn.node)
				));
			if(g_Worker){
				memset(&tn.sname, 0, sizeof(tn.sname));
				g_Worker->inform_load(&tn, 1);
			}
		}else if(p->Class == AC_Offline){
			/*
			host_to_node(&packet->src.host, &tn.node);
			DEBUG_PRINTF((
				"Got offline broadcast from %s.\n",
				(char*)CNodeName(tn.node)
				));			
			if(lock_rtdb(__true, 500)){
				crNode = open_node(&tn.node);
				if(crNode){
					cursor_delete(crNode);
				}
				unlock_rtdb();
			}
			*/
		}
		rtk_queue_event(
			PT_Alarm, 
			p->Rank, 
			p->Class, 
			p->Msg, 
			&packet->src
			);
		break;
	}
}

/*
	_on_system()
*/
void PMC_API _on_system(PCRTK_PACKET packet, HVBUS bus)
{
#if 0
	if(get_power_state() != PWR_RUNNING){
		return;
	}
#endif
	{
		static __bool priorityBoosted = __false;
		if(!priorityBoosted){
			DWORD boost;
			boost = GetPrivateProfileInt(
				"vbus", 
				"SystemBoost", 
				THREAD_PRIORITY_ABOVE_NORMAL,
				get_config_file()
				);
			SetThreadPriority(GetCurrentThread(), boost);
			priorityBoosted = __true;
		}
	}

	if(packet->packet_type != PT_ServerClaim){
		return;
	}
	if(!lock_rtdb(__false, 1000)){
		return;
	}
	RTK_CURSOR	hNode;
	PRTK_NODE	pNode;
	TAG_NAME	tn;
	host_to_node(&packet->src.host, &tn.node);
	hNode = open_node(&tn.node);
	pNode = (PRTK_NODE)cursor_get_item(hNode);
	if(pNode){
		pNode->dogcount = g_NodeLife;
	}
	close_handle(hNode);
	unlock_rtdb();
	if(!pNode && g_Worker){
		memset(&tn.sname, 0, sizeof(tn.sname));
		g_Worker->inform_load(&tn, 1);
	}
}

