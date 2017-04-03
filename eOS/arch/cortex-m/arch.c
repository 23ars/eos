/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "arch.h"
#include "stm32f407xx.h"
#include "core_cm4.h"
#include "kernel.h"
#include "scheduler.h"
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
systicks_t systicks;
volatile u8 u8_schd_counter = 0;

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */

//EOS_NAKED_ISR(PendSV_Handler);

/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */

void arch_Init(void) {
	/*Set lowest possible priority for SW Interrupt*/
	NVIC_SetPriority(PendSV_IRQn, 0xFFu);
	/*Set highest possible priority for SysTick*/
	NVIC_SetPriority(SysTick_IRQn, 0x00u);
	/*configure system tick frequency*/
	SysTick_Config(SystemCoreClock);
	/*clear base priority for exception processing*/
	__set_BASEPRI(0);
	/*set PendSV to the lowest priority*/
	NVIC_SetPriority(PendSV_IRQn, 0xFF);

	os_curr_process=&os_process_table.tasks[os_process_table.currentTask];
	/*Set PSP to the top of task's stack*/
	__set_PSP(os_curr_process->sp+64);
	/*swith to Unprivilleged Thread Mode with PSP*/
	__set_CONTROL(0x03);
	/*Execute ISB after changing controll (recommended)*/
	__ISB();
	PROCESS_SET_RUNNING((*os_curr_process));
	(os_curr_process->task)();

}



void arch_IssueSwInterrupt(void) {
	u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}



//EOS_NAKED_ISR(PendSV_Handler) {


//	KERNEL_CONTEXT_SAVE();
//	enable_protection();
//	sched_ScheduleNextTask();
//	u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
//	disable_protection();
//	/*issue new Sw Interrupt to kernel*/
//	if(u8_RunningProcess!=0){
//		(*rs_TaskStruct[u8_RunningProcess].task)();
//	}
//	KERNEL_CONTEXT_RESTORE();
//}
