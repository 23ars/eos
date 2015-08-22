/*
 * utils.h
 *
 * Created: 8/22/2015 1:49:47 PM
 *  Author: Mihai
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#include <stddef.h>
/// \defgroup utils
/// Needed functions offered by eOS
/// @{


/// memory_copy (similar to memcpy)
/// \param[in] dest destination
/// \param[in] src source
/// \param[in] n number of bytes to copy
/// \return dest
_PUBLIC void* memory_copy(void *dest, const void *src, size_t n);

/// memory_move (similar to memmove)
/// \param[in] dest destination
/// \param[in] src source
/// \param[in] n number of bytes to copy
/// \return dest
_PUBLIC void* memory_move(void *dest, const void *src, size_t n);

/// memory_move (similar to memset)
/// \param[in] s memory that'll be filled
/// \param[in] c value
/// \param[in] n number of bytes to fill
/// \return s
_PUBLIC void* memory_set(void *s,int c,size_t n);

/// crc32
/// \param[in] message message on which the checksum will be calculated
/// \return checksum
_PUBLIC UDWORD crc32(P_UBYTE message);

/// crc8
/// \param[in] data_in message on which the checksum will be calculated
/// \param[in] length message length
/// \return checksum
_PUBLIC UBYTE crc8 ( P_UBYTE data_in, UWORD length );

/// crc16
/// \param[in] data_in message on which the checksum will be calculated
/// \param[in] length message length
/// \return checksum
_PUBLIC UBYTE crc16(P_UBYTE data_p, UWORD length);

/// @} //end of task_stack
#endif /* UTILS_H_ */