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

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void arch_init(void);
#endif /* ARCH_CORTEX_M_ARCH_H_ */
