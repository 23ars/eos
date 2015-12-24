#include "stdtypes.h"
#include "errorcode.h"
#include "task_stack.h"
#include "task_manager.h"


_public s8 task_push(S_Tasks_Struct ls_task)
{
	s8 lb_errno=SUCCESS;
	
	if(rub_task_stack_top==MAX_TASK_NUMBER-1)
	{
		lb_errno=-ETSOF;
		
	}
	else
	{
		enable_protection();
		rub_task_stack_top++;
		rs_task_stack[rub_task_stack_top]=ls_task;
		rs_task_stack[rub_task_stack_top].rub_Task_State=TASK_ACTIVE;
		disable_protection();
		lb_errno=rub_task_stack_top;
	}
	
	return lb_errno;
	
}

_public u8 task_pop(void)
{
	u8 lub_errno=SUCCESS;
	if(rub_task_stack_top==-1)
	{
		lub_errno=ETSE;
	}
	else
	{
		enable_protection();
		rub_task_stack_top--;
		disable_protection();
	}
	return lub_errno;

}