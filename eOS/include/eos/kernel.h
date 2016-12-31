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
#define KERNEL_CONTEXT_SAVE()
#define KERNEL_CONTEXT_RESTORE()

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

inline void kernel_DisableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus&=~KERNEL_SCHEDULER_FLAG;
	disable_protection();
}
inline void kernel_EnableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus|=KERNEL_SCHEDULER_FLAG;
	disable_protection();
}
_public void kernel_ErrorHook(void);

_public boolean kernel_ProcessIsValid(void);

_public s16 kernel_CreateProcess(void (*task)(void), void (*error_hook)(void),
		E_TaskPriority priority, E_TaskType task_type);
_public s16 kernel_KillProcess(u8 processId);
_public void kernel_TerminateProcess(u8 processId);
#endif /*INCLUDE_EOS_KERNEL_H_*/
