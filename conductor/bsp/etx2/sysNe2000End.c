/* sysNe2000End.c - system configuration module for NE2000 END */
 
/* Copyright 1999-2001 Wind River Systems, Inc. */
 
/*
modification history
--------------------
01e,22oct01,pai  Updated documentation and cleaned up format.
01d,18jul01,hdn  replaced INT_VEC_ENE with INT_NUM_GET(INT_LVL_ENE)
01b,31mar99,sbs  corrected ne2000ParamTemplate initialization.
                 (SPR #26208)
01a,10mar99,sbs  written from sysNE2000End.c
*/


/*
DESCRIPTION
This is the WRS-supplied configuration module for the VxWorks 
ne2000End (ene) END driver for the ISA/PC104 bus.  It has routines for
initializing device resources and provides BSP-specific ne2000End
driver routines for Novell/Eagle 2000 and compatible network interface
cards.

It performs the dynamic parameterization of the ne2000End driver.
This technique of 'just-in-time' parameterization allows driver
parameter values to be declared as any other defined constants rather 
than as static strings. 

NOTE
This module and the supporting BSP files assume that, at most, one
ne2000End driver unit will be configured, initialized, and loaded
to the MUX.  Additional entries in the END device table, <endDevTbl>,
in the BSP configNet.h file are not sufficient to load additional
driver and device instances to the MUX in the case of the ne2000End
driver.
*/
#include "config.h"

#if defined(INCLUDE_ENE_END)

/* includes */

#include "end.h"


/* defines */

#define ENE_BYTE_ACCESS    (FALSE)  /* set to enforce 8 bit */
#define ENE_USE_ENET_PROM  (TRUE)   /* set to use prom enet adrs */
#define ENE_OFFSET         (0)      /* memory offset for alignment */

#ifndef ENE_MAX_DEV
#define ENE_MAX_DEV        (1)      /* max number of devices configured */
#endif /* ENE_MAX_DEV */


/* globals */
#define NENE 2

char ne2000EnetAddr[NENE][6]={             /* place holder for driver */
{0x00,0xac,0x1E,0xc1,0xf8,0x80},
{0x00,0xac,0x1E,0xc1,0xf8,0x80},
};

struct ne2Resource{
	int ioAddr;
	int irq;
	BOOL byteAccess;
	BOOL useEnetProm;
	int offset;
	void * devCtrl;
};

struct ne2Resource ne2Resources[NENE]=
{
	//{0x320,10,0,0,0},
	//{0x300,11,0,0,0},
	{0x300,3,0,0,0},
	{0x320,5,0,0,0},
};

#include "ne2000End.c"

/******************************************************************************
*
* sysNe2000EndLoad - construct a load string and load an Ne2000 device
*
* This routine will be invoked by the MUX for the purpose of loading an
* ne2000End (ene) device with initial parameters.  This routine is
* constructed as an interface wrapper for the driver load routine.  Thus,
* the arguments and return values are consistent with any xxxEndLoad()
* routine defined for an END driver and the MUX API.
*
* INTERNAL
* The muxDevLoad() operation calls this routine twice.  A zero length
* <pParamStr> parameter string indicates that this is the first time
* through this routine.  The driver load routine should return the
* driver name in <pParamStr>.
*
* On the second pass though this routine, the initialization parameter
* string is constructed.  Note that on the second pass, the <pParamStr>
* consists of a colon-delimeted END device unit number and rudimentary
* initialization string (often empty) constructed from entries in the
* BSP END Device Table such that:
*
*     <pParamStr> = "<unit>:<default initialization string>"
*
* In the process of building the rest of <pParamStr>, the prepended unit
* number must be preserved and passed to the driver load routine.  The
* <default initialization string> portion mentioned above is discarded,
* but future versions of this routine may use it.
*
* The complete ne2000End driver load string has format:
*
*     <unit>:<adrs>:<ivec>:<iLvl>:<byteAccess>:<usePromEnetAddr>:<offset>
*
* RETURNS: An END object pointer, or NULL on error, or 0 and the name of the
* device if the <pParamStr> was NULL.
*
* SEE ALSO: ne2000EndLoad()
*/
END_OBJ * sysNe2000EndLoad
    (
    char *    pParamStr,   /* pointer to initialization parameter string */
    void *    unused       /* unused optional argument */
    )
    {
    END_OBJ * pEnd;
    char      paramStr [END_INIT_STR_MAX];

    static const char * const paramTemplate = "%d:%#x:%#x:%#x:%d:%d:%#x";

/* hack for a/b keyswitch settings*/
	ne2000EnetAddr[0][5]=sysGetA_BSetting()?0x8b : 0x8a;
	ne2000EnetAddr[1][5]=ne2000EnetAddr[0][5];
	
    if (strlen (pParamStr) == 0)
        {
        /* PASS (1)
         * The driver load routine returns the driver name in <pParamStr>.
         */

        pEnd = ne2000EndLoad (pParamStr,0);
        }
    else
        {
        /* PASS (2)
         * The END <unit> number is prepended to <pParamStr>.  Construct
         * the rest of the driver load string by appending parameters to
         * the END <unit> number.
         */

		char * holder  = NULL;
		int    endUnit = atoi (strtok_r (pParamStr, ":", &holder));
		struct ne2Resource * r;
		if(endUnit<0 || endUnit >= NENE){
			return 0;
		}
		r=ne2Resources+endUnit;


        /* finish off the initialization parameter string */
/*
        sprintf (paramStr, paramTemplate,
                 endUnit,
                 IO_ADRS_ENE,
                 INT_NUM_GET (INT_LVL_ENE),
                 INT_LVL_ENE,
                 ENE_BYTE_ACCESS,
                 ENE_USE_ENET_PROM,
                 ENE_OFFSET);
*/
        sprintf (paramStr, paramTemplate,
                 endUnit,
                 r->ioAddr,
                 r->irq+INT_NUM_IRQ0,
                 r->irq,
                 r->byteAccess,
                 r->useEnetProm,
                 r->offset
                 );
        if ((pEnd = ne2000EndLoad (paramStr,0)) == (END_OBJ *) NULL)
            {
            printf ("Error ne2000EndLoad:  failed to load driver.\n");
            }
		r->devCtrl = pEnd;
        }

    return (pEnd);
    }

STATUS sysIoChannelHook(int c, STATUS (*hook)(int, char *, int))
{
	((NE2000END_DEVICE*)ne2Resources[c].devCtrl)->recvHook=hook;
	return OK;
}

STATUS sysIoChannelUnhook(int c)
{
	((NE2000END_DEVICE*)ne2Resources[c].devCtrl)->recvHook=0;
	return OK;
}

STATUS sysIoChannelEnable(int c)
{
	IMPORT STATUS sysLanIntEnable();
	return sysLanIntEnable (ne2Resources[c].irq); 
}

STATUS sysIoChannelDisable(int c)
{
	IMPORT STATUS sysLanIntDisable();
	return sysLanIntDisable (ne2Resources[c].irq); 
}

STATUS sysWriteNe2000(int c, void * d, int len, int timeout)
{
	return ne2000SendDirect(ne2Resources[c].devCtrl, d, len,timeout);
}

void ne2000_hook(int c)
{
	ne2000Int(ne2Resources[c].devCtrl);
}
#endif /* INCLUDE_ENE_END */

