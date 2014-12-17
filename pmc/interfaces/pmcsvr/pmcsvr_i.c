/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu May 27 10:50:47 2010
 */
/* Compiler settings for C:\proj\pmc\interfaces\pmcsvr\pmcsvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_PMCSVRLIB = {0x7BCEC898,0x6F19,0x4F89,{0x9B,0x3D,0xAE,0x59,0xE3,0x00,0x1B,0xC6}};


const CLSID CLSID_OpcServer = {0x268F712B,0xCFC3,0x4D8A,{0x96,0xB4,0x70,0x69,0x37,0xB6,0x16,0x68}};


const CLSID CLSID_PmcDB = {0xBA7CE1FB,0xE5DE,0x4ffc,{0x80,0x44,0xBF,0x30,0x53,0x95,0x5F,0xCF}};


#ifdef __cplusplus
}
#endif

