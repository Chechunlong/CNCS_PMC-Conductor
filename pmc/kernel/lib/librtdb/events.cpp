#include "precomp.h"

PRTDB_DISPATCH_TABLE	g_Handlers[MAX_HANDLERS];
__int					g_iHandlers;

RTDB_API __bool PMC_API hook_rtdb_events(PRTDB_DISPATCH_TABLE table)
{
	int i;

	if(g_iHandlers >= MAX_HANDLERS || !table){
		return __false;
	}

	for(i=0; i<g_iHandlers; i++){
		if(g_Handlers[i] == table){
			// cannot hook another
			return __true;
		}
	}
	
	g_Handlers[g_iHandlers] = table;
	g_iHandlers++;
	
	return __true;
}

RTDB_API __bool PMC_API unhook_rtdb_events(PRTDB_DISPATCH_TABLE table)
{
	__int i;
	if(!g_iHandlers || !table){
		return __false;
	}
	for(i=0; i<g_iHandlers; i++){
		if(g_Handlers[i] == table){
			break;
		}
	}
	if(i>=g_iHandlers){
		return __false;
	}
	for(; i<g_iHandlers - 1; i++){
		g_Handlers[i] = g_Handlers[i+1];
	}
	g_iHandlers--;
	return __true;
}

RTDB_API void PMC_API fire_rtdb_event(RTDB_EVENT id, void * p1, void *)
{
	switch(id){
	case EV_AddTag:
		FIRE_EVENT(OnAddTag, ((PRTK_TAG)p1));
		break;
	case EV_DropTag:
		FIRE_EVENT(OnDropTag, ((PRTK_TAG)p1));
		break;
	case EV_ModifyTag:
		FIRE_EVENT(OnModifyTag, ((PRTK_TAG)p1));
		break;
	case EV_AddGroup:
		FIRE_EVENT(OnAddGroup, ((PRTK_GROUP)p1));
		break;
	case EV_DropGroup:
		FIRE_EVENT(OnDropGroup, ((PRTK_GROUP)p1));
		break;
	case EV_ModifyGroup:
		FIRE_EVENT(OnModifyGroup, ((PRTK_GROUP)p1));
		break;
	case EV_AddNode:
		FIRE_EVENT(OnAddNode, ((PRTK_NODE)p1));
		break;
	case EV_DropNode:
		FIRE_EVENT(OnDropNode, ((PRTK_NODE)p1));
		break;
	default:
		break;
	}
}

