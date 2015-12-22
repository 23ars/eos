#include <avr/io.h>
#include "stdtypes.h"
#include "usart.h"

#ifdef INTERRUPT_TX_TRANSFER
ISR(USART_TX_vect)
{
	UDR0=send_data;	
	
}
#endif
#ifdef INTERRUPT_RX_TRANSFER
ISR(USART_RX_vect)
{
	received_data=UDR0;
}
#endif
void usart_cntl(u16 opt)
{
	UCSR0C|=opt;
	
}


void usart_init(void)
{
	UBRR0H=(u8)(BAUD_PRESCALLER>>8);
	UBRR0L=(u8)(BAUD_PRESCALLER);
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
//	UCSR0C=((1<<UCSZ00)|(1<<UCSZ01));
#ifdef INTERRUPT_RX_TRANSFER	
	UCSR0B|=(1<<RXCIE0);
#endif
#ifdef INTERRUPT_TX_TRANSFER
	UCSR0B|=(1<<TXCIE0);
#endif	
}

void usart_write(u8 data)
{
#ifndef INTERRUPT_TX_TRANSFER
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=data;
#else
	send_data=data;
#endif
}

u8 usart_read(void)
{
#ifndef INTERRUPT_RX_TRANSFER
	while(!(UCSR0A &(1<<RXC0)));
	return UDR0;
#else
	return received_data;
#endif

	
}

void usart_print(ptr_s8 p_string)
{
	while(*p_string)
	{
		usart_write(*p_string);
		p_string++;
	}
}