#ifndef GPIO_H_
#define GPIO_H_

/** \defgroup gpio
 * Gpio driver
 * @{
 */

/** Defines constants for input or output direction. 
 */
typedef enum
{
	INPUT=0x00, /**< input constant 0x00 */
	OUTPUT=0xFF /**< output constant 0xFF */
	
	
}E_Gpio_Direction;

/** gpio_set_direction sets the pin/pins as input or output
 * \param[in] direction the desired direction
 * \param[in] dir_reg register where the direction is set( For example DDRB for PORTB on an atmega microcontroller)
 * \param[in] pin_no pin that will be set as input/output
 */
_public s8 gpio_set_direction(const E_Gpio_Direction direction,volatile ptr_u8 dir_reg,const u8 pin_no);

/** gpio_write write data to address
 * \param[in] addr address where data will be written( For example &PORTB for PORTB on an atmega microcontroller)
 * \param[in] data data that will be written
 * \param[in] count no of bytes that will be written
 */
_public void gpio_write(volatile ptr_u8 addr,const ptr_void data,u32 count);

/** gpio_read read data from address
 * \param[in] addr address from where data will be read
 * \param[out] data buffer where read data will be stored
 * \param[in] count no of bytes that will be written
 */
_public void gpio_read(volatile ptr_u8 addr,void*data,u32 count);



/** @} //end of gpio
 */

#endif /* GPIO_H_ */