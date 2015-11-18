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

typedef enum
{
	ASYNC=~(1<<UMSEL00)|~(1<<UMSEL01),
	SYNC=(1<<UMSEL00)
}E_UsartTransmissionType;


typedef enum
{
	
	PARITY_DISABLED=~(1<<UPM00)|~(1<<UPM01),
	PARITY_EVEN=(1<<UPM01),
	PARITY_ODD=(1<<UPM01)|(1<<UPM00)
}E_UsartParity;

typedef enum
{
	STOP_BIT_1=~(1<<USBS0),
	STOP_BIT_2=(1<<USBS0)
	
}E_UsartStopBits;



typedef enum
{
	BIT_CHAR_SIZE_5=~(1<<UCSZ02)|~(1<<UCSZ01)|~(1<<UCSZ00),
	BIT_CHAR_SIZE_6=~(1<<UCSZ02)|~(1<<UCSZ01)|(1<<UCSZ00),
	BIT_CHAR_SIZE_7=~(1<<UCSZ02)|(1<<UCSZ01)|~(1<<UCSZ00),
	BIT_CHAR_SIZE_8=~(1<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00),
	BIT_CHAR_SIZE_9=(1<<UCSZ02)|(1<<UCSZ01)|(1<<UCSZ00)
}E_UsartDataBitsSize;

typedef enum
{
	CLOCKPOLARITY_R_F=~(1<<UCPOL0),
	CLOCKPOLARITY_F_R=(1<<UCPOL0)
	
}E_UsartClockPolarity;





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


extern void usart_init(void);
extern void usart_cntl(UWORD opt);
extern void usart_write(UBYTE data);
extern UBYTE usart_read(void);
extern void usart_print(P_BYTE p_string);
#endif