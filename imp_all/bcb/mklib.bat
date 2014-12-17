@echo off

rem
rem 2003-5-24, definition file is no longer needed as all functions are now 
rem stdcall
rem 2003-5-25, it seems definition file are still desirable
rem

for %%f in (m8kern configman rtkproxy powermgr) do implib lib%%f.lib %%f.def
for %%f in (rtk ioss rtdb spac rtknet utils rtkgui) do implib lib%%f.lib %%f.def

rem for %%f in (m8kern configman rtkproxy powermgr) do implib lib%%f.lib ..\..\target\win32\bin\lib%%f.dll
rem for %%f in (rtk ioss rtdb spac rtknet utils) do implib lib%%f.lib ..\..\target\win32\bin\lib%%f.dll

for %%f in (utils rtkproxy rtknet) do implib lib%%f_bcb.lib %%f_bcb.def

rem for %%f in (rtkgui) do implib lib%%f.lib %%f.def