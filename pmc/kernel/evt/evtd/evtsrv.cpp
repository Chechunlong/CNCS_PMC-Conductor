#include "precomp.h"
#pragma hdrstop

#include "evtsrv.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "../libhis.h"
#include "../event.h"
#include "object.h"

#include <string>

using namespace std;

#define ALARMPOOL	1024
#define ALARMLEN	1024
typedef CPMCArchive<CPMCEvent, ALARMLEN> CPMCAlarms;

#define OPERATEPOOL 1024
#define OPERATELEN	1024
typedef CPMCArchive<CPMCEvent, OPERATELEN> CPMCOperates;

#define SOEPOOL 1024
#define SOELEN	1024
typedef CPMCArchive<CPMCEvent, SOELEN> CPMCSoes;

#ifdef _WIN32
#pragma comment(lib, "libutils.lib")
#pragma comment(lib, "libntservice.lib")
#pragma comment(lib, "librtk.lib")
#pragma comment(lib, "librtknet.lib")
#pragma comment(lib, "libhis.lib")
#pragma comment(lib, "librtkproxy.lib")
#pragma comment(lib, "librtdb.lib")
#endif

#define MAX_SOE_MOD 16
#define MAX_SOE_TAG 16 * MAX_SOE_MOD
struct soe_msg_t{
	char off2on[128];
	char on2off[128];
}soe_msgs[MAX_SOE_TAG];
char soeGroup[34];

struct CEvtAswThread : public CRtkThread
{
	CEvtQryPkt qryPkt;
	char heap[SIZE_OF_ONE_PKT];
	char src[17];
	int port;

	virtual __uint run();
};

static bool bEndWorkThread = false;
static CPMCAlarms * alarms;
static CPMCOperates * operates;
static CPMCSoes * soes;
CPMCEvent events[MAX_GET_RECORD];
static RTK_GUID uidOld[16];
static int ptLastUid;

__uint CEvtAswThread::run()
{
	CEvtAswPkt &aswPkt = *((CEvtAswPkt *)heap);
	int count = 0;

	switch(qryPkt.eClass){
	case AC_Alarm:
	case AC_AckAlarm:
	case AC_CancelAlarm:
	case AC_Online:
	case AC_Offline:
		count = alarms->getRecord(qryPkt.stm, qryPkt.etm, qryPkt.count, events);
		break;
	case AC_WriteDevice:
		count = operates->getRecord(qryPkt.stm, qryPkt.etm, qryPkt.count, events);
		break;
	}

	int pcount;
	CMulticastSocket sck;
	RTK_TIME	t1, t2;
	
	sck.Socket();
	
	int length=65535;
	sck.SetSockOpt(SO_RCVBUF, (void *)&length, sizeof(length));
	sck.SetSockOpt(SO_SNDBUF, (void *)&length, sizeof(length));

	utils_debug(
		"Answering query from %s:%d of class %d with %d entries.\n", 
		src,
		port,
		qryPkt.eClass,
		count
		);

	rtk_time_mark(&t1);
	aswPkt.gid = qryPkt.gid;
	aswPkt.id = 0;
	aswPkt.count = COUNT_IN_ONE_PKT;
	pcount = 0;
	CPMCEvent * pEvent = events;
	while(count >= COUNT_IN_ONE_PKT){
		memcpy(
			// aswPkt.events, 
			EVT_ARRAY_OF(aswPkt),
			pEvent,
			COUNT_IN_ONE_PKT * sizeof(CPMCEvent)
			);
		sck.SendTo(
			&aswPkt, 
			sizeof(CEvtAswPkt) + COUNT_IN_ONE_PKT * sizeof(CPMCEvent),
			port, 
			src
			);
		pEvent += COUNT_IN_ONE_PKT;
		aswPkt.id += COUNT_IN_ONE_PKT;
		pcount++;
		count -= COUNT_IN_ONE_PKT;
		Sleep(100);
	}
	if(count){
		aswPkt.count = count;
		memcpy(
			// aswPkt.events, 
			EVT_ARRAY_OF(aswPkt),
			pEvent,
			count * sizeof(CPMCEvent)
			);
		pcount++;
		sck.SendTo(
			&aswPkt, 
			sizeof(CEvtAswPkt) + count * sizeof(CPMCEvent),
			port, 
			src
			);
	}
	rtk_time_mark(&t2);

	utils_debug(
		"%d packets sent in %.3f seconds.\n", 
		pcount,
		rtk_time_diff(&t2, &t1) 
		);

	Sleep(1000);

	delete this;

	return 1;
}

CEvtSocket::CEvtSocket()
{
	ptLastUid = -1;
	for(int i = 0; i < 16; i++){
		memset(&uidOld[i], 0, sizeof(RTK_GUID));
	}
}

int CEvtSocket::OnData(void * buf,int length,int port,char * src_addr)
{
	CEvtQryPkt *p = (CEvtQryPkt*)buf;
	
	if(length != sizeof(CEvtQryPkt) ){
		return 0;
	}

#if 0
	CMulticastSocket sock;
	sock.Create(0);
	sock.SendTo(buf, length, port, src_addr);
#endif

	for(int i = 0; i < 16; i++){
		if(p->gid == uidOld[i]){
			return 0;
		}
	}
	ptLastUid = (ptLastUid + 1) % 16;
	uidOld[ptLastUid] = p->gid;

	CEvtAswThread *pat = new CEvtAswThread;
	
	memcpy(&(pat->qryPkt), buf, sizeof(CEvtQryPkt));
	pat->port = port;
	memset(pat->src, 0, sizeof(pat->src));
	strncpy(pat->src, src_addr, sizeof(pat->src));
	pat->start();

	return 0;
}

static void formatEvent(int rank, ALARM_CLASS ac, const char *msg, PCRTK_ADDR src, CPMCEvent *evt)
{
	evt->valid = true;
	switch (ac){
	case AC_Alarm:
	case AC_AckAlarm:
	case AC_CancelAlarm:
	case AC_Online:
	case AC_Offline:
	case AC_WriteDevice:
		evt->eClass = ac;
		strncpy(evt->data, msg, sizeof(evt->data));
		evt->data[sizeof(evt->data) - 1] = 0;
		evt->src = src->host;
		evt->rTime = getCurrentTime();
		evt->eTime = evt->rTime;
		break;
	}
}

static void _cdecl evtCallBack(int rank, ALARM_CLASS ac, const char *msg, PCRTK_ADDR src)
{
	CPMCEvent evt;
	formatEvent(rank, ac, msg, src, &evt);

	switch (ac){
	case AC_Alarm:
	case AC_AckAlarm:
	case AC_CancelAlarm:
	case AC_Online:
	case AC_Offline:
		alarms->addNewRecord(&evt);
		break;
	case AC_WriteDevice:
		operates->addNewRecord(&evt);
		break;
	}

	printf("%s\n", msg);
}

void CEvtSrv::Stop()
{
	ReportStatus(SERVICE_STOP_PENDING, 3000);
	printf("stop гн evtd\n");

	KillTimer(NULL, idTimer);
	KillTimer(NULL, idTimerSoe);
	KillTimer(NULL, idTimerAlarm);

	while(!bEndWorkThread){
		bEndWorkThread = true;
	}

	::PostThreadMessage(dwMainThreadId, WM_QUIT, 0, 0);	
}

void __stdcall CEvtSrv::flush(struct HWND__ *,unsigned int,unsigned int,unsigned long)
{
	alarms->flush2file();
	operates->flush2file();
}

void __stdcall CEvtSrv::raise_alarms(struct HWND__ *,unsigned int,unsigned int,unsigned long)
{
	RTK_CURSOR hNode, hGroup, hTag;

	int	countNode = 0;
	int countGroup = 0;
	int countTag = 0;

	if(!lock_rtdb(false, 1000)){
		return;
	}

	hNode=open_first_node();
	while(!cursor_is_end(hNode)){
		hGroup = cursor_open_first_subitem(hNode);
		while(!cursor_is_end(hGroup)){
			hTag = cursor_open_first_subitem(hGroup);
			while(!cursor_is_end(hTag)){
				countTag++;
				cursor_move_next(hTag);
			}
			close_handle(hTag);
			countGroup++;
			cursor_move_next(hGroup);
		}
		close_handle(hGroup);
		countNode++;
		cursor_move_next(hNode);
	}
	close_handle(hNode);

	printf("tag count is %d.\n", countTag);
	printf("group count is %d.\n", countGroup);
	printf("node count is %d.\n\n", countNode);

	unlock_rtdb();
}


void __stdcall CEvtSrv::record_soe(struct HWND__ *,unsigned int,unsigned int,unsigned long)
{
	static int last_ch = -1, last_val = -1;
	static TAG_VALUE last_tvv;

	char str[1024];
	char strMsg[256];
	TAG_NAME tn[12];
	//TAG_NAME tn_flag, tn_id, tn_yy, tn_mm, tn_dd, tn_hh, tn_nn, tn_ss, tn_ms, tn_ch, tn_val, tn_idc;
	struct pmc_value_t tv[12];
    TAG_VALUE tvv;
	bool valid;
	int i, j;
	CPMCEvent evt;
	TIME_ZONE_INFORMATION tz;
	SYSTEMTIME utm, ltm;

	int ch, val;

	for(i = 1; i <= MAX_SOE_MOD; i++){
		sprintf(str, "%s.soe%d_flag", soeGroup, i);
		tagname_by_text(&tn[0], str);
		sprintf(str, "%s.soe%d_id", soeGroup, i);
		tagname_by_text(&tn[1], str);
		sprintf(str, "%s.soe%d_yy", soeGroup, i);
		tagname_by_text(&tn[2], str);
		sprintf(str, "%s.soe%d_mm", soeGroup, i);
		tagname_by_text(&tn[3], str);
		sprintf(str, "%s.soe%d_dd", soeGroup, i);
		tagname_by_text(&tn[4], str);
		sprintf(str, "%s.soe%d_hh", soeGroup, i);
		tagname_by_text(&tn[5], str);
		sprintf(str, "%s.soe%d_nn", soeGroup, i);
		tagname_by_text(&tn[6], str);
		sprintf(str, "%s.soe%d_ss", soeGroup, i);
		tagname_by_text(&tn[7], str);
		sprintf(str, "%s.soe%d_ms", soeGroup, i);
		tagname_by_text(&tn[8], str);
		sprintf(str, "%s.soe%d_ch", soeGroup, i);
		tagname_by_text(&tn[9], str);
		sprintf(str, "%s.soe%d_val", soeGroup, i);
		tagname_by_text(&tn[10], str);
		sprintf(str, "%s.soe%d_idc", soeGroup, i);
		tagname_by_text(&tn[11], str);

		proxy_read_tags(12, tn, tv, 0);
		valid = true;
		for(j = 0; j < 12; j++){
			if(!(tv[j].Flags & TF_Valid)){
				valid = false;
			}
		}

		// flag
		if(valid && tv[0].Value.u8){
			// id
			// yy
			utm.wYear = 2000 + tv[2].Value.u16;
			// mm
			utm.wMonth = tv[3].Value.u16;
			// dd
			utm.wDay = tv[4].Value.u16;
			// hh
			utm.wHour = tv[5].Value.u16;
			// nn
			utm.wMinute = tv[6].Value.u16;
			// ss
			utm.wSecond = tv[7].Value.u16;
			// ms
			utm.wMilliseconds = tv[8].Value.u16;
			// ch
			ch = tv[9].Value.u8 + (i - 1) * 16;
			// val
			val = tv[10].Value.u8;
			// idc
			if(ch == last_ch && val == last_val){
				proxy_write_tags(1, &tn[11], &last_tvv);
				break;
			}else{
				last_ch = ch;
				last_val = val;
			}

			GetTimeZoneInformation(&tz);
			SystemTimeToTzSpecificLocalTime(&tz, &utm, &ltm);
			
			// clear this soe
			tvv.iValue = tv[1].Value.iValue;
			proxy_write_tags(1, &tn[11], &tvv);
			last_tvv = tvv;
			if(val == 0x0f){
				sprintf(strMsg, "%s@%d-%d-%d %d:%d:%d %dms.", soe_msgs[ch].off2on, ltm.wYear, ltm.wMonth, ltm.wDay, ltm.wHour, ltm.wMinute, ltm.wSecond, ltm.wMilliseconds);
			}else{
				sprintf(strMsg, "%s@%d-%d-%d %d:%d:%d %dms.", soe_msgs[ch].on2off, ltm.wYear, ltm.wMonth, ltm.wDay, ltm.wHour, ltm.wMinute, ltm.wSecond, ltm.wMilliseconds);
			}
			strncpy(evt.data, strMsg, sizeof(evt.data));
			evt.data[sizeof(evt.data) - 1] = 0;
			evt.rTime = getCurrentTime();
			evt.eTime = evt.rTime;
			soes->addNewRecord(&evt);
			soes->flush2file();

			break;
		}
	}
}

/*
DWORD GetPrivateProfileString(
  LPCTSTR lpAppName,
  LPCTSTR lpKeyName,
  LPCTSTR lpDefault,
  LPTSTR lpReturnedString,
  DWORD nSize,
  LPCTSTR lpFileName
);

*/
int CEvtSrv::init_soe(string msg_file)
{
	string strLine; 
	char   strLineBuf[1024];
	int    iLine;
	FILE   * fp;
	CArgs args;

	GetPrivateProfileString("evtd", "soegroup", "default.soegroup", soeGroup, 34, get_config_file());

	fp = fopen(msg_file.data(),"rt");
	if(!fp){
		utils_error("Cannot open soe message file:%s\n", msg_file.data()); 	   
		return 0;
	}

	iLine = 0;
	while(!feof(fp)){
		if( !fgets(strLineBuf,sizeof(strLineBuf),fp) ) break;
		if(strLineBuf[strlen(strLineBuf)-1]=='\n'){
			strLineBuf[strlen(strLineBuf)-1]=0;
		}
		if(strLineBuf[0] == '#'){
			continue;
		}

		parse_arg_ey(strLineBuf, &args, ",\t\r\n");	
		if(args.argc != 3){
			continue;
		}
		
		strncpy(soe_msgs[iLine].off2on, args.argv[1], 128);
		soe_msgs[iLine].off2on[127] = 0;
		strncpy(soe_msgs[iLine].on2off, args.argv[2], 128);
		soe_msgs[iLine].on2off[127] = 0;

		iLine++;
		if(iLine == MAX_SOE_TAG){
			break;
		}
	}

	fclose(fp);

	return 1;
}

void CEvtSrv::Run(DWORD argc, LPTSTR * argv)
{
	init_proxy(0, PROXY_ENABLE_DISPATCHER | PROXY_SILENT | PROXY_ENABLE_BGLOADER);
	
	dwMainThreadId=::GetCurrentThreadId();

	string str, s1, s2, s3;
	
	str = string(get_working_dir()) + string("var");
	mkdir(str.c_str());
	str = str + "/evtd";
	mkdir(str.c_str());
	s1 = str + "/alarm";
	s2 = str + "/operate";
	s3 = str + "/soe";
	mkdir( s1.c_str() );
	mkdir( s2.c_str() );
	mkdir( s3.c_str() );
	
	alarms = new CPMCAlarms;
	if(!alarms){
		return;
	}
	alarms->initialize(s1.c_str(), ALARMPOOL);

	operates = new CPMCOperates;
	if(!operates){
		return;
	}
	operates->initialize(s2.c_str(), OPERATEPOOL);

	soes = new CPMCSoes;
	if(!soes){
		return;
	}
	soes->initialize(s3.c_str(), SOEPOOL);

	g_ProxyDispatchTable.OnAlarm = evtCallBack;

	//int ret = sck.Create(15426 + 100);
	sck.JoinGroup("230.13.15.19", 15426+100);

	idTimer = SetTimer(NULL, 0, 60 * 1000, flush);

	str = str + "/soe_msg.csv";
	if(init_soe(str)){
		idTimerSoe = SetTimer(NULL, 0, 1000, record_soe);
	}
	idTimerAlarm = SetTimer(NULL, 0, 100, raise_alarms);

	ReportStatus(SERVICE_RUNNING);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	uninit_proxy();
}
