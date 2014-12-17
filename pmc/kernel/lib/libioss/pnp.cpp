#include "precomp.h"

__bool pnp_init()
{
	return __true;
}

__bool pnp_uninit()
{
	return __true;
}

/*
	io_probe_device

	The function is named after a linux kernel function, mod_probe, :-)

	Parameters:

	dev_name --- gives the name of the device to be loaded. the device's
	configuration is loaded from the config registry.
	
	bValidateTags	--- if specified, the database is searched, the tags
	pertaining to this device are attached to this device. this allows
	us to mount a device at runtime, well after the database subsystem
	is already started.

	NOTE : the bValidateTags is specified in the case of delayed device
	loading, i.e., loading device after the database is already started. the
	device loader has to take the responsibility to attach the tags to this
	device. While in earlier stage of system initialization, the pnp_probe_devices
	don't use this flag, because the database subsystem will make the 
	attachment at a later phase.

	For now, we don't see any need to load a device in a way other than
	the two above stated patterns.

	If you're familiar with the Windows Driver Model, you may have correctly
	sensed that what we implement here is just the equivalence of NT's
	unkown bus (enumerator) driver.
*/
IO_API PDEVICE_INFO PMC_API io_probe_device(
	const char * dev_name, 
	__bool bValidateTags
	)
{	
	CArgsEx ag_dev;
	PDRIVER_INFO pDriver;
	PDEVICE_INFO pDevice;
	CArgsEx vt; // vendor and type
	char dev_setting[256];
	
	GetPrivateProfileString(
		"devices",
		dev_name,
		"",
		dev_setting,
		sizeof(dev_setting),
		get_config_file()
		);
	ag_dev.parse(dev_setting, ",", MAX_ARGC, MAX_LINE_LENGTH, false);
	if(ag_dev.argc < 1){
		// line syntax: vendor.type, bus-address, parameters
		/*
			anything beyond the third ',' segmented part constitutes
			the device parameters.
		*/
		utils_error(
			"Invalid device setting for '%s':%s\n", 
			dev_name, 
			dev_setting
			);
		return 0;
	}
	vt.parse(ag_dev.argv[0], ".");
	if(vt.argc != 2){
		utils_error(
			"Invalid device setting for '%s':%s\n", 
			dev_name, 
			dev_setting
			);
		return 0;
	}
	
	if(!lock_rtdb(__true, 1000)){
		return 0;
	}
	
	pDriver = io_load_driver(
			&(VENDOR_KEY)CVendorName(vt.argv[0]),
			&(DEVTYPE_KEY)CDevTypeName(vt.argv[1])
			);
	if(!pDriver){
		utils_error("Cannot load IO driver %s\n", ag_dev.argv[0]);
	}

	// 2003/4/21, the device object must be created even if the settings
	// are invalid, thus giving user a chance to correct the error.
	// create the device
	pDevice = io_create_device(
		pDriver,
		&(DEVICE_KEY)CDeviceName(dev_name)
		);
	if(!pDevice){
		utils_error("Cannot create device %s\n", dev_name);
		unlock_rtdb();
		return 0;
	}

	if(pDriver){
		pDevice->v = pDriver->vendor;
		pDevice->t = pDriver->type;
		strncpy(
			pDevice->address, 
			ag_dev.argv[1], 
			sizeof(pDevice->address)
			);
		pDevice->address[sizeof(pDevice->address) - 1] = 0;
		if(ag_dev.argc > 2){
			strncpy(
				pDevice->parameter,
				dev_setting + ag_dev.arg_idx[2],
				sizeof(pDevice->parameter)
				);
		}		
		pDevice->parameter[sizeof(pDevice->parameter) - 1] = 0;
	}

	if(bValidateTags){
		attach_device_tags(pDevice);
	}

	if(!io_start_device(pDevice)){
		/*
			error happed during device loading.
			we keep this faulty device in memory, so that
			the configurator has a chance to correct the
			error.
		*/
		// io_delete_device(pDevice);			
	}
	
	unlock_rtdb();
	
	return pDevice;
}

/*
	enumerate the devices to be loaded and load them.
*/
__bool pnp_probe_devices()
{
	int i;
	char dev_list[1024], *dev_name;
	CArgsEx ag_loaded;	

	GetPrivateProfileString(
		"devices",
		"load",
		"",
		dev_list,
		sizeof(dev_list),
		get_config_file()
		);
	ag_loaded.parse(dev_list);

	for(i=0; i<ag_loaded.argc; i++){
		dev_name = ag_loaded.argv[i];
		io_probe_device(dev_name, __false);
	}

	return __true;
}

__bool pnp_stop_devices()
{
	PDEVICE_INFO dev;
	DEVICE_LIST::iterator it;
	DEVICE_LIST::iterator tmp;
	
	for(it = g_Devices.begin(); it != g_Devices.end(); ){
		dev = it->second;
		if(io_stop_device(dev)){
			it++;
			io_delete_device(dev);
		}
	}

	if(g_Drivers.size()){
		utils_error(
			"%d drivers are still in memory after stopping command.\n",
			g_Drivers.size()
			);
	}

	return __true;
}

