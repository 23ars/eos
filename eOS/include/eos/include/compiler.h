/*
 * compiler.h
 *
 *  Created on: Dec 10, 2016
 *      Author: mihai
 */

#ifndef INCLUDE_EOS_INCLUDE_COMPILER_H_
#define INCLUDE_EOS_INCLUDE_COMPILER_H_


#include <string.h>

#define DISABLE_INTERRUPTS  __asm volatile("cpsid i")
#define ENABLE_INTERRUPTS   __asm volatile("cpsie i")

#ifndef EOS_ISR
  #define EOS_ISR(ISR_name) void __attribute__ ((interrupt)) ISR_name(void)
#endif

#ifndef mem_copy
#define mem_copy(target,src,size) memcpy(target,src,size)
#endif

#ifndef mem_fill
#define mem_fill(target,value,size) memset(target,value,size)
#endif

#ifndef mem_move
#define mem_move(target,value,size) memmove(target,value,size)
#endif

#endif /* INCLUDE_EOS_INCLUDE_COMPILER_H_ */
