//
//  addnames.c
//  aodec
//
//  Created by zlot on 05/02/2020.
//  Copyright © 2020 zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"

// ============================================================================
#pragma mark - Addnames routines
// ============================================================================
static void cnul() {
}
static void alocb() {
//    ADDNAME_ALOCB_0x3
//00018194 10 1b           move.b     (A3)+,D0b
//00018196 e1 40           asl.w      #0x8,D0w
//00018198 10 1b           move.b     (A3)+,D0b
//0001819a df 36 00 00     add.b      D7b,(0x0,A6,D0w*0x1)
//0001819e 4e 75           rts
    u16 offset = read16();
    add8(offset, (u8)alis.varD7);
}
static void alocw() {
//    ADDNAME_ALOCW_0x4
//000181a0 10 1b           move.b     (A3)+,D0b
//000181a2 e1 40           asl.w      #0x8,D0w
//000181a4 10 1b           move.b     (A3)+,D0b
//000181a6 df 76 00 00     add.w      D7w,(0x0,A6,D0w*0x1)
//000181aa 4e 75           rts
    u16 offset = read16();
    add16(offset, alis.varD7);
}
static void alocp() {
    // log_debug("STUBBED");
}
static void aloctp() {
    // log_debug("STUBBED");
}
static void aloctc() {
    // log_debug("STUBBED");
}
static void alocti() {
    // log_debug("STUBBED");
}
static void adirb() {
//    ADDNAME_ADIRB_0x9
//00018214 42 40           clr.w      D0w
//00018216 10 1b           move.b     (A3)+,D0b
//00018218 df 36 00 00     add.b      D7b,(0x0,A6,D0w*0x1)
//0001821c 4e 75           rts
    u8 offset = read8();
    *(u8 *)(alis.scripts[alis.scriptID]->vram_org + offset) += (u8)alis.varD7;
}
static void adirw() {
//    ADDNAME_ADIRW_0xa
//0001821e 42 40           clr.w      D0w
//00018220 10 1b           move.b     (A3)+,D0b
//00018222 df 76 00 00     add.w      D7w,(0x0,A6,D0w*0x1)
//00018226 4e 75           rts
    u8 offset = read8();
    *(u16 *)(alis.scripts[alis.scriptID]->vram_org + offset) += (u16)alis.varD7;
}
static void adirp() {
    // log_debug("STUBBED");
}
static void adirtp() {
    // log_debug("STUBBED");
}
static void adirtc() {
    // log_debug("STUBBED");
}
static void adirti() {
    // log_debug("STUBBED");
}
static void amainb() {
    // log_debug("STUBBED");
}
static void amainw() {
    // log_debug("STUBBED");
}
static void amainp() {
    // log_debug("STUBBED");
}
static void amaintp() {
    // log_debug("STUBBED");
}
static void amaintc() {
    // log_debug("STUBBED");
}
static void amainti() {
    // log_debug("STUBBED");
}
static void ahimb() {
    // log_debug("STUBBED");
}
static void ahimw() {
    // log_debug("STUBBED");
}
static void ahimp() {
    // log_debug("STUBBED");
}
static void ahimtp() {
    // log_debug("STUBBED");
}
static void ahimtc() {
    // log_debug("STUBBED");
}
static void ahimti() {
    // log_debug("STUBBED");
}
static void spile() {
    // log_debug("STUBBED");
}
static void aeval() {
    // log_debug("STUBBED");
}
static void ofin() {
    // log_debug("STUBBED");
}


// ============================================================================
#pragma mark - Addnames pointer table
// ============================================================================
sAlisOpcode addnames[] = {
    DECL_OPCODE(0x00, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x02, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x04, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x06, alocb, "TODO add desc"),
    {},
    DECL_OPCODE(0x08, alocw, "TODO add desc"),
    {},
    DECL_OPCODE(0x0a, alocp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0c, aloctp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0e, aloctc, "TODO add desc"),
    {},
    DECL_OPCODE(0x10, alocti, "TODO add desc"),
    {},
    DECL_OPCODE(0x12, adirb, "TODO add desc"),
    {},
    DECL_OPCODE(0x14, adirw, "TODO add desc"),
    {},
    DECL_OPCODE(0x16, adirp, "TODO add desc"),
    {},
    DECL_OPCODE(0x18, adirtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x1a, adirtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x1c, adirti, "TODO add desc"),
    {},
    DECL_OPCODE(0x1e, amainb, "TODO add desc"),
    {},
    DECL_OPCODE(0x20, amainw, "TODO add desc"),
    {},
    DECL_OPCODE(0x22, amainp, "TODO add desc"),
    {},
    DECL_OPCODE(0x24, amaintp, "TODO add desc"),
    {},
    DECL_OPCODE(0x26, amaintc, "TODO add desc"),
    {},
    DECL_OPCODE(0x28, amainti, "TODO add desc"),
    {},
    DECL_OPCODE(0x2a, ahimb, "TODO add desc"),
    {},
    DECL_OPCODE(0x2c, ahimw, "TODO add desc"),
    {},
    DECL_OPCODE(0x2e, ahimp, "TODO add desc"),
    {},
    DECL_OPCODE(0x30, ahimtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x32, ahimtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x34, ahimti, "TODO add desc"),
    {},
    DECL_OPCODE(0x36, spile, "TODO add desc"),
    {},
    DECL_OPCODE(0x38, aeval, "TODO add desc"),
    {},
    DECL_OPCODE(0x3a, ofin, "TODO add desc")
};
