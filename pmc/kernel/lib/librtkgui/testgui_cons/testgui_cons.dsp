# Microsoft Developer Studio Project File - Name="testgui_cons" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=testgui_cons - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testgui_cons.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testgui_cons.mak" CFG="testgui_cons - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testgui_cons - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "testgui_cons - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "testgui_cons - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f testgui_cons.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "testgui_cons.exe"
# PROP BASE Bsc_Name "testgui_cons.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\..\..\scripts\bld RELEASE -C lib/rtkgui/testgui_cons"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../../../target/win32/bin/testgui_cons.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "testgui_cons - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f testgui_cons.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "testgui_cons.exe"
# PROP BASE Bsc_Name "testgui_cons.bsc"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "..\..\..\scripts\bld DEBUG -C lib/rtkgui/testgui_cons"
# PROP Rebuild_Opt "clean all"
# PROP Target_File "../../../target/win32/bin/testgui_cons.exe"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "testgui_cons - Win32 Release"
# Name "testgui_cons - Win32 Debug"

!IF  "$(CFG)" == "testgui_cons - Win32 Release"

!ELSEIF  "$(CFG)" == "testgui_cons - Win32 Debug"

!ENDIF 

# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\testshl_cons.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Makefile
# End Source File
# End Target
# End Project
