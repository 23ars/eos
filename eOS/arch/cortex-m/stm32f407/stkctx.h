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
/*context saved by hardware*/
struct S_MainStkCtxt{
	memaddr r0;
	memaddr r1;
	memaddr r2;
	memaddr r3;
	memaddr r12;
	memaddr lr;
	memaddr pc;
	memaddr psr;
};
/*context saved by software*/
struct S_TaskStkCtxt{
	memaddr r4;
	memaddr r5;
	memaddr r6;
	memaddr r7;
	memaddr r8;
	memaddr r9;
	memaddr r10;
	memaddr r11;
	memaddr lr;
};
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
#define STORE_REGISTERS_PSP_ASM()	\
__asm volatile(						\
	 "MRS r0, psp			\n\t"	\
	 "STMDB r0!, {r4-r11}	\n\t"	\
	 "MSR psp, r0			\n\t"	\
	 "BX lr					\n\t"	\
	 );

#define LOAD_REGISTERS_PSP_ASM()	\
__asm volatile(						\
	"MRS r0, psp			\n\t"	\
	"LDMFD r0!, {r4-r11}	\n\t"	\
	"MSR psp, r0			\n\t"	\
	"BX lr					\n\t"	\
);

#define SET_PSP_ASM(PSP)			\
__asm volatile(						\
	"MSR psp,r0				\n\t"   \
	"BX lr					\n\t"	\
);

#define GET_PSP_ASM()				\
__asm volatile(						\
	"MRS r0,psp				\n\t"   \
	"BX lr					\n\t"	\
);
#endif /* ARCH_CORTEX_M_STM32F407_STKCTX_H_ */
