/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "configuration.h"
#include "errno.h"

#include "process.h"
/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
volatile struct S_ProcessData rs_TaskStruct[AVAILABLE_PROCESS_NUMBER];
volatile u8 u8_task_stack_top=0;

/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_private s16 create(void (*task)(void),void (*error_hook)(void),E_TaskPriority priority,E_TaskType task_type);
/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */
void process_Init(void)
{
	u8_task_stack_top=0;
	/*set internal process (error hook for kernel)*/
	mem_fill(&rs_TaskStruct[u8_task_stack_top],0,sizeof(sizeof(struct S_ProcessData)));
}
s16 create_process(void (*task)(void),void (*error_hook)(void),E_TaskPriority priority,E_TaskType task_type)
{
	/*returns -1 in case of error or a number >0 that represents the process id.*/
	u8 errorNumber=EOK;

	enable_protection();
	if(create(task,error_hook,priority,task_type)!=0){
		errorNumber=ETSOF;
	}
	disable_protection();
	return ((errorNumber==EOK)?0:-1);
}


s16 kill_process(u8 processId)
{
	if(processId==0)
	{
		/*cannot kill reserved process*/
		errno=ERSPR;
		return -1;
	}
	if(AVAILABLE_PROCESS_NUMBER<processId){
		errno=EIDNR;
		return -1;
	}
	enable_protection();
	rs_TaskStruct[processId].process_state=BLOCKED;
	disable_protection();
	return 0;
}


s16 create(void (*task)(void),void (*error_hook)(void),E_TaskPriority priority,E_TaskType task_type)
{
	u8 taskIndex=0;
	boolean is_found=FALSE;
	struct S_ProcessData ls_Task;
	mem_fill(&ls_Task,0,sizeof(struct S_ProcessData));
	ls_Task.process_state=READY;
	ls_Task.priority=priority;
	ls_Task.processId=u8_task_stack_top;
	ls_Task.task=task;
	ls_Task.task_type=task_type;
	ls_Task.error_hook=error_hook;
#ifndef USE_MEMORY_PROTECTION
	ls_Task.is_emp_used=NO_MPU;
#endif
	for(taskIndex=0;taskIndex<AVAILABLE_PROCESS_NUMBER;taskIndex++){
		if(rs_TaskStruct[taskIndex].process_state==BLOCKED){
			is_found=TRUE;
			break;
		}
	}
	if(is_found==TRUE){
		rs_TaskStruct[taskIndex]=ls_Task;
		return 0;
	}

	if((AVAILABLE_PROCESS_NUMBER-1)==u8_task_stack_top){
		return -1;
	}

	u8_task_stack_top++;
	rs_TaskStruct[u8_task_stack_top]=ls_Task;
	return 0;
}


