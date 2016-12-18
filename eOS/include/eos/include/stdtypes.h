/**
\mainpage  eOS, an embedded Operating System
* <p></p>
* <p>Author: Mihai Seba <b>23ars</b></p>
* <p>Version: 1.0</p>
* <p>License: GPL</p>
* @see https://github.com/23ars/eos
*/
#ifndef INCLUDE_EOS_INCLUDE_STDTYPES_H_
#define INCLUDE_EOS_INCLUDE_STDTYPES_H_


#include "compiler.h"

/** \defgroup CommonMacros Library Macros
 * These Macros allow you to implement basic logical operations and also to "encapsulate" functions and variables.
 * @{
 */

/** Defines macro that should be called before doing operations on shared variables
 */

#define enable_protection() DISABLE_INTERRUPTS


/**  Defines macro that should be called after doing operations on shared variables
 */

#define disable_protection() ENABLE_INTERRUPTS


/** Defines the "_PRIVATE" type that can be added to a function or a global variable
 */
#ifndef _private
#define _private static
#endif

/** Defines the "_PUBLIC" type that can be added to a function or a global variable
 */
#ifndef _public
#define _public extern
#endif

/** Defines the "_FAR_FUNC" type of a function. Not available for AVR
 */
#ifndef _far_func
#define _far_func
#endif

/** Defines the "_NEAR_FUNC" type of a function. Not available for AVR
 */
#ifndef _near_func
#define _near_func
#endif


/** Defines the max value for an unsigned char
 */
#ifndef MAX_U8
#define MAX_U8	255
#endif

/** Defines the max value for an unsigned int
 */
#ifndef MAX_U16
#define MAX_U16	65535
#endif

/** Defines the max value for an unsigned long int
 */
#ifndef MAX_U32
#define MAX_U32	4294967295
#endif

/** Defines the min value for a signed char
 */
#ifndef MIN_S8
#define MIN_S8	-128
#endif

/** Defines the max value for a signed char
 */
#ifndef MAX_S8
#define MAX_S8	127
#endif

/** Defines the min value for a signed int
 */
#ifndef MIN_S16
#define MIN_S16	-32768
#endif

/** Defines the max value for a signed int
 */
#ifndef MAX_S16
#define MAX_S16	32767
#endif

/** Defines the min value for a signed long int
 */
#ifndef MIN_S32
#define MIN_S32	-2147483648
#endif

/** Defines the max value for a signed long int
 */
#ifndef MAX_S32
#define MAX_S32	2147483647
#endif

/** Define HWREG General register access macro.
 * \param[in] register address
  */
#ifndef HWREG
#define HWREG(x) (*((volatile unsigned int *)(x)))
#endif
/** Define BIT Set logical operation.
 * \param[in] variable/register in which the bit will be set
 * \param[in] bit to act upon
 */
#ifndef BIT_SET
#define BIT_SET(a,b) ((a) |= (1<<(b)))
#endif

/** Define BIT CLEAR logical operation.
 * \param[in] variable/register in which the bit will be cleared
 * \param[in] bit to act upon
 */
#ifndef BIT_CLEAR
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#endif

/** Define BIT TOGGLE logical operation.
 * \param[in] variable/register in which the bit will be toggled
 * \param[in] bit to act upon
 */
#ifndef BIT_TOGGLE
#define BIT_TOGGLE(a,b) ((a) ^= (1<<(b)))
#endif

/** Define BIT CHECK logical operation.
 * \param[in] variable/register in which the bit will be checked
 * \param[in] bit to act upon
 */
#ifndef BIT_CHECK
#define BIT_CHECK(a,b) ((a) & (1<<(b)))
#endif


/** Define BITMASK SET logical operation.
 * \param[in] target
 * \param[in] mask
 */
#ifndef BITMASK_SET
#define BITMASK_SET(x,y) ((x) |= (y))
#endif

/** Define BITMASK CLEAR logical operation.
 * \param[in] target
 * \param[in] mask
 */
#ifndef BITMASK_CLEAR
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#endif

/** Define BITMASK TOGGLE logical operation.
 * \param[in] target
 * \param[in] mask
 */
#ifndef BITMASK_TOGGLE
#define BITMASK_TOGGLE(x,y) ((x) ^= (y))
#endif

/** Define BITMASK CHECK logical operation.
 * \param[in] target
 * \param[in] mask
 */
#ifndef BITMASK_CHECK
#define BITMASK_CHECK(x,y) ((x) & (y))
#endif

/** Define OUT_B macro. Similar to OUT mnemonic from x86 assembly language
 * \param[in] address
 * \param[in] data
 */
#ifndef OUT_B
#define	OUT_B(addr, data)	((addr) = (data))
#endif

/** Define IN_B macro. Similar to IN mnemonic from x86 assembly language
 * \param[in] address
 */
#ifndef IN_B
#define	IN_B(addr)			(addr)
#endif

/**  @} //end of CommonMacros
 */

/**  \defgroup datatypes
 * Datatypes defined for code portability
 * @{
 */

/** Defines signed BYTE type
 */
typedef signed char s8;  /**< 8 bits signed type */

/** Defines signed WORD type
 */
typedef signed int s16;  /**< 16 bits signed type */

/** Defines signed DWORD type
 */
typedef signed long int s32;  /**< 32 bits signed type */

/** Defines signed QWORD type
 */
typedef signed long long int s64;  /**< 64 bits signed type */

/** Defines unsigned BYTE type
 */
typedef unsigned char u8;  /**< 8 bits unsigned type */

/** Defines unsigned WORD type
 */
typedef unsigned int u16; /**< bits unsigned type */

/** Defines unsigned DWORD type
 */
typedef unsigned long int u32; /**< 32 bits unsigned type */

/** Defines unsigned QWORD type
 */
typedef unsigned long long int u64; /**< 64 bits unsigned type */

/** Defines unsigned memaddr type
 */
typedef u32 memaddr; /**< 32 bits unsigned type */

/** Defines the BOOL type. By convention, FALSE means 0 and TRUE means 1.
 */
typedef unsigned char boolean;
#define FALSE 0x00
#define TRUE 0x01



/** Defines void pointer type
 */
typedef void* ptr_void;

/** Defines signed BYTE pointer type
 */
typedef signed char* ptr_s8;

/** Defines signed WORD pointer type
 */
typedef signed int* ptr_s16;

/** Defines signed DWORD pointer type
 */
typedef signed long int* ptr_s32;

/** Defines signed QWORD pointer type
 */
typedef signed long long int* ptr_s64;

/** Defines unsigned BYTE pointer type
 */
typedef unsigned char* ptr_u8;

/** Defines unsigned WORD pointer type
 */
typedef unsigned int* ptr_u16;

/** Defines unsigned DWORD pointer type
 */
typedef unsigned long int* ptr_u32;

/** Defines unsigned QWORD pointer type
 */
typedef unsigned long long int* ptr_u64;


/** @} //end of datatypes
 */


/** Defines BYTE bitfield in LSB order
 */
typedef struct
{
	unsigned int bit0:1; /**< bit0 */
	unsigned int bit1:1; /**< bit1 */
	unsigned int bit2:1; /**< bit2 */
	unsigned int bit3:1; /**< bit3 */
	unsigned int bit4:1; /**< bit4 */
	unsigned int bit5:1; /**< bit5 */
	unsigned int bit6:1; /**< bit6 */
	unsigned int bit7:1; /**< bit7 */

}s8_bitfield;

/** Defines WORD bitfield in LSB order
 */
typedef struct
{
	unsigned int bit0:1; /**< bit0 */
	unsigned int bit1:1; /**< bit1 */
	unsigned int bit2:1; /**< bit2 */
	unsigned int bit3:1; /**< bit3 */
	unsigned int bit4:1; /**< bit4 */
	unsigned int bit5:1; /**< bit5 */
	unsigned int bit6:1; /**< bit6 */
	unsigned int bit7:1; /**< bit7 */
	unsigned int bit8:1; /**< bit8 */
	unsigned int bit9:1; /**< bit9 */
	unsigned int bit10:1; /**< bit10 */
	unsigned int bit11:1; /**< bit11 */
	unsigned int bit12:1; /**< bit12 */
	unsigned int bit13:1; /**< bit13 */
	unsigned int bit14:1; /**< bit14 */
	unsigned int bit15:1; /**< bit15 */
}s16_bitfield;


/** Defines address format in LSB order
 */

typedef union
{
	u16 address; /**< 16 bits address */
	struct
	{
		u8 addr_L; /**< address low nibble */
		u8 addr_H; /**< address high nibble */
	}Bytes;

}addr;




#endif /* INCLUDE_EOS_STDTYPES_H_ */
