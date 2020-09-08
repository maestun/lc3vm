//
//  vm.h
//  lc3vm-orig
//

#ifndef vm_h
#define vm_h

#include "config.h"
#include "traps.h"
#include "opcodes.h"

/* 65536 locations */
extern uint16_t memory[UINT16_MAX];

enum {
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC, /* program counter */
  R_COND,
  R_COUNT
};

extern uint16_t reg[R_COUNT];


/* condition flags */
enum {
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};


/* memory mapped registers */
enum {
  MR_KBSR = 0xFE00, /* keyboard status */
  MR_KBDR = 0xFE02  /* keyboard data */
};

int read_and_execute_instruction(void);
int read_image(const char * image_path);

#endif /* vm_h */
