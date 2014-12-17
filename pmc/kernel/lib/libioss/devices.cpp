#include "precomp.h"

DEVICE_LIST	g_Devices;

void attach_tag_to_device(PRTK_TAG tag, PDEVICE_INFO d)
{
	assert(!tag->d.DeviceObj);
	assert(RtkIsListEmpty(&tag->d.DeviceLink));
	
	tag->d.DeviceObj = d;
	
	if(!d->d){
		return;
	}

	/*
		2005-7-30
		the address translation interface is supersuded by 
		the newer DISP_DB_ADD_TAG message passed to
		the dispatch interface, if implemented.
	*/
	if(d->d->dispatch){
		d->d->dispatch(d, DISP_DB_ADD_TAG, (int)tag);
	}else{
		tag->d.Value.Flags &= ~TF_Translated;
		if(d->d->address_translate){
			/*
				note, during address translation, the device driver
				might set other flags in tag->d.Value.Flags
			*/
			if(d->d->address_translate(tag)){
				tag->d.Value.Flags |= TF_Translated;
			}
		}else{
			// device tag address needs no translation
			tag->d.Value.Flags |= TF_Translated;
		}
	}

	RtkInsertTailList(&d->tags, &tag->d.DeviceLink);
}

void detach_tag_from_device(PRTK_TAG tag)
{
	PDRIVER_INFO drv;

	// TODO: notify the device we're depriving this tag
	
	if(tag->d.DeviceObj){
		drv = tag->d.DeviceObj->d;
		if(drv && drv->dispatch){
			drv->dispatch(tag->d.DeviceObj, DISP_DB_DROP_TAG, (int)tag);
		}
		// detach tag from the old device
		RtkRemoveEntryList(&tag->d.DeviceLink);
		RtkInitializeListHead(&tag->d.DeviceLink);
	}else{
		assert(RtkIsListEmpty(&tag->d.DeviceLink));
	}

	tag->d.DeviceObj = 0;
}

/*
*/
void attach_device_tags(PDEVICE_INFO d)
{
	RTK_CURSOR handle;
	PRTK_GROUP p;

	handle = cursor_open_first_subitem(HNODE_LOCAL_MACHINE);
	while(!cursor_is_end(handle)){
		p = (PRTK_GROUP)cursor_get_item(handle);
		RTK_CURSOR hTag;
		PRTK_TAG   pTag;
		hTag = cursor_open_first_subitem(handle);
		while(pTag = (PRTK_TAG)cursor_get_item(hTag)){
			if(pTag->s.Device == d->k){
				attach_tag_to_device(pTag, d);
			}
			cursor_move_next(hTag);
		}
		close_handle(hTag);
		cursor_move_next(handle);
	}
	close_handle(handle);
}


/*
	caller must have DB locked exclusively.
*/
static void detach_device_tags(PDEVICE_INFO dev)
{
	PRTK_TAG tag;
	PRTK_LIST_ENTRY head, entry, next;
	head = &dev->tags;
	entry = head->Flink;
	while(entry != head){
		next = entry->Flink;
		tag = RTK_CONTAINING_RECORD(entry, RTK_TAG, d.DeviceLink);
#if 0
		assert(tag->d.DeviceObj == dev);
		RtkRemoveEntryList(entry);
		RtkInitializeListHead(entry);
		tag->d.DeviceObj = 0;
#else
		detach_tag_from_device(tag);
#endif
		entry = next;
	}
}

/*
	create a device object and insert it into system's
	device list.

	Enrironment :
	db lock acquired exclusively
*/
IO_API PDEVICE_INFO PMC_API io_create_device(
	PDRIVER_INFO driverObj,
	PCDEVICE_KEY key,
	__uint extension_size
	)
{
	PDEVICE_INFO dev;
	pair<DEVICE_LIST::iterator, bool> pr;
	dev = (PDEVICE_INFO)new char[sizeof(DEVICE_INFO) + extension_size];
	if(!dev){
		return 0;
	}
	ZeroMemory(dev, sizeof(DEVICE_INFO) + extension_size);
	dev->k = *key;
	make_unified_key(dev->k);
	dev->d = driverObj;
	if(driverObj){
		driverObj->device_count++;
	}
	RtkInitializeListHead(&dev->tags);
	pr = g_Devices.insert(DEVICE_LIST::value_type(*key, dev));
	return dev;
}

/*
	remove a device object from system's device list

	Environment:

	db lock acquired exclusively.
*/
IO_API __bool PMC_API io_delete_device(PDEVICE_INFO dev)
{
	PDRIVER_INFO driverObj;
	DEVICE_LIST::iterator it;

	detach_device_tags(dev);

	it = g_Devices.find(dev->k);
	assert(it != g_Devices.end());
	driverObj = dev->d;
	g_Devices.erase(it);
	delete dev;

	if(driverObj){
		driverObj->device_count--;
		assert(driverObj->device_count >= 0);
		if(!driverObj->device_count){
			io_unload_driver(driverObj);
		}
	}	
	
	return __true;
}

/*
	enumerate device list

	Environment:

	db lock acquired either exclusively or non-exclusively
*/
IO_API __uint PMC_API io_get_devices(
	DEVICE_INFO * buffer, 
	__uint *maxcount
	)
{
	__uint count, i;
	count = min(g_Devices.size(), *maxcount);
	DEVICE_LIST::iterator p;
	p = g_Devices.begin();
	for(i=0; i<count; i++, p++){
		buffer[i] = *(p->second);
	}
	if(*maxcount < g_Devices.size()){
		*maxcount = g_Devices.size();
	}
	return count;
}

/*
	search for a device

	Environment :
	
	db lock acquired, either read or write
*/
IO_API PDEVICE_INFO PMC_API io_open_device(PCDEVICE_KEY key)
{
	DEVICE_LIST::iterator it;
	it = g_Devices.find(*key);
	if(it == g_Devices.end()){
		return 0;
	}
	return it->second;
}

/*
	caller must have DB locked exclusively
*/
IO_API __bool PMC_API io_start_device(PDEVICE_INFO dev)
{
	__bool r;	

	// a fake driver is created even if the module cannot be loaded
	assert(dev->d);
	
	if(!(dev->d->flags & DRIVER_FLAG_LOADED)){
		dev->error = IOSS_DRIVER_NOT_LOADED;
		r = __false;
	}else{
		if(!dev->d->start_device){
			r = __true;
		}else{
			r = dev->d->start_device(dev);
			if(!r){
				dev->error = IOSS_DEVICE_NOT_STARTED;
			}
		}
	}
	
	if(!r){
		dev->flags &= ~DF_Active;
	}else{
		dev->flags |= DF_Active;
		dev->error = 0;
	}
	
	if(r){
		utils_trace(
			"Device %s started.\n", 
			(char*)CDeviceName(dev->k)
			);
	}else{
		utils_error(
			"Cannot start device %s.\n", 
			(char*)CDeviceName(dev->k)
			);
	}
	
	return r;
}

/*
	caller must have DB locked exclusively.
*/
IO_API __bool PMC_API io_stop_device(PDEVICE_INFO dev)
{	
	if( !(dev->flags & DF_Active) ){
		return __true;
	}
	utils_trace("Stopping device %s\n", (char*)CDeviceName(dev->k));
	// newly created devices might not be attached to driver yet
	if(dev->d){
		if(dev->d->stop_device){
			if(!dev->d->stop_device(dev)){
				dev->flags &= ~DF_Active;
				utils_error(
					"Device %s not responding to STOP command.\n", 
					(char*)CDeviceName(dev->k)
					);
				return __false;
			}
		}
	}
	dev->flags &= ~DF_Active;
	utils_trace("Device %s stopped\n", (char*)CDeviceName(dev->k));
	
	return __true;
}

