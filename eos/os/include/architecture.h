/*
 * atmega.h
 *
 * Created: 8/22/2015 10:19:01 PM
 *  Author: Mihai
 */ 


#ifndef ARCHITECTURE_H_
#define ARCHITECTURE_H_
#include "../threading/task_stack.h"
#include "../threading/task_manager.h"
#include "../../eos_conf.h"


#if defined (__AVR__) || defined ATMEGA
	
	
	#include "../../arch/atmega/include/scheduler.h"


#else if defined (__XC8) || defined PIC
	#define DISABLE_INTERRUPTS
	#define ENABLE_INTERRUPTS
	#define  NO_OPERATION()

else if defined 80C51

#endif



#endif /* ATMEGA_H_ */