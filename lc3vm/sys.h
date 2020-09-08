//
//  sys.h
//  lc3vm
//

#ifndef sys_h
#define sys_h

#include "config.h"

void        sys_init(FILE * term_in, FILE * term_out);
void        sys_deinit(void);

void        sys_abort(void);
uint16_t    sys_check_key(void);
uint16_t    sys_getc(void);
void        sys_putc(uint16_t c);
void        sys_fflush(void);
void        sys_fprintf(char * format, ...);

#endif /* sys_h */
