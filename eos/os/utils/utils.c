/*
 * utils.c
 *
 * Created: 8/22/2015 1:49:39 PM
 *  Author: Mihai
 */ 
#include "../stdtypes.h"
#include <stddef.h>
#include "utils.h"

_PUBLIC void* memcopy(void *dest, const void *src, size_t n)
{
	P_UBYTE s = (P_UBYTE)src;
	P_UBYTE d = dest;
	while (n--) *d++ = *s++;
	return dest;
}

_PUBLIC void* memmove(void *dest, const void *src, size_t n)
{
	P_UBYTE d=dest;
	P_UBYTE s=(P_UBYTE)src;
	if(s<dest)
	{
		for(d+=n;s+=n;n--)
			*--d=*--s;
	}
	else
	{
		while(n--)
			*d++=*s++;
	}
	return dest;
}

_PUBLIC void* memory_set(void *s,int c,size_t n)
{
	P_UBYTE p=s;
	while(n--)
	{
		*p++=(UBYTE)c;
	}
	return s;
}

#define CRC8INIT  0x00
#define CRC8POLY  0x18              //0X18 = X^8+X^5+X^4+X^0

_PUBLIC UBYTE crc8 ( P_UBYTE data_in, UWORD number_of_bytes_to_read )
{
	UBYTE  crc;
	UWORD loop_count;
	UBYTE  bit_counter;
	UBYTE  data;
	UBYTE  feedback_bit;
	
	crc = 0x00;

	for (loop_count = 0; loop_count != number_of_bytes_to_read; loop_count++)
	{
		data = data_in[loop_count];
		
		bit_counter = 8;
		do {
			feedback_bit = (crc ^ data) & 0x01;
			
			if ( feedback_bit == 0x01 ) {
				crc = crc ^ 0x18;
			}
			crc = (crc >> 1) & 0x7F;
			if ( feedback_bit == 0x01 ) {
				crc = crc | 0x80;
			}
			
			data = data >> 1;
			bit_counter--;
			
		} while (bit_counter > 0);
	}
	
	return crc;
}


UBYTE crc16(P_UBYTE data_p, UWORD length)
{
	UBYTE i;
	UWORD data;
	UWORD crc = 0xffff;

	if (length == 0)
		return (~crc);

	do
	{
		for (i=0, data=(unsigned int)0xff & *data_p++;
		i < 8;
		i++, data >>= 1)
		{
			if ((crc & 0x0001) ^ (data & 0x0001))
			crc = (crc >> 1) ^ 0x8408;
			else  crc >>= 1;
		}
	} while (--length);

	crc = ~crc;
	data = crc;
	crc = (crc << 8) | (data >> 8 & 0xff);

	return (crc);
}


_PUBLIC UDWORD crc32(P_UBYTE message)
{
	int j;
	UDWORD byte, crc, mask, word;
	static unsigned int table[256];

	/* Set up the table, if necessary. */

	if (table[1] == 0) 
	{
		for (byte = 0; byte <= 255; byte++) 
		{
			crc = byte;
			for (j = 7; j >= 0; j--) 
			{    // Do eight times.
				mask = -(crc & 1);
				crc = (crc >> 1) ^ (0xEDB88320 & mask);
			}
			table[byte] = crc;
		}
	}

	/* Through with table setup, now calculate the CRC. */

	crc = 0xFFFFFFFF;
	while (((word = *(unsigned int *)message) & 0xFF) != 0) 
	{
		crc = crc ^ word;
		crc = (crc >> 8) ^ table[crc & 0xFF];
		crc = (crc >> 8) ^ table[crc & 0xFF];
		crc = (crc >> 8) ^ table[crc & 0xFF];
		crc = (crc >> 8) ^ table[crc & 0xFF];
		message = message + 4;
	}
	return ~crc;
}

