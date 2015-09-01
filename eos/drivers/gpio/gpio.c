/*
 * gpio.c
 *
 * Created: 8/27/2015 11:06:13 PM
 *  Author: Mihai
 */ 

#include "stdtypes.h"
#include "driver_register.h"
#include "io_driver.h"
#include "threading.h"
#include "gpio.h"


void gpio_write(volatile P_UBYTE addr,UDWORD data)
{

	lock_mutex();
	*addr=data;
	unlock_mutex();
	
}
UDWORD gpio_read(volatile P_UBYTE addr,UBYTE no_of_blocks)
{
	lock_mutex();
	UDWORD data=*addr;
	unlock_mutex();
	return data;
	
}
BYTE gpio_configure(UBYTE dir,UBYTE pld,UBYTE ev)
{
	
}

_PRIVATE void _init(void)
{
	
	gpio_file_descriptor=ops_add(gpio_file);
	driver_descriptor=gpio_file_descriptor;
	
}


_PRIVATE void _exit(void)
{
	if(gpio_file_descriptor!=-1)
	{
		ops_rem(gpio_file_descriptor);
	}
	
}

driver_init(_init);
driver_exit(_exit);