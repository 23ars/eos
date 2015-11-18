/*
 * errorcode.h
 *
 * Created: 8/22/2015 4:51:09 PM
 *  Author: Mihai
 */ 


#ifndef ERRORCODE_H_
#define ERRORCODE_H_

/** \defgroup errorcodes
 * Error codes that will be used by the os
 * @{
 */
#define SUCCESS 0x00 /**< Code for Success execution */
#define ETSOF 0x01 /**< Tasks Stack Overflow */
#define ETSE  0x03 /**< Tasks Stack Empty */
#define EOOM 0x04 /**< Out of memory error code */
#define EAPL 0x05 /**< Application already loaded to list */
#define NTID 0x06 /**< Not a task ID */
#define TSNA 0x07 /**< Reserved task state */

/** @} //end of errorcodes
*/

#endif /* ERRORCODE_H_ */
