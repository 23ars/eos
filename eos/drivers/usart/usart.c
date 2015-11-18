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
void usart_cntl(UWORD opt)
{
	UCSR0C|=opt;
	
}


void usart_init(void)
{
	UBRR0H=(UBYTE)(BAUD_PRESCALLER>>8);
	UBRR0L=(UBYTE)(BAUD_PRESCALLER);
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
//	UCSR0C=((1<<UCSZ00)|(1<<UCSZ01));
#ifdef INTERRUPT_RX_TRANSFER	
	UCSR0B|=(1<<RXCIE0);
#endif
#ifdef INTERRUPT_TX_TRANSFER
	UCSR0B|=(1<<TXCIE0);
#endif	
}

void usart_write(UBYTE data)
{
#ifndef INTERRUPT_TX_TRANSFER
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0=data;
#else
	send_data=data;
#endif
}

UBYTE usart_read(void)
{
#ifndef INTERRUPT_RX_TRANSFER
	while(!(UCSR0A &(1<<RXC0)));
	return UDR0;
#else
	return received_data;
#endif

	
}

void usart_print(P_BYTE p_string)
{
	while(*p_string)
	{
		usart_write(*p_string);
		p_string++;
	}
}