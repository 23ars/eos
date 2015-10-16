/*
 * gpio.h
 *
 * Created: 8/27/2015 11:06:26 PM
 *  Author: Mihai
 */ 


#ifndef GPIO_H_
#define GPIO_H_




_PUBLIC void _init(void);

_PUBLIC void gpio_set_pud();
_PUBLIC void gpio_set_direction();
_PUBLIC void gpio_set_event();
_PUBLIC void gpio_write(volatile P_UBYTE addr,UDWORD data);
_PUBLIC UDWORD gpio_read(volatile P_UBYTE addr,UBYTE no_of_blocks);





#endif /* GPIO_H_ */