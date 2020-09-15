//
//  vm.h
//  lc3vm
//

#ifndef vm_h
#define vm_h

#include "config.h"
#include "opcodes.h"
#include "sys.h"
#include "traps.h"

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

typedef struct {
    uint32_t    len;
    uint16_t    org;
    char        name[kPathMaxLen];
    uint16_t *  data;
} sScript;

#define OP_LEN
#define RAM_MAX UINT16_MAX

typedef struct {
    uint8_t     running;
    uint16_t    memory[RAM_MAX];
    uint16_t    reg[R_COUNT];
} sVM;

extern sVM vm;

void        vm_init(void);
void        vm_deinit(void);
sScript *   vm_load(const char * script_path);
void        vm_unload_script(sScript * script);
void        vm_start(sScript * script);
void        vm_step(void);

#endif /* vm_h */
