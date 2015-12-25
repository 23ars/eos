#include "stdtypes.h"
#include "gpio.h"


void gpio_write(volatile ptr_u8 addr,const ptr_void data,u32 count)
{
	ptr_u8 lpub_d=(ptr_u8)data;
	while(count--)
	{
		*addr=lpub_d;	
		*lpub_d++;
	}
}
void gpio_read(volatile ptr_u8 addr,void*data,u32 count)
{
	
	u8 lub_d;
	while (count--)
	{
		lub_d=*addr;
		*data++;
		*((u8*)(data))=lub_d;	
	}

	
	
}


s8 gpio_set_direction(const E_Gpio_Direction direction,volatile ptr_u8 dir_reg,const u8 pin_no)
{
	if(INPUT==direction)
	{
		*dir_reg&=~(1<<pin_no);
		
	}
	else
	{
		*dir_reg|=(1<<pin_no);
	}
	
}




