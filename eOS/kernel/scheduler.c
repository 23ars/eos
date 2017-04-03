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

volatile u32 u32_KernelStatus;
ptr_u32 stack;
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



EOS_ISR(SysTick_Handler) {

	enable_protection();
	os_curr_process=&os_process_table.tasks[os_process_table.currentTask];
	PROCESS_SET_READY((*os_curr_process));
	os_process_table.currentTask++;

	if(os_process_table.currentTask>=os_process_table.size){
		//kernel process is never killed.
		os_process_table.currentTask=1;
	}

	os_next_process=&os_process_table.tasks[os_process_table.currentTask];
	PROCESS_SET_RUNNING((*os_next_process));

	disable_protection();
	if (u32_KernelStatus & KERNEL_SCHEDULER_FLAG)
	{
		enable_protection();
		u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
		disable_protection();
		arch_IssueSwInterrupt();
	}



}


void sched_Init(void)
{

	u8_schd_counter = 0;


}

