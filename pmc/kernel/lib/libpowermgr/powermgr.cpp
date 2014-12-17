#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <powermgr.h>
#include <rtk_list_entry.h>

static int power_state = PWR_BACKUP;

struct CALLBACK_ITEM
{
	POWERMGR_CALLBACK	func;
	int context;
	RTK_LIST_ENTRY link;
};

static RTK_LIST_ENTRY cbs;

static void _check_queue()
{
	if(!cbs.Flink){
		init_powermgr();
	}
}

POWERMGR_API int PMC_API init_powermgr()
{
	power_state = PWR_BACKUP;
	RtkInitializeListHead(&cbs);
	return 0;
}

POWERMGR_API __bool PMC_API set_power_state(int newstate)
{
	CALLBACK_ITEM * ci;
	RTK_LIST_ENTRY * li;

	_check_queue();
	li = cbs.Flink;
	while(li != &cbs){
		ci = SAFE_CONTAINING_RECORD(li, CALLBACK_ITEM, link);
		if( !ci->func(newstate, ci->context) ){
			return __false;
		}
		li = li->Flink;
	}

	power_state = newstate;

	return __true;
}

POWERMGR_API int PMC_API get_power_state()
{
	_check_queue();
	return power_state;
}

POWERMGR_API __bool PMC_API register_power_callback(
	POWERMGR_CALLBACK cb, 
	int context
	)
{
	CALLBACK_ITEM * ci;
	_check_queue();
	ci = new CALLBACK_ITEM;
	if(!ci){
		return __false;
	}
	ci->func = cb;
	ci->context = context;
	RtkInsertTailList(&cbs, &ci->link);
	return __true;
}

POWERMGR_API __bool PMC_API unregister_power_callback(
	POWERMGR_CALLBACK cb, 
	int context
	)
{
	CALLBACK_ITEM * ci;
	RTK_LIST_ENTRY * li;

	_check_queue();
	li = cbs.Flink;
	while(li != &cbs){
		ci = SAFE_CONTAINING_RECORD(li, CALLBACK_ITEM, link);
		if(ci->func == cb && ci->context == context){
			RtkRemoveEntryList(li);
			delete ci;
			break;
		}
		li = li->Flink;
	}

	if(li == &cbs){
		return __false;
	}

	return __true;
}

static __bool PMC_API _power_state_changed(
	int ns, 
	int context
	)
{
	CPowerAware * pa;

	_check_queue();
	pa = reinterpret_cast<CPowerAware*>(context);
	return pa->OnPowerStateChanged(ns);
}

CPowerAware::CPowerAware()
{
	_check_queue();
	register_power_callback(_power_state_changed, (int)this);
}

CPowerAware::~CPowerAware()
{
	unregister_power_callback(_power_state_changed, (int)this);
}
