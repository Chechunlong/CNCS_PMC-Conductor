#include "precomp.h"

DRIVER_LIST g_Drivers;
static RTDB_DISPATCH_TABLE s_Handler;

#ifndef _WIN32
#define LoadLibrary(name) dlopen(name, 0)
#define HINSTANCE void *
#define GetProcAddress(handle, name) dlsym(handle, name)
#define FARPROC void *
#define FreeLibrary(handle) dlclose(handle)
#endif

#ifdef _WIN32
#define DLL_SUFFIX ".DLL"
#else
#define DLL_SUFFIX ".so"
#endif

__bool _load_module(DRIVER_INFO & driver)
{
	HINSTANCE h;

	utils_trace("Loading IO driver %s\n", driver.dllname);

	driver.flags &= ~DRIVER_FLAG_LOADED;
	
	h = LoadLibrary(driver.dllname);
	if( !h ){
		strncat(driver.dllname, DLL_SUFFIX, sizeof(driver.dllname));
		driver.dllname[ sizeof(driver.dllname) - 1] = 0;
		h = LoadLibrary(driver.dllname);
	}

	if( !h ){
		utils_error("Cannot load driver %s.\n", driver.dllname); 
		return __false;
	}
	
	driver.plugin_handle = (void*)h;
	driver.flags |= DRIVER_FLAG_LOADED;

#define check_old(p) assert(!GetProcAddress(h, #p))
	check_old(init);
	check_old(start);
	check_old(stop);

	(FARPROC&)driver.load = GetProcAddress(h, "load");
	(FARPROC&)driver.unload  = GetProcAddress(h, "unload");
	(FARPROC&)driver.start_device = GetProcAddress(h, "start_device");
	(FARPROC&)driver.stop_device = GetProcAddress(h, "stop_device");
	(FARPROC&)driver.address_translate = GetProcAddress(h, "address_translate");
	(FARPROC&)driver.update_tag = GetProcAddress(h, "update_tag");
	(FARPROC&)driver.write_device = GetProcAddress(h, "write_device");
	(FARPROC&)driver.dispatch = GetProcAddress(h, "dispatch");
	if(!driver.dispatch){
		(FARPROC&)driver.dispatch = GetProcAddress(h, "_dispatch@12");
	}
#ifdef _WIN32
	get_file_version(driver.dllname, (PLARGE_INTEGER)&driver.version);
	get_file_description(
        driver.dllname,
        driver.description,
        sizeof(driver.description)
        );
#else
    //
#endif
	utils_trace("IO driver %s loaded at 0x%08x\n", driver.dllname, driver.plugin_handle);

	return __true;
}

PDRIVER_INFO get_driver(PCDEVICE_KEY key)
{
	PDEVICE_INFO dev;
	dev = io_open_device(key);
	if(!dev){
		return 0;
	}
	return dev->d;
}

IO_API PDRIVER_INFO PMC_API io_load_driver(PCVENDOR_KEY v, PCDEVTYPE_KEY t)
{		
	DRIVER_LIST::iterator it;
	DRIVER_INFO driver;
	string		infofile;

	ZeroMemory(&driver, sizeof(DRIVER_INFO));

	infofile = get_exe_dir();
	infofile += "infs/";
	infofile += (char*)CVendorName(*v);
	infofile += ".inf";
	GetPrivateProfileString(
		(char*)CDevTypeName(*t),
		"module",
		"",
		driver.dllname,
		sizeof(driver.dllname),
		infofile.data()
		 );	
	for(it = g_Drivers.begin(); it != g_Drivers.end(); it++){
		if( !strnicmp(it->dllname, driver.dllname, sizeof(it->dllname)) ){
			return &(*it);  
		}
	}	

	driver.vendor.key = *v;
	driver.type.key = *t;

	GetPrivateProfileString(
		"oem",
		"vendor",
		"",
		driver.vendor.description,
		sizeof(driver.vendor.description),
		infofile.data()
		);
	GetPrivateProfileString(
		(char*)CDevTypeName(*t),
		"description",
		"",
		driver.type.description,
		sizeof(driver.type.description),
		infofile.data()
		);
	
	if(_load_module(driver)){
		if(driver.load){
			driver.load(&driver);
		}
	}
	
	it = g_Drivers.insert(g_Drivers.end(), driver);
	if(it == g_Drivers.end()){
		io_unload_driver(&driver);
		return 0;
	}
	
	return &(*it);
}

IO_API __bool PMC_API io_unload_driver(PDRIVER_INFO driver)
{
	DRIVER_LIST::iterator it;

	utils_trace("Unloading driver %s\n", driver->dllname);
	for(it = g_Drivers.begin(); it != g_Drivers.end(); it++){
		if(&(*it) == driver){
			break;
		}
	}
	if(it == g_Drivers.end()){
		DEBUG_PRINTF((
			"Warning : unload a non-existing driver : 0x%08x\n", driver
			));
		return __false;
	}

	if(driver->device_count){
		utils_error(
            "Driver %s cannot unload with %d devices active.\n",
            driver->dllname,
            driver->device_count
            );
		return __false;
	}

	if(driver->unload){
		if(!driver->unload()){
			DEBUG_PRINTF((
				"Error : driver %s rejected unload request.\n",
				driver->dllname
				));
			return __false;
		}
	}

	if(driver->plugin_handle){
		FreeLibrary((HINSTANCE)driver->plugin_handle);
	}
	g_Drivers.erase(it);
	return __true;
}

