/*
 * bin_semaphore.h
 *
 * Created: 8/26/2015 9:45:26 PM
 *  Author: Mihai
 */ 


#ifndef BIN_SEMAPHORE_H_
#define BIN_SEMAPHORE_H_
/** \defgroup binary_semaphores
 * Macros for defining and controlling shared resources
 * @{
 */
#include "../include/stdtypes.h"

/** 
 * Variable used to control the semaphore state -> locked or unlocked
 */
_PRIVATE BOOL lock_var=FALSE;

/** 
 * lock_semaphore() locks the semaphore
 * \param[in] none
 */
#define lock_semaphore()					\
	ENABLE_PROTECTION();					\
	((lock_var==TRUE)?return:lock_var=TRUE)	\
	DISABLE_PROTECTION();					
	

/** 
 * unlock_semaphore() unlocks the semaphore
 * \param[in] none
 */
#define unlock_semaphore()			\
	ENABLE_PROTECTION();			\
	lock_var=FALSE;					\
	DISABLE_PROTECTION();		



#endif /* BIN_SEMAPHORE_H_ */