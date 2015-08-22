/*
 * task_manager.h
 *
 * Created: 8/20/2015 11:33:17 PM
 *  Author: Mihai
 */ 


#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include "task_stack.h"
_PUBLIC UBYTE task_push(S_Tasks_Struct ls_task);

_PUBLIC UBYTE task_pop();



#endif /* TASK_MANAGER_H_ */