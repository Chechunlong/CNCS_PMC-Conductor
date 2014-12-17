// GpsService.cpp: implementation of the CGpsService class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <crtdbg.h>
#include <math.h>

#include <io.h>			//!! TCW MOD
#include <fcntl.h>		//!! TCW MOD
#include <fstream.h>

#include "GpsService.h"
#include "pcomm.h"
#include "LimitSingleInstance.h"

#pragma comment (lib, "pcomm.lib")

//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
//const int c_AdjDelta = 3600 * 24 - 1;
const int c_AdjDelta = 59;
const double c_Step = (c_AdjDelta + 1)* 10000000.;

static int iPort;
static double dDrift = 0.;
static DWORD dwTmInc;

static CLimitSingleInstance g_SingleInstanceObj(TEXT("PMC_GPSD")); 

//////////////////////////////////////////////////////////////////////
// 有关时间的函数
//////////////////////////////////////////////////////////////////////

//调整对时权利
inline bool EnableAdjustTimePrivilege(bool bEnable)
{
	HANDLE hProcess=GetCurrentProcess();
	HANDLE hToken;

	if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken)) return false;

	TOKEN_PRIVILEGES tpNew;
	if(!LookupPrivilegeValue(NULL,SE_SYSTEMTIME_NAME,&tpNew.Privileges[0].Luid)) return false;

	if(bEnable) tpNew.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
	else tpNew.Privileges[0].Attributes=0;
	tpNew.PrivilegeCount=1;
		
	if(!AdjustTokenPrivileges(hToken,FALSE,&tpNew,0,NULL,NULL)) return false;

	return true;
}

//获取参考时间和时间差
inline bool GetRefDiff(char *buf, int len, FILETIME *ptmRef,LARGE_INTEGER *pliDiff)
{
    static SYSTEMTIME tmSys = { 0, 0, 0, 0, 0, 0, 0};
    static char cs[3] = {0, 0, 0};
    // 校验包的有效性
    if(len != 72){
        printf("Incorrect NMEA sentence length\n");
        return false;
    }
    if(memcmp(buf, "$GPRMC", 6) != 0){
        printf("Bad NMEA sentence head\n");
        return false;
    }
    // ddmmyy
    memcpy(cs, &buf[53], 2);
    tmSys.wDay = atoi(cs);
    memcpy(cs, &buf[55], 2);
    tmSys.wMonth = atoi(cs);
    memcpy(cs, &buf[57], 2);
    tmSys.wYear = 2000 + atoi(cs);
    // hhmmss
    memcpy(cs, &buf[7], 2);
    tmSys.wHour = atoi(cs);
    memcpy(cs, &buf[9], 2);
    tmSys.wMinute = atoi(cs);
    memcpy(cs, &buf[11], 2);
    tmSys.wSecond = atoi(cs);

    //if('A' == buf[14]){
        SystemTimeToFileTime(&tmSys, ptmRef);
        FILETIME tmFile;
		GetSystemTimeAsFileTime(&tmFile);
        LARGE_INTEGER liLocal;
        LARGE_INTEGER liRef;
        memcpy(&liLocal, &tmFile, sizeof(LARGE_INTEGER));
        memcpy(&liRef, ptmRef, sizeof(LARGE_INTEGER));
        pliDiff->QuadPart = liLocal.QuadPart - liRef.QuadPart;
        return true;
    //}else{
    //    printf("NAV receive warning\n");
    //    return false;
    //}
}

inline bool liAbsBiger(LARGE_INTEGER liVal, LARGE_INTEGER liRef)
{
    if(liVal.QuadPart > liRef.QuadPart || liVal.QuadPart < -liRef.QuadPart){
        return true;
    }else{
        return false;
    }
}

inline bool SetAdjustment(DWORD dwTmAdj)
{
	if(EnableAdjustTimePrivilege(true)){
		if(SetSystemTimeAdjustment(dwTmAdj, false)){
            printf("Set time adjustment succeed! adj:%d\n", dwTmAdj);
            return true;
		}else{
            printf("Set time adjustment fail! err code:%d\n", GetLastError());
		}
		EnableAdjustTimePrivilege(false);

        return false;
    }

    return false;
}

inline void LoadDrift()
{
    DWORD dwTmAdj;
    BOOL bDisable;

	if(GetSystemTimeAdjustment(&dwTmAdj,&dwTmInc,&bDisable)){
        // 从文件中读取 drift 记录
		fstream fsDrift("drift.log", ios::in|ios::out|ios::binary, filebuf::sh_read || filebuf::sh_write);
		fsDrift >> dDrift;
		if(fsDrift.fail()){	//drift file is empty
			fsDrift.clear();
            SetAdjustment(dwTmInc);
        }else{
		    dwTmAdj=(DWORD)(dwTmInc * (1. + dDrift));
            printf("Load drift from drift.log, val:%f\n", dDrift);
            SetAdjustment(dwTmAdj);
        }
    }
}

inline void SetDrift(FILETIME tmRef, FILETIME tmLastAdj, LARGE_INTEGER liDiff, LARGE_INTEGER liOldDiff)
{
    const int c_AvgCount = 8;
    static int iAvgCount = 0;
    static double dAvgDrift = 0.;
    static double dOldDisturb =0.;    

    DWORD dwTmAdj;

    //计算新的 drift
    LARGE_INTEGER liTemp1, liTemp2;
    memcpy(&liTemp1, &tmLastAdj, sizeof(LARGE_INTEGER));
    memcpy(&liTemp2, &tmRef, sizeof(LARGE_INTEGER));
    double dTimeDelta = (double)(liTemp2.QuadPart - liTemp1.QuadPart);
    double dDiffDelta = (double)(liDiff.QuadPart - liOldDiff.QuadPart);
    dDrift = dDrift + dOldDisturb - dDiffDelta / dTimeDelta;
    double dDisturb = -(double)liDiff.QuadPart / c_Step;
    dOldDisturb = dDisturb;

// for debug only
printf("old-diff:%d ", liOldDiff.QuadPart / 10000);
printf("diff:%d ", liDiff.QuadPart / 10000);
printf("delta:%d\n", (liDiff.QuadPart - liOldDiff.QuadPart) / 10000);
printf("delta/t:%f drift:%f disturb:%f\n\n", dDiffDelta / dTimeDelta, dDrift, dDisturb);

	dwTmAdj=(DWORD)(dwTmInc * (1. + dDrift + dDisturb));
    //dwTmAdj = (DWORD)(dwTmInc * (1. + dDisturb));
    SetAdjustment(dwTmAdj);

    iAvgCount ++;
    dAvgDrift += dDrift;
    if(c_AvgCount == iAvgCount){
        dAvgDrift = dAvgDrift / (double)iAvgCount;
		fstream fsDrift("drift.log",ios::in|ios::out|ios::binary,filebuf::sh_read||filebuf::sh_write);
		fsDrift<<dAvgDrift;
        iAvgCount = 0;
        dAvgDrift = 0.;
    }
}

//////////////////////////////////////////////////////////////////////
// 串口回调服务
//////////////////////////////////////////////////////////////////////
static VOID CALLBACK TermIrq(int port)
{
    //printf("get a line\n");
    const LARGE_INTEGER c_MaxDiff = {200000000, 0}; // 20 seconds
    const LARGE_INTEGER c_HalfMaxDiff = {100000000, 0}; // 10 seconds

    static bool bFirst = true;
    static char buf[1024];
    static FILETIME tmRef;
    static FILETIME tmLastAdj;
    static LARGE_INTEGER liDiff;
    static LARGE_INTEGER liOldDiff = {0, 0};
    static int iCount = 0;

    int ret = sio_read(iPort, buf, 1024);

    //if(0 == iCount){
        if(GetRefDiff(buf, ret, &tmRef, &liDiff)){        
            if(bFirst || liAbsBiger(liDiff, c_MaxDiff)){ // 第一次启机或时间偏差大于 1 秒，直接对时
                SYSTEMTIME tmSys;
                FileTimeToSystemTime(&tmRef, &tmSys);
                SetSystemTime(&tmSys);
                if(bFirst){
                    printf("It's first time, set local time to refrence time.\n\n");
                }else{
                    printf("Time bias bigger than %d ms, force local time equal to refrence time.\n\n", c_MaxDiff.QuadPart / 10000);
                }
                tmLastAdj = tmRef;
                iCount = 0;
                bFirst = false;
            }else{ //调整时钟偏差
				//为了可靠，只保留直接对时部分
				/*
                SetDrift(tmRef, tmLastAdj, liDiff, liOldDiff);
                tmLastAdj = tmRef;
                liOldDiff.QuadPart = liDiff.QuadPart;
				*/
            }
        }
    //}

    //iCount++;
    //if(iCount >= c_AdjDelta) iCount = 0;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGpsService::CGpsService()
		: CNTService(TEXT("gpsd"), TEXT("PMC - GPS Synchronization Service"))
{

}

CGpsService::~CGpsService()
{

}

void CGpsService::Run(DWORD, LPTSTR *)
{
	// report to the SCM that we're about to start
	ReportStatus(SERVICE_START_PENDING);

    if ( g_SingleInstanceObj.IsAnotherInstanceRunning() ){
        printf("Another gpsd instance is already running.\n");
        return;
    }
	
	// report SERVICE_RUNNING immediately before you enter the main-loop
	// DON'T FORGET THIS!
	ReportStatus(SERVICE_RUNNING);

    Init();

	// enter main-loop
	// If the Stop() method sets the event, then we will break out of
	// this loop.
    hStop = ::CreateEvent(0, TRUE, FALSE, 0);
    WaitForSingleObject(hStop,INFINITE);
    if(hStop){
        ::CloseHandle(hStop);
    }
}

void CGpsService::Stop()
{
	// report to the SCM that we're about to stop
	// Note that the service might Sleep(), so we have to tell
	// the SCM
	// "The next operation may take me up to 11 seconds. Please be patient."
	ReportStatus(SERVICE_STOP_PENDING, 11000);
    
    if(hStop) ::SetEvent(hStop);
}

bool CGpsService::Init()
{
    LoadDrift();

    char lpFilename[_MAX_PATH];
    memset(lpFilename,0,_MAX_PATH);
    GetModuleFileName( NULL,lpFilename,_MAX_PATH);
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath( lpFilename, drive, dir, fname, ext );
	char path[_MAX_PATH];
	sprintf(path, "%s%s\\gps.ini", drive, dir);

    iPort = ::GetPrivateProfileInt("com","port",1,path);
    printf("GPS NMEA Sentences use port %d\n", iPort);

    int ret;
    // open port
    ret = sio_open(iPort);
    if (ret != SIO_OK) {
        //SIO_BADPORT	-1	Port is not opened in advance
        //SIO_WIN32FAIL	-8	Calling Win32 function failed
        //Call GetLastError to get the error code
        printf("Can't open port, err code:%d\n",ret);
        return false;
    }
    // set port mode
    ret = sio_ioctl(iPort, B4800, P_NONE | BIT_8 | STOP_1);
    // set irq
    ret = sio_term_irq(iPort, TermIrq, 10);
    if (ret != SIO_OK) {
        //SIO_BADPORT	-1	Port is not opened in advance
        //SIO_WIN32FAIL	-8	Calling Win32 function failed
        //Call GetLastError to get the error code
        printf("Can't set irq, err code:%d\n",ret);
        return false;
    }
    printf("Set irq success\n");

    return true;
}
