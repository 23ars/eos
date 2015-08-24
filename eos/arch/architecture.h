/*
 * atmega.h
 *
 * Created: 8/22/2015 10:19:01 PM
 *  Author: Mihai
 */ 


#ifndef ARCHITECTURE_H_
#define ARCHITECTURE_H_
#include "task_stack.h"
#include "task_manager.h"
#if defined (__AVR__)
	
	
	#include "atmega/include/scheduler.h"


#else if defined (__XC8)
	#define DISABLE_INTERRUPTS
	#define ENABLE_INTERRUPTS
	#define  NO_OPERATION()

#endif



#endif /* ATMEGA_H_ */