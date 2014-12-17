/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 10 10:20:54 2001
 */
/* Compiler settings for D:\development\pi\clients\pisdk1.1\DLL\PISDKCommon\PISDKCommon.idl:
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

#ifndef __PISDKCommon_h__
#define __PISDKCommon_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __INameResolver_FWD_DEFINED__
#define __INameResolver_FWD_DEFINED__
typedef interface INameResolver INameResolver;
#endif 	/* __INameResolver_FWD_DEFINED__ */


#ifndef __IPISDKThreadSafe_FWD_DEFINED__
#define __IPISDKThreadSafe_FWD_DEFINED__
typedef interface IPISDKThreadSafe IPISDKThreadSafe;
#endif 	/* __IPISDKThreadSafe_FWD_DEFINED__ */


#ifndef __IRefresh_FWD_DEFINED__
#define __IRefresh_FWD_DEFINED__
typedef interface IRefresh IRefresh;
#endif 	/* __IRefresh_FWD_DEFINED__ */


#ifndef __ISlimFast_FWD_DEFINED__
#define __ISlimFast_FWD_DEFINED__
typedef interface ISlimFast ISlimFast;
#endif 	/* __ISlimFast_FWD_DEFINED__ */


#ifndef __ITraverse_FWD_DEFINED__
#define __ITraverse_FWD_DEFINED__
typedef interface ITraverse ITraverse;
#endif 	/* __ITraverse_FWD_DEFINED__ */


#ifndef ___EnumNamedValue_FWD_DEFINED__
#define ___EnumNamedValue_FWD_DEFINED__
typedef interface _EnumNamedValue _EnumNamedValue;
#endif 	/* ___EnumNamedValue_FWD_DEFINED__ */


#ifndef ___NamedValues_FWD_DEFINED__
#define ___NamedValues_FWD_DEFINED__
typedef interface _NamedValues _NamedValues;
#endif 	/* ___NamedValues_FWD_DEFINED__ */


#ifndef __INamedValues2_FWD_DEFINED__
#define __INamedValues2_FWD_DEFINED__
typedef interface INamedValues2 INamedValues2;
#endif 	/* __INamedValues2_FWD_DEFINED__ */


#ifndef __NamedValue_FWD_DEFINED__
#define __NamedValue_FWD_DEFINED__
typedef interface NamedValue NamedValue;
#endif 	/* __NamedValue_FWD_DEFINED__ */


#ifndef __INamedValue2_FWD_DEFINED__
#define __INamedValue2_FWD_DEFINED__
typedef interface INamedValue2 INamedValue2;
#endif 	/* __INamedValue2_FWD_DEFINED__ */


#ifndef ___PIErrors_FWD_DEFINED__
#define ___PIErrors_FWD_DEFINED__
typedef interface _PIErrors _PIErrors;
#endif 	/* ___PIErrors_FWD_DEFINED__ */


#ifndef ___PIError_FWD_DEFINED__
#define ___PIError_FWD_DEFINED__
typedef interface _PIError _PIError;
#endif 	/* ___PIError_FWD_DEFINED__ */


#ifndef ___PIAsynchStatus_FWD_DEFINED__
#define ___PIAsynchStatus_FWD_DEFINED__
typedef interface _PIAsynchStatus _PIAsynchStatus;
#endif 	/* ___PIAsynchStatus_FWD_DEFINED__ */


#ifndef __NamedValues_FWD_DEFINED__
#define __NamedValues_FWD_DEFINED__

#ifdef __cplusplus
typedef class NamedValues NamedValues;
#else
typedef struct NamedValues NamedValues;
#endif /* __cplusplus */

#endif 	/* __NamedValues_FWD_DEFINED__ */


#ifndef __NamedValue2_FWD_DEFINED__
#define __NamedValue2_FWD_DEFINED__

#ifdef __cplusplus
typedef class NamedValue2 NamedValue2;
#else
typedef struct NamedValue2 NamedValue2;
#endif /* __cplusplus */

#endif 	/* __NamedValue2_FWD_DEFINED__ */


#ifndef __PIErrors_FWD_DEFINED__
#define __PIErrors_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIErrors PIErrors;
#else
typedef struct PIErrors PIErrors;
#endif /* __cplusplus */

#endif 	/* __PIErrors_FWD_DEFINED__ */


#ifndef __PIError_FWD_DEFINED__
#define __PIError_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIError PIError;
#else
typedef struct PIError PIError;
#endif /* __cplusplus */

#endif 	/* __PIError_FWD_DEFINED__ */


#ifndef ___PIAsynchStatusEvents_FWD_DEFINED__
#define ___PIAsynchStatusEvents_FWD_DEFINED__
typedef interface _PIAsynchStatusEvents _PIAsynchStatusEvents;
#endif 	/* ___PIAsynchStatusEvents_FWD_DEFINED__ */


#ifndef __PIAsynchStatus_FWD_DEFINED__
#define __PIAsynchStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class PIAsynchStatus PIAsynchStatus;
#else
typedef struct PIAsynchStatus PIAsynchStatus;
#endif /* __cplusplus */

#endif 	/* __PIAsynchStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_PISDKCommon_0000 */
/* [local] */ 

#pragma once




extern RPC_IF_HANDLE __MIDL_itf_PISDKCommon_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_PISDKCommon_0000_v0_0_s_ifspec;

#ifndef __INameResolver_INTERFACE_DEFINED__
#define __INameResolver_INTERFACE_DEFINED__

/* interface INameResolver */
/* [unique][helpcontext][helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_INameResolver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("289040A1-599F-11d2-8118-00A0240B7FDC")
    INameResolver : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Resolve( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INameResolverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INameResolver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INameResolver __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INameResolver __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            INameResolver __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } INameResolverVtbl;

    interface INameResolver
    {
        CONST_VTBL struct INameResolverVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INameResolver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INameResolver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INameResolver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INameResolver_Resolve(This,Name,pVal)	\
    (This)->lpVtbl -> Resolve(This,Name,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE INameResolver_Resolve_Proxy( 
    INameResolver __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB INameResolver_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INameResolver_INTERFACE_DEFINED__ */


#ifndef __IPISDKThreadSafe_INTERFACE_DEFINED__
#define __IPISDKThreadSafe_INTERFACE_DEFINED__

/* interface IPISDKThreadSafe */
/* [unique][helpstring][helpcontext][hidden][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IPISDKThreadSafe;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07336561-EF21-11d3-BDC7-00C04F779EB2")
    IPISDKThreadSafe : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IPISDKThreadSafeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPISDKThreadSafe __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPISDKThreadSafe __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPISDKThreadSafe __RPC_FAR * This);
        
        END_INTERFACE
    } IPISDKThreadSafeVtbl;

    interface IPISDKThreadSafe
    {
        CONST_VTBL struct IPISDKThreadSafeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPISDKThreadSafe_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPISDKThreadSafe_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPISDKThreadSafe_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPISDKThreadSafe_INTERFACE_DEFINED__ */


#ifndef __IRefresh_INTERFACE_DEFINED__
#define __IRefresh_INTERFACE_DEFINED__

/* interface IRefresh */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IRefresh;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B8AEB9C1-5227-11d2-BEFA-0060B0290178")
    IRefresh : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRefreshVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRefresh __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRefresh __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRefresh __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IRefresh __RPC_FAR * This);
        
        END_INTERFACE
    } IRefreshVtbl;

    interface IRefresh
    {
        CONST_VTBL struct IRefreshVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRefresh_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRefresh_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRefresh_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRefresh_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IRefresh_Refresh_Proxy( 
    IRefresh __RPC_FAR * This);


void __RPC_STUB IRefresh_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRefresh_INTERFACE_DEFINED__ */


#ifndef __ISlimFast_INTERFACE_DEFINED__
#define __ISlimFast_INTERFACE_DEFINED__

/* interface ISlimFast */
/* [unique][helpstring][helpcontext][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ISlimFast;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE619C61-1793-11d2-80EE-00A0240B7FDC")
    ISlimFast : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SlimFast( 
            /* [defaultvalue][in] */ long Reserved = 0) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISlimFastVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISlimFast __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISlimFast __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISlimFast __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SlimFast )( 
            ISlimFast __RPC_FAR * This,
            /* [defaultvalue][in] */ long Reserved);
        
        END_INTERFACE
    } ISlimFastVtbl;

    interface ISlimFast
    {
        CONST_VTBL struct ISlimFastVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISlimFast_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISlimFast_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISlimFast_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISlimFast_SlimFast(This,Reserved)	\
    (This)->lpVtbl -> SlimFast(This,Reserved)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ISlimFast_SlimFast_Proxy( 
    ISlimFast __RPC_FAR * This,
    /* [defaultvalue][in] */ long Reserved);


void __RPC_STUB ISlimFast_SlimFast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISlimFast_INTERFACE_DEFINED__ */


#ifndef __ITraverse_INTERFACE_DEFINED__
#define __ITraverse_INTERFACE_DEFINED__

/* interface ITraverse */
/* [unique][helpstring][helpcontext][hidden][local][uuid][object] */ 

typedef /* [public][public][helpcontext][helpstring] */ 
enum __MIDL_ITraverse_0001
    {	pitrNoOptions	= 0,
	pitrSorted	= 1,
	pitrUnsorted	= 2
    }	pitrStyleFlags;


EXTERN_C const IID IID_ITraverse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DB1D5986-8A3F-11d2-BD40-00C04F779EB2")
    ITraverse : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Traverse( 
            /* [in] */ void __RPC_FAR *pCallback,
            /* [defaultvalue][in] */ void __RPC_FAR *pPassThru = 0,
            /* [defaultvalue][in] */ pitrStyleFlags Style = pitrNoOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITraverseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITraverse __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITraverse __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITraverse __RPC_FAR * This);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Traverse )( 
            ITraverse __RPC_FAR * This,
            /* [in] */ void __RPC_FAR *pCallback,
            /* [defaultvalue][in] */ void __RPC_FAR *pPassThru,
            /* [defaultvalue][in] */ pitrStyleFlags Style);
        
        END_INTERFACE
    } ITraverseVtbl;

    interface ITraverse
    {
        CONST_VTBL struct ITraverseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITraverse_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITraverse_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITraverse_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITraverse_Traverse(This,pCallback,pPassThru,Style)	\
    (This)->lpVtbl -> Traverse(This,pCallback,pPassThru,Style)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE ITraverse_Traverse_Proxy( 
    ITraverse __RPC_FAR * This,
    /* [in] */ void __RPC_FAR *pCallback,
    /* [defaultvalue][in] */ void __RPC_FAR *pPassThru,
    /* [defaultvalue][in] */ pitrStyleFlags Style);


void __RPC_STUB ITraverse_Traverse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITraverse_INTERFACE_DEFINED__ */


#ifndef ___EnumNamedValue_INTERFACE_DEFINED__
#define ___EnumNamedValue_INTERFACE_DEFINED__

/* interface _EnumNamedValue */
/* [unique][oleautomation][hidden][uuid][object] */ 


EXTERN_C const IID IID__EnumNamedValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8A5AC971-5D60-11d1-808B-00A0240B7FDC")
    _EnumNamedValue : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _EnumNamedValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _EnumNamedValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _EnumNamedValue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _EnumNamedValue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            _EnumNamedValue __RPC_FAR * This,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } _EnumNamedValueVtbl;

    interface _EnumNamedValue
    {
        CONST_VTBL struct _EnumNamedValueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _EnumNamedValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _EnumNamedValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _EnumNamedValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _EnumNamedValue_Next(This,pVal)	\
    (This)->lpVtbl -> Next(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE _EnumNamedValue_Next_Proxy( 
    _EnumNamedValue __RPC_FAR * This,
    /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _EnumNamedValue_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___EnumNamedValue_INTERFACE_DEFINED__ */


#ifndef ___NamedValues_INTERFACE_DEFINED__
#define ___NamedValues_INTERFACE_DEFINED__

/* interface _NamedValues */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 

typedef /* [public][public][public][helpcontext][helpstring] */ 
enum __MIDL__NamedValues_0001
    {	pinvHKEY_CLASSES_ROOT	= 0x80000000,
	pinvHKEY_CURRENT_USER	= 0x80000001,
	pinvHKEY_LOCAL_MACHINE	= 0x80000002,
	pinvHKEY_USERS	= 0x80000003,
	pinvHKEY_PERFORMANCE_DATA	= 0x80000004,
	pinvHKEY_CURRENT_CONFIG	= 0x80000005,
	pinvHKEY_DYN_DATA	= 0x80000006
    }	pinvRegistryKeyConstants;

typedef /* [public][public][public][helpcontext][helpstring] */ 
enum __MIDL__NamedValues_0002
    {	pinvNoOptions	= 0,
	pinvIncludeSubkeys	= 1,
	pinvDoNotCreate	= 2,
	pinvKeyMustNotExist	= 4
    }	pinvRegistryOptions;

typedef /* [public][public][public][helpcontext][helpstring] */ 
enum __MIDL__NamedValues_0003
    {	pinvCaseSensitive	= 1,
	pinvLocaleSensitive	= 2,
	pinvAllowLeadingSpace	= 4,
	pinvAllowTrailingSpace	= 8
    }	pinvStyleConstants;


EXTERN_C const IID IID__NamedValues;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("010F0970-5A49-11D1-8088-00A0240B7FDC")
    _NamedValues : public IDispatch
    {
    public:
        virtual /* [helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT __RPC_FAR *Index,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT __RPC_FAR *Value,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [in] */ NamedValue __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            /* [in] */ _NamedValues __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates = -1) = 0;
        
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__MemberEnum( 
            /* [retval][out] */ _EnumNamedValue __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SetSize( 
            /* [in] */ long NewSize) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE LoadFromString( 
            /* [in] */ BSTR str) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE DumpToString( 
            /* [retval][out] */ BSTR __RPC_FAR *pStr) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOnly( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE Freeze( void) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE LoadFromRegistry( 
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt = pinvNoOptions) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE DumpToRegistry( 
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt = pinvNoOptions) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ pinvStyleConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ pinvStyleConstants newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Sorted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Sorted( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _NamedValuesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _NamedValues __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _NamedValues __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _NamedValues __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Index,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT __RPC_FAR *Value,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ NamedValue __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Merge )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ _NamedValues __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__MemberEnum )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ _EnumNamedValue __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSize )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ long NewSize);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromString )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ BSTR str);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpToString )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pStr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadOnly )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Freeze )( 
            _NamedValues __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromRegistry )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpToRegistry )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt);
        
        /* [helpstring][helpcontext][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ pinvStyleConstants __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ pinvStyleConstants newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Sorted )( 
            _NamedValues __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Sorted )( 
            _NamedValues __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } _NamedValuesVtbl;

    interface _NamedValues
    {
        CONST_VTBL struct _NamedValuesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _NamedValues_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _NamedValues_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _NamedValues_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _NamedValues_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _NamedValues_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _NamedValues_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _NamedValues_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _NamedValues_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _NamedValues_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define _NamedValues_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _NamedValues_Add(This,Name,Value,pval)	\
    (This)->lpVtbl -> Add(This,Name,Value,pval)

#define _NamedValues_Copy(This,source,ReplaceDuplicates,pval)	\
    (This)->lpVtbl -> Copy(This,source,ReplaceDuplicates,pval)

#define _NamedValues_Merge(This,source,ReplaceDuplicates)	\
    (This)->lpVtbl -> Merge(This,source,ReplaceDuplicates)

#define _NamedValues_get__MemberEnum(This,pVal)	\
    (This)->lpVtbl -> get__MemberEnum(This,pVal)

#define _NamedValues_SetSize(This,NewSize)	\
    (This)->lpVtbl -> SetSize(This,NewSize)

#define _NamedValues_LoadFromString(This,str)	\
    (This)->lpVtbl -> LoadFromString(This,str)

#define _NamedValues_DumpToString(This,pStr)	\
    (This)->lpVtbl -> DumpToString(This,pStr)

#define _NamedValues_get_ReadOnly(This,pVal)	\
    (This)->lpVtbl -> get_ReadOnly(This,pVal)

#define _NamedValues_Freeze(This)	\
    (This)->lpVtbl -> Freeze(This)

#define _NamedValues_LoadFromRegistry(This,RootKey,SubKey,Opt)	\
    (This)->lpVtbl -> LoadFromRegistry(This,RootKey,SubKey,Opt)

#define _NamedValues_DumpToRegistry(This,RootKey,SubKey,Opt)	\
    (This)->lpVtbl -> DumpToRegistry(This,RootKey,SubKey,Opt)

#define _NamedValues_get_Style(This,pVal)	\
    (This)->lpVtbl -> get_Style(This,pVal)

#define _NamedValues_put_Style(This,newVal)	\
    (This)->lpVtbl -> put_Style(This,newVal)

#define _NamedValues_get_Sorted(This,pVal)	\
    (This)->lpVtbl -> get_Sorted(This,pVal)

#define _NamedValues_put_Sorted(This,newVal)	\
    (This)->lpVtbl -> put_Sorted(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get__NewEnum_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get_Item_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *Index,
    /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get_Count_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_Add_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT __RPC_FAR *Value,
    /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);


void __RPC_STUB _NamedValues_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_Copy_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ NamedValue __RPC_FAR *source,
    /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates,
    /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);


void __RPC_STUB _NamedValues_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_Merge_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ _NamedValues __RPC_FAR *source,
    /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates);


void __RPC_STUB _NamedValues_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get__MemberEnum_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ _EnumNamedValue __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get__MemberEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_SetSize_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ long NewSize);


void __RPC_STUB _NamedValues_SetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_LoadFromString_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ BSTR str);


void __RPC_STUB _NamedValues_LoadFromString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_DumpToString_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pStr);


void __RPC_STUB _NamedValues_DumpToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get_ReadOnly_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get_ReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_Freeze_Proxy( 
    _NamedValues __RPC_FAR * This);


void __RPC_STUB _NamedValues_Freeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_LoadFromRegistry_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ pinvRegistryKeyConstants RootKey,
    /* [in] */ BSTR SubKey,
    /* [defaultvalue][in] */ pinvRegistryOptions Opt);


void __RPC_STUB _NamedValues_LoadFromRegistry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _NamedValues_DumpToRegistry_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ pinvRegistryKeyConstants RootKey,
    /* [in] */ BSTR SubKey,
    /* [defaultvalue][in] */ pinvRegistryOptions Opt);


void __RPC_STUB _NamedValues_DumpToRegistry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get_Style_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ pinvStyleConstants __RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE _NamedValues_put_Style_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ pinvStyleConstants newVal);


void __RPC_STUB _NamedValues_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _NamedValues_get_Sorted_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB _NamedValues_get_Sorted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE _NamedValues_put_Sorted_Proxy( 
    _NamedValues __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB _NamedValues_put_Sorted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___NamedValues_INTERFACE_DEFINED__ */


#ifndef __INamedValues2_INTERFACE_DEFINED__
#define __INamedValues2_INTERFACE_DEFINED__

/* interface INamedValues2 */
/* [unique][helpcontext][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_INamedValues2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5546F22-EF21-11d3-BDC7-00C04F779EB2")
    INamedValues2 : public _NamedValues
    {
    public:
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ INamedValues2 __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ NamedValue __RPC_FAR *toInsert) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INamedValues2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INamedValues2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INamedValues2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INamedValues2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *Index,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT __RPC_FAR *Value,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ NamedValue __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates,
            /* [retval][out] */ NamedValue __RPC_FAR *__RPC_FAR *pval);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Merge )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ _NamedValues __RPC_FAR *source,
            /* [defaultvalue][in] */ VARIANT_BOOL ReplaceDuplicates);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__MemberEnum )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ _EnumNamedValue __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSize )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ long NewSize);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromString )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ BSTR str);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpToString )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pStr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadOnly )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Freeze )( 
            INamedValues2 __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromRegistry )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DumpToRegistry )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ pinvRegistryKeyConstants RootKey,
            /* [in] */ BSTR SubKey,
            /* [defaultvalue][in] */ pinvRegistryOptions Opt);
        
        /* [helpstring][helpcontext][hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ pinvStyleConstants __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ pinvStyleConstants newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Sorted )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Sorted )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rename )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ BSTR OldName,
            /* [in] */ BSTR NewName);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            INamedValues2 __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            INamedValues2 __RPC_FAR * This,
            /* [retval][out] */ INamedValues2 __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            INamedValues2 __RPC_FAR * This,
            /* [in] */ NamedValue __RPC_FAR *toInsert);
        
        END_INTERFACE
    } INamedValues2Vtbl;

    interface INamedValues2
    {
        CONST_VTBL struct INamedValues2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INamedValues2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INamedValues2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INamedValues2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INamedValues2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INamedValues2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INamedValues2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INamedValues2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INamedValues2_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define INamedValues2_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define INamedValues2_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define INamedValues2_Add(This,Name,Value,pval)	\
    (This)->lpVtbl -> Add(This,Name,Value,pval)

#define INamedValues2_Copy(This,source,ReplaceDuplicates,pval)	\
    (This)->lpVtbl -> Copy(This,source,ReplaceDuplicates,pval)

#define INamedValues2_Merge(This,source,ReplaceDuplicates)	\
    (This)->lpVtbl -> Merge(This,source,ReplaceDuplicates)

#define INamedValues2_get__MemberEnum(This,pVal)	\
    (This)->lpVtbl -> get__MemberEnum(This,pVal)

#define INamedValues2_SetSize(This,NewSize)	\
    (This)->lpVtbl -> SetSize(This,NewSize)

#define INamedValues2_LoadFromString(This,str)	\
    (This)->lpVtbl -> LoadFromString(This,str)

#define INamedValues2_DumpToString(This,pStr)	\
    (This)->lpVtbl -> DumpToString(This,pStr)

#define INamedValues2_get_ReadOnly(This,pVal)	\
    (This)->lpVtbl -> get_ReadOnly(This,pVal)

#define INamedValues2_Freeze(This)	\
    (This)->lpVtbl -> Freeze(This)

#define INamedValues2_LoadFromRegistry(This,RootKey,SubKey,Opt)	\
    (This)->lpVtbl -> LoadFromRegistry(This,RootKey,SubKey,Opt)

#define INamedValues2_DumpToRegistry(This,RootKey,SubKey,Opt)	\
    (This)->lpVtbl -> DumpToRegistry(This,RootKey,SubKey,Opt)

#define INamedValues2_get_Style(This,pVal)	\
    (This)->lpVtbl -> get_Style(This,pVal)

#define INamedValues2_put_Style(This,newVal)	\
    (This)->lpVtbl -> put_Style(This,newVal)

#define INamedValues2_get_Sorted(This,pVal)	\
    (This)->lpVtbl -> get_Sorted(This,pVal)

#define INamedValues2_put_Sorted(This,newVal)	\
    (This)->lpVtbl -> put_Sorted(This,newVal)


#define INamedValues2_Rename(This,OldName,NewName)	\
    (This)->lpVtbl -> Rename(This,OldName,NewName)

#define INamedValues2_Remove(This,Name)	\
    (This)->lpVtbl -> Remove(This,Name)

#define INamedValues2_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define INamedValues2_Clone(This,pVal)	\
    (This)->lpVtbl -> Clone(This,pVal)

#define INamedValues2_Insert(This,toInsert)	\
    (This)->lpVtbl -> Insert(This,toInsert)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValues2_Rename_Proxy( 
    INamedValues2 __RPC_FAR * This,
    /* [in] */ BSTR OldName,
    /* [in] */ BSTR NewName);


void __RPC_STUB INamedValues2_Rename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValues2_Remove_Proxy( 
    INamedValues2 __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB INamedValues2_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValues2_Clear_Proxy( 
    INamedValues2 __RPC_FAR * This);


void __RPC_STUB INamedValues2_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValues2_Clone_Proxy( 
    INamedValues2 __RPC_FAR * This,
    /* [retval][out] */ INamedValues2 __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB INamedValues2_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValues2_Insert_Proxy( 
    INamedValues2 __RPC_FAR * This,
    /* [in] */ NamedValue __RPC_FAR *toInsert);


void __RPC_STUB INamedValues2_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INamedValues2_INTERFACE_DEFINED__ */


#ifndef __NamedValue_INTERFACE_DEFINED__
#define __NamedValue_INTERFACE_DEFINED__

/* interface NamedValue */
/* [unique][helpcontext][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_NamedValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("444DBB11-5A50-11d1-8088-00A0240B7FDC")
    NamedValue : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ _NamedValues __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct NamedValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            NamedValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            NamedValue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            NamedValue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            NamedValue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            NamedValue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            NamedValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            NamedValue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            NamedValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            NamedValue __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            NamedValue __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            NamedValue __RPC_FAR * This,
            /* [retval][out] */ _NamedValues __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } NamedValueVtbl;

    interface NamedValue
    {
        CONST_VTBL struct NamedValueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define NamedValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define NamedValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define NamedValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define NamedValue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define NamedValue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define NamedValue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define NamedValue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define NamedValue_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define NamedValue_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define NamedValue_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define NamedValue_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE NamedValue_get_Name_Proxy( 
    NamedValue __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB NamedValue_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE NamedValue_get_Value_Proxy( 
    NamedValue __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB NamedValue_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE NamedValue_put_Value_Proxy( 
    NamedValue __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB NamedValue_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE NamedValue_get_Parent_Proxy( 
    NamedValue __RPC_FAR * This,
    /* [retval][out] */ _NamedValues __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB NamedValue_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __NamedValue_INTERFACE_DEFINED__ */


#ifndef __INamedValue2_INTERFACE_DEFINED__
#define __INamedValue2_INTERFACE_DEFINED__

/* interface INamedValue2 */
/* [unique][helpcontext][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_INamedValue2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5546F21-EF21-11d3-BDC7-00C04F779EB2")
    INamedValue2 : public NamedValue
    {
    public:
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR NewName) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Detach( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INamedValue2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INamedValue2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INamedValue2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INamedValue2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            INamedValue2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            INamedValue2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            INamedValue2 __RPC_FAR * This,
            /* [retval][out] */ _NamedValues __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rename )( 
            INamedValue2 __RPC_FAR * This,
            /* [in] */ BSTR NewName);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Detach )( 
            INamedValue2 __RPC_FAR * This);
        
        END_INTERFACE
    } INamedValue2Vtbl;

    interface INamedValue2
    {
        CONST_VTBL struct INamedValue2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INamedValue2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INamedValue2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INamedValue2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INamedValue2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INamedValue2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INamedValue2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INamedValue2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INamedValue2_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define INamedValue2_get_Value(This,pVal)	\
    (This)->lpVtbl -> get_Value(This,pVal)

#define INamedValue2_put_Value(This,newVal)	\
    (This)->lpVtbl -> put_Value(This,newVal)

#define INamedValue2_get_Parent(This,pVal)	\
    (This)->lpVtbl -> get_Parent(This,pVal)


#define INamedValue2_Rename(This,NewName)	\
    (This)->lpVtbl -> Rename(This,NewName)

#define INamedValue2_Detach(This)	\
    (This)->lpVtbl -> Detach(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValue2_Rename_Proxy( 
    INamedValue2 __RPC_FAR * This,
    /* [in] */ BSTR NewName);


void __RPC_STUB INamedValue2_Rename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE INamedValue2_Detach_Proxy( 
    INamedValue2 __RPC_FAR * This);


void __RPC_STUB INamedValue2_Detach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INamedValue2_INTERFACE_DEFINED__ */


#ifndef ___PIErrors_INTERFACE_DEFINED__
#define ___PIErrors_INTERFACE_DEFINED__

/* interface _PIErrors */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PIErrors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21CC3DE6-EF1F-11D3-BDC7-00C04F779EB2")
    _PIErrors : public IDispatch
    {
    public:
        virtual /* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ long Number,
            /* [in] */ BSTR Description,
            /* [defaultvalue][in] */ BSTR Source,
            /* [defaultvalue][in] */ BSTR HelpFile,
            /* [defaultvalue][in] */ long HelpContext,
            /* [optional][in] */ VARIANT Cause,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddErrorInfo( 
            /* [in] */ long Number,
            /* [defaultvalue][in] */ IUnknown __RPC_FAR *punkErrInfo,
            /* [optional][in] */ VARIANT Cause,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOnly( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][hidden][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Freeze( void) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SetSize( 
            /* [in] */ long NewSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PIErrorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PIErrors __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PIErrors __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PIErrors __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            _PIErrors __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            _PIErrors __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ long Number,
            /* [in] */ BSTR Description,
            /* [defaultvalue][in] */ BSTR Source,
            /* [defaultvalue][in] */ BSTR HelpFile,
            /* [defaultvalue][in] */ long HelpContext,
            /* [optional][in] */ VARIANT Cause,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddErrorInfo )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ long Number,
            /* [defaultvalue][in] */ IUnknown __RPC_FAR *punkErrInfo,
            /* [optional][in] */ VARIANT Cause,
            /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadOnly )( 
            _PIErrors __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][hidden][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Freeze )( 
            _PIErrors __RPC_FAR * This);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSize )( 
            _PIErrors __RPC_FAR * This,
            /* [in] */ long NewSize);
        
        END_INTERFACE
    } _PIErrorsVtbl;

    interface _PIErrors
    {
        CONST_VTBL struct _PIErrorsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIErrors_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIErrors_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIErrors_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIErrors_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIErrors_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIErrors_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIErrors_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PIErrors_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define _PIErrors_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define _PIErrors_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define _PIErrors_Add(This,Number,Description,Source,HelpFile,HelpContext,Cause,pVal)	\
    (This)->lpVtbl -> Add(This,Number,Description,Source,HelpFile,HelpContext,Cause,pVal)

#define _PIErrors_AddErrorInfo(This,Number,punkErrInfo,Cause,pVal)	\
    (This)->lpVtbl -> AddErrorInfo(This,Number,punkErrInfo,Cause,pVal)

#define _PIErrors_get_ReadOnly(This,pVal)	\
    (This)->lpVtbl -> get_ReadOnly(This,pVal)

#define _PIErrors_Freeze(This)	\
    (This)->lpVtbl -> Freeze(This)

#define _PIErrors_SetSize(This,NewSize)	\
    (This)->lpVtbl -> SetSize(This,NewSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][id][propget] */ HRESULT STDMETHODCALLTYPE _PIErrors_get__NewEnum_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PIErrors_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIErrors_get_Item_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PIErrors_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIErrors_get_Count_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _PIErrors_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PIErrors_Add_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [in] */ long Number,
    /* [in] */ BSTR Description,
    /* [defaultvalue][in] */ BSTR Source,
    /* [defaultvalue][in] */ BSTR HelpFile,
    /* [defaultvalue][in] */ long HelpContext,
    /* [optional][in] */ VARIANT Cause,
    /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PIErrors_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PIErrors_AddErrorInfo_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [in] */ long Number,
    /* [defaultvalue][in] */ IUnknown __RPC_FAR *punkErrInfo,
    /* [optional][in] */ VARIANT Cause,
    /* [retval][out] */ _PIError __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB _PIErrors_AddErrorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIErrors_get_ReadOnly_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB _PIErrors_get_ReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PIErrors_Freeze_Proxy( 
    _PIErrors __RPC_FAR * This);


void __RPC_STUB _PIErrors_Freeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _PIErrors_SetSize_Proxy( 
    _PIErrors __RPC_FAR * This,
    /* [in] */ long NewSize);


void __RPC_STUB _PIErrors_SetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PIErrors_INTERFACE_DEFINED__ */


#ifndef ___PIError_INTERFACE_DEFINED__
#define ___PIError_INTERFACE_DEFINED__

/* interface _PIError */
/* [unique][helpstring][helpcontext][hidden][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID__PIError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("21CC3DE8-EF1F-11D3-BDC7-00C04F779EB2")
    _PIError : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Number( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cause( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpContext( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_HelpFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PIErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PIError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PIError __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PIError __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PIError __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PIError __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PIError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PIError __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Number )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cause )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContext )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Source )( 
            _PIError __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } _PIErrorVtbl;

    interface _PIError
    {
        CONST_VTBL struct _PIErrorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIError_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIError_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIError_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIError_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PIError_get_Number(This,pVal)	\
    (This)->lpVtbl -> get_Number(This,pVal)

#define _PIError_get_Cause(This,pVal)	\
    (This)->lpVtbl -> get_Cause(This,pVal)

#define _PIError_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define _PIError_get_HelpContext(This,pVal)	\
    (This)->lpVtbl -> get_HelpContext(This,pVal)

#define _PIError_get_HelpFile(This,pVal)	\
    (This)->lpVtbl -> get_HelpFile(This,pVal)

#define _PIError_get_Source(This,pVal)	\
    (This)->lpVtbl -> get_Source(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_Number_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_Cause_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_Cause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_Description_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_HelpContext_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_HelpContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_HelpFile_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIError_get_Source_Proxy( 
    _PIError __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB _PIError_get_Source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PIError_INTERFACE_DEFINED__ */


#ifndef ___PIAsynchStatus_INTERFACE_DEFINED__
#define ___PIAsynchStatus_INTERFACE_DEFINED__

/* interface _PIAsynchStatus */
/* [unique][helpstring][helpcontext][nonextensible][dual][uuid][object] */ 

typedef /* [public][public][public][public][helpcontext][helpstring] */ 
enum __MIDL__PIAsynchStatus_0001
    {	csInitial	= 0,
	csInProgress	= 1,
	csComplete	= 2,
	csHasErrors	= 4,
	csCompleteWithErrors	= 6,
	csCancelFlag	= 8,
	csCancelPending	= 9,
	csCancelComplete	= 10,
	csCancelCompleteWithErrors	= 14
    }	CallStatusConstants;


EXTERN_C const IID IID__PIAsynchStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("36FC9461-5334-11d2-BEFA-0060B0290178")
    _PIAsynchStatus : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProgressPercent( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProgressPercent( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ CallStatusConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Status( 
            /* [in] */ CallStatusConstants newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Cancel( void) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SetComplete( void) = 0;
        
        virtual /* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE SetErrors( void) = 0;
        
        virtual /* [helpcontext][helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Result( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE put_Result( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _PIAsynchStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProgressPercent )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpcontext][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProgressPercent )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [retval][out] */ CallStatusConstants __RPC_FAR *pVal);
        
        /* [helpcontext][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Status )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ CallStatusConstants newVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetComplete )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        /* [helpstring][helpcontext][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetErrors )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        /* [helpcontext][helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            _PIAsynchStatus __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Result )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpcontext][hidden][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Result )( 
            _PIAsynchStatus __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } _PIAsynchStatusVtbl;

    interface _PIAsynchStatus
    {
        CONST_VTBL struct _PIAsynchStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIAsynchStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIAsynchStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIAsynchStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIAsynchStatus_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIAsynchStatus_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIAsynchStatus_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIAsynchStatus_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _PIAsynchStatus_get_ProgressPercent(This,pVal)	\
    (This)->lpVtbl -> get_ProgressPercent(This,pVal)

#define _PIAsynchStatus_put_ProgressPercent(This,newVal)	\
    (This)->lpVtbl -> put_ProgressPercent(This,newVal)

#define _PIAsynchStatus_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define _PIAsynchStatus_put_Status(This,newVal)	\
    (This)->lpVtbl -> put_Status(This,newVal)

#define _PIAsynchStatus_Cancel(This)	\
    (This)->lpVtbl -> Cancel(This)

#define _PIAsynchStatus_SetComplete(This)	\
    (This)->lpVtbl -> SetComplete(This)

#define _PIAsynchStatus_SetErrors(This)	\
    (This)->lpVtbl -> SetErrors(This)

#define _PIAsynchStatus_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define _PIAsynchStatus_get_Result(This,pVal)	\
    (This)->lpVtbl -> get_Result(This,pVal)

#define _PIAsynchStatus_put_Result(This,newVal)	\
    (This)->lpVtbl -> put_Result(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_get_ProgressPercent_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB _PIAsynchStatus_get_ProgressPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_put_ProgressPercent_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB _PIAsynchStatus_put_ProgressPercent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_get_Status_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [retval][out] */ CallStatusConstants __RPC_FAR *pVal);


void __RPC_STUB _PIAsynchStatus_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_put_Status_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [in] */ CallStatusConstants newVal);


void __RPC_STUB _PIAsynchStatus_put_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_Cancel_Proxy( 
    _PIAsynchStatus __RPC_FAR * This);


void __RPC_STUB _PIAsynchStatus_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_SetComplete_Proxy( 
    _PIAsynchStatus __RPC_FAR * This);


void __RPC_STUB _PIAsynchStatus_SetComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][hidden][id] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_SetErrors_Proxy( 
    _PIAsynchStatus __RPC_FAR * This);


void __RPC_STUB _PIAsynchStatus_SetErrors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_Reset_Proxy( 
    _PIAsynchStatus __RPC_FAR * This);


void __RPC_STUB _PIAsynchStatus_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_get_Result_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB _PIAsynchStatus_get_Result_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][hidden][id][propput] */ HRESULT STDMETHODCALLTYPE _PIAsynchStatus_put_Result_Proxy( 
    _PIAsynchStatus __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB _PIAsynchStatus_put_Result_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___PIAsynchStatus_INTERFACE_DEFINED__ */



#ifndef __PISDKCommon_LIBRARY_DEFINED__
#define __PISDKCommon_LIBRARY_DEFINED__

/* library PISDKCommon */
/* [helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_PISDKCommon;

EXTERN_C const CLSID CLSID_NamedValues;

#ifdef __cplusplus

class DECLSPEC_UUID("010F0971-5A49-11D1-8088-00A0240B7FDC")
NamedValues;
#endif

EXTERN_C const CLSID CLSID_NamedValue2;

#ifdef __cplusplus

class DECLSPEC_UUID("A6CCC641-5F6C-11d4-BDF9-00C04F779EB2")
NamedValue2;
#endif

EXTERN_C const CLSID CLSID_PIErrors;

#ifdef __cplusplus

class DECLSPEC_UUID("21CC3DE7-EF1F-11D3-BDC7-00C04F779EB2")
PIErrors;
#endif

EXTERN_C const CLSID CLSID_PIError;

#ifdef __cplusplus

class DECLSPEC_UUID("21CC3DE9-EF1F-11D3-BDC7-00C04F779EB2")
PIError;
#endif

#ifndef ___PIAsynchStatusEvents_DISPINTERFACE_DEFINED__
#define ___PIAsynchStatusEvents_DISPINTERFACE_DEFINED__

/* dispinterface _PIAsynchStatusEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__PIAsynchStatusEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("36FC9462-5334-11d2-BEFA-0060B0290178")
    _PIAsynchStatusEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _PIAsynchStatusEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _PIAsynchStatusEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _PIAsynchStatusEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _PIAsynchStatusEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _PIAsynchStatusEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _PIAsynchStatusEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _PIAsynchStatusEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _PIAsynchStatusEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _PIAsynchStatusEventsVtbl;

    interface _PIAsynchStatusEvents
    {
        CONST_VTBL struct _PIAsynchStatusEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _PIAsynchStatusEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _PIAsynchStatusEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _PIAsynchStatusEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _PIAsynchStatusEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _PIAsynchStatusEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _PIAsynchStatusEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _PIAsynchStatusEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___PIAsynchStatusEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PIAsynchStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("36FC9463-5334-11d2-BEFA-0060B0290178")
PIAsynchStatus;
#endif
#endif /* __PISDKCommon_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
