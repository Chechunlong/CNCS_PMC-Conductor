/*
* F8 controller
* global database daemon
*/
#include "../../fkern/precomp.h"
#include <math.h>
#include <ctype.h>
#include <sockLib.h>
#include <ioLib.h>

#include <pshpack1.h>
struct gmem_slot_t{
	unsigned short flag;
	unsigned short addr;
	char data[32]; 
};

//wdt_new
struct sync_time_t{
	unsigned short flag;
	unsigned short time[9];
};

#include <poppack.h>

#define GSLOT_COUNT 32
#define OUT_SIZE sizeof(struct gmem_slot_t) * GSLOT_COUNT
#define OUT_SZ1 64
#define IN_SIZE 32 * 1024
#define GSLOT_VALID 0x55aa

//wdt_new
#define SYNC_TIME 0x55bb

#define ETHER_INTERFACE "rtl"
#define F8_DBSYNCD_PORT 10933

static void *p_out_mem;
static void *p_in_mem;
static double *p_time_offset;

char buf_in[IN_SIZE];
char buf_out[OUT_SIZE];
char buf_stop[OUT_SZ1] = "cpu - stop!";
char buf_standby[OUT_SZ1] = "cpu - standby!";
char buf_sync[OUT_SZ1] = "cpu - sync!";
static int tid_reader;
static int tid_writer;
static int tid_update;
static int task_flag;

#define DEF_FREQ 250
static int b_single = 1;
static int send_freq = DEF_FREQ;

static void sync_time(int year, int mon, int mday, int wday, int yday, int hour, int min, int sec, unsigned long ms){
	struct	timespec  set_ts;
	struct	tm  set_t;	
	struct	tm  *p_tm;
	double	tlocal, tset, offset, ww;

	tlocal = _irqh_gettime();

	set_t.tm_year = year - 1900;
	set_t.tm_mon = mon;
	set_t.tm_mday = mday;
	set_t.tm_wday = wday;
	set_t.tm_yday = yday;
	set_t.tm_hour = hour;
	set_t.tm_min = min;
	set_t.tm_sec = sec;
	set_t.tm_isdst = 0;
	set_ts.tv_sec = mktime(&set_t);
	set_ts.tv_nsec = ms*1000*1000;

	//printf("set_t: %d %d %d %d %d %d %d %d %d\n", set_t.tm_year, set_t.tm_mon, set_t.tm_mday, 
		//set_t.tm_wday, set_t.tm_yday, set_t.tm_hour, set_t.tm_min,set_t.tm_sec, ms);
	
	tset = (double)set_ts.tv_sec + (double)set_ts.tv_nsec/1000000000;
	ww = (double)((369*365)+89)*24*3600; 	//the number of seconds from 1600 to 1970
	offset = tset + ww - tlocal;	
	//printf("tlocal: %f, tset: %f, offset: %f, ww: %f\n\n", tlocal, tset, offset, ww);
	*p_time_offset = offset;
}

static void init_g_mem()
{
	while(!ke_lock(&g_kernel, 0)){
		taskDelay(10);
	}

	p_out_mem = g_kernel.x_memory + 120 * 1024; //(12 + 12 + 32 + 32 + 0 + 32) * 1024;
	p_in_mem = g_kernel.x_memory + 128 * 1024;
	p_time_offset = p_in_mem - 8;
	ke_unlock(&g_kernel, 0);
}

static void set_in_mem()
{
	int i, *p_mem, *p_buf;
	
	p_mem = p_in_mem;
	p_buf = (int*)buf_in;
	for(i = 0; i < IN_SIZE /4; i++){
		*p_mem = *p_buf;
		p_mem++;
		p_buf++;
	}
}

static void get_and_clear_out_mem()
{
	int i, *p_mem, *p_buf;
	
	p_mem = p_out_mem;
	p_buf = (int*)buf_out;
	for(i = 0; i < OUT_SIZE / 4; i++){
		*p_buf = *p_mem;
		*p_mem = 0;
		p_mem++;
		p_buf++;
	}
}

static int reader_handle(F8_SOCKET s)
{
	char heap[1500];
	int mlen;
	int i;
	struct sockaddr_in addr;
	int alen = sizeof(addr);
	struct gmem_slot_t *p_msg;
	char *p_data;
	
	struct sync_time_t *p_time;//wdt_new

	mlen = recvfrom(s, heap, sizeof(heap), 0, (struct sockaddr*)&addr, &alen);
	
	//printf("receive data len=%d\n",mlen);//wdt_new
	
	p_time = (struct sync_time_t*)heap;
	if(mlen != OUT_SIZE){
		//perror("reader handle");
	
		//wdt_new
		if(mlen != 20){
			return 0;	//}else if((p_time->flag == SYNC_TIME) && (kernelState == KERN_S_RUNNING)){
		}else if(p_time->flag == SYNC_TIME){
			sync_time((int)p_time->time[0], (int)p_time->time[1], (int)p_time->time[2], (int)p_time->time[3], (int)p_time->time[4], 
				(int)p_time->time[5], (int)p_time->time[6], (int)p_time->time[7], (unsigned long)p_time->time[8]);
		}
		return 0;
	}

	p_msg = (struct gmem_slot_t*)heap;
	for(i = 0; i < GSLOT_COUNT; i++){
		if(p_msg->flag == GSLOT_VALID){
			if(p_msg->addr < IN_SIZE / 32){
				p_data = buf_in + p_msg->addr * 32;
				memcpy(p_data, p_msg->data, 32);
			}
		}
		p_msg++;
	}
	
	return 0;
}

static int gmem_update()
{
	while(task_flag != TSK_STOPPING){
		get_and_clear_out_mem();
		set_in_mem();
		taskDelay(100);
	}
	
	return 0;
}

static int gmem_reader()
{
	F8_SOCKET s[2];
	int ret = -1;
	struct sockaddr_in addr;
	fd_set sset;
	struct timeval tout;
	int tval = 1;
	
	s[0] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	s[1] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(IS_INVALID_SOCKET(s[0]) || IS_INVALID_SOCKET(s[1])){
		//perror("gemem reader socket");
		goto __final__;
	}

	setsockopt(s[0], SOL_SOCKET, SO_REUSEPORT, (char*)&tval, sizeof(tval));
	setsockopt(s[1], SOL_SOCKET, SO_REUSEPORT, (char*)&tval, sizeof(tval));
	setsockopt(s[0], SOL_SOCKET, SO_BROADCAST, (char*)&tval, sizeof(tval));
	setsockopt(s[1], SOL_SOCKET, SO_BROADCAST, (char*)&tval, sizeof(tval));

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_len = sizeof(addr);
	addr.sin_port = htons(F8_DBSYNCD_PORT);
	// addr.sin_addr.s_addr=getInterfaceIp(0);
	if(bind(s[0], (struct sockaddr*)&addr,sizeof(addr)) < 0){
		//perror("gemem reader socket0 bind 0");
		goto __final__;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_len = sizeof(addr);
	addr.sin_port = htons(F8_DBSYNCD_PORT+1);
	// addr.sin_addr.s_addr=getInterfaceIp(1);
	if(bind(s[1],(struct sockaddr*)&addr,sizeof(addr)) < 0){
		//perror("gemem reader socket1 bind 0");
		goto __final__;
	}

	listen(s[0], 1);
	listen(s[1], 1);

	for(;task_flag != TSK_STOPPING; taskDelay(1)){
		int scode, scode0, scode1;

		FD_ZERO(&sset);
		FD_SET(s[0],&sset);
		FD_SET(s[1],&sset);
		tout.tv_sec = 0;
		tout.tv_usec = 100000;
		if((scode = select(s[0]>s[1]?s[0]+1 : s[1]+1, &sset, 0, 0, &tout)) < 0){
			//perror("sync - select");
			continue;
		}
#if 0
		printf("sync - select ok %d\n",scode);
#endif

		scode0 = -1;
		scode1 = -1;
		if(FD_ISSET(s[0], &sset)){
			if((scode0 = reader_handle(s[0])) < 0){
				//printf("reader handle 0 err %d\n", scode0);
			}
		}
		if(FD_ISSET(s[1], &sset)){
			if((scode1 = reader_handle(s[1])) < 0){
				//printf("reader handle 1 err %d\n", scode1);
			}
		}	
	}

__final__:
	if(!IS_INVALID_SOCKET(s[0])){
		closesocket(s[0]);
	}
	if(!IS_INVALID_SOCKET(s[1])){
		closesocket(s[1]);
	}
	tid_reader = -1;
	return ret;
}

/*
* helper routines, get first/second ethernet interface broadcast IP
*/
u_long getInterfaceBcastIp(int n)
{
	char name[32];
	char itfcName[16];
	sprintf(itfcName, "%s%d", ETHER_INTERFACE, n);
	if(ifBroadcastGet(itfcName,name) < 0){
		return 0;
	}
	return inet_addr(name);
}

static int gmem_writer()
{
	F8_SOCKET s;
	struct sockaddr_in addr[2];
	int tval = 1;
	
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(IS_INVALID_SOCKET(s)){
		//perror("gmem writer - socket");
		return -1;
	}
	if(setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char*)&tval,sizeof(tval)) < 0){	
		//perror("gmem writer - setsocketopt");
	}
	memset(addr, 0, sizeof(addr));
	addr[0].sin_addr.s_addr = getInterfaceBcastIp(0);
	addr[0].sin_family = AF_INET;
	addr[0].sin_len = sizeof(addr[0]);
	addr[0].sin_port = htons(F8_DBSYNCD_PORT);
	
	addr[1].sin_addr.s_addr = getInterfaceBcastIp(1);
	addr[1].sin_family = AF_INET;
	addr[1].sin_len = sizeof(addr[0]);
	addr[1].sin_port = htons(F8_DBSYNCD_PORT + 1);
	
	while(task_flag != TSK_STOPPING){
		if(kernelState == KERN_S_RUNNING){
			if(!b_single){
				if(sendto(s, buf_out, OUT_SIZE, 0, (struct sockaddr*)&addr[0], sizeof(addr[0]))<0){
					//perror("gmem writer - sendto 1");
				}
				taskDelay(send_freq);
			}
			if(sendto(s, buf_out, OUT_SIZE, 0, (struct sockaddr*)&addr[1], sizeof(addr[1]))<0){
				//perror("gmem writer - sendto 2");
			}
			taskDelay(send_freq);
		}else if(kernelState == KERN_S_STANDBY && ke_get_flag(FKERN_LED_SYNCHRONIZED)){
			if(!b_single){
				if(sendto(s, buf_sync, OUT_SZ1, 0, (struct sockaddr*)&addr[0], sizeof(addr[0]))<0){
					//perror("gmem writer - sendto 1");
				}
				taskDelay(DEF_FREQ);
			}
			if(sendto(s, buf_sync, OUT_SZ1, 0, (struct sockaddr*)&addr[1], sizeof(addr[1]))<0){
				//perror("gmem writer - sendto 2");
			}
			taskDelay(DEF_FREQ);
		}else if(kernelState == KERN_S_STANDBY){
			if(!b_single){
				if(sendto(s, buf_standby, OUT_SZ1, 0, (struct sockaddr*)&addr[0], sizeof(addr[0]))<0){
					//perror("gmem writer - sendto 1");
				}
				taskDelay(DEF_FREQ);
			}
			if(sendto(s, buf_standby, OUT_SZ1, 0, (struct sockaddr*)&addr[1], sizeof(addr[1]))<0){
				//perror("gmem writer - sendto 2");
			}
			taskDelay(DEF_FREQ);
		}else{
			if(!b_single){
				if(sendto(s, buf_stop, OUT_SZ1, 0, (struct sockaddr*)&addr[0], sizeof(addr[0]))<0){
					//perror("gmem writer - sendto 1");
				}
				taskDelay(DEF_FREQ);
			}
			if(sendto(s, buf_stop, OUT_SZ1, 0, (struct sockaddr*)&addr[1], sizeof(addr[1]))<0){
				//perror("gmem writer - sendto 2");
			}
			taskDelay(DEF_FREQ);
		}

	}
	
	closesocket(s);
	tid_writer=-1;
	return 0;
}

int gmem_start()
{
	init_g_mem();
	task_flag = TSK_RUNNING;

	/* start daemon */
	tid_reader = taskSpawn(
		"gmem_reader",	/* name */
		52,			/* priority */
		VX_FP_TASK,		/* options */
		128*1024,		/* stack size */
		gmem_reader,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);

	tid_writer = taskSpawn(
		"gmem_writer",	/* name */
		52,			/* priority */
		VX_FP_TASK,		/* options */
		128*1024,		/* stack size */
		gmem_writer,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);

	tid_update = taskSpawn(
		"gmem_update",	/* name */
		255,			/* priority */
		VX_FP_TASK,		/* options */
		128*1024,		/* stack size */
		gmem_update,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);
	return 0;
}

int gmem_start_ex(int freq, int single)
{
	if(freq < 100){
		send_freq = DEF_FREQ;
	}else{
		send_freq = freq;
	}
	
	b_single = single;
	
	return gmem_start();
}


int gmem_stop()
{
	int i;
	
	task_flag = TSK_STOPPING;
	for(i = 0; i < 10; i++){
		if(tid_reader < 0 && tid_writer && tid_update < 0){
			return 0;
		}
		taskDelay(100);
	}
	return -1;
}
