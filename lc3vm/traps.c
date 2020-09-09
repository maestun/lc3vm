//
//  traps.c
//  lc3vm
//

#include "sys.h"
#include "traps.h"
#include "vm.h"

typedef int (*trapPtr)(void);

typedef struct {
    uint8_t code;
    trapPtr tptr;
    char    name[kNameMaxLen];
    char    desc[kDescMaxLen];
} sTrap;


// =============================================================================
// MARK: - Trap implementation
// =============================================================================
// TRAP 0x20: GETC
// Read a single character from the keyboard.
// The character is not echoed onto the console.
// Its ASCII code is copied into R0. The high eight bits of R0 are cleared.
int trap_getc() {
    uint16_t c = sys_getc();
    vm.reg[R_R0] = c;
    return 1;
}

// TRAP 0x21: OUT
// Write a character in R0[7:0] to the console display.
int trap_out() {
    char c = (char)vm.reg[R_R0 & 0xff];
//    putc(c, out);
    sys_putc(c);
    return 1;
}

// TRAP 0x22: PUTS
// Write a string of ASCII characters to the console display.
// The characters are contained in consecutive memory locations,
// one character per memory location, starting with the address specified in R0.
// Writing terminates with the occurrence of 0x0000 in a memory location.
int trap_puts() {
    /* one char per word */
    uint16_t *word = vm.memory + vm.reg[R_R0];
    while (*word) {
      sys_putc((char)(*word & 0xff));
      word++;
    }
    sys_fflush();
    return 1;
}

// TRAP 0x23: IN
// Print a prompt on the screen and read a single character from the keyboard.
// The character is echoed onto the console monitor,
// and its ASCII code is copied into R0.
// The high eight bits of R0 are cleared.
int trap_in() {
    sys_fprintf("Enter a character: ");
    sys_fflush();

    uint16_t c = sys_getc();
    sys_putc((char)c);
    sys_fflush();

    vm.reg[R_R0] = c;
    return 1;
}

// TRAP 0x24: PUTSP
// Write a string of ASCII characters to the console.
// The characters are contained in consecutive memory locations, two characters
// per memory location, starting with the address specified in R0.
// The ASCII code contained in bits [7:0] of a memory location is written
// to the console first.
// Then the ASCII code contained in bits [15:8] of that memory location is
// written to the console. (A character string consisting of an odd number of
// characters to be written will have x00 in bits [15:8] of the memory location
// containing the last character to be written.)
// Writing terminates with the occurrence of x0000 in a memory location.
int trap_putsp() {
    // one char per byte (two bytes per word)
    // here we need to swap back to big endian format
    uint16_t *word = vm.memory + vm.reg[R_R0];
    while (*word) {
      sys_putc((char)(*word & 0xff));

      char c = *word >> 8;
      if (c) {
        sys_putc(c);
      }
      word++;
    }
    sys_fflush();
    return 1;
}

// TRAP 0x25: HALT
// Halt execution and print a message on the console.
int trap_halt() {
    sys_fprintf("HALT\n");
    sys_fflush();
    return 0;
}

int trap_stub() {
    return 1;
}

// =============================================================================
// MARK: - Trap jump table
// =============================================================================
sTrap traps[] = {
    { 0x00, trap_stub,  "stub", "stub" },
    { 0x01, trap_stub,  "stub", "stub" },
    { 0x02, trap_stub,  "stub", "stub" },
    { 0x03, trap_stub,  "stub", "stub" },
    { 0x04, trap_stub,  "stub", "stub" },
    { 0x05, trap_stub,  "stub", "stub" },
    { 0x06, trap_stub,  "stub", "stub" },
    { 0x07, trap_stub,  "stub", "stub" },
    { 0x08, trap_stub,  "stub", "stub" },
    { 0x09, trap_stub,  "stub", "stub" },
    { 0x0a, trap_stub,  "stub", "stub" },
    { 0x0b, trap_stub,  "stub", "stub" },
    { 0x0c, trap_stub,  "stub", "stub" },
    { 0x0d, trap_stub,  "stub", "stub" },
    { 0x0e, trap_stub,  "stub", "stub" },
    { 0x0f, trap_stub,  "stub", "stub" },
    { 0x10, trap_stub,  "stub", "stub" },
    { 0x11, trap_stub,  "stub", "stub" },
    { 0x12, trap_stub,  "stub", "stub" },
    { 0x13, trap_stub,  "stub", "stub" },
    { 0x14, trap_stub,  "stub", "stub" },
    { 0x15, trap_stub,  "stub", "stub" },
    { 0x16, trap_stub,  "stub", "stub" },
    { 0x17, trap_stub,  "stub", "stub" },
    { 0x18, trap_stub,  "stub", "stub" },
    { 0x19, trap_stub,  "stub", "stub" },
    { 0x1a, trap_stub,  "stub", "stub" },
    { 0x1b, trap_stub,  "stub", "stub" },
    { 0x1c, trap_stub,  "stub", "stub" },
    { 0x1d, trap_stub,  "stub", "stub" },
    { 0x1e, trap_stub,  "stub", "stub" },
    { 0x1f, trap_stub,  "stub", "stub" },
    { TRAP_GETC,    trap_getc,  "GETC", "get character from keyboard, not echoed onto the terminal" },
    { TRAP_OUT,     trap_out,   "OUT",  "output a character" },
    { TRAP_PUTS,    trap_puts,  "PUTS", "output a word string" },
    { TRAP_IN,      trap_in,    "IN",   "get character from keyboard, echoed onto the terminal" },
    { TRAP_PUTSP,   trap_putsp, "PUTSP","output a byte string" },
    { TRAP_HALT,    trap_halt,  "HALT", "halt the program" }
};

uint16_t trap_exec(uint16_t instr) {
    // execute trap
    uint8_t tvec = instr & 0xff;
    trapPtr t = traps[tvec].tptr;
    // debug_instr("TRAP\t0x%02x\t; %s\n", tvec, traps[tvec].desc);
    return t();
}

char * trap_name(uint16_t tvec) {
    return traps[tvec].name;
}
