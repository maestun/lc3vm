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
#include "utils.h"

sAlisVM alis;

// =============================================================================
// MARK: - Private
// =============================================================================
alisRet readexec(sAlisOpcode * table, char * name, u8 identation) {
    if(alis.pc - alis.pc_org == kVirtualRAMSize) {
        // pc overflow !
        debug(EDebugFatal, "PC OVERFLOW !");
    }
    else {
        // fetch code
        u8 code = *(alis.pc++);
        sAlisOpcode opcode = table[code];
        debug(EDebugVerbose, " %s", opcode.name);
        return opcode.fptr();
    }
}

alisRet readexec_opcode() {
    //debug(EDebugVerbose, "------\n");
    debug(EDebugVerbose, "\n");
    
    // TODO: adresse de script dans l'emulateur steem, aide pour debug
    debug(EDebugVerbose, "0x%06x:", alis.pc - alis.pc_org + alis.scripts[alis.scriptID]->org);
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


// =============================================================================
// MARK: - Script
// =============================================================================
void script_read_debug(u32 value) {
    if (value > 0xffff) {
        debug(EDebugVerbose, " 0x%06x", value);
    }
    else if (value > 0xff) {
        debug(EDebugVerbose, " 0x%04x", value);
    }
    else  {
        debug(EDebugVerbose, " 0x%02x", value);
    }
}

u8 script_read8(void) {
    u8 ret = *alis.pc++;
    script_read_debug(ret);
    return ret;
}

u16 script_read8ext16(void) {
    u16 ret = extend_w(*alis.pc++);
    script_read_debug(ret);
    return  ret;
}

u32 script_read8ext32(void) {
    u16 ret = extend_l(extend_w(*alis.pc++));
    script_read_debug(ret);
    return  ret;
}

u16 script_read16(void) {
    u16 ret = (*alis.pc++ << 8) + *alis.pc++;
    script_read_debug(ret);
    return ret;
}

u32 script_read16ext32(void) {
    u32 ret = extend_l((*alis.pc++ << 8) + *alis.pc++);
    script_read_debug(ret);
    return ret;
}

u32 script_read24(void) {
    u32 ret = (*alis.pc++ << 16) + (*alis.pc++ << 8) + *alis.pc++;
    script_read_debug(ret);
    return ret;
}

void script_read_bytes(u32 len, u8 * dest) {
    while(len--) {
        *dest++ = *alis.pc++;
    }
}

void script_read_until_zero(u8 * dest) {
    while(*alis.pc) {
        *dest++ = *alis.pc++;
    }
    alis.pc++;
}


// =============================================================================
// MARK: - Virtual RAM
// =============================================================================
u8 vram_read8(u16 offset) {
    return *(u8 *)(alis.scripts[alis.scriptID]->ram + offset);
}

u16 vram_read16(u16 offset) {
    return *(u16 *)(alis.scripts[alis.scriptID]->ram + offset);
}

void vram_write8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->ram + offset) = value;
}

void vram_write16(u16 offset, u16 value) {
    value = 0xcafe;
    *(u16 *)(alis.scripts[alis.scriptID]->ram + offset) = value;
}

void vram_add8(u16 offset, u8 value) {
    *(u8 *)(alis.scripts[alis.scriptID]->ram + offset) += value;
}

void vram_add16(u16 offset, u16 value) {
    *(u16 *)(alis.scripts[alis.scriptID]->ram + offset) += value;
}

void push8(u8 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u8);
    *(u8 *)(alis.scripts[alis.scriptID]->sp) = value;
}

void push16(u16 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u16);
    *(u16 *)(alis.scripts[alis.scriptID]->sp) = value;
}

void push32(u32 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u32);
    *(u32 *)(alis.scripts[alis.scriptID]->sp) = value;
}

u8 pop8() {
    u8 ret = *(u8 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u8);
    return ret;
}

u16 pop16() {
    u16 ret = *(u16 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u16);
    return ret;
}

u32 pop32() {
    u32 ret = *(u32 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u32);
    return ret;
}

void script_jump(u32 offset) {
    if(!alis.disasm) {
        alis.pc += offset;
    }
}


// =============================================================================
// MARK: - Push and Pop data in virtual RAM using virtual stack pointer
// =============================================================================
//u8 pop8() {
//    u8 val = *alis.stack++;
//    return val;
//}
//
//u16 pop16() {
//    u16 val = (*alis.stack++ << 8) + *alis.stack++;
//    return val;
//}
//
//void push8(u32 offset, u8 val) {
//    *(u8 *)(alis.stack_org + offset) = val;
//}
//
//void push16(u32 offset, u16 val) {
//    *(u16 *)(alis.stack_org + offset) = val;
//}

// =============================================================================
// MARK: - VM API
// =============================================================================
void alis_init(sPlatform platform) {
    
    // init virtual ram
//    alis.ram = (u8 *)malloc(kVirtualRAMSize * sizeof(u8));
//    memset(alis.ram, 0, kVirtualRAMSize * sizeof(u8));
    
    // init virtual registers
    alis.varD6 = alis.varD7 = 0;
    alis.bssChunk1 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    alis.bssChunk2 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    alis.bssChunk3 = (u8 *)malloc(kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk1, 0, kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk2, 0, kBSSChunkLen * sizeof(u8));
    memset(alis.bssChunk3, 0, kBSSChunkLen * sizeof(u8));
    
    // init virtual accumulator
    alis.acc_org = (s16 *)malloc(kVirtualRAMSize);
    alis.acc = alis.acc_org + kVirtualRAMSize;
    
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
    free(alis.bssChunk1);
    free(alis.bssChunk2);
    free(alis.bssChunk3);
    
//    free(alis.ram);
    free(alis.acc_org);
}

u8 alis_main() {
    u8 ret = 0;
    sAlisScript * main = script_load(alis.platform.main);
    if(main) {
        main->org = 0x2d290; // TODO: for debug
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
    alis.scriptID = script->ID;
    alis.scripts[alis.scriptID] = script;
    
    // set pc to script origin in virtual ram
    alis.pc = alis.pc_org = script->data + script->headerlen; // TODO: determine org
    alis.running = 1;
}


void alis_error(u8 errnum, ...) {
    sAlisError err = errors[errnum];
    debug(EDebugError, err.descfmt, errnum);
    exit(-1);
}


void alis_debug() {
    printf("ALIS: %s (0x%02x)\n", alis.scripts[alis.scriptID]->name, alis.scriptID);
    printf("R6=0x%04x\n", alis.varD6);
    printf("R7=0x%04x\n", alis.varD7);
    printf("PC  OFFSET=0x%04x (byte=0x%02x) (word=0x%04x)\n",
           (u16)(alis.pc - alis.pc_org),
           (u8)(*alis.pc),
           (u16)(*alis.pc));
    printf("ACC OFFSET=0x%04x (byte=0x%02x) (word=0x%04x)\n",
           (u16)(alis.acc - alis.acc_org),
           (u8)(*alis.acc),
           (u16)(*alis.acc));
    printf("BSS1=%s\n", alis.bssChunk1);
    printf("BSS2=%s\n", alis.bssChunk2);
    printf("BSS3=%s\n", alis.bssChunk3);
    // printf("RAM OFFSET=0x%04x\n", (u16)(alis.acc - alis.acc_org));
}


void alis_debug_ram() {
    u8 width = 16;
    printf("ALIS VRAM:\n");
    
    printf("       ");
    for(u8 j = 0; j < width; j++) {
        printf("  %x", j);
    }
    printf("\n");
    
    for(u32 i = 0; i < kVirtualRAMSize; i += width) {
        printf("0x%04x: ", i);
        for(u8 j = 0; j < width; j++) {
            printf("%02x ", alis.scripts[alis.scriptID]->ram[i + j]);
        }
        printf("\n");
    }
}


void alis_debug_addr(u16 addr) {
    u8 width = 16;
    printf("ALIS VRAM:\n");
    
    printf("       ");
    for(u8 j = 0; j < width; j++) {
        printf("  %x", j);
    }
    printf("\n");

    printf("0x%04x: ", addr);
    for(u32 j = addr; j < addr + width; j++) {
        printf("%02x ", alis.scripts[alis.scriptID]->ram[j]);
    }
}


void alis_debug_acc() {
}


sAlisError errors[] = {
    { ALIS_ERR_FOPEN,   "fopen", "Failed to open file %s\n" },
    { ALIS_ERR_FWRITE,  "fwrite", "Failed to write to file %s\n" },
    { ALIS_ERR_FCREATE, "fcreate", "" },
    { ALIS_ERR_FDELETE, "fdelete", "" },
    { ALIS_ERR_CDEFSC,  "cdefsc", "" },
    { ALIS_ERR_FREAD,   "fread", "" },
    { ALIS_ERR_FCLOSE,  "fclose", "" },
    { ALIS_ERR_FSEEK,   "fseek", "" }
};
