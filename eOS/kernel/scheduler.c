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
_private struct S_ProcessData ls_CallableTask;
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
		if (PROCESS_IS_LOW_PRIO(ls_Task) == TRUE) {
			ls_CallableTask = ls_Task;
			u8_StackIndex++;
			continue;
		} else {
			ls_CallableTask = ls_Task;
		}
		if ((u8_schd_counter % CYCLIC_5MS)
				== 0&& PROCESS_IS_CYCLIC_5MS(ls_CallableTask)==TRUE) {
			/*Call 5 ms*/
			goto call_task;
		}
		if ((u8_schd_counter % CYCLIC_10MS)
				== 0&& PROCESS_IS_CYCLIC_10MS(ls_CallableTask)==TRUE) {
			/*Call 10ms*/
			goto call_task;
		}
		if ((u8_schd_counter % CYCLIC_20MS)
				== 0&& PROCESS_IS_CYCLIC_20MS(ls_CallableTask)==TRUE) {
			/*Call 20ms*/
			goto call_task;
		}
		if (PROCESS_IS_ONE_SHOT(ls_Task) == TRUE) {
			goto call_task;
		}
	}

	if (u8_StackIndex > u8_task_stack_top) {
		u8_StackIndex = 0;
	}
	/*call task with the higher priority and smaller cycle time*/
	/*prepare next SW Interrupt*/
	call_task:
	enable_protection();
	u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
	disable_protection();
	(*ls_CallableTask.task)();

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

