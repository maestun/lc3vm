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
// MARK: - Private
// =============================================================================
static alisRet readexec_opcode() {
    if(alis.pc == kMaxVirtualRAMSize) {
        // pc overflow !
        debug(EDebugFatal, "PC OVERFLOW !");
    }
    else {
        // fetch opcode
        debug(EDebugVerbose, "0x%06x: ", alis.pc);
        u8 i = alis.memory[alis.pc++];
        sAlisOpcode opcode = opcodes[i];
        debug(EDebugVerbose, "0x%02x\t%s\n", i, opcode.name);
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
    
    // TODO: scene ptr ??
    alis.scene_ptr = (alis.memory + 0x6000);
    
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
        debug(EDebugFatal,
                   "Failed to load main script '%s'\n",
                   alis.platform.main);
        ret = 1;
    }
    return ret;
}

void alis_start_script(sAlisScript * script) {
    // copy script data to virtual ram, at given offset (script origin)
    memcpy(alis.memory + script->org,
           script->code,
           script->codelen * sizeof(u8));
    
    // set pc to script origin in virtual ram
    alis.pc = script->org; // TODO: determine org
    alis.running = 1;
}
