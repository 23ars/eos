/*
 * boot.h
 *
 *  Created on: Dec 10, 2016
 *      Author: mihai
 */

#ifndef ARCH_CORTEX_M_ARCH_H_
#define ARCH_CORTEX_M_ARCH_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "configuration.h"
#include "stdtypes.h"
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
typedef u32 systicks_t;
_public ptr_u32 stack;

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public EOS_ISR(SysTick_Handler);
//_public EOS_NAKED_ISR(PendSV_Handler);
_public void arch_Init(void);
_public void arch_IssueSwInterrupt(void);
_public void arch_Init(void);
#endif /* ARCH_CORTEX_M_ARCH_H_ */
