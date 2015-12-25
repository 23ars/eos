#ifndef UTILS_H_
#define UTILS_H_
#include <stddef.h>
/* \defgroup utils
 * Needed functions offered by eOS
 * @{
 */
/*lint -save -e49 -e601 -e10 size_t is define in stddef.h */
/* memory_copy (similar to memcpy)
 * \param[in] dest destination
 * \param[in] src source
 * \param[in] n number of bytes to copy
 * \return dest
 */
_public void* memory_copy(void *dest, const void *src, size_t n);

/* memory_move (similar to memmove)
 * \param[in] dest destination
 * \param[in] src source
 * \param[in] n number of bytes to copy
 * \return dest
 */
_public void* memory_move(void *dest, const void *src, size_t n);

/* memory_move (similar to memset)
 * \param[in] s memory that'll be filled
 * \param[in] c value
 * \param[in] n number of bytes to fill
 * \return s
 */
_public void* memory_set(void *s,const int c,size_t n);

/* crc32
 * \param[in] message message on which the checksum will be calculated
 * \return checksum
 */
_public u32 crc32(ptr_u8 message);

/* crc8
 * \param[in] data_in message on which the checksum will be calculated
 * \param[in] length message length
 * \return checksum
 */
_public u8 crc8 ( ptr_u8 data_in, u16 length );

/* crc16
 * \param[in] data_in message on which the checksum will be calculated
 * \param[in] length message length
 * \return checksum
 */
_public u8 crc16(ptr_u8 data_p, u16 length);

/* @} //end of task_stack
 */
/*lint-restore*/
#endif /* UTILS_H_ */
	