//
//  vm_tests.c
//  lc3vm-orig
//
//  Created by developer on 08/09/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#include "vm_tests.h"
#include "sys.h"

/* tests */
int test_add_instr_1() {
  int pass = 1;

  uint16_t add_instr =
    ((OP_ADD & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    (R_R2 & 0x7);

  memory[0x3000] = add_instr;
  reg[R_R1] = 1;
  reg[R_R2] = 2;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 3) {
    printf("Expected register 0 to contain 3, got %d\n", reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_add_instr_2() {
  int pass = 1;

  uint16_t add_instr =
    ((OP_ADD & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    (1 << 5) |
    0x2;

  memory[0x3000] = add_instr;
  reg[R_R1] = 1;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 3) {
    printf("Expected register 0 to contain 3, got %d\n", reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_and_instr_1() {
  int pass = 1;

  uint16_t and_instr =
    ((OP_AND & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    (R_R2 & 0x7);

  memory[0x3000] = and_instr;
  reg[R_R1] = 0xff;
  reg[R_R2] = 0xf0;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0xf0) {
    printf("Expected register 0 to contain %d, got %d\n", 0xf0, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_and_instr_2() {
  int pass = 1;

  uint16_t and_instr =
    ((OP_AND & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    (1 << 5) |
    0x0f;

  memory[0x3000] = and_instr;
  reg[R_R1] = 0xff;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0x0f) {
    printf("Expected register 0 to contain %d, got %d\n", 0x0f, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_not_instr() {
  int pass = 1;

  uint16_t not_instr =
    ((OP_NOT & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    0x3f;

  memory[0x3000] = not_instr;
  reg[R_R1] = 0xf;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0xfff0) {
    printf("Expected register 0 to contain %d, got %d\n", 0xfff0, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_NEG) {
    printf("Expected condition flags to be %d, got %d\n", FL_NEG, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_br_instr_1() {
  int pass = 1;

  uint16_t br_instr =
    ((OP_BR & 0xf) << 12) |
    (1 << 11) |
    0x123;

  memory[0x3000] = br_instr;

  /* nothing should happen */
  reg[R_COND] = 0;
  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x3001) {
    printf("Expected program counter to contain %d, got %d\n", 0x3001, reg[R_PC]);
    pass = 0;
  }

  return pass;
}

int test_br_instr_2() {
  int pass = 1;

  uint16_t br_instr =
    ((OP_BR & 0xf) << 12) |
    (1 << 11) |
    0x0ff;

  memory[0x3000] = br_instr;

  reg[R_COND] = FL_NEG;
  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x3100) {
    printf("Expected program counter to contain %d, got %d\n", 0x3100, reg[R_PC]);
    pass = 0;
  }

  return pass;
}

int test_br_instr_3() {
  int pass = 1;

  uint16_t br_instr =
    ((OP_BR & 0xf) << 12) |
    (1 << 10) |
    0x0ff;

  memory[0x3000] = br_instr;

  reg[R_COND] = FL_ZRO;
  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x3100) {
    printf("Expected program counter to contain %d, got %d\n", 0x3100, reg[R_PC]);
    pass = 0;
  }

  return pass;
}

int test_br_instr_4() {
  int pass = 1;

  uint16_t br_instr =
    ((OP_BR & 0xf) << 12) |
    (1 << 9) |
    0x0ff;

  memory[0x3000] = br_instr;

  reg[R_COND] = FL_POS;
  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x3100) {
    printf("Expected program counter to contain %d, got %d\n", 0x3100, reg[R_PC]);
    pass = 0;
  }

  return pass;
}

int test_jmp_instr() {
  int pass = 1;

  uint16_t jmp_instr =
    ((OP_JMP & 0xf) << 12) |
    ((R_R0 & 0x7) << 6);

  memory[0x3000] = jmp_instr;
  reg[R_R0] = 0x1234;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x1234) {
    printf("Expected program counter to contain %d, got %d\n", 0x1234, reg[R_PC]);
    pass = 0;
  }

  return pass;
}

int test_jsr_instr_1() {
  int pass = 1;

  uint16_t jsr_instr =
    ((OP_JSR & 0xf) << 12) |
    (1 << 11) |
    0xff;

  memory[0x3000] = jsr_instr;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x3100) {
    printf("Expected program counter to contain %d, got %d\n", 0x3100, reg[R_PC]);
    pass = 0;
  }

  if (reg[R_R7] != 0x3001) {
    printf("Expected register 7 to contain %d, got %d\n", 0x3001, reg[R_R7]);
    pass = 0;
  }

  return pass;
}

int test_jsr_instr_2() {
  int pass = 1;

  uint16_t jsr_instr =
    ((OP_JSR & 0xf) << 12) |
    ((R_R0 & 0x7) << 6);

  memory[0x3000] = jsr_instr;
  reg[R_R0] = 0x1234;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_PC] != 0x1234) {
    printf("Expected program counter to contain %d, got %d\n", 0x1234, reg[R_PC]);
    pass = 0;
  }

  if (reg[R_R7] != 0x3001) {
    printf("Expected register 7 to contain %d, got %d\n", 0x3001, reg[R_R7]);
    pass = 0;
  }

  return pass;
}

int test_ld_instr() {
  int pass = 1;

  uint16_t ld_instr =
    ((OP_LD & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)   |
    0xff;

  memory[0x3000] = ld_instr;
  memory[0x3100] = 0x123;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0x123) {
    printf("Expected register 0 to contain %d, got %d\n", 0x123, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_ldi_instr() {
  int pass = 1;

  uint16_t ldi_instr =
    ((OP_LDI & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)   |
    0xff;

  memory[0x3000] = ldi_instr;
  memory[0x3100] = 0x3200;
  memory[0x3200] = 0x123;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0x123) {
    printf("Expected register 0 to contain %d, got %d\n", 0x123, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_ldr_instr() {
  int pass = 1;

  uint16_t ldr_instr =
    ((OP_LDR & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    0xf;

  memory[0x3000] = ldr_instr;
  reg[R_R1] = 0x31f1;
  memory[0x3200] = 0x123;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0x123) {
    printf("Expected register 0 to contain %d, got %d\n", 0x123, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_lea_instr() {
  int pass = 1;

  uint16_t lea_instr =
    ((OP_LEA & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    0xff;

  memory[0x3000] = lea_instr;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 0x3100) {
    printf("Expected register 0 to contain %d, got %d\n", 0x3100, reg[R_R0]);
    pass = 0;
  }

  if (reg[R_COND] != FL_POS) {
    printf("Expected condition flags to be %d, got %d\n", FL_POS, reg[R_COND]);
    pass = 0;
  }

  return pass;
}

int test_st_instr() {
  int pass = 1;

  uint16_t st_instr =
    ((OP_ST & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    0xff;

  memory[0x3000] = st_instr;
  reg[R_R0] = 0x123;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (memory[0x3100] != 0x123) {
    printf("Expected memory location %d to contain %d, got %d\n", 0x3100, 0x123, reg[R_R0]);
    pass = 0;
  }

  return pass;
}

int test_sti_instr() {
  int pass = 1;

  uint16_t sti_instr =
    ((OP_STI & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    0xff;

  memory[0x3000] = sti_instr;
  memory[0x3100] = 0x3200;
  reg[R_R0] = 0x123;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (memory[0x3200] != 0x123) {
    printf("Expected memory location %d to contain %d, got %d\n", 0x3200, 0x123, reg[R_R0]);
    pass = 0;
  }

  return pass;
}

int test_str_instr() {
  int pass = 1;

  uint16_t str_instr =
    ((OP_STR & 0xf) << 12) |
    ((R_R0 & 0x7) << 9)    |
    ((R_R1 & 0x7) << 6)    |
    0xf;

  memory[0x3000] = str_instr;
  reg[R_R0] = 0x123;
  reg[R_R1] = 0x31f1;

  int result = read_and_execute_instruction();
  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (memory[0x3200] != 0x123) {
    printf("Expected memory location %d to contain %d, got %d\n", 0x3200, 0x123, reg[R_R0]);
    pass = 0;
  }

  return pass;
}

int test_trap_getc() {
  int pass = 1;

  uint16_t trap_getc_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_GETC & 0xff);

  char in_buf[] = {'x'};
  char out_buf[256];
  FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
  FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");

    sys_init(in, out);
    
  int result = trap_exec(trap_getc_instr);
    sys_deinit();

  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 'x') {
    printf("Expected register 0 to contain %d, got %d\n", 'x', reg[R_R0]);
    pass = 0;
  }

  if (out_buf[0] != 0) {
    printf("Expected output buffer to contain %d, got %d\n", 0, out_buf[0]);
    pass = 0;
  }

  return pass;
}

int test_trap_out() {
  int pass = 1;

  uint16_t trap_out_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_OUT & 0xff);

  char in_buf[] = {0};
  char out_buf[256];
  FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
  FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");

  reg[R_R0] = 'x';

  int result = trap_exec(trap_out_instr);
  fclose(in);
  fclose(out);

  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (out_buf[0] != 'x') {
    printf("Expected output buffer to contain %d, got %d\n", 'x', out_buf[0]);
    pass = 0;
  }

  return pass;
}

int test_trap_puts() {
  int pass = 1;

  uint16_t trap_puts_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_PUTS & 0xff);

  char in_buf[] = {0};
  char out_buf[256];
  FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
  FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");

    sys_init(in, out);
    
  reg[R_R0] = 0x3100;
  memory[0x3100] = 'h';
  memory[0x3101] = 'e';
  memory[0x3102] = 'y';
  memory[0x3103] = 0;

  int result = trap_exec(trap_puts_instr);
  fclose(in);
  fclose(out);

  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (strncmp(out_buf, "hey", 3) != 0) {
    printf("Expected output buffer to contain %s, got %s\n", "hey", out_buf);
    pass = 0;
  }

  return pass;
}

int test_trap_in() {
  int pass = 1;

  uint16_t trap_in_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_IN & 0xff);

  char in_buf[] = {'x'};
  char out_buf[256];
  FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
  FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");
sys_init(in, out);
  int result = trap_exec(trap_in_instr);
  fclose(in);
  fclose(out);

  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (reg[R_R0] != 'x') {
    printf("Expected register 0 to contain %d, got %d\n", 'x', reg[R_R0]);
  }

  if (strncmp(out_buf, "Enter a character: x", 27) != 0) {
    printf("Expected output buffer to contain %s, got %s\n", "Enter a character: x", out_buf);
    pass = 0;
  }

  return pass;
}

int test_trap_putsp() {
  int pass = 1;

  uint16_t trap_putsp_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_PUTSP & 0xff);

  char in_buf[] = {0};
  char out_buf[256];
  FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
  FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");
sys_init(in, out);
  reg[R_R0] = 0x3100;
  memory[0x3100] = 'h' | ('e' << 8);
  memory[0x3101] = 'y' | (' ' << 8);
  memory[0x3102] = 'd' | ('u' << 8);
  memory[0x3103] = 'd' | ('e' << 8);
  memory[0x3104] = 0;

  int result = trap_exec(trap_putsp_instr);
  fclose(in);
  fclose(out);

  if (result != 1) {
    printf("Expected return value to be 1, got %d\n", result);
    pass = 0;
  }

  if (strncmp(out_buf, "hey dude", 8) != 0) {
    printf("Expected output buffer to contain %s, got %s\n", "hey dude", out_buf);
    pass = 0;
  }

  return pass;
}

int test_trap_halt() {
  int pass = 1;

  uint16_t trap_halt_instr =
    ((OP_TRAP & 0xf) << 12) |
    (TRAP_HALT & 0xff);


      char in_buf[] = {0};
      char out_buf[256];
      FILE *in = fmemopen(in_buf, sizeof(in_buf), "r");
      FILE *out = fmemopen(out_buf, sizeof(out_buf), "w");
    sys_init(in, out);
  int result = trap_exec(trap_halt_instr);
  fclose(in);
  fclose(out);

  if (result != 0) {
    printf("Expected return value to be 0, got %d\n", result);
    pass = 0;
  }

  if (strncmp(out_buf, "HALT", 8) != 0) {
    printf("Expected output buffer to contain %s, got %s\n", "hey dude", out_buf);
    pass = 0;
  }

  return pass;
}

int vm_run_tests() {
  int (*tests[])(void) = {
    test_add_instr_1,
    test_add_instr_2,
    test_and_instr_1,
    test_and_instr_2,
    test_not_instr,
    test_br_instr_1,
    test_br_instr_2,
    test_br_instr_3,
    test_br_instr_4,
    test_jmp_instr,
    test_jsr_instr_1,
    test_jsr_instr_2,
    test_ld_instr,
    test_ldi_instr,
    test_ldr_instr,
    test_lea_instr,
    test_st_instr,
    test_sti_instr,
    test_str_instr,
    test_trap_getc,
    test_trap_out,
    test_trap_puts,
    test_trap_in,
    test_trap_putsp,
    NULL
  };
    

  int i, result, ok = 1;
  for (i = 0; tests[i] != NULL; i++) {
    /* clear memory */
    memset(reg, 0, sizeof(reg));
    memset(memory, 0, sizeof(memory));

    /* set the PC to starting position */
    /* 0x3000 is the default */
    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    result = tests[i]();
    if (!result) {
      printf("Test %d failed!\n", i);
      ok = 0;
    }
  }
  
    printf(ok ? "All tests passed!\n" : "Tests failed!\n");
    return ok;
}
