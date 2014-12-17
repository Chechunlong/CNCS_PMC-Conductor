/*
	2007-6-24 fix bug of save_nvram (not lock db)
	we disable the watch dog of save config to avoid agent suspend
*/


#include "../../fkern/precomp.h"
//#include <endLib.h>
//#include "../../fkern/vxworks/rtl8139.c"
#include "rtl81x9end.h"
#include <cacheLib.h>

int peer_fix_count = 0;

/* The definition of the driver control structure */
typedef struct rtl_device{	
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

extern END_OBJ * rtl81x9Objects[4];
#define PEER_PORT 2
#define peerEtherPort rtl81x9Objects[PEER_PORT]
#define HSP_PROTOCOL 0xf8cf

static int tid_cwd;
static int task_flag;
//extern int saveConfigWatchDog;

#define PCI_WORD_SWAP(x)	(x)

#define SYS_IN_SHORT(pDrvCtrl,addr,data) \
    { \
    ((data) = PCI_WORD_SWAP(*((USHORT *)(addr)))); \
    }      

#define SYS_IN_BYTE(pDrvCtrl,addr,data) \
	{ \
	((data) = *((UCHAR *)(addr))); \
	}

#define SYS_OUT_SHORT(pDrvCtrl,addr,value) \
{ \
	*((USHORT *)(addr)) = PCI_WORD_SWAP((value)); \
}

#define SYS_OUT_BYTE(pDrvCtrl,addr,value) \
    { \
    *((UCHAR *)(addr)) = (value); \
    }

#define SYS_OUT_LONG(pDrvCtrl,addr,value) \
{ \
	*((ULONG *)(addr)) = PCI_SWAP((value)); \
}

#define peerState (g_kernel.peer_status.state)

void pnet_show()
{
	u_short 	   stat;

	RTL81X9END_DEVICE * o;
	o=peerEtherPort;
	printf("RTL object %08x\n", o);
	printf("unit=%d,", o->unit);
	printf("phy_addr=%08x,", o->phy_addr);
	printf("freeDesc=%d,", o->freeDesc);
	printf("pciMemBase=%08x,", o->pciMemBase);
	printf("memBase=%08x,", o->memBase);
	printf("memAdrs=%08x,", o->memAdrs);
	printf("memSize=%08x,", o->memSize);
	printf("devAdrs=%08x,", o->devAdrs);
	printf("ivec=%d,", o->ivec);
	printf("ilevel=%d,", o->ilevel);
	printf("flags=%08x,", o->flags);
	printf("shMem=%08x,", o->pShMem);
	printf("rring=%08x,", o->pRring);
	printf("rringlen=%08x,", o->rringLen);
	printf("RxBuf=%08x,", o->ptrRxBufSpace);
	printf("RxLen=%08x\n", RTL_RXBUFLEN);
	printf("pNetPool=%d,",o->end.pNetPool);
	printf("pClPoolId=%d,",o->pClPoolId);
	printf("ptrRxBufSpace=%08x\n",o->ptrRxBufSpace);

	printf("intCounter=%08x\n", o->intCounter);
	printf("hook=%08x\n", o->recvHook);
	//stat = rtl81x9CsrReadWord (o, RTL_REGS_INTR_STATUS, NONE);
	//printf("intStat=%08x\n", stat);

}

static int err_count = 0;
static int peer_need_fix()
{
	if(g_kernel.status.state != KERN_S_STANDBY){
		err_count = 0;
		return 0;
	}

	if(g_kernel.status.prog_id != g_kernel.peer_status.prog_id){
		err_count = 0;
		return 0;
	}

	if(ke_get_flag(FKERN_LED_SYNCHRONIZED)){
		err_count = 0;
		return 0;
	}	
	
	err_count++;
	if(err_count < 3){
		return 0;
	}

	err_count = 0;
	peer_fix_count++;
	return 1;
}

void pnet_fix()
{
	USHORT		inWord, inWord2;
	int 		level;
	//UCHAR 		b;

	RTL81X9END_DEVICE * o;
	o=peerEtherPort;

	level = intLock ();
	//SYS_IN_BYTE  (o, (o->devAdrs + (UINT32)RTL_REGS_CHIP_CMD), b);
	//if((b & RTL_CMD_RX_BUF_EMPTY) == 0){
		SYS_IN_SHORT (o, (o->devAdrs + (UINT32)RTL_REGS_RX_BUF_ADDR), inWord);
		SYS_IN_SHORT (o, (o->devAdrs + (UINT32)RTL_REGS_RX_BUF_PTR), inWord2);
		inWord -= 16;
		if(inWord != inWord2){
			SYS_OUT_SHORT (o, (o->devAdrs + (UINT32)RTL_REGS_RX_BUF_PTR), inWord);
		}
	//}
	intUnlock (level);	
}

void pnet_reset()
{
	register int	ix;
	int 		level;

	RTL81X9END_DEVICE * o;
	o=peerEtherPort;

	level = intLock ();
	SYS_OUT_BYTE(o, (o->devAdrs + (UINT32)RTL_REGS_CHIP_CMD), RTL_CMD_RESET);
	intUnlock (level);	

	taskDelay(500);

	level = intLock ();
	SYS_OUT_BYTE(o, (o->devAdrs + (UINT32)RTL_REGS_CHIP_CMD), RTL_CMD_RX_ENB + RTL_CMD_TX_ENB);
	SYS_OUT_LONG(o, (o->devAdrs + (UINT32)RTL_REGS_TX_CONFIG), RTL_TXCFG_CONFIG);
	SYS_OUT_LONG(o, (o->devAdrs + (UINT32)RTL_REGS_RX_CONFIG), o->reg_rcr);
	SYS_OUT_LONG(o, (o->devAdrs + (UINT32)RTL_REGS_RX_MISSED), 0);
	SYS_OUT_BYTE(o, (o->devAdrs + (UINT32)RTL_REGS_CHIP_CMD), RTL_CMD_RX_ENB + RTL_CMD_TX_ENB);
	intUnlock (level);	

	//sysIntEnablePIC(o->ilevel);	
	//printf("reg_rcr=%08x\n", o->reg_rcr);
}

static int dis_conf_dog()
{
	while(task_flag != TSK_STOPPING){
//		saveConfigWatchDog = 0;
		if(peer_need_fix()){
			pnet_fix();
		}
		//taskDelay(500 * 60);
		taskDelay(500);
	}
	
	tid_cwd=-1;
	
	return 0;
}

int f8_fix_start()
{
	task_flag = TSK_RUNNING;

	tid_cwd = taskSpawn(
		"dis_conf_dog",	/* name */
		255,			/* priority */
		VX_FP_TASK,		/* options */
		1024,		/* stack size */
		dis_conf_dog,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);

	return 0;
}



int f8_fix_stop()
{
	int i;
	
	task_flag = TSK_STOPPING;
	for(i = 0; i < 10; i++){
		if(tid_cwd < 0){
			return 0;
		}
		taskDelay(100);
	}
	
	return -1;
}
