#include "precomp.h"

/*
	outout debug message
*/
void net_debug()
{
	#if 0
	if(vbus_system){
		utils_debug("system bus dump:\n");
		((CRtkVBus*)vbus_system)->dbg_dump();
	}
	if(vbus_rtdb){
		utils_debug("rtdb bus dump:\n");
		((CRtkVBus*)vbus_rtdb)->dbg_dump();
	}
	if(vbus_config){
		utils_debug("config bus dump:\n");
		((CRtkVBus*)vbus_config)->dbg_dump();
	}
	if(vbus_operation){
		utils_debug("operation bus dump:\n");
		((CRtkVBus*)vbus_operation)->dbg_dump();
	}
	#endif
}

