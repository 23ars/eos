/*
 * stkctx.h
 *
 *  Created on: Dec 18, 2016
 *      Author: mihai
 */

#ifndef ARCH_CORTEX_M_STM32F407_STKCTX_H_
#define ARCH_CORTEX_M_STM32F407_STKCTX_H_

/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
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

static inline void READ_STACK_CTX(void)
{
	__asm volatile(
			"cpsid i			\n\t"
			"MRS 	r0,psp		\n\t"

		);
}

static inline void READ_REGISTERS(void)
{
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

			);
}

static inline void SAVE_CURRENT_TASK(void)
{
	__asm volatile(
			"ldr	r2, =os_curr_process		\n\t"
			"ldr	r1, [r2]	\n\t"			//load content from address from r2 in r1
			"str	r0, [r1]	\n\t"			//store content of r0 at address from r1.
			);//Save current task's SP
}

static inline void LOAD_NEXT_TASK(void)
{
	__asm volatile(
				"ldr	r2, =os_next_process		\n\t"
				"ldr	r1, [r2]	\n\t"			//load content from address r2 in r1
				"ldr	r0, [r1]	\n\t"			//load in r0 content from address r1
		);//Load next task
}

static inline void WRITE_REGISTERS(void)
{
	__asm volatile(
			"ldmia	r0!,{r4-r7}				\n\t"			//load r4-r7 to r0
			"mov	r8, r4					\n\t"				//move
			"mov	r9, r5          		\n\t"
			"mov	r10, r6         		\n\t"
			"mov	r11, r7         		\n\t"
			"ldmia	r0!,{r4-r7}				\n\t"			//load r4-r7 to r0

	);//Write registers
}

static inline void WRITE_STACK_CTX(void)
{
	__asm volatile(
			"MSR	psp,r0					\n\t"
			);//WRITE_STACK_CTX
}


static inline void BRANCH(void)
{
	__asm volatile(
			"ldr	r0,=0xFFFFFFFD			\n\t"
			"cpsie i						\n\t"
			"bx	r0							\n\t	//branch indirect"
	);//BRANCH
}
#endif /* ARCH_CORTEX_M_STM32F407_STKCTX_H_ */
