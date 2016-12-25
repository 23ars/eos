/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "process.h"
#include "errno.h"
#include "scheduler.h"
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
void kernel_ErrorHook(void)
{
	/*TODO:Do nothing for now!*/
	__asm("NOP");
}

inline void kernel_DisableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus&=~KERNEL_SCHEDULER_FLAG;
	disable_protection();
}
inline void kernel_EnableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus|=KERNEL_SCHEDULER_FLAG;
	disable_protection();
}


void kernel_Init(void)
{
	/*set kernel status to 0*/
	u32_KernelStatus=KERNEL_SCHEDULER_FLAG;
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

