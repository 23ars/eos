/*
 * task_manager.h
 *
 * Created: 8/20/2015 11:33:17 PM
 *  Author: Mihai
 */ 


#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_
/** \defgroup taskmanager
 * Allow basic operations on the stack used for task
 * @{
 */
#include "task_stack.h"
/** push
 * \param[in] S_Tasks_Struct
 * \return ETSOF or task_id ( position in stack)
 */
_PUBLIC BYTE task_push(S_Tasks_Struct ls_task);

/** push
 * \param[in] void
 * \return errorcodes
 */
_PUBLIC UBYTE task_pop(void);

/** @} //end of taskmanager
 */

#endif /* TASK_MANAGER_H_ */