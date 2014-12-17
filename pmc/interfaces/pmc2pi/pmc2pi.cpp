#include "precomp.h"
#pragma hdrstop

#include "buffer.h"

#pragma comment (lib, "librtk.lib")
#pragma comment (lib, "libntservice.lib")
#pragma comment (lib, "librtkproxy.lib")
#pragma comment (lib, "libutils.lib")
#pragma comment (lib, "librtdb.lib")


class CRefresher : public CPeriodicThread
{
public:
	CRefresher();
	virtual void task();
};

CRefresher::CRefresher()
{
	m_dwPeriod = 3000;
}

void CRefresher::task()
{
	updateBuffer();
}

class CPmc2PiSrv : public CNTService  
{
public:
	CPmc2PiSrv()
		:CNTService(TEXT("PIIntfTest"), TEXT(""))
	{
	};

	virtual void Run(DWORD, LPTSTR*);
	virtual void Stop();

private:
	DWORD dwMainThreadId;
};

void CPmc2PiSrv::Stop()
{
	ReportStatus(SERVICE_STOP_PENDING, 3000);
	printf("stop - pmc2pi interface\n");

	::PostThreadMessage(dwMainThreadId,WM_QUIT,0,0);	
}

void CPmc2PiSrv::Run(DWORD argc, LPTSTR * argv)
{
	ReportStatus(SERVICE_RUNNING);
	printf("run - pmc2pi interface\n");

	dwMainThreadId=::GetCurrentThreadId();

	if(!initBuffer()){
		return;
	}

	CRefresher refresh;
	refresh.start();

	MSG msg;
	while(GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	refresh.stop();

	clearBuffer();
}

int main(int argc, char* argv[])
{
	CPmc2PiSrv serv;
	
	return serv.RegisterService(argc, argv);
}
