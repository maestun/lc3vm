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
        // fetch code
        long steem_pc = 0x2d290; // TODO: adresse de main.ao dans l'emulateur steem, aide pour debug
        debug(EDebugVerbose, "0x%06x: %s ", alis.pc - alis.pc_org + steem_pc, name);
        u8 code = *(alis.pc++);
        sAlisOpcode opcode = table[code];
        debug(EDebugVerbose, "%s (0x%02x)\n", opcode.name, code);
        return opcode.fptr();
    }
}

alisRet readexec_opcode() {
    debug(EDebugVerbose, "------\n");
    return readexec(opcodes, "opcode", 0);
}

alisRet readexec_opername() {
    return readexec(opernames, "opername", 1);
}

alisRet readexec_storename() {
    return readexec(storenames, "storename", 2);
}

alisRet readexec_addname() {
    return readexec(addnames, "addname", 2);
}

alisRet readexec_addname_swap() {
    u8 * tmp = alis.bssChunk1;
    alis.bssChunk1 = alis.bssChunk3;
    alis.bssChunk3 = tmp;
    return readexec_addname();
}

alisRet readexec_opername_saveD7() {
    alis.varD6 = alis.varD7;
    return readexec_opername();
}

alisRet readexec_opername_swap() {
    u8 * tmp = alis.bssChunk1;
    alis.bssChunk1 = alis.bssChunk3;
    alis.bssChunk3 = tmp;
    return readexec_opername();
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

void write8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->vram_org + offset) = value;
}

void write16(u16 offset, u16 value) {
    *(u16 *)(alis.scripts[alis.scriptID]->vram_org + offset) = value;
}

void add8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->vram_org + offset) += value;
}

void add16(u16 offset, u16 value) {
    *(u16 *)(alis.scripts[alis.scriptID]->vram_org + offset) += value;
}

u8 pop8() {
    u8 val = *alis.stack++;
    return val;
}

u16 pop16() {
    u16 val = (*alis.stack++ << 8) + *alis.stack++;
    return val;
}

void push8(u32 offset, u8 val) {
    *(u8 *)(alis.stack_org + offset) = val;
}

void push16(u32 offset, u16 val) {
    *(u16 *)(alis.stack_org + offset) = val;
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
    alis.ram = (u8 *)malloc(kMaxVirtualRAMSize * sizeof(u8));
    memset(alis.ram, 0, kMaxVirtualRAMSize * sizeof(u8));
    alis.varD6 = alis.varD7 = 0;
    alis.bssChunk1 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    alis.bssChunk2 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    alis.bssChunk3 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk1, 0, kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk2, 0, kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk3, 0, kBSSChunkLen * sizeof(u8));
    
    // init helpers
    if(alis.fp) {
        fclose(alis.fp);
        alis.fp = NULL;
    }
    
    
    alis.stack_org = (u8 *)malloc(kMaxVirtualRAMSize * sizeof(u8));
    alis.stack = alis.stack_org;
    
    
    
    
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
    free(alis.ram);
    free(alis.stack_org);
    free(alis.bssChunk1);
    free(alis.bssChunk2);
    free(alis.bssChunk3);
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
    alis.pc = alis.pc_org = script->data + script->headerlen; // TODO: determine org
    alis.running = 1;
}
