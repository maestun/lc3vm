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

u8 sys_fexists(char * name) {
    u8 ret = 0;
    FILE * fp = sys_fopen(name);
    if(fp) {
        ret = 1;
        sys_fclose(fp);
    }
    return ret;
}


u16 sys_get_model(void) {
    debug(EDebugWarning, "\n%s SIMULATED\n", __FUNCTION__);
    return 0x456; // Atari STe / 1MB / Lowrez
}
