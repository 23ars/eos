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
volatile os_process_t *os_curr_process;
volatile os_process_t *os_next_process;
volatile struct S_ProcessTable os_process_table;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_private void kernel_Init(void);
_private void kernel_ProcessErrorHook(u8 processId);
_private void kernel_IdleTask(void);
_private void kernel_BackgroundProcess(void);
_private void kerkel_RestartProcess(void);
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
	/*set internal process (error hook for kernel)*/
	mem_fill(&os_process_table, 0,
			sizeof(struct S_ProcessTable));
	/*clean errors*/
	errno=EOK;
	kernel_CreateProcess(&kernel_BackgroundProcess, &kernel_ErrorHook, TASK_LOW_PRIO, CYCLIC_20MS);
}

void kernel_BackgroundProcess(void)
{
	__asm volatile("NOP");
}

void kernel_RestartProcess(void)
{

//	os_process_table.tasks[os_process_table.currentTask].sp=(u32)(os_process_table.tasks[os_process_table.currentTask].stack+PROCESS_STACK_SIZE-16);
//	(os_process_table.tasks[os_process_table.currentTask].task)();


}

os_error_t kernel_CreateProcess(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type) {
	os_process_t *p_Task=&os_process_table.tasks[os_process_table.size];
	u8 processId=os_process_table.size;
	p_Task->task=task;
	p_Task->error_hook=error_hook;
	p_Task->sp=(u32)(p_Task->stack+PROCESS_STACK_SIZE-16);
	switch (priority) {
		case TASK_HIGH_PRIO:
			PROCESS_SET_HIGH_PRIO((*p_Task));
			break;
		case TASK_LOW_PRIO:
			PROCESS_SET_LOW_PRIO((*p_Task));
			break;
		}
		switch (task_type) {
		case CYCLIC_5MS:
			PROCESS_SET_CYCLIC_5MS((*p_Task));
			break;
		case CYCLIC_10MS:
			PROCESS_SET_CYCLIC_10MS((*p_Task));
			break;
		case CYCLIC_20MS:
			PROCESS_SET_CYCLIC_20MS((*p_Task));
			break;
		}
#ifndef USE_MEMORY_PROTECTION
	PROCESS_SET_NO_MPU((*p_Task));
#endif
	p_Task->stack[PROCESS_STACK_SIZE-1] = 0x01000000;
	p_Task->stack[PROCESS_STACK_SIZE-2] = (u32)task;
	p_Task->stack[PROCESS_STACK_SIZE-3] = (u32)&kernel_TerminateProcess;


	os_process_table.size++;
	PROCESS_SET_READY((*p_Task));
	return processId;
}

s16 kernel_KillProcess(u8 processId) {
	NOT_USED(processId);
	return 0;
}


void kernel_ProcessErrorHook(u8 processId) {
	NOT_USED(processId);
	kernel_ErrorHook();
}

boolean kernel_ProcessIsValid(u8 processId) {
	NOT_USED(processId);
	return TRUE;
}

void kernel_TerminateProcess() {
	kernel_RestartProcess();
	while(1){
		__asm volatile("NOP");
	}
}

void kernel_IdleTask(void){
	while(1){
		__asm volatile("NOP");
	}
}

int main(void)
{
	/*initialize MCU*/
	enable_protection();
	kernel_Init();
	KERNEL_DISABLE_SW_INTR();
	initApp();
	arch_Init();
	KERNEL_ENABLE_SW_INTR();
	sched_Init();
	disable_protection();
	kernel_IdleTask();
    return 0;

}

