/*
 * io_driver.c
 *
 * Created: 8/31/2015 9:46:14 PM
 *  Author: Mihai
 */ 
#include "stdtypes.h"

#include "eos_utils.h"
#include "io_driver.h"


_PUBLIC int ops_add(struct io_file s_desc)
{
	static int ops_desc_index=-1;
	ENABLE_PROTECTION();
	if(ops_desc_index==MAX_OPS_NO-1)
	{
		UBYTE index=0;
		for(index=0;index<MAX_OPS_NO;index)
		{
			if(ops[index].ub_is_location_used==0x00)
			{
				ops_desc_index=index;
				goto add_operation;
			}
			
		}
		DISABLE_PROTECTION();
		return -1;
	}
	ops_desc_index++;
	add_operation:
	{
		ops[ops_desc_index].ub_is_location_used=0x01;
		memory_copy(&ops[ops_desc_index].op,&s_desc,sizeof(struct io_file));
		DISABLE_PROTECTION();
		return ops_desc_index;
	}
}
_PUBLIC void ops_rem(int desc)
{
	if(desc!=-1)
	{
		memory_set(&ops[desc],0,sizeof(struct io_file));
	}
	
}