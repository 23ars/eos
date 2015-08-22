/*
 * task_manager.c
 *
 * Created: 8/20/2015 11:33:02 PM
 *  Author: Mihai
 */ 

#include "../../stdtypes.h"
#include "../../errorcode.h"
#include "task_stack.h"
#include "task_manager.h"


_PUBLIC UBYTE task_push(S_Tasks_Struct ls_task)
{
	UBYTE lub_errno=SUCCESS;
	
	if(rub_task_stack_top==MAX_TASK_NUMBER-1)
	{
		lub_errno=TSOF;
		
	}
	else
	{
		ENABLE_PROTECTION();
		rub_task_stack_top++;
		rs_task_stack[rub_task_stack_top]=ls_task;
		DISABLE_PROTECTION();
	}
	return lub_errno;
	
}

_PUBLIC UBYTE task_pop()
{
	UBYTE lub_errno=SUCCESS;
	if(rub_task_stack_top==-1)
	{
		lub_errno=TSE;
	}
	else
	{
		ENABLE_PROTECTION();
		rub_task_stack_top--;
		DISABLE_PROTECTION();
	}
	return lub_errno;

}