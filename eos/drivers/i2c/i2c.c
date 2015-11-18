#include <avr/io.h>

#include "stdtypes.h"

#include <util/delay.h>
#include "i2c.h"
void TWI_init(void)
{
	
	TWI_info.mode=READY;
	TWI_info.error_code=0xFF;
	TWI_info.repeated_start=0;
	#ifdef TWI_PRESCALER_1
	TWSR|=~(1<<TWPS1)|~(1<<TWPS0);
	#endif
	#ifdef TWI_PRESCALER_4
	TWSR|=~(1<<TWPS1)|(1<<TWPS0);
	#endif
	#ifdef TWI_PRESCALER_16
	TWSR|=(1<<TWPS1)|(1<<TWPS0);
	#endif
	#ifdef TWI_PRESCALER_64
	TWSR|=(1<<TWPS1)|(1<<TWPS0);
	#endif
	//Set bit rate
	TWBR=((F_CPU/TWI_FREQ)-16)/(2*TWI_PRESCALER);
	//enable TWI and INT
	TWCR=(1<<TWIE)|(1<<TWEN);
	TWI_info.mode=READY;
	
}

ISR(TWI_vect)
{
	switch(TWI_STATUS)
	{
		case TWI_START_SENT:
		{

			if(TWI_info.mode==MASTER_TX)
			{
				
				TWDR=tx_address_buffer;
				TWI_info.mode=MASTER_TX;
				goto send_ack;
			}
			if(TWI_info.mode==MASTER_RX)
			{
				
				TWDR=rx_address_buffer;
				TWI_info.mode=MASTER_RX;
				goto send_ack;
			}
			if(TWI_info.mode==INIT)
			{
				TWI_info.mode=READY;
				goto do_not_send;
			}
			
			do_not_send:
			break;
			send_ack:
			TWI_SEND_ACK();
			break;
		}
		
		case TWI_MT_SLAW_ACK:
		{

			if(tx_data_buffer[tx_data_index])
			{
				
				TWDR=tx_data_buffer[tx_data_index];
				tx_data_index++;
				TWI_info.mode=MASTER_TX;
				TWI_SEND_ACK();
			}
			else
			{
				if(TWI_info.repeated_start==TRUE)
				{
					TWI_info.mode=REPEATED_START_SENT;
					TWI_SEND_START();
					
				}
				else
				{
					TWI_info.mode=READY;
					TWI_SEND_STOP();
				}
			}
			
			break;
		}
		case TWI_MT_SLAW_NACK:
		{

			if(tx_data_buffer[tx_data_index])
			{
				
				TWDR=tx_data_buffer[tx_data_index];
				tx_data_index++;
				TWI_info.mode=MASTER_TX;
				TWI_SEND_NACK();
			}
			else
			{
				if(TWI_info.repeated_start==TRUE)
				{
					TWI_info.mode=REPEATED_START_SENT;
					TWI_SEND_START();
					
				}
				else
				{
					TWI_info.mode=READY;
					TWI_SEND_STOP();
				}
				tx_data_index=0;
			}
			break;
		}
		case TWI_MR_SLAR_ACK:
		{
			
			rx_data_buffer[rx_buffer_index]=TWDR;
			TWI_info.mode=MASTER_RX;
			
			if(rx_buffer_index<rx_data_index)
			{
				rx_buffer_index++;
				TWI_SEND_ACK();
			}
			else
			{
				
				TWI_SEND_NACK();
			}
			
			break;
		}
		case TWI_MR_SLAR_NACK:
		{
			
			if(TWI_info.repeated_start==TRUE)
			{
				TWI_info.mode=REPEATED_START_SENT;
				TWI_SEND_START();
				
			}
			else
			{
				TWI_SEND_STOP();
				TWI_info.mode=READY;
			}
			rx_buffer_index=0;
			break;
		}
		case TWI_LOST_ARBIT:
		{
			TWI_info.mode=READY;
			TWI_info.error_code=TWI_STATUS;
			rx_buffer_index=0;
			break;
			
		}
	}
}


void TWI_tx_data(P_UBYTE data,UBYTE data_length,UBYTE address,BOOL repeated_start)
{
	
	TWI_info.repeated_start=repeated_start;
	
	
	if(data_length<=TWI_MAX_DATA_BUFFER)
	{
		UBYTE iindex=0;
		for(iindex=0;iindex<data_length;iindex++)
		{
			tx_data_buffer[iindex]=data[iindex];
		}
		
		TWI_info.mode=MASTER_TX;
		if(TWI_info.mode==REPEATED_START_SENT)
		{
			

			TWDR=address;
			
			TWI_SEND_ACK();
		}
		else
		{
			
			tx_address_buffer=address;
			
			TWI_SEND_START();
		}
		
	}
}

void TWI_rx_data(UBYTE address,UBYTE data_length,BOOL repeated_start)
{
	TWI_info.repeated_start=repeated_start;
	if(data_length<=TWI_MAX_DATA_BUFFER)
	{
		TWI_info.mode=MASTER_RX;
		if(TWI_info.mode==REPEATED_START_SENT)
		{
			
			TWDR=address;
			TWI_SEND_ACK();
			
		}
		else
		{
			
			
			rx_data_index=data_length;
			rx_address_buffer=address;
			TWI_SEND_START();
		}
		
		
	}
	
}

 P_UBYTE TWI_get_data()
 {
	 return rx_data_buffer;
	 
 }

 UBYTE TWI_get_mode()
 {
	 return TWI_info.mode;
 }

 UBYTE TWI_get_error_code()
 {
	 return TWI_info.error_code;
 }