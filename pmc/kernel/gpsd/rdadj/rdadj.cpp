// rdadj.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <fstream.h>


int main(int argc, char* argv[])
{
    DWORD dwTmInc,dwTmAdj;
    BOOL bDisable;

	if(GetSystemTimeAdjustment(&dwTmAdj,&dwTmInc,&bDisable)){
		cout<<"initial time interval is "<<dwTmInc<<"\n";
		cout<<"initial time adjustment is "<<dwTmAdj<<"\n";
        if(bDisable)
            cout<<"adjustment is disable\n";
        else
            cout<<"adjustment is enable\n";
	}else{
		cout<<"can't get system time adjustment! err code:"<<GetLastError()<<"\n";
	}

	return 0;
}
