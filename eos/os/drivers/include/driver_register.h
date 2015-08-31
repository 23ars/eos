/*
 * app_queue.h
 *
 * Created: 8/23/2015 11:09:42 AM
 *  Author: Mihai
 */ 


#ifndef DRIVER_REGISTER_H_
#define DRIVER_REGISTER_H_


/** \defgroup app_register
 * Module implemented to allow add of application code without modifying eos.c main function
 * @{
*/


_PUBLIC void fct_driver_load();
_PUBLIC void fct_driver_unload();
_PRIVATE UBYTE driver_descriptor=0;

/**
 * driver_load. Inline function which is called from each application module, to load specific drivers.
 * \param[in] driver name
 * \return void
 */
#define driver_load(drv)										\
	void fct_driver_load() __attribute__((alias(load_##drv)));	\
		
		

/**
 * driver_unload. Inline function which is called from each application module, to unload specific drivers.
 * \param[in] driver name
 * \return void
 */
#define driver_unload(drv)				\
	void fct_driver_unload() __attribute__((alias(unload_##drv)));

/**
 * driver_init. Inline function which is called from each driver for registering.
 * \param[in] driver name
 * \param[in] driver entry function
 * \return void
 */
#define driver_init(drv,x)						\	
	void load_##drv(x) __attribute__((alias(#x)));		
	
	
	
		
		
/**
 * driver_exit. Inline function which is called from each driver for unregistering.
 * \param[in] driver name
 * \param[in] driver exit function
 * \return void
 */
#define driver_exit(drv,x)				\
	void unload_##drv(x) __attribute__((alias(#x)));	


/** @} //end of app_register
 */

#endif /* APP_LIST_H_ */