//
//  config.h
//  lc3vm
//

#ifndef config_h
#define config_h

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <libgen.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define kProgName           "lc3vm"
#define kProgVersion        "0.1"
#define kPathMaxLen         (256)
#define kDescMaxLen         (256)
#ifdef _WIN32
#  define kPathSeparator    "\\"
#else
#  define kPathSeparator    "/"
#endif

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;

#endif /* config_h */
