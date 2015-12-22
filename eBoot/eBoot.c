/*
 * eBoot.c
 *
 * Created: 12/22/2015 04:54:12 PM
 *  Author: Mihai
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/boot.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "stdtypes.h"
#include <util/delay.h>
#define BAUD 9600
#define BAUDRATE (((F_CPU)/((BAUD)*16UL))-1)



static void uart_init(void)
{
	/*Set baud rate*/
	UBRR0H=(u8)BAUDRATE>>8;	
	UBRR0L=(u8)BAUDRATE;
	/*Enable receiver and transmitter*/
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
	/*Set frame format:8 data bits, 2 stop bits*/
	UCSR0C|=(1<<USBS0)|(3<<UCSZ00);
	/*Set parity even*/
	UCSR0C|=(1<<UPM01);
}

static void uart_transmit(u8 data)
{
	/*Wait for empty transmit buffer*/
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0=data;
	
}
static void uart_receive(ptr_u8 data)
{
	while(!(UCSR0A &(1<<RXC0)));
	*data=UDR0;
	
}

int main(void)
{
	uart_init();
	u8 send_data=0x00;
    while(1)
    {
		uart_transmit(send_data++);
        _delay_ms(100);
    }
}