/*
 * test_item.c
 *
 * Created: 8/22/2015 7:09:44 PM
 *  Author: Mihai
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "../os/stdtypes.h"
#include "../arch/architecture.h"
#include "../os/app_register.h"
#include "../os/threading/mutex.h"
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
	lock_mutex();
	PORTB^=(1<<PINB0);
	unlock_mutex();
}

void exit_port()
{
	DDRB=0x00;
	
}


app_init(init_port);
app_exit(exit_port);