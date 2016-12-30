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
#define PROCESS_CLEAR_STATE(process)			((process.processData^)=(process.processData))

#define PROCESS_SET_RUNNING(process)			((process.processData)|=(0x00u<<22))
#define PROCESS_SET_READY(process)				((process.processData)|=(0x01u<<22))
#define PROCESS_SET_BLOCKED(process)			((process.processData)|=(0x02u<<22))

#define PROCESS_SET_HIGH_PRIO(process)			((process.processData)|=(0x00u<<20))
#define PROCESS_SET_LOW_PRIO(process)		  	((process.processData)|=(0x01u<<20))

#define PROCESS_SET_MPU(process)				((process.processData)|=(0x00u<<18))
#define PROCESS_SET_NO_MPU(process)				((process.processData)|=(0x01u<<18))

#define PROCESS_SET_ONE_SHOT(process)			((process.processData)|=(0x00u<<16))
#define PROCESS_SET_CYCLIC_5MS(process)			((process.processData)|=(0x01u<<16))
#define PROCESS_SET_CYCLIC_10MS(process)		((process.processData)|=(0x02u<<16))
#define PROCESS_SET_CYCLIC_20MS(process)		((process.processData)|=(0x03u<<16))

#define PROCESS_ID(process,id)					((process.processData)|=(id))
#define PROCESS_SET_VALID(process)				((process.processData)|=(1<<31))

#define PROCESS_IS_VALID(process)				(((process.processData)&(1<<31))!=0x00)

#define PROCESS_IS_RUNNING(process)				(((process.processData)&(0x00u<<22))!=0x00)
#define PROCESS_IS_READY(process)				(((process.processData)&(0x01u<<22))!=0x00)
#define PROCESS_IS_BLOCKED(process)				(((process.processData)&(0x02u<<22))!=0x00)

#define PROCESS_IS_HIGH_PRIO(process)			(((process.processData)&(0x00u<<20))!=0x00)
#define PROCESS_IS_LOW_PRIO(process)			(((process.processData)&(0x01u<<20))!=0x00)

#define PROCESS_IS_ONE_SHOT(process)			(((process.processData)&(0x00u<<16))!=0x00)
#define PROCESS_IS_CYCLIC_5MS(process)			(((process.processData)&(0x01u<<16))!=0x00)
#define PROCESS_IS_CYCLIC_10MS(process)			(((process.processData)&(0x02u<<16))!=0x00)
#define PROCESS_IS_CYCLIC_20MS(process)			(((process.processData)&(0x03u<<16))!=0x00)

/** Process states
 */
typedef enum {
	RUNNING = 0x00,/**< A process in <b>RUNNING</b> state cannot be activated by scheduler*/
	READY,/**< A process in <b>READY</b> state will be activated by scheduler*/
	BLOCKED,/**< A process in <b>BLOCKED</b> state is marked for deletion*/

} E_ProcessStates;

/** Task priorities
 */
typedef enum {
	TASK_HIGH_PRIO = 0x01, /**< High priority task */
	TASK_LOW_PRIO = 0x02 /**< Low priority task */
} E_TaskPriority;

typedef enum {
	USE_MPU = 0x00, NO_MPU

} E_MemoryProtection;

typedef enum {
	ONE_SHOT, CYCLIC_5MS = 0x05, CYCLIC_10MS = 0x0A, CYCLIC_20MS = 0x14,
} E_TaskType;

struct S_ProcessData {
	void *base_address;
	u32 memory_length;
	ptr_u32 sp;
	ptr_u32 stk_end;
	u32 processData;
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
_public boolean process_CheckIfValid(void);
_public void process_ErrorHook(u8 processId);
_public void process_Init(void);
_public s16 process_Create(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type);
_public s16 process_Kill(u8 processId);
_public void process_TerminateTask(u8 processId);
#endif /* PROCESS_H_ */
