/*
 * test_item.c
 *
 * Created: 8/22/2015 7:09:44 PM
 *  Author: Mihai
 */ 
#include "../os/stdtypes.h"
#include <avr/io.h>
#include "../os/sw/task_manager/scheduler.h"
#include "../os/sw/task_manager/task_manager.h"
#include "test_item.h"

void init_port()
{
	
	DDRB=0xFF;
	S_Tasks_Struct task_20;
	task_20.rub_Task_Priority=TASK_HIGH_PRIO;
	task_20.rub_Task_Schedule=E_Task_20ms;
	task_20.task=&toggle_led;
	if(task_push(task_20)==0)
	{
		PORTB|=(1<<PINB3);
	}
	else
	{
		PORTB|=(1<<PINB4);
	}
	
}
void toggle_led()
{
	PORTB^=(1<<PINB0);

}