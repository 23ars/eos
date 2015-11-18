/*
 * boot.c
 *
 * Created: 10/24/2015 09:17:56 PM
 *  Author: Mihai
 */ 


#include <avr/io.h>
//#include <avr/boot.h>
//#include <avr/interrupt.h>
//#include <avr/pgmspace.h>

#include "errorcode.h"
#include "stdtypes.h"

#include "../../../os/threading/scheduler.h"

#include "../eos_conf.h"



/*****************************************************
 * Timer configuration function
 * \param[in] void
 * \return void
 *****************************************************/
_PRIVATE void timer_config(void);

_PRIVATE ISR(TIMER0_OVF_vect);

int main(void)
{
	
	/*init scheduler*/
	timer_config();
	
	///*
	//init usart communication
	//
	//*/
	//
	//usart_init();
	//
	
	run_apps();
	

	while(1);
	
}


void timer_config(void)
{
	ENABLE_PROTECTION();
	
	sched_init();
	
	/*
	Timer resolution=(1 / (Input Frequency / Prescale))=0.000004
	Timer resolution*255= 0.00102=1.02 ms
	*/
	
	TCNT0=0x00;
	TCCR0B|=(1<<CS00)|(1<<CS01);//set 64 prescaler
	TIMSK0=(1<<TOIE0);
	//enable timer0 overflow interrupt

	
	DISABLE_PROTECTION();
	
}


ISR(TIMER0_OVF_vect)
{
	Timer_Overflow_ServiceRoutine();
	
}