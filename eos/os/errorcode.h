/*
 * errorcode.h
 *
 * Created: 8/22/2015 4:51:09 PM
 *  Author: Mihai
 */ 


#ifndef ERRORCODE_H_
#define ERRORCODE_H_

/// \defgroup errorcodes
/// Error codes that will be used by the os
/// @{
#define SUCCESS 0x00 ///< Code for Success execution
#define TSOF 0x01 ///< Tasks Stack Overflow
#define TSE  0x03 ///< Tasks Stack Empty
#define TNA 0x04 ///< Task not accepted. Only one accepted 1ms task
/// @} //end of errorcodes

#endif /* ERRORCODE_H_ */