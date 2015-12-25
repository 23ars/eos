#ifndef TASK_STACK_H_
#define TASK_STACK_H_

/** \defgroup task_stack
 * Definition of the stack that is used for holding tasks
 * @{
 */
/*lint -save -e537 eos_conf.h is needed because it contains the custom definition of MAX_TASK_NUMBER */
#include "eos_conf.h"
/*lint-restore */

/** Maximum number of tasks. By default it will be 20, 5 task for each time interval
 */
#ifndef MAX_TASK_NUMBER
#define MAX_TASK_NUMBER 15
#endif

/** Available task
 */
typedef enum
{
	E_Task_20ms=20, /**< 20ms task that will be run every 20ms */
	E_Task_10ms=10, /**< 10ms task that will be run every 10ms */
	E_Task_5ms=5 /**< 5ms task that will be run every 5ms */
	
}E_AvailableTasks;

/** Task priorities
 */
typedef enum
{
	TASK_HIGH_PRIO=0x01, /**< High priority task */
	TASK_MEDIUM_PRIO=0x02, /**< Medium priority task */
	TASK_LOW_PRIO=0x03 /**< Low priority task */
}E_task_priority;

/** Task states
 */
typedef enum
{
	OS_DESTROYED=0x00,/**< Task State that can be set only by OS */
	TASK_ACTIVE=0x10, /**< Task State Active */
	TASK_SLEEPING=0x20,/**< Task State Sleeping */
	TASK_BLOCKED=0x30 /**< Task State Disabled */
	
}E_Task_State;

/** Task structure
 */
typedef struct
{
	E_task_priority rub_Task_Priority; /**< Task priority */
	E_Task_State rub_Task_State;
	E_AvailableTasks rub_Task_Schedule; /**< Task scheduler */
	void (*task)(void); /**< Pointer to a function that will run on task */
	
}S_Tasks_Struct;

/*lint -save -e960 Needed global objects */
volatile S_Tasks_Struct rs_task_stack[MAX_TASK_NUMBER];
volatile s8 rub_task_stack_top;
volatile s8 rub_thread_id;
/*lint -restore*/

/** @} //end of task_stack
 */
#endif /* TASK_STACK_H_ */
