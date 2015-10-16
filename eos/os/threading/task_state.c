/*
 * task_state.c
 *
 * Created: 10/16/2015 11:06:16 PM
 *  Author: Mihai
 */ 
#include "stdtypes.h"
#include "errorcode.h"
#include "task_stack.h"
#include "task_manager.h"
#include "task_state.h"


_PUBLIC BYTE task_change_state(BYTE task_id,E_Task_State task_state)
{
	if((MAX_TASK_NUMBER<task_id && -1>task_id))
	{
		return -NTID;
	}
	if(OS_DESTROYED==task_state)
	{
		
		return -TSNA;
	}
	ENABLE_PROTECTION();
	rs_task_stack[task_id].rub_Task_State=task_state;
	DISABLE_PROTECTION();
	return SUCCESS;
	
}