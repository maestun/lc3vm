//
//  storenames.c
//  aodec
//
//  Created by zlot on 05/02/2020.
//  Copyright © 2020 zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"

static void cnul() {
    // log_debug("STUBBED");
}
static void slocb() {
    // log_debug("STUBBED");
}
static void slocw() {
    // log_debug("STUBBED");
}
static void slocp() {
    // log_debug("STUBBED");
}
static void sloctp() {
    // log_debug("STUBBED");
}
static void sloctc() {
    // log_debug("STUBBED");
}
static void slocti() {
    // log_debug("STUBBED");
}
static void sdirb() {
//    **************************************************************
//    * - Reads a byte offset from script                          *
//    * - Stores D7.b at (A6 + offset)                             *
//    **************************************************************
//    undefined STORENAME_SDIRB_0x9()
//undefined         D0b:1          <RETURN>
//    STORENAME_SDIRB_0x9
//00017f80 42 40           clr.w      D0w
//00017f82 10 1b           move.b     (A3)+,D0b
//00017f84 1d 87 00 00     move.b     D7b,(0x0,A6,D0w*0x1)
//00017f88 4e 75           rts
    u8 offset = read8();
    *(u8 *)(alis.scripts[alis.scriptID]->stack + offset) = (u8)alis.varD7;
}
static void sdirw() {
   
//    **************************************************************
//    * - Reads a byte offset from script                          *
//    * - Stores D7.w at (A6 + offset)                             *
//    **************************************************************
//    undefined STORENAME_SDIRW_0xa()
//undefined         D0b:1          <RETURN>
//    STORENAME_SDIRW_0xa
//00017f8a 42 40           clr.w      D0w
//00017f8c 10 1b           move.b     (A3)+,D0b
//00017f8e 3d 87 00 00     move.w     D7w,(0x0,A6,D0w*0x1)
    u8 offset = read8();
    *(u16 *)(alis.scripts[alis.scriptID]->stack + offset) = (u16)alis.varD7;
}
static void sdirp() {
    // log_debug("STUBBED");
}
static void sdirtp() {
    // log_debug("STUBBED");
}
static void sdirtc() {
    // log_debug("STUBBED");
}
static void sdirti() {
    // log_debug("STUBBED");
}
static void smainb() {
    // log_debug("STUBBED");
}
static void smainw() {
    // log_debug("STUBBED");
}
static void smainp() {
    // log_debug("STUBBED");
}
static void smaintp() {
    // log_debug("STUBBED");
}
static void smaintc() {
    // log_debug("STUBBED");
}
static void smainti() {
    // log_debug("STUBBED");
}
static void shimb() {
    // log_debug("STUBBED");
}
static void shimw() {
    // log_debug("STUBBED");
}
static void shimp() {
    // log_debug("STUBBED");
}
static void shimtp() {
    // log_debug("STUBBED");
}
static void shimtc() {
    // log_debug("STUBBED");
}
static void shimti() {
    // log_debug("STUBBED");
}
static void spile() {
    // log_debug("STUBBED");
}
static void seval() {
//    00015d2c 39 07           move.w     D7w,-(A4)
//    00015d2e 61 00 fd 86     bsr.w      FUN_READEXEC_OPNAME                              undefined FUN_READEXEC_OPNAME()
//                         -- Flow Override: CALL_RETURN (CALL_TERMINATOR)
//    00015d32 41 f9 00        lea        (JTAB_STORENAME).l,A0
//             01 0f 92
//    00015d38 10 1b           move.b     (A3)+,D0b
//    00015d3a 48 80           ext.w      D0w
//    00015d3c 30 30 00 00     move.w     (0x0,A0,D0w*offset JTAB_STORENAME),D0w
//    00015d40 4e f0 00 00     jmp        (0x0,A0,D0w*0x1)

    // TODO: push D7 into virtual stack
    alis.scripts[alis.scriptID]->stack;
    
    // opername_oeval_0x1c
    // oeval();
    
}
static void ofin() {
    // log_debug("STUBBED");
}

// ============================================================================
#pragma mark - Storenames pointer table
// In the disasm, the table JTAB_STOREADD_NAMES is at address $10f92 -> $10fce.
// So it contains 0x3c / 60 bytes, or 30 words, it matches the storeadd count.
// So the routine FUN_READEXEC_OPERNAME() gets a BYTE code from script pc,
//  then retrieves a WORD offset at (JTAB_OPERNAMES[code]), then
//  jumps at the address (JTAB_OPERAMES + offset).
// ============================================================================
sAlisOpcode storenames[] = {
    DECL_OPCODE(0x00, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x02, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x04, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x06, slocb, "TODO add desc"),
    {},
    DECL_OPCODE(0x08, slocw, "TODO add desc"),
    {},
    DECL_OPCODE(0x0a, slocp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0c, sloctp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0e, sloctc, "TODO add desc"),
    {},
    DECL_OPCODE(0x10, slocti, "TODO add desc"),
    {},
    DECL_OPCODE(0x12, sdirb, "TODO add desc"),
    {},
    DECL_OPCODE(0x14, sdirw, "TODO add desc"),
    {},
    DECL_OPCODE(0x16, sdirp, "TODO add desc"),
    {},
    DECL_OPCODE(0x18, sdirtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x1a, sdirtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x1c, sdirti, "TODO add desc"),
    {},
    DECL_OPCODE(0x1e, smainb, "TODO add desc"),
    {},
    DECL_OPCODE(0x20, smainw, "TODO add desc"),
    {},
    DECL_OPCODE(0x22, smainp, "TODO add desc"),
    {},
    DECL_OPCODE(0x24, smaintp, "TODO add desc"),
    {},
    DECL_OPCODE(0x26, smaintc, "TODO add desc"),
    {},
    DECL_OPCODE(0x28, smainti, "TODO add desc"),
    {},
    DECL_OPCODE(0x2a, shimb, "TODO add desc"),
    {},
    DECL_OPCODE(0x2c, shimw, "TODO add desc"),
    {},
    DECL_OPCODE(0x2e, shimp, "TODO add desc"),
    {},
    DECL_OPCODE(0x30, shimtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x32, shimtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x34, shimti, "TODO add desc"),
    {},
    DECL_OPCODE(0x36, spile, "TODO add desc"),
    {},
    DECL_OPCODE(0x38, seval, "TODO add desc"),
    {},
    DECL_OPCODE(0x3a, ofin, "TODO add desc"),
};
