//
//  disasm.h
//  lc3vm
//

#ifndef disasm_h
#define disasm_h

#include "config.h"
#include "vm.h"

typedef enum {
    EOpKindReg = 0,
    EOpKindImm,
    EOpKindOff,
} EOpKind;

typedef struct {
    EOpKind   kind;
    uint16_t  value;
} sDisasmOp;

typedef struct {
    uint16_t    addr;
    uint16_t    data;
    sOpcode     opcode;
    sDisasmOp   operands[4];
    char        comment[kDescMaxLen];
} sDisasmSt;

typedef struct {
    uint16_t    count;
    sDisasmSt * statements;
} sDisasm;

char * disasm_script(sScript * script);

#endif /* disasm_h */
