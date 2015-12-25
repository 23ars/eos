#ifndef TASK_STATE_H_
#define TASK_STATE_H_
/* \defgroup task_state
 * Api offered to change state of a task.
 * @{
 */


/* task_change_state 
 * \param[in] task_id task_id obtained after a succesfully push
 * \param[in] task_state value from E_Task_State Enum
 * \return 0 for success and a negative number for failure.
 */
_public s8 task_change_state(s8 task_id,E_Task_State task_state);
/**  @} //end of task_state
 */


#endif /* TASK_STATE_H_ */
