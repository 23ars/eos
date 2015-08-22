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

/// Maximum number of tasks. By default it will be 20, 5 task for each time interval
#ifndef MAX_TASK_NUMBER
#define MAX_TASK_NUMBER 20
#endif


/// Available task
typedef enum
{
	E_Task_20ms=20, ///< 20ms task that will be run every 20ms
	E_Task_10ms=10, ///< 10ms task that will be run every 10ms
	E_Task_5ms=5 ///< 5ms task that will be run every 5ms
	
}E_AvailableTasks;

/// Task priorities
typedef enum
{
	TASK_HIGH_PRIO=0x01, ///< High priority task
	TASK_MEDIUM_PRIO=0x02, ///< Medium priority task
	TASK_LOW_PRIO=0x03 ///< Low priority task
}E_task_priority;

/// Task structure
typedef struct
{
	E_task_priority rub_Task_Priority; ///< Task priority
	E_AvailableTasks rub_Task_Schedule; ///< Task scheduler
	void (*task)(void); ///< Pointer to a function that will run on task
	
}S_Tasks_Struct;

ISR(TIMER0_OVF_vect);

_PRIVATE volatile UBYTE rub_schd_counter;
_PRIVATE volatile S_Tasks_Struct rs_task_stack[MAX_TASK_NUMBER];
_PRIVATE volatile UBYTE rub_task_stack_top=-1;

_PRIVATE void (*high_prio_task)(void)=0;
_PRIVATE void (*medium_prio_task)(void)=0;   //in c code use Task_10ms = &my_int_func;
_PRIVATE void (*low_prio_task)(void)=0;

/// Init function
/// \param[in] (*sc_1ms_task)(void) Pointer to the function that will be run on 1ms task, or 0
/// \param[in] (*sc_5ms_task)(void) Pointer to the function that will be run on 5ms task or 0
/// \param[in] (*sc_10ms_task)(void) Pointer to the function that will be run on 10ms task or 0
/// \param[in] (*sc_20ms_task)(void) Pointer to the function that will be run on 20ms task or 0
/// \return void
_PUBLIC void init();

_PRIVATE void execute_task(E_AvailableTasks task_scheduler);

/// @} //end of scheduler
#endif /* SCHEDULER_H_ */