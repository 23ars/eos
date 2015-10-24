/*
 * boot.c
 *
 * Created: 10/24/2015 09:17:56 PM
 *  Author: Mihai
 */ 


#include <avr/io.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "errorcode.h"
#include "stdtypes.h"
#include "architecture.h"
#include "../../drivers/usart/usart.h"
#include "../eos_conf.h"




int main(void)
{
	/*init scheduler*/
	sched_init();
	
	/*
	init usart communication
	
	*/
	UWORD uart_ctl=STOP_BIT_2|BIT_CHAR_SIZE_8|PARITY_DISABLED|STOP_BIT_1;
	usart_init();
	usart_cntl(uart_ctl);
	
	run_apps();
	
	/*disable usart*/
	while(1);
	
}