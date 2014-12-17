/* rtl81x9End.c - RealTek RTL81x9 Fast Ethernet interface header */

/* Copyright 1984-2000 Wind River Systems, Inc. */
/*
modification history
--------------------
01c,28jan00,dgy  Updated comments that refered to the wrong files.
01b,28jan00,dgy  Changed ryl81x9CsrReadByte to use the correct SYS_IN
macro.
01a,29oct99,dgy  created
*/

/* 
Theory of Operation

I. Board Compatibility

This device driver is designed for the RealTek RTL81x9, the RealTek Fast
Ethernet controllers for PCI.  This chip is used on a few clone boards.


II. Board-specific settings

PCI bus devices are configured by the system at boot time, so no jumpers
need to be set on the board.  The system BIOS will assign the
PCI INTA signal to a (preferably otherwise unused) system IRQ line.

III. Driver operation

IIIa. Rx Ring buffers

The receive unit uses a single linear ring buffer rather than the more
common (and more efficient) descriptor-based architecture.	Incoming frames
are sequentially stored into the Rx region, and the host copies them into
mBlks.

IIIb. Tx operation

The RTL81x9 uses a fixed set of four Tx descriptors in register space.

EXTERNAL INTERFACE
The only external interface is the rtl81x9EndLoad() routine, which expects
the <initString> parameter as input.  This parameter passes in a 
colon-delimited string of the format:

<unit>:<devMemAddr>:<devIoAddr>:<pciMemBase:<vecNum>:<intLvl>:<memAdrs>:
<memSize>:<memWidth>:<flags>:<buffMultiplier>

TARGET-SPECIFIC PARAMETERS
.IP <unit>
A convenient holdover from the former model.  This parameter is used only
in the string name for the driver.

.IP <devMemAddr>
This parameter in the memory base address of the device registers in the
memory map of the CPU. It indicates to the driver where to find the
register set. < This parameter should be equal to NONE if the device
does not support memory mapped registers.


.IP <devIoAddr>
This parameter in the IO base address of the device registers in the
IO map of some CPUs. It indicates to the driver where to find the RDP
register. If both <devIoAddr> and <devMemAddr> are given then the device
chooses <devMemAddr> which is a memory mapped register base address.
This parameter should be equal to NONE if the device does not support 
IO mapped registers.


. <pciMemBase>
This parameter is the base address of the CPU memory as seen from the
PCI bus. This parameter is zero for most intel architectures.

.IP <vecNum>
This parameter is the vector associated with the device interrupt.
This driver configures the LANCE device to generate hardware interrupts
for various events within the device; thus it contains
an interrupt handler routine.  The driver calls intConnect() to connect 
its interrupt handler to the interrupt vector generated as a result of 
the LANCE interrupt.

.IP <intLvl>
Some targets use additional interrupt controller devices to help organize
and service the various interrupt sources.	This driver avoids all
board-specific knowledge of such devices.  During the driver's
initialization, the external routine sysRtl81x9IntEnable() is called to
perform any board-specific operations required to allow the servicing of a
NIC interrupt.	For a description of sysRtl81x9IntEnable(), see "External
Support Requirements" below.

.IP <memAdrs>
This parameter gives the driver the memory address to carve out its
buffers and data structures. If this parameter is specified to be
NONE then the driver allocates cache coherent memory for buffers
and descriptors from the system pool.
The 3C90x NIC is a DMA type of device and typically shares access to
some region of memory with the CPU.  This driver is designed for systems
that directly share memory between the CPU and the NIC.  It
assumes that this shared memory is directly available to it
without any arbitration or timing concerns.

.IP <memSize>
This parameter can be used to explicitly limit the amount of shared
memory (bytes) this driver will use.  The constant NONE can be used to
indicate no specific size limitation.  This parameter is used only if
a specific memory region is provided to the driver.

.IP <memWidth>
Some target hardware that restricts the shared memory region to a
specific location also restricts the access width to this region by
the CPU.  On these targets, performing an access of an invalid width
will cause a bus error.

This parameter can be used to specify the number of bytes of access
width to be used by the driver during access to the shared memory.
The constant NONE can be used to indicate no restrictions.

Current internal support for this mechanism is not robust; implementation 
may not work on all targets requiring these restrictions.

.IP <flags>
This is parameter is used for future use, currently its value should be
zero.


EXTERNAL SUPPORT REQUIREMENTS
This driver requires several external support functions, defined as macros:
.CS
SYS_INT_CONNECT(pDrvCtrl, routine, arg)
SYS_INT_DISCONNECT (pDrvCtrl, routine, arg)
SYS_INT_ENABLE(pDrvCtrl)
SYS_INT_DISABLE(pDrvCtrl)
SYS_OUT_BYTE(pDrvCtrl, reg, data)
SYS_IN_BYTE(pDrvCtrl, reg, data)
SYS_OUT_WORD(pDrvCtrl, reg, data)
SYS_IN_WORD(pDrvCtrl, reg, data)
SYS_OUT_LONG(pDrvCtrl, reg, data)
SYS_IN_LONG(pDrvCtrl, reg, data)
SYS_DELAY (delay)
sysEl3c90xIntEnable(pDrvCtrl->intLevel) 
sysEl3c90xIntDisable(pDrvCtrl->intLevel)
sysDelay (delay)
.CE

There are default values in the source code for these macros.  They presume
memory mapped accesses to the device registers and the normal intConnect(),
and intEnable() BSP functions.	The first argument to each is the device
controller structure. Thus, each has access back to all the device-specific
information.  Having the pointer in the macro facilitates the addition 
of new features to this driver.

The macros SYS_INT_CONNECT, SYS_INT_DISCONNECT, SYS_INT_ENABLE and
SYS_INT_DISABLE allow the driver to be customized for BSPs that use special
versions of these routines.

The macro SYS_INT_CONNECT is used to connect the interrupt handler to
the appropriate vector.  By default it is the routine intConnect().

The macro SYS_INT_DISCONNECT is used to disconnect the interrupt handler prior
to unloading the module.  By default this is a dummy routine that
returns OK.

The macro SYS_INT_ENABLE is used to enable the interrupt level for the
end device.  It is called once during initialization.  It calls an
external board level routine sysRtl81x9IntEnable(). 

The macro SYS_INT_DISABLE is used to disable the interrupt level for the
end device.  It is called during stop.	It calls an
external board level routine sysRtl81x9IntDisable().

The macro SYS_DELAY is used for a delay loop. It calls an external board
level routine sysDelay(delay). The granularity of delay is one microsecond.

SYSTEM RESOURCE USAGE
When implemented, this driver requires the following system resources:

- one mutual exclusion semaphore
- one interrupt vector
- 24072 bytes in text for a I80486 target
- 112 bytes in the initialized data section (data)
- 0 bytes in the uninitialized data section (BSS)

The driver allocates clusters of size 1536 bytes for receive frames and
and transmit frames. There are 16 descriptors in the upload ring
and 16 descriptors in the download ring. The buffer multiplier by default
is 2, which means that the total number of clusters allocated by default
are 64 ((upload descriptors + download descriptors)*2). There are as many
clBlks as the number of clusters. The number of mBlks allocated are twice
the number of clBlks. By default there are 64 clusters, 64 clBlks and 128
mBlks allocated in the pool for the device. Depending on the load of the
system increase the number of clusters allocated by incrementing the buffer
multiplier.


INCLUDES:
end.h endLib.h etherMultiLib.h rtl81x9End.h

SEE ALSO: muxLib, endLib, netBufLib
.pG "Writing and Enhanced Network Driver"
																					
*/

#define END_MACROS

#include "vxWorks.h"
#include "config.h"

#ifdef INCLUDE_RTL_81X9_END

#include "wdLib.h"
#include "stdlib.h"
#include "taskLib.h"
#include "logLib.h"
#include "intLib.h"
#include "netLib.h"
#include "stdio.h"
#include "stdlib.h"
#include "sysLib.h"
#include "iv.h"
#include "memLib.h"
#include "semLib.h"
#include "cacheLib.h"
#include "sys/ioctl.h"
#include "etherLib.h"
#include "ioLib.h"


#define CPU_PENTIUM /* for the bug of OS in Pentium */

#ifndef DOC 			/* don't include when building documentation */
#include "net/mbuf.h"
#endif	/* DOC */

#include "net/protosw.h"
#include "sys/socket.h"
#include "errno.h"
#include "net/if.h"
#include "net/route.h"
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
#include "net/if_subr.h"
#include "m2Lib.h"
#include "etherMultiLib.h"		/* multicast stuff. */
#include "end.h"			/* Common END structures. */
#include "netBufLib.h"
#include "muxLib.h"

#include "endLib.h"
#include "lstLib.h" 		/* Needed to maintain protocol list. */

#define _not_specified(x) ((x) == NONE || (x) == 0)

#if 0
#undef LOCAL
#define LOCAL
#endif

/***** LOCAL DEFINITIONS *****/

#include "rtl81x9End.h"

/***** DEBUG MACROS *****/

/* #define RTL81X9_DEBUG */
//#ifdef	RTL81X9_DEBUG
#if 0

#define RTL81X9_DEBUG_OFF			0x0000
#define RTL81X9_DEBUG_RX			0x0001
#define RTL81X9_DEBUG_TX			0x0002
#define RTL81X9_DEBUG_INT			0x0004
#define RTL81X9_DEBUG_POLL			(RTL81X9_DEBUG_POLL_RX | RTL81X9_DEBUG_POLL_TX)
#define RTL81X9_DEBUG_POLL_RX		0x0008
#define RTL81X9_DEBUG_POLL_TX		0x0010
#define RTL81X9_DEBUG_LOAD			0x0020
#define RTL81X9_DEBUG_IOCTL			0x0040
#define RTL81X9_DEBUG_POLL_REDIR	0x10000
#define RTL81X9_DEBUG_LOG_NVRAM		0x20000
#define RTL81X9_DEBUG_FUNCLOG 0x40000
#define RTL81X9_DEBUG_ERROR 0x80000
#define RTL81X9_DEBUG_ALL			0xfffff

#define RTL81X9_LOG(FLG, X0, X1, X2, X3, X4, X5, X6)				\
	if ((rtl81x9Debug & FLG )&& pDrvCtrl->unit==2)			\
            logMsg(X0, X1, X2, X3, X4, X5, X6);

/* int rtl81x9Debug = (RTL81X9_DEBUG_ALL & (~RTL81X9_DEBUG_POLL));  */
/* Turn it off initially.  vicadd*/
int rtl81x9Debug =0x00000;

#else /*RTL81X9_DEBUG*/

#define RTL81X9_LOG(DBG_SW, X0, X1, X2, X3, X4, X5, X6)

#endif /*RTL81X9_DEBUG*/


#if 0
LOCAL int funcLogLevel;
LOCAL void enterFunc(const char * func)
{
	int i;
	char buf[512];
	char *p = buf;
	*buf = 0;
	for(i=0; i<funcLogLevel; i++){
		p += sprintf(p, "  ");
	}
	RTL81X9_LOG(RTL81X9_DEBUG_FUNCLOG, "%s Entering %s\n", (int)buf, (int)func, 0,1,2,3);
	funcLogLevel ++;
}

LOCAL void leaveFunc(const char * func)
{
	int i;
	char buf[512];
	char *p = buf;
	*buf = 0;
	funcLogLevel --;
	for(i=0; i<funcLogLevel; i++){
		p += sprintf(p, "  ");
	}
	RTL81X9_LOG(RTL81X9_DEBUG_FUNCLOG, "%s Leaving %s\n", (int)buf, (int)func, 0,1,2,3);
}

#define ENTER_FUNC() enterFunc(__FUNCTION__)
#define LEAVE_FUNC() leaveFunc(__FUNCTION__)

#define _RETURN LEAVE_FUNC(); return
#define _return return
#else
#define ENTER_FUNC()
#define LEAVE_FUNC()
#define _RETURN return
#define _return return
#endif

/* The definition of the driver control structure */
typedef struct rtl_device
	{	
	END_OBJ     end;			/* The class we inherit from. */
	rtl_ib       *ib;			/* ptr to Initialization Block */
	UINT8		devType;	    /* 8129, 8139A or 8139B  OR 8139C*/
	int			unit;			/* unit number */
	UINT8		phy_addr;		/* PHY address */
	int			nextDesc;		/* Next Tx Descriptor */
	int			freeDesc;		/* Free Tx Descriptors */
	char		*pDescMem[RTL_NUM_TX_DESC]; /* Pointer to buffer */
	char 		txmemspace[RTL_NUM_TX_DESC * RTL81x9_BUFSIZE];
	ULONG		rmdNext;		/* index into the next Rx Pkt */
	char		*ptrRxBufSpace;	/* Ptr to the Rx Buffer Pool */
	int			rringSize;		/* RMD ring size */
	int 		rringLen; 		/* RMD ring length (bytes) */
	RTL_RMD		*pRring;		/* RMD ring start */
	int         ivec;           /* interrupt vector */
	int         ilevel;         /* interrupt level */
	UINT32		devAdrs;		/* device register RAP */
	UINT16		csr3B;			/* csr3 value board specific */
	char*       pShMem;         /* real ptr to shared memory */
	char*       memBase;        /* RTL memory pool base */
	char*       memAdrs;        /* RTL memory pool base */
	int         memSize;        /* RTL memory pool size */
	int         memWidth;       /* width of data port */
	int         offset;
	int         csr0Errs;       /* count of csr0 errors */
	UINT32      flags;			/* Our local flags */
	UINT32		pciMemBase;		/* memory base as seen from PCI*/
	UCHAR		enetAddr[6];	/* ethernet address */
	CACHE_FUNCS cacheFuncs;     /* cache function pointers */
	BOOL		txBlocked; 		/* transmit flow control */
	CL_POOL_ID  pClPoolId;
	END_ERR     lastError;      /* Last error passed to muxError */
	BOOL        errorHandling;  /* task level error handling */
	u_short     errorStat;      /* error status */
	UINT32      reg_rcr;	/* RCR for reset */

	int intCounter;
	STATUS (*recvHook)(END_OBJ *, M_BLK * b);
} RTL81X9END_DEVICE;

/* network buffers configuration */

M_CL_CONFIG rtlMclConfig = 	/* mBlk configuration table */
    {
    0, 0, NULL, 0
    };

CL_DESC rtlClDesc [] = 	/* network cluster pool configuration table */
    {
    /* 
    clusterSize	num		memArea		memSize
    -----------	----		-------		-------
    */
    {RTL_BUFSIZ,		0,	NULL,		0}
    }; 

int rtlClDescNumEnt = (NELEMENTS(rtlClDesc));

#define END_FLAGS_ISSET(pEnd, setBits)									\
((pEnd)->flags & (setBits))

#define END_HADDR(pEnd) 												\
((pEnd)->mib2Tbl.ifPhysAddress.phyAddress)

#define END_HADDR_LEN(pEnd) 											\
((pEnd)->mib2Tbl.ifPhysAddress.addrLength)

/*
* Default macro definitions for BSP interface.
* For X86 arch, the intConnect/Disconnect defaults are pciIntConnect and
* pciIntDisconnect.  For all others it is just intConnect and a dummy
* disconnect function.
* HELP: This needs to be fixed by porting pciIntLib to all architectures.
*/

#if CPU_FAMILY == I80X86
#ifndef SYS_INT_CONNECT
#define SYS_INT_CONNECT(pDrvCtrl,rtn,arg,pResult)						\
{																	\
	IMPORT STATUS pciIntConnect();										\
	*pResult = pciIntConnect ((VOIDFUNCPTR *)INUM_TO_IVEC (pDrvCtrl->ivec),\
	(rtn), (int)(arg)); 					   \
}
#endif	/* SYS_INT_CONNECT */

#ifndef SYS_INT_DISCONNECT
#define SYS_INT_DISCONNECT(pDrvCtrl,rtn,arg,pResult)					\
{																	\
	IMPORT STATUS pciIntDisconnect();									   \
	*pResult = pciIntDisconnect ((VOIDFUNCPTR *)INUM_TO_IVEC (pDrvCtrl->ivec),\
	(rtn)); 							\
}
#endif /* SYS_INT_DISCONNECT */

#else /* CPU_FAMILY == I80X86 */

#ifndef SYS_INT_CONNECT
#define SYS_INT_CONNECT(pDrvCtrl,rtn,arg,pResult)						\
{																	\
	IMPORT STATUS intConnect(); 									 \
	*pResult = intConnect ((VOIDFUNCPTR *)INUM_TO_IVEC (pDrvCtrl->ivec),\
	(rtn), (int)(arg)); 					   \
}
#endif /*SYS_INT_CONNECT*/

#ifndef SYS_INT_DISCONNECT
#define SYS_INT_DISCONNECT(pDrvCtrl,rtn,arg,pResult)					\
{																	\
	*pResult = OK;							\
}
#endif /*SYS_INT_DISCONNECT*/


#endif /* CPU_FAMILY == I80X86 */

/* Macro to enable the appropriate interrupt level */

#ifndef SYS_INT_ENABLE
#define SYS_INT_ENABLE(pDrvCtrl) \
{ \
	IMPORT STATUS sysRtl81x9IntEnable(); \
	sysRtl81x9IntEnable ((pDrvCtrl)->ilevel); \
}
#endif /* SYS_INT_ENABLE*/

/* Macro to disable the appropriate interrupt level */

#ifndef SYS_INT_DISABLE
#define SYS_INT_DISABLE(pDrvCtrl) \
{ \
	IMPORT void sysRtl81x9IntDisable (); \
	sysRtl81x9IntDisable ((pDrvCtrl)->ilevel); \
}
#endif

#ifndef SYS_OUT_LONG
#define SYS_OUT_LONG(pDrvCtrl,addr,value) \
{ \
	*((ULONG *)(addr)) = PCI_SWAP((value)); \
}
#endif /* SYS_OUT_LONG */

#ifndef SYS_IN_LONG
#define SYS_IN_LONG(pDrvCtrl,addr,data) \
{ \
	((data) = PCI_SWAP(*((ULONG *)(addr)))); \
}
#endif /* SYS_IN_LONG */

#ifndef SYS_OUT_SHORT
#define SYS_OUT_SHORT(pDrvCtrl,addr,value) \
{ \
	*((USHORT *)(addr)) = PCI_WORD_SWAP((value)); \
}
#endif /* SYS_OUT_SHORT*/

#ifndef SYS_IN_SHORT
#define SYS_IN_SHORT(pDrvCtrl,addr,data) \
	{ \
	((data) = PCI_WORD_SWAP(*((USHORT *)(addr)))); \
	}	   
#endif /* SYS_IN_SHORT*/

#ifndef SYS_OUT_BYTE
#define SYS_OUT_BYTE(pDrvCtrl,addr,value) \
	{ \
	*((UCHAR *)(addr)) = (value); \
	}
#endif /* SYS_OUT_BYTE */

#ifndef SYS_IN_BYTE
#define SYS_IN_BYTE(pDrvCtrl,addr,data) \
	{ \
	((data) = *((UCHAR *)(addr))); \
	}
#endif /* SYS_IN_BYTE */

#ifndef SYS_OUT_SHORT_CSR
#define SYS_OUT_SHORT_CSR(pDrvCtrl,addr,value) \
	{ \
	*(USHORT *)addr = value; \
	}
#endif /*SYS_OUT_SHORT_CSR*/

#ifndef SYS_IN_SHORT_CSR
#define SYS_IN_SHORT_CSR(pDrvCtrl,addr,pData) \
(*(USHORT *)pData = *(USHORT *)addr)
#endif /*SYS_IN_SHORT_CSR*/


#define SYS_DELAY(count)	{												\
	volatile int cx = 0;							\
	for (cx = 0; cx < (count); cx++);				\
	}

#undef SYS_ENET_ADDR_GET
#define SYS_ENET_ADDR_GET(pDrvCtrl, pAddress) \
	{ \
	IMPORT STATUS sysRtl81x9EnetAddrGet (RTL81X9END_DEVICE *pDrvCtrl, \
	char * enetAdrs); \
	sysRtl81x9EnetAddrGet (pDrvCtrl, pAddress); \
	}

/* Cache macros */

#define RTL_CACHE_INVALIDATE(address, len) \
CACHE_DRV_INVALIDATE (&pDrvCtrl->cacheFuncs, (address), (len))

#define RTL_CACHE_VIRT_TO_PHYS(address) \
CACHE_DRV_VIRT_TO_PHYS (&pDrvCtrl->cacheFuncs, (address))


/*
* MII access routines are provided for the 8129, which
* doesn't have a built-in PHY. For the 8139, we fake things
* up by diverting rl_phy_readreg()/rl_phy_writereg() to the
* direct access PHY registers.
*/

#define MII_SET(x)					\
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_MII,				\
rtl81x9CsrReadByte(pDrvCtrl, RTL_REGS_MII, RTL_WIN_0) | x, RTL_WIN_0 )

#define MII_CLR(x)					\
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_MII,				\
rtl81x9CsrReadByte(pDrvCtrl, RTL_REGS_MII, RTL_WIN_0) & ~x, RTL_WIN_0 )

/* EEPROM Macros */

#define EE_SET(x)					\
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_CFG_9346,			\
rtl81x9CsrReadByte(pDrvCtrl, RTL_REGS_CFG_9346, RTL_WIN_0) | x, RTL_WIN_0)

#define EE_CLR(x)					\
	rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CFG_9346,			\
rtl81x9CsrReadByte(pDrvCtrl, RTL_REGS_CFG_9346, RTL_WIN_0) & ~x, RTL_WIN_0)



/***** LOCALS *****/

LOCAL int rtlRsize = RTL_RMD_RLEN;	  /* recv ring size */

/* forward static functions */

LOCAL STATUS	rtl81x9Reset ();
LOCAL void		rtl81x9Int			(RTL81X9END_DEVICE *);
LOCAL void		rtl81x9HandleRecvInt(RTL81X9END_DEVICE *);
LOCAL void		rtl81x9HandleTxInt	(RTL81X9END_DEVICE *);
LOCAL void		rtl81x9Restart		(RTL81X9END_DEVICE *);
LOCAL STATUS	rtl81x9RestartSetup (RTL81X9END_DEVICE *);
LOCAL void		rtl81x9Config		(RTL81X9END_DEVICE *);
LOCAL void		rtl81x9AddrFilterSet(RTL81X9END_DEVICE *);

/* END Specific interfaces. */


/* This is the only externally visible interface. */

END_OBJ *		rtl81x9EndLoad (char *initString);

LOCAL STATUS	rtl81x9Start		(RTL81X9END_DEVICE *);
LOCAL STATUS	rtl81x9Stop 		(RTL81X9END_DEVICE *);
LOCAL STATUS	rtl81x9Unload		(RTL81X9END_DEVICE *);
LOCAL int		rtl81x9Ioctl		(RTL81X9END_DEVICE *, int, caddr_t);
LOCAL STATUS	rtl81x9Send 		(RTL81X9END_DEVICE *, M_BLK *);
LOCAL STATUS	rtl81x9MCastAddrAdd (RTL81X9END_DEVICE *, char *);
LOCAL STATUS	rtl81x9MCastAddrDel (RTL81X9END_DEVICE *, char *);
LOCAL STATUS	rtl81x9MCastAddrGet (RTL81X9END_DEVICE *, MULTI_TABLE *);
LOCAL STATUS	rtl81x9PollSend 	(RTL81X9END_DEVICE *, M_BLK *);
LOCAL STATUS	rtl81x9PollReceive	(RTL81X9END_DEVICE *, M_BLK *);
LOCAL STATUS	rtl81x9PollStart	(RTL81X9END_DEVICE *);
LOCAL STATUS	rtl81x9PollStop 	(RTL81X9END_DEVICE *);
LOCAL STATUS	rtl81x9InitParse	(RTL81X9END_DEVICE *, char *);
LOCAL STATUS	rtl81x9InitMem		(RTL81X9END_DEVICE *);


LOCAL void		rtl81x9LowPowerMode (RTL81X9END_DEVICE *);
LOCAL UCHAR 	rtl81x9CsrReadByte	(RTL81X9END_DEVICE *, USHORT, int);
LOCAL USHORT	rtl81x9CsrReadWord	(RTL81X9END_DEVICE *, USHORT, int);
LOCAL ULONG 	rtl81x9CsrReadLong	(RTL81X9END_DEVICE *, USHORT, int);
LOCAL void		rtl81x9CsrWriteByte (RTL81X9END_DEVICE *, USHORT, UCHAR, int);
LOCAL void		rtl81x9CsrWriteWord (RTL81X9END_DEVICE *, USHORT, USHORT, int);
LOCAL void		rtl81x9CsrWriteLong (RTL81X9END_DEVICE *, USHORT, ULONG, int);
LOCAL void		rtl81x9ReadEEPROM	(RTL81X9END_DEVICE *, UCHAR *, ULONG, ULONG, ULONG);
LOCAL void		rtl81x9EEPROMPutByte(RTL81X9END_DEVICE *, ULONG);
LOCAL void		rtl81x9EEPROMGetWord(RTL81X9END_DEVICE *, ULONG, USHORT*);

LOCAL void		rtl81x9Phy_writereg (RTL81X9END_DEVICE *, int, int);
LOCAL USHORT	rtl81x9Phy_readreg	(RTL81X9END_DEVICE *, int);
LOCAL int		rtl81x9MII_writereg (RTL81X9END_DEVICE *, RTL_MII_FRAME *);
LOCAL void		rtl81x9MII_sync 	(RTL81X9END_DEVICE *);
LOCAL void		rtl81x9MII_send 	(RTL81X9END_DEVICE *, ULONG, int);
LOCAL int		rtl81x9MII_readreg	(RTL81X9END_DEVICE *, RTL_MII_FRAME *);
LOCAL void		rtl81x9AutoNegTx	(RTL81X9END_DEVICE *);
LOCAL int		rtl81x9MII_autoneg	(RTL81X9END_DEVICE *);
LOCAL int		rtl81x9MediaSet 	(RTL81X9END_DEVICE *, int);
LOCAL int		rtl81x9MediaConfig	(RTL81X9END_DEVICE *);

/* 
* Define the device function table.  This is static across all driver
* instances.
*/

LOCAL NET_FUNCS rtlFuncTable = 
{
	(FUNCPTR)rtl81x9Start,		/* start func. */				  
	(FUNCPTR)rtl81x9Stop,			/* stop func. */
	(FUNCPTR)rtl81x9Unload, 	/* unload func. */				  
	(FUNCPTR)rtl81x9Ioctl,		/* ioctl func. */				  
	(FUNCPTR)rtl81x9Send,			/* send func. */				  
	(FUNCPTR)rtl81x9MCastAddrAdd,	/* multicast add func. */		  
	(FUNCPTR)rtl81x9MCastAddrDel,	/* multicast delete func. */	  
	(FUNCPTR)rtl81x9MCastAddrGet,	/* multicast get fun. */		  
	(FUNCPTR)rtl81x9PollSend,		/* polling send func. */		  
	(FUNCPTR)rtl81x9PollReceive,	/* polling receive func. */ 	  
	endEtherAddressForm,			/* put address info into a NET_BUFFER */
	endEtherPacketDataGet,		/* get pointer to data in NET_BUFFER */
	endEtherPacketAddrGet			/* Get packet addresses. */
};				


/*******************************************************************************
*
* rtl81x9EndLoad - initialize the driver and device
*
* This routine initializes the driver and the device to the operational state.
* All of the device-specific parameters are passed in <initString>, which
* expects a string of the following format:
*
* <unit>:<CSR_reg_addr>:<RAP_reg_addr>:<int_vector>:<int_level>:<shmem_addr>:
* <shmem_size>:<shmem_width>
*
* This routine can be called in two modes. If it is called with an empty but
* allocated string, it places the name of this device (that is, "rtl") into 
* the <initString> and returns 0.
*
* If the string is allocated and not empty, the routine attempts to load
* the driver using the values specified in the string.
*
* RETURNS: An END object pointer, or NULL on error, or 0 and the name of the
* device if the <initString> was NULL.
*/

END_OBJ* rtl81x9EndLoad
(
 char* initString		/* string to be parse by the driver */
 )
{
	RTL81X9END_DEVICE	*pDrvCtrl;
	USHORT				rtl_dev_id = 0;
	int 				speed;
	int 				i;
	

	ENTER_FUNC();
	
	RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "rtl81x9EndLoad %s\n", (int)initString, 0, 0, 0, 0, 0);
		
	if (initString == NULL){
		_RETURN NULL;
	}
	
	if (initString[0] == 0){
		bcopy((char *)RTL_DEV_NAME, initString, RTL_DEV_NAME_LEN);
		_RETURN 0;
	}
	
	/* allocate the device structure */
	
	pDrvCtrl = (RTL81X9END_DEVICE *)calloc (sizeof (RTL81X9END_DEVICE), 1);
	if (pDrvCtrl == NULL)
		goto errorExit;
	
	/* parse the init string, filling in the device structure */
	
	if (rtl81x9InitParse (pDrvCtrl, initString) == ERROR)
		goto errorExit;
	
	/* Reset the adaptor */
	rtl81x9Reset (pDrvCtrl);
	
	/* Read the station address */
	for (i=0; i < 6; i++){
		pDrvCtrl->enetAddr[i] = rtl81x9CsrReadByte (pDrvCtrl, RTL_REGS_IDR0 + i, RTL_WIN_0);
	}
				
	/*
	* Now read the exact device type from the EEPROM to find
	* out if it's an 8129 or 8139.
	*/
	rtl81x9ReadEEPROM (pDrvCtrl, (UCHAR *) &rtl_dev_id, RTL_EE_PCI_DID, 1, 0);
	
	/* Perform memory allocation */
	
	if (rtl81x9InitMem (pDrvCtrl) == ERROR)
		goto errorExit;
	
	if (rtl_dev_id == RTL_DEVICEID_8139 || rtl_dev_id == ACCTON_DEVICEID_5030 ||
		rtl_dev_id == DELTA_DEVICEID_8139 || rtl_dev_id == ADDTRON_DEVICEID_8139)
	{
		if ((rtl81x9CsrReadLong (pDrvCtrl, RTL_REGS_TX_CONFIG, 0) & RTL_TXCG_BLID))/*vicadd*/
			pDrvCtrl->devType = RTL_DEV_8139A;
		else
			pDrvCtrl->devType = RTL_DEV_8139B;
	}
	else if (rtl_dev_id == RTL_DEVICEID_8129)
		pDrvCtrl->devType = RTL_DEV_8129;
	else {
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl: unknown device ID: %x\n", rtl_dev_id, 2, 3, 4, 5, 6);
		goto errorExit;
	}
	
	speed =  rtl81x9MediaConfig (pDrvCtrl);
	
	pDrvCtrl->nextDesc = 0;
	pDrvCtrl->freeDesc = RTL_NUM_TX_DESC;
	
	for (i=0; i < RTL_NUM_TX_DESC; i++)
		pDrvCtrl->pDescMem[i] = NULL; 
	
	/* Perform memory distribution and reset and reconfigure the device */
	
	if (rtl81x9RestartSetup (pDrvCtrl) == ERROR)
		goto errorExit;
	
	/* initialize the END and MIB2 parts of the structure */
	
	if (END_OBJ_INIT (&pDrvCtrl->end, (DEV_OBJ *)pDrvCtrl, RTL_DEV_NAME,
		pDrvCtrl->unit, &rtlFuncTable,
		"RTL 81x9 Fast Ethernet Enhanced Network Driver") == ERROR
		|| END_MIB_INIT (&pDrvCtrl->end, M2_ifType_ethernet_csmacd,
		&pDrvCtrl->enetAddr[0], 6, ETHERMTU,
		speed)
		== ERROR)
		goto errorExit;
	
	/* set the flags to indicate readiness */
	
	END_OBJ_READY (&pDrvCtrl->end,
		IFF_UP | IFF_RUNNING | IFF_NOTRAILERS | IFF_BROADCAST
		| IFF_MULTICAST | IFF_SIMPLEX);
	
	/*V_LOG (RTL81X9_DEBUG_LOAD, "Done loading rtl...\n", 1, 2, 3, 4, 5, 6);*/
	
	_RETURN &pDrvCtrl->end;
	
errorExit:
	if (pDrvCtrl != NULL)
		free ((char *)pDrvCtrl);
	
	_RETURN NULL;
}
	
	
	
/*******************************************************************************
*
* rtl81x9InitParse - parse parameter values from initString
*
* Parse the input string.  Fill in values in the driver control structure.
*
* The initialization string format is:
* "<device addr>:<PCI addr>:<ivec>:<ilevel>:<mem base>:<mem size>:	\
*  <user flags>:<offset>"
*
* .IP <device addr>
* base address of hardware device registers
* .IP <PCI addr>
* main memory address over the PCI bus
* .IP <ivec>
* interrupt vector number
* .IP <ilevel>
* interrupt level
* .IP <mem base>
* base address of a DMA-able, cache free,pre-allocated	memory
* .IP <mem size>
* size of the pre-allocated memory
* .IP <user flags>
* User flags control the run-time characteristics of the chip
* .IP <offset>
* Memory offset for alignment
* .LP
*
* RETURNS: OK or ERROR for invalid arguments.
*/

LOCAL STATUS rtl81x9InitParse
	(
	RTL81X9END_DEVICE * pDrvCtrl,
	char *	initString
	)
{
	char *		tok;
	/*char**	  holder = NULL;*/
	char*	   holder = NULL;	/* vicadd*/
	UINT32		devMemAddr;
	UINT32		devIoAddr;
	
	/* Parse the initString */
	ENTER_FUNC();
	RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "Parse starting ...\n", 0, 0, 0, 0, 0, 0);
	
	/* Unit number. */
	
	tok = strtok_r (initString, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->unit = atoi (tok);
	
	RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "Unit : %d ...\n", pDrvCtrl->unit, 0, 0, 0, 0, 0);
	
	/* devAdrs address. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	devMemAddr = (UINT32) strtoul (tok, NULL, 16);
	
	RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "devMemAddr : 0x%X ...\n", devMemAddr, 0, 0, 0, 0, 0);
	
	/* devIoAddrs address */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	devIoAddr = (UINT32) strtoul (tok, NULL, 16);
	
	/* always use memory mapped IO if provided, else use io map */
	
	if (_not_specified(devMemAddr) && _not_specified(devIoAddr)){
		RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "No memory or IO base specified ...\n", 0, 0, 0, 0, 0, 0);
		_RETURN ERROR;
	}else if (!_not_specified(devMemAddr)){
		pDrvCtrl->devAdrs = devMemAddr;
		pDrvCtrl->flags   |= RTL_FLG_MODE_MEM_IO_MAP;
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "devMemAddr specified for devAdrs ...\n", 0, 0, 0, 0, 0, 0);
	}else{
		pDrvCtrl->devAdrs = devIoAddr;
		RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "devIoAddr specified for devAdrs - 0x%X ...\n", devIoAddr, 0, 0, 0, 0, 0);
	}
	
	/* PCI memory base address as seen from the CPU */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->pciMemBase = strtoul (tok, NULL, 16);
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Pci : 0x%X ...\n", pDrvCtrl->pciMemBase, 0, 0, 0, 0, 0);
	
	/* Interrupt vector. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->ivec = atoi (tok);
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "ivec : 0x%X ...\n", pDrvCtrl->ivec, 0, 0, 0, 0, 0);
	
	/* Interrupt level. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->ilevel = atoi (tok);
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "ilevel : 0x%X ...\n", pDrvCtrl->ilevel, 0, 0, 0, 0, 0);
	
	/* Caller supplied memory address. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->memAdrs = (char *)strtoul (tok, NULL, 16);
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "memAdrs : 0x%X ...\n", (int)pDrvCtrl->memAdrs, 0, 0, 0, 0, 0);
	
	/* Caller supplied memory size. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->memSize = strtoul (tok, NULL, 16);
	
	RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "memSize : 0x%X ...\n", pDrvCtrl->memSize, 0, 0, 0, 0, 0);
	
	/* Caller supplied memory width. */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->memWidth = atoi (tok);
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, ("memWidth : 0x%X ...\n", pDrvCtrl->memWidth,
	2, 3, 4, 5, 6);*/
	
	/* CSR3B value */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->csr3B = strtoul (tok, NULL, 16);
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, ("csr3b value : %d ...\n", pDrvCtrl->csr3B,
	2, 3, 4, 5, 6);*/
	
	/* Caller supplied alignment offset. */
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	pDrvCtrl->offset = atoi (tok);
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, ("offset value : %d ...\n", pDrvCtrl->offset,
	2, 3, 4, 5, 6);*/
	
	/* caller supplied flags */
	
	tok = strtok_r (NULL, ":", &holder);
	if (tok == NULL){
		_RETURN ERROR;
	}
	
	pDrvCtrl->flags |= strtoul (tok, NULL, 16);
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, ("flags : 0x%X ...\n", pDrvCtrl->flags,
	2, 3, 4, 5, 6);*/
	
	_RETURN OK;
}

/*******************************************************************************
*
* rtl81x9InitMem - initialize memory for the device
*
* Using data in the control structure, setup and initialize the memory
* areas needed.  If the memory address is not already specified, then allocate
* cache safe memory.
*
* RETURNS: OK or ERROR.
*
*/

LOCAL STATUS rtl81x9InitMem
	(
	RTL81X9END_DEVICE * pDrvCtrl	/* device to be initialized */
	)
{
	UINT	sz = 0; 			/* temporary size holder */

	ENTER_FUNC();
	
	/***** Establish size of shared memory region we require *****/
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl81x9InitMem\n", 0, 0, 0, 0, 0, 0);*/
	if ( !_not_specified((int)pDrvCtrl->memAdrs) ) {
	/* specified memory pool */
	/*
	* With a specified memory pool we want to maximize
	* rtlRsize and rtlTsize
		*/
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "No memAdrs supplied\n", 0, 0, 0, 0, 0, 0); 
		
		sz = (pDrvCtrl->memSize - (RMD_SIZ + sizeof (rtl_ib)))
			/ ((2 * RTL_BUFSIZ) + RMD_SIZ);
		
		sz >>= 1;				/* adjust for roundoff */
		
		for (rtlRsize = 0; sz != 0; rtlRsize++, sz >>= 1)
			;
		
	}
	
	/* limit ring sizes to reasonable values */
	
	rtlRsize = max (rtlRsize, 2);		/* 4 Rx buffers is reasonable min */
	rtlRsize = min (rtlRsize, 7);		/* 128 Rx buffers is max for chip */
	
	/* Add it all up */
	
	sz = (((1 << rtlRsize) + 1) * RMD_SIZ) + IB_SIZ + 24;
	
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "sx - %d\n",sz, 0, 0, 0, 0, 0); */
	
	
	/***** Establish a region of shared memory *****/
	
	/* OK. We now know how much shared memory we need.	If the caller
	* provides a specific memory region, we check to see if the provided
	* region is large enough for our needs.  If the caller did not
	* provide a specific region, then we attempt to allocate the memory
	* from the system, using the cache aware allocation system call.
	*/
	
	switch ((int) pDrvCtrl->memAdrs){
	default :		/* caller provided memory */
		if (pDrvCtrl->memSize < sz){
			/* not enough space */
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl81x9: not enough memory provided need %ul got %d\n", 
				pDrvCtrl->memSize, sz, 0, 0, 0, 0);
			_RETURN OK;
		}
		
		/* set the beginning of pool */
		
		pDrvCtrl->pShMem = pDrvCtrl->memAdrs;
		
		/* assume pool is cache coherent, copy null structure */
		
		pDrvCtrl->cacheFuncs = cacheNullFuncs;
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Memory checks out\n",0, 0, 0, 0, 0, 0); 
		break;
		
	case NONE : 	/* get our own memory */
	case NULL:
		
		/* Because the structures that are shared between the device
		* and the driver may share cache lines, the possibility exists
		* that the driver could flush a cache line for a structure and
		* wipe out an asynchronous change by the device to a neighboring
		* structure. Therefore, this driver cannot operate with memory
		* that is not write coherent.  We check for the availability of
		* such memory here, and abort if the system did not give us what
		* we need.
		*/
		
		if (!CACHE_DMA_IS_WRITE_COHERENT ()){
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl: device requires cache coherent memory\n", 0, 0, 0, 0, 0, 0);
			_RETURN ERROR;
		}
		
		pDrvCtrl->pShMem = (char *) cacheDmaMalloc (sz);
		
		if ((int)pDrvCtrl->pShMem == 0){
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl: system memory unavailable\n", 0, 0, 0, 0, 0, 0);
			_RETURN ERROR;
		}
		
		/* copy the DMA structure */
		
		pDrvCtrl->cacheFuncs = cacheDmaFuncs;
		
		break;
	}
	
	/*						  Turkey Carving
	*						 --------------
	*
	*						   LOW MEMORY
	*
	*			  |----------------------------------------|
	*			  | 	  The initialization block		   |
	*			  | 		(sizeof (rtl_ib))			   |
	*			  |----------------------------------------|
	*			  | 		The Rx descriptors			   |
	*			  | ((1 << rtlRsize) + 1)*sizeof (RTL_RMD) |
	*			  |----------------------------------------|
	*/
	
	/* align */
	pDrvCtrl->pShMem = (char *) ( ( (int)pDrvCtrl->pShMem + 3) & ~3);
	
	/* Save some things */
	
	pDrvCtrl->memBase  = (char *)((ULONG)pDrvCtrl->pShMem & 0xff000000);
	
	if (_not_specified((int)pDrvCtrl->memAdrs))
		pDrvCtrl->flags |= RTL_FLG_MEM_ALLOC_FLAG;
	
	/* first let's clear memory */
	
	bzero ((char *) pDrvCtrl->pShMem, (int) sz); 
	
	/* setup Rx memory pointers */
	
	pDrvCtrl->pRring	  = (RTL_RMD *) ((int)pDrvCtrl->pShMem + IB_SIZ);
	pDrvCtrl->rringLen	  = rtlRsize;
	pDrvCtrl->rringSize   = 1 << rtlRsize;
	
	/* Allocate a chunk of memory for the Chip to place the Rx Buffers in */
	
	pDrvCtrl->ptrRxBufSpace = malloc (RTL_RXBUFLEN + 64);		
	
	if (pDrvCtrl->ptrRxBufSpace == NULL){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "ptrRxBufSpace == NULL\n", 0, 0, 0, 0, 0, 0);
		_RETURN ERROR;
	}

	pDrvCtrl->ptrRxBufSpace += 4;
	
	pDrvCtrl->rmdNext = 0;
	
	/*
	* Allocate receive buffers from our own private pool.
	*/
	if ((pDrvCtrl->end.pNetPool = malloc (sizeof(NET_POOL))) == NULL){
		_RETURN ERROR;
	}
	
	rtlMclConfig.mBlkNum = pDrvCtrl->rringSize * 2;
	rtlClDesc[0].clSize = RTL_BUFSIZ;
	rtlClDesc[0].clNum = pDrvCtrl->rringSize *2;
	rtlMclConfig.clBlkNum = rtlClDesc[0].clNum;
	
	rtlMclConfig.memSize = (rtlMclConfig.mBlkNum * (MSIZE + sizeof (long))) +
		(rtlMclConfig.clBlkNum * (CL_BLK_SZ + sizeof(long)));
	
	if ((rtlMclConfig.memArea = (char *) memalign (sizeof(long), rtlMclConfig.memSize))== NULL){
		_RETURN ERROR;
	}
	rtlClDesc[0].clNum = pDrvCtrl->rringSize *2;
	
	rtlClDesc[0].memSize = (rtlClDesc[0].clNum * (RTL_BUFSIZ + 8))	+ sizeof(int);
	
	if (!_not_specified((int)pDrvCtrl->memAdrs)) {
		/* Do we hand over our own memory? */
		rtlClDesc[0].memArea = (char *)(pDrvCtrl->pRring + (((1 << rtlRsize) + 1) * RMD_SIZ));
	}else{
		rtlClDesc[0].memArea = (char *) cacheDmaMalloc (rtlClDesc[0].memSize);
		if ((int)rtlClDesc[0].memArea == 0)	{
			RTL81X9_LOG(RTL81X9_DEBUG_LOAD, "system memory unavailable\n", 1, 2, 3, 4, 5, 6);
			_RETURN ERROR;
		}
	}
	
	if (netPoolInit(pDrvCtrl->end.pNetPool, &rtlMclConfig, &rtlClDesc[0], NELEMENTS(rtlClDesc), NULL) == ERROR){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Could not init buffering\n",0, 0, 0, 0, 0, 0); 
		_RETURN ERROR;
	}
	/* Store the cluster pool id as others need it later. */
	pDrvCtrl->pClPoolId = clPoolIdGet(pDrvCtrl->end.pNetPool, RTL_BUFSIZ, FALSE);
	
	_RETURN OK;
}
	
/*******************************************************************************
*
* rtl81x9Start - start the device
*
* This function initializes the device and calls BSP functions to connect
* interrupts and start the device running in interrupt mode.
*
* The complement of this routine is rtl81x9Stop.  Once a unit is reset by
* rtl81x9Stop, it may be re-initialized to a running state by this routine.
*
* RETURNS: OK if successful, otherwise ERROR
*/

LOCAL STATUS rtl81x9Start
	(
	RTL81X9END_DEVICE * pDrvCtrl
	)
{
	STATUS	result;
	int 	rxcfg;
	
	ENTER_FUNC();
	RTL81X9_LOG (RTL81X9_DEBUG_FUNCLOG, "RTL81x9 start\n",1 , 2, 3, 4, 5, 6);
	/* logMsg("RTL81X9 start %d\n", pDrvCtrl->unit, 2,3,4,5,6); */
	
	pDrvCtrl->txBlocked = FALSE;
	SYS_INT_CONNECT (pDrvCtrl, rtl81x9Int, (int)pDrvCtrl, &result);
	if (result == ERROR){
		_RETURN ERROR;
	}
	
	SYS_INT_ENABLE (pDrvCtrl);
	
	/* Init the RX buffer pointer register. */
	
	rtl81x9CsrWriteLong(pDrvCtrl, RTL_REGS_RX_BUF, (ULONG) pDrvCtrl->ptrRxBufSpace, RTL_WIN_0);
	/*RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rxbuffer start- %x: \n",(ULONG) pDrvCtrl->ptrRxBufSpace , 2, 3, 4, 5, 6);*/		
	
	/* Enable Tx and RX */
	rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_RX_ENB + RTL_CMD_TX_ENB, RTL_WIN_0);
	
	/*
	* Set the initial TX and RX configuration.
	* Set the buffer size and set the wrap register
	*/
	
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_CONFIG, RTL_TXCFG_CONFIG, RTL_WIN_0); 
	
	/* RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rtl81x9-TXCFG - %x: \n",RTL_TXCFG_CONFIG , 2, 3, 4, 5, 6);*/
	
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, RTL_RXCFG_CONFIG, RTL_WIN_0); 
	
	rxcfg = rtl81x9CsrReadLong(pDrvCtrl, RTL_REGS_RX_CONFIG, RTL_WIN_0);
	
	/* Set the Early Threshold bits depending on flags read */	/*vicadd*/
	/* from initialisation string							*/
	rxcfg |= ((pDrvCtrl->flags >> 16) << 24);
	
	/* Set the individual bit to receive frames for this host only. */
	rxcfg |= RTL_RXCG_APM;
	
	/* If we want promiscuous mode, set the allframes bit. */
	if (pDrvCtrl->ib->rtlIBMode == 0x8000){ 
		rxcfg |= RTL_RXCG_AAP;
		rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, rxcfg, RTL_WIN_0); 
	}else{ 
		rxcfg &= ~RTL_RXCG_AAP;
		rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, rxcfg, RTL_WIN_0); 
	}
	/*
	* Set capture broadcast bit to capture broadcast frames.
	*/
	rxcfg |= RTL_RXCG_AB;
	
	
	/*	RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rtl81x9-RCR - %x: \n", rxcfg, 2, 3, 4, 5, 6);*/
	
	pDrvCtrl-> reg_rcr =rxcfg;/* save it */
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, rxcfg, RTL_WIN_0); 
	
	/* We now need to update the Multicast Registers */
	/* These values need to be finalised and written */
	
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_MAR0, 0xffff, RTL_WIN_0); 
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_MAR0 + 4, 0xffff, RTL_WIN_0); 
	
	/* Enable Controller Interrupts */
	
	/*vicadd*/
	if(pDrvCtrl->flags & RTL_FLG_POLLING){
		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0, 0);
	}else{
		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);
	}
	
	/* RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rtl81x9-IMR - %x: \n",RTL_VALID_INTERRUPTS , 2, 3, 4, 5, 6);*/
	
	/* Start RX/TX process. */
	rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_MISSED, 0, RTL_WIN_0); 
	
	/* Enable Tx and RX */
	rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_RX_ENB + RTL_CMD_TX_ENB, RTL_WIN_0);
	
	_RETURN OK;
}

#ifdef ETHER_DEBUG
int rtlLastPacketLen;
char rtlLastPacket[1600];
int rtlLastPacketLenSent;
char rtlLastPacketSent[1600];
int jobAddMagic;
int rtlIntMagic;
#endif

/*******************************************************************************
*
* rtl81x9Int - handle controller interrupt
*
* This routine is called at interrupt level in response to an interrupt from
* the controller.
*
* RETURNS: N/A.
*/

LOCAL void rtl81x9Int
	(
	RTL81X9END_DEVICE  *pDrvCtrl
	)
{
	u_short 	   stat;

	ENTER_FUNC();
#ifdef ETHER_DEBUG
	rtlIntMagic = 'IM';
#endif
	/* Disable controller interrupts. */
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);
	
	for (;;){
		pDrvCtrl->intCounter++;
		
		/* Read the interrupt status register */
		stat = rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE);
		RTL81X9_LOG (RTL81X9_DEBUG_INT, "ISR %x \n", stat,0,0,0,0,0);
		
		/* clear interrupts, */
		/* 
		jht, no use as the datasheet states that write to ISR has no effect 
		just read ISR will clear it
		jht 2005-9-6 
		yes it's useful, the datasheet is wrong, writing with 1 will clear the bits
		respectfully, see the p-guide for detail.
		*/
		if (stat){
			/* In case of an RxFIFOOver we must also clear the RxOverflow
		   bit to avoid dropping frames for ever.
			*/
			rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_STATUS, 
				(stat & RTL_IPT_RX_FIFO_OVER)? stat | RTL_IPT_RX_OVERFLOW : stat, NONE);
		}
		
		/* Check if a valid Interrupt has been set */
		if ((stat & RTL_VALID_INTERRUPTS) == 0)
			break;
		
		if (stat & RTL_IPT_PCI_ERR)	{
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_PCI_ERR - Reset and Re initialise\n", 0,0,0,0,0,0);
			rtl81x9Reset (pDrvCtrl);
			rtl81x9Restart (pDrvCtrl);
		}
		
		if (stat & RTL_IPT_PCS_TIMEOUT){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_PCS_TIMEOUT\n", 0, 0, 0, 0, 0, 0);
		}
		
		if (stat & RTL_IPT_CABLE_LEN_CHG){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_CABLE_LEN_CHG\n", 0, 0, 0, 0, 0, 0);
		}
		
		if (stat & RTL_IPT_RX_FIFO_OVER){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_RX_FIFO_OVER\n", 0, 0, 0, 0, 0, 0);
		}
		
		if (stat & RTL_IPT_RX_UNDERUN){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_RX_UNDERUN\n", 0, 0, 0, 0, 0, 0);
			/*rxcfg=rtl81x9CsrReadLong (pDrvCtrl, RTL_REGS_RX_CONFIG,  RTL_WIN_0);				
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rtl81x9-RCR - %x: \n", rxcfg, 2, 3, 4, 5, 6);
			*/	
		}
		
		if (stat & RTL_IPT_RX_OVERFLOW){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_RX_OVERFLOW\n", 0, 0, 0, 0, 0, 0);
		}
		
		if (stat & RTL_IPT_TX_ERR){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_TX_ERR\n", 0, 0, 0, 0, 0, 0);
			rtl81x9HandleTxInt (pDrvCtrl);
		}
		
		/* Check for transmit Interrupt */
		if (stat & RTL_IPT_TX_OK){
			rtl81x9HandleTxInt (pDrvCtrl);
		}
		
		if (stat & RTL_IPT_RX_ERR){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RTL_IPT_RX_ERR\n", 0, 0, 0, 0, 0, 0);
		}
		
		if (stat & (RTL_IPT_RX_OK | RTL_IPT_RX_OVERFLOW | RTL_IPT_RX_FIFO_OVER | RTL_IPT_RX_UNDERUN)){
			int code;
#ifdef ETHER_DEBUG
			jobAddMagic = 'magi';
#endif
			code = netJobAdd ((FUNCPTR)rtl81x9HandleRecvInt, (int) pDrvCtrl, 0, 0, 0, 0);
#ifdef ETHER_DEBUG
			jobAddMagic = 0;
#endif
			if(code != OK){
				RTL81X9_LOG (RTL81X9_DEBUG_INT, "xl: netJobAdd (rtl81x9HandleRecvInt) failed\n", 0, 0, 0, 0, 0, 0);
			}
		}		
	}
	
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);
#ifdef ETHER_DEBUG
	rtlIntMagic = 0;
#endif
	_RETURN;
}
	
/*******************************************************************************
*
* rtl81x9HandleTxInt - task level interrupt service for tx packets
*
* This routine is called by the interrupt service routine to do any 
* message transmission processing.
*
* RETURNS: N/A.
*/

LOCAL void rtl81x9HandleTxInt
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
	
{
	int 		   txDesc;

	ENTER_FUNC();
	
	for (txDesc=0; txDesc < RTL_NUM_TX_DESC; txDesc++) {
		u_long txstatus;
		
		txstatus = rtl81x9CsrReadLong (pDrvCtrl, 
			RTL_REGS_TX_STATUS0 + (txDesc*4), NONE);
		
		if (txstatus & RTL_TX_STATUS_OK){
			/* Has the packet been sent previously */
			if ((txstatus & RTL_TX_HOST_OWNS) && (pDrvCtrl->pDescMem[txDesc] != NULL)){
				#if 0
				/* Clear the buffer that was registered to the Descriptor */
				/* vicadd */
				netClFree (pDrvCtrl->end.pNetPool, pDrvCtrl->pDescMem[txDesc]);
				#endif
				pDrvCtrl->pDescMem[txDesc] = NULL;
				pDrvCtrl->freeDesc++;
				if (pDrvCtrl->freeDesc > RTL_NUM_TX_DESC)
					pDrvCtrl->freeDesc = RTL_NUM_TX_DESC;
			}
		}else if (txstatus & (RTL_TX_UNDERRUN | RTL_TX_OUT_OF_WINDOW | RTL_TX_ABORTED )){
			/* Clear the buffer that was registered to the Descriptor */
			
			/*vicaddnetClFree (pDrvCtrl->end.pNetPool, pDrvCtrl->pDescMem[txDesc]);*/
			pDrvCtrl->pDescMem[txDesc] = NULL;
			
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_STATUS0 + (txDesc*4), RTL_TX_HOST_OWNS, NONE);
		}
	}
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9HandleRecvInt - task level interrupt service for input packets
*
* This routine is called by the interrupt service routine to do any 
* message received processing.
*
* RETURNS: N/A.
*/

LOCAL void rtl81x9HandleRecvInt
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
{
	int 		len, wrapSize; 
	M_BLK_ID	pMblk;
	char*		pNewCluster;
	CL_BLK_ID	pClBlk;
	RTL_RMD *rxData;
	
	USHORT		cur_rx;
	/*USHORT		limit,max_bytes = 0;*/
	USHORT		 rx_bytes = 0;
	
	char		*readPtr;

	ENTER_FUNC();
	
	/* Disable interrupts by clearing the interrupt mask. */
	cur_rx = ((rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_RX_BUF_PTR, NONE) + 16) % RTL_RXBUFLEN);
	
	/*	
	limit  = (rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_RX_BUF_ADDR, NONE) % RTL_RXBUFLEN);
	if (limit < cur_rx)
		max_bytes = (RTL_RXBUFLEN - cur_rx) + limit;
	else
		max_bytes = limit - cur_rx;
	*/
	while ((rtl81x9CsrReadByte (pDrvCtrl, RTL_REGS_CHIP_CMD, NONE) & RTL_CMD_RX_BUF_EMPTY) == 0){
		/*rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE) ;*//*test*/
		
		readPtr = (pDrvCtrl->ptrRxBufSpace + cur_rx);
		rxData = (RTL_RMD *) readPtr;		
		
		if ((rxData->rxPktLen >> 16) == RTL_RX_UNFINISHED){
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RxHandError 0fff0: ", 1, 2, 3, 4, 5, 6);
			break;
		}
				
		if (!(rxData->rxStatusFlags & RTL_RX_STATUS_OK)) {
			if (rxData->rxStatusFlags & (RTL_RX_BAD_SYMBOL|
				RTL_RX_RUNT|
				RTL_RX_TOO_LONG|
				RTL_RX_CRC_ERROR|
				RTL_RX_BAD_ALIGN)) 
			{
			/*rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);
			rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
				RTL_CMD_RX_ENB, RTL_WIN_0);*/
				rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);
				rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
					RTL_CMD_RX_ENB, RTL_WIN_0);
				
				rtl81x9CsrWriteLong(pDrvCtrl, RTL_REGS_RX_BUF, (ULONG) pDrvCtrl->ptrRxBufSpace, RTL_WIN_0);
				/*rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_RX_BUF_PTR, cur_rx - 16, RTL_WIN_0);*/
				cur_rx = 0;
				/*RTL81X9_LOG (RTL81X9_DEBUG_ALL, "RxHandError:rxData->rxStatusFlags=%x ", rxData->rxStatusFlags, 2, 3, 4, 5, 6);
				i = rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE);
				RTL81X9_LOG (RTL81X9_DEBUG_INT, "ISR %x ", i,0,0,0,0,0);*/
				
				rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, pDrvCtrl->reg_rcr, RTL_WIN_0); 
				
				
			}
			break;
		}
		
		
		/* No errors; receive the packet. */	
		len = rxData->rxPktLen; 	/* get packet length */
		
		/*
		RTL81X9_LOG (
			RTL81X9_DEBUG_RX, 
			"Rmask %x", 
			rtl81x9CsrReadWord(pDrvCtrl, RTL_REGS_INTR_MASK, NONE), 
			0, 0, 0, 0, 0
			); 
		*/
		/*test*/
		
		rx_bytes += len + 4;
		
		len -= RTL_CRC_SIZE;
		
		/*
		* Avoid trying to read more bytes than we know
		* the chip has prepared for us.
		*/
		/* unknow what do */
		/*
		if (rx_bytes > max_bytes){
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "MAX bytes error rx_bytes=%x max_bytes=%x\n", rx_bytes, max_bytes, 0, 0, 0, 0); 		
			break; 
		}
		*/
		
		if(len>1518) {			
			/*
			rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, 
				RTL_WIN_0);
			rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
				RTL_CMD_RX_ENB, RTL_WIN_0);
			*/
			rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);
			rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
				RTL_CMD_RX_ENB, RTL_WIN_0);
			
			rtl81x9CsrWriteLong(pDrvCtrl, RTL_REGS_RX_BUF, (ULONG) pDrvCtrl->ptrRxBufSpace, RTL_WIN_0);
			/*rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_RX_BUF_PTR, cur_rx - 16, RTL_WIN_0);*/
			cur_rx = 0;
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "RxHandError:rxData->rxStatusFlags=%x ", rxData->rxStatusFlags, 2, 3, 4, 5, 6);
			/*i = rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE);*/
			/*RTL81X9_LOG (RTL81X9_DEBUG_INT, "ISR %x ", i,0,0,0,0,0);*/
			
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_RX_CONFIG, pDrvCtrl->reg_rcr, RTL_WIN_0); 
			
			RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "MAX bytes error rx_bytes>1518=%x \n", len, 0, 0, 0, 0, 0); 		
			break;
		}	
			
			
		/*	
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Rx_Bytes=%x len=%x max_byte=%x\n", rx_bytes, len, max_bytes, 4, 5, 6);
		*/
		
		/* If we cannot get a buffer to loan then bail out. */
		pNewCluster = netClusterGet(pDrvCtrl->end.pNetPool, pDrvCtrl->pClPoolId);
		
		/*RTL81X9_LOG (RTL81X9_DEBUG_RX, "Cannot loan cluster!\n", 0, 0, 0, 0, 0, 0);
		END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);*/
		
		if (pNewCluster == NULL){
			RTL81X9_LOG (RTL81X9_DEBUG_RX, "Cannot loan cluster!\n", 0, 0, 0, 0, 0, 0);
			END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);
			goto cleanRXD;
		}
		
		if ((pClBlk = netClBlkGet (pDrvCtrl->end.pNetPool, M_DONTWAIT)) == NULL){
			netClFree (pDrvCtrl->end.pNetPool, pNewCluster);
			RTL81X9_LOG (RTL81X9_DEBUG_RX, "Out of Cluster Blocks!\n", 0, 0, 0, 0, 0, 0);
			END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);
			goto cleanRXD;
		}
		
		/*
		* OK we've got a spare, let's get an M_BLK_ID and marry it to the
		* one in the ring.
		*/
		if ((pMblk = mBlkGet(pDrvCtrl->end.pNetPool, M_DONTWAIT, MT_DATA))== NULL){
			netClBlkFree (pDrvCtrl->end.pNetPool, pClBlk);
			netClFree (pDrvCtrl->end.pNetPool, pNewCluster);
			RTL81X9_LOG (RTL81X9_DEBUG_RX, "Out of M Blocks!\n", 0, 0, 0, 0, 0, 0);
			END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);
			goto cleanRXD;
		}
		
		/* Copy the data found into the new cluster, we have (+4) to get us past the */
		/* data that the rtl chip places at the start of the message and we remove	 */
		/* the CRC from the end of the message	*/
		
		if ((readPtr + len) >= (pDrvCtrl->ptrRxBufSpace + RTL_RXBUFLEN)){
			wrapSize = (int) ((readPtr + len) - (pDrvCtrl->ptrRxBufSpace + RTL_RXBUFLEN));
			
			/* Copy in first section of message as stored */
			/* at the end of the ring buffer			  */
			
			memcpy (pNewCluster, readPtr + 4, len - wrapSize);
			
			/* Copy in end of message as stored */
			/* at the start of the ring buffer	*/
			
			/*vicadd*/
#ifdef	CPU_PENTIUM
			memcpy (pNewCluster +len - wrapSize -4, pDrvCtrl->ptrRxBufSpace, wrapSize+0x04);
			/* there have some error compiler's bug in this line*/
			/* If I just copy the correct bytes the last two bytes will*/
			/* have some trouble, so I copy extra bytes to fix the CPU or*/
			/* OS's bug vic 					*/						
#else
			memcpy (pNewCluster /*+len - wrapSize -4*/, pDrvCtrl->ptrRxBufSpace, wrapSize/*+0x04*/);
#endif
			
			cur_rx = (wrapSize + RTL_CRC_SIZE + 4 + 3) & ~3;
			
			/*
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "wrapsize=%x readptr=%x len=%x pNew=%x newwrapsize %x\n",wrapSize,readPtr,len,pNewCluster,pNewCluster-wrapSize ,6);
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "header=%02x %02x %02x %02x %02x %02x \n",readPtr[4],readPtr[5],readPtr[6],readPtr[7],readPtr[8],readPtr[9]);		
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "newheader=%02x %02x %02x %02x %02x %02x \n",pNewCluster[0],pNewCluster[1],pNewCluster[2],pNewCluster[3],pNewCluster[4],pNewCluster[5]);
			RTL81X9_LOG (RTL81X9_DEBUG_ALL, "len=%02x \n",len,2, 3, 4, 5, 6);
			*/			
		}else{
			memcpy (pNewCluster, readPtr + 4, len);
			cur_rx = (cur_rx + len + RTL_CRC_SIZE + 4 + 3) & ~3;
		}

#ifdef ETHER_DEBUG
		rtlLastPacketLen = len;
		memcpy(rtlLastPacket, pNewCluster, len);
#endif		
		/* Disable interrupts by clearing the interrupt mask. */
		/*vicadd		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);*/
		
		/* We then write the CAPR as the next ptr we will read minus 0x10 which 	*/
		/* give us a little leeway to ensure that there is no overflow				*/
		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_RX_BUF_PTR, (cur_rx - 16), RTL_WIN_0);
		/*RTL81X9_LOG (RTL81X9_DEBUG_ALL, "CAPR=%x len=%d\n",(cur_rx - 16), len, 0, 0, 0, 0);*/
		
		/* Enable interrupts by setting the interrupt mask. */
		/*vicadd		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);*/
		
		/* Join the cluster to the MBlock */
		
		netClBlkJoin (pClBlk, pNewCluster, len, NULL, 0, 0, 0);
		netMblkClJoin (pMblk, pClBlk);
		
		/* make the packet data coherent */
		
		RTL_CACHE_INVALIDATE (pMblk->mBlkHdr.mData, len);
		
		pMblk->mBlkHdr.mLen   = len;
		pMblk->mBlkHdr.mFlags |= M_PKTHDR;
		pMblk->mBlkPktHdr.len = len;
#if 0		
		{
			int i;
			unsigned char * ptr = (unsigned char *)readPtr + 4;
			printf("%d bytes got\n", len);
			for(i=0; i<32; i++, ptr++){
				printf("%02x ", *ptr);
			}
			printf("\n");
		}
#endif		
		/* Call the upper layer's receive routine. */

		RTL81X9_LOG(RTL81X9_DEBUG_RX, "Got data %d bytes, protocol=%04x unit %d\n", len, 
			*((unsigned short*)pNewCluster+6), pDrvCtrl->unit, 0, 0, 0);

		/* */
		if(pDrvCtrl->recvHook && (pDrvCtrl->recvHook(&pDrvCtrl->end, pMblk) == OK)){
			continue;
		}
		
		END_RCV_RTN_CALL (&pDrvCtrl->end, pMblk);
			
	}
	
cleanRXD:
	
	_RETURN;
}
	
	
/*******************************************************************************
*
* rtl81x9Ioctl - interface ioctl procedure
*
* Process an interface ioctl request.
*
* This routine implements the network interface control functions.
* It handles EIOCSADDR, EIOCGADDR, EIOCSFLAGS, EIOCGFLAGS, EIOCMULTIADD,
* EIOCMULTIDRTL, EIOCMULTIGET, EIOCPOLLSTART, EIOCPOLLSTOP, EIOCGMIB2 commands.
*
* RETURNS: OK if successful, otherwise EINVAL.
*/

LOCAL int rtl81x9Ioctl
	(
	RTL81X9END_DEVICE * pDrvCtrl,
	int 	cmd,
	caddr_t data
	)
{
	int error = 0;
	long value;

	ENTER_FUNC();

	/* logMsg("rtl81x9IoCtl(%08x, %s)\n", cmd, data, 0,1,2,3); */
	
	switch (cmd){
	case EIOCSADDR:
		if (data == NULL){
			_RETURN EINVAL;
		}
		bcopy ((char *)data, (char *)END_HADDR(&pDrvCtrl->end), END_HADDR_LEN(&pDrvCtrl->end));
		break;
		
	case EIOCGADDR:
		if (data == NULL){
			_RETURN EINVAL;
		}
		bcopy ((char *)END_HADDR(&pDrvCtrl->end), (char *)data, END_HADDR_LEN(&pDrvCtrl->end));
		break;
		
	case EIOCSFLAGS:
		value = (long)data;
		if (value < 0){
			value = -value;
			value--;		/* HRTLP: WHY ??? */
			END_FLAGS_CLR (&pDrvCtrl->end, value);
		}else{
			END_FLAGS_SET (&pDrvCtrl->end, value);
		}
		rtl81x9Config (pDrvCtrl);
		break;
	case EIOCGFLAGS:
		*(int *)data = END_FLAGS_GET(&pDrvCtrl->end);
		break;
		
	case EIOCPOLLSTART:
		error = rtl81x9PollStart (pDrvCtrl);
		break;
		
	case EIOCPOLLSTOP:
		error = rtl81x9PollStop (pDrvCtrl);
		break;
		
	case EIOCGMIB2:
		if (data == NULL){
			_RETURN EINVAL;
		}
		bcopy((char *)&pDrvCtrl->end.mib2Tbl, (char *)data, sizeof(pDrvCtrl->end.mib2Tbl));
		break;
	case EIOCGFBUF:
		if (data == NULL){
			_RETURN EINVAL;
		}
		*(int *)data = RTL_MIN_FBUF;
		break;
	case EIOCGMWIDTH:
		if (data == NULL){
			_RETURN EINVAL;
		}
		*(int *)data = pDrvCtrl->memWidth;
		break;
	case EIOCGHDRLEN:
		if (data == NULL){
			_RETURN EINVAL;
		}
		*(int *)data = 14;
		break;
	default:
		error = EINVAL;
	}
	_RETURN error;
}

	
/*******************************************************************************
*
* rtl81x9Wait - wait for the command completion
*
* This function waits for the command completion
* It is possible the chip can wedge and the 'command in progress' bit may
* never clear. Hence, we wait only a finite amount of time to avoid getting
* caught in an infinite loop. Normally this delay routine would be a macro,
* but it isn't called during normal operation so we can afford to make it a
* function.
*
* RETURNS: N/A
*/

LOCAL void rtl81x9Wait
	(
	RTL81X9END_DEVICE * 	pDrvCtrl	/* device control structure */
	)
{
	register int	ix;
	
	ENTER_FUNC();
	for (ix = 0; ix < RTL_TIMEOUT; ix++)
	{
		/*if ((rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_CHIP_CMD, NONE) & 0x10) == 0)*/
		if ((rtl81x9CsrReadByte (pDrvCtrl, RTL_REGS_CHIP_CMD, NONE) & 0x10) == 0)
			break;					/*vicadd*/
	}
	
	if (ix == RTL_TIMEOUT)
		RTL81X9_LOG (RTL81X9_DEBUG_ERROR, "rtl81x9Wait - rtlPci%d: command never completed!\n",
		pDrvCtrl->unit, 2, 3, 4, 5, 6);
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9Reset - Reset the chip
*
* This routine does a soft reset on the chip.
*
* RETURNS: OK, Always. 
*/

LOCAL STATUS rtl81x9Reset
	(
	RTL81X9END_DEVICE * pDrvCtrl	/* pointer to device control structure */
	)
{
	ENTER_FUNC();
	/* issue the reset command */
	/*RTL81X9_LOG (RTL81X9_DEBUG_LOAD, " rtl81x9Reset\n",0,0,0,0,0,0);*/
#if 0
	logMsg (" rtl81x9Reset device at %08x\n", pDrvCtrl->devAdrs,0,0,0,0,0);
	/* pcicShow(); */
	logMsg("pcicShow() called.", 0, 0, 0, 0, 0, 0);
#endif
	/*rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_RESET, RTL_WIN_0);*/
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_RESET, RTL_WIN_0);	
	rtl81x9Wait(pDrvCtrl);	/* wait for the command to complete */
	
	/* wait for a while */
	
	SYS_DELAY(10);/*vicadd*/
	_RETURN OK;
}

/*******************************************************************************
*
* rtl81x9LowPowerMode - Enter low power mode
*
*
* RETURNS: N/A
*
* NOMANUAL
*/

void rtl81x9LowPowerMode (RTL81X9END_DEVICE* pDrvCtrl)
{
/*
rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CFG_9346, 0xC0, RTL_WIN_0);
rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CONFIG_1, 0x03, RTL_WIN_0);
	*/
	ENTER_FUNC();
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9NormalPowerMode - Come out of Low power mode
*
*
* RETURNS: N/A
*
* NOMANUAL
*/

/*

  void rtl81x9NormalPowerMode (RTL81X9END_DEVICE* pDrvCtrl)
  {
  	ENTER_FUNC();
	rtl81x9CsrWrite(pDrvCtrl, RTL_REGS_CONFIG_1,	0x00,  RTL_WIN_0);
  }
  
*/

/*******************************************************************************
*
* rtl81x9Stop - stop the device
*
* This routine marks the interface as down and resets the device.  This
* includes disabling interrupts, stopping the transmitter and receiver.
*
* The complement of this routine is rtl81x9Start.  Once a unit is
* stop in this routine, it may be re-initialized to a running state by
* rtl81x9Start.
*
* RETURNS: OK or ERROR
*/

LOCAL STATUS rtl81x9Stop
	(
	RTL81X9END_DEVICE * pDrvCtrl
	)
{
	STATUS result = OK;

	ENTER_FUNC();
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl81x9Stop\n",0,0,0,0,0,0);
	
	/* Disable interrupts by clearing the interrupt mask. */
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);
	
	/* Stop the chip's Tx and Rx DMA processes. */
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_CHIP_CMD, 0x00, NONE);
	
	/* Green! Put the chip in low-power mode. */
	rtl81x9LowPowerMode (pDrvCtrl);
	
	SYS_INT_DISCONNECT (pDrvCtrl, rtl81x9Int, (int)pDrvCtrl, &result);
	
	if (result == ERROR)
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl81x9Stop - Could not disconnect interrupt!\n"
		,0,0,0,0,0,0);
	
	_RETURN result;
}

	
	
/******************************************************************************
*
* rtl81x9AddrFilterSet - set the address filter for multicast addresses
*
* This routine goes through all of the multicast addresses on the list
* of addresses (added with the rtl81x9AddrAdd() routine) and sets the
* device's filter correctly.
*
* NOMANUAL
*/

LOCAL void rtl81x9AddrFilterSet
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
{
	
	ETHER_MULTI*	pCurr;
	rtl_ib* 		pIb;
	u_char* 		pCp;
	u_char			c;
	u_long			crc;
	u_long			carry;
	int 			i, j;
	
	ENTER_FUNC();
	pIb = pDrvCtrl->ib;
	
	RTL_ADDRF_CLEAR (pIb);
	
	pCurr = END_MULTI_LST_FIRST (&pDrvCtrl->end);
	
	while (pCurr != NULL){
		
		pCp = (unsigned char *)&pCurr->addr;
		crc = 0xFFFFFFFF; /* initial value */
		
		for (i = 0; i < 6; i++){
			c = *(pCp + i);
			for (j = 0; j < 8; j++){
				carry = ((crc & 0x80000000) ? 1 : 0) ^ (c & 0x01);
				crc <<= 1;
				c >>= 1;
				if (carry)
					crc = (crc ^ 0x04c11db6) | carry;
			}
		}
		
		/* Just want the 6 most significant bits. */
		
		crc = crc >> 26;
		
		/* Turn on the corresponding bit in the filter. */
		
		RTL_ADDRF_SET (pIb, crc);
		
		pCurr = END_MULTI_LST_NEXT(pCurr);
	}
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9PollReceive - routine to receive a packet in polled mode.
*
* This routine is called by a user to try and get a packet from the
* device.
*/

LOCAL STATUS rtl81x9PollReceive
	(
	RTL81X9END_DEVICE *pDrvCtrl,
	M_BLK_ID pMblk
	)
{
	
	int 		len, wrapSize;
	char*		pNewCluster;
	CL_BLK_ID	pClBlk;
	RTL_RMD *rxData;
	USHORT		cur_rx;
	USHORT		limit;
	USHORT		max_bytes = 0, rx_bytes = 0;
	char		*readPtr;
	
	
	/*_RETURN OK; */ /* test only */
	ENTER_FUNC();
	
	/* RTL81X9_LOG (RTL81X9_DEBUG_ALL, "rtl81x9PollReceive\n",0,0,0,0,0,0);*/
	
	/* Disable interrupts by clearing the interrupt mask. */
	/*	   rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);vicadd*/
	
	cur_rx = ((rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_RX_BUF_PTR, NONE) 
		+ 16) % RTL_RXBUFLEN);
	
	/* Enable interrupts by setting the interrupt mask. */
	/*	  rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);vicadd*/
	
	limit  = (rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_RX_BUF_ADDR, NONE) % RTL_RXBUFLEN);
	
	if (limit < cur_rx)
		max_bytes = (RTL_RXBUFLEN - cur_rx) + limit;
	else
		max_bytes = limit - cur_rx;
	
	while ((rtl81x9CsrReadByte (pDrvCtrl, RTL_REGS_CHIP_CMD, NONE) & RTL_CMD_RX_BUF_EMPTY) == 0){
		readPtr = (pDrvCtrl->ptrRxBufSpace + cur_rx);
		rxData = (RTL_RMD *) readPtr;
					
		if ((rxData->rxPktLen >> 16) == RTL_RX_UNFINISHED)
			break;
		
		if (!(rxData->rxStatusFlags & RTL_RX_STATUS_OK)){
			if (rxData->rxStatusFlags & (RTL_RX_BAD_SYMBOL|
				RTL_RX_RUNT|
				RTL_RX_TOO_LONG|
				RTL_RX_CRC_ERROR|
				RTL_RX_BAD_ALIGN))
			{
				/*rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);*/
				/*rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
				RTL_CMD_RX_ENB, RTL_WIN_0);*/
				
				
				rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);
				rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
					RTL_CMD_RX_ENB, RTL_WIN_0);
				rtl81x9CsrWriteLong(pDrvCtrl, RTL_REGS_RX_BUF, (ULONG) pDrvCtrl->ptrRxBufSpace, RTL_WIN_0);
				rtl81x9CsrWriteWord(pDrvCtrl, RTL_REGS_RX_BUF_PTR, cur_rx - 16, RTL_WIN_0);
				cur_rx = 0;
			}
			break;
		}
		
		
		/* No errors; receive the packet. */	
		len = rxData->rxPktLen; 	/* get packet length */
		
		
		rx_bytes += len + 4;
		
		/*
		*/
		len -= RTL_CRC_SIZE;
		
		/*
		* Avoid trying to read more bytes than we know
		* the chip has prepared for us.
		*/
		if (rx_bytes > max_bytes)
			break;
		
		/* If we cannot get a buffer to loan then bail out. */
		pNewCluster = netClusterGet(pDrvCtrl->end.pNetPool, pDrvCtrl->pClPoolId);
		
		if (pNewCluster == NULL){
			RTL81X9_LOG (RTL81X9_DEBUG_POLL_RX, "Cannot loan cluster!\n", 0, 0, 0, 0, 0, 0);
			END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);
			goto cleanRXD;
		}
		
		if ((pClBlk = netClBlkGet (pDrvCtrl->end.pNetPool, M_DONTWAIT)) == NULL){
			netClFree (pDrvCtrl->end.pNetPool, pNewCluster);
			RTL81X9_LOG (RTL81X9_DEBUG_POLL_RX, "Out of Cluster Blocks!\n", 0, 0, 0, 0, 0, 0);
			END_ERR_ADD (&pDrvCtrl->end, MIB2_IN_ERRS, +1);
			goto cleanRXD;
		}
		
		/* Copy the data found into the new cluster, we have (+4) to get us past the */
		/* data that the rtl chip places at the start of the message and we remove	 */
		/* the CRC from the end of the message	*/
		
		if ((readPtr + len) >= (pDrvCtrl->ptrRxBufSpace + RTL_RXBUFLEN)){
			wrapSize = (int) ((readPtr + len) - (pDrvCtrl->ptrRxBufSpace + RTL_RXBUFLEN));
			
			/* Copy in first section of message as stored */
			/* at the end of the ring buffer			  */
			
			memcpy (pNewCluster, readPtr + 4, len - wrapSize);
			
			/* Copy in end of message as stored */
			/* at the start of the ring buffer	*/
			/* haha, big big bug! jhut 2005-10-12 */
			/* memcpy (pNewCluster, pDrvCtrl->ptrRxBufSpace, wrapSize); */
			memcpy (pNewCluster + len - wrapSize, pDrvCtrl->ptrRxBufSpace, wrapSize);
			cur_rx = (wrapSize + RTL_CRC_SIZE + 4 + 3) & ~3;
		}else{
			memcpy (pNewCluster, readPtr + 4, len);
			cur_rx = (cur_rx + len + RTL_CRC_SIZE + 4 + 3) & ~3;
		}
		
		/* Disable interrupts by clearing the interrupt mask. */
		/*vicadd		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);*/
		
		
		/* We then write the CAPR as the next ptr we will read minus 0x10 which 	*/
		/* give us a little leeway to ensure that there is no overflow				*/
		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_RX_BUF_PTR, (cur_rx - 16), RTL_WIN_0);
		
		/*RV_LOG (RTL81X9_DEBUG_ALL,"Capr=%X\n",(cur_rx - 16) , 0, 0, 0, 0, 0);*/
		
		/* Enable interrupts by setting the interrupt mask. */
		/*		rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);vicadd*/
		
		/* Join the cluster to the MBlock */
		
		netClBlkJoin (pClBlk, pNewCluster, len, NULL, 0, 0, 0);
		netMblkClJoin (pMblk, pClBlk);
		
		/* make the packet data coherent */
		
		RTL_CACHE_INVALIDATE (pMblk->mBlkHdr.mData, len);
		
		pMblk->mBlkHdr.mLen   = len;
		pMblk->mBlkHdr.mFlags |= M_PKTHDR;
		pMblk->mBlkPktHdr.len = len;
		
		/* Call the upper layer's receive routine. */
		
		END_RCV_RTN_CALL (&pDrvCtrl->end, pMblk);
		
		_RETURN OK;
	}
	
cleanRXD:
	_RETURN ERROR;
	
	
}


/*******************************************************************************
*
* rtl81x9ReceiveDirect - routine to receive a packet in polled mode.
*
* This routine is called by a user to try and get a packet from the
* device.
*/
int rtl81x9ReceiveDirect(RTL81X9END_DEVICE * d, char * buf, int len, int milliseconds)
{
	int retry;
	int wrapSize;
	RTL_RMD *rxData;
	USHORT		cur_rx;
	USHORT		limit;
	USHORT		max_bytes = 0, rx_bytes = 0;
	char		*readPtr;
	int t2;
	u_short stat;
	int microseconds=milliseconds*1000;

	
	/* In case of an RxFIFOOver we must also clear the RxOverflow
   bit to avoid dropping frames for ever.
	*/
	stat = rtl81x9CsrReadWord (d, RTL_REGS_INTR_STATUS, 0);
	if(stat){
		rtl81x9CsrWriteWord (d, RTL_REGS_INTR_STATUS, 
			(stat & RTL_IPT_RX_FIFO_OVER)? stat | RTL_IPT_RX_OVERFLOW : stat, NONE);
	}
	cur_rx = ((rtl81x9CsrReadWord  (d, RTL_REGS_RX_BUF_PTR, NONE) + 16) % RTL_RXBUFLEN);
		
	t2 = microseconds/10;
	retry = 0;
	while ((rtl81x9CsrReadByte (d, RTL_REGS_CHIP_CMD, NONE) & RTL_CMD_RX_BUF_EMPTY) == 1 && retry<10){
		sysStallExecutionProcessor(t2);
		retry++;
	}
	
	if((rtl81x9CsrReadByte (d, RTL_REGS_CHIP_CMD, NONE) & RTL_CMD_RX_BUF_EMPTY) == 1){
		return -1;
	}
	
	limit  = (rtl81x9CsrReadWord  (d, RTL_REGS_RX_BUF_ADDR, NONE) % RTL_RXBUFLEN);
	
	if (limit < cur_rx)
		max_bytes = (RTL_RXBUFLEN - cur_rx) + limit;
	else
		max_bytes = limit - cur_rx;
	
	readPtr = (d->ptrRxBufSpace + cur_rx);
	rxData = (RTL_RMD *) readPtr;
				
	if ((rxData->rxPktLen >> 16) == RTL_RX_UNFINISHED){
		return -2;
	}
		
	if (!(rxData->rxStatusFlags & RTL_RX_STATUS_OK)){
		if (rxData->rxStatusFlags & (RTL_RX_BAD_SYMBOL|
			RTL_RX_RUNT|
			RTL_RX_TOO_LONG|
			RTL_RX_CRC_ERROR|
			RTL_RX_BAD_ALIGN))
		{
			rtl81x9CsrWriteByte(d, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB, RTL_WIN_0);
			rtl81x9CsrWriteByte(d, RTL_REGS_CHIP_CMD, RTL_CMD_TX_ENB|
				RTL_CMD_RX_ENB, RTL_WIN_0);
			rtl81x9CsrWriteLong(d, RTL_REGS_RX_BUF, (ULONG) d->ptrRxBufSpace, RTL_WIN_0);
			rtl81x9CsrWriteWord (d, RTL_REGS_RX_BUF_PTR, cur_rx - 16, RTL_WIN_0);
			cur_rx = 0;
		}
		return -3;
	}
		
		
	/* No errors; receive the packet. */

	/* get packet length */
	if(rxData->rxPktLen < len){
		len = rxData->rxPktLen;
	}else if(rxData->rxPktLen > len){
		/* buffer too small */
		return -4;
	}
	
	rx_bytes += len + 4;
	
	/*
	*/
	len -= RTL_CRC_SIZE;
	
	/*
	* Avoid trying to read more bytes than we know
	* the chip has prepared for us.
	*/
	if (rx_bytes > max_bytes){
		/*??? the chip cheats us? */
#if 0
#define _(x) printf(#x "=%08x\n", x)
		_(rx_bytes);
		_(max_bytes);
		_(rxData->rxPktLen);
		_(len);
		_(cur_rx);
		_(limit);
		return -5;
#endif
	}
		
	/* Copy the data found into the new cluster, we have (+4) to get us past the */
	/* data that the rtl chip places at the start of the message and we remove	 */
	/* the CRC from the end of the message	*/
	
	if ((readPtr + len) >= (d->ptrRxBufSpace + RTL_RXBUFLEN)){
		wrapSize = (int) ((readPtr + len) - (d->ptrRxBufSpace + RTL_RXBUFLEN));
		
		/* Copy in first section of message as stored */
		/* at the end of the ring buffer			  */
		
		memcpy (buf, readPtr + 4, len - wrapSize);
		
		/* Copy in end of message as stored */
		/* at the start of the ring buffer	*/
		
		/* memcpy (buf+len - wrapSize, d->ptrRxBufSpace, wrapSize); */
		memcpy (buf+len - wrapSize -4, d->ptrRxBufSpace, wrapSize+0x04);
		cur_rx = (wrapSize + RTL_CRC_SIZE + 4 + 3) & ~3;
	}else{
		memcpy (buf, readPtr + 4, len);
		cur_rx = (cur_rx + len + RTL_CRC_SIZE + 4 + 3) & ~3;
	}
		
	/* We then write the CAPR as the next ptr we will read minus 0x10 which 	*/
	/* give us a little leeway to ensure that there is no overflow				*/
	rtl81x9CsrWriteWord  (d, RTL_REGS_RX_BUF_PTR, (cur_rx - 16), RTL_WIN_0);
	
	return len;	
}

/*******************************************************************************
*
* rtl81x9PollSend - routine to send a packet in polled mode.
*
* This routine is called by a user to try and send a packet on the
* device.
*/

LOCAL STATUS rtl81x9PollSend
	(
	RTL81X9END_DEVICE* pDrvCtrl,
	M_BLK_ID pMblk
	)
{
	/*int		   txDesc;*/
	int level = 0;
	int 		len = 0;
	char*		pBuf;
	ULONG		tx_val;
	u_short 	   stat;
	
	
	ENTER_FUNC();
	RTL81X9_LOG (RTL81X9_DEBUG_FUNCLOG, "rtl81x9PollSend\n",0,0,0,0,0,0);
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		level = intLock ();   /* now templateInt won't get confused vic test */
	
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_STATUS, 0xffff, NONE);
	
	/* find Tx Descriptor */
	if (pDrvCtrl->freeDesc != 0){
		if (pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] == NULL){
			pBuf = (pDrvCtrl->txmemspace + (pDrvCtrl->nextDesc * RTL81x9_BUFSIZE));
			pBuf += pDrvCtrl->offset;	/* take care of the alignment */
			
			
			len = netMblkToBufCopy (pMblk, pBuf, NULL);
			
			netMblkClChainFree(pMblk);
			len = max (len, ETHERSMALL);
			
			tx_val = len + (3 << 16);
			
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_ADDR0 + (pDrvCtrl->nextDesc * 4), (int) pBuf, RTL_WIN_0); 
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_STATUS0 + (pDrvCtrl->nextDesc * 4), tx_val, RTL_WIN_0);
			
			/*RTL81X9_LOG (RTL81X9_DEBUG_ALL, "No=%x txstatus=%x\n", pDrvCtrl->nextDesc, tx_val, 0, 0, 0, 0);	*/
			
			stat = rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE);
			while(!(stat & 0x04)){
				stat = rtl81x9CsrReadWord (pDrvCtrl, RTL_REGS_INTR_STATUS, NONE);
			}	
			
			/*pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] = pBuf;*/
			
			/*netClFree (pDrvCtrl->end.pNetPool, pDrvCtrl->pDescMem[pDrvCtrl->nextDesc]);*/
			
			pDrvCtrl->nextDesc++;
			if (pDrvCtrl->nextDesc == 4)
				pDrvCtrl->nextDesc = 0;
				/*if (pDrvCtrl->freeDesc != 0)
			pDrvCtrl->freeDesc--;*/
		}else{
			RTL81X9_LOG (RTL81X9_DEBUG_TX, "Next Desc %d is not free yet\n", pDrvCtrl->nextDesc, 0, 0, 0, 0, 0);
			netMblkClChainFree(pMblk);
			_RETURN ERROR;
		}
	}else{
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "No free Descriptors\n", 0, 0, 0, 0, 0, 0);
		netMblkClChainFree(pMblk);
		_RETURN ERROR;
	}
	
	/* Flush the write pipe */
	
	CACHE_PIPE_FLUSH ();
	
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		END_TX_SEM_GIVE (&pDrvCtrl->end);
	
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		intUnlock (level);	 /* now templateInt won't get confused victest */
	
	
	/*rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);*/
	
	_RETURN OK;
}

/*****************************************************************************
*
* rtl81x9MCastAddrAdd - add a multicast address for the device
*
* This routine adds a multicast address to whatever the driver
* is already listening for.  It then resets the address filter.
*/

LOCAL STATUS rtl81x9MCastAddrAdd
	(
	RTL81X9END_DEVICE *pDrvCtrl,
	char* pAddress
	)
{
	
	int error;
	ENTER_FUNC();
	if ((error = etherMultiAdd (&pDrvCtrl->end.multiList, pAddress)) == ENETRESET)
		rtl81x9Config (pDrvCtrl);
	
	_RETURN OK;
}

/*****************************************************************************
*
* rtl81x9MCastAddrDel - delete a multicast address for the device
*
* This routine removes a multicast address from whatever the driver
* is listening for.  It then resets the address filter.
*/

LOCAL STATUS rtl81x9MCastAddrDel
	(
	RTL81X9END_DEVICE* pDrvCtrl,
	char* pAddress
	)
{
	
	int error;
	
	if ((error = etherMultiDel (&pDrvCtrl->end.multiList, (char *)pAddress)) == ENETRESET)
		rtl81x9Config (pDrvCtrl);
	
	_RETURN OK;
}

/*****************************************************************************
*
* rtl81x9MCastAddrGet - get the multicast address list for the device
*
* This routine gets the multicast list of whatever the driver
* is already listening for.
*/
LOCAL STATUS rtl81x9MCastAddrGet
	(
	RTL81X9END_DEVICE* pDrvCtrl,
	MULTI_TABLE* pTable
	)
{
	
	int error;
	ENTER_FUNC();
	error = etherMultiGet (&pDrvCtrl->end.multiList, pTable);
	
	_RETURN error;
}

STATUS rtl81x9SendDirect(RTL81X9END_DEVICE * pDrvCtrl, void * buf, int len)
{
	char * pBuf;
	ULONG		tx_val;
	STATUS		status = OK;
	u_long txstatus;
	int 		   txDesc;
	unsigned int tsad;

	ENTER_FUNC();
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		END_TX_SEM_TAKE (&pDrvCtrl->end, WAIT_FOREVER);
	
	
	/* find Tx Descriptor *//*vicedit */
	if(pDrvCtrl->freeDesc == 0){	/*1*/
		int cnt;
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "No free Descriptors0\n", 0, 0, 0,0, 0, 0);
		
		cnt=2;
		/*cnt = sysClkRateGet ();*/
		do{
			taskDelay (1);
			tsad = rtl81x9CsrReadWord (pDrvCtrl,RTL_REGS_TX_SUMMARY, NONE);
		} while ((tsad & 0xf000)==0 && (cnt-->0))	;
		
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "tsad=%x\n", tsad, 0, 0,0, 0, 0);
		
		for (txDesc=0; txDesc < RTL_NUM_TX_DESC; txDesc++) {		/*2*/
			txstatus = rtl81x9CsrReadLong (pDrvCtrl, RTL_REGS_TX_STATUS0 + (txDesc*4), NONE);
			
			if (txstatus & RTL_TX_STATUS_OK){		/*3*/
				/* Has the packet been sent previously */
				if ((txstatus & RTL_TX_HOST_OWNS) && (pDrvCtrl->pDescMem[txDesc] != NULL)){	/*4*/
					#if 0
					RTL81X9_LOG (RTL81X9_DEBUG_TX, "new buffer free\n", 0, 0, 0,0, 0, 0);
					/* Clear the buffer that was registered to the Descriptor */
					netClFree (pDrvCtrl->end.pNetPool, pDrvCtrl->pDescMem[txDesc]);
					RTL81X9_LOG (RTL81X9_DEBUG_TX, "net free\n", 0, 0, 0,0, 0, 0);
					#endif
					pDrvCtrl->pDescMem[txDesc] = NULL;
					pDrvCtrl->freeDesc++;
					if (pDrvCtrl->freeDesc > RTL_NUM_TX_DESC)
						pDrvCtrl->freeDesc = RTL_NUM_TX_DESC;
				}	/*4*/
				
			}		/*3*/
		}		/*2*/
	}			/*1*/
	
	
	if (pDrvCtrl->freeDesc != 0){
		if (pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] ==NULL) {
			pBuf = (pDrvCtrl->txmemspace + (pDrvCtrl->nextDesc * RTL81x9_BUFSIZE));
			pBuf += pDrvCtrl->offset; /* take care of the alignment */
			
			memcpy(pBuf, buf, len);

#ifdef ETHER_DEBUG
			rtlLastPacketLenSent = len;
			memcpy(rtlLastPacketSent, pBuf, len);
			RTL81X9_LOG (RTL81X9_DEBUG_TX, "send throuth RTL %d %d bytes, protocol %04x\n", 
				pDrvCtrl->unit, len, *((unsigned short*)pBuf + 6), 0, 0, 0); 
#endif
			len = max (len, ETHERSMALL);
			
			tx_val = len + (3 << 16);
			
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_ADDR0
				+ (pDrvCtrl->nextDesc * 4), (int) pBuf, RTL_WIN_0); 
			rtl81x9CsrWriteLong (pDrvCtrl,
				RTL_REGS_TX_STATUS0 + (pDrvCtrl->nextDesc * 4), tx_val, RTL_WIN_0);
			
			pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] = pBuf;
			pDrvCtrl->nextDesc++;
			if (pDrvCtrl->nextDesc == 4)
				pDrvCtrl->nextDesc = 0;
			if (pDrvCtrl->freeDesc != 0)
				pDrvCtrl->freeDesc--;
		}else {
			RTL81X9_LOG (RTL81X9_DEBUG_TX, "Next Desc %d is not free yet\n", pDrvCtrl->nextDesc, 0, 0, 0, 0, 0);
			status = ERROR;
			goto rtl81x9SendERROR;
		}
	}else	{
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "No free Descriptors\n", 0, 0, 0,
			0, 0, 0);
		status = ERROR;
		goto rtl81x9SendERROR;
	}
	
	/* Flush the write pipe */
	
	CACHE_PIPE_FLUSH ();
	
rtl81x9SendERROR:
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		END_TX_SEM_GIVE (&pDrvCtrl->end);
		
	_RETURN OK;
}

/***********************************************************************
********
*
* rtl81x9Send - the driver send routine
*
* This routine takes a M_BLK_ID sends off the data in the M_BLK_ID.
* The buffer must already have the addressing information properly
installed
* in it.  This is done by a higher layer.  
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS rtl81x9Send
	(
	RTL81X9END_DEVICE	*pDrvCtrl, /* device ptr */
	M_BLK_ID	pMblk 			   /* data to send */
	 )
{
	int 		len = 0;
	char*		pBuf;
	ULONG			  tx_val;
	STATUS		status = OK;
	u_long txstatus;
	int 		   txDesc;
	unsigned int tsad;

	ENTER_FUNC();
	#if 0
	/* debug purpose, jht 2005-9-6 */
	netMblkClChainFree(pMblk);
	_RETURN status;
	#endif
	/*
	* Obtain exclusive access to transmitter.  This is necessary because
	* we might have more than one stack transmitting at once.
	*/
	/* jht 2005-9-8 removed this stupid line, that's totally unnecessary 
	because masking interrupts from 8139 won't guarantee that current
	task won't be blocked, that's another story.
	in fact, masking interrupts here can lead to severe problem when
	network load is high, as my tests reveals, the 8100 card will enter
	a deadlocking mode, no interrupts will be triggered.
	*/
#if 0
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);
#endif 

	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		END_TX_SEM_TAKE (&pDrvCtrl->end, WAIT_FOREVER);
	
	
	/* find Tx Descriptor *//*vicedit */
	if(pDrvCtrl->freeDesc == 0){	/*1*/
		int cnt;
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "No free Descriptors0\n", 0, 0, 0,0, 0, 0);
		
		cnt=10;
		/*cnt = sysClkRateGet ();*/
		do{
			taskDelay (1);
			tsad = rtl81x9CsrReadWord (pDrvCtrl,RTL_REGS_TX_SUMMARY, NONE);
		} while ((tsad & 0xf000)==0 && (cnt-->0))	;
		
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "tsad=%x\n", tsad, 0, 0,0, 0, 0);
		
		for (txDesc=0; txDesc < RTL_NUM_TX_DESC; txDesc++) {		/*2*/
			txstatus = rtl81x9CsrReadLong (pDrvCtrl, RTL_REGS_TX_STATUS0 + (txDesc*4), NONE);
			
			if (txstatus & RTL_TX_STATUS_OK){		/*3*/
				/* Has the packet been sent previously */
				if ((txstatus & RTL_TX_HOST_OWNS) && (pDrvCtrl->pDescMem[txDesc] != NULL)){	/*4*/
					#if 0
					RTL81X9_LOG (RTL81X9_DEBUG_TX, "new buffer free\n", 0, 0, 0,0, 0, 0);
					/* Clear the buffer that was registered to the Descriptor */
					netClFree (pDrvCtrl->end.pNetPool, pDrvCtrl->pDescMem[txDesc]);
					RTL81X9_LOG (RTL81X9_DEBUG_TX, "net free\n", 0, 0, 0,0, 0, 0);
					#endif
					pDrvCtrl->pDescMem[txDesc] = NULL;
					pDrvCtrl->freeDesc++;
					if (pDrvCtrl->freeDesc > RTL_NUM_TX_DESC)
						pDrvCtrl->freeDesc = RTL_NUM_TX_DESC;
				}	/*4*/
				
			}		/*3*/
		}		/*2*/
	}			/*1*/
	
	
	if (pDrvCtrl->freeDesc != 0){
		if (pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] ==NULL) {
			pBuf = (pDrvCtrl->txmemspace + (pDrvCtrl->nextDesc * RTL81x9_BUFSIZE));
			pBuf += pDrvCtrl->offset; /* take care of the alignment */
			
			len = netMblkToBufCopy (pMblk, pBuf, NULL);
			
			netMblkClChainFree(pMblk);
#ifdef ETHER_DEBUG
			rtlLastPacketLenSent = len;
			memcpy(rtlLastPacketSent, pBuf, len);
			RTL81X9_LOG (RTL81X9_DEBUG_TX, "send throuth RTL %d %d bytes, protocol %04x\n", 
				pDrvCtrl->unit, len, *((unsigned short*)pBuf + 6), 0, 0, 0); 
#endif
			len = max (len, ETHERSMALL);
			
			tx_val = len + (3 << 16);
			
			rtl81x9CsrWriteLong (pDrvCtrl, RTL_REGS_TX_ADDR0
				+ (pDrvCtrl->nextDesc * 4), (int) pBuf, RTL_WIN_0); 
			rtl81x9CsrWriteLong (pDrvCtrl,
				RTL_REGS_TX_STATUS0 + (pDrvCtrl->nextDesc * 4), tx_val, RTL_WIN_0);
			
			pDrvCtrl->pDescMem[pDrvCtrl->nextDesc] = pBuf;
			pDrvCtrl->nextDesc++;
			if (pDrvCtrl->nextDesc == 4)
				pDrvCtrl->nextDesc = 0;
			if (pDrvCtrl->freeDesc != 0)
				pDrvCtrl->freeDesc--;
		}else {
			RTL81X9_LOG (RTL81X9_DEBUG_TX, "Next Desc %d is not free yet\n", pDrvCtrl->nextDesc, 0, 0, 0, 0, 0);
			netMblkClChainFree(pMblk);
			status = ERROR;
			goto rtl81x9SendERROR;
		}
	}else	{
		RTL81X9_LOG (RTL81X9_DEBUG_TX, "No free Descriptors\n", 0, 0, 0,
			0, 0, 0);
		netMblkClChainFree(pMblk);
		status = ERROR;
		goto rtl81x9SendERROR;
	}
	
	/* Flush the write pipe */
	
	CACHE_PIPE_FLUSH ();
	
rtl81x9SendERROR:
	
	if (!(pDrvCtrl->flags & RTL_FLG_POLLING))
		END_TX_SEM_GIVE (&pDrvCtrl->end);
#if 0
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK,RTL_VALID_INTERRUPTS, NONE);
#endif

	_RETURN OK;
	
}  

/*******************************************************************************
*
* rtl81x9RestartSetup - setup memory descriptors and turn on chip
*
* Initializes all the shared memory structures and turns on the chip.
*/

LOCAL STATUS rtl81x9RestartSetup
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
{
	int 	rsize;
	void *	pTemp;
	
	/* reset the device */
	ENTER_FUNC();
	
	rtl81x9Reset (pDrvCtrl);
	
	/* setup Rx buffer descriptors	- align on 000 boundary */
	
	rsize = pDrvCtrl->rringLen;
	pDrvCtrl->pRring = (RTL_RMD *) ( ( (int)pDrvCtrl->pRring + 7) & ~7);	
	
	/* setup the initialization block */
	
	pDrvCtrl->ib = (rtl_ib *)pDrvCtrl->pShMem;
	
	/* HRTLP */
	swab ((char *) END_HADDR(&pDrvCtrl->end), pDrvCtrl->ib->rtlIBPadr, 6);
	
	CACHE_PIPE_FLUSH ();
	
	pTemp = RTL_CACHE_VIRT_TO_PHYS (pDrvCtrl->pRring);	 /* point to Rx ring */
	RTL_ADDR_TO_IB_RMD (pTemp, pDrvCtrl->ib, rsize);
	
	/* reconfigure the device */
	
	rtl81x9Config (pDrvCtrl);
	
	_RETURN OK; 
}
	
/*******************************************************************************
*
* rtl81x9Restart - restart the device after a fatal error
*
* This routine takes care of all the messy details of a restart.  The device
* is reset and re-initialized.	The driver state is re-synchronized.
*/

LOCAL void rtl81x9Restart
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
{
	ENTER_FUNC();
	rtl81x9Reset (pDrvCtrl);
	
	rtl81x9RestartSetup (pDrvCtrl);
	
	/* set the flags to indicate readiness */
	
	END_OBJ_READY (&pDrvCtrl->end,
		IFF_UP | IFF_RUNNING | IFF_NOTRAILERS | IFF_BROADCAST
		| IFF_MULTICAST);
	_RETURN;
}

	
/******************************************************************************
*
* rtl81x9Config - reconfigure the interface under us.
*
* Reconfigure the interface setting promiscuous mode, and changing the
* multicast interface list.
*
* NOMANUAL
*/

LOCAL void rtl81x9Config
	(
	RTL81X9END_DEVICE *pDrvCtrl
	)
{
	ENTER_FUNC();
	/* Set promiscuous mode if it's asked for. */
	
	if (END_FLAGS_GET(&pDrvCtrl->end) & IFF_PROMISC)	{
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Setting promiscuous mode on!\n", 0, 0, 0, 0, 0, 0);
		
		/* chip will be in promiscuous mode */
		
		pDrvCtrl->ib->rtlIBMode = 0x8000;
	}else{
		
		/*vicadd RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "Setting promiscuous mode off!\n", 0, 0, 0, 0, 0, 0);*/
		pDrvCtrl->ib->rtlIBMode = 0;
		
	}
	
	CACHE_PIPE_FLUSH ();
	
	/* Set up address filter for multicasting. */
	
	if (END_MULTI_LST_CNT(&pDrvCtrl->end) > 0){
		rtl81x9AddrFilterSet (pDrvCtrl);
	}
	_RETURN;
	
}

/*******************************************************************************
*
* rtl81x9Unload - unload a driver from the system
*
* This routine deallocates lists, and free allocated memory.
*
* RETURNS: OK, always.
*/

LOCAL STATUS rtl81x9Unload
	(
	RTL81X9END_DEVICE * pDrvCtrl
	)
{
	ENTER_FUNC();
	END_OBJECT_UNLOAD (&pDrvCtrl->end);
	
	/* Free the shared DMA memory. */
	if (pDrvCtrl->flags & RTL_FLG_MEM_ALLOC_FLAG)
		cacheDmaFree (pDrvCtrl->pShMem);
	
	_RETURN OK;
}

/*******************************************************************************
*
* rtl81x9PollStart - start polled mode operations
*
* This function starts polled mode operation.
*
* The device interrupts are disabled, the current mode flag is switched
* to indicate Polled mode and the device is reconfigured.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS rtl81x9PollStart
	(
	RTL81X9END_DEVICE * pDrvCtrl	/* device to be polled */
	)
{
	int 		oldLevel;
	ENTER_FUNC();
	oldLevel = intLock ();			/* disable ints during update */
	
	/* RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "pollstart", 1, 2, 3, 4, 5, 6);*/
	
	/* Turn off interrupts */
	
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, 0x00, NONE);
	
	pDrvCtrl->flags |= RTL_FLG_POLLING;
	
	intUnlock (oldLevel);	/* now rtl81x9Int won't get confused */
	
	/* RTL81X9_LOG (RTL81X9_DEBUG_POLL, "STARTED\n", 1, 2, 3, 4, 5, 6); */
	/*rtl81x9Config (pDrvCtrl);test only*/	/* reconfigure device */
	
	_RETURN OK;
}
	
/*******************************************************************************
*
* rtl81x9PollStop - stop polled mode operations
*
* This function terminates polled mode operation.  The device returns to
* interrupt mode.
*
* The device interrupts are enabled, the current mode flag is switched
* to indicate interrupt mode and the device is then reconfigured for
* interrupt operation.
*
* RETURNS: OK or ERROR.
*/

LOCAL STATUS rtl81x9PollStop
	(
	RTL81X9END_DEVICE * pDrvCtrl	/* device structure */
	)
{
	
	int 		oldLevel;
	ENTER_FUNC();
	oldLevel = intLock ();			/* disable ints during update */
	
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_INTR_MASK, RTL_VALID_INTERRUPTS, NONE);
	
	pDrvCtrl->flags &= ~RTL_FLG_POLLING;
	
	intUnlock (oldLevel);	/* now rtl81x981x9Int won't get confused */
	
	
	rtl81x9Config (pDrvCtrl);	/* reconfigure device */
	RTL81X9_LOG (RTL81X9_DEBUG_POLL, "STOPPED\n", 1, 2, 3, 4, 5, 6);	
	
	_RETURN OK;
}



/*******************************************************************************
*
* rtl81x9CsrReadByte - read a byte from a given window and register
*
* This function reads a byte from a given window and register
*
* RETURNS: UCHAR
*/

LOCAL UCHAR rtl81x9CsrReadByte
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	int 		window		/* window number */
	)
{
	UCHAR		inWord;
	int 		level;

	/* disable all controller interrupts to prevent race conditions */
	level = intLock ();
	/* set the register */
	SYS_IN_BYTE (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32)reg), inWord);
	
	/* reenable controller interrupts */
	intUnlock (level);
	
	_return inWord;
}

/*******************************************************************************
*
* rtl81x9CsrReadWord - read a word from a given window and register
*
* This function reads a word from a given window and register
*
* RETURNS: USHORT
*/

LOCAL USHORT rtl81x9CsrReadWord
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	int 		window		/* window number */
	)
{
	USHORT		inWord;
	int 		level;

	/* disable all controller interrupts to prevent race conditions */
	level = intLock ();
	/* set the register */
	SYS_IN_SHORT (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32)reg), inWord);
	
	/* reenable controller interrupts */
	intUnlock (level);
	
	_return inWord;
}

/*******************************************************************************
*
* rtl81x9CsrReadLong - read a long from a given window and register
*
* This function reads a long from a given window and register
*
* RETURNS: USHORT
*/

LOCAL ULONG rtl81x9CsrReadLong
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	int 		window		/* window number */
	)
{
	ULONG		inWord;
	int 		level;

	/* disable all controller interrupts to prevent race conditions */
	level = intLock ();
	/* set the register */
	SYS_IN_LONG (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32)reg), inWord);
	
	/* reenable controller interrupts */
	intUnlock (level);
	
	_return inWord;
}

/*******************************************************************************
*
* rtl81x9CsrWriteByte - write a byte to a given window and register
*
* This function writes a byte to a given window and register
*
* RETURNS: N/A
*/

LOCAL void rtl81x9CsrWriteByte
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	UCHAR		outByte,	/* byte to be written */
	int 		window		/* window number */
	)
{
	int 		level;

	level = intLock ();
	
	/* set the register */
	SYS_OUT_BYTE (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32)reg), outByte);
	
	/* reenable interrupts */
	intUnlock (level);
	_return;
}

/*******************************************************************************
*
* rtl81x9CsrWriteWord - write a word to a given window and register
*
* This function writes a word to a given window and register
*
* RETURNS: N/A
*/

LOCAL void rtl81x9CsrWriteWord
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	USHORT		outWord,	/* word to be written */
	int 		window		/* window number */
	)
	
{
	int 		level;
	
	/* disable interrupts to prevent race conditions */
	
	level = intLock ();
	
	/* set the register */
	SYS_OUT_SHORT (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32)reg), outWord);
	
	/* reenable interrupts */
	
	intUnlock (level);
	_return;
}


/*******************************************************************************
*
* rtl81x9CsrWriteLong - write a long to a given window and register
*
* This function writes a long to a given window and register
*
* RETURNS: N/A
*/

LOCAL void rtl81x9CsrWriteLong
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	USHORT		reg,		/* register offset */
	ULONG		outLong,	/* long word to be written */
	int 		window		/* window number */
	)
{
	int 		level;
	
	/* disable interrupts to prevent race conditions */
	level = intLock ();
	
	/* set the register */
	SYS_OUT_LONG (pDrvCtrl, (pDrvCtrl->devAdrs + (UINT32) reg), outLong);
	
	/* reenable interrupts */
	intUnlock (level);
	
	_return;
}

/*******************************************************************************
*
* rtl81x9ReadEEPROM - read a value from the EEPROM
*
* This function reads a sequence of words from the EEPROM at the address passed in the params
*
* RETURNS: N/A
*/

LOCAL void rtl81x9ReadEEPROM
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	UCHAR					*dest,
	ULONG					off,
	ULONG					cnt,
	ULONG					swap
	)
	
{
	int 		i;
	USHORT		word = 0, *ptr;

	ENTER_FUNC();
	for (i = 0; i < cnt; i++)	{
		rtl81x9EEPROMGetWord(pDrvCtrl, off + i, &word);
		ptr = (USHORT *)(dest + (i * 2));
		if (swap)
			*ptr = ntohs(word);
		else
			*ptr = word;
	}
	
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9EEPROMGetWord - read a value from the EEPROM
*
* Read a word of data stored in the EEPROM at address 'addr.'
*
* RETURNS: N/A
*/

LOCAL void rtl81x9EEPROMGetWord
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	ULONG					addr,
	USHORT					*dest
	)
	
{
	register int		i;
	USHORT				word = 0;

	ENTER_FUNC();
	/* Enter EEPROM access mode. */
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_CFG_9346, RTL_EEMODE_PROGRAM|RTL_EE_SEL, RTL_WIN_0);
	
	/*
	* Send address of word we want to read.
	*/
	rtl81x9EEPROMPutByte (pDrvCtrl, addr);
	
	rtl81x9CsrWriteByte (pDrvCtrl, RTL_REGS_CFG_9346, RTL_EEMODE_PROGRAM|RTL_EE_SEL, RTL_WIN_0);
	
	/*
	* Start reading bits from EEPROM.
	*/
	for (i = 0x8000; i; i >>= 1) {
		EE_SET(RTL_EE_CLK);
		SYS_DELAY(100);
		if (rtl81x9CsrReadByte (pDrvCtrl, RTL_REGS_CFG_9346, RTL_WIN_0) & RTL_EE_DATAOUT)
			word |= i;
		EE_CLR(RTL_EE_CLK);
		SYS_DELAY(100);
	}
	
	/* Turn off EEPROM access mode. */
	rtl81x9CsrWriteByte(pDrvCtrl, RTL_REGS_CFG_9346, RTL_EEMODE_OFF, RTL_WIN_0);
	
	*dest = word;
	
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9EEPROMPutByte - read a value from the EEPROM
*
* Send a read command and address to the EEPROM, check for ACK
*
* RETURNS: N/A
*/

LOCAL void rtl81x9EEPROMPutByte
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	ULONG					addr
	)
	
{
	register int		d, i;

	ENTER_FUNC();
	d = addr | RTL_EECMD_READ;
	
	/*
	* Feed in each bit and stobe the clock.
	*/
	for (i = 0x400; i; i >>= 1) {
		if (d & i) {
			EE_SET(RTL_EE_DATAIN);
		} else {
			EE_CLR(RTL_EE_DATAIN);
		}
		SYS_DELAY(100);
		EE_SET(RTL_EE_CLK);
		SYS_DELAY(150);
		EE_CLR(RTL_EE_CLK);
		SYS_DELAY(100);
	}
	
	_RETURN;
}

/*******************************************************************************
*
* rtl81x9MII_sync - Sync the PHY's
*
* Sync the PHYs by setting data bit and strobing the clock 32 times.
*
* RETURNS: N/A
*/

LOCAL void rtl81x9MII_sync
	(
	RTL81X9END_DEVICE * 	pDrvCtrl	/* device control structure */
	)
	
{
	register int		i;
	ENTER_FUNC();
	MII_SET(RTL_MII_DIR|RTL_MII_DATAOUT);
	
	for (i = 0; i < 32; i++) {
		MII_SET(RTL_MII_CLK);
		SYS_DELAY(100);
		MII_CLR(RTL_MII_CLK);
		SYS_DELAY(100);
	}
	
	_RETURN;
}


/*******************************************************************************
*
* rtl81x9MII_send
*
* Clock a series of bits through the MII.
*
* RETURNS: N/A
*/

LOCAL void rtl81x9MII_send
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	ULONG					bits,
	int 					cnt
	)
	
{
	int 		i;
	ENTER_FUNC();
	MII_CLR(RTL_MII_CLK);
	
	for (i = (0x1 << (cnt - 1)); i; i >>= 1) {
		if (bits & i) {
			MII_SET(RTL_MII_DATAOUT);
		} else {
			MII_CLR(RTL_MII_DATAOUT);
		}
		SYS_DELAY(100);
		MII_CLR(RTL_MII_CLK);
		SYS_DELAY(100);
		MII_SET(RTL_MII_CLK);
	}

	_RETURN;
}

/*******************************************************************************
*
* rtl81x9MII_readreg
*
* Read an PHY register through the MII.
*
* RETURNS: N/A
*/

LOCAL int rtl81x9MII_readreg 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	RTL_MII_FRAME * 		frame
	)
	
{
	int 		i, ack, s;

	ENTER_FUNC();
	s = splimp();
	
	/*
	* Set up frame for RX.
	*/
	frame->mii_stdelim = RTL_MII_STARTDELIM;
	frame->mii_opcode = RTL_MII_READOP;
	frame->mii_turnaround = 0;
	frame->mii_data = 0;
	
	rtl81x9CsrWriteWord (pDrvCtrl, RTL_REGS_MII, 0, RTL_WIN_0);
	
	/*
	* Turn on data xmit.
	*/
	MII_SET(RTL_MII_DIR);
	
	rtl81x9MII_sync(pDrvCtrl);
	
	/*
	* Send command/address info.
	*/
	rtl81x9MII_send(pDrvCtrl, frame->mii_stdelim, 2);
	rtl81x9MII_send(pDrvCtrl, frame->mii_opcode,  2);
	rtl81x9MII_send(pDrvCtrl, frame->mii_phyaddr, 5);
	rtl81x9MII_send(pDrvCtrl, frame->mii_regaddr, 5);
	
	/* Idle bit */
	MII_CLR((RTL_MII_CLK|RTL_MII_DATAOUT));
	SYS_DELAY(100);
	MII_SET(RTL_MII_CLK);
	SYS_DELAY(100);
	
	/* Turn off xmit. */
	MII_CLR(RTL_MII_DIR);
	
	/* Check for ack */
	MII_CLR(RTL_MII_CLK);
	SYS_DELAY(100);
	MII_SET(RTL_MII_CLK);
	SYS_DELAY(100);
	ack = rtl81x9CsrReadWord(pDrvCtrl, RTL_REGS_MII, RTL_WIN_0) & RTL_MII_DATAIN;
	
	/*
	* Now try reading data bits. If the ack failed, we still
	* need to clock through 16 cycles to keep the PHY(s) in sync.
	*/
	if (ack) {
		for(i = 0; i < 16; i++) {
			MII_CLR(RTL_MII_CLK);
			SYS_DELAY(100);
			MII_SET(RTL_MII_CLK);
			SYS_DELAY(100);
		}
		goto fail;
	}
	
	for (i = 0x8000; i; i >>= 1) {
		MII_CLR(RTL_MII_CLK);
		SYS_DELAY(100);
		if (!ack) {
			if (rtl81x9CsrReadWord(pDrvCtrl, RTL_REGS_MII, RTL_WIN_0) & RTL_MII_DATAIN)
				frame->mii_data |= i;
			SYS_DELAY(100);
		}
		MII_SET(RTL_MII_CLK);
		SYS_DELAY(100);
	}
	
fail:
	
	MII_CLR(RTL_MII_CLK);
	SYS_DELAY(100);
	MII_SET(RTL_MII_CLK);
	SYS_DELAY(100);
	
	splx(s);
	
	if (ack){
		_RETURN 1;
	}
	_RETURN 0;
}



/*******************************************************************************
*
* rtl81x9MII_writereg
*
* Write an PHY register through the MII.
*
* RETURNS: N/A
*/
	
LOCAL int rtl81x9MII_writereg 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	RTL_MII_FRAME * 		frame
	)
{
	int 		s;

	ENTER_FUNC();
	s = splimp();
	
	/*
	* Set up frame for TX.
	*/
	
	frame->mii_stdelim = RTL_MII_STARTDELIM;
	frame->mii_opcode = RTL_MII_WRITEOP;
	frame->mii_turnaround = RTL_MII_TURNAROUND;
	
	/*
	* Turn on data output.
	*/
	
	MII_SET(RTL_MII_DIR);
	
	rtl81x9MII_sync(pDrvCtrl);
	
	rtl81x9MII_send(pDrvCtrl, frame->mii_stdelim, 2);
	rtl81x9MII_send(pDrvCtrl, frame->mii_opcode, 2);
	rtl81x9MII_send(pDrvCtrl, frame->mii_phyaddr, 5);
	rtl81x9MII_send(pDrvCtrl, frame->mii_regaddr, 5);
	rtl81x9MII_send(pDrvCtrl, frame->mii_turnaround, 2);
	rtl81x9MII_send(pDrvCtrl, frame->mii_data, 16);
	
	/* Idle bit. */
	MII_SET(RTL_MII_CLK);
	SYS_DELAY(100);
	MII_CLR(RTL_MII_CLK);
	SYS_DELAY(100);
	
	/*
	* Turn off xmit.
	*/
	MII_CLR(RTL_MII_DIR);
	
	splx(s);
	
	_RETURN 0;
}
		
/*******************************************************************************
*
* rtl81x9Phy_readreg
*
* Read an PHY register.
*
* RETURNS: N/A
*/

LOCAL USHORT rtl81x9Phy_readreg 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	int 					reg
	)
	
{
	RTL_MII_FRAME			frame;
	USHORT					rval = 0;
	USHORT					rtl8139_reg = 0;

	ENTER_FUNC();
	if ((pDrvCtrl->devType == RTL_DEV_8139A) || (pDrvCtrl->devType == RTL_DEV_8139B)){
		switch(reg) {
		case RTL_PHY_BMCR:
			rtl8139_reg = RTL_REGS_MII_BMCR;
			break;
		case RTL_PHY_BMSR:
			rtl8139_reg = RTL_REGS_MII_BMSR;
			break;
		case RTL_PHY_ANAR:
			rtl8139_reg = RTL_REGS_NWAY_ADVERT;
			break;
		case RTL_PHY_LPAR:
			rtl8139_reg = RTL_REGS_NWAY_LPAR;
			break;
		default:
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rl%d: bad phy register\n", pDrvCtrl->unit, 0, 0, 0, 0, 0);
			_RETURN 0;
		}
		rval = rtl81x9CsrReadWord(pDrvCtrl, rtl8139_reg, RTL_WIN_0);
		
		_RETURN rval;
	}
	
	bzero((char *)&frame, sizeof(frame));
	
	frame.mii_phyaddr = pDrvCtrl->phy_addr;
	frame.mii_regaddr = reg;
	rtl81x9MII_readreg(pDrvCtrl, &frame);
	
	_RETURN frame.mii_data;
}
		
		
/*******************************************************************************
*
* rtl81x9Phy_writereg
*
* Read an PHY register.
*
* RETURNS: N/A
*/

LOCAL void rtl81x9Phy_writereg 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl,	/* device control structure */
	int 					reg,
	int 					data
	)
{
	RTL_MII_FRAME			frame;
	USHORT					rtl8139_reg = 0;

	ENTER_FUNC();
	
	if ((pDrvCtrl->devType == RTL_DEV_8139A) || (pDrvCtrl->devType == RTL_DEV_8139B)){
		switch(reg) {
		case RTL_PHY_BMCR:
			rtl8139_reg = RTL_REGS_MII_BMCR;
			break;
		case RTL_PHY_BMSR:
			rtl8139_reg = RTL_REGS_MII_BMSR;
			break;
		case RTL_PHY_ANAR:
			rtl8139_reg = RTL_REGS_NWAY_ADVERT;
			break;
		case RTL_PHY_LPAR:
			rtl8139_reg = RTL_REGS_NWAY_LPAR;
			break;
		default:
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl%d: bad phy register\n", pDrvCtrl->devType, 0, 0, 0, 0, 0);
			_RETURN;
		}
		rtl81x9CsrWriteWord (pDrvCtrl, rtl8139_reg, data, RTL_WIN_0);
		_RETURN;
	}
	
	bzero((char *)&frame, sizeof(frame));
	
	frame.mii_phyaddr = pDrvCtrl->phy_addr;
	frame.mii_regaddr = reg;
	frame.mii_data = data;
	
	rtl81x9MII_writereg(pDrvCtrl, &frame);
	
	_RETURN;
}


/*******************************************************************************
*
* rtl81x9AutoNegTx
*
* Initiate an autonegotiation session.
*
* RETURNS: N/A
*/

LOCAL void rtl81x9AutoNegTx 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl	/* device control structure */
	)
{
	
	USHORT		phy_sts;
	
	ENTER_FUNC();
	
	rtl81x9Phy_writereg (pDrvCtrl, RTL_PHY_BMCR, RTL_PHY_BMCR_RESET);
	
	SYS_DELAY(50000);
	while(rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMCR)
		& RTL_PHY_BMCR_RESET);
	
	phy_sts = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMCR);
	phy_sts |= RTL_PHY_BMCR_AUTONEGENBL|RTL_PHY_BMCR_AUTONEGRSTR;
	rtl81x9Phy_writereg(pDrvCtrl, RTL_PHY_BMCR, phy_sts);
	
	SYS_DELAY(50000);
	
	_RETURN;
}


/*******************************************************************************
*
* rtl81x9MII_autoneg
*
* Invoke autonegotiation on a PHY. Also used with the 8139 internal
* transceiver.
*
* RETURNS: N/A
*/

LOCAL int rtl81x9MII_autoneg 
	(
	RTL81X9END_DEVICE * 	pDrvCtrl	/* device control structure */
	)
	
{
	UINT16		phyStatus = 0;
	UINT16		media;
	UINT16		advert;
	UINT16		ability;
	int 		speed = 10000000;

	ENTER_FUNC();
	/*
	* The 100baseT4 PHY sometimes has the 'autoneg supported'
	* bit cleared in the status register, but has the 'autoneg enabled'
	* bit set in the control register. This is a contradiction, and
	* I'm not sure how to handle it. If you want to force an attempt
	* to autoneg for 100baseT4 PHYs, #define FORCE_AUTONEG_TFOUR
	* and see what happens.
	*/
#ifndef FORCE_AUTONEG_TFOUR
	/*
	* First, see if autoneg is supported. If not, there's
	* no point in continuing.
	*/
	phyStatus = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMSR);
	if (!(phyStatus & RTL_PHY_BMSR_CANAUTONEG)) {
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl%d: autonegotiation not supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		media = rtl81x9Phy_readreg (pDrvCtrl, RTL_PHY_BMCR);
		media &= ~RTL_PHY_BMCR_SPEEDSEL;
		media &= ~RTL_PHY_BMCR_DUPLEX;
		
		rtl81x9Phy_writereg (pDrvCtrl, RTL_PHY_BMCR, media);
		
		_RETURN speed;
	}
#endif
	
	
	rtl81x9AutoNegTx (pDrvCtrl);
	
	SYS_DELAY (50000000);
	/* sysStallExecutionProcessor(100000); */
	
	if (rtl81x9Phy_readreg (pDrvCtrl, RTL_PHY_BMSR) & RTL_PHY_BMSR_AUTONEGCOMP){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl%d: autoneg complete, \n", pDrvCtrl->unit, 0, 0, 0, 0, 0);
		phyStatus = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMSR);
	}else{
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rtl%d: autoneg not complete, \n", pDrvCtrl->unit, 0, 0, 0, 0, 0);
	}
	
	media = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMCR);
	
	/* Link is good. Report modes and set duplex mode. */
	if (rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMSR) & RTL_PHY_BMSR_LINKSTAT){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "link status good ", 0, 0, 0, 0, 0, 0);
		advert = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_ANAR);
		ability = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_LPAR);
		
		if (advert & RTL_PHY_ANAR_100BT4 && ability & RTL_PHY_ANAR_100BT4){
			media |= RTL_PHY_BMCR_SPEEDSEL;
			media &= ~RTL_PHY_BMCR_DUPLEX;
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "(100baseT4)\n", 0, 0, 0, 0, 0, 0);
			speed = 100000000;
		} else if (advert & RTL_PHY_ANAR_100BTXFULL &&	ability & RTL_PHY_ANAR_100BTXFULL){
			media |= RTL_PHY_BMCR_SPEEDSEL;
			media |= RTL_PHY_BMCR_DUPLEX;
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "(full-duplex, 100Mbps)\n", 0, 0, 0, 0, 0, 0);
			speed = 100000000;
		}else if (advert & RTL_PHY_ANAR_100BTXHALF && ability & RTL_PHY_ANAR_100BTXHALF){
			media |= RTL_PHY_BMCR_SPEEDSEL;
			media &= ~RTL_PHY_BMCR_DUPLEX;
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "(half-duplex, 100Mbps)\n", 0, 0, 0, 0, 0, 0);
			speed = 100000000;
		} else if (advert & RTL_PHY_ANAR_10BTFULL && ability & RTL_PHY_ANAR_10BTFULL) {
			media &= ~RTL_PHY_BMCR_SPEEDSEL;
			media |= RTL_PHY_BMCR_DUPLEX;
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "(full-duplex, 10Mbps)\n", 0, 0, 0, 0, 0, 0);
			speed = 10000000;
		} else {
			media &= ~RTL_PHY_BMCR_SPEEDSEL;
			media &= ~RTL_PHY_BMCR_DUPLEX;
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "(half-duplex, 10Mbps)\n", 0, 0, 0, 0, 0, 0);
			speed = 10000000;
		}
		
		/* Set ASIC's duplex mode to match the PHY. */
		rtl81x9Phy_writereg(pDrvCtrl, RTL_PHY_BMCR, media);
	} 	else {
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "no carrier\n", 0, 0, 0, 0, 0, 0);
		media &= ~RTL_PHY_BMCR_SPEEDSEL;
		media &= ~RTL_PHY_BMCR_DUPLEX;
		rtl81x9Phy_writereg (pDrvCtrl, RTL_PHY_BMCR, media);
	}
	
	_RETURN speed;
}

/*******************************************************************************
*
* rtl81x9MediaSet
*
* Set speed and duplex mode.
*
* RETURNS: N/A
*/

LOCAL int rtl81x9MediaSet 
(
	RTL81X9END_DEVICE *	pDrvCtrl,	/* device control structure */
	int 					media
	)
	
{
	USHORT		bmcr;
	USHORT			bmsr;
	int 			speed = 10000000;
	
	ENTER_FUNC();
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "rl%d: selecting MII\n", pDrvCtrl->unit, 0, 0, 0, 0, 0);
	
	bmsr = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMSR);
	bmcr = rtl81x9Phy_readreg(pDrvCtrl, RTL_PHY_BMCR);
	
	bmcr &= ~(RTL_PHY_BMCR_AUTONEGENBL|RTL_PHY_BMCR_SPEEDSEL|
		RTL_PHY_BMCR_DUPLEX|RTL_PHY_BMCR_LOOPBK);
	
	RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"elPci%d: PHY status word: %x\n", pDrvCtrl->unit, bmsr, 3, 4, 5, 6);
	
	if (bmsr & RTL_PHY_BMSR_CANAUTONEG)	{
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"elPci%d: autoneg supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		return 0;
	}
	
	
	if (bmsr & RTL_PHY_BMSR_10BTHALF)	{
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d: 10Mbps half-duplex mode supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		if (IFM_SUBTYPE(media) == IFM_10_T) {
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "10Mbps, ", 0, 0, 0, 0, 0, 0);
			bmcr &= ~RTL_PHY_BMCR_SPEEDSEL;
		}
	}
	
	if (bmsr & RTL_PHY_BMSR_10BTFULL){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d: 10Mbps full-duplex mode supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		if (IFM_SUBTYPE(media) == IFM_10_T) {
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "10Mbps, ", 0, 0, 0, 0, 0, 0);
			bmcr &= ~RTL_PHY_BMCR_SPEEDSEL;
		}
	}
	
	if (bmsr & RTL_PHY_BMSR_100BTXHALF){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d:100Mbps half-duplex mode supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		speed = 100000000;
		if (IFM_SUBTYPE(media) == IFM_100_TX) {
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "100Mbps, ", 0, 0, 0, 0, 0, 0);
			bmcr |= RTL_PHY_BMCR_SPEEDSEL;
		}
	}
	
	if (bmsr & RTL_PHY_BMSR_100BTXFULL){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d:100Mbps full-duplex mode supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		speed = 100000000;
		if (IFM_SUBTYPE(media) == IFM_100_TX){
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "100Mbps, ", 0, 0, 0, 0, 0, 0);
			bmcr |= RTL_PHY_BMCR_SPEEDSEL;
		}
	}
	
	/* Some also support 100BaseT4 */
	if (bmsr & RTL_PHY_BMSR_100BT4){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d:100baseT4 mode supported\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
		speed = 100000000;
#ifdef FORCE_AUTONEG_TFOUR
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD,"rtl81x9%d:force on autoneg support for BT4\n",
			pDrvCtrl->unit, 2, 3, 4, 5, 6);
#endif
		if (IFM_SUBTYPE(media) == IFM_100_T4){
			RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "100Mbps/T4, half-duplex\n", 0, 0, 0, 0, 0, 0);
			bmcr |= RTL_PHY_BMCR_SPEEDSEL;
			bmcr &= ~RTL_PHY_BMCR_DUPLEX;
		}
	}
	if ((media & IFM_GMASK) == IFM_FDX){
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "full duplex\n", 0, 0, 0, 0, 0, 0);
		bmcr |= RTL_PHY_BMCR_DUPLEX;
	}else{
		RTL81X9_LOG (RTL81X9_DEBUG_LOAD, "half duplex\n", 0, 0, 0, 0, 0, 0);
		bmcr &= ~RTL_PHY_BMCR_DUPLEX;
	}
	
	rtl81x9Phy_writereg(pDrvCtrl, RTL_PHY_BMCR, bmcr);
	
	_RETURN speed;
	
}

/*******************************************************************************
*
* rtl81x9MediaConfig - configure the media and do auto negotiation
*
* This function configures the media and does the auto negotioation.
*
* RETURNS: speed or 0
*
*/

LOCAL int rtl81x9MediaConfig
(
 RTL81X9END_DEVICE *	pDrvCtrl	/* device control structure */
 )
{
	int speed;
	ENTER_FUNC();
	if ((speed = rtl81x9MediaSet (pDrvCtrl, IFM_100_TX)) == 0){
		speed = rtl81x9MII_autoneg (pDrvCtrl);
	}
	
	_RETURN speed;
}

STATUS rtl81x9Hook
	(
	RTL81X9END_DEVICE	*pDrvCtrl, /* device ptr */
	STATUS (*hook)(END_OBJ*,M_BLK_ID)
	 )
{
	pDrvCtrl->recvHook=hook;
	return OK;
}

STATUS rtl81x9Unhook
	(
	RTL81X9END_DEVICE	*pDrvCtrl
	 )
{
	pDrvCtrl->recvHook=0;
	return OK;
}

int rtl81x9Lock(RTL81X9END_DEVICE * d)
{
	int mode = rtl81x9CsrReadWord(d, RTL_REGS_INTR_MASK, 0);
	if(!(d->flags & RTL_FLG_POLLING)){
		rtl81x9CsrWriteWord(d, RTL_REGS_INTR_MASK, 0, 0);
	}
	return mode & RTL_VALID_INTERRUPTS;
}

void rtl81x9Unlock(RTL81X9END_DEVICE * d, int mode)
{
	if(!(d->flags & RTL_FLG_POLLING)){
		if(mode){
			int m1=rtl81x9CsrReadWord(d, RTL_REGS_INTR_MASK, 0);
			rtl81x9CsrWriteWord(d, RTL_REGS_INTR_MASK, (m1 & ~RTL_VALID_INTERRUPTS)|mode, 0);
		}
	}
}

#endif


