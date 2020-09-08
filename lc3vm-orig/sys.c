//
//  sys.c
//  lc3vm-orig
//

#include "sys.h"

typedef struct {
    FILE * term_in;
    FILE * term_out;
} sSys;

sSys sys;


/* terminal input setup */
struct termios original_tio;

// TODO: document this
void disable_input_buffering() {
  tcgetattr(STDIN_FILENO, &original_tio);
  struct termios new_tio = original_tio;
  new_tio.c_lflag &= ~ICANON & ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

void restore_input_buffering() {
  tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
}

void handle_interrupt(int signal) {
  restore_input_buffering();
  printf("\n");
  exit(-2);
}


void sys_init(FILE * term_in, FILE * term_out) {
    
    sys.term_in = term_in;
    sys.term_out = term_out;
    
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();
}


void sys_deinit() {
    
    fclose(sys.term_in);
    fclose(sys.term_out);
    
    restore_input_buffering();
}

uint16_t sys_getc() {
    return getc(sys.term_in);
}

void sys_putc(uint16_t c) {
    putc(c, sys.term_out);
}

void sys_fflush() {
    fflush(sys.term_out);
}

void sys_fprintf(char * format, ...) {
    va_list arg;
    va_start(arg, format);
    fprintf(sys.term_out, format, arg);
    va_end(arg);
}
