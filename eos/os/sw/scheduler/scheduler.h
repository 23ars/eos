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



/// Available task
typedef enum
{
	E_Task_20ms=20, ///< 20ms task that will be run every 20ms
	E_Task_10ms=10, ///< 10ms task that will be run every 10ms
	E_Task_5ms=5, ///< 5ms task that will be run every 5ms
	E_Task_1ms=1 ///< 1ms task that will be run every 1ms	
	
}E_AvailableTasks;

ISR(TIMER0_OVF_vect);

_PRIVATE volatile UBYTE rub_schd_counter;

/// Init function
/// \param[in] (*sc_1ms_task)(void) Pointer to the function that will be run on 1ms task, or 0
/// \param[in] (*sc_5ms_task)(void) Pointer to the function that will be run on 5ms task or 0
/// \param[in] (*sc_10ms_task)(void) Pointer to the function that will be run on 10ms task or 0
/// \param[in] (*sc_20ms_task)(void) Pointer to the function that will be run on 20ms task or 0
/// \return void
_PUBLIC void init(void (*sc_1ms_task)(void),void (*sc_5ms_task)(void),void (*sc_10ms_task)(void),void (*sc_20ms_task)(void));

_PRIVATE void (*Task_20ms)(void)=0;   
_PRIVATE void (*Task_10ms)(void)=0;   //in c code use Task_10ms = &my_int_func;
_PRIVATE void (*Task_5ms)(void)=0;   
_PRIVATE void (*Task_1ms)(void)=0;   

/// @} //end of scheduler
#endif /* SCHEDULER_H_ */