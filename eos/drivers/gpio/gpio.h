#ifndef GPIO_H_
#define GPIO_H_




_public void _init(void);

_public void gpio_set_pud();
_public void gpio_set_direction();
_public void gpio_set_event();
_public void gpio_write(volatile ptr_u8 addr,u32 data);
_public u32 gpio_read(volatile ptr_u8 addr,u8 no_of_blocks);





#endif /* GPIO_H_ */