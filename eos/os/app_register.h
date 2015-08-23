/*
 * app_queue.h
 *
 * Created: 8/23/2015 11:09:42 AM
 *  Author: Mihai
 */ 


#ifndef APP_REGISTER_H_
#define APP_REGISTER_H_




/** \defgroup app_register
 * Module implemented to allow add of application code without modifying eos.c main function
 * @{
*/



_PUBLIC void app_load();
_PUBLIC void app_unload();

/**
 * app_init. Inline function which is called from each application module, to register it.
 * \param[in] application entry function
 * \return UBYTE error code 
 */
#define app_init(x)				\	
	void app_load(x) __attribute__((alias(#x)));
	
		
		
/**
 * app_exit. Inline function which is called from each application module, to unregister it.
 * \param[in] application exit function
 * \return void
 */
#define app_exit(x)				\
	void app_unload(x) __attribute__((alias(#x)));


/** @} //end of app_register
 */

#endif /* APP_LIST_H_ */