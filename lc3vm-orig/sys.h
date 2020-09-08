//
//  sys.h
//  lc3vm-orig
//

#ifndef sys_h
#define sys_h

#include "config.h"

void        sys_init(FILE * term_in, FILE * term_out);
void        sys_deinit(void);

uint16_t    sys_getc(void);
void        sys_putc(uint16_t c);
void        sys_fflush(void);
void        sys_fprintf(char * format, ...);

#endif /* sys_h */
