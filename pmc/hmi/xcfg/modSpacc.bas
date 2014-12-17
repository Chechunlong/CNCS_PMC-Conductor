Attribute VB_Name = "modSpacc"
Option Explicit

'=======================================================================
'declare in C language
'
'int LIBSPAC_API init_spac();
'int LIBSPAC_API uninit_spac();
'int LIBSPAC_API lock_port(int PortNum, int TimeOut);
'int LIBSPAC_API unlock_port(int PortNum);
'int LIBSPAC_API read_port(int pno, char * buf, int *size,int timeout);
'int LIBSPAC_API write_port(int pno, char * buf, int size,int timeout);
'=======================================================================

Declare Function init_spac Lib "libspac.dll" () As Long
Declare Function uninit_spac Lib "libspac.dll" () As Long
Declare Function lock_port Lib "libspac.dll" (ByVal pno As Long, ByVal timeout As Long) As Long
Declare Function unlock_port Lib "libspac.dll" (ByVal pno As Long) As Long
Declare Function read_port Lib "libspac.dll" (ByVal pno As Long, ByRef buf As Byte, ByRef size As Long, ByVal timeout As Long) As Long
Declare Function write_port Lib "libspac.dll" (ByVal pno As Long, ByRef buf As Byte, ByVal size As Long, ByVal timeout As Long) As Long

