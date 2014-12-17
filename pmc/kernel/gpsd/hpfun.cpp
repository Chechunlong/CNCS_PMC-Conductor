//调整对时权利
bool EnableAdjustTimePrivilege(bool bEnable)
{
	HANDLE hProcess=GetCurrentProcess();
	HANDLE hToken;

	if(!OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,&hToken)) return false;

	TOKEN_PRIVILEGES tpNew;
	if(!LookupPrivilegeValue(NULL,SE_SYSTEMTIME_NAME,&tpNew.Privileges[0].Luid)) return false;

	if(bEnable) tpNew.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
	else tpNew.Privileges[0].Attributes=0;
	tpNew.PrivilegeCount=1;
		
	if(!AdjustTokenPrivileges(hToken,FALSE,&tpNew,0,NULL,NULL)) return false;

	return true;
}
