/*! \file mm_arch_deps.h
File is property of &copy; MikroM Gmbh, 1997-2005
\author Timo Kabsch (created 2005/03/15)

This file contains architecture dependent definition, e.g. basic integer types.
*/

// From ISO9899:1999E

// Integer Types:
//   When typedef names differing only in the absence or presence of the initial u are defined,
//   they shall denote corresponding signed and unsigned types as described in 6.2.5; an
//   implementation providing one of these corresponding types shall also provide the other.
//   2 In the following descriptions, the symbol N represents an unsigned decimal integer with
//   no leading zeros (e.g., 8 or 24, but not 04 or 048).



#ifndef _MM_TYPES_H_
#define _MM_TYPES_H_

#include "mm_defines.h"

#if defined(MM_HCARC)
//////////////////////////////////////////////////////////////////////////
// Argonaut RISC core (ARC) with Metaware hcarc compiler
//////////////////////////////////////////////////////////////////////////

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef signed short int_fast16_t;
typedef unsigned int uint_fast32_t;
typedef signed int int_fast32_t;

// Definitions for least type

typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef unsigned char uint_least16_t;
typedef signed short int_least16_t;
typedef unsigned int uint_least32_t;
typedef signed int int_least32_t;

#if !defined(MM_CPP)
#define inline
typedef uint_fast8_t bool;
#define true (1==1)
#define false (1==0)
#endif

#define _CHAR_ char

#elif defined(MM_WIN32)
//////////////////////////////////////////////////////////////////////////
// Windows i386
//////////////////////////////////////////////////////////////////////////

#ifdef __MINGW32__
#   define MM_HAS_STDINT
#endif

#if !defined(__MINGW32__)
#   ifndef ssize_t
	typedef signed int ssize_t;
#   endif
#endif

#if defined(MM_HAS_STDINT)
#   include "stdint.h"
#else

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef signed short int_fast16_t;
typedef unsigned int uint_fast32_t;
typedef signed int int_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef signed long long int_fast64_t;

typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef signed short int_least16_t;
typedef unsigned int uint_least32_t;
typedef signed int int_least32_t;
typedef unsigned long long uint_least64_t;
typedef signed long long int_least64_t;

#include "basetsd.h"

typedef INT_PTR intptr_t;
typedef UINT_PTR uintptr_t;

#endif // MM_HAS_STDINT

#if defined(MM_WIN32_KERNEL)
#define SKIP_DEF_TRUE
#define SKIP_DEF_FALSE
#endif

#if !defined(MM_WIN32_KERNEL)
#define SKIP_DEF_BOOL
#endif

#define MM_INLINE _inline

#if !defined(MM_CPP)
typedef uint_fast8_t bool;
#define true (1==1)
#define false (1==0)
#endif

#define _CHAR_ char

#elif defined(MM_ECOS)
//////////////////////////////////////////////////////////////////////////
// eCos based definitions
//////////////////////////////////////////////////////////////////////////

#include <cyg/infra/cyg_type.h>
#include <sys/types.h>

#if !(CYGINT_ISO_BSDTYPES)

typedef cyg_int8 int8_t;
typedef cyg_uint8 uint8_t;
typedef cyg_uint16 uint16_t;
typedef cyg_int16 int16_t;
typedef cyg_uint32 uint32_t;
typedef cyg_int32 int32_t;
typedef cyg_uint64 uint64_t;
typedef cyg_int64 int64_t;

#endif

// Definitions for fastest type

typedef cyg_int8 int_fast8_t;
typedef cyg_uint8 uint_fast8_t;
typedef cyg_uint16 uint_fast16_t;
typedef cyg_int16 int_fast16_t;
typedef cyg_uint32 uint_fast32_t;
typedef cyg_int32 int_fast32_t;
typedef cyg_uint64 uint_fast64_t;
typedef cyg_int64 int_fast64_t;

// Definitions for least type
typedef cyg_int8 int_least8_t;
typedef cyg_uint8 uint_least8_t;
typedef cyg_uint16 uint_least16_t;
typedef cyg_int16 int_least16_t;
typedef cyg_uint32 uint_least32_t;
typedef cyg_int32 int_least32_t;
typedef cyg_uint64 uint_least64_t;
typedef cyg_int64 int_least64_t;
#define _CHAR_ uint8_t

typedef int32_t intptr_t;
typedef uint32_t uintptr_t;

#elif defined(MM_ARM)
//////////////////////////////////////////////////////////////////////////
// ARM architecture
//////////////////////////////////////////////////////////////////////////
//
#if defined(MM_LINUX)
# define MM_HAS_STDINT
#endif

#if defined(MM_HAS_STDINT)
#   ifdef __KERNEL__
#      include <linux/types.h>
#   else
#      include <stdint.h>
#   endif
#else

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef unsigned short uint_fast16_t;
typedef signed short int_fast16_t;
typedef unsigned int uint_fast32_t;
typedef signed int int_fast32_t;
typedef unsigned long uint_fast64_t;
typedef signed long int_fast64_t;

typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef signed short int_least16_t;
typedef unsigned int uint_least32_t;
typedef signed int int_least32_t;
typedef unsigned long uint_least64_t;
typedef signed long int_least64_t;
#endif

#if !defined (MM_CPP)
#ifndef __KERNEL__
typedef uint_fast8_t bool;
#define true (1==1)
#define false (1==0)
#endif
#endif

#define _CHAR_ unsigned char

#elif defined(MM_LINUX)
//////////////////////////////////////////////////////////////////////////
// Linux i386
//////////////////////////////////////////////////////////////////////////

#   ifdef __KERNEL__
#      include <linux/types.h>
#   else
#      include <stdint.h>
#   endif

#if !defined (MM_CPP)
#   include <stdbool.h>
#endif

#define _CHAR_ char

#elif defined(MM_CYGWIN)
//////////////////////////////////////////////////////////////////////////
// Cygwin
//////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#if !defined (MM_CPP)
   typedef uint8_t bool;
   #define true 1
   #define false 0
   #define CHAR char 
#endif

//////////////////////////////////////////////////////////////////////////
// OSXtypedef <#existing_type#> <#new_name#>
//////////////////////////////////////////////////////////////////////////
#elif defined (MM_OSX)
#   include <stdint.h>
#	if !defined (MM_CPP)
		typedef uint_fast8_t bool;
#		define true (1==1)
#		define false (1==0)
#	endif
#       define CHAR char
#else

//#elif defined _YOUR_ARCH_
//////////////////////////////////////////////////////////////////////////
// add your architecture here
//////////////////////////////////////////////////////////////////////////

#endif

#if !defined(U8) && !defined(SKIP_DEF_U8)
typedef uint8_t U8;		//!< unsigned 8 bit value
#endif

#if !defined(S8)  && !defined(SKIP_DEF_S8)
typedef int8_t S8;		//!< signed 8 bit value
#endif

#if !defined(U16) && !defined(SKIP_DEF_U16)
typedef uint16_t U16;		//!< unsigned 16 bit value
#endif

#if !defined(S16) && !defined(SKIP_DEF_S16)
typedef int16_t S16;		//!< signed 16 bit value
#endif

#if !defined(U32) && !defined(SKIP_DEF_U32)
typedef uint32_t U32;		//!< unsigned 32 bit value
#endif

#if !defined(S32) && !defined(SKIP_DEF_S32)
typedef int32_t S32;		//!< signed 32 bit value
#endif

#if !defined(U64) && !defined(SKIP_DEF_U64)
typedef uint64_t U64;		//!< unsigned 64 bit value
#endif

#if !defined(S64) && !defined(SKIP_DEF_S64)
typedef int64_t S64;		//!< signed 64 bit value
#endif

#if !defined(BOOL) && !defined(SKIP_DEF_BOOL)
typedef bool BOOL;
#endif

#if !defined(FALSE) && !defined(SKIP_DEF_FALSE)
#define FALSE false
#endif

#if !defined(TRUE) && !defined(SKIP_DEF_TRUE)
#define TRUE true
#endif

#if !defined(CHAR) && !defined(SKIP_DEF_CHAR)
typedef _CHAR_ CHAR;		//!< unsigned 8 bit value
#endif

/*! This is the global return code type for all functions with a return value denoting an error or a warning. Negative values
denote errors, while positive values denote warnings. Successful operation is denoted by returning zero (<link EMmRc::MMRC_Ok>). */
typedef int32_t TMmRc;

#if !defined(inline) && defined(MM_INLINE) && defined(MM_WIN32_KERNEL)
#	define inline MM_INLINE
#endif

//////////////////////////////////////////////////////////////////////////
//! Minimum and maximum value defines
//////////////////////////////////////////////////////////////////////////
#if !defined(INT8_MIN)
#define INT8_MIN (-0x7f-1)
#endif

#if !defined(INT8_MAX)
#define INT8_MAX 0x7f
#endif

#if !defined(INT16_MIN)
#define INT16_MIN (-0x7fff-1)
#endif

#if !defined(INT16_MAX)
#define INT16_MAX 0x7fff
#endif

#if !defined(INT32_MIN)
#define INT32_MIN (-0x7fffffffL-1)
#endif

#if !defined(INT32_MAX)
#define INT32_MAX 0x7fffffffL
#endif

#if !defined(INT64_MIN)
#define INT64_MIN (-0x7fffffffffffffffLL-1)
#endif

#if !defined(INT64_MAX)
#define INT64_MAX 0x7fffffffffffffffLL
#endif

#if !defined(UINT8_MAX)
#define UINT8_MAX 0xff
#endif

#if !defined(UINT16_MAX)
#define UINT16_MAX 0xffff
#endif

#if !defined(UINT32_MAX)
#define UINT32_MAX 0xffffffffUL
#endif

#if !defined(UINT64_MAX)
#define UINT64_MAX 0xffffffffffffffffULL
#endif

// definition of the fast MIN MAX types are qual to the one that INT defined
//---------------------------------------------------------------------------------------

#if !defined(INT_FAST8_MIN)
#define INT_FAST8_MIN (-0x7f-1)
#endif

#if !defined(INT_FAST8_MAX)
#define INT_FAST8_MAX 0x7f
#endif

#if !defined(INT_FAST16_MIN)
#define INT_FAST16_MIN (-0x7fff-1)
#endif

#if !defined(INT_FAST16_MAX)
#define INT_FAST16_MAX 0x7fff
#endif

#if !defined(INT32_MIN)
#define INT_FAST32_MIN (-0x7fffffffL-1)
#endif

#if !defined(INT32_MAX)
#define INT_FAST32_MAX 0x7fffffffL
#endif

#if !defined(INT_FAST64_MIN)
#define INT_FAST64_MIN (-0x7fffffffffffffffLL-1)
#endif

#if !defined(INT_FAST64_MAX)
#define INT_FAST64_MAX 0x7fffffffffffffffLL
#endif

#if !defined(UINT_FAST8_MAX)
#define UINT_FAST8_MAX 0xff
#endif

#if !defined(UINT_FAST16_MAX)
#define UINT_FAST16_MAX 0xffff
#endif

#if !defined(UINT_FAST32_MAX)
#define UINT_FAST32_MAX 0xffffffffUL
#endif

#if !defined(UINT_FAST64_MAX)
#define UINT_FAST64_MAX 0xffffffffffffffffULL
#endif

// definition of the fast MIN MAX types are equal to the one that INT defined

#if !defined(INT_LEAST8_MIN)
#define INT_LEAST8_MIN (-0x7f-1)
#endif

#if !defined(INT_LEAST8_MAX)
#define INT_LEAST8_MAX 0x7f
#endif

#if !defined(INT_LEAST16_MIN)
#define INT_LEAST16_MIN (-0x7fff-1)
#endif

#if !defined(INT_LEAST16_MAX)
#define INT_LEAST16_MAX 0x7fff
#endif

#if !defined(INT_LEAST32_MIN)
#define INT_LEAST32_MIN (-0x7fffffffL-1)
#endif

#if !defined(INT_LEAST32_MAX)
#define INT_LEAST32_MAX 0x7fffffffL
#endif

#if !defined(INT_LEAST64_MIN)
#define INT_LEAST64_MIN (-0x7fffffffffffffffLL-1)
#endif

#if !defined(INT_LEAST64_MAX)
#define INT_LEAST64_MAX 0x7fffffffffffffffLL
#endif

#if !defined(UINT_LEAST8_MAX)
#define UINT_LEAST8_MAX 0xff
#endif

#if !defined(UINT_LEAST16_MAX)
#define UINT_LEAST16_MAX 0xffff
#endif

#if !defined(UINT_LEAST32_MAX)
#define UINT_LEAST32_MAX 0xffffffffUL
#endif

#if !defined(UINT_LEAST64_MAX)
#define UINT_LEAST64_MAX 0xffffffffffffffffULL
#endif

/*
static union
{
	char s8_incorrect  [sizeof( S8) == 1];
   char u8_incorrect  [sizeof( U8) == 1];
   char s16_incorrect [sizeof(S16) == 2];
   char u16_incorrect [sizeof(U16) == 2];
   char s32_incorrect [sizeof(U32) == 4];
   char u32_incorrect [sizeof(U32) == 4];
   char s64_incorrect [sizeof(S64) == 8];
   char u64_incorrect [sizeof(U64) == 8];
	
   char int8_t_incorrect   [sizeof(   int8_t) == 1];
   char uint8_t_incorrect  [sizeof(  uint8_t) == 1];
   char int16_t_incorrect  [sizeof(  int16_t) == 2];
   char uint16_t_incorrect [sizeof( uint16_t) == 2];
   char int32_t_incorrect  [sizeof(  int32_t) == 4];
   char uint32_t_incorrect [sizeof( uint32_t) == 4];
   char int64_t_incorrect  [sizeof(  int64_t) == 8];
   char uint64_t_incorrect [sizeof( uint64_t) == 8];

   char int_least8_t_incorrect   [sizeof(   int8_t) >= 1];
   char uint_least8_t_incorrect  [sizeof(  uint8_t) >= 1];
   char int_least16_t_incorrect  [sizeof(  int16_t) >= 2];
   char uint_least16_t_incorrect [sizeof( uint16_t) >= 2];
   char int_least32_t_incorrect  [sizeof(  int32_t) >= 4];
   char uint_least32_t_incorrect [sizeof( uint32_t) >= 4];
   char int_least64_t_incorrect  [sizeof(  int64_t) >= 8];
   char uint_least64_t_incorrect [sizeof( uint64_t) >= 8];

   char int_fast8_t_incorrect   [sizeof(   int8_t) >= 1];
   char uint_fast8_t_incorrect  [sizeof(  uint8_t) >= 1];
   char int_fast16_t_incorrect  [sizeof(  int16_t) >= 2];
   char uint_fast16_t_incorrect [sizeof( uint16_t) >= 2];
   char int_fast32_t_incorrect  [sizeof(  int32_t) >= 4];
   char uint_fast32_t_incorrect [sizeof( uint32_t) >= 4];
   char int_fast64_t_incorrect  [sizeof(  int64_t) >= 8];
   char uint_fast64_t_incorrect [sizeof( uint64_t) >= 8];
};
*/

#endif // _MM_TYPES_H_
