#ifndef INCLUDE_EOS_INCLUDE_ERRNO_H_
#define INCLUDE_EOS_INCLUDE_ERRNO_H_
/*
 * ######################################################
 * ##			API Include      					   ##
 * ######################################################
 * */
#include <stdtypes.h>
/*
 * ######################################################
 * ##			Type Definitions					   ##
 * ######################################################
 * */
#define EOK 0x00
#define ETSOF 0x01 /**< Tasks Stack Overflow */
#define ERSPR 0x02 /**< Process id 0. Reserved process */
#define EIDNR 0x03 /**< Process id not in range */
//#define ETSE  0x03 /**< Tasks Stack Empty */
//#define EOOM 0x04 /**< Out of memory error code */
//#define EAPL 0x05 /**< Application already loaded to list */
//#define NTID 0x06 /**< Not a task ID */
//#define TSNA 0x07 /**< Reserved task state */
/*
 * ######################################################
 * ##			Variable Definitions				   ##
 * ######################################################
 * */
volatile u8 errno;
/*
 * ######################################################
 * ##			Function Definitions				   ##
 * ######################################################
 * */

#endif /* INCLUDE_EOS_INCLUDE_ERRNO_H_ */
