// SetAdj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fstream.h"
#include "windows.h"

//调整对时权利
bool EnableAdjustTimePrivilege(bool bEnable)
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


int main(int argc, char* argv[])
{
    DWORD dwTmAdj;
    
    cout<<"please input time adjustment (unit is 100ns):\n";
    cin>>dwTmAdj;

    cout<<"ok! use time adjustment "<<dwTmAdj<<"\n";

	if(EnableAdjustTimePrivilege(true)){
		if(!SetSystemTimeAdjustment(dwTmAdj,false)){
			cout<<"set time adjustment fail! err code "<<GetLastError()<<"\n";
			return false;
		}else{
			cout<<"set time adjustment succeed!\n";
		}
		EnableAdjustTimePrivilege(false);
	}else{
		return false;
	}
        
    return 0;
}
