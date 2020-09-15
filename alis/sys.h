//
//  sys.h
//  alis
//

#ifndef sys_h
#define sys_h

#include "config.h"

typedef u32 mouse_t;

mouse_t sys_get_mouse(void);

int sys_fclose(FILE * fp);
FILE * sys_fopen(char * path);


#endif /* sys_h */
