/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "arch.h"
#include "stm32f407xx.h"
#include "core_cm4.h"
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
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
EOS_ISR(SysTick_Handler);
/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */

void arch_Init(void)
{
	/* set interrupt priority grouping to be preemptive (no sub-priority)*/
	NVIC_SetPriorityGrouping( 0x03 );
	/*configure system tick frequency*/
	SysTick_Config( SystemCoreClock / SYSTICK_FREQUENCY_HZ );
	/*clear base priority for exception processing*/
	__set_BASEPRI( 0 );
	/*set PendSV to the lowest priority*/
	NVIC_SetPriority( PendSV_IRQn, 0xFF );
}





EOS_ISR(SysTick_Handler)
{
	SystemTick_ServiceRoutine();

}
