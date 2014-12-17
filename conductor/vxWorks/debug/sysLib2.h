/*
* utility functions for VxWorks
* william.pan@kcn
* 
* jan04,panxiaohui@actech-mc.com created
*/

#ifndef __syslib2_h__
#define __syslib2_h__

#ifndef __VXWORKS__
#define __VXWORKS__ 0x551
#endif

#include "stdint.h"
#ifndef __ASSEMBLER__
typedef unsigned long long uint64_t;
#endif

/*
* ---------------  pentium specific routines
*/
#define wrmsr(c,d,a) \
	__asm__ __volatile__(\
	"wrmsr" \
	: \
	:"c"(c),"d"(d),"a"(a) \
	)

#define rdmsr(c,d,a) \
	__asm__ __volatile__(\
	"rdmsr" \
	:"=d"(d),"=a"(a) \
	:"c"(c) \
	)

#ifndef __ASSEMBLER__

#ifdef __cplusplus
extern "C"{
#endif

extern void sysRdmsr(uint32_t idx,uint32_t *d,uint32_t *a);
extern void sysWrmsr(uint32_t idx,uint32_t d,uint32_t a);

extern void sysPatchPentiumTscDriver(int protected);
extern uint64_t tscFrequency;
extern uint_t microsecondCount;
extern void sysClkInt (void);
extern void sysStallExecutionProcessor(int microseconds);
extern uint64_t sysCalibrateCpu();

/*
* ----------- console debug routines 
*/
int sysSetBootFlag(int flag);
int sysResetBootFlag(int flag);
int sysGetBootFlag();

extern int sysDebugTrace(unsigned int code);
extern int sysDisplayStringOnSerial(const char * s);
extern int sysDisplayString(const char * s);
extern int sysPrintf(const char * fmt, ...);
extern int consoleSerialPort;
int sysPrintOnConsole(int x, int y, const char * fmt,...);
extern int sysBugCheck(int code);
extern void sysHwInitOthers();
extern void sysSetTimerProc();
extern void sysDelayMs(int milliseconds);
extern double sysTimeMark();
extern uint64_t sysTimeMarkUs();
extern void sysHwTest();
extern void sysPrintBinary(uint32_t b);
int sysGetChar();
void sysMsgWaitChar(int ch, const char *fmt,...);
void sysDumpIoSpace(unsigned int buf, int len);
void sysDumpBuf(void * buf, int len);

#if __VXWORKS__ < 0x550
typedef STATUS (*PCI_FOREACH_FUNC)(int bus, int dev, int func, void *pArg);
STATUS pciConfigForeachFunc
    (
    UINT8 bus,			    /* bus to start on */
    BOOL recurse,		    /* if TRUE, do subordinate busses */
    PCI_FOREACH_FUNC funcCheckRtn,  /* routine to call for each PCI func */
    void *pArg			    /* argument to funcCheckRtn */
    );
#endif
extern int sysDebugIndentLevel;

#if __VXWORKS__ > 0x540
/*
* start a new line of trace message
* indent 2 spaces every level
*/
#define SYS_PRINTF_INDENTED(l,...)\
	do{\
		int level = l;\
		for(;level;level--) sysPrintf("  ");\
		sysPrintf(__VA_ARGS__);\
	}while(0)

#define SYS_DEBUG_ENTER_FUNC() \
	do{\
		SYS_PRINTF_INDENTED(sysDebugIndentLevel, ("Entering %s\n", __FUNCTION__));\
		sysDebugIndentLevel++;\
	}while(0)
	
#define SYS_DEBUG_LEAVE_FUNC() \
	do{\
		sysDebugIndentLevel--;\
		SYS_PRINTF_INDENTED(sysDebugIndentLevel, ("Leaving %s\n", __FUNCTION__));\
	}while(0);\

#define SYS_TRACE_LINE(...)\
	sysPrintf("Here %s!%s@%d\n", __FILE__,__FUNCTION__,__LINE__);\
	sysPrintf(__VA_ARGS__)

#define __HERE__() SYS_TRACE_LINE("")
#else
#define __HERE__() sysPrintf("Here %s!%s@%d\n", __FILE__,__FUNCTION__,__LINE__);
#endif

/*
* linux-like macros
*/
#define inb(p) ({uint8_t v;__asm__ __volatile__("in %%dx,%%al\n":"=a"(v):"d"(p));v;})
#define inw(p) ({uint16_t v;__asm__ __volatile__("in %%dx,%%ax\n":"=a"(v):"d"(p));v;})
#define inl(p) ({uint32_t v;__asm__ __volatile__("in %%dx,%%eax\n":"=a"(v):"d"(p));v;})
#define outb(v,p) __asm__ __volatile__("out %%al, %%dx\n"::"a"(v),"d"(p));
#define outw(v,p) __asm__ __volatile__("out %%ax, %%dx\n"::"a"(v),"d"(p));
#define outl(v,p) __asm__ __volatile__("out %%eax, %%dx\n"::"a"(v),"d"(p));

struct msr_value_t{
	int idx;
	uint32_t d,a;
};

struct pci_irq_t{
	int b,d,f;
	int irq;
};

/* source and dest must be 128-bit aligned */
void memcpy_sse2(void * dest, const void * src, int len);
int memset_sse2(void * dest, char c, int len);
void memcpy_sse(void * dest, const void * src, int len);
int memset_sse(void * dest, char c, int len);

int kcnGetPhysicalMemTop();
void kcnInitIrqHook(void (*p)());
void kcnIdtShow(int v);


#ifdef __cplusplus
}
#endif

#endif // __ASSEMBLER__

#endif


