/*
 * scheduler.c
 *
 * Created: 2/6/2016 11:47:18 PM
 *  Author: Mihai
 */ 
#include "stdtypes.h"
#include "scheduler.h"
#include "process.h"
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
_private volatile u8 rub_schd_counter=0;
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
void Timer_Overflow_ServiceRoutine(void)
{
	
	enable_protection();
	rub_schd_counter++;

	disable_protection();
	
	
	
}


void sched_init(void)
{

//	rub_task_stack_top=-1;
	
}
