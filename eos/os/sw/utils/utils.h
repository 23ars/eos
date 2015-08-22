/*
 * utils.h
 *
 * Created: 8/22/2015 1:49:47 PM
 *  Author: Mihai
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#include <stddef.h>
_PUBLIC void* memory_copy(void *dest, const void *src, size_t n);
_PUBLIC void* memory_move(void *dest, const void *src, size_t n);
_PUBLIC void* memory_set(void *s,int c,size_t n);
_PUBLIC UDWORD crc32(P_UBYTE message);
_PUBLIC UBYTE crc8 ( P_UBYTE data_in, UWORD number_of_bytes_to_read );
_PUBLIC UBYTE crc16(P_UBYTE data_p, UWORD length);
#endif /* UTILS_H_ */