//
//  sys.h
//  alis
//

#ifndef sys_h
#define sys_h

#include "config.h"
#include "debug.h"

typedef u32 mouse_t;
mouse_t sys_get_mouse(void);


// FILE I/O
int     sys_fclose(FILE * fp);
FILE *  sys_fopen(char * path);
u8      sys_fexists(char * path);
u16     sys_get_model(void);
u16     sys_random(void);

#endif /* sys_h */
