#ifndef INCLUDE_EOS_KERNEL_H_
#define INCLUDE_EOS_KERNEL_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "scheduler.h"

/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */

inline void kernel_DisableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus&=~KERNEL_SCHEDULER_FLAG;
	disable_protection();
}
inline void kernel_EnableSwInterrupt()
{
	enable_protection();
	u32_KernelStatus|=KERNEL_SCHEDULER_FLAG;
	disable_protection();
}
_public void kernel_ErrorHook(void);
#endif /*INCLUDE_EOS_KERNEL_H_*/
