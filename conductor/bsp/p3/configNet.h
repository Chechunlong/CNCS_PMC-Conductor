/* configNet.h - Network configuration header file */

/* Copyright 1984-2002 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,25apr02,rhe  Added C++ Protection
01k,23apr02,pai  Made DEC and GEI END driver config names consistent with
                 other END driver config names.
01j,22oct01,pai  Cleaned up formatting and set XXX_BUFF_LOAN to TRUE, as
                 this is formally a kind of Boolean value.
01i,18oct01,jln  added support for GEI8254X END driver
01h,26sep01,pai  Added support for dec21x40End driver.
01g,31mar99,dat  SPR 25958, added #ifndef IP_MAX_UNITS
01f,12mar99,cn   added support for SMC el3c90xEnd driver (SPR# 25327).
01e,08mar99,sbs  added support for SMC Elite Ultra card.(SPR #25234)
                 changed elt3c509 end support to use sysElt3c509End routine
                 added support for ne2000End driver (SPR #25398)
01d,01feb99,jkf  added support for AMD 7997x PCI card.
01c,26nov98,ms_  add support for end enabled elt3c509
01b,12nov98,dat  added INCLUDE_FEI_END around fei unit 0 entry
01a,31mar98,cn   written.
*/

#ifndef INCconfigNeth
#define INCconfigNeth

#ifdef __cplusplus
extern "C" {
#endif

#include "vxWorks.h"
#include "end.h"

IMPORT END_TBL_ENTRY endDevTbl [];

/* max number of END ipAttachments we can have */

#ifndef IP_MAX_UNITS
#define IP_MAX_UNITS 3
#endif

#ifdef __cplusplus
}
#endif

#endif /* INCconfigNeth */

