//
//  escnames.c
//  aodec
//
//  Created by zlot on 05/02/2020.
//  Copyright © 2020 zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"

// ============================================================================
#pragma mark - Escnames routines
// ============================================================================
static void cnul() {
}
void consound() {
    // log_debug("STUBBED");
}
void coffsound() {
    // log_debug("STUBBED");
}
void conmusic() {
    // log_debug("STUBBED");
}
void coffmusic() {
    // log_debug("STUBBED");
}
void cdelfilm() {
    // log_debug("STUBBED");
}
void copenfilm() {
    // log_debug("STUBBED");
}


// ============================================================================
#pragma mark - Escnames pointer table
// ============================================================================
sAlisOpcode escnames[] = {
    DECL_OPCODE(0x00, cnul,         "null"),
    DECL_OPCODE(0x01, consound,     "TODO: add desc"),
    DECL_OPCODE(0x02, coffsound,    "TODO: add desc"),
    DECL_OPCODE(0x03, conmusic,     "TODO: add desc"),
    DECL_OPCODE(0x04, coffmusic,    "TODO: add desc"),
    DECL_OPCODE(0x05, cdelfilm,     "TODO: add desc"),
    DECL_OPCODE(0x06, copenfilm,    "TODO: add desc")
};
