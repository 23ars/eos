/*
 * task_manager.h
 *
 * Created: 8/20/2015 11:33:17 PM
 *  Author: Mihai
 */ 


#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_


/*
use an array of pointers to function for each task, max 5 function per task=> 4 arrays (queues) of 5 elements
add functions like push task, pop task, kill task
functions from task manager will be called in main, init...
 
 
 also... all modules will be considered drivers, so they'll be independend from OS. the os will export an api 2 functions, init & exit...
 exit will be called on reset for each driver


NOTE: application specific code will run on task.
Drivers will just offer implementation for application and will NOT run independently on tasks. 
Used drivers will be registered and unregistered when application needs them. Use queue or stacks implementation for
registered drivers


Think about the mutexes/signals/semaphores/utils function like memcpy. 



*/


#endif /* TASK_MANAGER_H_ */