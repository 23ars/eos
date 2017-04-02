/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "arch.h"
#include "kernel.h"
#include "scheduler.h"

/*
 * ######################################################
 * ##           Type Definitions                       ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##           Variable Definitions                   ##
 * ######################################################
 * */

volatile u32 u32_KernelStatus;
ptr_u32 stack;
/*
 * ######################################################
 * ##           Function Definitions                   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##           Function Implementations               ##
 * ######################################################
 * */

void sched_ScheduleNextTask(void) {

}

//void SystemTick_ServiceRoutine(void) {
//
//	enable_protection();
//	u8_schd_counter++;
//
//
//
//
//	disable_protection();
//	if (u32_KernelStatus & KERNEL_SCHEDULER_FLAG) {
//		enable_protection();
//		u32_KernelStatus ^= KERNEL_SCHEDULER_FLAG;
//		disable_protection();
//		arch_IssueSwInterrupt();
//	}

//}

void sched_Init(void)
{

	u8_schd_counter = 0;

}

