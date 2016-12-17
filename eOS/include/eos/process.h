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



struct S_ProcessData
{
	void *base_address;
	u32 memory_length;
	E_ProcessStates process_state;
	E_TaskPriority priority;
	E_MemoryProtection is_emp_used;
	u8 processId;
	void (*task)(void);
	void (*error_hook)(void);
};

/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public volatile u8 u8_task_stack_top;
_public volatile struct S_ProcessData rs_TaskStruct[AVAILABLE_PROCESS_NUMBER];

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void process_Init(void);
_public s16 create_process(void (*task)(void),void (*error_hook)(void),E_TaskPriority priority);
_public s16 kill_process(u8 processId);
#endif /* PROCESS_H_ */
