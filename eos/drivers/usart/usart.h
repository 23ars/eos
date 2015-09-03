/*
 * usart.h
 *
 * Created: 5/16/2015 1:40:10 PM
 *  Author: Mihai
 */ 
#ifndef USART_H_
#define USART_H_
/*
1 start bit
5, 6, 7, 8, or 9 data bits
no, even or odd parity bit
1 or 2 stop bits
*/


#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifdef ASYNC
UCSR0C|=~(1<<UMSEL00)|~(1<<UMSEL01);
#endif

#ifdef SYNC
UCSR0C|=(1<<UMSEL00);
#endif

#ifdef PARITY_DISABLED
UCSR0C|=~(1<<UPM00)|~(1<<UPM01)
#endif

#ifdef PARITY_EVEN
UCSR0C|=(1<<UPM01)
#endif

#ifdef PARITY_ODD
UCSR0|=(1<<UPM01)|(1<<UPM00)
#endif

#ifdef _STOP_BIT_1
UCSR0C|=~(1<<USBS0)
#endif

#ifdef _STOP_BIT_2
UCSR0C|=(1<<USBS0)
#endif

#ifdef _BIT_CHAR_SIZE_5
UCSR0C|=~(1<<UCSZ02)|~(1<<UCSZ01)|~(1<<UCSZ00)
#endif

#ifdef _BIT_CHAR_SIZE_6
UCSR0C|=~(1<<UCSZ02)|~(1<<UCSZ01)|(1<<UCSZ00)
#endif

#ifdef _BIT_CHAR_SIZE_7
UCSR0C|=~(1<<UCSZ02)|(1<<UCSZ01)|~(1<<UCSZ00)
#endif

#ifdef _BIT_CHAR_SIZE_8
UCSR0C|=~(1<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00)
#endif


#ifdef _BIT_CHAR_SIZE_9
UCSR0C|=(1<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00)
#endif

#ifdef CLOCKPOLARITY_R_F
UCSR0C|=~(1<<UCPOL0)
#endif

#ifdef CLOCKPOLARITY_F_R
UCSR0C|=(1<<UCPOL0)
#endif

#ifndef BAUD_PRESCALLER
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
#endif

#ifdef INTERRUPT_RX_TRANSFER
ISR(USART_RX_vect);
volatile UBYTE received_data;
#endif
#ifdef INTERRUPT_TX_TRANSFER
ISR(USART_TX_vect);
volatile UBYTE send_data;
#endif


extern void USART_init(void);
extern void USART_write(UBYTE data);
extern UBYTE USART_read(void);
extern void USART_print(P_BYTE p_string);
#endif