#ifndef INCLUDE_EOS_SCHEDULER_H_
#define INCLUDE_EOS_SCHEDULER_H_
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
#define KERNEL_SCHEDULER_FLAG 0x00000001
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
_public volatile u32 u32_KernelStatus;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void SystemTick_ServiceRoutine(void);
_public void sched_Init(void);
_public void sched_ScheduleNextTask(void);
#endif 
