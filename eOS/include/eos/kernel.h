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
#define KERNEL_CONTEXT_SAVE() STORE_REGISTERS_PSP_ASM()
#define KERNEL_CONTEXT_RESTORE() LOAD_REGISTERS_PSP_ASM()

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

#define PROCESS_SET_ONE_SHOT(process)			((process.processData.task_type)=0x00u)
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

#define PROCESS_IS_ONE_SHOT(process)			((process.processData.task_type)==0x00u)
#define PROCESS_IS_CYCLIC_5MS(process)			((process.processData.task_type)==0x01u)
#define PROCESS_IS_CYCLIC_10MS(process)			((process.processData.task_type)==0x02u)
#define PROCESS_IS_CYCLIC_20MS(process)			((process.processData.task_type)==0x03u)



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

struct S_ProcessData {
	void *base_address;
	u32 memory_length;
	ptr_u32 sp;
	ptr_u32 stk_end;
	u32_process processData;
	struct S_MainStkCtxt s_MainStkCtxt;
	struct S_TaskStkCtxt s_TaskStkCtxt;
	void (*task)(void);
	void (*error_hook)(void);
};
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public volatile u8 u8_task_stack_top;
_public volatile u8 u8_RunningProcess;
_public volatile struct S_ProcessData rs_TaskStruct[AVAILABLE_PROCESS_NUMBER];
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void kernel_ErrorHook(void);

_public boolean kernel_ProcessIsValid(u8 processId);

_public s16 kernel_CreateProcess(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type);
_public s16 kernel_KillProcess(u8 processId);
_public void kernel_TerminateProcess(u8 processId);

#endif /*INCLUDE_EOS_KERNEL_H_*/
