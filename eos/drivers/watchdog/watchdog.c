/*
 * watchdog.c
 *
 * Created: 8/9/2015 11:27:53 AM
 *  Author: Mihai
 */ 
#include "stdtypes.h"
#include "avr/wdt.h"
#include <avr/interrupt.h>
#include "watchdog.h"

/* Pointer to the function that will be executed on watchdog interrupt */
_PRIVATE void (*wdt_task)(void)=0;
/* Watchdog interrupt*/
ISR(WDT_vect);
/* Function that will init the watchdog*/
_PRIVATE void wdt_init(E_WatchDogModes lub_watchdog_mode,E_WdtTimerPrescaler lub_wdt_prescaler);

ISR(WDT_vect)
{
	(*wdt_task)();	
	
}

_PUBLIC void wdt_int_task(void (*int_task)(void))
{
	wdt_task=int_task;
}


void wdt_init(E_WatchDogModes lub_watchdog_mode,E_WdtTimerPrescaler lub_wdt_prescaler)
{
	ENABLE_PROTECTION();
	
	wdt_reset();										/* reset the watchdog*/
	switch(lub_watchdog_mode)
	{
		case WATCHDOG_INTERRUPT_MODE:
			WDTCSR|=(1<<WDIE);
		break;
		case WATCHDOG_RESET_MODE:
			WDTCSR|=(1<<WDE);
			break;
		case WATCHDOG_INTERRUPT_RESET:
			WDTCSR|=(1<<WDE)|(1<<WDIE);					/* set up int & reset mode */
			break;
		default:
			{
				BIT_CLEAR(WDTCSR,WDE);
				BIT_CLEAR(WDTCSR,WDIE);
				break;
			}
	}
	WDTCSR|=lub_wdt_prescaler;							/* set up timer prescaler */
	DISABLE_PROTECTION();
	
}