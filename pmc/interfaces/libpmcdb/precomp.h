#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma warning(disable:4786)
#endif

#include <atlbase.h>

// #define RTK_USE_HASHMAP
// #define RTK_USE_SGI_STL

namespace std{
}

using namespace std;

#ifdef _WIN32
#include <process.h>
#endif
#include <string>
#include <ctype.h>

#include <pmc.h>
#include <hisproxy.h>

#include <object.h>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include "comutil.h"

