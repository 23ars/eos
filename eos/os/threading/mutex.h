/*
 * mutex.h
 *
 * Created: 8/24/2015 10:47:51 PM
 *  Author: Mihai
 */ 


#ifndef MUTEX_H_
#define MUTEX_H_

/** \defgroup Mutex
 * Macros for defining and controlling shared resources
 * @{
 */
#include "../include/stdtypes.h"
#include "task_stack.h"
#include "../utils/utils.h"
#define MAX_NO_OF_MUTEX 256
/** 
 * Variable used to control the mutex state -> locked or unlocked
 */
typedef struct  
{
	BOOL lock_var;
	/*resource is BYTE because if there is no owner thread, -1 will be*/
	BYTE owner_thread; 
	/*max task number -1 because 1 thread is already locking the resource*/
	UBYTE locked_threads_stack[MAX_TASK_NUMBER];
	BYTE locked_threads_stack_top;
}S_Mutex_Struct;

_PRIVATE S_Mutex_Struct rs_mutex_configuration[MAX_NO_OF_MUTEX];
BYTE lub_mutex_index;
_PRIVATE inline void mutex_stack_push(UBYTE thread,BYTE ub_mutex_id)
{
	if (rs_mutex_configuration[ub_mutex_id].locked_threads_stack_top != (MAX_TASK_NUMBER - 1))
	{
		rs_mutex_configuration[ub_mutex_id].locked_threads_stack[++rs_mutex_configuration[ub_mutex_id].locked_threads_stack_top] = thread;
	}
}

_PRIVATE inline BYTE mutex_stack_pop(BYTE ub_mutex_id)
{
	BYTE thread_id=-1;
	if (-1!=rs_mutex_configuration[ub_mutex_id].locked_threads_stack_top)
	{
		thread_id = rs_mutex_configuration[ub_mutex_id].locked_threads_stack[rs_mutex_configuration[ub_mutex_id].locked_threads_stack_top--];
	}
	return thread_id;
}
/************************************************************************/
/* init_mutex initialize the mutex                                      */
/* \param[in] none														*/
/* \param[out] P_BYTE mutex_id											*/
/************************************************************************/
#define init_mutex()																		\	
	inline void mutex_init()																\
	{																						\
		if(lub_mutex_index!=MAX_NO_OF_MUTEX-1)												\
		{																					\
			memory_set(&rs_mutex_configuration[lub_mutex_index],0,sizeof(S_Mutex_Struct));	\
			rs_mutex_configuration[lub_mutex_index].lock_var=FALSE;							\
			rs_mutex_configuration[lub_mutex_index].owner_thread=-1;						\
			rs_mutex_configuration[lub_mutex_index].locked_threads_stack_top=-1;			\									
			lub_mutex_index++;																\
		}																					\
	}

/************************************************************************/
/* lock_mutex() locks the mutex											*/
/* \param[in] UBYTE lub_mutex_index										*/
/************************************************************************/
#define lock_mutex()																\
	inline void lock()																\
	{																				\
		ENABLE_PROTECTION();														\			
		if(rs_mutex_configuration[lub_mutex_index].lock_var==TRUE)					\
		{																			\
			mutex_stack_push(rub_thread_id,lub_mutex_index);						\
		}																			\
		else																		\
		{																			\
			rs_mutex_configuration[lub_mutex_index].lock_var=TRUE;					\
			rs_mutex_configuration[lub_mutex_index].owner_thread=rub_thread_id;		\
			BYTE thread_id=mutex_stack_pop(lub_mutex_index);						\
			(thread_id==-1)?:(*(rs_task_stack[thread_id].task))();					\
		}																			\		
		DISABLE_PROTECTION();														\
	}							

/************************************************************************/
/* lock_mutex() unlocks the mutex										*/
/* \param[in] none														*/						
/************************************************************************/
#define unlock_mutex()													\
	inline void unlock()												\
	{																	\
		ENABLE_PROTECTION();											\
		rs_mutex_configuration[lub_mutex_index].lock_var=FALSE;			\
		BYTE thread_id=mutex_stack_pop(lub_mutex_index);				\
		(thread_id==-1)?:(*(rs_task_stack[thread_id].task))();			\
		DISABLE_PROTECTION();											\
	}

#endif /* MUTEX_H_ */