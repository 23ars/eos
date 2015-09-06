/*
 * watchdog.h
 *
 * Created: 8/9/2015 11:27:43 AM
 *  Author: Mihai
 */ 
#ifndef WATCHDOG_H_
#define WATCHDOG_H_
#include "avr/wdt.h"

/// \defgroup watchdog
/// These functions allow the activation of watchdog
/// @{
	
/// Define Watchdog modes. This modes are, in fact the actions that the watchdog will trigger	
typedef enum
{
	WATCHDOG_INTERRUPT_MODE=0x00, ///< interrupt mode
	WATCHDOG_RESET_MODE, ///< reset mode
	WATCHDOG_INTERRUPT_RESET, ///< interrupt and reset mode
	NONE ///< none
}E_WatchDogModes;

/// Define Watchdog timer prescaler
typedef enum
{
	wdt_16ms_prescaler=0x00, ///< 16ms prescaler
	wdt_32ms_prescaler=(1<<WDP0), ///< 32ms prescaler
	wdt_64ms_prescaler=(1<<WDP1), ///< 64ms prescaler
	wdt_125ms_prescaler=(1<<WDP1)|(1<<WDP0), ///< 125ms prescaler
	wdt_250ms_prescaler=(1<<WDP2), ///< 250ms prescaler
	wdt_500ms_prescaler=(1<<WDP2)|(1<<WDP0), ///< 500ms prescaler
	wdt_1s_prescaler=(1<<WDP2)|(1<<WDP1), ///< 1ms prescaler
	wdt_2s_prescaler=(1<<WDP2)|(1<<WDP1)|(1<<WDP0), ///< 2ms prescaler
	wdt_4s_prescaler=(1<<WDP3), ///< 4ms prescaler
	wdt_8s_prescaler=(1<<WDP3)|(1<<WDP0) ///< 8ms prescaler
	
}E_WdtTimerPrescaler;

/* Pointer to the function that will be executed on watchdog interrupt */
_PRIVATE void (*wdt_task)(void)=0; 
/* Watchdog interrupt*/
ISR(WDT_vect);

/* Function that will init the watchdog*/
void wdt_init(E_WatchDogModes lub_watchdog_mode,E_WdtTimerPrescaler lub_wdt_prescaler);

/// Setup the task that will be run on watchdog interrupt, if WATCHDOG_INTERRUPT_MODE or WATCHDOG INTERRUPT_RESET mode was selected
/// \param[in] (*int_task)(void) Pointer to a function that will be called in ISR's body
/// \return void
_PUBLIC void wdt_int_task(void (*int_task)(void));

/// WDT_INIT initialize the watchdog
/// \param[in] lub_watchdog_mode Unsigned Byte representing the watchdog mode
/// \param[in] lub_wdt_prescaler Unsigned Byte representing the watchdog prescaler
#define WDT_INIT(lub_watchdog_mode,lub_wdt_prescaler) wdt_init(lub_watchdog_mode,lub_wdt_prescaler)

/// WDT_DISABLE disable the watchdog
#define WDT_DISABLE() wdt_disable()

/// WDT_CLEAR clear the watchdog
#define WDT_CLEAR() wdt_reset()
/// @} //end of watchdog
#endif /* WATCHDOG_H_ */