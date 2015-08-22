/*
* scheduler.c
*
* Created: 8/9/2015 11:24:51 AM
*  Author: Mihai
*/

#include "../../stdtypes.h"
#include "scheduler.h"
#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER0_OVF_vect)
{
	
	ENABLE_PROTECTION();
	rub_schd_counter++;
	DISABLE_PROTECTION();
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
	_PRIVATE UBYTE stack_index=MAX_TASK_NUMBER;	
	_PRIVATE S_Tasks_Struct ls_task;
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
	(*high_prio_task)();	
	(*medium_prio_task)();	
	(*low_prio_task)();	
}


_PUBLIC void init()
{

	ENABLE_PROTECTION();
	if(rub_task_stack_top!=-1)
	{
		rub_task_stack_top=-1;
	}
	/*
	 Timer resolution=(1 / (Input Frequency / Prescale))=0.000004
	 Timer resolution*255= 0.00102=1.02 ms
	*/
	
	TCNT0=0x00;
	TCCR0B|=(1<<CS00)|(1<<CS01);//set 64 prescaler
	TIMSK0=(1<<TOIE0);
	//enable timer0 overflow interrupt

	DDRB=0xFF;
	DISABLE_PROTECTION();
	
}
//extern void Task_1ms