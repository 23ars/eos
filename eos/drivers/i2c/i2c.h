#ifndef I2C_H_
#define I2C_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifdef TWI_PRESCALER_1
#define TWI_PRESCALER 1
#elif defined TWI_PRESCALER_4
#define TWI_PRESCALER 4
#elif defined TWI_PRESCALER_16
#define TWI_PRESCALER 16
#elif defined TWI_PRESCALER_64
#define TWI_PRESCALER 64
#else
#define TWI_PRESCALER_1
#define TWI_PRESCALER 1
#endif


#ifndef PORT_SDA
#define PORT_SDA PORTC
#endif

#ifndef PIN_SDA
#define PIN_SDA 4
#endif

#define WRITE_SDA() PORT_SDA = PORT_SDA | (1<<PIN_SDA) //SDA must be output when writing
#define READ_SDA()  PORT_SDA = PORT_SDA & ~(1<<PIN_SDA)

//TWI bit rate
#ifndef TWI_FREQ
#define TWI_FREQ 100000
#endif

#ifndef TWI_STATUS
#define TWI_STATUS (TWSR&0xF8)
#endif

#ifndef TWI_MAX_DATA_BUFFER
#define TWI_MAX_DATA_BUFFER 32
#endif

typedef enum
{
	READY,
	INIT,
	REPEATED_START_SENT,
	MASTER_TX,
	MASTER_RX,
	SLAVE_TX,
	SLAVE_RX
}TWI_MODE;

typedef struct _TWI_INFO_STRUCT
{
	TWI_MODE mode;
	u8 error_code;
	BOOL repeated_start;
	
}TWI_INFO_STRUCT;

TWI_INFO_STRUCT TWI_info;

// TWI Status Codes
#define TWI_START_SENT			0x08 // Start sent
#define TWI_REP_START_SENT		0x10 // Repeated Start sent
// Master Transmitter Mode
#define TWI_MT_SLAW_ACK			0x18 // SLA+W sent and ACK received
#define TWI_MT_SLAW_NACK		0x20 // SLA+W sent and NACK received
#define TWI_MT_DATA_ACK			0x28 // DATA sent and ACK received
#define TWI_MT_DATA_NACK		0x30 // DATA sent and NACK received
// Master Receiver Mode
#define TWI_MR_SLAR_ACK			0x40 // SLA+R sent, ACK received
#define TWI_MR_SLAR_NACK		0x48 // SLA+R sent, NACK received
#define TWI_MR_DATA_ACK			0x50 // Data received, ACK returned
#define TWI_MR_DATA_NACK		0x58 // Data received, NACK returned

// Miscellaneous States
#define TWI_LOST_ARBIT			0x38 // Arbitration has been lost
#define TWI_NO_RELEVANT_INFO	0xF8 // No relevant information available
#define TWI_ILLEGAL_START_STOP	0x00 // Illegal START or STOP condition has been detected
#define TWI_SUCCESS				0xFF // Successful transfer, this state is impossible from TWSR as bit2 is 0 and read only


#define TWI_SEND_START() (TWCR=(1<<TWINT)|(1<<TWSTA)|(~(1<<TWSTO))|(1<<TWEN)|(1<<TWIE))//send START, enable interrupt
#define TWI_SEND_STOP()	 (TWCR=(1<<TWINT)|(~(1<<TWSTA))|(1<<TWSTO)|(1<<TWEN)|(1<<TWIE))//send STOP, enable interrupt

#define TWI_SEND_TX()	(TWCR=(1<<TWINT)||(1<<TWEN)|(1<<TWIE))
#define TWI_SEND_ACK()   (TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA))
#define TWI_SEND_NACK()	(TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWIE))

volatile u8 tx_data_buffer[TWI_MAX_DATA_BUFFER];
volatile u8 tx_data_index;
volatile u8 tx_address_buffer;

volatile u8 rx_data_buffer[TWI_MAX_DATA_BUFFER];
volatile u8 rx_data_index;
volatile u8 rx_address_buffer;
volatile u8 rx_buffer_index;
extern void TWI_init(void);

extern void TWI_tx_data(ptr_u8 data,u8 data_length,u8 address,BOOL repeated_start);

extern void TWI_rx_data(u8 address,u8 data_length,BOOL repeated_start);

extern ptr_u8 TWI_get_data();

extern u8 TWI_get_mode();

extern u8 TWI_get_error_code();

#endif /* I2C_H_ */