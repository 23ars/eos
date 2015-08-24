/*
 * mutex.h
 *
 * Created: 8/24/2015 10:47:51 PM
 *  Author: Mihai
 */ 


#ifndef MUTEX_H_
#define MUTEX_H_

/** \defgroup Mutex
 * Function for control mutex
 * @{
 */
#include "../stdtypes.h"

/** 
 * Variable used to control the mutex state -> locked or unlocked
 */
_PRIVATE BOOL lock_var=FALSE;

/** 
 * lock_mutex() locks the mutex
 * \param[in] none
 */
#define lock_mutex()			\
	inline void lock()			\
	{							\
		ENABLE_PROTECTION();	\
		lock_var=TRUE;			\
		DISABLE_PROTECTION();	\
	}							

/** 
 * lock_mutex() unlocks the mutex
 * \param[in] none
 */
#define unlock_mutex()			\
	inline void unlock()		\
	{							\
		ENABLE_PROTECTION();	\
		lock_var=FALSE;			\
		DISABLE_PROTECTION();	\
	}

#endif /* MUTEX_H_ */