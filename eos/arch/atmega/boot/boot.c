#include <avr/io.h>
#include "eos_conf.h"
#include "stdtypes.h"

#include "../threading/scheduler.h"





/*****************************************************
 * Timer configuration function
 * \param[in] void
 * \return void
 *****************************************************/
_private void timer_config(void);

/*lint -save -e10 It's just the declaration of the ISR */
void __vector_16 (void) __attribute__ ((signal,__INTR_ATTRS));
/*lint-restore*/

int main(void)
{
	
	/*init scheduler*/
	timer_config();
	
	run_apps();
	
	while(1);
	/*Just an infinite loop to keep the application running*/

	
}

/*lint -save -e40 -e63 -e522 TCNT0, TCCR0B and TIMSK0 are registers defined in avr/io.h. Since
This header is not included to be parsed by Lint, the static compiler doesn't recognize them */
_private void timer_config(void)
{
	enable_protection();
	
	sched_init();
	
	/*
	Timer resolution=(1 / (Input Frequency / Prescale))=0.000004
	Timer resolution*255= 0.00102=1.02 ms
	*/
	
	TCNT0=0x00;
	TCCR0B|=(1<<CS00)|(1<<CS01);/*set 64 prescaler*/
	TIMSK0=(1<<TOIE0);
	

	
	disable_protection();
	
}
/*lint-restore*/
/*lint -save -e31 The implementation of ISR*/
void __vector_16(void)
{
	
	Timer_Overflow_ServiceRoutine();
	
}
/*lint-restore*/
