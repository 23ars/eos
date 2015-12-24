#ifndef EOS_CONF_H_
#define EOS_CONF_H_
#define F_CPU 16000000UL
#define MAX_TASK_NUMBER 15
#define ATMEGA
//#define PIC
//#define 80C51
//#include "test_item.h"




inline void run_apps()
{
	init_port();
	
}



#endif /* EOS_CONF_H_ */