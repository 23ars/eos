/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include "stdtypes.h"
#include "configuration.h"
#include "process.h"
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
static volatile struct S_ProcessData rs_TaskStruct[AVAILABLE_PROCESS_NUMBER];
volatile s8 rub_task_stack_top=-1;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */

/*
 * ######################################################
 * ##			Function Implementations			   ##
 * ######################################################
 * */
s8 create_process(void (*task)(void),void (*error_hook)(void),E_ProcessType processType,E_TaskPriority priority)
{

    return -1;
}






