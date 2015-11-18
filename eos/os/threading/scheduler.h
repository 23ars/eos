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

#include "task_stack.h"









/** Scheduler Service Routine
 * \param[in] void
 * \return void
 */
_PUBLIC void Timer_Overflow_ServiceRoutine(void);

/** Init function
 * \param[in] void
 * \return void
 */
_PUBLIC void sched_init();



/** @} //end of scheduler
 */
#endif /* SCHEDULER_H_ */