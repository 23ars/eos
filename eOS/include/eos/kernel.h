#ifndef INCLUDE_EOS_KERNEL_H_
#define INCLUDE_EOS_KERNEL_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
typedef u32 systicks_t;
typedef u32 status_t;
typedef u32 memaddr_t;
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public systicks_t systicks;
_public status_t sysstatus;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void kernel_Init(void);

#endif /*INCLUDE_EOS_KERNEL_H_*/
