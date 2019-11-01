#ifndef _MM_DEFINES_H_
#define _MM_DEFINES_H_

#if defined(_ARC_LE)
#define MM_ARC
#endif

#if defined(DEBUG) || defined(_DEBUG) || (defined(DBG) && DBG == 1)
#undef MM_DEBUG
#define MM_DEBUG
#endif

#if defined(_BIG_ENDIAN)
#undef MM_BIG_ENDIAN
#define MM_BIG_ENDIAN
#endif

#if defined(WIN32) || defined(_WIN32)
#undef MM_WIN32
#define MM_WIN32
#if defined(WINDDK)
#define MM_WIN32_KERNEL
#endif
#endif

#if defined(__POWERPC__)
#undef MM_POWER_PC
#define MM_POWER_PC
#endif

#if defined(__APPLE__)
#undef MM_OSX
#define MM_OSX
#endif

#if defined(__arm__)
#undef MM_ARM
#define MM_ARM
#endif

#if defined(_ECOS_)
#undef MM_ECOS
#define MM_ECOS
#endif

#if defined(__GNUC__)
#undef MM_GNUC
#define MM_GNUC
#endif

#if defined(__linux)
#   if defined(__KERNEL__)
#      undef MM_LINUX_KERNEL
#      define MM_LINUX_KERNEL
#   endif
#undef MM_LINUX
#define MM_LINUX
#endif

#if defined(__cplusplus)
#undef MM_CPP
#define MM_CPP
#endif

#ifdef AT91SAM7S256
#undef MM_LITTLE_ENDIAN
#define MM_LITTLE_ENDIAN
#endif

#endif
