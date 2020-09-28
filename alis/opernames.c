//
//  opernames.c
//  aodec
//
//  Created by zlot on 05/02/2020.
//  Copyright © 2020 zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"

static int oeval_end = 0;

// =============================================================================
#pragma mark - TODO: opernames
// =============================================================================
void oimmb() {
    // reads a byte, extends into D7
    u8 b = read8();
    u16 w = extend_w(b);
    alis.varD7 = w;
    debug(EDebugVerbose, "\tvarD7 <- 0x%04x\n", alis.varD7);
}
void oimmw() {
    // reads a word into D7
    alis.varD7 = read16();
    debug(EDebugVerbose, "\tvarD7 <- 0x%04x\n", alis.varD7);
}
void oimmp() {
    // reads null-terminated data into bssChunk1
    readToZero(alis.bssChunk1);
}
void olocb() {
//    OPERNAME_OLOCB_0x3
//000175b0 10 1b           move.b     (A3)+,D0b
//000175b2 e1 40           asl.w      #0x8,D0w
//000175b4 10 1b           move.b     (A3)+,D0b
//000175b6 1e 36 00 00     move.b     (0x0,A6,D0w*0x1),D7b
//000175ba 48 87           ext.w      D7w
//000175bc 4e 75           rts
    u16 offset = read16();
    u8 b = (u8)*(alis.scripts[alis.scriptID]->stack + offset);
    alis.varD7 = extend_w(b);
}
void olocw() {
//    OPERNAME_OLOCW_0x4
//000175be 10 1b           move.b     (A3)+,D0b
//000175c0 e1 40           asl.w      #0x8,D0w
//000175c2 10 1b           move.b     (A3)+,D0b
//000175c4 3e 36 00 00     move.w     (0x0,A6,D0w*0x1),D7w
//000175c8 4e 75           rts
    u16 offset = read16();
    u16 w = (u16)*(alis.scripts[alis.scriptID]->stack + offset);
    alis.varD7 = w;
}
void olocp() {
//    OPERNAME_OLOCP_0x5
//000175ca 10 1b           move.b     (A3)+,D0b
//000175cc e1 40           asl.w      #0x8,D0w
//000175ce 10 1b           move.b     (A3)+,D0b
//000175d0 43 f6 00 00     lea        (0x0,A6,D0w*0x1),A1
//000175d4 20 79 00        movea.l    (ADDR_BSS_256_CHUNK_1).l,A0
//01 95 e2
//    LAB_000175da                                    XREF[1]:     000175dc(j)
//000175da 10 d9           move.b     (A1)+,(A0)+
//000175dc 66 00 ff fc     bne.w      LAB_000175da
//000175e0 4e 75           rts
    u16 offset = read16();
    u8 * src_ptr = (alis.scripts[alis.scriptID]->stack + offset);
    u8 * dst_ptr = alis.bssChunk1;
    while(*src_ptr) {
        *dst_ptr++ = *src_ptr++;
    }
}
void oloctp() {
    // log_debug("STUBBED");
}
void oloctc() {
//    OPERNAME_OLOCTC_0x7
//000175e2 10 1b           move.b     (A3)+,D0b
//000175e4 e1 40           asl.w      #0x8,D0w
//000175e6 10 1b           move.b     (A3)+,D0b
//000175e8 61 00 02 2e     bsr.w      FUN_00017818                                     undefined FUN_00017818()
//000175ec 1e 36 00 00     move.b     (0x0,A6,D0w*0x1),D7b
//000175f0 48 87           ext.w      D7w
//000175f2 4e 75           rts
    u16 offset = read16();

}
void olocti() {
    // log_debug("STUBBED");
}
void odirb() {
    // log_debug("STUBBED");
}
void odirw() {
    // log_debug("STUBBED");
}
void odirp() {
    // log_debug("STUBBED");
}
void odirtp() {
    // log_debug("STUBBED");
}
void odirtc() {
    // log_debug("STUBBED");
}
void odirti() {
    // log_debug("STUBBED");
}
void omainb() {
    // log_debug("STUBBED");
}
void omainw() {
    // log_debug("STUBBED");
}
void omainp() {
    // log_debug("STUBBED");
}
void omaintp() {
    // log_debug("STUBBED");
}
void omaintc() {
    // log_debug("STUBBED");
}
void omainti() {
    // log_debug("STUBBED");
}
void ohimb() {
    // log_debug("STUBBED");
}
void ohimw() {
    // log_debug("STUBBED");
}
void ohimp() {
    // log_debug("STUBBED");
}
void ohimtp() {
    // log_debug("STUBBED");
}
void ohimtc() {
    // log_debug("STUBBED");
}
void ohimti() {
    // log_debug("STUBBED");
}
void opile() {
    // log_debug("STUBBED");
}

void oeval() {
    // exec opernames until ofin() is called
    oeval_end = 0;
    while(!oeval_end) {
        readexec_opername();
    }
}
void ofin() {
    oeval_end = 1;
}
void opushacc() {
    // log_debug("STUBBED");
}
void oand() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 &= alis.varD6;
}
void oor() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 |= alis.varD6;
}
void oxor() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 ^= alis.varD6;
}
void oeqv() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 ^= alis.varD6;
    alis.varD7 = ~alis.varD7;
}
void oegal() {
    alis.varD7 = (alis.varD6 == alis.varD7) ? 0xff : 0x0;
}
void odiff() {
    alis.varD7 = (alis.varD6 != alis.varD7) ? 0xff : 0x0;
}
void oinfeg() {
    alis.varD7 = (alis.varD6 <= alis.varD7) ? 0xff : 0x0;
}
void osupeg() {
    alis.varD7 = (alis.varD6 >= alis.varD7) ? 0xff : 0x0;
}
void oinf() {
    alis.varD7 = (alis.varD6 < alis.varD7) ? 0xff : 0x0;
}
void osup() {
    alis.varD7 = (alis.varD6 > alis.varD7) ? 0xff : 0x0;
}
void oadd() {
//00017932 61 00 fc 38     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017936 de 46           add.w      D6w,D7w
//00017938 4e 75           rts
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 += alis.varD6;
}
void osub() {
//0001793a 61 00 fc 30     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//0001793e 9c 47           sub.w      D7w,D6w
//00017940 3e 06           move.w     D6w,D7w
//00017942 4e 75           rts
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD6 -= alis.varD7;
    alis.varD7 = alis.varD6;
}
void omod() {
//00017944 61 00 fc 26     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017948 48 c6           ext.l      D6
//0001794a 8d c7           divs.w     D7w,D6
//0001794c 2e 06           move.l     D6,D7
//0001794e 48 47           swap       D7
//00017950 4e 75           rts
    debug(EDebugWarning, "%s: TODO", __FUNCTION__);
}
void odiv() {
//00017952 61 00 fc 18     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017956 48 c6           ext.l      D6
//00017958 8d c7           divs.w     D7w,D6
//0001795a 3e 06           move.w     D6w,D7w
//0001795c 4e 75           rts
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD6 /= alis.varD7;
    alis.varD7 = alis.varD6;
}
void omul() {
//0001795e 61 00 fc 0c     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017962 cf c6           muls.w     D6w,D7
//00017964 4e 75           rts
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 *= alis.varD6;
}
void oneg() {
    alis.varD7 = -alis.varD7;
}
void oabs() {
    alis.varD7 = (alis.varD7 < 0) ? -alis.varD7 : alis.varD7;
}
void ornd() {
    // log_debug("STUBBED");
}
void osgn() {
    // log_debug("STUBBED");
}
void onot() {
    alis.varD7 = ~alis.varD7;
}
void oinkey() {
    // log_debug("STUBBED");
}
void okeyon() {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
void ojoy() {
    // log_debug("STUBBED");
}
void oprnd() {
    // log_debug("STUBBED");
}
void oscan() {
    // log_debug("STUBBED");
}
void oshiftkey() {
    // log_debug("STUBBED");
}
void ofree() {
    // log_debug("STUBBED");
}
void omodel() {
    // log_debug("STUBBED");
}
void ogetkey() {
    // log_debug("STUBBED");
}
void oleft() {
    // log_debug("STUBBED");
}
void oright() {
    // log_debug("STUBBED");
}
void omid() {
    // log_debug("STUBBED");
}
void olen() {
    // log_debug("STUBBED");
}
void oasc() {
    // log_debug("STUBBED");
}
void ostr() {
    // log_debug("STUBBED");
}
void osadd() {
    // log_debug("STUBBED");
}
void osegal() {
    // log_debug("STUBBED");
}
void osdiff() {
    // log_debug("STUBBED");
}
void osinfeg() {
    // log_debug("STUBBED");
}
void ossupeg() {
    // log_debug("STUBBED");
}
void osinf() {
    // log_debug("STUBBED");
}
void ossup() {
    // log_debug("STUBBED");
}
void ospushacc() {
    // log_debug("STUBBED");
}
void ospile() {
    // log_debug("STUBBED");
}
void oval() {
    // log_debug("STUBBED");
}
void oexistf() {
    // log_debug("STUBBED");
}
void ochr() {
    // log_debug("STUBBED");
}
void ochange() {
    // log_debug("STUBBED");
}
void ocountry() {
    // log_debug("STUBBED");
}
void omip() {
    alis.varD7 = 0x64;
}
void ojoykey() {
    // log_debug("STUBBED");
}
void oconfig() {
    alis.varD7 = 0;
}
static void cnul() {
}

// =============================================================================
#pragma mark - Opername Pointer table (85 values)
// In the disasm, the table JTAB_OPERNAMES is at address $10ee8 -> $10f92.
// So it contains 0xaa / 170 bytes, or 85 words, it matches the opernames count.
// So the routine FUN_READEXEC_OPERNAME() gets a BYTE code from script pc,
//  then retrieves a WORD offset at (JTAB_OPERNAMES[code]), then
//  jumps at the address (JTAB_OPERAMES + offset).
// =============================================================================
sAlisOpcode opernames[] = {
    DECL_OPCODE(0x00, oimmb, "TODO add desc"),
    {},
    DECL_OPCODE(0x01, oimmw, "TODO add desc"),
    {},
    DECL_OPCODE(0x02, oimmp, "TODO add desc"),
    {},
    DECL_OPCODE(0x03, olocb, "TODO add desc"),
    {},
    DECL_OPCODE(0x04, olocw, "TODO add desc"),
    {},
    DECL_OPCODE(0x05, olocp, "TODO add desc"),
    {},
    DECL_OPCODE(0x06, oloctp, "TODO add desc"),
    {},
    DECL_OPCODE(0x07, oloctc, "TODO add desc"),
    {},
    DECL_OPCODE(0x08, olocti, "TODO add desc"),
    {},
    DECL_OPCODE(0x09, odirb, "TODO add desc"),
    {},
    DECL_OPCODE(0x0A, odirw, "TODO add desc"),
    {},
    DECL_OPCODE(0x0B, odirp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0C, odirtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x0D, odirtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x0E, odirti, "TODO add desc"),
    {},
    DECL_OPCODE(0x0F, omainb, "TODO add desc"),
    {},
    DECL_OPCODE(0x10, omainw, "TODO add desc"),
    {},
    DECL_OPCODE(0x11, omainp, "TODO add desc"),
    {},
    DECL_OPCODE(0x12, omaintp, "TODO add desc"),
    {},
    DECL_OPCODE(0x13, omaintc, "TODO add desc"),
    {},
    DECL_OPCODE(0x14, omainti, "TODO add desc"),
    {},
    DECL_OPCODE(0x15, ohimb, "TODO add desc"),
    {},
    DECL_OPCODE(0x16, ohimw, "TODO add desc"),
    {},
    DECL_OPCODE(0x17, ohimp, "TODO add desc"),
    {},
    DECL_OPCODE(0x18, ohimtp, "TODO add desc"),
    {},
    DECL_OPCODE(0x19, ohimtc, "TODO add desc"),
    {},
    DECL_OPCODE(0x1A, ohimti, "TODO add desc"),
    {},
    DECL_OPCODE(0x1B, opile, "TODO add desc"),
    {},
    DECL_OPCODE(0x1C, oeval, "TODO add desc"),
    {},
    DECL_OPCODE(0x1D, ofin, "TODO add desc"),
    {},
    DECL_OPCODE(0x1E, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x1F, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x20, opushacc, "TODO add desc"),
    {},
    DECL_OPCODE(0x21, oand, "TODO add desc"),
    {},
    DECL_OPCODE(0x22, oor, "TODO add desc"),
    {},
    DECL_OPCODE(0x23, oxor, "TODO add desc"),
    {},
    DECL_OPCODE(0x24, oeqv, "TODO add desc"),
    {},
    DECL_OPCODE(0x25, oegal, "TODO add desc"),
    {},
    DECL_OPCODE(0x26, odiff, "TODO add desc"),
    {},
    DECL_OPCODE(0x27, oinfeg, "TODO add desc"),
    {},
    DECL_OPCODE(0x28, osupeg, "TODO add desc"),
    {},
    DECL_OPCODE(0x29, oinf, "TODO add desc"),
    {},
    DECL_OPCODE(0x2A, osup, "TODO add desc"),
    {},
    DECL_OPCODE(0x2B, oadd, "TODO add desc"),
    {},
    DECL_OPCODE(0x2C, osub, "TODO add desc"),
    {},
    DECL_OPCODE(0x2D, omod, "TODO add desc"),
    {},
    DECL_OPCODE(0x2E, odiv, "TODO add desc"),
    {},
    DECL_OPCODE(0x2F, omul, "TODO add desc"),
    {},
    DECL_OPCODE(0x30, oneg, "TODO add desc"),
    {},
    DECL_OPCODE(0x31, oabs, "TODO add desc"),
    {},
    DECL_OPCODE(0x32, ornd, "TODO add desc"),
    {},
    DECL_OPCODE(0x33, osgn, "TODO add desc"),
    {},
    DECL_OPCODE(0x34, onot, "TODO add desc"),
    {},
    DECL_OPCODE(0x35, oinkey, "TODO add desc"),
    {},
    DECL_OPCODE(0x36, okeyon, "TODO add desc"),
    {},
    DECL_OPCODE(0x37, ojoy, "TODO add desc"),
    {},
    DECL_OPCODE(0x38, oprnd, "TODO add desc"),
    {},
    DECL_OPCODE(0x39, oscan, "TODO add desc"),
    {},
    DECL_OPCODE(0x3A, oshiftkey, "TODO add desc"),
    {},
    DECL_OPCODE(0x3B, ofree, "TODO add desc"),
    {},
    DECL_OPCODE(0x3C, omodel, "TODO add desc"),
    {},
    DECL_OPCODE(0x3D, ogetkey, "TODO add desc"),
    {},
    DECL_OPCODE(0x3E, oleft, "TODO add desc"),
    {},
    DECL_OPCODE(0x3F, oright, "TODO add desc"),
    {},
    DECL_OPCODE(0x40, omid, "TODO add desc"),
    {},
    DECL_OPCODE(0x41, olen, "TODO add desc"),
    {},
    DECL_OPCODE(0x42, oasc, "TODO add desc"),
    {},
    DECL_OPCODE(0x43, ostr, "TODO add desc"),
    {},
    DECL_OPCODE(0x44, osadd, "TODO add desc"),
    {},
    DECL_OPCODE(0x45, osegal, "TODO add desc"),
    {},
    DECL_OPCODE(0x46, osdiff, "TODO add desc"),
    {},
    DECL_OPCODE(0x47, osinfeg, "TODO add desc"),
    {},
    DECL_OPCODE(0x48, ossupeg, "TODO add desc"),
    {},
    DECL_OPCODE(0x49, osinf, "TODO add desc"),
    {},
    DECL_OPCODE(0x4A, ossup, "TODO add desc"),
    {},
    DECL_OPCODE(0x4B, ospushacc, "TODO add desc"),
    {},
    DECL_OPCODE(0x4C, ospile, "TODO add desc"),
    {},
    DECL_OPCODE(0x4D, oval, "TODO add desc"),
    {},
    DECL_OPCODE(0x4E, oexistf, "TODO add desc"),
    {},
    DECL_OPCODE(0x4F, ochr, "TODO add desc"),
    {},
    DECL_OPCODE(0x50, ochange, "TODO add desc"),
    {},
    DECL_OPCODE(0x51, ocountry, "TODO add desc"),
    {},
    DECL_OPCODE(0x52, omip, "TODO add desc"),
    {},
    DECL_OPCODE(0x53, ojoykey, "TODO add desc"),
    {},
    DECL_OPCODE(0x54, oconfig, "TODO add desc"),
    {}
};
