/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 14 21:13:35 2006
 */
/* Compiler settings for pmcdb_idl.idl:
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

const IID LIBID_pmcdb = {0x4a906362,0x612d,0x43fb,{0xa4,0xcb,0x93,0x87,0xfc,0xc1,0x30,0xe7}};


const IID IID_IPmcDB = {0xF35F7568,0x07D5,0x4137,{0xA9,0xC9,0xE8,0x73,0x7A,0x39,0x45,0x36}};


const IID DIID_IPmcDBEvents = {0x5F679D6F,0x6147,0x4865,{0x84,0x95,0xF2,0x8A,0x60,0x53,0x10,0xFA}};


#ifdef __cplusplus
}
#endif

