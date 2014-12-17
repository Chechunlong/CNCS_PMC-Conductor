/********************************************************************
	PC-Based monitoring & controlling system source
	prodoct version : 2.03
	filename:	ioss.cpp
	author:		Jackie Pan, jhunter@tsinghua.org.cn
	
	purpose:	IO subsystem
	history:
	created:	10:9:2002	14:37
*********************************************************************/
#include "precomp.h"

#ifdef _WIN32
#pragma comment(linker, "/base:0x76560000")
#endif

__r4	g_fltMaxChangeRate;
__r4	g_fltTagLife;

static __bool PMC_API _power_callback(int newState, int context)
{
	PDEVICE_INFO dev;
	DEVICE_LIST::iterator it;
	PDRIVER_INFO drv;
	IOSS_STATUS code;

	for(it = g_Devices.begin(); it != g_Devices.end(); it++){
		dev = it->second;
		drv = dev->d;
		if( (dev->flags & DF_Active) && (drv->dispatch)){
			code = drv->dispatch(dev, DISP_POWER_STATE_CHANGED, newState);
			if(code){
				utils_error(
					"Error : device %s vetoed `power-state-changed' command,"
					"error code 0x%08x.\n"
					"This may cause unpredictable result.\n",
					(char*)CDeviceName(dev->k),
					code
					);
				return __false;
			}
		}
	}

	return __true;
}

static void _load_settings()
{
	char buf[32];

	*buf = 0;
	GetPrivateProfileString(
		"PMC",
		"MaxChangeRate",
		"0.01",
		buf,
		sizeof(buf),
		get_config_file()
		);
	g_fltMaxChangeRate = (__r4)atof(buf);
	if(g_fltMaxChangeRate < 0.0001 || g_fltMaxChangeRate > 5){
		utils_error(
			"MaxChangeRate=%.3f%% is not valid.\n",
			g_fltMaxChangeRate
			);
		g_fltMaxChangeRate = rtkm_default_change_rate;
	}
	utils_trace("MaxChangeRate is set to %.3f%% \n", g_fltMaxChangeRate);
	
	*buf = 0;
	GetPrivateProfileString(
		"PMC",
		"TagLife",
		"60",
		buf,
		sizeof(buf),
		get_config_file()
		);
	g_fltTagLife = (__r4)atof(buf);
	if(g_fltTagLife < 5){
		utils_error(
			"TagLife=%.1fs is not valid, reset to 5s.\n", 
			g_fltTagLife
			);
	}
	utils_trace("TagLife is set to %.1fs\n", g_fltTagLife);
}

IO_API __bool PMC_API init_ioss()
{
	_load_settings();

	register_power_callback(_power_callback, 0);
	
	pnp_probe_devices();

	if(!CDBRefresher::init()){
		utils_error("Global initialization of CRefresher failed.\n");
		return __false;
	}	

	return __true;
}

IO_API void PMC_API uninit_ioss()
{
	if(!lock_rtdb(__true, 1000)){
		return;
	}
	g_Refresher.uninit();
	pnp_stop_devices();
	unregister_power_callback(_power_callback, 0);
	unlock_rtdb();
}

static __bool _writeDevice(PRTK_TAG p, PCTAG_VALUE value)
{
	PDRIVER_INFO npu;
	__bool retval = false;
	
	// p->d.DeviceObj = io_open_device(&p->s.Device);
	if(p->d.DeviceObj){
		npu = ((PDEVICE_INFO)p->d.DeviceObj)->d;
		if(npu){
			if(npu->write_device){
				retval = npu->write_device(p, value);
			}
		}
	}

	return retval;
}

IO_API __bool PMC_API io_write_device(
	PCSHORT_TAG_NAME name, 
	PCTAG_VALUE value
	)
{
	__bool retval = __false;

	if(!lock_rtdb(__false, 100)){
		return __false;
	}
	PRTK_TAG p = query_tag(HNODE_LOCAL_MACHINE, name);
	if(p && !(p->d.Value.Flags & TF_ReadOnly)){
	#if 0
		{
			char valbuf[32];
			if(get_value_type(p->s.Flags) == dt_real4){
				sprintf(valbuf, "%f", value->fltValue);
			}else{
				sprintf(valbuf, "%s", value->iValue? "On" : "Off");
			}
			utils_debug(
				"WriteDevice(%s.%s)=%s\n", 
				(char *)CGroupName(name->group),
				(char *)CTagName(name->tag),
				valbuf
				);
		}
	#endif
		retval = _writeDevice(p, value);
	}
	unlock_rtdb();

	return retval;
}

IO_API __bool PMC_API io_write_device_ex(
	PCSHORT_TAG_NAME name, 
	PCpmc_value_t value
	)
{
	pmc_value_t value2;
	__bool retval = __false;

	if(!lock_rtdb(__false, 100)){
		return __false;
	}
	PRTK_TAG p = query_tag(HNODE_LOCAL_MACHINE, name);
	if(p && !(p->d.Value.Flags & TF_ReadOnly)){
		ZeroMemory(&value2, sizeof(value2));
		set_value_type(value2.Flags, get_value_type(p->s.Flags));
		if(pmc_type_cast(value, &value2)){
			retval = _writeDevice(p, &value2.Value);
		}
	}
	unlock_rtdb();

	return retval;
}

IO_API __bool PMC_API io_update_tag(
	PCRTK_TAG tag, 
	Ppmc_value_t new_value,
	PCRTK_TIME now
	)
{
	PDRIVER_INFO drv;

	new_value->Flags = 0;
	set_value_type(new_value->Flags,  get_value_type(tag->s.Flags));
	
	/* 
	pre-set all unused bytes to zero, this will make it easier to
	write code depending on the tag types
	*/
	new_value->Value.u64 = 0;
	
	// assert(tag->d.DeviceObj == io_open_device(&tag->s.Device));

	if(!tag->d.DeviceObj){
		return __false;
	}
	drv = ((PDEVICE_INFO)tag->d.DeviceObj)->d;
	if(!drv){
		return __false;
	}
	if(!drv->update_tag){
		return __false;
	}
	
	if(drv->update_tag){
		drv->update_tag(tag, new_value, now);
	}

	// some ill-behavioured driver will overwrite the type field
	set_value_type(new_value->Flags, get_value_type(tag->s.Flags));
	if(get_value_type(tag->s.Flags) == dt_bool){
		/* make digital variable cannonical */
		new_value->Value.b = new_value->Value.b? 1 : 0;
	}
	
	return __true;
}

