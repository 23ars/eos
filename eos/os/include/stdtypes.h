/*
 * stdtypes.h
 *
 * Created: 8/9/2015 11:24:12 AM
 *  Author: Mihai
 */ 
/**
\mainpage  eOS, an embedded Operating System
* <p></p>
* <p>Author: Mihai Seba <<b>23ars</b>></p>
* <p>Version: 1.0</p>
* <p>License: GPL</p>
* @see 
*/

#ifndef STDTYPES_H_
#define STDTYPES_H_
#include "compiler.h"


/** \defgroup CommonMacros Library Macros
 * These Macros allow you to implement basic logical operations and also to "encapsulate" functions and variables.
 * @{
 */

/** Defines macro that should be called before doing operations on shared variables
 */
/*lint -save -e961 Know it's function-like */
#define ENABLE_PROTECTION() DISABLE_INTERRUPTS


/**  Defines macro that should be called after doing operations on shared variables
 */

#define DISABLE_PROTECTION() ENABLE_INTERRUPTS
/*lint -restore*/

/** Defines the "_PRIVATE" type that can be added to a function or a global variable
 */
#ifndef _PRIVATE
#define _PRIVATE static
#endif

/** Defines the "_PUBLIC" type that can be added to a function or a global variable
 */
#ifndef _PUBLIC
#define _PUBLIC extern
#endif

/** Defines the "_FAR_FUNC" type of a function. Not available for AVR
 */
#ifndef _FAR_FUNC
#define _FAR_FUNC
#endif

/** Defines the "_NEAR_FUNC" type of a function. Not available for AVR
 */
#ifndef _NEAR_FUNC
#define _NEAR_FUNC
#endif

/*lint -save -e694 General constants for min and max value. */
/** Defines the max value for an unsigned char
 */
#ifndef MAX_UBYTE
#define MAX_UBYTE	255
#endif

/** Defines the max value for an unsigned int
 */
#ifndef MAX_UWORD
#define MAX_UWORD	65535
#endif

/** Defines the max value for an unsigned long int
 */
#ifndef MAX_UDWORD
#define MAX_UDWORD	4294967295
#endif

/** Defines the min value for a signed char
 */
#ifndef MIN_BYTE
#define MIN_BYTE	-128
#endif

/** Defines the max value for a signed char
 */
#ifndef MAX_BYTE
#define MAX_BYTE	127
#endif

/** Defines the min value for a signed int
 */
#ifndef MIN_WORD
#define MIN_WORD	-32768
#endif

/** Defines the max value for a signed int
 */
#ifndef MAX_WORD
#define MAX_WORD	32767
#endif

/** Defines the min value for a signed long int
 */
#ifndef MIN_DWORD
#define MIN_DWORD	-2147483648
#endif

/** Defines the max value for a signed long int
 */
#ifndef MAX_DWORD
#define MAX_DWORD	2147483647
#endif
/*lint -restore*/

/*lint -save -e961 Know it's function-like */
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
/*lint -restore*/
/**  @} //end of CommonMacros
 */

/**  \defgroup datatypes
 * Datatypes defined for code portability
 * @{
 */

/** Defines signed BYTE type
 */
typedef signed char BYTE;  /**< 8 bits signed type */

/** Defines signed WORD type
 */
typedef signed int WORD;  /**< 16 bits signed type */

/** Defines signed DWORD type
 */
typedef signed long int DWORD;  /**< 32 bits signed type */

/** Defines signed QWORD type
 */
typedef signed long long int QWORD;  /**< 64 bits signed type */

/** Defines unsigned BYTE type
 */
typedef unsigned char UBYTE;  /**< 8 bits unsigned type */

/** Defines unsigned WORD type
 */
typedef unsigned int UWORD; /**< bits unsigned type */

/** Defines unsigned DWORD type
 */
typedef unsigned long int UDWORD; /**< 32 bits unsigned type */

/** Defines unsigned QWORD type
 */
typedef unsigned long long int UQWORD; /**< 64 bits unsigned type */

/** Defines the BOOL type. By convention, FALSE means 0 and TRUE means 1.
 */
typedef enum
{
	FALSE=0,
	TRUE
	
}BOOL;

/** Defines signed BYTE pointer type
 */
typedef signed char* P_BYTE;

/** Defines signed WORD pointer type
 */
typedef signed int* P_WORD;

/** Defines signed DWORD pointer type
 */
typedef signed long int* P_DWORD;

/** Defines signed QWORD pointer type
 */
typedef signed long long int* P_QWORD;

/** Defines unsigned BYTE pointer type
 */
typedef unsigned char* P_UBYTE;

/** Defines unsigned WORD pointer type
 */
typedef unsigned int* P_UWORD;

/** Defines unsigned DWORD pointer type
 */
typedef unsigned long int* P_UDWORD;

/** Defines unsigned QWORD pointer type
 */
typedef unsigned long long int* P_UQWORD;

/** Pointer to const data 
 */
#define PTR_CTDATA(ptrtype) const prttype*

/**Const pointer to variable data 
*/
#define CTPTR(ptrtype) ptrtype *const

/**Const pointer to const data 
*/
#define CTPTR_CTDATA(ptrtype) const ptrtype * const


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
	
}BYTE_BITFIELD;

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
}WORD_BITFIELD;


/** Defines address format in LSB order
 */
/*lint -save -e960 Needed union for address variables */
typedef union
{
	UWORD address; /**< 16 bits address */
	struct
	{
		UBYTE addr_L; /**< address low nibble */
		UBYTE addr_H; /**< address high nibble */
	}Bytes;
	
}ADDRESS;
/*lint -restore*/


#endif /* STDTYPES_H_ */
