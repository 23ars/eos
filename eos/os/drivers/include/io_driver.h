/*
 * io_driver.h
 *
 * Created: 8/27/2015 11:12:32 PM
 *  Author: Mihai
 */ 


#ifndef IO_DRIVER_H_
#define IO_DRIVER_H_
/************************************************************************/
/* \defgroup io_driver													*/
/* Interface for development of IO drivers. IO drivers type will be     */
/* applicable to GPIO, eeprom etc                                       */
/* @{                                                                   */
/************************************************************************/

/************************************************************************/
/* Max number of descriptors for IO that can be opened in the same time */
/************************************************************************/
#define MAX_OPS_NO 8

/************************************************************************/
/* Seek Location Enum.						                            */
/************************************************************************/
typedef enum
{
	SEEK_SET=0x00,/**< offset is set to offset bytes */
	SEEK_CURRENT,/**< offset is set to current location+offset bytes*/
	SEEK_END     /**< offset is set to the size of the file +offset bytes*/	
}E_Seek_Location;
/************************************************************************/
/* Type of driver                                                       */
/************************************************************************/
typedef enum
{
	GPIO_DRIVER=0x00,/**< GPIO Driver */
	EEP_DRIVER/**<EEPROM driver */
		
}E_Driver_Type;


/************************************************************************/
/* io_file structure represent the properties of a io descriptor       */
/************************************************************************/
_PUBLIC struct io_file
{
	void (*io_write)(volatile P_UBYTE,UDWORD);/**< pointer to write function defined by driver */
	UDWORD (*io_read)(volatile P_UBYTE,UBYTE);/**< pointer to read function defined by driver */
	E_Driver_Type dt;/** <driver type*/
	union 
	{
		UWORD (*io_seek)(UWORD,E_Seek_Location);/**< pointer to seek function defined by driver */		
		BYTE (*io_conf)(UBYTE,UBYTE,UBYTE);/**< pointer to config function defined by driver */
	}special_fct;/**<driver type specific functions*/
	
};
/************************************************************************/
/* Struct that will hold info about each opened descriptor              */
/************************************************************************/
struct descriptors
{
	UBYTE ub_is_location_used;/**<BYTE variable that will be set to 0x01 if location is used, otherwise 0x00*/
	struct io_file op;/**<descriptor*/	
};

/************************************************************************/
/* Array of descriptors                                                 */
/************************************************************************/
struct descriptors ops[MAX_OPS_NO];
/************************************************************************/
/* ops_add. Function that will add a new opened descriptor to array     */
/* \param[in] struct io_file s_desc new descriptor						*/
/* \param[out] int index of descriptor in array							*/
/************************************************************************/
_PUBLIC int ops_add(struct io_file s_desc);

/************************************************************************/
/* ops_rem. Function that will remove a descriptor                      */
/* \param[in] descriptor index											*/
/* \param[out] void														*/
/************************************************************************/
_PUBLIC void ops_rem(int desc);

/************************************************************************/
/* @} //end of app_register                                             */
/************************************************************************/


#endif /* IO_DRIVER_H_ */