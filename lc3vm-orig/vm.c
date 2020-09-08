//
//  vm.c
//  lc3vm-orig
//
//  Created by developer on 08/09/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#include "vm.h"

uint16_t memory[UINT16_MAX];
uint16_t reg[R_COUNT];

void debug_instr(char * format, ...) {
//    static FILE * dbfp = NULL;
//    if(dbfp == NULL) {
//        dbfp = fopen("debug.s", "w");
//    }
//
//    va_list arg;
//    va_start(arg, format);
//    vfprintf(dbfp, format, arg);
//    fflush(dbfp);
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
  if (reg[r] == 0) {
    reg[R_COND] = FL_ZRO;
  }
  else if (reg[r] >> 15) { /* a 1 in the left-most bit indicates negative */
    reg[R_COND] = FL_NEG;
  }
  else {
    reg[R_COND] = FL_POS;
  }
}

/* change endianness */
uint16_t swap16(uint16_t x) {
    return (x << 8) | (x >> 8);
}



/* get keyboard status */
uint16_t check_key() {
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  return select(1, &readfds, NULL, NULL, &timeout) != 0;
}

/* memory access */
void mem_write(uint16_t address, uint16_t val) {
  memory[address] = val;
}

uint16_t mem_read(uint16_t address) {
  /* reading the memory mapped keyboard register triggers a key check */
  if (address == MR_KBSR) {
    if (check_key()) {
      memory[MR_KBSR] = (1 << 15);
      memory[MR_KBDR] = getchar();
    }
    else {
      memory[MR_KBSR] = 0;
    }
  }
  return memory[address];
}


/* read and execute instruction */
int read_and_execute_instruction() {
  int running = 1;
  int is_max = R_PC == UINT16_MAX;

  /* FETCH */
    
    debug_instr("0x%04x:\t", reg[R_PC]);
    
    uint16_t instr = mem_read(reg[R_PC]++);
    uint16_t op = instr >> 12;

    debug_instr("0x%04x\t", instr);
    
  switch (op) {
    case OP_ADD:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;
        /* first operand (SR1) */
        uint16_t sr1 = (instr >> 6) & 0x7;
        /* whether we are in immediate mode */
        uint16_t imm_flag = (instr >> 5) & 0x1;

        if (imm_flag) {
          uint16_t imm5 = sign_extend(instr & 0x1f, 5);
          reg[dr] = reg[sr1] + imm5;
            debug_instr("ADD R%d R%d 0x%04x\n", dr, sr1, imm5);
        }
        else {
          uint16_t sr2 = instr & 0x7;
          reg[dr] = reg[sr1] + reg[sr2];
            debug_instr("ADD R%d R%d R%d\n", dr, sr1, sr2);
        }

        update_flags(dr);
      }
      break;
    case OP_AND:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;
        /* first operand (SR1) */
        uint16_t sr1 = (instr >> 6) & 0x7;
        /* whether we are in immediate mode */
        uint16_t imm_flag = (instr >> 5) & 0x1;

        if (imm_flag) {
          uint16_t imm5 = sign_extend(instr & 0x1f, 5);
          reg[dr] = reg[sr1] & imm5;
            
            debug_instr("AND R%d R%d 0x%04x\n", dr, sr1, imm5);
        }
        else {
          uint16_t sr2 = instr & 0x7;
          reg[dr] = reg[sr1] & reg[sr2];
            
            debug_instr("AND R%d R%d R%d\n", dr, sr1, sr2);
        }
        update_flags(dr);
      }
      break;
    case OP_NOT:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;

        /* source register (SR) */
        uint16_t sr = (instr >> 6) & 0x7;

        reg[dr] = ~reg[sr];
          
          debug_instr("NOT R%d R%d\n", dr, sr);
        update_flags(dr);
      }
      break;
    case OP_BR:
      {
        uint16_t n_flag = (instr >> 11) & 0x1;
        uint16_t z_flag = (instr >> 10) & 0x1;
        uint16_t p_flag = (instr >> 9) & 0x1;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        /* advance program counter if one of the following is true:
         * - n_flag is set and negative condition flag is set
         * - z_flag is set and zero condition flag is set
         * - p_flag is set and positive condition flag is set */
        if ((n_flag && (reg[R_COND] & FL_NEG)) ||
            (z_flag && (reg[R_COND] & FL_ZRO)) ||
            (p_flag && (reg[R_COND] & FL_POS))) {

          reg[R_PC] += pc_offset;
            
            debug_instr("BR%s%s%s 0x%04x\n",
                        n_flag ? "n" : "",
                        z_flag ? "z" : "",
                        p_flag ? "p" : "",
                        pc_offset);

        }
      }
      break;
    case OP_JMP:
      {
        uint16_t base_r = (instr >> 6) & 0x7;
          
          debug_instr(base_r == R_R7 ? "RET\n" : "JMP R%d\n", base_r);
        reg[R_PC] = reg[base_r];
      }
      break;
    case OP_JSR:
      {
        /* save PC in R7 to jump back to later */
        reg[R_R7] = reg[R_PC];

        /* whether we are in immediate mode */
        uint16_t imm_flag = (instr >> 11) & 0x1;

        if (imm_flag) {
          /* PCoffset 11 */
          uint16_t pc_offset = sign_extend(instr & 0x7ff, 11);

            debug_instr("JSR 0x%04x\n", pc_offset);

          /* add offset to program counter */
          reg[R_PC] += pc_offset;
        }
        else {
          /* assign contents of base register directly to program counter */
          uint16_t base_r = (instr >> 6) & 0x7;
            
            debug_instr("JSRR R%d\n", base_r);
            reg[R_PC] = reg[base_r];
        }
      }
      break;
    case OP_LD:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        /* add pc_offset to the current PC and load that memory location */
        reg[dr] = mem_read(reg[R_PC] + pc_offset);
        update_flags(dr);
          
          debug_instr("LD R%d 0x%04x\n", dr, pc_offset);
      }
      break;
    case OP_LDI:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        /* add pc_offset to the current PC, look at that memory location to
         * get the final address */
        reg[dr] = mem_read(mem_read(reg[R_PC] + pc_offset));
        update_flags(dr);
      }
      break;
    case OP_LDR:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;

        /* base register (BaseR) */
        uint16_t base_r = (instr >> 6) & 0x7;

        /* offset 6 */
        uint16_t offset = sign_extend(instr & 0x3f, 6);

        reg[dr] = mem_read(reg[base_r] + offset);
        update_flags(dr);
      }
      break;
    case OP_LEA:
      {
        /* destination register (DR) */
        uint16_t dr = (instr >> 9) & 0x7;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        reg[dr] = reg[R_PC] + pc_offset;
        update_flags(dr);
      }
      break;
    case OP_ST:
      {
        /* source register (SR) */
        uint16_t sr = (instr >> 9) & 0x7;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        mem_write(reg[R_PC] + pc_offset, reg[sr]);
      }
      break;
    case OP_STI:
      {
        /* source register (SR) */
        uint16_t sr = (instr >> 9) & 0x7;

        /* PCoffset 9 */
        uint16_t pc_offset = sign_extend(instr & 0x1ff, 9);

        mem_write(mem_read(reg[R_PC] + pc_offset), reg[sr]);
      }
      break;
    case OP_STR:
      {
        /* source register (DR) */
        uint16_t sr = (instr >> 9) & 0x7;

        /* base register (BaseR) */
        uint16_t base_r = (instr >> 6) & 0x7;

        /* offset 6 */
        uint16_t offset = sign_extend(instr & 0x3f, 6);

        mem_write(reg[base_r] + offset, reg[sr]);
      }
      break;
    case OP_TRAP:
      running = trap_exec(instr);
      break;
    case OP_RES:
    case OP_RTI:
    default:
      abort();
  }

  if (running && is_max) {
    printf("Program counter overflow!");
    return 0;
  }

  return running;
}



/* load program into memory from a file */
void read_image_file(FILE *file) {
  /* the origin tells us where in memory to place the image */
  uint16_t origin;
  fread(&origin, sizeof(origin), 1, file);
  origin = swap16(origin);

  /* we know the maximum file size so we only need one fread */
  uint16_t max_read = UINT16_MAX - origin;
  uint16_t *p = memory + origin;
  size_t read = fread(p, sizeof(uint16_t), max_read, file);

  /* swap to little endian */
  while (read-- > 0) {
    *p = swap16(*p);
    ++p;
  }
}

int read_image(const char* image_path) {
  FILE *file = fopen(image_path, "rb");
  if (!file) { return 0; };
  read_image_file(file);
  fclose(file);
  return 1;
}
