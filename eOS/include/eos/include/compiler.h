/*
 * compiler.h
 *
 *  Created on: Dec 10, 2016
 *      Author: mihai
 */

#ifndef INCLUDE_EOS_INCLUDE_COMPILER_H_
#define INCLUDE_EOS_INCLUDE_COMPILER_H_



#define DISABLE_INTERRUPTS  __asm volatile("cpsid i")
#define ENABLE_INTERRUPTS   __asm volatile("cpsie i")

#endif /* INCLUDE_EOS_INCLUDE_COMPILER_H_ */
