/*
 * compiler.h
 *
 * Created: 8/9/2015 4:28:26 PM
 *  Author: Mihai
 */ 


#ifndef COMPILER_H_
#define COMPILER_H_


/*lint -save -e544 it's really ok if not followed by EOL */
/*lint -save -e961 Used as macro for NOP */
#if defined (__AVR__)

	#define DISABLE_INTERRUPTS __asm__ __volatile__ ("cli" ::: "memory")
	#define ENABLE_INTERRUPTS   __asm__ __volatile__ ("sei" ::: "memory")



/************************************************************************/
/* AVR ASSEMBLY OPS                                                     */
/************************************************************************/

	#define NO_OPERATION() asm volatile("NOP")

#else if defined (__XC8) 

	#define DISABLE_INTERRUPTS
	#define ENABLE_INTERRUPTS
	#define  NO_OPERATION()	
	
#endif
/*lint -restore */
/*lint -restore*/
#endif /* COMPILER_H_ */
