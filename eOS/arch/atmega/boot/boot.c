/*
* eos.c
*
* Created: 2/3/2016 11:43:34 PM
*  Author: Mihai
*/


#include <avr/io.h>
#include "eos_conf.h"
#include "stdtypes.h"

#include "scheduler.h"





/*****************************************************
* Timer configuration function
* \param[in] void
* \return void
*****************************************************/
_private void timer_config(void);


void __vector_16 (void) __attribute__ ((signal,__INTR_ATTRS));






_private void timer_config(void)
{
	enable_protection();

	sched_init();

	/*
	Timer resolution=(1 / (Input Frequency / Prescale))=0.000004
	Timer resolution*255= 0.00102=1.02 ms
	*/

	//TCNT0=0x00;
	//TCCR0B|=(1<<CS00)|(1<<CS01);/*set 64 prescaler*/
	//TIMSK0=(1<<TOIE0);



	disable_protection();

}

void __vector_16(void)
{

	//Timer_Overflow_ServiceRoutine();

}
