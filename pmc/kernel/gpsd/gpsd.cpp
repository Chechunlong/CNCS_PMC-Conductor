#include "windows.h"
#include "stdio.h"
#include "gpsservice.h"

int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
    HANDLE hProcess;
    hProcess=GetCurrentProcess();
    if(!SetPriorityClass(hProcess,REALTIME_PRIORITY_CLASS)){
        return 1;
    }

    // create the service-object
	CGpsService serv;
	
	// RegisterService() checks the parameterlist for predefined switches
	// (such as -d or -i etc.; see NTService.h for possible switches) and
	// starts the services functionality.
	// You can use the return value from "RegisterService()"
	// as your exit-code.
	return serv.RegisterService(argc, argv);
}
