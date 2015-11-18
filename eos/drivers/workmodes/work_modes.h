#ifndef WORK_MODES_H_
#define WORK_MODES_H_
#include <avr/io.h>
/// \defgroup work_modes
/// These functions allows the activation of various work modes
/// @{
	
/// Sleep modes of an ATmega microcontroller, in this case ATmega328p
typedef enum
{
	SLEEP_MODE_IDLE=0x00, ///< idle 
	SLEEP_MODE_ADC=(1<<SM0), ///< adc noise reduction 
	SLEEP_MODE_PWR_DOWN=(1<<SM1), ///< power-down
	SLEEP_MODE_PWR_SAVE=(1<<SM0)|(1<<SM1), ///< power save
	SLEEP_MODE_STANDBY=(1<<SM2)|(1<<SM1), ///< standby
	SLEEP_MODE_EXT_STANDBY=(1<<SM2)|(1<<SM1)|(1<<SM0) ///< extended standby
}E_Sleep_modes;

/// Functionalities that can be shutdown when enter in sleep mode
typedef enum
{
	ShutDown_ALL=(1<<PRTWI)|(1<<PRTIM2)|(1<<PRTIM0)|(1<<PRTIM1)|(1<<PRSPI)|(1<<PRUSART0)|(1<<PRADC),///< shutdown all
	ShutDown_TWI=(1<<PRTWI), ///< shutdown only TWI
	ShutDown_TIMER_2=(1<<PRTIM2), ///< shutdown only TIMER2
	ShutDown_TIMER_1=(1<<PRTIM1), ///< shutdown only TIMER1
	ShutDown_TIMER_0=(1<<PRTIM0), ///< shutdown only TIMER0
	ShutDown_SPI=(1<<PRSPI), ///< shutdown only SPI
	ShutDown_USART=(1<<PRUSART0), ///< shutdown only USART
	ShutDown_ADC=(1<<PRADC) ///< shutdown only ADC
	
}E_ShudDown_Modules;

/// Pointer to the function that will set up the wakeup condition
_PRIVATE void (*wm_wakeup_condition)(void)=0; 

/// Initialize Sleep mode
/// \param[in] lub_sleep_mode Unsigned Byte variable that represents the Sleep mode
/// \param[in] lub_sleep_modules Unsigned Byte variable that represents the modules that will be shutdown
/// \param[in] (*_wakeup_condition)(void) Pointer to function that will set up the wakeup condition
/// \return void
_PUBLIC void wm_init(E_Sleep_modes lub_sleep_mode,E_ShudDown_Modules lub_sleep_modules,void (*_wakeup_condition)(void));



/// Wakeup from sleep mode 
#define WORK_MODE_WAKEUP() wm_wakeup()
/// @} //end of work_modes


#endif /* WORK_MODES_H_ */