//
//  opcodes.c
//  lc3vm
//

#include "opcodes.h"
#include "vm.h"
#include "sys.h"

// forward declarations
uint16_t mem_read(uint16_t addr);
uint16_t mem_write(uint16_t addr, uint16_t regno);

// disasm string, updated at each opcode execution
static char d_str[kDescMaxLen] = {0};

// =============================================================================
// MARK: - Utilities
// =============================================================================
#define CHECK_BIT(v, b)     ((v >> b) & 1)
#define MAX_BIT(b)          ((1 << b) - 1)
#define GET_BITS(s, ub, lb) ((s >> lb) & ((1 << (ub - lb)) - 1))

void debug_instr(char * format, ...) {
//    static FILE * dbfp = NULL;
//    if(dbfp == NULL) {
//        dbfp = fopen("debug.s", "w");
//    }
//    va_list arg;
//    va_start(arg, format);
//    vfprintf(stdout, format, arg);
//    fflush(stdout);
//    va_end(arg);
}

/* convert small bit number to 16-bit, keeping sign bit intact */
uint16_t sign_extend(uint16_t x, int bit_count) {
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

/* update condition flags based on outcome of result (negative, zero, or
 * positive */
void update_flags(uint16_t r) {
    if (vm.reg[r] == 0) {
        vm.reg[R_COND] = FL_ZRO;
    }
    else if (vm.reg[r] >> 15) { /* a 1 in the left-most bit indicates negative */
        vm.reg[R_COND] = FL_NEG;
    }
    else {
        vm.reg[R_COND] = FL_POS;
    }
}

/* change endianness */
uint16_t swap16(uint16_t x) {
    return (x << 8) | (x >> 8);
}


// =============================================================================
// MARK: - Opcode implementation
// =============================================================================
/*
 ADD dr, sr1, sr2
 Adds value stored in sr1 with value stored in sr2,
 then stores the result in dr
 
 ADD dr, sr, #val
 Adds value stored in sr with immediate value #val,
 then stores the result in dr
 */
uint16_t add(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;
    /* first operand (SR1) */
    uint16_t sr1 = (instr >> 6) & 0x7;
    /* whether we are in immediate mode */
    uint16_t imm_flag = (instr >> 5) & 0x1;

    uint16_t op1 = vm.reg[sr1];
    uint16_t op2 = 0;
    if (imm_flag) {
        op2 = sign_extend(instr & 0x1f, 5);
        sprintf(d_str, "ADD R%d R%d 0x%04x", dr, sr1, op2);
    }
    else {
        uint16_t sr2 = instr & 0x7;
        op2 = vm.reg[sr2];
        sprintf(d_str, "ADD R%d R%d R%d", dr, sr1, sr2);
    }
    
    if(exec) {
        vm.reg[dr] = op1 + op2;
        update_flags(dr);
    }
    return 1;
}

/*
 AND dr, sr1, sr2
 Bitwise AND between value stored in sr1 and value stored in sr2,
 stores the result in dr
 
 AND dr, sr, #val
 Bitwise AND between value stored in sr and immediate value #val,
 stores the result in dr
*/
uint16_t and(uint16_t instr, int exec) {
    
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;
    /* first operand (SR1) */
    uint16_t sr1 = (instr >> 6) & 0x7;
    /* whether we are in immediate mode */
    uint16_t imm_flag = (instr >> 5) & 0x1;

    uint16_t op1 = vm.reg[sr1];
    uint16_t op2 = 0;

    if (imm_flag) {
        op2 = sign_extend(instr & 0x1f, 5);
        sprintf(d_str, "AND R%d R%d 0x%04x", dr, sr1, op2);
    }
    else {
        uint16_t sr2 = instr & 0x7;
        op2 = vm.reg[sr2];
        sprintf(d_str, "AND R%d R%d R%d", dr, sr1, sr2);
    }
    if(exec) {
        vm.reg[dr] = op1 & op2;
        update_flags(dr);
    }
    return 1;
}

/*
 NOT dr, sr
 Bitwise NOT of value stored in sr, stores the result in dr
 */
uint16_t not(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;
    /* source register (SR) */
    uint16_t sr = (instr >> 6) & 0x7;

    sprintf(d_str,"NOT R%d R%d", dr, sr);
    if(exec) {
        vm.reg[dr] = ~vm.reg[sr];
        update_flags(dr);
    }
    return 1;
}

/*
 BR[n|z|p] offset
 BRanch
 Branches to pc + offset if the given conditions are met
 */
uint16_t br(uint16_t instr, int exec) {
    uint16_t n_flag = (instr >> 11) & 0x1;
    uint16_t z_flag = (instr >> 10) & 0x1;
    uint16_t p_flag = (instr >> 9) & 0x1;

    /* PCoffset 9 */
    uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

    sprintf(d_str, "BR%s%s%s 0x%04x",
            n_flag ? "n" : "",
            z_flag ? "z" : "",
            p_flag ? "p" : "",
            pc_offset);
    
    /* advance program counter if one of the following is true:
    * - n_flag is set and negative condition flag is set
    * - z_flag is set and zero condition flag is set
    * - p_flag is set and positive condition flag is set */
    if ((n_flag && (vm.reg[R_COND] & FL_NEG)) ||
        (z_flag && (vm.reg[R_COND] & FL_ZRO)) ||
        (p_flag && (vm.reg[R_COND] & FL_POS))) {

        if(exec) {
            vm.reg[R_PC] += pc_offset;
        }
    }
    return 1;
}

/*
 JMP reg
 JuMP
 Jumps to the address stored in reg
 
 RET
 RETurn
 Jumps to the address stored in R_R7
 */
uint16_t jmp(uint16_t instr, int exec) {
    uint16_t base_r = (instr >> 6) & 0x7;
    sprintf(d_str, base_r == R_R7 ? "RET" : "JMP R%d", base_r);
    if(exec) {
        vm.reg[R_PC] = vm.reg[base_r];
    }
    return 1;
}

/*
 JSR offset
 Jump SubRoutine
 Jump to subroutine at pc + offset
 
 JSRR reg
 Jump SubRoutine Register
 Jump to subroutine at address stored in reg
 */
uint16_t jsr(uint16_t instr, int exec) {
    /* save PC in R7 to jump back to later */
    vm.reg[R_R7] = vm.reg[R_PC];

    /* whether we are in immediate mode */
    uint16_t imm_flag = (instr >> 11) & 0x1;
    uint16_t offset = 0;
    uint16_t pc = 0;
    
    if (imm_flag) {
        /* pc = pc + offset (11 bits) */
        offset = sign_extend(instr & 0x7ff, 11);
        pc = vm.reg[R_PC] + offset;
        sprintf(d_str, "JSR 0x%04x", offset);
    }
    else {
        /* assign contents of base register directly to program counter */
        uint16_t base_r = (instr >> 6) & 0x7;
        sprintf(d_str, "JSRR R%d", base_r);
        pc = vm.reg[base_r];
    }
    
    if(exec) {
        /* add offset to program counter */
        vm.reg[R_PC] = pc;
    }

    return 1;
}

/*
 LD reg, offset
 LoaD
 Loads the contents at pc + offset into reg
 */
uint16_t ld(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;

    /* PCoffset 9 */
    uint16_t offset = sign_extend(instr & 0x1ff, 9);
    sprintf(d_str, "LD R%d 0x%04x", dr, offset);
    
    /* add pc_offset to the current PC and load that memory location */
    if(exec) {
        vm.reg[dr] = mem_read(vm.reg[R_PC] + offset);
        update_flags(dr);
    }
    return 1;
}

/*
 LDI reg, offset
 LoaD Indirect
 Loads the contents of the address at pc + offset into reg
 */
uint16_t ldi(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;

    /* PCoffset 9 */
    uint16_t offset = sign_extend(instr & 0x1ff, 9);

    sprintf(d_str, "LDI R%d 0x%04x", dr, offset);
    
    /* add pc_offset to the current PC, look at that memory location to
    * get the final address */
    if(exec) {
        vm.reg[dr] = mem_read(mem_read(vm.reg[R_PC] + offset));
        update_flags(dr);
    }
    return 1;
}

/*
 LDR dr, sr, offset
 LoaD Register
 Loads the contents of the address at (sr + offset) into dr
 */
uint16_t ldr(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;

    /* base register (BaseR) */
    uint16_t base_r = (instr >> 6) & 0x7;

    /* offset 6 */
    uint16_t offset = sign_extend(instr & 0x3f, 6);

    sprintf(d_str, "LDR R%d R%d 0x%04x", dr, base_r, offset);
    
    if(exec) {
        vm.reg[dr] = mem_read(vm.reg[base_r] + offset);
        update_flags(dr);
    }
    return 1;
}

/*
 LEA dr, offset
 Load Effective Address
 Loads the (pc + offset) address into dr, and updates flags
 */
uint16_t lea(uint16_t instr, int exec) {
    /* destination register (DR) */
    uint16_t dr = (instr >> 9) & 0x7;

    /* PCoffset 9 */
    uint16_t offset = sign_extend(instr & 0x1ff, 9);

    sprintf(d_str, "LEA R%d 0x%04x", dr, offset);
    
    if(exec) {
        vm.reg[dr] = vm.reg[R_PC] + offset;
        update_flags(dr);
    }
    return 1;
}

/*
 ST sr, offset
 STore
 Stores the value contained into sr at address (pc + offset)
 */
uint16_t st(uint16_t instr, int exec) {
    /* source register (SR) */
    uint16_t sr = (instr >> 9) & 0x7;

    /* PCoffset 9 */
    uint16_t offset = sign_extend(instr & 0x1ff, 9);

    sprintf(d_str, "ST R%d 0x%04x", sr, offset);
    if(exec) {
        mem_write(vm.reg[R_PC] + offset, vm.reg[sr]);
    }
    return 1;
}

/*
 STI sr, offset
 STore Indirect
 Stores the value contained into sr at address stored at address (pc + offset)
 */
uint16_t sti(uint16_t instr, int exec) {
    /* source register (SR) */
    uint16_t sr = (instr >> 9) & 0x7;

    /* PCoffset 9 */
    uint16_t offset = sign_extend(instr & 0x1ff, 9);
    
    sprintf(d_str, "STI R%d 0x%04x", sr, offset);
    if(exec) {
        mem_write(mem_read(vm.reg[R_PC] + offset), vm.reg[sr]);
    }
    return 1;
}

/*
 STR sr, reg, offset
 STore base Register + offset
 Stores the value contained into sr at address (reg + offset)
 */
uint16_t str(uint16_t instr, int exec) {
    /* source register (DR) */
    uint16_t sr = (instr >> 9) & 0x7;

    /* base register (BaseR) */
    uint16_t base_r = (instr >> 6) & 0x7;

    /* offset 6 */
    uint16_t offset = sign_extend(instr & 0x3f, 6);
    sprintf(d_str, "STR R%d R%d 0x%04x", sr, base_r, offset);
    if(exec) {
        mem_write(vm.reg[base_r] + offset, vm.reg[sr]);
    }
    return 1;
}


/*
 RTI
 ReTurn from Interrupt
 */
uint16_t rti(uint16_t instr, int exec) {
    sprintf(d_str, "RTI\n");
    if(exec) {
        sys_abort();
    }
    return 0;
}

/*
 RES
 */
uint16_t res(uint16_t instr, int exec) {
    sprintf(d_str, "RES\n");
    if(exec) {
        sys_abort();
    }
    return 0;
}


uint16_t trap(uint16_t instr, int exec) {
    // save return addr
    vm.reg[R_R7] = vm.reg[R_PC];
    
    // get trap vector: 8 bits (7...0)
    uint16_t tvec = GET_BITS(instr, 7, 0);
    
    sprintf(d_str, "TRAP 0x%02x ; %s", tvec & 0xff, trap_name(tvec));
    
    // execute trap
    return exec ? trap_exec(tvec) : 1;
}

// =============================================================================
// MARK: - Opcode jump table
// =============================================================================
sOpcode opcodes[] = {
    { OP_BR,    br,     "branch" },
    { OP_ADD,   add,    "add" },
    { OP_LD,    ld,     "load" },
    { OP_ST,    st,     "store" },
    { OP_JSR,   jsr,    "jump register" },
    { OP_AND,   and,    "bitwise and" },
    { OP_LDR,   ldr,    "load register" },
    { OP_STR,   str,    "store register" },
    { OP_RTI,   rti,    "unused" },
    { OP_NOT,   not,    "bitwise not" },
    { OP_LDI,   ldi,    "load indirect" },
    { OP_STI,   sti,    "store indirect" },
    { OP_JMP,   jmp,    "jump" },
    { OP_RES,   res,    "reserved (unused)" },
    { OP_LEA,   lea,    "load effective address" },
    { OP_TRAP,  trap,   "execute trap" }
};



int op_exec(uint16_t instr) {
    opPtr f = opcodes[instr >> 12].optr;
    printf("0x%04x:\t0x%04x\t", (uint16_t)vm.reg[R_PC] >> 1, instr);
    uint16_t ret = f(instr, 1);
    printf("%s\n", d_str);
    return ret;
}


uint16_t op_assemble(char * instr) {
    return 0;
}

char * op_disasm(uint16_t addr, uint16_t instr) {
    char * linebuf = (char *)malloc(kDescMaxLen * sizeof(char));
    uint16_t code = instr >> 12;
    if(code >= 0 && code < OP_COUNT) {
        opPtr f = opcodes[instr >> 12].optr;
        f(instr, 0);
        sprintf(linebuf, "0x%04x:\t0x%04x\t%s\n",
                addr, instr, d_str);
    }
    else {
        uint8_t c = instr & 0xff;
        sprintf(linebuf, "0x%04x:\t0x%04x\t%s ; '%c' \n",
                addr, instr, "??", c);
    }
    return linebuf;
}
