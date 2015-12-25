#ifndef EOS_CONF_H_
#define EOS_CONF_H_
#define F_CPU 16000000UL
#define MAX_TASK_NUMBER 15
#define ATMEGA
/*
#define PIC
#define 80C51
#include "test_item.h"
*/

/*lint -save -e960 -e957 -e129 Inline function defined in config header */
inline void run_apps(void)
{
	init_port();
	
}
/*lint-restore*/



#endif /* EOS_CONF_H_ */
