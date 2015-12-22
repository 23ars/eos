#include "stdtypes.h"
#include "threading.h"
#include "gpio.h"


void gpio_write(volatile ptr_u8 addr,u32 data)
{

	lock_mutex();
	*addr=data;
	unlock_mutex();
	
}
u32 gpio_read(volatile ptr_u8 addr,u8 no_of_blocks)
{
	lock_mutex();
	u32 data=*addr;
	unlock_mutex();
	return data;
	
}
s8 gpio_configure(u8 dir,u8 pld,u8 ev)
{
	
}

void _init(void)
{
	
	
	
}


