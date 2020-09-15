//
//  sys.c
//  alis
//

#include "sys.h"

mouse_t mouse;

void sys_init() {
    
}

void sys_deinit() {
    
}

mouse_t sys_get_mouse() {
    // STUBBED
    return mouse;
}


// MARK: - File I/O
FILE * sys_fopen(char * path) {
    return fopen(path, "r");
}
int sys_fclose(FILE * fp) {
    return fclose(fp);
}
