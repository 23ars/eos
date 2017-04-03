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
_public volatile u8 u8_schd_counter;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */
_public void sched_Init(void);
#endif 
