//
//  traps.h
//  lc3vm-orig
//

#ifndef traps_h
#define traps_h

#include "config.h"

/* trap codes */
enum {
  TRAP_GETC = 0x20,  /* get character from keyboard */
  TRAP_OUT = 0x21,   /* output a character */
  TRAP_PUTS = 0x22,  /* output a word string */
  TRAP_IN = 0x23,    /* input a string */
  TRAP_PUTSP = 0x24, /* output a byte string */
  TRAP_HALT = 0x25   /* halt the program */
};

uint16_t trap_exec(uint16_t tvec);

#endif /* traps_h */
