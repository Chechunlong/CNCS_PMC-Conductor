#include <assert.h>

int sysDebugTrace(int code)
{
	__asm__(
		"pushl %%eax\n"
		"pushl %%ecx\n"
		"pushl %%edx\n"
		"movw $0x80, %%dx\n"
		"mov %0, %%eax\n"
		"movl $4, %%ecx\n"
	"next:\n"
		"outb %%al, %%dx\n"
		"inc %%dx\n"
		"shrl $1, %%eax\n"
		"loopnz next\n"
		"popl %%edx\n"
		"popl %%ecx\n"
		"popl %%eax\n"
		:
		:"g"(code)
		);
	return 0;
}

long long tscFrequency;
int microsecondCount;

extern void sysClkInt (void);

/*
	disable wind river's default behaviour on TSC(reset each clock tick)
	warning : target server wll complain on the mismatched checksum
	between core file and target.
*/
LOCAL void patchPentiumTscDriver()
{
	int level;
	int pageAddr;
	STATUS code;
	UINT st;
	level = intLock();
	pageAddr = (int)sysClkInt & ~(VM_PAGE_SIZE-1);
	code=vmStateGet(0, (void*)pageAddr, &st);
	vmStateSet (0, (void*)pageAddr, VM_PAGE_SIZE, VM_STATE_MASK_WRITABLE, VM_STATE_WRITABLE);
	if(code == OK){
		vmStateSet(0, (void*)pageAddr, VM_PAGE_SIZE, VM_STATE_MASK_WRITABLE, st);
	}
	((char*)sysClkInt)[0xe] = 0xeb;
	pentiumTscReset();
	intUnlock(level);
}

LOCAL void calibrateCpu()
{
	long long t1, t2;
	pentiumTscGet64(&t1);
	taskDelay(SYS_CLK_RATE / 2);
	pentiumTscGet64(&t2);
	tscFrequency = (t2 - t1)*2;
	microsecondCount = tscFrequency/1000000;
	printf("%.1f MHz CPU calibrated.\n", tscFrequency / 1e6);
}

void sysStallExecutionProcessor(int microseconds)
{
	long long t, t2;
	pentiumTscGet64(&t);
	if(microseconds > 1000000){
		t2 = t + (double)microseconds * microsecondCount;
	}else{
		t2 = t + (long long)microseconds * microsecondCount;
	}
	while(t < t2){
		pentiumTscGet64(&t);
	}
}

/*
	display a string by directly writing to video memory.
*/
int sysDisplayString(const char * s)
{
	static int x, y;
	int count=0;
	char * vMem=(char *)0xb8000, *p;
	p=vMem+y*80*2+x*2;
	while(*s){
		switch(*s){
		case '\n':
			y++;
			x=0;
			if(y==25){
				y=0;
			}
			p=vMem+y*80*2+x*2;
			memset(p,160,0);
			break;
		case '\r':
			x=0;
			p=vMem+y*80*2+x*2;
			break;
		case '\b':
			x--;
			p=vMem+y*80*2+x*2;
			break;
		default:
			*p=*s;
			p++;
			*p=7;
			p++;
			x++;
			if(x==80){
				x=0;
				y++;
				if(y==25){
					y=0;
				}
				p=vMem+y*80*2+x*2;
				memset(p,160,0);
			}
			break;
		}
		count++;
		s++;
	}
	return count;
}

int sysPrintf(const char * fmt, ...)
{
	va_list v;
	char buf[4096];
	va_start(v, fmt);
	vsprintf(buf, fmt, v);
	return sysDisplayString(buf);
}

int sysBugCheck(int code)
{
	sysPrintf("\nsysBugCheck(%08x)\n", code);
	__asm__("cli"::);
	sysDebugTrace(code);
	while(1);
	return 0;
}

void sysHwInitOthers()
{
	patchPentiumTscDriver();
	calibrateCpu();
}

void sysSetTimerProc()
{
}

void sysDelayMs(int milliseconds)
{
	int i,j;
	for(i=0;i<milliseconds;i++){
		for(j=0;j<1300;j++){
			sysDelay();
		}
	}
}

/*
panel key position
return 
0 -> stopped
1 -> running
2 -> locked
*/
int sysGetKeyPosition()
{
	/* N.A. yet */
	assert(0);
	return 0;
}

/*
return
0 -> station A 
1 -> station B
*/
int sysGetA_BSetting()
{
	if(sysInByte(0x244) & 0x01){
		return 0; 
	}else{
		return 1;	
	}
}

void sysEnableWatchdog(int timeout)
{
	return;
}

void sysRefreshWatchdog(int timeout)
{
	return;
}

void sysDisableWatchdog()
{
	return;
}

double sysTimeMark()
{
	long long t;
	pentiumTscGet64(&t);
	return (double)t/microsecondCount/1000;
}


