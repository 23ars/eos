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
	_private u8 u8_StackIndex = 1;
	_private u8 u8_TaskId = 0;
	_private u8 u8_CallableTask = 0;
	/*select called task*/
	while (u8_StackIndex <= u8_task_stack_top) {
		u8_TaskId = u8_StackIndex;
		if (rs_TaskStruct[u8_TaskId].task == 0) {
			u8_StackIndex++;
			continue;
		}
		if (PROCESS_IS_RUNNING(rs_TaskStruct[u8_TaskId]) == TRUE
				|| PROCESS_IS_BLOCKED(rs_TaskStruct[u8_TaskId]) == TRUE) {
			u8_StackIndex++;
			continue;
		}
		if (PROCESS_IS_LOW_PRIO(rs_TaskStruct[u8_TaskId]) == TRUE) {
			u8_CallableTask = u8_TaskId;
			u8_StackIndex++;
			continue;
		} else {
			u8_CallableTask = u8_TaskId;
		}
		if ((u8_schd_counter % CYCLIC_5MS)
				== 0&& PROCESS_IS_CYCLIC_5MS(rs_TaskStruct[u8_CallableTask])==TRUE) {
			/*Call 5 ms*/
			goto save_task_id;
		} else if ((u8_schd_counter % CYCLIC_10MS)
				== 0&& PROCESS_IS_CYCLIC_10MS(rs_TaskStruct[u8_CallableTask])==TRUE) {
			/*Call 10ms*/
			goto save_task_id;
		} else if ((u8_schd_counter % CYCLIC_20MS)
				== 0&& PROCESS_IS_CYCLIC_20MS(rs_TaskStruct[u8_CallableTask])==TRUE) {
			/*Call 20ms*/
			goto save_task_id;
		} else if (PROCESS_IS_ONE_SHOT(rs_TaskStruct[u8_CallableTask]) == TRUE) {
			goto save_task_id;
		} else {
			u8_RunningProcess = 0;
			goto early_return;
		}

	}
	early_return:
	if (u8_StackIndex > u8_task_stack_top) {
		u8_StackIndex = 1;
		u8_RunningProcess = 0;

	}
	return;
	/*call task with the higher priority and smaller cycle time*/
	/*prepare next SW Interrupt*/
	save_task_id: u8_RunningProcess = u8_CallableTask;
}

void SystemTick_ServiceRoutine(void) {

	enable_protection();
	u8_schd_counter++;
	disable_protection();
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

