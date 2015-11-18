#include "stdtypes.h"
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

void _init(void)
{
	
	
	
}


