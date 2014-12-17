/* sysRtl81x9End.c - system configuration module for RTL81x9 END driver */

/* Copyright 1984-1999 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
02b,28jan00, Added new define RTL81X9_EARX_THRESH
02a,27jan00, Modified the initialisation and resource table.
01a,12nov99, dgy created.
*/

/*
DESCRIPTION
This is the WRS-supplied configuration module for the VxWorks
Realtek 81x9 (rtl) END driver.

  It initializes the resources for all the 81x9 devices found.
  
	It performs the dynamic parameterization of the rtl81x9End driver.
	This technique of 'just-in-time' parameterization allows driver
	parameter values to be declared as any other defined constants rather
	than as static strings.
*/
#include "vxWorks.h"
#include "config.h"
#include "configNet.h"

#ifdef INCLUDE_RTL_81X9_END

#include "vmLib.h"
#include "stdio.h"
#include "sysLib.h"
#include "logLib.h"
#include "stdlib.h"
#include "string.h"
#include "end.h"
#include "intLib.h"
#include "drv/pci/pciConfigLib.h"
#include "drv/pci/pciIntLib.h"

/* imports */

IMPORT STATUS			sysMmuMapAdd (void * address, UINT len,
									  UINT initialStateMask,
									  UINT initialState);

IMPORT END_TBL_ENTRY	endDevTbl[];	/* end device table */

IMPORT END_OBJ *	rtl81x9EndLoad (char *);

/* defines */

#define RTL_81X9_LOAD_FUNC		  rtl81x9EndLoad

/*
* default values if PCI_CFG_TYPE defined to be PCI_CFG_FORCE
* note: memory addresses must be aligned on MMU page boundaries
*/

#define RTL81X9_IO_ADR0 	0xf400
#define RTL81X9_MEM_ADR0	0xfd000000
#define RTL81X9_INT_LVL0	0x0b
#define RTL81X9_INT_VEC0	0

#define RTL81X9_IO_ADR1 	0xf420
#define RTL81X9_MEM_ADR1	0xfd200000
#define RTL81X9_INT_LVL1	0x05
#define RTL81X9_INT_VEC1	0

#define RTL81X9_IO_ADR2 	0xf440
#define RTL81X9_MEM_ADR2	0xfd300000
#define RTL81X9_INT_LVL2	0x0c
#define RTL81X9_INT_VEC2	0

#define RTL81X9_IO_ADR3 	0xf460
#define RTL81X9_MEM_ADR3	0xfd400000
#define RTL81X9_INT_LVL3	0x9
#define RTL81X9_INT_VEC3	0

#define RTL81X9_MAX_DEV 	4

#define RTL81X9_EARX_THRESH 10
#define RTL81X9_END_FLAGS	(RTL81X9_EARX_THRESH << 16)

#define RTL81X9_BUFF_MTPLR	NONE

#define EXT_INTERRUPT_BASE		INT_NUM_IRQ0	/* irq0 	*/

#define PCI_DEV_MMU_MSK 		(~(VM_PAGE_SIZE - 1))	/* Mask MMU page */

/* Offsets of PCI resources in host space */

#ifndef CPU_PCI_IO_ADRS
#define CPU_PCI_IO_ADRS 		0				/* base of PCI I/O addr */
#endif /* CPU_PCI_IO_ADRS */

#ifndef CPU_PCI_MEM_ADRS
#define CPU_PCI_MEM_ADRS		0				/* base of PCI mem address */
#endif /* CPU_PCI_MEM_ADRS */

#ifndef PCI2DRAM_BASE_ADRS
#define PCI2DRAM_BASE_ADRS		0				/* DRAM base addrs from PCI */
#endif /* PCI2DRAM_BASE_ADRS */

#include "rtl81x9End.c"

/* typedefs */

typedef struct rtl81x9PciResource			   /* RTL81X9_PCI_RESOURCES */
{
	UINT32		iobaseCsr;				/* Base Address Register 0 */
	UINT32		membaseCsr; 			/* Base Address Register 1 */
	char		irq;					/* Interrupt Request Level */
	UINT32		irqvec; 				/* Interrupt Request vector */
	UINT32		configType; 			/* type of configuration */
	UINT32		boardType;				/* type of LAN board for this unit */
	UINT32		pciBus; 				/* PCI Bus number */
	UINT32		pciDevice;				/* PCI Device number */
	UINT32		pciFunc;				/* PCI Function number */
} RTL81X9_PCI_RESOURCES;

typedef struct rtl81x9BoardResource 		   /* RTL81X9_BOARD_RESOURCES */
{
	UINT32		type;					/* type of the board */
	UINT32		vendorId;				/* Vendor ID */
	UINT32		deviceId;				/* Device ID */
	UINT32		RtlUsrFlags;			 /* RTL driver user flags */
	FUNCPTR 	mediaSelectFunc;		/* media select routine */
} RTL81X9_BOARD_RESOURCES;

/* locals */

/*
* This array defines the board-specific PCI resources, the base address
* register configuration mode and the Ethernet adapter type. It's indexed
* using the device number returned from pciFindDevice().
*/

LOCAL RTL81X9_PCI_RESOURCES rtl81x9PciResrcs [] =
{
	{RTL81X9_IO_ADR0, RTL81X9_MEM_ADR0, RTL81X9_INT_LVL0, RTL81X9_INT_VEC0,
		PCI_CFG_TYPE, 0, 0, 0, 0},
	{RTL81X9_IO_ADR1, RTL81X9_MEM_ADR1, RTL81X9_INT_LVL1, RTL81X9_INT_VEC1,
		PCI_CFG_TYPE, 0, 0, 0, 0},
	{RTL81X9_IO_ADR2, RTL81X9_MEM_ADR2, RTL81X9_INT_LVL2, RTL81X9_INT_VEC2,
		PCI_CFG_TYPE, 0, 0, 0, 0},
	{RTL81X9_IO_ADR3, RTL81X9_MEM_ADR3, RTL81X9_INT_LVL3, RTL81X9_INT_VEC3,
		PCI_CFG_TYPE, 0, 0, 0, 0}
};

#if 0

/*
	2005-8-17 jackie
	we don't need this array because we use the specialized board.
*/
/*
* This array defines board-specific vendor and device ids, flags to pass to
* the drive load routine and the function used to select the media.
*/

LOCAL RTL81X9_BOARD_RESOURCES rtl81x9Brds [] =
{
	{0, RTL_VENDORID,		RTL_8139_DEV_ID,		0,	NULL},
	{0, RTL_VENDORID,		RTL_8129_DEV_ID,		0,	NULL},		
	{0, RTL_VENDOR_ID_MIS,	RTL_MIS_DEV_ID, 		0,	NULL},
	{0, ADDTRON_VENDORID,	ADDTRON_DEVICEID_8139,	0,	NULL},
	{0, DELTA_VENDORID, 	DELTA_DEVICEID_8139,	0,	NULL},
	{0, ACCTON_VENDORID,	ACCTON_DEVICEID_5030,	0,	NULL},
};

#endif

LOCAL int rtl81x9EndUnits = 0;
RTL81X9END_DEVICE * rtl81x9Objects[4];
int rtl81x9Resources[4][4];

extern int sysDebugTrace(int code);

/*******************************************************************************
*
* sysRtl81x9PciInit - prepare LAN adapter for RTL_81X9 initialization
*
* This routine finds out the PCI device, maps its memory and IO address.
* It must be done prior to initializing the driver.  Also
* must be done prior to MMU initialization, usrMmuInit().
*
* RETURNS: OK/ERROR
*/

STATUS sysRtl81x9PciInit (
    UINT32  pciBus,      /* store a PCI bus number */
    UINT32  pciDevice,   /* store a PCI device number */
    UINT32  pciFunc,     /* store a PCI function number */
    UINT32  vendorId,    /* store a PCI vendor ID */
    UINT32  deviceId,    /* store a PCI device ID */
    UINT8   revisionId   /* store a PCI revision ID */
    )
{
	UINT32		membaseCsr;
	UINT32		iobaseCsr;
	char		irq;
	RTL81X9_PCI_RESOURCES * pRsrc;
	/* for all the support network devices find if some of them exist */
	
	sysDebugTrace(0x70);

	if(rtl81x9EndUnits >= RTL81X9_MAX_DEV){
		return ERROR;
	}
	
	/* load up the PCI device table */
	
	pRsrc = rtl81x9PciResrcs + rtl81x9EndUnits; 
	
	pRsrc->pciBus	= pciBus;
	pRsrc->pciDevice = pciDevice;
	pRsrc->pciFunc	= pciFunc;
	
	rtl81x9EndUnits++;		/* number of units found */

	sysDebugTrace(0x72);
	
	/* Now initialize the unit */
	
	/* Fill in the resource entry */
	
	sysDebugTrace(0x74);		

	/*
	* get memory base address and IO base address
	* Note: we read it in again, even if we just wrote it out because  
	* the device can change what we wrote
	*/
	
	pciConfigInLong (pRsrc->pciBus, 
		pRsrc->pciDevice, 
		pRsrc->pciFunc,
		PCI_CFG_BASE_ADDRESS_0, &iobaseCsr);
	
	pciConfigInLong (pRsrc->pciBus, 
		pRsrc->pciDevice, 
		pRsrc->pciFunc,
		PCI_CFG_BASE_ADDRESS_1, &membaseCsr);
	
	pciConfigInByte (pRsrc->pciBus, 
		pRsrc->pciDevice, 
		pRsrc->pciFunc,
		PCI_CFG_DEV_INT_LINE, &irq);
	sysDebugTrace(0x75);
	/*
	* mask off registers. IO base needs to be masked off because bit0
	* will always be set to 1
	*/
	
	membaseCsr	 &= PCI_MEMBASE_MASK;
	iobaseCsr	 &= PCI_IOBASE_MASK;
	
#if defined(INCLUDE_MMU_BASIC) || defined(INCLUDE_MMU_FULL)
	sysDebugTrace(0x76);
	if (sysMmuMapAdd ((void *)(membaseCsr & PCI_DEV_MMU_MSK),
		VM_PAGE_SIZE,
		VM_STATE_MASK_FOR_ALL,
		VM_STATE_FOR_PCI
		) == ERROR)
	{
	/* for now, exit, but later break and stop where we're at 
		when we're detecting multiple units */
		return (ERROR);
		
	}
#endif /* INCLUDE_MMU_BASIC */

	sysDebugTrace(0x78);
	/* over write the resource table with values read */
	
	pRsrc->membaseCsr   = membaseCsr;
	pRsrc->iobaseCsr	  = iobaseCsr;
	pRsrc->irq		  = irq;
	pRsrc->irqvec 	  = irq + EXT_INTERRUPT_BASE;
	
	/* enable mapped memory and IO addresses */
	pciConfigOutWord (pRsrc->pciBus, 
		pRsrc->pciDevice, 
		pRsrc->pciFunc,
		PCI_CFG_COMMAND, PCI_CMD_IO_ENABLE |
		PCI_CMD_MEM_ENABLE | PCI_CMD_MASTER_ENABLE);
	
	/* disable sleep mode */
	sysDebugTrace(0x79);	
	pciConfigOutWord (
		pRsrc->pciBus, 
		pRsrc->pciDevice, 
		pRsrc->pciFunc, 
		PCI_CFG_MODE, 
		SLEEP_MODE_DIS);

	rtl81x9Resources[rtl81x9EndUnits-1][0]=membaseCsr;
	rtl81x9Resources[rtl81x9EndUnits-1][1]=irq;
	rtl81x9Resources[rtl81x9EndUnits-1][2]=irq+EXT_INTERRUPT_BASE;

	sysDebugTrace(0x7a);
	return OK; 
}
	
/*******************************************************************************
*
* sysRtl81x9IntEnable - enable interrupts
*
* This routine enables interrupts.	This may involve operations on
* interrupt control hardware.
*
* RETURNS: OK or ERROR for invalid arguments.
*/

STATUS sysRtl81x9IntEnable
	(
	int level		/* level number */
	)
{
	return (sysIntEnablePIC(level));
}

/*******************************************************************************
*
* sysLanIntDisable - disable interrupts
*
* This routine disables interrupts.  This may involve operations on
* interrupt control hardware.
*
* RETURNS: OK or ERROR for invalid arguments.
*/

STATUS sysRtl81x9IntDisable
	(
	int level		/* level number */
	)
{
	return (sysIntDisablePIC(level));
}


/******************************************************************************
*
* sysRtl81x9EndLoad - load an istance of the rtl81x9 END driver
*
* This routine loads the rtl81x9 driver with the parameters specified by
* the resource table for the device, and some default values.
*
* The END device load string formed by this routine is in the following
* following format.
* <devMemAddr>:<devIoAddr>:<pciMemBase>:<vecnum>:<intLvl>:<memAdrs>
* :<memSize>:<memWidth>:<flags>:<buffMultiplier>
*
* .IP <devMemAddr>
* Device register base memory address
* .IP <devIoAddr>
* Device register base IO address
* .IP <pciMemBase>
* Base address of PCI memory space
* .IP <vecNum>
* Interrupt vector number.
* .IP <intLvl>
* Interrupt level.
* .IP <memAdrs>
* Memory pool address or NONE.
* .IP <memSize>
* Memory pool size or zero.
* .IP <memWidth>
* Memory system size, 1, 2, or 4 bytes (optional).
* .IP <flags>
* Device specific flags.
* .IP <buffMultiplier>
* Buffer Multiplier or NONE. If NONE is specified, it defaults to 2
*
* This routine only loads and initializes instance zero of the device.
* If the user wishes to use more than one rtl81x9 devices, this routine
* should be changed.
*
* RETURNS: pointer to END object or ERROR.
*
* SEE ALSO: rtl81x9EndLoad()
*/

END_OBJ * sysRtl81x9EndLoad
	(
	char * pParamStr,	/* ptr to initialization parameter string */
	void * unused		/* unused optional argument */
	)
{
/*
* The rtl81x9 driver END_LOAD_STRING should be:
* <devMemAddr>:<devIoAddr>:<pciMemBase>:<vecnum>:<intLvl>:<memAdrs>
* :<memSize>:<memWidth>:<flags>:<buffMultiplier>
* Note that unit string is prepended by the mux, so we
* don't put it here.
*/
	
	int unit_number;
	char * pStr = NULL;
	char paramStr [200];
#define rtl81x9ParamTemplate "0x%x:0x%x:0x%x:%d:%d:-1:-1:-1:0x%x:%d:0x%x"
	END_OBJ * pEnd;
	RTL81X9_PCI_RESOURCES * pRsrc;	
	
	sysDebugTrace(0x80);
	if (strlen (pParamStr) == 0){
	/*
	* muxDevLoad() calls us twice.	If the string is
	* zero length, then this is the first time through
	* this routine.
		*/
		sysDebugTrace(0x81);			
		pEnd = (END_OBJ *) rtl81x9EndLoad (pParamStr);
		sysDebugTrace(0x82);			
	}else{
		/*
		* On the second pass through here, we actually create
		* the initialization parameter string on the fly.
		* Note that we will be handed our unit number on the
		* second pass and we need to preserve that information.
		* So we use the unit number handed from the input string.
		*/
			
		/* Work out the Unit Number to initialise */
		
		unit_number = atoi (pParamStr);
		if ((unit_number < 0) || (unit_number >= rtl81x9EndUnits)){
			return NULL;
		}else{
			pRsrc = rtl81x9PciResrcs + unit_number; 
			pStr = strcpy (paramStr, pParamStr);
			
			/* Now, we get to the end of the string */
			
			pStr += strlen (paramStr);
			
			/* finish off the initialization parameter string */
			sprintf (
				pStr, 
				rtl81x9ParamTemplate,
				/* device memory IO base */
				(UINT) pRsrc->membaseCsr + CPU_PCI_MEM_ADRS,
				/* device Io base */
				(UINT) pRsrc->iobaseCsr  + CPU_PCI_IO_ADRS,
				PCI2DRAM_BASE_ADRS, 				/* pciMemBase */
				pRsrc->irqvec, 		/* interrupt IRQ vector */
				pRsrc->irq,			/* interrupt irq number */
				0,									/* ?????? */
				0,									/* offset */
				RTL81X9_END_FLAGS					/* flags */
				);
			
			if ((pEnd = (END_OBJ *) rtl81x9EndLoad (paramStr)) == (END_OBJ *)ERROR){
				logMsg ("Error: rtl81x9EndLoad failed to load driver\n",
					0, 0, 0, 0, 0, 0);
			}
			rtl81x9Objects[unit_number] = pEnd;
		}
	}

	return (pEnd);
}

void sysRtl81x9Show(int d)
{
	RTL81X9END_DEVICE * o;
	o=(RTL81X9END_DEVICE *)rtl81x9Objects[d];
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
	printf("intCounter=%08x\n", o->intCounter);
	printf("BUS %d DEV %d FUNC %d\n", rtl81x9PciResrcs[d].pciBus, 
		rtl81x9PciResrcs[d].pciDevice, 
		rtl81x9PciResrcs[d].pciFunc
		);
}

void sysRtl81x9AssignInterrupt(int d, int irq)
{
	rtl81x9Stop(rtl81x9Objects[d]);
	pciConfigOutByte (rtl81x9PciResrcs[d].pciBus, 
		rtl81x9PciResrcs[d].pciDevice, 
		rtl81x9PciResrcs[d].pciFunc,
		PCI_CFG_DEV_INT_LINE, irq);
	rtl81x9Objects[d]->ilevel=irq;
	rtl81x9Objects[d]->ivec=irq+EXT_INTERRUPT_BASE;
	rtl81x9Start(rtl81x9Objects[d]);
}

#endif /* INCLUDE_RTL_81X9_END */

