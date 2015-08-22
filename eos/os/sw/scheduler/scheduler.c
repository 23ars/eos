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
	DISABLE_INTERRUPTS;
	rub_schd_counter++;
	ENABLE_INTERRUPTS;
	if(Task_1ms!=0)
	{
		(*Task_1ms)();	
	}
	if(rub_schd_counter%E_Task_5ms==0 && Task_5ms!=0)
	{
		(*Task_5ms)();
	}
	if(rub_schd_counter%E_Task_10ms==0 && Task_10ms!=0)
	{
		(*Task_10ms)();
	}
	if(rub_schd_counter%E_Task_20ms==0 && Task_20ms!=0)
	{
		(*Task_20ms)();
	}
	
}

_PUBLIC void init(void (*sc_1ms_task)(void),void (*sc_5ms_task)(void),void (*sc_10ms_task)(void),void (*sc_20ms_task)(void))
{

	DISABLE_INTERRUPTS;
	Task_1ms=sc_1ms_task;
	Task_5ms=sc_5ms_task;
	Task_10ms=sc_10ms_task;
	Task_20ms=sc_20ms_task;
	
	/*
	 Timer resolution=(1 / (Input Frequency / Prescale))=0.000004
	 Timer resolution*255= 0.00102=1.02 ms
	*/
	
	TCNT0=0x00;
	TCCR0B|=(1<<CS00)|(1<<CS01);//set 64 prescaler
	TIMSK0=(1<<TOIE0);
	//enable timer0 overflow interrupt

	DDRB=0xFF;
	ENABLE_INTERRUPTS;
	
}
//extern void Task_1ms