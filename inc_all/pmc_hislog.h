/*
	data structures and types shared by archive subsystem and
	its clients.

	created
	-jhunter@tsinghua.org.cn, 2004/8/9
*/
#ifndef __pmc_hislog_h__
#define __pmc_hislog_h__

#include <librtdb.h>

#define HISLOG_SERVICE_NAME "hisd"
#define HISLOG_SERVICE_COMMENT "PMC Archive Subsystem"

/*
	error numbers
*/
#define HISLOG_MODULE_NUM 'HS'

#define HISLOG_ERROR(code) PMC_ERROR(HISLOG_MODULE_NUM, (code))

#define HISLOG_TIME_OUT_OF_RANGE \
	HISLOG_ERROR(-1)
	
#define HISLOG_INVALID_ARCHIVE \
	HISLOG_ERROR(-2)

/*
	define packet type constants used on the hislog vbus channel
*/
#define PT_QueryArchivedData	0x00000001

/*
	hislog_key_t is the internal representation of
	time in hislog.
*/
typedef __i64 hislog_key_t;
typedef struct pmc_value_t hislog_item_t;

#include <pshpack1.h>

struct hisqry_pkt_t{
	RTK_GUID	m_gid;
	hislog_key_t	m_time;
	int 	m_step;
	int 	m_count;
	int 	m_tagcount;
	// TAG_NAME m_names[0];
}PACKED;

struct hisack_pkt_t{
	RTK_GUID	m_gid;
	TAG_NAME	m_tagName;
	__uint		m_count;
	// int m_ret;	//return 0 mean ok, it's seem we should never return error
	// int m_id;		//0 to MAX_QUERY_TAG-1
	// int m_count;
	// struct pmc_value_t value[0];
};

#define HISLOG_MAX_QUERY_COUNT 		600
#define HISLOG_MAX_QUERY_TAG_COUNT 	15

#include <poppack.h>

#endif
