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

EOS_NAKED_ISR(PendSV_Handler) {

	enable_protection();
	READ_STACK_CTX();

	READ_REGISTERS();

	SAVE_CURRENT_TASK();

	LOAD_NEXT_TASK();
	WRITE_REGISTERS();

	WRITE_STACK_CTX();

	CONFIGURE_THREAD_MODE();
	disable_protection();

	BRANCH();

/*
	enable_protection();
	__asm volatile(
			"MRS 	r0,psp		\n\t"

	);//move PSP to R0 READ_STACK_CTX

	__asm volatile(
			"SUBS	r0,#16					\n\t"
			"STMIA	r0!,{r4-r7}				\n\t"
			"mov	r4, r8					\n\t"					//move r8 to r4
			"mov	r5, r9					\n\t"					//move r9 to r5
			"mov	r6, r10					\n\t"					//move r10 to r6
			"mov	r7, r11					\n\t"					//move r11 to r7
			"subs	r0, #32					\n\t"				//substract 32 from r0 and save it to r0.
			"stmia	r0!,{r4-r7}				\n\t"				//store r4-r7 at the address specified in r0.
			"subs	r0, #16					\n\t"				//subs 16 from r0

			);//read registers
	__asm volatile(
			"ldr	r2, =os_curr_process	\n\t"			//load address of os_curr_process in R2
			"ldr	r1, [r2]				\n\t"			//load content from address from r2 in r1
			"str	r0, [r1]				\n\t"			//store content of r0 at address from r1.
			);//Save current task's SP

	__asm volatile(

			"ldr	r2, =os_next_process	\n\t"			//load address of next process in r2
			"ldr	r1, [r2]				\n\t"			//load content from address r2 in r1
			"ldr	r0, [r1]				\n\t"			//load in r0 content from address r1
	);//Load next task

	__asm volatile(
			"ldmia	r0!,{r4-r7}				\n\t"			//load r4-r7 to r0
			"mov	r8, r4					\n\t"				//move
			"mov	r9, r5          		\n\t"
			"mov	r10, r6         		\n\t"
			"mov	r11, r7         		\n\t"
			"ldmia	r0!,{r4-r7}				\n\t"			//load r4-r7 to r0

	);//Write registers

	__asm volatile(
			"MSR	psp,r0					\n\t"
			);//WRITE_STACK_CTX

	__asm volatile(
			"ldr	r0,=0xFFFFFFFD			\n\t"
			);//EXC_RETURN - Thread mode with PSP
	disable_protection();

	__asm volatile(
			"bx	r0							\n\t	//branch indirect"
	);//BRANCH
*/
}


void sched_Init(void)
{

	u8_schd_counter = 0;


}

