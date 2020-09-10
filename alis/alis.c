//
//  alis_vm.c
//  lc3vm
//
//  Created by developer on 09/09/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#include "alis.h"
#include "sys.h"

sAlisVM alis;

// =============================================================================
// MARK: - Helpers
// =============================================================================

void alis_debug(EDebugLevel level, char * format, ...) {
//    static FILE * dbfp = NULL;
//    if(dbfp == NULL) {
//        dbfp = fopen("alis_debug.log", "w");
//    }
    if(level <= DEBUG_LEVEL) {
        va_list arg;
        va_start(arg, format);
        vfprintf(stdout, format, arg);
        fflush(stdout);
        va_end(arg);
    }
}

// =============================================================================
// MARK: - Private
// =============================================================================
static alisRet readexec_opcode() {
    if(alis.pc == kMaxVirtualRAMSize) {
        // pc overflow !
        alis_debug(EDebugFatal, "PC OVERFLOW !");
    }
    else {
        // fetch opcode
        u8 i = alis.memory[alis.pc++];
        sAlisOpcode opcode = opcodes[i];
        opcode.fptr();
    }
}


// =============================================================================
// MARK: - VM API
// =============================================================================
void alis_init(sPlatform platform) {
    // clear virtual memory
    memset(alis.memory, 0, sizeof(alis.memory));
    
    // init pointers
    alis.memory_org = alis.memory;
    alis.pc_org = alis.memory;
    alis.sp_org = alis.memory;
    
    // init vars
    alis.varD6 = alis.varD7 = 0;
    
    // init helpers
    if(alis.fp) {
        fclose(alis.fp);
        alis.fp = NULL;
    }
    
    alis.platform = platform;
    
    // TODO: init sys w/ platform
}

void alis_deinit() {
}

u8 alis_main() {
    u8 ret = 0;
    sAlisScript * main = script_load(alis.platform.main);
    if(main) {
        alis_start_script(main);
        while(alis.running) {
            readexec_opcode();
        }
    }
    else {
        alis_debug(EDebugFatal,
                   "Failed to load main script '%s'\n",
                   alis.platform.main);
        ret = 1;
    }
    return ret;
}

void alis_start_script(sAlisScript * script) {
    // copy script data to virtual ram, at given offset (script origin)
    memcpy(alis.memory + script->org, script->code, script->len * sizeof(u8));
    
    // set pc to script origin in virtual ram
    alis.pc = script->org;
    
    alis.running = 1;
}

void alis_step() {
    if(alis.running) {
        readexec_opcode();
    }
}
