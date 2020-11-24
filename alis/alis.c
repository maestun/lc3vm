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


// =============================================================================
// MARK: - Private
// =============================================================================
alisRet readexec(sAlisOpcode * table, char * name, u8 identation) {
    if(alis.script->pc - alis.script->pc_org == kVirtualRAMSize) {
        // pc overflow !
        debug(EDebugFatal, "PC OVERFLOW !");
    }
    else {
        // fetch code
        u8 code = *(alis.script->pc++);
        sAlisOpcode opcode = table[code];
        debug(EDebugVerbose, " %s", opcode.name);
        return opcode.fptr();
    }
}

alisRet readexec_opcode() {
    debug(EDebugVerbose, "\n0x%06x:", script_pc(alis.script));
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
// MARK: - VM API
// =============================================================================
void alis_init(sPlatform platform) {
    
    // init virtual ram and stack offset
    alis.vram = vram_init();
    
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
    
    alis.script = script_load(alis.platform.main);
    alis.scriptID = alis.script->ID;
    alis.scripts[alis.scriptID] = alis.script;
    
    // system stuff
    alis.pixelbuf.w = alis.platform.width;
    alis.pixelbuf.h = alis.platform.height;
    alis.pixelbuf.data = (u8 *)malloc(alis.pixelbuf.w * alis.pixelbuf.h);
}

void alis_deinit() {
    // free scripts
    for(int i = 0; i < kMaxScripts; i++) {
        script_unload(alis.script);
    }
    free(alis.bssChunk1);
    free(alis.bssChunk2);
    free(alis.bssChunk3);
    
    vram_deinit(alis.vram);
    free(alis.acc_org);
}


//sAlisScript * alis_load_script(const char * name, const u32 org) {
//    sAlisScript * script = script_load(name, org);
//    if(script) {
//        alis.scripts[script->ID] = script;
//        alis.nextScriptID = script->ID;
//    }
//    else {
//        debug(EDebugFatal,
//              "Failed to load script '%s'\n",
//              alis.platform.main);
//    }
//    return script;
//}

u8 alis_run() {
    u8 ret = 0;
    alis.running = 1;
    while(alis.running) {
        alis.script->running = 1;
        while (alis.running && alis.script->running) {
            alis.running = sys_poll_event();
            readexec_opcode();
            sys_render(alis.pixelbuf);
        }

        u8 next_id = alis.scriptID;
        u8 current_id = alis.script->ID;
        alis.script = alis.scripts[next_id];
        alis.scriptID = current_id;
        script_debug(alis.script);
    }
    return ret;
}


void alis_error(u8 errnum, ...) {
    sAlisError err = errors[errnum];
    debug(EDebugError, err.descfmt, errnum);
    exit(-1);
}


void alis_debug() {
    printf("ALIS: %s (0x%02x)\n", alis.scripts[alis.scriptID]->name, alis.scriptID);
    printf("R6  0x%04x\n", alis.varD6);
    printf("R7  0x%04x\n", alis.varD7);
    printf("PC  OFFSET=0x%04x (byte=0x%02x) (word=0x%04x)\n",
           (u16)(alis.script->pc - alis.script->pc_org),
           (u8)(*alis.script->pc),
           (u16)(*alis.script->pc));
    printf("ACC OFFSET=0x%04x (byte=0x%02x) (word=0x%04x)\n",
           (u16)(alis.acc - alis.acc_org),
           (u8)(*alis.acc),
           (u16)(*alis.acc));
    printf("BSS1=%s\n", alis.bssChunk1);
    printf("BSS2=%s\n", alis.bssChunk2);
    printf("BSS3=%s\n", alis.bssChunk3);
    // printf("RAM OFFSET=0x%04x\n", (u16)(alis.acc - alis.acc_org));
}

