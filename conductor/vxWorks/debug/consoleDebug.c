#include <string.h>
#include <stdio.h>
#include "sysLib2.h"

extern int sysClkRateGet();

int sysDebugIndentLevel;

uint64_t tscFrequency;
uint_t microsecondCount;

int consoleSerialPort=0x2f8;

/* Data */
#define UART_RBR 0x00
#define UART_TBR 0x00

/* Control */
#define UART_IER 0x01
#define UART_IIR 0x02
#define UART_FCR 0x02
#define UART_LCR 0x03
#define UART_MCR 0x04
#define UART_DLL 0x00
#define UART_DLM 0x01

/* Status */
#define UART_LSR 0x05
#define UART_MSR 0x06
#define UART_SCR 0x07

extern void sysDelay();

void uart8250_init(unsigned base_port, unsigned divisor, unsigned lcs)
{
	lcs &= 0x7f;
	/* disable interrupts */
	outb(0x0, base_port + UART_IER);
	/* enable fifo's */
	outb(0x01, base_port + UART_FCR);
	/* assert DTR and RTS so the other end is happy */
	outb(0x03, base_port + UART_MCR);
	/* Set Baud Rate Divisor to 12 ==> 115200 Baud */
	outb(0x80 | lcs, base_port + UART_LCR);
	outb(divisor & 0xFF,   base_port + UART_DLL);
	outb((divisor >> 8) & 0xFF,    base_port + UART_DLM);
	outb(lcs, base_port + UART_LCR);
}

static void _out_charOnSerial(char c)
{
	static int base;
	if(base != consoleSerialPort){
		base=consoleSerialPort;
		uart8250_init(consoleSerialPort,1,3);
	}
	outb(c,consoleSerialPort);
	while(!(inb(consoleSerialPort+UART_LSR) & 0x40))
		sysDelay();
}

#define DMESG_BUFFER ((char*)0x80000)
#define DMESG_LEN 0x10000
static int dmesgX;

static void _out_charOnBuffer(char c)
{
	static char * p=DMESG_BUFFER;
	p+=dmesgX;
	*p++=c;
	if(dmesgX==DMESG_LEN)
		dmesgX=0;
}


static void _out_charOnConsoleXY(int *xx, int *yy, char c)
{
	char *vMem,*p;
	int tabSize=8,nextStop;
	
	vMem=(char *)0xb8000;
	p=vMem+*yy*80*2+*xx*2;

	switch(c){
	case '\n':
		memset(p,0,(80-*xx)*2);
		(*yy)++;
		*xx=0;
		if(*yy==25){
			*yy=0;
		}
		p=vMem+*yy*80*2;
		memset(p,0,160);
		break;
	case '\r':
		memset(p,0,(80-*xx)*2);
		*xx=0;
		p=vMem+*yy*80*2+*xx*2;
		break;
	case '\b':
		(*xx)--;
		p=vMem+*yy*80*2+*xx*2;
		break;
	case '\t':
		nextStop=(*xx+tabSize-1) & ~tabSize;
		while(*xx < nextStop){
			_out_charOnConsoleXY(xx,yy,' ');
		}
		break;
	default:
		*p=c;
		p++;
		*p=7;
		p++;
		(*xx)++;
		if(*xx==80){
			*xx=0;
			(*yy)++;
			if(*yy==25){
				*yy=0;
			}
			p=vMem+*yy*80*2+*xx*2;
			memset(p,160,0);
		}
		break;
	}
}

static void _out_charOnConsole(char c)
{
	static int x, y;
	_out_charOnConsoleXY(&x,&y,c);
}

static __inline__ void out_char(char c,int flags)
{
	if(flags & 0x1000)
		_out_charOnConsole(c);
	if(flags & 0x2000)
		_out_charOnSerial(c);
	if(flags & 0x4000)
		_out_charOnBuffer(c);
}

#include <tickLib.h>

static __inline__ void outputTimemark(int flags)
{
	char timeMark[32];
	char *p=timeMark;
#if 0
	if(microsecondCount){
		uint64_t tms;
		uint_t ts,tMs;
		tms=sysTimeMarkUs();
		tMs=tms/1000;
		ts=tMs/1000;
		sprintf(timeMark,"%03d.%03d.%03d - ",ts,tMs%1000,(uint_t)tms%1000);
	}else
#endif
	{
		int ticks=tickGet();
		int r=sysClkRateGet();
		/*
		* william.pan@kcn, mar07
		* in case tickLib is not initialized 
		*/
		if(r)
			sprintf(timeMark,"%04d.%03d - ",ticks/r,(ticks % r)*1000/r);
		else
			strcpy(timeMark,"----.--- - ");

	}
	while(*p){
		out_char(*p,flags);
		p++;
	}
}

void dmesg(int clear)
{
	printf("%s",DMESG_BUFFER);
	if(clear){
		*DMESG_BUFFER=0;
		dmesgX=0;
	}
}

void sysOutChar(char c,int flags)
{
	static int last;
	if(c=='\n' && last!='\r')
		sysOutChar('\r',flags);
	if(last=='\n'){
		outputTimemark(flags);
	}
	out_char(c,flags);
	last=c;
}

static __inline__ void _out_char(char c)
{
	sysOutChar(c,0x3000);
}

int sysGetChar()
{
	while(!(inb(consoleSerialPort+5)&1))
		sysDelay();
	return inb(consoleSerialPort);
}

void sysMsgWaitChar(int ch, const char *fmt,...)
{
	va_list v;
	char buf[256];
	va_start(v, fmt);
	vsprintf(buf, fmt, v);
	sysDisplayString(buf);
	while(sysGetChar() != ch)
		sysDelay();
}

/*
	display a string by directly writing to video memory.
*/
static int sysDisplayString(const char * s)
{
	const char * b=s;
	while(*s){
		_out_char(*s);
		s++;
	}
	return s-b;
}

static int sysPrintf(const char * fmt, ...)
{
	va_list v;
	char buf[256];
	va_start(v, fmt);
	vsprintf(buf, fmt, v);
	return sysDisplayString(buf);
}

int sysPrintOnConsole(int x, int y, const char * fmt,...)
{
	va_list v;
	char buf[256];
	const char * b=buf;
	char * s=buf;
	va_start(v, fmt);
	vsprintf(buf, fmt, v);
	while(*s){
		_out_charOnConsoleXY(&x,&y,*s);
		s++;
	}
	return s-b;
}
	


