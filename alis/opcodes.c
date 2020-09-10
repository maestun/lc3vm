//
//  opcodes.c
//  alis
//
//

#include "alis.h"

// =============================================================================
#pragma mark - Helpers
// =============================================================================
static void cstart(u32 offset) {
    // TODO: check OP_CSTART in asm source
}

static void save_D7_then_exec_opname() {
    // save d7.w into d6.w
//    MOVE_W(vm->d7, vm->d6);
//
//    u8 code = vm_read_8();
//    vm_execute_instruction(code, EOpcodeKindOpname);
}


// ============================================================================
#pragma mark - TODO: opcodes
// ============================================================================
static void cstore() {
    save_D7_then_exec_opname();
    
//    0001144a 20 79 00        movea.l    (DAT_00017146).l,A0
//             01 71 46
//    00011450 23 f9 00        move.l     (DAT_0001714e).l,(DAT_00017146).l
//             01 71 4e
//             00 01 71 46
//    0001145a 23 c8 00        move.l     A0,(DAT_0001714e).l
//             01 71 4e
//    vm->d0 = 0;
//    u8 b = vm_read_8();
//    vm_execute_instruction(b, EOpcodeKindStorename);
}

static void ceval() {
    // log_debug("STUBBED");
}

static void cadd() {
    // log_debug("STUBBED");
}

static void csub() {
    // log_debug("STUBBED");
}

static void cvprint() {
    // log_debug("STUBBED");
}

static void csprinti() {
    // log_debug("STUBBED");
}

static void csprinta() {
    // log_debug("STUBBED");
}

static void clocate() {
    // log_debug("STUBBED");
}

static void ctab() {
    // log_debug("STUBBED");
}

static void cdim() {
    
    // read word param
//    vm->d0 = vm_read_16() - 1;
//
//    // read byte param, store it at vram + offset
//    vm->d1 = vm_read_8();
//    *(vm->virtual_ram + vm->d0) = vm->d1; // (vm->ram + 0x2030f) doit valoir 1
//
//    vm->d0--;
//
//    // read byte param, store it at vram + (offset - 1)
//    *(vm->virtual_ram + --vm->d0) = vm_read_8();
//
//    // loop w/ counter, read words, store in vram
//    vm->d0 -= 2;
//    while(vm->d1-- > 0) {
//        vm->d2 = vm_read_16();
//        *(u16 *)(vm->virtual_ram + vm->d0) = vm->d2;
//        vm->d0 -= 2;
//    }
}

static void crandom() {
    // log_debug("STUBBED");
}

static void cloop8() {
    // log_debug("STUBBED");
}

static void cloop16() {
    // log_debug("STUBBED");
}

static void cloop24() {
    // log_debug("STUBBED");
}

static void cswitch1() {
    // log_debug("STUBBED");
}

static void cswitch2() {
    // log_debug("STUBBED");
}

static void cleave() {
    // log_debug("STUBBED");
}

static void cprotect() {
    // log_debug("STUBBED");
}

static void casleep() {
    // log_debug("STUBBED");
}

static void cscmov() {
    // log_debug("STUBBED");
}

static void cscset() {
    // log_debug("STUBBED");
}

static void cclipping() {
    // log_debug("STUBBED");
}

static void cswitching() {
    // log_debug("STUBBED");
}

static void cwlive() {
    // log_debug("STUBBED");
}

static void cunload() {
    // log_debug("STUBBED");
}

static void cwakeup() {
    // log_debug("STUBBED");
}

static void csleep() {
    // log_debug("STUBBED");
}

static void clive() {
    // log_debug("STUBBED");
}

static void ckill() {
    // log_debug("STUBBED");
}

static void cstop() {
    // log_debug("STUBBED");
}

static void cstopret() {
    // log_debug("STUBBED");
}

static void cexit() {
    // log_debug("STUBBED");
}

static void cload() {
    // log_debug("STUBBED");
}

static void cdefsc() {
//    // read a word
//    /*
//     00011a2e 10 1b           move.b     (A3)+,D0b
//     00011a30 e1 40           asl.w      #0x8,D0w
//     00011a32 10 1b           move.b     (A3)+,D0b
//     */
//    u16 offset = vm_read_16();
//
//    /*
//     00011a3a 08 f0 00        bset.b     0x6,(0x0,A0,D0w*0x1)
//     */
//    u8 * a0 = vm->scene_ptr;
//    *(a0 + offset) &= 0x6;
//
//    /*
//     00011a40 11 9b 00 01     move.b     (A3)+,(0x1,A0,D0w*0x1)
//     */
//    *(a0 + offset + 1) = vm_read_8();
//
//    u8 counter = 0x1f;
//
//    /*
//     00011a46 43 f0 00 06     lea        (0x6,A0,D0w*0x1),A1
//     */
//    u8 * a1 = (a0 + offset + 1);
//
//    /*
//     __cdefsc_copy_32_bytes
//     00011a4a 12 db           move.b     (A3)+,(A1)+
//     00011a4c 51 c9 ff fc     dbf        D1w,__cdefsc_copy_32_bytes
//     */
//    do {
//        *(a1) = vm_read_8();
//    } while(--counter != 0);
//
//    /*
//     00011a50 22 79 00        movea.l    (DAT_000170c2).l,A1
//              01 70 c2
//     00011a56 32 39 00        move.w     (DAT_000170c6).l,D1w
//              01 70 c6
//     */
//    // TODO: ..
//
//
//    /*
//     00011a68 31 81 00 02     move.w     D1w,(0x2,A0,D0w*0x1)
//     00011a6c 42 71 10 06     clr.w      (0x6,A1,D1w*0x1)
//     00011a70 42 70 00 04     clr.w      (0x4,A0,D0w*0x1)
//     00011a74 13 b0 00        move.b     (0x1,A0,D0w*0x1),(0x1,A1,D1w*0x1)
//              01 10 01
//     00011a7a 34 30 00 0e     move.w     (0xe,A0,D0w*0x1),D2w
//     00011a7e 02 42 ff f0     andi.w     #-0x10,D2w
//     00011a82 33 82 10 0c     move.w     D2w,(0xc,A1,D1w*0x1)
//     00011a86 33 b0 00        move.w     (0x10,A0,D0w*0x1),(0xe,A1,D1w*0x1)
//              10 10 0e
//     00011a8c 33 bc 7f        move.w     #0x7fff,(0x10,A1,D1w*0x1)
//              ff 10 10
//     00011a92 34 30 00 0e     move.w     (0xe,A0,D0w*0x1),D2w
//     00011a96 d4 70 00 12     add.w      (0x12,A0,D0w*0x1),D2w
//     00011a9a 00 42 00 0f     ori.w      #0xf,D2w
//     00011a9e 33 82 10 16     move.w     D2w,(0x16,A1,D1w*0x1)
//     00011aa2 34 30 00 10     move.w     (0x10,A0,D0w*0x1),D2w
//     00011aa6 d4 70 00 14     add.w      (0x14,A0,D0w*0x1),D2w
//     00011aaa 33 82 10 18     move.w     D2w,(0x18,A1,D1w*0x1)
//     00011aae 42 70 00 2a     clr.w      (0x2a,A0,D0w*0x1)
//     00011ab2 42 70 00 2c     clr.w      (0x2c,A0,D0w*0x1)
//     00011ab6 42 70 00 2e     clr.w      (0x2e,A0,D0w*0x1)
//     00011aba 61 00 03 28     bsr.w      FUN_00011de4                                     undefined FUN_00011de4()
//     00011abe 41 f0 00 00     lea        (0x0,A0,D0w*0x1),A0
//     00011ac2 61 00 03 78     bsr.w      FUN_00011e3c                                     undefined FUN_00011e3c()
//     00011ac6 4e 75           rts
//
//     */
}

static void cscreen() {
    // log_debug("STUBBED");
}

static void cput() {
    // log_debug("STUBBED");
}

static void cputnat() {
    // log_debug("STUBBED");
}

static void cerase() {
    // log_debug("STUBBED");
}

static void cerasen() {
    // log_debug("STUBBED");
}

static void cset() {
    // log_debug("STUBBED");
}

static void cmov() {
    // log_debug("STUBBED");
}

static void copensc() {
    // log_debug("STUBBED");
}

static void cclosesc() {
    // log_debug("STUBBED");
}

static void cerasall() {
    // log_debug("STUBBED");
}

static void cforme() {
    // log_debug("STUBBED");
}

static void cdelforme() {
    // log_debug("STUBBED");
}

static void ctstmov() {
    // log_debug("STUBBED");
}

static void ctstset() {
    // log_debug("STUBBED");
}

static void cftstmov() {
    // log_debug("STUBBED");
}

static void cftstset() {
    // log_debug("STUBBED");
}

static void csuccent() {
    // log_debug("STUBBED");
}

static void cpredent() {
    // log_debug("STUBBED");
}

static void cnearent() {
    // log_debug("STUBBED");
}

static void cneartyp() {
    // log_debug("STUBBED");
}

static void cnearmat() {
    // log_debug("STUBBED");
}

static void cviewent() {
    // log_debug("STUBBED");
}

static void cviewtyp() {
    // log_debug("STUBBED");
}

static void cviewmat() {
    // log_debug("STUBBED");
}

static void corient() {
    // log_debug("STUBBED");
}

static void crstent() {
    // log_debug("STUBBED");
}

static void csend() {
    // log_debug("STUBBED");
}

static void cscanon() {
    // log_debug("STUBBED");
}

static void cscanoff() {
    // log_debug("STUBBED");
}

static void cinteron() {
    // log_debug("STUBBED");
}

static void cinteroff() {
    // log_debug("STUBBED");
}

static void cscanclr() {
    // log_debug("STUBBED");
}

static void callentity() {
    // log_debug("STUBBED");
}

static void cpalette() {
    // log_debug("STUBBED");
}

static void cdefcolor() {
    // log_debug("STUBBED");
}

static void ctiming() {
    // log_debug("STUBBED");
}

static void czap() {
    // log_debug("STUBBED");
}

static void cexplode() {
    // log_debug("STUBBED");
}

static void cding() {
    // log_debug("STUBBED");
}

static void cnoise() {
    // log_debug("STUBBED");
}

static void cinitab() {
    // log_debug("STUBBED");
}

static void cfopen() {
    // log_debug("STUBBED");
}

static void cfclose() {
    // log_debug("STUBBED");
}

static void cfcreat() {
    // log_debug("STUBBED");
}

static void cfdel() {
    // log_debug("STUBBED");
}

static void cfreadv() {
    // log_debug("STUBBED");
}

static void cfwritev() {
    // log_debug("STUBBED");
}

static void cfwritei() {
    // log_debug("STUBBED");
}

static void cfreadb() {
    // log_debug("STUBBED");
}

static void cfwriteb() {
    // log_debug("STUBBED");
}

static void cplot() {
    // log_debug("STUBBED");
}

static void cdraw() {
    // log_debug("STUBBED");
}

static void cbox() {
    // log_debug("STUBBED");
}

static void cboxf() {
    // log_debug("STUBBED");
}

static void cink() {
    // log_debug("STUBBED");
}

static void cpset() {
    // log_debug("STUBBED");
}

static void cpmove() {
    // log_debug("STUBBED");
}

static void cpmode() {
    // log_debug("STUBBED");
}

static void cpicture() {
    // log_debug("STUBBED");
}

static void cxyscroll() {
    // log_debug("STUBBED");
}

static void clinking() {
    // log_debug("STUBBED");
}

static void cmouson() {
    // log_debug("STUBBED");
}

static void cmousoff() {
    // log_debug("STUBBED");
}

static void cmouse() {
    // log_debug("STUBBED");
}

static void cdefmouse() {
    // log_debug("STUBBED");
}

static void csetmouse() {
    // log_debug("STUBBED");
}

static void cdefvect() {
    // log_debug("STUBBED");
}

static void csetvect() {
    // log_debug("STUBBED");
}

static void capproach() {
    // log_debug("STUBBED");
}

static void cescape() {
    // log_debug("STUBBED");
}

static void cvtstmov() {
    // log_debug("STUBBED");
}

static void cvftstmov() {
    // log_debug("STUBBED");
}

static void cvmov() {
    // log_debug("STUBBED");
}

static void cdefworld() {
    // log_debug("STUBBED");
}

static void cworld() {
    // log_debug("STUBBED");
}

static void cfindmat() {
    // log_debug("STUBBED");
}

static void cfindtyp() {
    // log_debug("STUBBED");
}

static void cmusic() {
    // log_debug("STUBBED");
}

static void cdelmusic() {
    // log_debug("STUBBED");
}

static void ccadence() {
    // log_debug("STUBBED");
}

static void csetvolum() {
    // log_debug("STUBBED");
}

static void cxinv() {
    // log_debug("STUBBED");
}

static void cxinvon() {
    // log_debug("STUBBED");
}

static void cxinvoff() {
    // log_debug("STUBBED");
}

static void clistent() {
    // log_debug("STUBBED");
}

static void csound() {
    // log_debug("STUBBED");
}

static void cmsound() {
    // log_debug("STUBBED");
}

static void credon() {
    // log_debug("STUBBED");
}

static void credoff() {
    // log_debug("STUBBED");
}

static void cdelsound() {
    // log_debug("STUBBED");
}

static void cwmov() {
    // log_debug("STUBBED");
}

static void cwtstmov() {
    // log_debug("STUBBED");
}

static void cwftstmov() {
    // log_debug("STUBBED");
}

static void ctstform() {
    // log_debug("STUBBED");
}

static void cxput() {
    // log_debug("STUBBED");
}

static void cxputat() {
    // log_debug("STUBBED");
}

static void cmput() {
    // log_debug("STUBBED");
}

static void cmputat() {
    // log_debug("STUBBED");
}

static void cmxput() {
    // log_debug("STUBBED");
}

static void cmxputat() {
    // log_debug("STUBBED");
}

static void cmmusic() {
    // log_debug("STUBBED");
}

static void cmforme() {
    // log_debug("STUBBED");
}

static void csettime() {
    // log_debug("STUBBED");
}

static void cgettime() {
    // log_debug("STUBBED");
}

static void cvinput() {
    // log_debug("STUBBED");
}

static void csinput() {
    // log_debug("STUBBED");
}

static void crunfilm() {
    // log_debug("STUBBED");
}

static void cvpicprint() {
    // log_debug("STUBBED");
}

static void cspicprint() {
    // log_debug("STUBBED");
}

static void cvputprint() {
    // log_debug("STUBBED");
}

static void csputprint() {
    // log_debug("STUBBED");
}

static void cfont() {
    // log_debug("STUBBED");
}

static void cpaper() {
    // log_debug("STUBBED");
}

static void ctoblack() {
    // log_debug("STUBBED");
}

static void cmovcolor() {
    // log_debug("STUBBED");
}

static void ctopalet() {
    // log_debug("STUBBED");
}

static void cnumput() {
    // log_debug("STUBBED");
}

static void cscheart() {
    // log_debug("STUBBED");
}

static void cscpos() {
    // log_debug("STUBBED");
}

static void cscsize() {
    // log_debug("STUBBED");
}

static void cschoriz() {
    // log_debug("STUBBED");
}

static void cscvertic() {
    // log_debug("STUBBED");
}

static void cscreduce() {
    // log_debug("STUBBED");
}

static void cscscale() {
    // log_debug("STUBBED");
}

static void creducing() {
    // log_debug("STUBBED");
}

static void cscmap() {
    // log_debug("STUBBED");
}

static void cscdump() {
    // log_debug("STUBBED");
}

static void cfindcla() {
    // log_debug("STUBBED");
}

static void cnearcla() {
    // log_debug("STUBBED");
}

static void cviewcla() {
    // log_debug("STUBBED");
}

static void cinstru() {
    // log_debug("STUBBED");
}

static void cminstru() {
    // log_debug("STUBBED");
}

static void cordspr() {
    // log_debug("STUBBED");
}

static void calign() {
    // log_debug("STUBBED");
}

static void cbackstar() {
    // log_debug("STUBBED");
}

static void cstarring() {
    // log_debug("STUBBED");
}

static void cengine() {
    // log_debug("STUBBED");
}

static void cautobase() {
    // log_debug("STUBBED");
}

static void cquality() {
    // log_debug("STUBBED");
}

static void chsprite() {
    // log_debug("STUBBED");
}

static void cselpalet() {
    // log_debug("STUBBED");
}

static void clinepalet() {
    // log_debug("STUBBED");
}

static void cautomode() {
    // log_debug("STUBBED");
}

static void cautofile() {
    // log_debug("STUBBED");
}

static void ccancel() {
    // log_debug("STUBBED");
}

static void ccancall() {
    // log_debug("STUBBED");
}

static void ccancen() {
    // log_debug("STUBBED");
}

static void cblast() {
    // log_debug("STUBBED");
}

static void cscback() {
    // log_debug("STUBBED");
}

static void cscrolpage() {
    // log_debug("STUBBED");
}

static void cmatent() {
    // log_debug("STUBBED");
}

static void cshrink() {
    // log_debug("STUBBED");
}

static void cdefmap() {
    // log_debug("STUBBED");
}

static void csetmap() {
    // log_debug("STUBBED");
}

static void cputmap() {
    // log_debug("STUBBED");
}

static void csavepal() {
    // log_debug("STUBBED");
}

static void csczoom() {
    // log_debug("STUBBED");
}

static void ctexmap() {
    // log_debug("STUBBED");
}

static void calloctab() {
    // log_debug("STUBBED");
}

static void cfreetab() {
    // log_debug("STUBBED");
}

static void cscantab() {
    // log_debug("STUBBED");
}

static void cneartab() {
    // log_debug("STUBBED");
}

static void cscsun() {
    // log_debug("STUBBED");
}

static void cdarkpal() {
    // log_debug("STUBBED");
}

static void cscdark() {
    // log_debug("STUBBED");
}

static void caset() {
    // log_debug("STUBBED");
}

static void camov() {
    // log_debug("STUBBED");
}

static void cscaset() {
    // log_debug("STUBBED");
}

static void cscamov() {
    // log_debug("STUBBED");
}

static void cscfollow() {
    // log_debug("STUBBED");
}

static void cscview() {
    // log_debug("STUBBED");
}

static void cfilm() {
    // log_debug("STUBBED");
}

static void cwalkmap() {
    // log_debug("STUBBED");
}

static void catstmap() {
    // log_debug("STUBBED");
}

static void cavtstmov() {
    // log_debug("STUBBED");
}

static void cavmov() {
    // log_debug("STUBBED");
}

static void caim() {
    // log_debug("STUBBED");
}

static void cpointpix() {
    // log_debug("STUBBED");
}

static void cchartmap() {
    // log_debug("STUBBED");
}

static void cscsky() {
    // log_debug("STUBBED");
}

static void czoom() {
    // log_debug("STUBBED");
}


// ============================================================================
#pragma mark - Empty opcodes
// ============================================================================
static void cnul()      {  }
static void cesc1()     {  }
static void cesc2()     {  }
static void cesc3()     {  }
static void cclock()    {  }
static void cbreakpt()  {  }
static void cmul()      {  }
static void cdiv()      {  }
static void cjsrabs()   {  }
static void cjmpabs()   {  }
static void cjsrind16() {  }
static void cjsrind24() {  }
static void cjmpind16() {  }
static void cjmpind24() {  }


// ============================================================================
#pragma mark - Flow control opcodes
// ============================================================================
static void cjsr(u32 offset) {
    // save return offset
//    vm->virtual_return_offset -= 4;
//    *(u32 *)(vm->virtual_ram + vm->d4) = *(u32 *)vm->script->ptr;
//
//    // jump to subroutine
//    vm->script->ptr += offset;
}

static void cjsr8() {
    // read byte, extend sign
//    u8 offset8 = vm_read_8();
//    u16 offset16 = offset8 + (BIT_CHK(offset8, 7) ? 0xff00 : 0);
//    cjsr(offset16);
}

static void cjsr16() {
//    u16 offset = vm_read_16();
//    cjsr(offset);
}

static void cjsr24() {
    // read 24 bits from script
//    u32 offset = vm_read_24();
//    cjsr(offset);
}

static void cjmp8() {
//    u16 offset16 = vm_read_8_ext();
//    vm->script->ptr += offset16;
}

static void cjmp16() {
//    u16 offset16 = vm_read_16();
//    vm->script->ptr += offset16;
}

static void cjmp24() {
//    u32 offset32 = vm_read_24();
//    vm->script->ptr += offset32;
}

static void cret() {}
static void cbz8() {}
static void cbz16() {}
static void cbz24() {}
static void cbnz8() {}
static void cbnz16() {}
static void cbnz24() {}
static void cbeq8() {}
static void cbeq16() {}
static void cbeq24() {}
static void cbne8() {}
static void cbne16() {}
static void cbne24() {}

static void cstart8() {
    // read byte, extend sign to word, then to long
//    u16 offset16 = vm_read_8_ext();
//    u32 offset32 = offset16 + (BIT_CHK(offset16, 7) ? 0xffff0000 : 0); // EXT.L
//    cstart(offset32);
}

static void cstart16() {
//    u16 offset16 = vm_read_16();
//    cstart(offset16);
}

static void cstart24() {
//    u32 offset32 = vm_read_24();
//    cstart(offset32);
}


// ============================================================================
#pragma mark - Other opcodes
// ============================================================================


// ============================================================================
#pragma mark - Opcode pointer table
// ============================================================================
sAlisOpcode opcodes[] = {
    DECL_OPCODE(0x00, cnul,         "TODO: add desc"),
    DECL_OPCODE(0x01, cesc1,        "TODO: add desc"),
    DECL_OPCODE(0x02, cesc2,        "TODO: add desc"),
    DECL_OPCODE(0x03, cesc3,        "TODO: add desc"),
    DECL_OPCODE(0x04, cbreakpt,     "TODO: add desc"),
    DECL_OPCODE(0x05, cjsr8,        "jump to sub-routine with 8-bit offset"),
    DECL_OPCODE(0x06, cjsr16,       "jump to sub-routine with 16-bit offset"),
    DECL_OPCODE(0x07, cjsr24,       "jump to sub-routine with 24-bit offset"),
    DECL_OPCODE(0x08, cjmp8,        "jump (8-bit offset)"),
    DECL_OPCODE(0x09, cjmp16,       "jump (16-bit offset)"),
    DECL_OPCODE(0x0a, cjmp24,       "jump (24-bit offset)"),
    DECL_OPCODE(0x0b, cjsrabs,      "unknown"),
    DECL_OPCODE(0x0c, cjmpabs,      "unknown"),
    DECL_OPCODE(0x0d, cjsrind16,    "unknown"),
    DECL_OPCODE(0x0e, cjsrind24,    "unknown"),
    DECL_OPCODE(0x0f, cjmpind16,    "unknown"),
    DECL_OPCODE(0x10, cjmpind24,    "unknown"),
    DECL_OPCODE(0x11, cret,         "return from sub-routine"),
    DECL_OPCODE(0x12, cbz8,         "branch if zero with 8-bit offset"),
    DECL_OPCODE(0x13, cbz16,        "branch if zero with 16-bit offset"),
    DECL_OPCODE(0x14, cbz24,        "branch if zero with 24-bit offset"),
    DECL_OPCODE(0x15, cbnz8,        "branch if non-zero with 8-bit offset"),
    DECL_OPCODE(0x16, cbnz16,       "branch if non-zero with 16-bit offset"),
    DECL_OPCODE(0x17, cbnz24,       "branch if non-zero with 24-bit offset"),
    DECL_OPCODE(0x18, cbeq8, "branch if equal with 8-bit offset"),
    DECL_OPCODE(0x19, cbeq16, "branch if equal with 16-bit offset"),
    DECL_OPCODE(0x1a, cbeq24, "branch if equal with 24-bit offset"),
    DECL_OPCODE(0x1b, cbne8, "branch if non-equal with 8-bit offset"),
    DECL_OPCODE(0x1c, cbne16, "branch if non-equal with 16-bit offset"),
    DECL_OPCODE(0x1d, cbne24, "branch if non-equal with 24-bit offset"),
    DECL_OPCODE(0x1e, cstore, "TODO: add desc"),
    DECL_OPCODE(0x1f, ceval, "TODO: add desc"),
    DECL_OPCODE(0x20, cadd, "TODO: add desc"),
    DECL_OPCODE(0x21, csub, "TODO: add desc"),
    DECL_OPCODE(0x22, cmul, "TODO: add desc"),
    DECL_OPCODE(0x23, cdiv, "TODO: add desc"),
    DECL_OPCODE(0x24, cvprint, "TODO: add desc"),
    DECL_OPCODE(0x25, csprinti, "TODO: add desc"),
    DECL_OPCODE(0x26, csprinta, "TODO: add desc"),
    DECL_OPCODE(0x27, clocate, "TODO: add desc"),
    DECL_OPCODE(0x28, ctab, "TODO: add desc"),
    DECL_OPCODE(0x29, cdim, "TODO: add desc"),
    DECL_OPCODE(0x2a, crandom, "TODO: add desc"),
    DECL_OPCODE(0x2b, cloop8, "TODO: add desc"),
    DECL_OPCODE(0x2c, cloop16, "TODO: add desc"),
    DECL_OPCODE(0x2d, cloop24, "TODO: add desc"),
    DECL_OPCODE(0x2e, cswitch1, "TODO: add desc"),
    DECL_OPCODE(0x2f, cswitch2, "TODO: add desc"),
    DECL_OPCODE(0x30, cstart8, "TODO: add desc"),
    DECL_OPCODE(0x31, cstart16, "TODO: add desc"),
    DECL_OPCODE(0x32, cstart24, "TODO: add desc"),
    DECL_OPCODE(0x33, cleave, "TODO: add desc"),
    DECL_OPCODE(0x34, cprotect, "TODO: add desc"),
    DECL_OPCODE(0x35, casleep, "TODO: add desc"),
    DECL_OPCODE(0x36, cclock, "TODO: add desc"),
    DECL_OPCODE(0x37, cnul, "TODO: add desc"),
    DECL_OPCODE(0x38, cscmov, "TODO: add desc"),
    DECL_OPCODE(0x39, cscset, "TODO: add desc"),
    DECL_OPCODE(0x3a, cclipping, "TODO: add desc"),
    DECL_OPCODE(0x3b, cswitching, "TODO: add desc"),
    DECL_OPCODE(0x3c, cwlive, "TODO: add desc"),
    DECL_OPCODE(0x3d, cunload, "TODO: add desc"),
    DECL_OPCODE(0x3e, cwakeup, "TODO: add desc"),
    DECL_OPCODE(0x3f, csleep, "TODO: add desc"),
    DECL_OPCODE(0x40, clive, "TODO: add desc"),
    DECL_OPCODE(0x41, ckill, "TODO: add desc"),
    DECL_OPCODE(0x42, cstop, "TODO: add desc"),
    DECL_OPCODE(0x43, cstopret, "TODO: add desc"),
    DECL_OPCODE(0x44, cexit, "TODO: add desc"),
    DECL_OPCODE(0x45, cload, "TODO: add desc"),
    DECL_OPCODE(0x46, cdefsc, "Define Scene ??"),
    DECL_OPCODE(0x47, cscreen, "TODO: add desc"),
    DECL_OPCODE(0x48, cput, "TODO: add desc"),
    DECL_OPCODE(0x49, cputnat, "TODO: add desc"),
    DECL_OPCODE(0x4a, cerase, "TODO: add desc"),
    DECL_OPCODE(0x4b, cerasen, "TODO: add desc"),
    DECL_OPCODE(0x4c, cset, "TODO: add desc"),
    DECL_OPCODE(0x4d, cmov, "TODO: add desc"),
    DECL_OPCODE(0x4e, copensc, "TODO: add desc"),
    DECL_OPCODE(0x4f, cclosesc, "TODO: add desc"),
    DECL_OPCODE(0x50, cerasall, "TODO: add desc"),
    DECL_OPCODE(0x51, cforme, "TODO: add desc"),
    DECL_OPCODE(0x52, cdelforme, "TODO: add desc"),
    DECL_OPCODE(0x53, ctstmov, "TODO: add desc"),
    DECL_OPCODE(0x54, ctstset, "TODO: add desc"),
    DECL_OPCODE(0x55, cftstmov, "TODO: add desc"),
    DECL_OPCODE(0x56, cftstset, "TODO: add desc"),
    DECL_OPCODE(0x57, csuccent, "TODO: add desc"),
    DECL_OPCODE(0x58, cpredent, "TODO: add desc"),
    DECL_OPCODE(0x59, cnearent, "TODO: add desc"),
    DECL_OPCODE(0x5a, cneartyp, "TODO: add desc"),
    DECL_OPCODE(0x5b, cnearmat, "TODO: add desc"),
    DECL_OPCODE(0x5c, cviewent, "TODO: add desc"),
    DECL_OPCODE(0x5d, cviewtyp, "TODO: add desc"),
    DECL_OPCODE(0x5e, cviewmat, "TODO: add desc"),
    DECL_OPCODE(0x5f, corient, "TODO: add desc"),
    DECL_OPCODE(0x60, crstent, "TODO: add desc"),
    DECL_OPCODE(0x61, csend, "TODO: add desc"),
    DECL_OPCODE(0x62, cscanon, "TODO: add desc"),
    DECL_OPCODE(0x63, cscanoff, "TODO: add desc"),
    DECL_OPCODE(0x64, cinteron, "TODO: add desc"),
    DECL_OPCODE(0x65, cinteroff, "TODO: add desc"),
    DECL_OPCODE(0x66, cscanclr, "TODO: add desc"),
    DECL_OPCODE(0x67, callentity, "TODO: add desc"),
    DECL_OPCODE(0x68, cpalette, "TODO: add desc"),
    DECL_OPCODE(0x69, cdefcolor, "TODO: add desc"),
    DECL_OPCODE(0x6a, ctiming, "TODO: add desc"),
    DECL_OPCODE(0x6b, czap, "TODO: add desc"),
    DECL_OPCODE(0x6c, cexplode, "TODO: add desc"),
    DECL_OPCODE(0x6d, cding, "TODO: add desc"),
    DECL_OPCODE(0x6e, cnoise, "TODO: add desc"),
    DECL_OPCODE(0x6f, cinitab, "TODO: add desc"),
    DECL_OPCODE(0x70, cfopen, "TODO: add desc"),
    DECL_OPCODE(0x71, cfclose, "TODO: add desc"),
    DECL_OPCODE(0x72, cfcreat, "TODO: add desc"),
    DECL_OPCODE(0x73, cfdel, "TODO: add desc"),
    DECL_OPCODE(0x74, cfreadv, "TODO: add desc"),
    DECL_OPCODE(0x75, cfwritev, "TODO: add desc"),
    DECL_OPCODE(0x76, cfwritei, "TODO: add desc"),
    DECL_OPCODE(0x77, cfreadb, "TODO: add desc"),
    DECL_OPCODE(0x78, cfwriteb, "TODO: add desc"),
    DECL_OPCODE(0x79, cplot, "TODO: add desc"),
    DECL_OPCODE(0x7a, cdraw, "TODO: add desc"),
    DECL_OPCODE(0x7b, cbox, "TODO: add desc"),
    DECL_OPCODE(0x7c, cboxf, "TODO: add desc"),
    DECL_OPCODE(0x7d, cink, "TODO: add desc"),
    DECL_OPCODE(0x7e, cpset, "TODO: add desc"),
    DECL_OPCODE(0x7f, cpmove, "TODO: add desc"),
    DECL_OPCODE(0x80, cpmode, "TODO: add desc"),
    DECL_OPCODE(0x81, cpicture, "TODO: add desc"),
    DECL_OPCODE(0x82, cxyscroll, "TODO: add desc"),
    DECL_OPCODE(0x83, clinking, "TODO: add desc"),
    DECL_OPCODE(0x84, cmouson, "TODO: add desc"),
    DECL_OPCODE(0x85, cmousoff, "TODO: add desc"),
    DECL_OPCODE(0x86, cmouse, "TODO: add desc"),
    DECL_OPCODE(0x87, cdefmouse, "TODO: add desc"),
    DECL_OPCODE(0x88, csetmouse, "TODO: add desc"),
    DECL_OPCODE(0x89, cdefvect, "TODO: add desc"),
    DECL_OPCODE(0x8a, csetvect, "TODO: add desc"),
    DECL_OPCODE(0x8b, cnul, "TODO: add desc"),
    DECL_OPCODE(0x8c, capproach, "TODO: add desc"),
    DECL_OPCODE(0x8d, cescape, "TODO: add desc"),
    DECL_OPCODE(0x8e, cvtstmov, "TODO: add desc"),
    DECL_OPCODE(0x8f, cvftstmov, "TODO: add desc"),
    DECL_OPCODE(0x90, cvmov, "TODO: add desc"),
    DECL_OPCODE(0x91, cdefworld, "TODO: add desc"),
    DECL_OPCODE(0x92, cworld, "TODO: add desc"),
    DECL_OPCODE(0x93, cfindmat, "TODO: add desc"),
    DECL_OPCODE(0x94, cfindtyp, "TODO: add desc"),
    DECL_OPCODE(0x95, cmusic, "TODO: add desc"),
    DECL_OPCODE(0x96, cdelmusic, "TODO: add desc"),
    DECL_OPCODE(0x97, ccadence, "TODO: add desc"),
    DECL_OPCODE(0x98, csetvolum, "TODO: add desc"),
    DECL_OPCODE(0x99, cxinv, "TODO: add desc"),
    DECL_OPCODE(0x9a, cxinvon, "TODO: add desc"),
    DECL_OPCODE(0x9b, cxinvoff, "TODO: add desc"),
    DECL_OPCODE(0x9c, clistent, "TODO: add desc"),
    DECL_OPCODE(0x9d, csound, "TODO: add desc"),
    DECL_OPCODE(0x9e, cmsound, "TODO: add desc"),
    DECL_OPCODE(0x9f, credon, "TODO: add desc"),
    DECL_OPCODE(0xa0, credoff, "TODO: add desc"),
    DECL_OPCODE(0xa1, cdelsound, "TODO: add desc"),
    DECL_OPCODE(0xa2, cwmov, "TODO: add desc"),
    DECL_OPCODE(0xa3, cwtstmov, "TODO: add desc"),
    DECL_OPCODE(0xa4, cwftstmov, "TODO: add desc"),
    DECL_OPCODE(0xa5, ctstform, "TODO: add desc"),
    DECL_OPCODE(0xa6, cxput, "TODO: add desc"),
    DECL_OPCODE(0xa7, cxputat, "TODO: add desc"),
    DECL_OPCODE(0xa8, cmput, "TODO: add desc"),
    DECL_OPCODE(0xa9, cmputat, "TODO: add desc"),
    DECL_OPCODE(0xaa, cmxput, "TODO: add desc"),
    DECL_OPCODE(0xab, cmxputat, "TODO: add desc"),
    DECL_OPCODE(0xac, cmmusic, "TODO: add desc"),
    DECL_OPCODE(0xad, cmforme, "TODO: add desc"),
    DECL_OPCODE(0xae, csettime, "TODO: add desc"),
    DECL_OPCODE(0xaf, cgettime, "TODO: add desc"),
    DECL_OPCODE(0xb0, cvinput, "TODO: add desc"),
    DECL_OPCODE(0xb1, csinput, "TODO: add desc"),
    DECL_OPCODE(0xb2, cnul, "TODO: add desc"),
    DECL_OPCODE(0xb3, cnul, "TODO: add desc"),
    DECL_OPCODE(0xb4, cnul, "TODO: add desc"),
    DECL_OPCODE(0xb5, crunfilm, "TODO: add desc"),
    DECL_OPCODE(0xb6, cvpicprint, "TODO: add desc"),
    DECL_OPCODE(0xb7, cspicprint, "TODO: add desc"),
    DECL_OPCODE(0xb8, cvputprint, "TODO: add desc"),
    DECL_OPCODE(0xb9, csputprint, "TODO: add desc"),
    DECL_OPCODE(0xba, cfont, "TODO: add desc"),
    DECL_OPCODE(0xbb, cpaper, "TODO: add desc"),
    DECL_OPCODE(0xbc, ctoblack, "TODO: add desc"),
    DECL_OPCODE(0xbd, cmovcolor, "TODO: add desc"),
    DECL_OPCODE(0xbe, ctopalet, "TODO: add desc"),
    DECL_OPCODE(0xbf, cnumput, "TODO: add desc"),
    DECL_OPCODE(0xc0, cscheart, "TODO: add desc"),
    DECL_OPCODE(0xc1, cscpos, "TODO: add desc"),
    DECL_OPCODE(0xc2, cscsize, "TODO: add desc"),
    DECL_OPCODE(0xc3, cschoriz, "TODO: add desc"),
    DECL_OPCODE(0xc4, cscvertic, "TODO: add desc"),
    DECL_OPCODE(0xc5, cscreduce, "TODO: add desc"),
    DECL_OPCODE(0xc6, cscscale, "TODO: add desc"),
    DECL_OPCODE(0xc7, creducing, "TODO: add desc"),
    DECL_OPCODE(0xc8, cscmap, "TODO: add desc"),
    DECL_OPCODE(0xc9, cscdump, "TODO: add desc"),
    DECL_OPCODE(0xca, cfindcla, "TODO: add desc"),
    DECL_OPCODE(0xcb, cnearcla, "TODO: add desc"),
    DECL_OPCODE(0xcc, cviewcla, "TODO: add desc"),
    DECL_OPCODE(0xcd, cinstru, "TODO: add desc"),
    DECL_OPCODE(0xce, cminstru, "TODO: add desc"),
    DECL_OPCODE(0xcf, cordspr, "TODO: add desc"),
    DECL_OPCODE(0xd0, calign, "TODO: add desc"),
    DECL_OPCODE(0xd1, cbackstar, "TODO: add desc"),
    DECL_OPCODE(0xd2, cstarring, "TODO: add desc"),
    DECL_OPCODE(0xd3, cengine, "TODO: add desc"),
    DECL_OPCODE(0xd4, cautobase, "TODO: add desc"),
    DECL_OPCODE(0xd5, cquality, "TODO: add desc"),
    DECL_OPCODE(0xd6, chsprite, "TODO: add desc"),
    DECL_OPCODE(0xd7, cselpalet, "TODO: add desc"),
    DECL_OPCODE(0xd8, clinepalet, "TODO: add desc"),
    DECL_OPCODE(0xd9, cautomode, "TODO: add desc"),
    DECL_OPCODE(0xda, cautofile, "TODO: add desc"),
    DECL_OPCODE(0xdb, ccancel, "TODO: add desc"),
    DECL_OPCODE(0xdc, ccancall, "TODO: add desc"),
    DECL_OPCODE(0xdd, ccancen, "TODO: add desc"),
    DECL_OPCODE(0xde, cblast, "TODO: add desc"),
    DECL_OPCODE(0xdf, cscback, "TODO: add desc"),
    DECL_OPCODE(0xe0, cscrolpage, "TODO: add desc"),
    DECL_OPCODE(0xe1, cmatent, "TODO: add desc"),
    DECL_OPCODE(0xe2, cshrink, "TODO: add desc"),
    DECL_OPCODE(0xe3, cdefmap, "TODO: add desc"),
    DECL_OPCODE(0xe4, csetmap, "TODO: add desc"),
    DECL_OPCODE(0xe5, cputmap, "TODO: add desc"),
    DECL_OPCODE(0xe6, csavepal, "TODO: add desc"),
    DECL_OPCODE(0xe7, csczoom, "TODO: add desc"),
    DECL_OPCODE(0xe8, ctexmap, "TODO: add desc"),
    DECL_OPCODE(0xe9, calloctab, "TODO: add desc"),
    DECL_OPCODE(0xea, cfreetab, "TODO: add desc"),
    DECL_OPCODE(0xeb, cscantab, "TODO: add desc"),
    DECL_OPCODE(0xec, cneartab, "TODO: add desc"),
    DECL_OPCODE(0xed, cscsun, "TODO: add desc"),
    DECL_OPCODE(0xee, cdarkpal, "TODO: add desc"),
    DECL_OPCODE(0xef, cscdark, "TODO: add desc"),
    DECL_OPCODE(0xf0, caset, "TODO: add desc"),
    DECL_OPCODE(0xf1, camov, "TODO: add desc"),
    DECL_OPCODE(0xf2, cscaset, "TODO: add desc"),
    DECL_OPCODE(0xf3, cscamov, "TODO: add desc"),
    DECL_OPCODE(0xf4, cscfollow, "TODO: add desc"),
    DECL_OPCODE(0xf5, cscview, "TODO: add desc"),
    DECL_OPCODE(0xf6, cfilm, "TODO: add desc"),
    DECL_OPCODE(0xf7, cwalkmap, "TODO: add desc"),
    DECL_OPCODE(0xf8, catstmap, "TODO: add desc"),
    DECL_OPCODE(0xf9, cavtstmov, "TODO: add desc"),
    DECL_OPCODE(0xfa, cavmov, "TODO: add desc"),
    DECL_OPCODE(0xfb, caim, "TODO: add desc"),
    DECL_OPCODE(0xfc, cpointpix, "TODO: add desc"),
    DECL_OPCODE(0xfd, cchartmap, "TODO: add desc"),
    DECL_OPCODE(0xfe, cscsky, "TODO: add desc"),
    DECL_OPCODE(0xff, czoom, "TODO: add desc")
};
