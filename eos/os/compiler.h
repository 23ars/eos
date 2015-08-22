/*
 * compiler.h
 *
 * Created: 8/9/2015 4:28:26 PM
 *  Author: Mihai
 */ 


#ifndef COMPILER_H_
#define COMPILER_H_
#include "avr/interrupt.h"

#if defined (__AVR__)

	#define DISABLE_INTERRUPTS cli()
	#define ENABLE_INTERRUPTS sei()



/************************************************************************/
/* AVR ASSEMBLY OPS                                                     */
/************************************************************************/
	#define NO_OPERATION() asm volatile("NOP")

#else if defined (__XC8)
	#define DISABLE_INTERRUPTS
	#define ENABLE_INTERRUPTS
	#define  NO_OPERATION()	
	
#endif

#endif /* COMPILER_H_ */
