/* usrAppInit.c - stub application initialization routine */

/* Copyright 1984-1998 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,02jun98,ms   written
*/

/*
DESCRIPTION
Initialize user application code.
*/ 

#if 0
#define DEPLOY
#endif

#include "vxworks.h"
#include "taskLib.h"
#include "drv/pci/pciConfigLib.h"
#include <taskLib.h>
#include <timers.h>
#include <netinet/in.h>
#include <ftpLib.h>
#include <stdio.h>
#include <loadLib.h>
#include <symLib.h>
#include <sysSymTbl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cbioLib.h>
#include <ramdiskCbio.h>
#include <dosfsLib.h>
#include <syslib.h>
#include <etherLib.h>

#define BUF_SIZE 1300

#define BOOT_DEV "/c"
#define RAM_DRIVE "/ram"

CBIO_DEV_ID ramDiskDev;
char f8ImagePath[256];

int hostexec(const char * url, const char * entryName, int a,int b,int c,int d)
{
	int fd, ctrlFd, diskFd;
	int status;
	MODULE_ID mid;
	int nBytes;
	char * execEntry;
	SYM_TYPE entryType;
	char * buf;
	int totalBytes;
	
	buf = malloc(BUF_SIZE);
	if(!buf){
		printf("Error allocating memory in %s.\n", __FUNCTION__);
		return -1;
	}

	diskFd = creat(RAM_DRIVE "/tmp.out", O_RDWR);
	if(diskFd == ERROR){
		printf("Cannot open disk image of executive.\n");
		free(buf);
		return -2;
	}
	
	status = ftpXfer(
		sysBootParams.had, 
		sysBootParams.usr, 
		sysBootParams.passwd, 
		"", 
		"RETR %s", 
		"", 
		url,
		&ctrlFd,
		&fd
	);
	if(status == ERROR){
		printf("Error locating program `%s'.\n", url);
		close(diskFd);
		free(buf);
 		return -3;
	}
	totalBytes = 0;
	/* copy from FTP to disk file */
	while ((nBytes = read (fd, buf, BUF_SIZE)) > 0){
		write(diskFd, buf, nBytes);
		totalBytes += nBytes;
	}

	printf("Image transferred %d bytes to %s.\n", totalBytes, RAM_DRIVE "/tmp.out");

	close (fd);

	if (nBytes < 0)
		status = ERROR;

	if (ftpReplyGet (ctrlFd, TRUE) != FTP_COMPLETE)
		status = ERROR;

	if (ftpCommand (ctrlFd, "QUIT", 0, 0, 0, 0, 0, 0) != FTP_COMPLETE)
		status = ERROR;

	close (ctrlFd);

	if(status == ERROR){
		printf("Error transferring program `%s'.\n", url);
		// close(diskFd);
		// free(buf);
		// return -4;
	}

	free(buf);
	lseek(diskFd, 0, SEEK_SET);

	mid = loadModule(diskFd, GLOBAL_SYMBOLS);
	if(mid == NULL){
		printf("Error loading program, code 0x%08x.\n", errno);
		close(diskFd);
		return -5;
	}
	printf("Program loaded successfully at 0x%08x.\n", mid);

	sprintf(f8ImagePath,"host://%s\n",url);
	
	status = symFindByName(sysSymTbl, entryName, &execEntry, &entryType);
	if(status == ERROR){
		printf("Error locating entry point of program, code 0x%08x.\n", errno);
		close(diskFd);
		return -6;
	}

	close(diskFd);

	printf("Executing '%s:%s' at 0x%08x....\n", url, entryName, execEntry);

	((void (*)(int,int,int,int))execEntry) (a,b,c,d);

	return 0;
}

int localexec(const char * url,const char * entryName,int a,int b,int c,int d)
{
	int diskFd;
	int status;
	MODULE_ID mid;
	int nBytes;
	char * execEntry;
	SYM_TYPE entryType;
	char * buf;
	int totalBytes;

	/* start from hard disk */
	diskFd = open(url, O_RDONLY, 0);
	if(diskFd == ERROR){
		printf("Error locating program.\n");
		return -1;
	}

	mid = loadModule(diskFd, GLOBAL_SYMBOLS);
	if(mid == NULL){
		printf("Error loading program, code 0x%08x.\n", errno);
		close(diskFd);
		return -2;
	}
	printf("Program loaded successfully at 0x%08x.\n", mid);

	sprintf(f8ImagePath,"local://%s\n",url);
	
	status = symFindByName(sysSymTbl, entryName, &execEntry, &entryType);
	if(status == ERROR){
		printf("Error locating entry point of %s, code 0x%08x.\n", entryName, errno);
		close(diskFd);
		return -3;
	}

	close(diskFd);

	printf("Starting '%s:%s' at 0x%08x....\n", url, entryName, execEntry);

	((void (*)(int,int,int,int))execEntry) (a,b,c,d);

	return 0;
}

/*
	sample config line:
	rtl 0 10.1.0.4 f8 255.0.0.0
*/
int initInterface(const char * _configLine)
{
	char *devName;
	int unitNum;
	char *ifAddr;
	char *hostName;
	int netMask;
	char * p;
	char configLine[256];

	strncpy(configLine, _configLine, sizeof(configLine));
	configLine[sizeof(configLine) - 1] = '\0';
	printf("Loading %s\n", configLine);
	devName = strtok(configLine, " \n\r");
	if(!devName){
		return ERROR;
	}
	p = strtok(NULL, " \r\n");
	if(!p){
		return ERROR;
	}
	unitNum = atoi(p);
	ifAddr = strtok(NULL, " \r\n");
	if(!ifAddr){
		return ERROR;
	}
	hostName = strtok(NULL, " \r\n");
	if(!hostName){
		return ERROR;
	}
	p = strtok(NULL, " \r\n");
	if(!p){
		return ERROR;
	}
	sscanf(p, "%x", &netMask);
	if (ipAttach(unitNum, devName) != OK){
		printf ("Failed to attach to END device %s\n", devName);
		return;
	}
	/* printf("calling netConfig(%s,%d,%s,%s,%08x[%s])\n", devName, unitNum, ifAddr, hostName, netMask, p); */
	if(usrNetIfConfig(devName, unitNum, ifAddr, hostName, netMask) == ERROR){
		fprintf(stderr, "Error configuring %s:%d, code %08x\n", devName, unitNum, errno);
		return ERROR;
	}

	return OK;
}

double time_diff(const struct timespec * t1, const struct timespec * t2)
{
	return t1->tv_sec-t2->tv_sec + (t1->tv_nsec - t2->tv_nsec)/1e9;
}

void initRamDrives()
{
	ramDiskDev = ramDiskDevCreate(0, 512, 16, 2*1024*10, 0);
	dosFsDevCreate(RAM_DRIVE, ramDiskDev, 0, NONE);
	dosFsVolFormat(ramDiskDev, DOS_OPT_BLANK | DOS_OPT_FAT16 | DOS_OPT_QUIET, NULL);	
}

extern void sysHwInitOthers();

void shellInitHook()
{
	/*
		2005-9-6 raise net task's priority to highest, as many tasks
		are dependant on this task.
	*/
	int taskId;
	taskId = taskNameToId("tNetTask");
	if(taskId != ERROR){
		taskPrioritySet(taskId, 10);
	}
	taskId = taskNameToId("tShell");
	if(taskId != ERROR){
		taskPrioritySet(taskId, 52);
	}
	// initInterfaces();
	initRamDrives();
	sysHwInitOthers();
	intStackEnable();
}

BOOL systemStarted;

/******************************************************************************
*
* usrAppInit - initialize the users application
*/ 
void usrAppInit (void)
{
	sysEnableIrqMonitor(-1);
	// make reference to ethernet library so linker will not discard them
	{
	char buf[128];
	sprintf(buf, "%x,%x,%x", etherOutput,etherInputHookAdd, etherInputHookDelete);
	}
	sysOutByte(0x280,1);
	sysOutByte(0x281,1);
	sysOutByte(0x282,1);
	sysOutByte(0x283,0);
	systemStarted=TRUE;
}

void mm()
{
	 hostexec("f8kernel.out","ex_main_x",0,0,0,0);
}

void mmm()
{
	localexec("/d/f8kernel.out","ex_main_x",0,0,0,0);
}

