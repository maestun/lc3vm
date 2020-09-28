//
//  alis_vm.c
//  lc3vm
//
//  Created by developer on 09/09/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"
#include "sys.h"

sAlisVM alis;

// =============================================================================
// MARK: - Private
// =============================================================================
alisRet readexec(sAlisOpcode * table, char * name, u8 identation) {
    if(alis.pc - alis.pc_org == kMaxVirtualRAMSize) {
        // pc overflow !
        debug(EDebugFatal, "PC OVERFLOW !");
    }
    else {
        for(int i = 0; i < identation; i++) {
            debug(EDebugVerbose, "\t");
        }
        // fetch code
        long steem_pc = 0x2d290; // TODO: adresse de main.ao dans l'emulateur steeù, aide pour debug
        debug(EDebugVerbose, "0x%06x: %s ", alis.pc - alis.pc_org + steem_pc, name);
        u8 code = *(alis.pc++);
        sAlisOpcode opcode = table[code];
        debug(EDebugVerbose, "%s (0x%02x)\n", opcode.name, code);
        return opcode.fptr();
    }
}

alisRet readexec_opcode() {
    readexec(opcodes, "opcode", 0);
}

alisRet readexec_opername() {
    readexec(opernames, "opername", 1);
}

alisRet readexec_storename() {
    readexec(storenames, "storename", 2);
}

alisRet readexec_addname() {
    readexec(addnames, "addname", 2);
}

u8 read8(void) {
    return *alis.pc++;
}

u16 read16(void) {
    return (*alis.pc++ << 8) + *alis.pc++;
}

u32 read24(void) {
    return (*alis.pc++ << 16) + (*alis.pc++ << 8) + *alis.pc++;
}

void readBytes(u32 len, u8 * dest) {
    while(len--) {
        *dest++ = *alis.pc++;
    }
}

void readToZero(u8 * dest) {
    while(*alis.pc++) {
        *dest++ = *alis.pc;
    }
}

uint16_t sign_extend(uint16_t x, int bit_count) {
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

uint16_t extend_w(uint8_t x) {
    return sign_extend(x, 8);
}

void writeStack8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->stack + offset) = value;
}

void writeStack16(u16 offset, u16 value) {
    *(u16 *)(alis.scripts[alis.scriptID]->stack + offset) = value;
}

void addStack8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->stack + offset) += value;
}

void addStack16(u16 offset, u16 value) {
    *(u16 *)(alis.scripts[alis.scriptID]->stack + offset) += value;
}

u8 pop8() {
    u8 val = *alis.vm_stack++;
    return val;
}

u16 pop16() {
    u16 val = (*alis.vm_stack++ << 8) + *alis.vm_stack++;
    return val;
}



// =============================================================================
// MARK: - VM API
// =============================================================================
void alis_init(sPlatform platform) {
    // clear virtual memory
    // memset(alis.memory, 0, sizeof(alis.memory));
    
    // init pointers
//    alis.memory_org = alis.memory;
//    alis.pc_org = alis.memory;
    
    // init vars
    alis.varD6 = alis.varD7 = 0;
    
    // init helpers
    if(alis.fp) {
        fclose(alis.fp);
        alis.fp = NULL;
    }
    
    alis.platform = platform;
    
    // TODO: scene ptr ??
//    alis.scene_ptr = (alis.memory + 0x6000);
    
    // TODO: init sys w/ platform
}

void alis_deinit() {
    // free scripts
    for(int i = 0; i < kMaxScripts; i++) {
        script_unload(alis.scripts[i]);
    }
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
//    memcpy(alis.memory + script->org,
//           script->code,
//           script->codelen * sizeof(u8));
    
    alis.scripts[script->ID] = script;
    
    // set pc to script origin in virtual ram
    alis.pc = alis.pc_org = script->code; // TODO: determine org
    alis.running = 1;
}
