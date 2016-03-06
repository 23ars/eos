/*
 * process.h
 *
 * Created: 2/6/2016 11:52:28 PM
 *  Author: Mihai
 */ 


#ifndef PROCESS_H_
#define PROCESS_H_

typedef enum 
{
	RUNNING=0x00,
	READY,
	BLOCKED,
	
}E_ProcessStates;

/** Task priorities
 */
typedef enum
{
	TASK_HIGH_PRIO=0x01, /**< High priority task */
	TASK_MEDIUM_PRIO=0x02, /**< Medium priority task */
	TASK_LOW_PRIO=0x03 /**< Low priority task */
}E_TaskPriority;

typedef enum 
{
	USE_MPU=0x00,
	NO_MPU	
	
}E_MemoryProtection;

struct S_ProcessData
{
	void *base_address;
	u32 memory_length;
	E_ProcessStates process_state;
	E_TaskPriority priority;
	E_MemoryProtection is_emp_used;
	void (*task)(void);
	/*How i'll map memory?*/
};


_public s8 create_process(void (*task)(void),E_TaskPriority);
_public volatile s8 rub_task_stack_top;
#endif /* PROCESS_H_ */