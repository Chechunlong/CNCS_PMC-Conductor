/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 14 21:13:35 2006
 */
/* Compiler settings for pmcdb_idl.idl:
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

#ifndef __pmcdb_idl_h__
#define __pmcdb_idl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPmcDB_FWD_DEFINED__
#define __IPmcDB_FWD_DEFINED__
typedef interface IPmcDB IPmcDB;
#endif 	/* __IPmcDB_FWD_DEFINED__ */


#ifndef __IPmcDBEvents_FWD_DEFINED__
#define __IPmcDBEvents_FWD_DEFINED__
typedef interface IPmcDBEvents IPmcDBEvents;
#endif 	/* __IPmcDBEvents_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __pmcdb_LIBRARY_DEFINED__
#define __pmcdb_LIBRARY_DEFINED__

/* library pmcdb */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_pmcdb;

#ifndef __IPmcDB_INTERFACE_DEFINED__
#define __IPmcDB_INTERFACE_DEFINED__

/* interface IPmcDB */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPmcDB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F35F7568-07D5-4137-A9C9-E8737A394536")
    IPmcDB : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE lock( 
            BOOL exclusive,
            LONG timeOut) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE unlock( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE readSnapshot( 
            /* [in] */ BSTR tagName,
            /* [retval][out] */ VARIANT __RPC_FAR *tagValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE writeDevice( 
            /* [in] */ BSTR tagName,
            /* [in] */ VARIANT tagValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE readArchiveValue( 
            /* [in] */ BSTR tagName,
            /* [in] */ VARIANT time,
            /* [retval][out] */ VARIANT __RPC_FAR *tagValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE readSnapshots( 
            /* [in] */ LONG count,
            /* [in] */ VARIANT tagNames,
            /* [out][in] */ VARIANT __RPC_FAR *tagValues) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE writeSnapshots( 
            /* [in] */ LONG count,
            /* [in] */ VARIANT tagNames,
            /* [in] */ VARIANT tagValues) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE readArchiveValues( 
            /* [in] */ VARIANT tagNames,
            /* [in] */ VARIANT startTime,
            /* [in] */ LONG interval,
            /* [in] */ LONG count,
            /* [out][in] */ VARIANT __RPC_FAR *tagValues) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE sleep( 
            /* [in] */ LONG miliSeconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPmcDBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPmcDB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPmcDB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPmcDB __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *lock )( 
            IPmcDB __RPC_FAR * This,
            BOOL exclusive,
            LONG timeOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *unlock )( 
            IPmcDB __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *readSnapshot )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ BSTR tagName,
            /* [retval][out] */ VARIANT __RPC_FAR *tagValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *writeDevice )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ BSTR tagName,
            /* [in] */ VARIANT tagValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *readArchiveValue )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ BSTR tagName,
            /* [in] */ VARIANT time,
            /* [retval][out] */ VARIANT __RPC_FAR *tagValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *readSnapshots )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ LONG count,
            /* [in] */ VARIANT tagNames,
            /* [out][in] */ VARIANT __RPC_FAR *tagValues);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *writeSnapshots )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ LONG count,
            /* [in] */ VARIANT tagNames,
            /* [in] */ VARIANT tagValues);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *readArchiveValues )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ VARIANT tagNames,
            /* [in] */ VARIANT startTime,
            /* [in] */ LONG interval,
            /* [in] */ LONG count,
            /* [out][in] */ VARIANT __RPC_FAR *tagValues);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *sleep )( 
            IPmcDB __RPC_FAR * This,
            /* [in] */ LONG miliSeconds);
        
        END_INTERFACE
    } IPmcDBVtbl;

    interface IPmcDB
    {
        CONST_VTBL struct IPmcDBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPmcDB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPmcDB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPmcDB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPmcDB_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPmcDB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPmcDB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPmcDB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPmcDB_lock(This,exclusive,timeOut)	\
    (This)->lpVtbl -> lock(This,exclusive,timeOut)

#define IPmcDB_unlock(This)	\
    (This)->lpVtbl -> unlock(This)

#define IPmcDB_readSnapshot(This,tagName,tagValue)	\
    (This)->lpVtbl -> readSnapshot(This,tagName,tagValue)

#define IPmcDB_writeDevice(This,tagName,tagValue)	\
    (This)->lpVtbl -> writeDevice(This,tagName,tagValue)

#define IPmcDB_readArchiveValue(This,tagName,time,tagValue)	\
    (This)->lpVtbl -> readArchiveValue(This,tagName,time,tagValue)

#define IPmcDB_readSnapshots(This,count,tagNames,tagValues)	\
    (This)->lpVtbl -> readSnapshots(This,count,tagNames,tagValues)

#define IPmcDB_writeSnapshots(This,count,tagNames,tagValues)	\
    (This)->lpVtbl -> writeSnapshots(This,count,tagNames,tagValues)

#define IPmcDB_readArchiveValues(This,tagNames,startTime,interval,count,tagValues)	\
    (This)->lpVtbl -> readArchiveValues(This,tagNames,startTime,interval,count,tagValues)

#define IPmcDB_sleep(This,miliSeconds)	\
    (This)->lpVtbl -> sleep(This,miliSeconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_lock_Proxy( 
    IPmcDB __RPC_FAR * This,
    BOOL exclusive,
    LONG timeOut);


void __RPC_STUB IPmcDB_lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_unlock_Proxy( 
    IPmcDB __RPC_FAR * This);


void __RPC_STUB IPmcDB_unlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_readSnapshot_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ BSTR tagName,
    /* [retval][out] */ VARIANT __RPC_FAR *tagValue);


void __RPC_STUB IPmcDB_readSnapshot_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_writeDevice_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ BSTR tagName,
    /* [in] */ VARIANT tagValue);


void __RPC_STUB IPmcDB_writeDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_readArchiveValue_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ BSTR tagName,
    /* [in] */ VARIANT time,
    /* [retval][out] */ VARIANT __RPC_FAR *tagValue);


void __RPC_STUB IPmcDB_readArchiveValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_readSnapshots_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ LONG count,
    /* [in] */ VARIANT tagNames,
    /* [out][in] */ VARIANT __RPC_FAR *tagValues);


void __RPC_STUB IPmcDB_readSnapshots_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_writeSnapshots_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ LONG count,
    /* [in] */ VARIANT tagNames,
    /* [in] */ VARIANT tagValues);


void __RPC_STUB IPmcDB_writeSnapshots_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_readArchiveValues_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ VARIANT tagNames,
    /* [in] */ VARIANT startTime,
    /* [in] */ LONG interval,
    /* [in] */ LONG count,
    /* [out][in] */ VARIANT __RPC_FAR *tagValues);


void __RPC_STUB IPmcDB_readArchiveValues_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPmcDB_sleep_Proxy( 
    IPmcDB __RPC_FAR * This,
    /* [in] */ LONG miliSeconds);


void __RPC_STUB IPmcDB_sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPmcDB_INTERFACE_DEFINED__ */


#ifndef __IPmcDBEvents_DISPINTERFACE_DEFINED__
#define __IPmcDBEvents_DISPINTERFACE_DEFINED__

/* dispinterface IPmcDBEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IPmcDBEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5F679D6F-6147-4865-8495-F28A605310FA")
    IPmcDBEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IPmcDBEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPmcDBEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPmcDBEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPmcDBEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPmcDBEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPmcDBEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPmcDBEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPmcDBEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IPmcDBEventsVtbl;

    interface IPmcDBEvents
    {
        CONST_VTBL struct IPmcDBEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPmcDBEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPmcDBEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPmcDBEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPmcDBEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPmcDBEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPmcDBEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPmcDBEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IPmcDBEvents_DISPINTERFACE_DEFINED__ */

#endif /* __pmcdb_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
