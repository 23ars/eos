/*
 * scheduler.h
 *
 * Created: 8/2/2015 5:48:29 PM
 *  Author: Mihai
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/// \defgroup scheduler
/// Module implemented to allow task scheduling in projects. The scheduler run on timer0 wich is an 8-bit timer. Timer0 is configured to interrupt on overflow
/// @{

/// CPU frequency
#ifndef F_CPU
#define F_CPU 16000000UL //16 MHz
#endif

#include "task_stack.h"




ISR(TIMER0_OVF_vect);

_PRIVATE volatile UBYTE rub_schd_counter;


_PRIVATE void (*high_prio_task)(void)=0;
_PRIVATE void (*medium_prio_task)(void)=0;   //in c code use Task_10ms = &my_int_func;
_PRIVATE void (*low_prio_task)(void)=0;

/// Init function
/// \param[in] (*sc_1ms_task)(void) Pointer to the function that will be run on 1ms task, or 0
/// \param[in] (*sc_5ms_task)(void) Pointer to the function that will be run on 5ms task or 0
/// \param[in] (*sc_10ms_task)(void) Pointer to the function that will be run on 10ms task or 0
/// \param[in] (*sc_20ms_task)(void) Pointer to the function that will be run on 20ms task or 0
/// \return void
_PUBLIC void sched_init();

_PRIVATE void execute_task(E_AvailableTasks task_scheduler);

/// @} //end of scheduler
#endif /* SCHEDULER_H_ */