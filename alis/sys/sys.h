//
//  sys.h
//  alis
//

#ifndef sys_h
#define sys_h

#include "config.h"
#include "debug.h"


typedef void (*vmStep)(void);
void    sys_main(vmStep fStep);
void    sys_init(void);
u8      sys_poll_event(void);
void    sys_deinit(void);


typedef struct {
    int x, y;
    u8 lb, rb;
} mouse_t;
mouse_t sys_get_mouse(void);


typedef struct {
    u16     w, h;
    u8      scale;
    u8 *    data;
} pixelbuf_t;
void    sys_render(pixelbuf_t buffer);

// FILE I/O
int     sys_fclose(FILE * fp);
FILE *  sys_fopen(char * path);
u8      sys_fexists(char * path);
u16     sys_get_model(void);
u16     sys_random(void);

#endif /* sys_h */
