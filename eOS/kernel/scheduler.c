/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "process.h"
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
_private volatile u8 u8_schd_counter = 0;
volatile u32 u32_KernelStatus;
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

void sched_ScheduleNextTask(void) {
	_private u8 u8_StackIndex = 0;
	_private struct S_ProcessData ls_Task;

	/*select called task*/
	while (u8_StackIndex < u8_task_stack_top) {
		ls_Task = rs_TaskStruct[u8_StackIndex];
		if (ls_Task.task == 0) {
			u8_StackIndex++;
			continue;
		}
		if (PROCESS_IS_RUNNING(ls_Task) == TRUE
				|| PROCESS_IS_BLOCKED(ls_Task) == TRUE) {
			u8_StackIndex++;
			continue;
		}
	}
	if (u8_StackIndex > u8_task_stack_top) {
		u8_StackIndex = 0;
	}
	/*launch task is one shot*/
	if(PROCESS_IS_ONE_SHOT(ls_Task)==TRUE){


	}

	/*prepare next SW Interrupt*/
	enable_protection();
	u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
	disable_protection();
//call task
	(*ls_Task.task)();
}

void SystemTick_ServiceRoutine(void) {

	enable_protection();
	u8_schd_counter++;
	disable_protection();
	/*issue new Sw Interrupt to kernel*/
	if (u32_KernelStatus & KERNEL_SCHEDULER_FLAG) {
		enable_protection();
		u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
		disable_protection();
		arch_IssueSwInterrupt();
	}
}

void sched_Init(void) {

	u8_schd_counter = 0;

}

