/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "configuration.h"
#include "errno.h"
#include "scheduler.h"
#include "kernel.h"
/*REMOVE*/
#include "../ToBeRemoved/test.h"//TODO: Remove after testing
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
volatile struct S_ProcessData rs_TaskStruct[AVAILABLE_PROCESS_NUMBER];
volatile u8 u8_task_stack_top = 0;
volatile u8 u8_RunningProcess=0;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_private void kernel_Init(void);
_private s16 create(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type);
_private void kernel_ProcessErrorHook(u8 processId);
_private void kernel_IdleTask(void);
/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */
void kernel_ErrorHook(void)
{
	/*TODO:Do nothing for now!*/
	__asm volatile("NOP");
}




void kernel_Init(void)
{
	/*set kernel status to 0*/
	u32_KernelStatus=KERNEL_SCHEDULER_FLAG;
	/*initialize scheduler*/
	sched_Init();
	/*initialize processes*/
	u8_task_stack_top = 0;
	/*set internal process (error hook for kernel)*/
	mem_fill(&rs_TaskStruct[u8_task_stack_top], 0,
			sizeof(struct S_ProcessData));
	/*clean errors*/
	errno=EOK;
}
s16 kernel_CreateProcess(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type) {
	/*returns -1 in case of error or a number >0 that represents the process id.*/
	u8 errorNumber = EOK;
	s16 processId;
	enable_protection();
	if ((processId=create(task, error_hook, priority, task_type)) ==-1) {
		errorNumber = ETSOF;
	}
	disable_protection();
	return ((errorNumber == EOK) ? processId : -1);
}

s16 kernel_KillProcess(u8 processId) {
	if (processId == 0) {
		/*cannot kill reserved process*/
		errno = ERSPR;
		return -1;
	}
	if (AVAILABLE_PROCESS_NUMBER < processId) {
		errno = EIDNR;
		return -1;
	}
	enable_protection();
	PROCESS_SET_BLOCKED(rs_TaskStruct[processId]);

	disable_protection();
	return 0;
}

s16 create(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type) {
	u8 taskIndex = 1;
	boolean is_found = FALSE;
	struct S_ProcessData ls_Task;
	mem_fill(&ls_Task, 0, sizeof(struct S_ProcessData));
	PROCESS_SET_READY(ls_Task);
	switch (priority) {
	case TASK_HIGH_PRIO:
		PROCESS_SET_HIGH_PRIO(ls_Task);
		break;
	case TASK_LOW_PRIO:
		PROCESS_SET_LOW_PRIO(ls_Task);
		break;
	}
	switch (task_type) {
	case ONE_SHOT:
		PROCESS_SET_ONE_SHOT(ls_Task);
		break;
	case CYCLIC_5MS:
		PROCESS_SET_CYCLIC_5MS(ls_Task);
		break;
	case CYCLIC_10MS:
		PROCESS_SET_CYCLIC_10MS(ls_Task);
		break;
	case CYCLIC_20MS:
		PROCESS_SET_CYCLIC_20MS(ls_Task);
		break;
	}
#ifndef USE_MEMORY_PROTECTION
	PROCESS_SET_NO_MPU(ls_Task);
#endif
	ls_Task.task = task;
	ls_Task.error_hook = error_hook;
	for (taskIndex = 1; taskIndex < AVAILABLE_PROCESS_NUMBER; taskIndex++) {
		if (PROCESS_IS_BLOCKED(rs_TaskStruct[taskIndex]) == TRUE) {
			is_found = TRUE;
			break;

		}
	}
	if (is_found == TRUE) {
		PROCESS_ID(ls_Task, taskIndex);
		rs_TaskStruct[taskIndex] = ls_Task;
		return taskIndex;
	}
	if ((AVAILABLE_PROCESS_NUMBER - 1) == u8_task_stack_top) {
		return -1;
	}

	u8_task_stack_top++;
	PROCESS_ID(ls_Task, u8_task_stack_top);
	rs_TaskStruct[u8_task_stack_top] = ls_Task;
	return u8_task_stack_top;
}

void kernel_ProcessErrorHook(u8 processId) {
	/*prevent task from executing*/
	PROCESS_SET_BLOCKED(rs_TaskStruct[processId]);
	/*call Kernel ErrorHook*/
	kernel_ErrorHook();
}

boolean kernel_ProcessIsValid(u8 processId) {
	NOT_USED(processId);
	return TRUE;
}

void kernel_TerminateProcess(u8 processId){
	PROCESS_SET_BLOCKED(rs_TaskStruct[processId]);
}

void kernel_IdleTask(void){
	while(1){
		__asm volatile("NOP");
	}
}

int main(void)
{
	/*initialize MCU*/
	arch_Init();
	enable_protection();
	kernel_Init();
	KERNEL_DISABLE_SW_INTR();
	initApp();
	KERNEL_ENABLE_SW_INTR();
	disable_protection();
	kernel_IdleTask();
    return 0;

}

