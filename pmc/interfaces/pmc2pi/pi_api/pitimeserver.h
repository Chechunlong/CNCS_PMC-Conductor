/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 10 10:21:27 2001
 */
/* Compiler settings for D:\development\pi\clients\pisdk1.1\DLL\PITimeServer\PITimeServer.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __PITimeServer_h__
#define __PITimeServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef ___DeviceTimeZones_FWD_DEFINED__
#define ___DeviceTimeZones_FWD_DEFINED__
typedef interface _DeviceTimeZones _DeviceTimeZones;
#endif 	/* ___DeviceTimeZones_FWD_DEFINED__ */


#ifndef __IClockSource_FWD_DEFINED__
#define __IClockSource_FWD_DEFINED__
typedef interface IClockSource IClockSource;
#endif 	/* __IClockSource_FWD_DEFINED__ */


#ifndef ___PITime_FWD_DEFINED__
#define ___PITime_FWD_DEFINED__
typedef interface _PITime _PITime;
#endif 	/* ___PITime_FWD_DEFINED__ */


#ifndef ___PITimeFormat_FWD_DEFINED__
#define ___PITimeFormat_FWD_DEFINED__
typedef interface _PITimeFormat _PITimeFormat;
#endif 	/* ___PITimeFormat_FWD_DEFINED__ */


#ifndef ___DynamicTime_FWD_DEFINED__
#define ___DynamicTime_FWD_DEFINED__
typedef interface _DynamicTime _DynamicTime;
#endif 	/* ___DynamicTime_FWD_DEFINED__ */


#ifndef __PITimeZoneInfo_FWD_DEFINED__
#define __PITimeZoneInfo_FWD_DEFINED__
typedef interface PITimeZoneInfo PITimeZoneInfo;
#endif 	/* __PITimeZoneInfo_FWD_DEFINED__ */


#ifndef ___PITimeZoneInfos_FWD_DEFINED__
#define ___PITimeZoneInfos_FWD_DEFINED__
typedef interface _PITimeZoneInfos _PITimeZoneInfos;
#endif 	/* ___PITimeZoneInfos_FWD_DEFINED__ */


#ifndef __ITimeInterval_FWD_DEFINED__
#define __ITimeInterval_FWD_DEFINED__
typedef interface ITimeInterval ITimeInterval;
#endif 	/* __ITimeInterval_FWD_DEFINED__ */


#ifndef ___TimeIntervals_FWD_DEFINED__
#define ___TimeIntervals_FWD_DEFINED__
typedef interface _TimeIntervals _TimeIntervals;
#endif 	/* ___TimeIntervals_FWD_DEFINED__ */


#ifndef __PITime_FWD_DEFINED__
#define __PITime_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITime PITime;
#else
typedef struct PITime PITime;
#endif /* __cplusplus */

#endif 	/* __PITime_FWD_DEFINED__ */


#ifndef __PITimeFormat_FWD_DEFINED__
#define __PITimeFormat_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeFormat PITimeFormat;
#else
typedef struct PITimeFormat PITimeFormat;
#endif /* __cplusplus */

#endif 	/* __PITimeFormat_FWD_DEFINED__ */


#ifndef __PITimeZoneInfos_FWD_DEFINED__
#define __PITimeZoneInfos_FWD_DEFINED__

#ifdef __cplusplus
typedef class PITimeZoneInfos PITimeZoneInfos;
#else
typedef struct PITimeZoneInfos PITimeZoneInfos;
#endif /* __cplusplus */

#endif 	/* __PITimeZoneInfos_FWD_DEFINED__ */


#ifndef __DeviceTimeZones_FWD_DEFINED__
#define __DeviceTimeZones_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeviceTimeZones DeviceTimeZones;
#else
typedef struct DeviceTimeZones DeviceTimeZones;
#endif /* __cplusplus */

#endif 	/* __DeviceTimeZones_FWD_DEFINED__ */


#ifndef __DynamicTime_FWD_DEFINED__
#define __DynamicTime_FWD_DEFINED__

#ifdef __cplusplus
typedef class DynamicTime DynamicTime;
#else
typedef struct DynamicTime DynamicTime;
#endif /* __cplusplus */

#endif 	/* __DynamicTime_FWD_DEFINED__ */


#ifndef __TimeIntervals_FWD_DEFINED__
#define __TimeIntervals_FWD_DEFINED__

#ifdef __cplusplus
typedef class TimeIntervals TimeIntervals;
#else
typedef struct TimeIntervals TimeIntervals;
#endif /* __cplusplus */

#endif 	/* __TimeIntervals_FWD_DEFINED__ */


#ifndef __ITimeIntervals_FWD_DEFINED__
#define __ITimeIntervals_FWD_DEFINED__
typedef interface ITimeIntervals ITimeIntervals;
#endif 	/* __ITimeIntervals_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_PITimeServer_0000 */
/* [local] */ 

#pragma once
typedef /* [helpstring] */ 
enum TSErrorConstants
    {	tseTIMEINVALID	= 0x8004a100,
	tseTIMEGETCOMP	= 0x8004a101,
	tseTIMEFILETIME	= 0x8004a102,
	tseTIMESTAMPTODATE	= 0x8004a103,
	tseSYSTIMETODATE	= 0x8004a104,
	tseVARIANTNOTDATE	= 0x8004a105,
	tseDATETOSYSTIME	= 0x8004a106,
	tseDATETOTIMESTAMP	= 0x8004a107,
	tseDATEOUTOFRANGE	= 0x8004a108,
	tseMEMBERNOTFOUND	= 0x8004a109,
	tseORDNOTFOUND	= 0x8004a10a
    }	TSErrorConstants;










extern RPC_IF_HANDLE __MIDL_itf_PITimeServer_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PITimeServer_0000_v0_0_s_ifspec;

#ifndef ___DeviceTimeZones_INTERFACE_DEFINED__
#define ___DeviceTimeZones_INTERFACE_DEFINED__

/* interface _DeviceTimeZones */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__DeviceTimeZones;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4507ED2-D021-11d3-853D-00C04F45D1DA")
    _DeviceTimeZones : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR DeviceName,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR DeviceName,
            /* [in] */ BSTR ZoneID) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR DeviceName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DeviceTimeZonesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DeviceTimeZones __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DeviceTimeZones __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ BSTR DeviceName,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ BSTR DeviceName,
            /* [in] */ BSTR ZoneID);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            _DeviceTimeZones __RPC_FAR * This,
            /* [in] */ BSTR DeviceName);
        
        END_INTERFACE
    } _DeviceTimeZonesVtbl;

    interface _DeviceTimeZones
    {
        CONST_VTBL struct _DeviceTimeZonesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DeviceTimeZones_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DeviceTimeZones_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DeviceTimeZones_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DeviceTimeZones_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DeviceTimeZones_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DeviceTimeZones_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DeviceTimeZones_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DeviceTimeZones_get_Item(This,DeviceName,pVal)	\
    (This)->lpVtbl -> get_Item(This,DeviceName,pVal)

#define _DeviceTimeZones_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _DeviceTimeZones_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _DeviceTimeZones_Add(This,DeviceName,ZoneID)	\
    (This)->lpVtbl -> Add(This,DeviceName,ZoneID)

#define _DeviceTimeZones_Remove(This,DeviceName)	\
    (This)->lpVtbl -> Remove(This,DeviceName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get_Item_Proxy( 
    _DeviceTimeZones __RPC_FAR * This,
    /* [in] */ BSTR DeviceName,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _DeviceTimeZones_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get__NewEnum_Proxy( 
    _DeviceTimeZones __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _DeviceTimeZones_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_get_Count_Proxy( 
    _DeviceTimeZones __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _DeviceTimeZones_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_Add_Proxy( 
    _DeviceTimeZones __RPC_FAR * This,
    /* [in] */ BSTR DeviceName,
    /* [in] */ BSTR ZoneID);


void __RPC_STUB _DeviceTimeZones_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _DeviceTimeZones_Remove_Proxy( 
    _DeviceTimeZones __RPC_FAR * This,
    /* [in] */ BSTR DeviceName);


void __RPC_STUB _DeviceTimeZones_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DeviceTimeZones_INTERFACE_DEFINED__ */


#ifndef __IClockSource_INTERFACE_DEFINED__
#define __IClockSource_INTERFACE_DEFINED__

/* interface IClockSource */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IClockSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C7F3F8C1-CA24-11d3-BDC2-00C04F779EB2")
    IClockSource : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCSeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeZoneInfo( 
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClockSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClockSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClockSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClockSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IClockSource __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IClockSource __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IClockSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IClockSource __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCSeconds )( 
            IClockSource __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeZoneInfo )( 
            IClockSource __RPC_FAR * This,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IClockSource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IClockSource __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IClockSourceVtbl;

    interface IClockSource
    {
        CONST_VTBL struct IClockSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClockSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClockSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClockSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClockSource_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClockSource_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClockSource_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClockSource_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IClockSource_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define IClockSource_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define IClockSource_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IClockSource_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_UTCSeconds_Proxy( 
    IClockSource __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IClockSource_get_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_TimeZoneInfo_Proxy( 
    IClockSource __RPC_FAR * This,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IClockSource_get_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_Name_Proxy( 
    IClockSource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IClockSource_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IClockSource_get_Description_Proxy( 
    IClockSource __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IClockSource_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClockSource_INTERFACE_DEFINED__ */


#ifndef ___PITime_INTERFACE_DEFINED__
#define ___PITime_INTERFACE_DEFINED__

/* interface _PITime */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("626F6911-CA37-11d3-BDC2-00C04F779EB2")
    _PITime : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCSeconds( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_UTCSeconds( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalDate( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocalDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetToCurrent( void) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTCFileTime( 
            /* [retval][out] */ CURRENCY __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_UTCFileTime( 
            /* [in] */ CURRENCY newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PITime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PITime __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PITime __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PITime __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PITime __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PITime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PITime __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCSeconds )( 
            _PITime __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCSeconds )( 
            _PITime __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalDate )( 
            _PITime __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalDate )( 
            _PITime __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetToCurrent )( 
            _PITime __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCFileTime )( 
            _PITime __RPC_FAR * This,
            /* [retval][out] */ CURRENCY __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCFileTime )( 
            _PITime __RPC_FAR * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            _PITime __RPC_FAR * This,
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } _PITimeVtbl;

    interface _PITime
    {
        CONST_VTBL struct _PITimeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITime_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITime_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITime_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITime_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITime_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITime_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITime_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITime_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _PITime_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _PITime_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _PITime_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _PITime_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _PITime_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _PITime_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _PITime_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_UTCSeconds_Proxy( 
    _PITime __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB _PITime_get_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_UTCSeconds_Proxy( 
    _PITime __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB _PITime_put_UTCSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_LocalDate_Proxy( 
    _PITime __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB _PITime_get_LocalDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_LocalDate_Proxy( 
    _PITime __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB _PITime_put_LocalDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITime_SetToCurrent_Proxy( 
    _PITime __RPC_FAR * This);


void __RPC_STUB _PITime_SetToCurrent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITime_get_UTCFileTime_Proxy( 
    _PITime __RPC_FAR * This,
    /* [retval][out] */ CURRENCY __RPC_FAR *pVal);


void __RPC_STUB _PITime_get_UTCFileTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITime_put_UTCFileTime_Proxy( 
    _PITime __RPC_FAR * This,
    /* [in] */ CURRENCY newVal);


void __RPC_STUB _PITime_put_UTCFileTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITime_Clone_Proxy( 
    _PITime __RPC_FAR * This,
    /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITime_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITime_INTERFACE_DEFINED__ */


#ifndef ___PITimeFormat_INTERFACE_DEFINED__
#define ___PITimeFormat_INTERFACE_DEFINED__

/* interface _PITimeFormat */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeFormat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB149699-C3CA-11D3-BDBF-00C04F779EB2")
    _PITimeFormat : public _PITime
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeZoneInfo( 
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_TimeZoneInfo( 
            /* [in] */ PITimeZoneInfo __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_FormatString( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE StartOfInterval( 
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IntervalNumber( 
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddIntervals( 
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IntervalDifference( 
            /* [in] */ BSTR IntervalName,
            /* [in] */ _PITime __RPC_FAR *Time2,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocaleIndependent( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_LocaleIndependent( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeFormatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PITimeFormat __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PITimeFormat __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PITimeFormat __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCSeconds )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCSeconds )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalDate )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalDate )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetToCurrent )( 
            _PITimeFormat __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCFileTime )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ CURRENCY __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCFileTime )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeZoneInfo )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_TimeZoneInfo )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ PITimeZoneInfo __RPC_FAR *newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputString )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputString )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FormatString )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FormatString )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputString )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartOfInterval )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntervalNumber )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddIntervals )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntervalDifference )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ _PITime __RPC_FAR *Time2,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocaleIndependent )( 
            _PITimeFormat __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocaleIndependent )( 
            _PITimeFormat __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } _PITimeFormatVtbl;

    interface _PITimeFormat
    {
        CONST_VTBL struct _PITimeFormatVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeFormat_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeFormat_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeFormat_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeFormat_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeFormat_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeFormat_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeFormat_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITimeFormat_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _PITimeFormat_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _PITimeFormat_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _PITimeFormat_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _PITimeFormat_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _PITimeFormat_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _PITimeFormat_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _PITimeFormat_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)


#define _PITimeFormat_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define _PITimeFormat_putref_TimeZoneInfo(This,newVal)	\
    (This)->lpVtbl -> putref_TimeZoneInfo(This,newVal)

#define _PITimeFormat_get_InputString(This,pVal)	\
    (This)->lpVtbl -> get_InputString(This,pVal)

#define _PITimeFormat_put_InputString(This,newVal)	\
    (This)->lpVtbl -> put_InputString(This,newVal)

#define _PITimeFormat_get_FormatString(This,pVal)	\
    (This)->lpVtbl -> get_FormatString(This,pVal)

#define _PITimeFormat_put_FormatString(This,newVal)	\
    (This)->lpVtbl -> put_FormatString(This,newVal)

#define _PITimeFormat_get_OutputString(This,pVal)	\
    (This)->lpVtbl -> get_OutputString(This,pVal)

#define _PITimeFormat_StartOfInterval(This,IntervalName,pVal)	\
    (This)->lpVtbl -> StartOfInterval(This,IntervalName,pVal)

#define _PITimeFormat_IntervalNumber(This,IntervalName,pVal)	\
    (This)->lpVtbl -> IntervalNumber(This,IntervalName,pVal)

#define _PITimeFormat_AddIntervals(This,IntervalName,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,IntervalName,nIntervals,pVal)

#define _PITimeFormat_IntervalDifference(This,IntervalName,Time2,pVal)	\
    (This)->lpVtbl -> IntervalDifference(This,IntervalName,Time2,pVal)

#define _PITimeFormat_get_LocaleIndependent(This,pVal)	\
    (This)->lpVtbl -> get_LocaleIndependent(This,pVal)

#define _PITimeFormat_put_LocaleIndependent(This,newVal)	\
    (This)->lpVtbl -> put_LocaleIndependent(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_TimeZoneInfo_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_get_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propputref] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_putref_TimeZoneInfo_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ PITimeZoneInfo __RPC_FAR *newVal);


void __RPC_STUB _PITimeFormat_putref_TimeZoneInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_InputString_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_get_InputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_InputString_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB _PITimeFormat_put_InputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_FormatString_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_get_FormatString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_FormatString_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB _PITimeFormat_put_FormatString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_OutputString_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_get_OutputString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_StartOfInterval_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR IntervalName,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_StartOfInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_IntervalNumber_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR IntervalName,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_IntervalNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_AddIntervals_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR IntervalName,
    /* [in] */ double nIntervals,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_AddIntervals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_IntervalDifference_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ BSTR IntervalName,
    /* [in] */ _PITime __RPC_FAR *Time2,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_IntervalDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_get_LocaleIndependent_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB _PITimeFormat_get_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _PITimeFormat_put_LocaleIndependent_Proxy( 
    _PITimeFormat __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB _PITimeFormat_put_LocaleIndependent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITimeFormat_INTERFACE_DEFINED__ */


#ifndef ___DynamicTime_INTERFACE_DEFINED__
#define ___DynamicTime_INTERFACE_DEFINED__

/* interface _DynamicTime */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__DynamicTime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B7BD37E3-C94E-11D3-BDC2-00C04F779EB2")
    _DynamicTime : public _PITimeFormat
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReferenceTime( 
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReferenceTime( 
            /* [in] */ _PITime __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SetClockSource( 
            /* [in] */ IClockSource __RPC_FAR *pSource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _DynamicTimeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _DynamicTime __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _DynamicTime __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _DynamicTime __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCSeconds )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCSeconds )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalDate )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocalDate )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetToCurrent )( 
            _DynamicTime __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTCFileTime )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ CURRENCY __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTCFileTime )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ CURRENCY newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeZoneInfo )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propputref] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_TimeZoneInfo )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ PITimeZoneInfo __RPC_FAR *newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InputString )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_InputString )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FormatString )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FormatString )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutputString )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartOfInterval )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntervalNumber )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddIntervals )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IntervalDifference )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ BSTR IntervalName,
            /* [in] */ _PITime __RPC_FAR *Time2,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocaleIndependent )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LocaleIndependent )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReferenceTime )( 
            _DynamicTime __RPC_FAR * This,
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReferenceTime )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *newVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetClockSource )( 
            _DynamicTime __RPC_FAR * This,
            /* [in] */ IClockSource __RPC_FAR *pSource);
        
        END_INTERFACE
    } _DynamicTimeVtbl;

    interface _DynamicTime
    {
        CONST_VTBL struct _DynamicTimeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DynamicTime_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DynamicTime_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DynamicTime_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DynamicTime_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DynamicTime_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DynamicTime_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DynamicTime_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _DynamicTime_get_UTCSeconds(This,pVal)	\
    (This)->lpVtbl -> get_UTCSeconds(This,pVal)

#define _DynamicTime_put_UTCSeconds(This,newVal)	\
    (This)->lpVtbl -> put_UTCSeconds(This,newVal)

#define _DynamicTime_get_LocalDate(This,pVal)	\
    (This)->lpVtbl -> get_LocalDate(This,pVal)

#define _DynamicTime_put_LocalDate(This,newVal)	\
    (This)->lpVtbl -> put_LocalDate(This,newVal)

#define _DynamicTime_SetToCurrent(This)	\
    (This)->lpVtbl -> SetToCurrent(This)

#define _DynamicTime_get_UTCFileTime(This,pVal)	\
    (This)->lpVtbl -> get_UTCFileTime(This,pVal)

#define _DynamicTime_put_UTCFileTime(This,newVal)	\
    (This)->lpVtbl -> put_UTCFileTime(This,newVal)

#define _DynamicTime_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)


#define _DynamicTime_get_TimeZoneInfo(This,pVal)	\
    (This)->lpVtbl -> get_TimeZoneInfo(This,pVal)

#define _DynamicTime_putref_TimeZoneInfo(This,newVal)	\
    (This)->lpVtbl -> putref_TimeZoneInfo(This,newVal)

#define _DynamicTime_get_InputString(This,pVal)	\
    (This)->lpVtbl -> get_InputString(This,pVal)

#define _DynamicTime_put_InputString(This,newVal)	\
    (This)->lpVtbl -> put_InputString(This,newVal)

#define _DynamicTime_get_FormatString(This,pVal)	\
    (This)->lpVtbl -> get_FormatString(This,pVal)

#define _DynamicTime_put_FormatString(This,newVal)	\
    (This)->lpVtbl -> put_FormatString(This,newVal)

#define _DynamicTime_get_OutputString(This,pVal)	\
    (This)->lpVtbl -> get_OutputString(This,pVal)

#define _DynamicTime_StartOfInterval(This,IntervalName,pVal)	\
    (This)->lpVtbl -> StartOfInterval(This,IntervalName,pVal)

#define _DynamicTime_IntervalNumber(This,IntervalName,pVal)	\
    (This)->lpVtbl -> IntervalNumber(This,IntervalName,pVal)

#define _DynamicTime_AddIntervals(This,IntervalName,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,IntervalName,nIntervals,pVal)

#define _DynamicTime_IntervalDifference(This,IntervalName,Time2,pVal)	\
    (This)->lpVtbl -> IntervalDifference(This,IntervalName,Time2,pVal)

#define _DynamicTime_get_LocaleIndependent(This,pVal)	\
    (This)->lpVtbl -> get_LocaleIndependent(This,pVal)

#define _DynamicTime_put_LocaleIndependent(This,newVal)	\
    (This)->lpVtbl -> put_LocaleIndependent(This,newVal)


#define _DynamicTime_get_ReferenceTime(This,pVal)	\
    (This)->lpVtbl -> get_ReferenceTime(This,pVal)

#define _DynamicTime_put_ReferenceTime(This,newVal)	\
    (This)->lpVtbl -> put_ReferenceTime(This,newVal)

#define _DynamicTime_SetClockSource(This,pSource)	\
    (This)->lpVtbl -> SetClockSource(This,pSource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _DynamicTime_get_ReferenceTime_Proxy( 
    _DynamicTime __RPC_FAR * This,
    /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _DynamicTime_get_ReferenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _DynamicTime_put_ReferenceTime_Proxy( 
    _DynamicTime __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *newVal);


void __RPC_STUB _DynamicTime_put_ReferenceTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _DynamicTime_SetClockSource_Proxy( 
    _DynamicTime __RPC_FAR * This,
    /* [in] */ IClockSource __RPC_FAR *pSource);


void __RPC_STUB _DynamicTime_SetClockSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___DynamicTime_INTERFACE_DEFINED__ */


#ifndef __PITimeZoneInfo_INTERFACE_DEFINED__
#define __PITimeZoneInfo_INTERFACE_DEFINED__

/* interface PITimeZoneInfo */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_PITimeZoneInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB14969B-C3CA-11D3-BDBF-00C04F779EB2")
    PITimeZoneInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoneID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoneRulesName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StandardName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StandardShortName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaylightName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaylightShortName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bias( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DaylightBias( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_JanuaryIsStandard( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Creator( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreationDate( 
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DSTYears( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DSTStartYear( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DSTData( 
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct PITimeZoneInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            PITimeZoneInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            PITimeZoneInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZoneID )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZoneRulesName )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StandardName )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StandardShortName )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DaylightName )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DaylightShortName )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bias )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DaylightBias )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_JanuaryIsStandard )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationDate )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DSTYears )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DSTStartYear )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DSTData )( 
            PITimeZoneInfo __RPC_FAR * This,
            /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pVal);
        
        END_INTERFACE
    } PITimeZoneInfoVtbl;

    interface PITimeZoneInfo
    {
        CONST_VTBL struct PITimeZoneInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define PITimeZoneInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define PITimeZoneInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define PITimeZoneInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define PITimeZoneInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define PITimeZoneInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define PITimeZoneInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define PITimeZoneInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define PITimeZoneInfo_get_ZoneID(This,pVal)	\
    (This)->lpVtbl -> get_ZoneID(This,pVal)

#define PITimeZoneInfo_get_ZoneRulesName(This,pVal)	\
    (This)->lpVtbl -> get_ZoneRulesName(This,pVal)

#define PITimeZoneInfo_get_StandardName(This,pVal)	\
    (This)->lpVtbl -> get_StandardName(This,pVal)

#define PITimeZoneInfo_get_StandardShortName(This,pVal)	\
    (This)->lpVtbl -> get_StandardShortName(This,pVal)

#define PITimeZoneInfo_get_DaylightName(This,pVal)	\
    (This)->lpVtbl -> get_DaylightName(This,pVal)

#define PITimeZoneInfo_get_DaylightShortName(This,pVal)	\
    (This)->lpVtbl -> get_DaylightShortName(This,pVal)

#define PITimeZoneInfo_get_Bias(This,pVal)	\
    (This)->lpVtbl -> get_Bias(This,pVal)

#define PITimeZoneInfo_get_DaylightBias(This,pVal)	\
    (This)->lpVtbl -> get_DaylightBias(This,pVal)

#define PITimeZoneInfo_get_JanuaryIsStandard(This,pVal)	\
    (This)->lpVtbl -> get_JanuaryIsStandard(This,pVal)

#define PITimeZoneInfo_get_Creator(This,pVal)	\
    (This)->lpVtbl -> get_Creator(This,pVal)

#define PITimeZoneInfo_get_CreationDate(This,pVal)	\
    (This)->lpVtbl -> get_CreationDate(This,pVal)

#define PITimeZoneInfo_get_DSTYears(This,pVal)	\
    (This)->lpVtbl -> get_DSTYears(This,pVal)

#define PITimeZoneInfo_get_DSTStartYear(This,pVal)	\
    (This)->lpVtbl -> get_DSTStartYear(This,pVal)

#define PITimeZoneInfo_get_DSTData(This,pVal)	\
    (This)->lpVtbl -> get_DSTData(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_ZoneID_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_ZoneID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_ZoneRulesName_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_ZoneRulesName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_StandardName_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_StandardName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_StandardShortName_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_StandardShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DaylightName_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DaylightName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DaylightShortName_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DaylightShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_Bias_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_Bias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DaylightBias_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DaylightBias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_JanuaryIsStandard_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_JanuaryIsStandard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_Creator_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_Creator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_CreationDate_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ _PITime __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_CreationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DSTYears_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DSTYears_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DSTStartYear_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DSTStartYear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE PITimeZoneInfo_get_DSTData_Proxy( 
    PITimeZoneInfo __RPC_FAR * This,
    /* [retval][out] */ SAFEARRAY __RPC_FAR * __RPC_FAR *pVal);


void __RPC_STUB PITimeZoneInfo_get_DSTData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __PITimeZoneInfo_INTERFACE_DEFINED__ */


#ifndef ___PITimeZoneInfos_INTERFACE_DEFINED__
#define ___PITimeZoneInfos_INTERFACE_DEFINED__

/* interface _PITimeZoneInfos */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PITimeZoneInfos;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A14DB12-CFA3-11d3-853D-00C04F45D1DA")
    _PITimeZoneInfos : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR ZoneName,
            /* [in] */ BSTR StandardName,
            /* [in] */ BSTR StandardShortName,
            /* [in] */ BSTR DaylightName,
            /* [in] */ BSTR DaylightShortName,
            /* [in] */ long Bias,
            /* [in] */ long DaylightBias,
            /* [in] */ VARIANT_BOOL JanuaryIsStandard,
            /* [in] */ long DSTYears,
            /* [in] */ int DSTStartYear,
            /* [in] */ SAFEARRAY __RPC_FAR * DSTData,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR ZoneID) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile( 
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE DumpToFile( 
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR FileName) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemByName( 
            /* [in] */ BSTR ZoneRulesName,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PITimeZoneInfosVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PITimeZoneInfos __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PITimeZoneInfos __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR ZoneID,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR ZoneName,
            /* [in] */ BSTR StandardName,
            /* [in] */ BSTR StandardShortName,
            /* [in] */ BSTR DaylightName,
            /* [in] */ BSTR DaylightShortName,
            /* [in] */ long Bias,
            /* [in] */ long DaylightBias,
            /* [in] */ VARIANT_BOOL JanuaryIsStandard,
            /* [in] */ long DSTYears,
            /* [in] */ int DSTStartYear,
            /* [in] */ SAFEARRAY __RPC_FAR * DSTData,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR ZoneID);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromFile )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR FileName);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpToFile )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR ZoneID,
            /* [in] */ BSTR FileName);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ItemByName )( 
            _PITimeZoneInfos __RPC_FAR * This,
            /* [in] */ BSTR ZoneRulesName,
            /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } _PITimeZoneInfosVtbl;

    interface _PITimeZoneInfos
    {
        CONST_VTBL struct _PITimeZoneInfosVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PITimeZoneInfos_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PITimeZoneInfos_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PITimeZoneInfos_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PITimeZoneInfos_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PITimeZoneInfos_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PITimeZoneInfos_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PITimeZoneInfos_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PITimeZoneInfos_get_Item(This,ZoneID,pVal)	\
    (This)->lpVtbl -> get_Item(This,ZoneID,pVal)

#define _PITimeZoneInfos_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _PITimeZoneInfos_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _PITimeZoneInfos_Add(This,ZoneID,ZoneName,StandardName,StandardShortName,DaylightName,DaylightShortName,Bias,DaylightBias,JanuaryIsStandard,DSTYears,DSTStartYear,DSTData,pVal)	\
    (This)->lpVtbl -> Add(This,ZoneID,ZoneName,StandardName,StandardShortName,DaylightName,DaylightShortName,Bias,DaylightBias,JanuaryIsStandard,DSTYears,DSTStartYear,DSTData,pVal)

#define _PITimeZoneInfos_Remove(This,ZoneID)	\
    (This)->lpVtbl -> Remove(This,ZoneID)

#define _PITimeZoneInfos_LoadFromFile(This,FileName)	\
    (This)->lpVtbl -> LoadFromFile(This,FileName)

#define _PITimeZoneInfos_DumpToFile(This,ZoneID,FileName)	\
    (This)->lpVtbl -> DumpToFile(This,ZoneID,FileName)

#define _PITimeZoneInfos_ItemByName(This,ZoneRulesName,pVal)	\
    (This)->lpVtbl -> ItemByName(This,ZoneRulesName,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get_Item_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR ZoneID,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITimeZoneInfos_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get__NewEnum_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITimeZoneInfos_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_get_Count_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _PITimeZoneInfos_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_Add_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR ZoneID,
    /* [in] */ BSTR ZoneName,
    /* [in] */ BSTR StandardName,
    /* [in] */ BSTR StandardShortName,
    /* [in] */ BSTR DaylightName,
    /* [in] */ BSTR DaylightShortName,
    /* [in] */ long Bias,
    /* [in] */ long DaylightBias,
    /* [in] */ VARIANT_BOOL JanuaryIsStandard,
    /* [in] */ long DSTYears,
    /* [in] */ int DSTStartYear,
    /* [in] */ SAFEARRAY __RPC_FAR * DSTData,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITimeZoneInfos_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_Remove_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR ZoneID);


void __RPC_STUB _PITimeZoneInfos_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_LoadFromFile_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR FileName);


void __RPC_STUB _PITimeZoneInfos_LoadFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_DumpToFile_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR ZoneID,
    /* [in] */ BSTR FileName);


void __RPC_STUB _PITimeZoneInfos_DumpToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PITimeZoneInfos_ItemByName_Proxy( 
    _PITimeZoneInfos __RPC_FAR * This,
    /* [in] */ BSTR ZoneRulesName,
    /* [retval][out] */ PITimeZoneInfo __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PITimeZoneInfos_ItemByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PITimeZoneInfos_INTERFACE_DEFINED__ */


#ifndef __ITimeInterval_INTERFACE_DEFINED__
#define __ITimeInterval_INTERFACE_DEFINED__

/* interface ITimeInterval */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 

typedef /* [helpstring][uuid][public] */ 
enum FindIntervalConstants
    {	fiBefore	= 0,
	fiOnOrBefore	= fiBefore + 1,
	fiCurrent	= fiOnOrBefore + 1,
	fiOnOrAfter	= fiCurrent + 1,
	fiAfter	= fiOnOrAfter + 1
    }	FindIntervalConstants;


EXTERN_C const IID IID_ITimeInterval;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E2496D2-C3CB-11d3-BDBF-00C04F779EB2")
    ITimeInterval : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShortName( 
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberName( 
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberShortName( 
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberLo( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_MemberHi( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ordinal( 
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddIntervals( 
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Difference( 
            /* [in] */ _PITime __RPC_FAR *pTime0,
            /* [in] */ _PITime __RPC_FAR *pTime1,
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE FindMember( 
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [in] */ VARIANT Index,
            /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeIntervalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimeInterval __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimeInterval __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITimeInterval __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITimeInterval __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShortName )( 
            ITimeInterval __RPC_FAR * This,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemberName )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemberShortName )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ long Index,
            /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemberLo )( 
            ITimeInterval __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MemberHi )( 
            ITimeInterval __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ordinal )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddIntervals )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [in] */ double nIntervals,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Difference )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *pTime0,
            /* [in] */ _PITime __RPC_FAR *pTime1,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindMember )( 
            ITimeInterval __RPC_FAR * This,
            /* [in] */ _PITime __RPC_FAR *pTime,
            /* [in] */ VARIANT Index,
            /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITimeIntervalVtbl;

    interface ITimeInterval
    {
        CONST_VTBL struct ITimeIntervalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeInterval_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeInterval_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeInterval_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeInterval_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeInterval_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeInterval_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeInterval_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeInterval_get_Name(This,localeindependent,pVal)	\
    (This)->lpVtbl -> get_Name(This,localeindependent,pVal)

#define ITimeInterval_get_ShortName(This,localeindependent,pVal)	\
    (This)->lpVtbl -> get_ShortName(This,localeindependent,pVal)

#define ITimeInterval_get_MemberName(This,Index,localeindependent,pVal)	\
    (This)->lpVtbl -> get_MemberName(This,Index,localeindependent,pVal)

#define ITimeInterval_get_MemberShortName(This,Index,localeindependent,pVal)	\
    (This)->lpVtbl -> get_MemberShortName(This,Index,localeindependent,pVal)

#define ITimeInterval_get_MemberLo(This,pVal)	\
    (This)->lpVtbl -> get_MemberLo(This,pVal)

#define ITimeInterval_get_MemberHi(This,pVal)	\
    (This)->lpVtbl -> get_MemberHi(This,pVal)

#define ITimeInterval_get_StartTime(This,pTime,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_StartTime(This,pTime,LocaleIndependent,pVal)

#define ITimeInterval_get_Ordinal(This,pTime,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_Ordinal(This,pTime,LocaleIndependent,pVal)

#define ITimeInterval_AddIntervals(This,pTime,nIntervals,pVal)	\
    (This)->lpVtbl -> AddIntervals(This,pTime,nIntervals,pVal)

#define ITimeInterval_Difference(This,pTime0,pTime1,pVal)	\
    (This)->lpVtbl -> Difference(This,pTime0,pTime1,pVal)

#define ITimeInterval_FindMember(This,pTime,Index,WhatToFind,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> FindMember(This,pTime,Index,WhatToFind,LocaleIndependent,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_Name_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_ShortName_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_ShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberName_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ long Index,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_MemberName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberShortName_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ long Index,
    /* [defaultvalue][in] */ VARIANT_BOOL localeindependent,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_MemberShortName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberLo_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_MemberLo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_MemberHi_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_MemberHi_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_StartTime_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *pTime,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE ITimeInterval_get_Ordinal_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *pTime,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_get_Ordinal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeInterval_AddIntervals_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *pTime,
    /* [in] */ double nIntervals,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_AddIntervals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeInterval_Difference_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *pTime0,
    /* [in] */ _PITime __RPC_FAR *pTime1,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_Difference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITimeInterval_FindMember_Proxy( 
    ITimeInterval __RPC_FAR * This,
    /* [in] */ _PITime __RPC_FAR *pTime,
    /* [in] */ VARIANT Index,
    /* [defaultvalue][in] */ FindIntervalConstants WhatToFind,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB ITimeInterval_FindMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeInterval_INTERFACE_DEFINED__ */


#ifndef ___TimeIntervals_INTERFACE_DEFINED__
#define ___TimeIntervals_INTERFACE_DEFINED__

/* interface _TimeIntervals */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__TimeIntervals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4B7F591-B417-11d4-BE0E-00C04F779EB2")
    _TimeIntervals : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index1,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _TimeIntervalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _TimeIntervals __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _TimeIntervals __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _TimeIntervals __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _TimeIntervals __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _TimeIntervals __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _TimeIntervals __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _TimeIntervals __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            _TimeIntervals __RPC_FAR * This,
            /* [in] */ VARIANT Index1,
            /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
            /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            _TimeIntervals __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            _TimeIntervals __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } _TimeIntervalsVtbl;

    interface _TimeIntervals
    {
        CONST_VTBL struct _TimeIntervalsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _TimeIntervals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _TimeIntervals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _TimeIntervals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _TimeIntervals_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _TimeIntervals_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _TimeIntervals_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _TimeIntervals_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _TimeIntervals_get_Item(This,Index1,LocaleIndependent,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index1,LocaleIndependent,pVal)

#define _TimeIntervals_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _TimeIntervals_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get_Item_Proxy( 
    _TimeIntervals __RPC_FAR * This,
    /* [in] */ VARIANT Index1,
    /* [defaultvalue][in] */ VARIANT_BOOL LocaleIndependent,
    /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _TimeIntervals_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get__NewEnum_Proxy( 
    _TimeIntervals __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _TimeIntervals_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _TimeIntervals_get_Count_Proxy( 
    _TimeIntervals __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _TimeIntervals_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___TimeIntervals_INTERFACE_DEFINED__ */



#ifndef __PITimeServer_LIBRARY_DEFINED__
#define __PITimeServer_LIBRARY_DEFINED__

/* library PITimeServer */
/* [version][helpstring][helpfile][uuid] */ 


EXTERN_C const IID LIBID_PITimeServer;

EXTERN_C const CLSID CLSID_PITime;

#ifdef __cplusplus

class DECLSPEC_UUID("80AB1DC1-CA37-11d3-BDC2-00C04F779EB2")
PITime;
#endif

EXTERN_C const CLSID CLSID_PITimeFormat;

#ifdef __cplusplus

class DECLSPEC_UUID("CB14969A-C3CA-11D3-BDBF-00C04F779EB2")
PITimeFormat;
#endif

EXTERN_C const CLSID CLSID_PITimeZoneInfos;

#ifdef __cplusplus

class DECLSPEC_UUID("0A14DB11-CFA3-11d3-853D-00C04F45D1DA")
PITimeZoneInfos;
#endif

EXTERN_C const CLSID CLSID_DeviceTimeZones;

#ifdef __cplusplus

class DECLSPEC_UUID("A4507ED1-D021-11d3-853D-00C04F45D1DA")
DeviceTimeZones;
#endif

EXTERN_C const CLSID CLSID_DynamicTime;

#ifdef __cplusplus

class DECLSPEC_UUID("B7BD37E4-C94E-11D3-BDC2-00C04F779EB2")
DynamicTime;
#endif

EXTERN_C const CLSID CLSID_TimeIntervals;

#ifdef __cplusplus

class DECLSPEC_UUID("500776E1-CF9C-11d3-853D-00C04F45D1DA")
TimeIntervals;
#endif

#ifndef __ITimeIntervals_INTERFACE_DEFINED__
#define __ITimeIntervals_INTERFACE_DEFINED__

/* interface ITimeIntervals */
/* [unique][helpstring][helpcontext][uuid][object] */ 


EXTERN_C const IID IID_ITimeIntervals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E2496D3-C3CB-11d3-BDBF-00C04F779EB2")
    ITimeIntervals : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index1,
            /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimeIntervalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimeIntervals __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimeIntervals __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimeIntervals __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITimeIntervals __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITimeIntervals __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITimeIntervals __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITimeIntervals __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITimeIntervals __RPC_FAR * This,
            /* [in] */ long Index1,
            /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITimeIntervals __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITimeIntervalsVtbl;

    interface ITimeIntervals
    {
        CONST_VTBL struct ITimeIntervalsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimeIntervals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimeIntervals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimeIntervals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimeIntervals_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITimeIntervals_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITimeIntervals_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITimeIntervals_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITimeIntervals_get_Item(This,Index1,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index1,pVal)

#define ITimeIntervals_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Item_Proxy( 
    ITimeIntervals __RPC_FAR * This,
    /* [in] */ long Index1,
    /* [retval][out] */ ITimeInterval __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITimeIntervals_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][propget] */ HRESULT STDMETHODCALLTYPE ITimeIntervals_get_Count_Proxy( 
    ITimeIntervals __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITimeIntervals_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimeIntervals_INTERFACE_DEFINED__ */

#endif /* __PITimeServer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
