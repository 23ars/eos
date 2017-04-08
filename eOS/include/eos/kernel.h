#ifndef INCLUDE_EOS_KERNEL_H_
#define INCLUDE_EOS_KERNEL_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "stkctx.h"
#include "scheduler.h"

/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
#define KERNEL_DISABLE_SW_INTR()				\
	enable_protection();						\
	u32_KernelStatus&=~KERNEL_SCHEDULER_FLAG;	\
	disable_protection();

#define KERNEL_ENABLE_SW_INTR()					\
	enable_protection();						\
	u32_KernelStatus|=KERNEL_SCHEDULER_FLAG;	\
	disable_protection();



#define PROCESS_CLEAR_STATE(process)			((process.processData^)=(process.processData))

#define PROCESS_SET_RUNNING(process)			((process.processData.task_state)=0x00u)
#define PROCESS_SET_READY(process)				((process.processData.task_state)=0x01u)
#define PROCESS_SET_BLOCKED(process)			((process.processData.task_state)=0x02u)


#define PROCESS_SET_HIGH_PRIO(process)			((process.processData.task_priority)=0x00u)
#define PROCESS_SET_LOW_PRIO(process)		  	((process.processData.task_priority)=0x01u)

#define PROCESS_SET_MPU(process)				((process.processData.task_mpu)=0x00u)
#define PROCESS_SET_NO_MPU(process)				((process.processData.task_mpu)=0x01u)

#define PROCESS_SET_DEFAULT(process)			((process.processData.task_type)=0x00u)
#define PROCESS_SET_CYCLIC_5MS(process)			((process.processData.task_type)=0x01u)
#define PROCESS_SET_CYCLIC_10MS(process)		((process.processData.task_type)=0x02u)
#define PROCESS_SET_CYCLIC_20MS(process)		((process.processData.task_type)=0x03u)

#define PROCESS_ID(process,id)					((process.processData.task_id)=(id))
#define PROCESS_SET_VALID(process)				((process.processData.task_valid)=0xFF)

#define PROCESS_IS_VALID(process)				((process.processData.task_valid)==0xFF)

#define PROCESS_IS_RUNNING(process)				((process.processData.task_state)==0x00u)
#define PROCESS_IS_READY(process)				((process.processData.task_state)==0x01u)
#define PROCESS_IS_BLOCKED(process)				((process.processData.task_state)==0x02u)

#define PROCESS_IS_HIGH_PRIO(process)			((process.processData.task_priority)==0x00u)
#define PROCESS_IS_LOW_PRIO(process)			((process.processData.task_priority)==0x01u)

#define PROCESS_IS_DEFAULT(process)				((process.processData.task_type)==0x00u)
#define PROCESS_IS_CYCLIC_5MS(process)			((process.processData.task_type)==0x01u)
#define PROCESS_IS_CYCLIC_10MS(process)			((process.processData.task_type)==0x02u)
#define PROCESS_IS_CYCLIC_20MS(process)			((process.processData.task_type)==0x03u)

#define IS_PROCESS_TABLE_EMPTY() (u8_task_stack_top==0)


typedef u16 os_error_t ;

typedef u32 os_stack;
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
	DEFAULT,
	CYCLIC_5MS = 0x05, CYCLIC_10MS = 0x0A, CYCLIC_20MS = 0x14,
} E_TaskType;
typedef struct
{
	unsigned int task_id:8;
	unsigned int reserved1:8;
	unsigned int task_type:2;
	unsigned int task_mpu:2;
	unsigned int task_priority:2;
	unsigned int task_state:2;
	unsigned int task_valid:8;
}u32_process;

typedef struct {
	volatile u32 sp;
	void (*task)(void);
	void (*error_hook)(void);
	volatile u32_process processData;
	os_stack stack[PROCESS_STACK_SIZE];
}os_process_t;

struct S_ProcessTable{
	os_process_t tasks[AVAILABLE_PROCESS_NUMBER];
	volatile u32 currentTask;
	u8 size;
};



/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public volatile os_process_t *os_curr_process;
_public volatile os_process_t *os_next_process;
_public volatile struct S_ProcessTable os_process_table;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void kernel_ErrorHook(void);

_public os_error_t kernel_CreateProcess(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type);
_public s16 kernel_KillProcess(u8 processId);
_public void kernel_TerminateProcess(void);

#endif /*INCLUDE_EOS_KERNEL_H_*/
