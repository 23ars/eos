/*
 * app_queue.h
 *
 * Created: 8/23/2015 11:09:42 AM
 *  Author: Mihai
 */ 


#ifndef APP_LIST_H_
#define APP_LIST_H_

/** \defgroup app_list
 * Module implemented to allow add of application code without modifying eos.c main function
 * @{
*/

/**
 * Structure S_List_Node that defines the basic info that eOS need to know about an application.
 * Allows developer to add a maxim number of 256 applications
 */
struct S_List_Node
{
	UBYTE app_identifier; /**< Application identifier, should be an unique number between 0 and 255 */
	void (*app_node)(void);	/**< Application initialization function. */
	struct S_List_Node *next; /**< Next node in applications list */
};

/**
 * Applications list root node 
 */
struct S_List_Node *app_list_root=NULL;



_PRIVATE UBYTE app_list_push(UBYTE app_identifier,void (*app_node)(void));
_PRIVATE void app_list_pop(UBYTE app_identifier);
_PRIVATE struct S_List_Node *app_list_search(UBYTE app_identifier);

/**
 * app_list_execute. This function is called from eos.c main function and executes sequentially all the apps that 
 * were registered
 * \param[in] void
 * \return void
 */
_PUBLIC void app_list_execute();

/**
 * app_register. Inline function which is called from each application module, to register it.
 * \param[in] app_identifier UBYTE unique ID for each application module
 * \param[in] (*app_node)(void) pointer to init function of application module
 * \return UBYTE error code 
 */
_PUBLIC inline UBYTE app_register(UBYTE app_identifier,void (*app_node)(void));

/**
 * app_unregister. Inline function which is called from each application module, to unregister it.
 * \param[in] app_identifier UBYTE unique ID for each application module
 * \return void
 */
_PUBLIC inline void app_unregister(UBYTE app_identifier);

/** @} //end of app_list
 */

#endif /* APP_LIST_H_ */