/*
 * configuration.h
 *
 *  Created on: Dec 10, 2016
 *      Author: mihai
 */

#ifndef INCLUDE_EOS_CONFIGURATION_H_
#define INCLUDE_EOS_CONFIGURATION_H_

#ifndef SYSTICK_FREQUENCY_HZ
#define SYSTICK_FREQUENCY_HZ 1000
#endif

#ifndef AVAILABLE_PROCESS_NUMBER
#define AVAILABLE_PROCESS_NUMBER 10
#endif

#ifndef USE_MEMORY_PROTECTION
//#define USE_MPU
#endif

#ifndef PROCESS_STACK_SIZE
#define PROCESS_STACK_SIZE 128
#endif

#endif /* INCLUDE_EOS_CONFIGURATION_H_ */
