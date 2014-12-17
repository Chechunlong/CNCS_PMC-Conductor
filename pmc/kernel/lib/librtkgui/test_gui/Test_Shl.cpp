// Test_Ssi.cpp : Defines the entry point for the application.
//



#include "stdafx.h"
#include "../../public/include/ssishl.h"
#include "stdio.h"
#include "resource.h"

BOOL (WINAPI * lpfnLoadSkin)(void);

inline char* _extract_file_name(char * path)
{
	char * p;
	
	p=path+strlen(path)-1;
	while(p != path){
		if(*p == '\\' || *p=='/')	break;
		p--;
	}
	return p+1;
}

inline char* _extract_file_path(char * path)
{
	char * p;
	p=_extract_file_name(path);
	*(p-1)=0;
	return path;
}

BOOL FixModulePath(HMODULE hModule, LPSTR lpFilePath)
{
	char szFilePath[MAX_PATH];

	
	if (!GetModuleFileName(hModule, szFilePath, MAX_PATH))
	{
		return FALSE;
	}

	_extract_file_path(szFilePath);

	strcpy(lpFilePath, szFilePath);
	
	return TRUE;
}

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	HMODULE hSkinLib;

	hSkinLib = LoadLibrary("dfvsskin.dll");
	
	
	(FARPROC&)lpfnLoadSkin = GetProcAddress(hSkinLib, "1");
	
	//if (lpfnLoadSkin)
	//	lpfnLoadSkin();
	
	
	
	
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST_SSI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_TEST_SSI);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{	
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	
	
	if (hSkinLib)
		FreeLibrary(hSkinLib);
	

	
	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TEST_SSI);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_TEST_SSI;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
                   
                   SSISHLABOUTBOXSTRUCT s;
				   SSISHLFILEVERSION f;
                   
				   SSiShlGetFileVersion(&f, "d:\\dfvs2.0\\bin\\runlocal\\dfvskve.dll");

                   ZeroMemory(&s, sizeof(s));
                   s.dwSize       = sizeof(s);
                   s.dwMask       =   SSAB_PRODUCT 
									| SSAB_CAPTION 
									| SSAB_PRODUCTLOGO 
									| SSAB_OTHERINFO 
									| SSAB_HOMEPAGE
									| SSAB_COPYRIGHT
									| SSAB_VERSION
									| SSAB_LOGO;
                   s.dwStyle          = SSABS_OWNERCENTER;
                   s.lpszProduct      = "交大铭泰软件有限公司 东方卫士";
                   s.lpszCaption      = "关于东方卫士 ";
                   s.lpszProductLogo  = "D:\\dfvs2.0\\bin\\runlocal\\RES\\about\\main.ico";
				   
				   char mj[255];
                   s.lpszOtherInfo	  = itoa(f.dwMajorVersion, mj, 10);
				   s.lpszHomePage     = "http://antivirus.sunv.com";
				   s.lpszCopyright    = "版权所有：交大铭泰";
				   s.lpszLogo         = "d:\\dfvs2.0\\bin\\runlocal\\res\\about\\logo.bmp";
				   s.lpszVersion      = "版本 2003";
				   
				   SsiShlAboutBox(hWnd, &s);
				   /*
				   char szTemp[MAX_PATH], szFile[MAX_PATH];
				   // 测试以ini文件配置显示关于对话框
				   FixModulePath(hInst, szTemp);
				   sprintf(szFile, "%s%s", szTemp, "\\config\\about.ini");
				   SsiShlAboutBoxEx(hWnd, szFile);*/
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
                case IDM_WAIT:
				
                   wmId = SsiShlMsgBox(hWnd, "ddfsfsdffdss", "dad", MB_YESNOALWAYS|MB_DEFBUTTON2);
				   SsiShlMsgBox(hWnd, "中文中文中中文中文中中文中文中中文中文中", "dad", MB_YESNOALWAYS|MB_ICONINFORMATION);
				   SsiShlMsgBox(hWnd, "中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中文中中文中文中中文中文中中文中文中中文中文中", "dad", MB_OKCANCELALWAYS|MB_ICONINFORMATION);
                   MessageBox(hWnd, "ddfsfs\ndff\ndss", "dad", MB_OKCANCEL);
				   MessageBox(hWnd, "ddfsfsfdsfdsfdsfsdfsdfsdfsfsdfsa", "dad", MB_OKCANCEL|MB_ICONINFORMATION);
                   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
