/*
* 8259-mode irq debugging code
* william.pan@kontron.cn, nov07
*/
#include "sysLib2.h"
#include <string.h>
#include <intLib.h>
#include <memLib.h>
#include <stdio.h>
#include "inline_asm.h"

#define IVEC_TO_INUM(intVec)	((int) (intVec) >> 3)
#define INUM_TO_IVEC(intNum)	((VOIDFUNCPTR *) ((intNum) << 3))
#define INT_NUM_IRQ0 0x20

struct int_stat_t{
	unsigned int count;
};
struct int_stat_t intStats[24];

struct hook_thunk_t {
	int param;
	int vector;
	VOIDFUNCPTR func;
	int type;
	UCHAR code[128];
	int irq;
};

uint16_t sysDebugEoiMask = 0;
char sysIrqMonitorEnabled=0;

void sysEnableIrqMonitor(int e)
{
	sysIrqMonitorEnabled=e;
}

static void dumpIrqStats()
{
	int i,j;
	struct int_stat_t * s;
	s=intStats;
	memset((void*)0xb8000,0,80*4*2);
	for(i=0;i<4;i++){
		for(j=0;j<4;j++,s++){
			sysPrintOnConsole(j*15,i,"IRQ[%02d]=%d\t",i*4+j,s->count);
		}
	}
	sysPrintOnConsole(0,4,"8259-MASK=%02x-%02x",inb(0x21),inb(0xa1));
}

static void eoi_thunk(struct hook_thunk_t *t)
{
	static int count;
	int c = count++;
	intStats[t->param].count++;
	if (sysDebugEoiMask & (1 << t->param))
		sysPrintf("NO.%d: IRQ%d \r\n", c, t->irq);
	if (t->func)
		t->func(t->param);
	if(!(count & 0xf)  && sysIrqMonitorEnabled)
		dumpIrqStats();
}

__asm__(
	"eoi_func_thunk:\n"
	"call 1f\n"
	"1:\n"
	"pop %eax\n"
	"sub $21,%eax\n"
	"push %eax\n"
	"lea eoi_thunk,%eax\n" 
	"call *%eax\n" 
	"add $4,%esp\n" 
	"ret\n"
);

typedef void (*INT_EOI_GET_PROC)(VOIDFUNCPTR * vector,
						VOIDFUNCPTR * routineBoi,
						int *parameterBoi,
						VOIDFUNCPTR * routineEoi,
						int *parameterEoi);

LOCAL INT_EOI_GET_PROC sysIntEoiGetProc;
IMPORT VOIDFUNCPTR intEoiGet;	/* BOI/EOI function pointer */
LOCAL void kontronIntEoiGet(VOIDFUNCPTR * vector,	/* interrupt vector to attach to */
						VOIDFUNCPTR * routineBoi,	/* BOI function */
						int *parameterBoi,	/* a parameter of the BOI function */
						VOIDFUNCPTR * routineEoi,	/* EOI function */
						int *parameterEoi	/* a parameter of the EOI function */
	)
{
	struct hook_thunk_t *t;
	extern char eoi_func_thunk[];
	sysIntEoiGetProc(vector, routineBoi, parameterBoi, routineEoi,
				  parameterEoi);
	t = memalign(_CACHE_ALIGN_SIZE, sizeof(*t));
	memcpy(t->code, eoi_func_thunk, 128);
	t->param = *parameterEoi;
	t->irq=*parameterEoi;
	t->type = 2;
	t->func = *routineEoi;
	t->vector = (int) *vector;
	*routineEoi = (VOIDFUNCPTR) t->code;
}

void kcnInitIrqHook(VOIDFUNCPTR p)
{
	intEoiGet=kontronIntEoiGet;
	sysIntEoiGetProc=(INT_EOI_GET_PROC)p;
}

/*
* dump idt
*/
void kcnIdtShow(int v)
{
	uint16_t _idt[3];
	uint16_t * idt;
	int i,vv;
	__asm__ __volatile__("sidt %0\n":"=g"(_idt):);
	idt=(int *)(*((int*)&_idt[1]));
	if(v==0){
		for(i=0;i<256;i++,idt+=4){
			printf("Int%03d=%08x\n",i,(idt[3]<<16) | idt[0]);
		}
		return;
	}
	/* negative number denotes IRQ */
	if(v<0)
		vv=-v+0x20;
	else
		vv=v;
	if(vv>=256){
		printf("Invalid interrupt number.\n");
		return;
	}
	idt+=vv*4;
	printf("%s%03d=%08x\n",v<0?"IRQ" : "INT", v<0? -v : v, (idt[3]<<16) | idt[0]);
}

