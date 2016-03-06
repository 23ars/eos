/*
 * process.c
 *
 * Created: 2/6/2016 11:52:17 PM
 *  Author: Mihai
 */ 
#include "stdtypes.h"
#include "eos_conf.h"
#include "process.h"

static volatile struct S_ProcessData rs_TaskStruct[MAX_TASK_NUMBER];

volatile s8 rub_task_stack_top=-1;

s8 create_process(void (*task)(void),E_TaskPriority priority)
{
	
	return -1;
}