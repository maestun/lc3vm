//
//  disasm.c
//  lc3vm
//

#include "disasm.h"
#include "opcodes.h"
#include "traps.h"

char * disasm(uint16_t * data, uint16_t len, uint16_t origin) {
    
    uint16_t * ptr = (uint16_t *)(data);
    uint16_t * end = (uint16_t *)(data + len);
    
    long linecount = (end - ptr);
    char * buf = (char *)malloc(kDescMaxLen * (1 + linecount));
    sprintf(buf, ".ORIG 0x%04x\n", origin);
    while (ptr < end) {
        char * linebuf = op_disasm(ptr - data, *ptr);
        strcat(buf, linebuf);
        free(linebuf);
        ptr++;
    }
    
    return buf;
}

char * disasm_memory() {
    return disasm(vm.memory, UINT16_MAX, 0);
}

char * disasm_script(sScript * script) {
    return disasm(script->data, script->len, script->org);
}
