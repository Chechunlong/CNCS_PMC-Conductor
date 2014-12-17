// testshl_cons.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include <process.h>
#include "private/rtkgui.h"


BOOL g_bPause = FALSE;
HANDLE ctx;
HANDLE hEvent;
 
int CALLBACK testwaitproc(HANDLE ctx, UINT uMsg, LPARAM lParam)
{
    uMsg = uMsg;
    switch(uMsg)
    {
    case WDN_BTNCLICK:
        switch(lParam)
        {
        case WDC_PAUSE:
			g_bPause = TRUE;
			break;
		case WDC_RESUME:
			g_bPause = FALSE;
			break;
		case WDC_CANCEL:
			
			SetEvent(hEvent);
			return -1; // kill dialog
			break;
        }
        break;
    }
    return 1;
}


int main(int argc, char* argv[])
{
    int i = 0;
    char szState[255];
	
	HMODULE hSkinLib;
	void    (WINAPI * lpfnLoadSkin)();
	

	
	hSkinLib = LoadLibrary("dfvsskin.dll");
	
	(FARPROC&)lpfnLoadSkin = GetProcAddress(hSkinLib, "1");

	if (lpfnLoadSkin)
	{
		lpfnLoadSkin();
	}
/*
	RtkGuiWDEnableSkin(TRUE);

    ctx = RtkGuiWDStart(WDS_PROGRESS|WDS_CANCEL|WDS_STATE|WDS_TIMEREMAIN|WDS_TIMELEFT,testwaitproc); 
    
    // 主线程必须首先加载皮肤，然后子线程才能对控件子类化
    RtkGuiWDSetCaption(ctx, "回调函数方法,带皮肤...");
    do
	{
		if (!g_bPause)
		{
			printf("%d", i);
			sprintf(szState, "%d", i/1000);
			RtkGuiWDSetPos(ctx, i / 1000);
			if(!(i%100)) {
				RtkGuiWDSetState(ctx, szState);
			}
			i++;
		}
    }while(i<=100000);

    RtkGuiWDDestroy(ctx);

	
	ctx = RtkGuiWDStart(WDS_PAUSE|WDS_PROGRESS|WDS_CANCEL|WDS_STATE|WDS_TIMEREMAIN|WDS_TIMELEFT,testwaitproc); 
	RtkGuiWDSetCaption(ctx, "带cancel按钮回调函数");
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	
	
	WaitForSingleObject(hEvent, INFINITE);
    
	CloseHandle(hEvent);
    
	*/
	//RtkGuiWDEnableSkin(FALSE);
	HANDLE ctx;
	ctx = RtkGuiWDStart(WDS_PROGRESS|WDS_STATE|WDS_CANCEL, NULL);
	RtkGuiWDSetCaption(ctx, "getbtnstate方法,不带skin");
    for (i=0; i<10001; i++) {
       printf("%d", i);
       wsprintf(szState, "%d", i/100);
       if (RtkGuiWDGetBtnState(ctx) & WDC_CANCEL)
		   RtkGuiMsgBox(NULL, "按下cancelfsdfdsffdsfdsnfsdfdsfdsfdsfsd\nf", "哈哈", MB_OKCANCELALWAYS | MB_ICONERROR);
       RtkGuiWDSetPos(ctx, i / 100);
       
       if(!(i%100)){
           RtkGuiWDSetState(ctx, szState);
       }
    }
    RtkGuiWDDestroy(ctx);

	
    _sleep(5000);
	return 0;
}
