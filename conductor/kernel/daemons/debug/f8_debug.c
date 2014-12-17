#include "../../fkern/precomp.h"

extern void process_input(struct kernel_t * kernel);

void show_kernel()
{
	printf("io_mem %d\n",g_kernel.io_memory);
	printf("devices %d\n",g_kernel.devices);
	printf("moduleStatus %d\n",g_kernel.moduleStatus);	
}

static int io_run()
{
	int j;
	int i;
	for(j=0;j<6;j++){
		for(i=0;i<50;i++){	
			process_input(&g_kernel);
			miliSleep(2);
		}
		printf("io_run: %d 50 times.\n",j);
	}
	
	return 0;
}

void io_test()
{
	taskSpawn(
		"io_run",	/* name */
		255,			/* priority */
		VX_FP_TASK,		/* options */
		128*1024,		/* stack size */
		io_run,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);
}
