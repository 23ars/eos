#include "stdtypes.h"

#include "scheduler.h"

_private volatile u8 rub_schd_counter;

_public void Timer_Overflow_ServiceRoutine(void);
_private void (*high_prio_task)(void)=0;
_private void (*medium_prio_task)(void)=0;
_private void (*low_prio_task)(void)=0;
_private void execute_task(E_AvailableTasks task_scheduler);

void Timer_Overflow_ServiceRoutine(void)
{
	
	enable_protection();
	rub_schd_counter++;

	disable_protection();
	
	if(rub_schd_counter%E_Task_5ms==0)
	{
		execute_task(E_Task_5ms);
	}
	if(rub_schd_counter%E_Task_10ms==0 )
	{
		execute_task(E_Task_10ms);
	}
	if(rub_schd_counter%E_Task_20ms==0 )
	{

		execute_task(E_Task_20ms);
	}

	
}

void execute_task(E_AvailableTasks task_scheduler)
{

	if(rub_task_stack_top==-1)
	{
		return;
	}	
	
	_private s8 stack_index=0;
	_private S_Tasks_Struct ls_task;
	stack_index=rub_task_stack_top;
	
	while(stack_index>=0)
	{

		ls_task=rs_task_stack[stack_index];
		if(ls_task.task==0)
		{
					
			stack_index--;
			continue;
		}
		
		if(ls_task.rub_Task_Schedule!=task_scheduler)
		{
			
			stack_index--;
			continue;
		}

		if(TASK_BLOCKED==ls_task.rub_Task_State )
		{
			stack_index--;
			continue;
		}
		if(TASK_SLEEPING==ls_task.rub_Task_State)
		{
			rs_task_stack[stack_index].rub_Task_State=TASK_BLOCKED;
			
		}
		
		rub_thread_id=stack_index;
		switch(ls_task.rub_Task_Priority)
		{
			
			case TASK_HIGH_PRIO:
				high_prio_task=ls_task.task;break;
			case TASK_MEDIUM_PRIO:
				medium_prio_task=ls_task.task;break;
			case TASK_LOW_PRIO:
				low_prio_task=ls_task.task;break;
		}
		stack_index--;
	}
	if(stack_index<0)
	{
		stack_index=rub_task_stack_top;		
	}
	
	if(high_prio_task!=0)
	{
		(*high_prio_task)();
	}
	if(medium_prio_task!=0)
	{
		(*medium_prio_task)();
	}
	if(low_prio_task!=0)
	{
		(*low_prio_task)();
	}
	

}


_public void sched_init()
{

	
	
	rub_task_stack_top=-1;
	
	
	
}
//extern void Task_1ms