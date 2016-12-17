/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "scheduler.h"
#include "process.h"
#include "errno.h"
#include "kernel.h"
/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */

status_t sysstatus;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_private void kernel_Init(void);
/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */
void kernel_Init(void)
{
	/*initialize scheduler*/
	sched_Init();
	/*initialize processes*/
	process_Init();
	/*clean errors*/
	errno=EOK;
}
int main(void)
{
	/*initialize MCU*/
	arch_Init();
	kernel_Init();
    while(1);
    return 0;

}

