/*
 * scheduler.h
 *
 * Created: 8/2/2015 5:48:29 PM
 *  Author: Mihai
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/** \defgroup scheduler
 * Module implemented to allow task scheduling in projects. The scheduler run on timer0 wich is an 8-bit timer. Timer0 is configured to interrupt on overflow
 * @{
*/
/** CPU frequency
 */
#ifndef F_CPU
#define F_CPU 16000000UL 
#endif

#include "../../../os/threading/task_stack.h"




ISR(TIMER0_OVF_vect);

_PRIVATE volatile UBYTE rub_schd_counter;


_PRIVATE void (*high_prio_task)(void)=0;
_PRIVATE void (*medium_prio_task)(void)=0;  
_PRIVATE void (*low_prio_task)(void)=0;

/** Init function
 * \param[in] void
 * \return void
 */
_PUBLIC void sched_init();

_PRIVATE void execute_task(E_AvailableTasks task_scheduler);

/** @} //end of scheduler
 */
#endif /* SCHEDULER_H_ */