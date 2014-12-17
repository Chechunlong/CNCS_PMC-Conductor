# Microsoft Developer Studio Project File - Name="MCDraw" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MCDraw - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MCDraw.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MCDraw.mak" CFG="MCDraw - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MCDraw - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MCDraw - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MCDraw - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\proj\target\bin"
# PROP Intermediate_Dir "\proj\temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "\proj\inc_all" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /I /pmc2/sdk/include" " /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /libpath:"\proj\imp_all"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "MCDraw - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\proj\target\bin"
# PROP Intermediate_Dir "\proj\temp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "\proj\inc_all" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /I /pmc2/sdk/include" /GZ " /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../target/win32/bin" /libpath:"\proj\imp_all"
# SUBTRACT LINK32 /profile /pdb:none

!ENDIF 

# Begin Target

# Name "MCDraw - Win32 Release"
# Name "MCDraw - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DiaBlink.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaButtonA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaButtonD.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaButtonWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaCellAttr.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaColorA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaColorAA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaColorD.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaColorDA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaDirection.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaDnyAttr.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaEnable.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaFillH.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaFillV.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaInputA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaInputD.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaPosH.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaPosV.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaReplace.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSave.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSizeH.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSizeV.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSlideH.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaSlidV.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaTrendAttr.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaValueA.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaValueD.cpp
# End Source File
# Begin Source File

SOURCE=.\DiaVisibility.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MCDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\MCDraw.rc
# End Source File
# Begin Source File

SOURCE=.\MCDrawDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\MCDrawView.cpp
# End Source File
# Begin Source File

SOURCE=.\OptGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\OptShow.cpp
# End Source File
# Begin Source File

SOURCE=.\OptWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Arc.h
# End Source File
# Begin Source File

SOURCE=.\Button.h
# End Source File
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# Begin Source File

SOURCE=.\Cursor.h
# End Source File
# Begin Source File

SOURCE=.\DiaBlink.h
# End Source File
# Begin Source File

SOURCE=.\DiaButtonA.h
# End Source File
# Begin Source File

SOURCE=.\DiaButtonD.h
# End Source File
# Begin Source File

SOURCE=.\DiaButtonWnd.h
# End Source File
# Begin Source File

SOURCE=.\DiaCellAttr.h
# End Source File
# Begin Source File

SOURCE=.\DiaColorA.h
# End Source File
# Begin Source File

SOURCE=.\DiaColorAA.h
# End Source File
# Begin Source File

SOURCE=.\DiaColorD.h
# End Source File
# Begin Source File

SOURCE=.\DiaColorDA.h
# End Source File
# Begin Source File

SOURCE=.\DiaDirection.h
# End Source File
# Begin Source File

SOURCE=.\DiaDnyAttr.h
# End Source File
# Begin Source File

SOURCE=.\DiaEnable.h
# End Source File
# Begin Source File

SOURCE=.\DiaFillH.h
# End Source File
# Begin Source File

SOURCE=.\DiaFillV.h
# End Source File
# Begin Source File

SOURCE=.\DiaInputA.h
# End Source File
# Begin Source File

SOURCE=.\DiaInputD.h
# End Source File
# Begin Source File

SOURCE=.\DiaPosH.h
# End Source File
# Begin Source File

SOURCE=.\DiaPosV.h
# End Source File
# Begin Source File

SOURCE=.\DiaReplace.h
# End Source File
# Begin Source File

SOURCE=.\DiaSave.h
# End Source File
# Begin Source File

SOURCE=.\DiaSelect.h
# End Source File
# Begin Source File

SOURCE=.\DiaSizeH.h
# End Source File
# Begin Source File

SOURCE=.\DiaSizeV.h
# End Source File
# Begin Source File

SOURCE=.\DiaSlideH.h
# End Source File
# Begin Source File

SOURCE=.\DiaSlidV.h
# End Source File
# Begin Source File

SOURCE=.\DiaTrendAttr.h
# End Source File
# Begin Source File

SOURCE=.\DiaValueA.h
# End Source File
# Begin Source File

SOURCE=.\DiaValueD.h
# End Source File
# Begin Source File

SOURCE=.\DiaVisibility.h
# End Source File
# Begin Source File

SOURCE=.\Dnyattr.h
# End Source File
# Begin Source File

SOURCE=.\Element.h
# End Source File
# Begin Source File

SOURCE=.\Ellipse.h
# End Source File
# Begin Source File

SOURCE=.\Line.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MCDraw.h
# End Source File
# Begin Source File

SOURCE=.\MCDrawDoc.h
# End Source File
# Begin Source File

SOURCE=.\MCDrawView.h
# End Source File
# Begin Source File

SOURCE=.\Meta.h
# End Source File
# Begin Source File

SOURCE=.\OptGrid.h
# End Source File
# Begin Source File

SOURCE=.\OptShow.h
# End Source File
# Begin Source File

SOURCE=.\OptWindow.h
# End Source File
# Begin Source File

SOURCE=.\Polygon.h
# End Source File
# Begin Source File

SOURCE=.\PolyLine.h
# End Source File
# Begin Source File

SOURCE=.\Rectangle.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RoundRect.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\Trend.h
# End Source File
# Begin Source File

SOURCE=.\Zoom.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\line1a1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\line1a9.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linenull.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linesoli.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MCDraw.ico
# End Source File
# Begin Source File

SOURCE=.\res\MCDraw.rc2
# End Source File
# Begin Source File

SOURCE=.\res\MCDrawDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z12.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z13.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z14.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z15.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z17.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z18.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z19.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z20.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z21.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z5.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z6.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z7.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\z9.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
