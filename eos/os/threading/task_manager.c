#include "stdtypes.h"
#include "errorcode.h"
#include "task_stack.h"
#include "task_manager.h"


_PUBLIC BYTE task_push(S_Tasks_Struct ls_task)
{
	BYTE lb_errno=SUCCESS;
	
	if(rub_task_stack_top==MAX_TASK_NUMBER-1)
	{
		lb_errno=-ETSOF;
		
	}
	else
	{
		ENABLE_PROTECTION();
		rub_task_stack_top++;
		rs_task_stack[rub_task_stack_top]=ls_task;
		rs_task_stack[rub_task_stack_top].rub_Task_State=TASK_ACTIVE;
		DISABLE_PROTECTION();
	}
	return rub_task_stack_top;
	
}

_PUBLIC UBYTE task_pop(void)
{
	UBYTE lub_errno=SUCCESS;
	if(rub_task_stack_top==-1)
	{
		lub_errno=ETSE;
	}
	else
	{
		ENABLE_PROTECTION();
		rub_task_stack_top--;
		DISABLE_PROTECTION();
	}
	return lub_errno;

}