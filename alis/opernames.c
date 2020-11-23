//
//  opernames.c
//  aodec
//
//  Created by zlot on 05/02/2020.
//  Copyright © 2020 zlot. All rights reserved.
//

#include "alis.h"
#include "alis_private.h"
#include "utils.h"

u16 loctp_common(u16 offset) {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    return offset;
}

u16 locti_common(u16 offset) {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    return offset;
}

u16 loctc_common(u16 offset) {
    u8 d1b = alis.vram[offset - 1];
    u16 d1w = extend_w(d1b);
    u16 a0 = offset - 2;
    offset += alis.varD7;
    while(d1w--) {

        // TODO:
        
    }
    debug(EDebugWarning, "\n%s INCOMPLETE\n", __FUNCTION__);
    return offset;
}


// =============================================================================
#pragma mark - TODO: opernames
// =============================================================================

void oimmb() {
    // reads a byte, extends into D7
    u8 b = script_read8();
    u16 w = extend_w(b);
    alis.varD7 = w;
    // debug(EDebugVerbose, " 0x%04x", (u16)alis.varD7);
}

void oimmw() {
    // reads a word into D7
    alis.varD7 = script_read16();
    //debug(EDebugVerbose, " 0x%04x", (u16)alis.varD7);
}

void oimmp() {
    // reads null-terminated data into bssChunk1
    script_read_until_zero(alis.bssChunk1);
}

// read word offset, copy byte from ram[offset] into r7
void olocb() {
//    OPERNAME_OLOCB_0x3
//000175b0 10 1b           move.b     (A3)+,D0b
//000175b2 e1 40           asl.w      #0x8,D0w
//000175b4 10 1b           move.b     (A3)+,D0b
//000175b6 1e 36 00 00     move.b     (0x0,A6,D0w*0x1),D7b
//000175ba 48 87           ext.w      D7w
//000175bc 4e 75           rts
    u16 offset = script_read16();
    u8 b = *(alis.vram + offset);
    alis.varD7 = extend_w(b);
}

// read word offset, copy word from ram[offset] into r7
void olocw() {
//    OPERNAME_OLOCW_0x4
//000175be 10 1b           move.b     (A3)+,D0b
//000175c0 e1 40           asl.w      #0x8,D0w
//000175c2 10 1b           move.b     (A3)+,D0b
//000175c4 3e 36 00 00     move.w     (0x0,A6,D0w*0x1),D7w
//000175c8 4e 75           rts
    u16 offset = script_read16();
    u16 w = *(u16 *)(alis.vram + offset);
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
    u16 offset = script_read16();
    u8 * src_ptr = (alis.vram + offset);
    u8 * dst_ptr = alis.bssChunk1;
    while(*src_ptr) {
        *dst_ptr++ = *src_ptr++;
    }
}
void oloctp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oloctc() {
//    OPERNAME_OLOCTC_0x7
//000175e2 10 1b           move.b     (A3)+,D0b
//000175e4 e1 40           asl.w      #0x8,D0w
//000175e6 10 1b           move.b     (A3)+,D0b
//000175e8 61 00 02 2e     bsr.w      FUN_LOCTC_COMMON                                     undefined FUN_00017818()
//000175ec 1e 36 00 00     move.b     (0x0,A6,D0w*0x1),D7b
//000175f0 48 87           ext.w      D7w
//000175f2 4e 75           rts
    
    u16 offset = script_read16();
    u16 ret = loctc_common(offset);
    alis.varD7 =  vram_read8(ret);
}

void olocti() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void odirb() {
//    OPERNAME_ODIRB_0x9
//00017620 42 40           clr.w      D0w
//00017622 10 1b           move.b     (A3)+,D0b
//00017624 1e 36 00 00     move.b     (0x0,A6,D0w*0x1),D7b
//00017628 48 87           ext.w      D7w
//0001762a 4e 75           rts
    u8 offset = script_read8();
    u16 val = extend_w(*(alis.vram + offset));
    alis.varD7 = val;
}

void odirw() {
//    OPERNAME_ODIRW_0xa
//0001762c 42 40           clr.w      D0w
//0001762e 10 1b           move.b     (A3)+,D0b
//00017630 3e 36 00 00     move.w     (0x0,A6,D0w*0x1),D7w
//00017634 4e 75           rts
    u8 offset = script_read8();
    u16 val = *(u16 *)(alis.vram + offset);
    alis.varD7 = val;
}

void odirp() {
//    OPERNAME_ODIRP_0xb
//00017636 42 40           clr.w      D0w
//00017638 10 1b           move.b     (A3)+,D0b
//0001763a 43 f6 00 00     lea        (0x0,A6,D0w*0x1),A1
//0001763e 20 79 00        movea.l    (ADDR_BSS_256_CHUNK_1).l,A0
//01 95 e2
//    __loop_until_zero                               XREF[1]:     00017646(j)
//00017644 10 d9           move.b     (A1)+,(A0)+
//00017646 66 00 ff fc     bne.w      __loop_until_zero
    u8 offset = script_read8();
    u8 * a1 = alis.vram + offset;
    u8 * a0 = alis.bssChunk1;
    while(*a1) {
        *a0++ = *a1++;
    }
}

void odirtp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void odirtc() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void odirti() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omainb() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omainw() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omainp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omaintp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omaintc() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omainti() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimb() {
//    OPERNAME_OHIMB_0x15
//00017724 10 1b           move.b     (A3)+,D0b
//00017726 e1 40           asl.w      #0x8,D0w
//00017728 10 1b           move.b     (A3)+,D0b
//0001772a 30 36 00 00     move.w     (0x0,A6,D0w*0x1),D0w
//0001772e 20 79 00        movea.l    (ADDR_VIRTUAL_STACK_ORG).l,A0
//01 95 44
//00017734 22 70 00 00     movea.l    (0x0,A0,D0w*0x1),A1
//00017738 10 1b           move.b     (A3)+,D0b
//0001773a e1 40           asl.w      #0x8,D0w
//0001773c 10 1b           move.b     (A3)+,D0b
//0001773e 1e 31 00 00     move.b     (0x0,A1,D0w*0x1),D7b
//00017742 48 87           ext.w      D7w
//00017744 4e 75           rts
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimw() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimtp() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimtc() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ohimti() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

// pop from accumulator into r6
void opile() {
    // save r6 into r7
    alis.varD7 = alis.varD6;
    alis.varD6 = *(alis.acc++);
}

// start eval loop, will stop after ofin() is called
void oeval() {
    alis.oeval_loop = 1;
    while(alis.oeval_loop) {
        readexec_opername();
    }
}

// stop eval loop
void ofin() {
    alis.oeval_loop = 0;
}

// push value from r7 register to accumulator
void opushacc() {
    *(--alis.acc) = alis.varD7;
}

// r7 = variable AND r7
void oand() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 &= alis.varD6;
}

// r7 = variable OR r7
void oor() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 |= alis.varD6;
}

// r7 = variable XOR r7
void oxor() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 ^= alis.varD6;
}

// r7 = variable EQV r7
void oeqv() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 ^= alis.varD6;
    alis.varD7 = ~alis.varD7;
}

// r6 == r7
void oegal() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 == alis.varD7) ? 0xff : 0x0;
}

// r6 != r7
void odiff() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 != alis.varD7) ? 0xff : 0x0;
}

// r6 <= r7
void oinfeg() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 <= alis.varD7) ? 0xff : 0x0;
}

// r6 >= r7
void osupeg() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 >= alis.varD7) ? 0xff : 0x0;
}

// r6 < r7
void oinf() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 < alis.varD7) ? 0xff : 0x0;
}

// r6 > r7
void osup() {
    alis.varD6 = alis.varD7;
    readexec_opername();
    alis.varD7 = (alis.varD6 > alis.varD7) ? 0xff : 0x0;
}

// r7 += variable
void oadd() {
//00017932 61 00 fc 38     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017936 de 46           add.w      D6w,D7w
//00017938 4e 75           rts
    readexec_opername_saveD7();
    alis.varD7 += alis.varD6;
}

// r7 -= variable
void osub() {
//0001793a 61 00 fc 30     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//0001793e 9c 47           sub.w      D7w,D6w
//00017940 3e 06           move.w     D6w,D7w
//00017942 4e 75           rts
    readexec_opername_saveD7();
    alis.varD6 -= alis.varD7;
    alis.varD7 = alis.varD6;
}

// r7 %= variable
void omod() {
//00017944 61 00 fc 26     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017948 48 c6           ext.l      D6
//0001794a 8d c7           divs.w     D7w,D6
//0001794c 2e 06           move.l     D6,D7
//0001794e 48 47           swap       D7
//00017950 4e 75           rts
    readexec_opername_saveD7();
    alis.varD6 %= alis.varD7;
    alis.varD7 = alis.varD6;
}

// r7 /= variable
void odiv() {
//00017952 61 00 fc 18     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017956 48 c6           ext.l      D6
//00017958 8d c7           divs.w     D7w,D6
//0001795a 3e 06           move.w     D6w,D7w
//0001795c 4e 75           rts
    readexec_opername_saveD7();
    alis.varD6 /= alis.varD7;
    alis.varD7 = alis.varD6;
}

// r7 *= variable
void omul() {
//0001795e 61 00 fc 0c     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00017962 cf c6           muls.w     D6w,D7
//00017964 4e 75           rts
    readexec_opername_saveD7();
    alis.varD7 *= alis.varD6;
}


void oneg() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}


void oabs() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ornd() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

// r7 <- (r7 < 0) ? 0xfff : 1
void osgn() {
    s16 d7 = (s16)alis.varD7;
    if(d7 > 0) {
        alis.varD7 = 1;
    }
    else if(d7 < 0) {
        alis.varD7 = 0xffff;
    }
}

void onot() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oinkey() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void okeyon() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ojoy() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oprnd() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oscan() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oshiftkey() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ofree() {
    debug(EDebugWarning, "\n%s SIMULATED\n", __FUNCTION__);
    alis.varD7 = 0x321;
}

void omodel() {
    alis.varD7 = sys_get_model();
}

void ogetkey() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oleft() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oright() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omid() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

// r7 <- len(str1)
void olen() {
    alis.varD7 = strlen((const char *)alis.bssChunk1);
}

void oasc() {
    alis.varD7 = 0;
    alis.varD7 = alis.bssChunk1[0];
}

void ostr() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void osadd() {
    // TODO: strcat ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void osegal() {
    // TODO: strcmp ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void osdiff() {
    // TODO: !strcmp ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void osinfeg() {
    // TODO: string equ or < ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ossupeg() {
    // TODO: string equ or > ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void osinf() {
    // TODO: string < ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ossup() {
    // TODO: string > ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ospushacc() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ospile() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oval() {
    // TODO: compute int value of chunk1 string -> d7 ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oexistf() {
    char * fpath = get_full_path((char *)alis.bssChunk1, alis.platform.path);
    alis.varD7 = sys_fexists(fpath) ? 0xffff : 0x0;
    free(fpath);
}

void ochr() {
    alis.bssChunk1[0] = (u8)alis.varD7;
}

void ochange() {
    // TODO: change le drive courant ??
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void ocountry() {
//    OPERNAME_OCOUNTRY_0x51
//00017d26 42 47           clr.w      D7w
//00017d28 1e 39 00        move.b     (B_COUNTRY_CODE_??).l,D7b
//01 95 09
//00017d2e 4e 75           rts
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void omip() {
    alis.varD7 = 0x64;
}

void ojoykey() {
    debug(EDebugWarning, "\n %s STUBBED\n", __FUNCTION__);
}

void oconfig() {
    alis.varD7 = 0;
}

void cnul() {
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
    DECL_OPCODE(0x00, oimmb,
                "read byte from script, extend to word, copy into r7"),
    {},
    DECL_OPCODE(0x01, oimmw,
                "read word from script, copy into r7"),
    {},
    DECL_OPCODE(0x02, oimmp,
                "read bytes from script until zero, copy into str1"),
    {},
    DECL_OPCODE(0x03, olocb,
                "read offset word from script, extend read byte at vram[offset] to word, copy into r7"),
    {},
    DECL_OPCODE(0x04, olocw,
                "read offset word from script, read word at vram[offset], copy into r7"),
    {},
    DECL_OPCODE(0x05, olocp,
                "read offset word from script, read bytes at vram[offset] until zero, copy into str1"),
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
    DECL_OPCODE(0x1B, opile,
                "copy r6 to r7, pop word form virtual accumulator into r6"),
    {},
    DECL_OPCODE(0x1C, oeval,
                "starts eval loop"),
    {},
    DECL_OPCODE(0x1D, ofin,
                "ends eval loop"),
    {},
    DECL_OPCODE(0x1E, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x1F, cnul, "TODO add desc"),
    {},
    DECL_OPCODE(0x20, opushacc,
                "push word from r7 into virtual accumulator"),
    {},
    DECL_OPCODE(0x21, oand,
                "TODO add desc"),
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
