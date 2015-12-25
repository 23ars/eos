#ifndef MUTEX_H_
#define MUTEX_H_

/** \defgroup Mutex
 * Macros for defining and controlling shared resources
 * @{
 */
#include "stdtypes.h"
#include "task_stack.h"
#include "eos_utils.h"

/** 
 * Variable used to control the mutex state -> locked or unlocked
 */
typedef struct  
{
	BOOL lock_var;
	/*resource is BYTE because if there is no owner thread, -1 will be*/
	s8 owner_thread; 
	/*max task number -1 because 1 thread is already locking the resource*/
	u8 locked_threads_stack[MAX_TASK_NUMBER];
	s8 locked_threads_stack_top;
}S_Mutex_Struct;

_private S_Mutex_Struct rs_mutex_configuration;
s8 lub_mutex_index;
_private inline void mutex_stack_push(u8 thread)
{
	if (rs_mutex_configuration.locked_threads_stack_top != (MAX_TASK_NUMBER - 1))
	{
		rs_mutex_configuration.locked_threads_stack[++rs_mutex_configuration.locked_threads_stack_top] = thread;
	}
}

_private inline s8 mutex_stack_pop()
{
	s8 thread_id=-1;
	if (-1!=rs_mutex_configuration.locked_threads_stack_top)
	{
		thread_id = rs_mutex_configuration.locked_threads_stack[rs_mutex_configuration.locked_threads_stack_top--];
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
			memory_set(&rs_mutex_configuration,0,sizeof(S_Mutex_Struct));					\
			rs_mutex_configuration.lock_var=FALSE;											\
			rs_mutex_configuration.owner_thread=-1;											\
			rs_mutex_configuration.locked_threads_stack_top=-1;								\
	}

/************************************************************************/
/* lock_mutex() locks the mutex											*/
/* \param[in] UBYTE lub_mutex_index										*/
/************************************************************************/
#define lock_mutex()																\
	inline void lock()																\
	{																				\
		enable_protection();														\
		if(rs_mutex_configuration.lock_var==TRUE)									\
		{																			\
			mutex_stack_push(rub_thread_id);										\
		}																			\
		else																		\
		{																			\
			rs_mutex_configuration.lock_var=TRUE;									\
			rs_mutex_configuration.owner_thread=rub_thread_id;						\
			s8 thread_id=mutex_stack_pop();											\
			(thread_id==-1)?TRUE:(*(rs_task_stack[thread_id].task))();					\
		}																			\
		disable_protection();														\
	}							

/************************************************************************/
/* lock_mutex() unlocks the mutex										*/
/* \param[in] none														*/						
/************************************************************************/
#define unlock_mutex()													\
	inline void unlock()												\
	{																	\
		enable_protection();											\
		rs_mutex_configuration.lock_var=FALSE;							\
		s8 thread_id=mutex_stack_pop();									\
		(thread_id==-1)?TRUE:(*(rs_task_stack[thread_id].task))();			\
		disable_protection();											\
	}

#endif /* MUTEX_H_ */