#ifndef INCLUDE_EOS_PROCESS_H_
#define INCLUDE_EOS_PROCESS_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
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

typedef enum
{
	SINGLE_SHOT_PROCESS=0x00,
	CYCLIC_PROCESS
}E_ProcessType;


struct S_ProcessData
{
	void *base_address;
	u32 memory_length;
	E_ProcessStates process_state;
	E_TaskPriority priority;
	E_MemoryProtection is_emp_used;
	E_ProcessType process_type;
	void (*task)(void);
	void (*error_hook)(void);
};

/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public volatile s8 rub_task_stack_top;


/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public s8 create_process(void (*task)(void),void (*error_hook)(void),E_ProcessType processType,E_TaskPriority priority);
#endif /* PROCESS_H_ */
