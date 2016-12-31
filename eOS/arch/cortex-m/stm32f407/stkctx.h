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

#endif /* ARCH_CORTEX_M_STM32F407_STKCTX_H_ */
