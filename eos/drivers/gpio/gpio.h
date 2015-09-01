/*
 * gpio.h
 *
 * Created: 8/27/2015 11:06:26 PM
 *  Author: Mihai
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#define MODULE_NAME gpio


_PRIVATE void _init(void);
_PRIVATE void _exit(void);

_PRIVATE void gpio_write(volatile P_UBYTE addr,UDWORD data);
_PRIVATE UDWORD gpio_read(volatile P_UBYTE addr,UBYTE no_of_blocks);
_PRIVATE BYTE gpio_configure(UBYTE dir,UBYTE pld,UBYTE ev);

_PRIVATE struct io_file gpio_file=
	{
		.io_read=&gpio_read,
		.io_write=&gpio_write,
		.dt=0x01,
		.special_fct.io_conf=gpio_configure
	};

_PRIVATE UBYTE gpio_file_descriptor;

#endif /* GPIO_H_ */