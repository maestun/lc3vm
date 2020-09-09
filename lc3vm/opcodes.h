//
//  opcodes.h
//  lc3vm
//

#ifndef opcodes_h
#define opcodes_h

#include "config.h"

/* op codes */
enum {
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP,   /* execute trap */
    OP_COUNT
};


typedef uint16_t (*opPtr)(uint16_t, int);
typedef char * (*opDisasm)(uint16_t);

typedef struct {
    uint8_t code;
    opPtr   optr;
    char    desc[kDescMaxLen];
} sOpcode;

typedef struct {
    uint8_t code;
    opPtr   optr;
    char    name[kNameMaxLen];
    char    fmt[kDescMaxLen];
} sOpcodeDesc;


int     op_exec(uint16_t instr);
char *  op_disasm(uint16_t addr, uint16_t instr);
#endif /* opcodes_h */
