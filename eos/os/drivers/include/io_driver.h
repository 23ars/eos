/*
 * io_driver.h
 *
 * Created: 8/27/2015 11:12:32 PM
 *  Author: Mihai
 */ 


#ifndef IO_DRIVER_H_
#define IO_DRIVER_H_

#define MAX_OPS_NO 256


//interfaces for I/O drivers: gpio, eeprom etc


typedef enum
{
	SEEK_SET=0x00,
	SEEK_CURRENT,
	SEEK_END	
}E_Seek_Location;

typedef enum
{
	GPIO_DRIVER=0x00,
	EEP_DRIVER
		
}E_Driver_Type;



_PUBLIC struct io_file
{
	void (*io_write)(volatile P_UBYTE,UDWORD);//return error code, input:address,data
	UDWORD (*io_read)(volatile P_UBYTE,UBYTE);//return error_code, input:address/port, output data
	E_Driver_Type dt;
	union 
	{
		UWORD (*io_seek)(UWORD,E_Seek_Location);//return offset/address input:offset/address, enum		
		BYTE (*io_conf)(UBYTE,UBYTE,UBYTE);
	}special_fct;
	
};

struct descriptors
{
	UBYTE ub_is_location_used;
	struct io_file op;	
};

_PRIVATE struct descriptors ops[MAX_OPS_NO];

_PUBLIC int ops_add(struct io_file s_desc);
_PUBLIC void ops_rem(int desc);



#endif /* IO_DRIVER_H_ */