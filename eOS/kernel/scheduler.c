/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "kernel.h"
#include "scheduler.h"

/*
 * ######################################################
 * ##           Type Definitions                       ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##           Variable Definitions                   ##
 * ######################################################
 * */
_private volatile u8 u8_schd_counter=0;
u32 u32_KernelStatus;
/*
 * ######################################################
 * ##           Function Definitions                   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##           Function Implementations               ##
 * ######################################################
 * */

void SystemTick_ServiceRoutine(void)
{

	enable_protection();
	u8_schd_counter++;
	/*issue new Sw Interrupt to kernel*/
	if ( u32_KernelStatus & KERNEL_SCHEDULER_FLAG ) {
		u32_KernelStatus^= KERNEL_SCHEDULER_FLAG;
		arch_IssueSwInterrupt();
	}
	disable_protection();
}


void sched_Init(void)
{

	u8_schd_counter=0;
	
}


