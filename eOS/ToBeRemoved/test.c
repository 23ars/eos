/*
 * test.c
 *
 *  Created on: Jan 1, 2017
 *      Author: mihai
 */
#include "stdtypes.h"
#include "configuration.h"
#include "kernel.h"
u8 taskOneId;
u8 taskTwoId;
void TaskOne() {
//	while(1){
//		__asm volatile("NOP");
//	}
		int i = 0;
	int a=0;
	for (i = 0; i < 10; i++) {
		__asm volatile("NOP");
		__asm volatile("NOP");
		a+=i;
		__asm volatile("NOP");
		__asm volatile("NOP");
	}
}

void TaskTwo() {
//	while(1){
//			__asm volatile("NOP");
//		}
	int i = 0;
	for (i = 0; i < 10; i++) {
		__asm volatile("NOP");
		__asm volatile("NOP");
		__asm volatile("NOP");
	}

}

void initApp()
{
	taskOneId=kernel_CreateProcess(&TaskOne, 0, TASK_HIGH_PRIO, CYCLIC_5MS);

	taskTwoId=kernel_CreateProcess(&TaskTwo, 0, TASK_HIGH_PRIO, CYCLIC_10MS);
}
