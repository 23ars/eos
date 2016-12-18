/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "process.h"
#include "errno.h"
#include "kernel.h"
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

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_private void kernel_Init(void);
/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */
EOS_NAKED_ISR(PendSV_Handler)
{
	/*save context*/
	__asm volatile (
			"mrs     r0, msp           \n"
			"push    {r4 - r11, lr}    \n"
			"mov     r11, r0           \n"
		);
	__asm("NOP");
}
void kernel_Init(void)
{
	/*set kernel status to 0*/
	u32_KernelStatus=0x00000001u;
	/*initialize scheduler*/
	sched_Init();
	/*initialize processes*/
	process_Init();
	/*clean errors*/
	errno=EOK;
}
int main(void)
{
	/*initialize MCU*/
	arch_Init();
	kernel_Init();
    while(1);
    return 0;

}

