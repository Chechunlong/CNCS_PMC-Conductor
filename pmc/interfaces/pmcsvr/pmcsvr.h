/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 27 10:50:47 2010
 */
/* Compiler settings for C:\proj\pmc\interfaces\pmcsvr\pmcsvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __pmcsvr_h__
#define __pmcsvr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __OpcServer_FWD_DEFINED__
#define __OpcServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class OpcServer OpcServer;
#else
typedef struct OpcServer OpcServer;
#endif /* __cplusplus */

#endif 	/* __OpcServer_FWD_DEFINED__ */


#ifndef __PmcDB_FWD_DEFINED__
#define __PmcDB_FWD_DEFINED__

#ifdef __cplusplus
typedef class PmcDB PmcDB;
#else
typedef struct PmcDB PmcDB;
#endif /* __cplusplus */

#endif 	/* __PmcDB_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "opcda.h"
#include "pmcdb_idl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __PMCSVRLIB_LIBRARY_DEFINED__
#define __PMCSVRLIB_LIBRARY_DEFINED__

/* library PMCSVRLIB */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PMCSVRLIB;

EXTERN_C const CLSID CLSID_OpcServer;

#ifdef __cplusplus

class DECLSPEC_UUID("268F712B-CFC3-4D8A-96B4-706937B61668")
OpcServer;
#endif

EXTERN_C const CLSID CLSID_PmcDB;

#ifdef __cplusplus

class DECLSPEC_UUID("BA7CE1FB-E5DE-4ffc-8044-BF3053955FCF")
PmcDB;
#endif
#endif /* __PMCSVRLIB_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
