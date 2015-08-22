/*
 * work_modes.c
 *
 * Created: 8/9/2015 5:43:32 PM
 *  Author: Mihai
 */ 
#include "../../stdtypes.h"

#include "work_modes.h"


_PUBLIC void wm_init(E_Sleep_modes lub_sleep_mode,E_ShudDown_Modules lub_sleep_modules,void (*_wakeup_condition)(void))
{
	DISABLE_INTERRUPTS;
	PRR|=lub_sleep_modules;/*set modules to sleep*/
	SMCR|=lub_sleep_mode; /*select sleep mode */
	
	ENABLE_INTERRUPTS; /*allow interrupt to end sleep mode*/
	
	wm_wakeup_condition=_wakeup_condition; /*wakeup condition*/
	
	SMCR=(1<<SE);/*enter sleep mode*/
	
	
	
}

void wm_wakeup()
{
	SMCR&=~(1<<SE);	//disable sleep
	
}

