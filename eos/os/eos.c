/*
 * eos.c
 *
 * Created: 8/20/2015 11:15:08 PM
 *  Author: Mihai
 */ 


#include <avr/io.h>
#include "errorcode.h"
#include "stdtypes.h"

#include "../arch/architecture.h"
#include "../app/test_item.h"


void init_os(void)
{
	sched_init();

}

void run_apps(void)
{
	init_port();

}

int main(void)
{
	init_os();
	run_apps();
    while(1)
    {
		//PORTB^=(1<<PINB1);
       // NO_OPERATION();//just do nops to avoid compiler optimizations on empty loops
    }
}
