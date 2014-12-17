#include "precomp.h"

static CArchiveCache * cache;

LIBHISPROXY_API void PMC_API initHisProxy()
{
	init_network(RTK_SKIP_STANDARD_BUSES, 0);
	initArchiveCache();
	cache = new CArchiveCache;
}

LIBHISPROXY_API void PMC_API uninitHisProxy()
{
	if(cache){
		delete cache;
		cache = 0;
	}
	uninitArchiveCache();
	uninit_network();
}

LIBHISPROXY_API void PMC_API queryHisData(
	const TAG_NAME * tag, 
	const FILETIME *startTime, 
	long interval, 
	long length
	)
{
	if(!cache){
		return;
	}
	cache->setNames(tag, 1);
	hislog_key_t st;
	st = hislogKeyByTime(startTime);
	cache->setTimeSpan(st, interval, length);
	cache->query(1000);
}

LIBHISPROXY_API __bool PMC_API getHisData(hislog_item_t * value)
{
	if(!cache->cacheFlag(0)){
		value->Flags &= ~TF_Valid;
		return __false;
	}
	memcpy(
		value, 
		cache->cacheValue(0, 0), 
		cache->returnedValueCount(0) * sizeof(hislog_item_t)
		);
	return __true;
}
