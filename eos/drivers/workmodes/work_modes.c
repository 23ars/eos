#include "stdtypes.h"

#include "work_modes.h"

_private void wm_wakeup();

_public void wm_init(E_Sleep_modes lub_sleep_mode,E_ShudDown_Modules lub_sleep_modules,void (*_wakeup_condition)(void))
{
	enable_protection();
	PRR|=lub_sleep_modules;/*set modules to sleep*/
	SMCR|=lub_sleep_mode; /*select sleep mode */
	
	disable_protection(); /*allow interrupt to end sleep mode*/
	
	wm_wakeup_condition=_wakeup_condition; /*wakeup condition*/
	
	SMCR=(1<<SE);/*enter sleep mode*/
	
	
	
}

void wm_wakeup()
{
	SMCR&=~(1<<SE);	//disable sleep
	
}

