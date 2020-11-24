//
//  opcodes.c
//  alis
//
//

#include "alis.h"
#include "alis_private.h"
#include "utils.h"


#define BIT_SCAN        (0)
#define BIT_INTER       (1)


// ============================================================================
#pragma mark - Opcodes
// ============================================================================
static void cstore() {
    readexec_opername_saveD7();
    
    // swap chunk 1 / 3
    u8 * tmp = alis.bssChunk1;
    alis.bssChunk1 = alis.bssChunk3;
    alis.bssChunk3 = tmp;
    
    readexec_storename();
}

static void ceval() {
    readexec_opername_saveD7();
}

static void cadd() {
    readexec_opername_saveD7();
    readexec_addname_swap();
}

static void csub() {
    readexec_opername_saveD7();
    alis.varD7 *= -1;
    readexec_addname_swap();
}

static void cvprint() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csprinti() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csprinta() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void clocate() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

// ???
// read x bytes
static void cdim() {

    u8 * ram = (u8 *)alis.vram;
    
    // read word param
    u16 offset = script_read16();
    u8 counter = script_read8();
    u8 byte2 = script_read8();
    
    ram[--offset] = counter;
    ram[--offset] = byte2;
    
    // loop w/ counter, read words, store backwards
    while(counter--) {
        u16 w = script_read16();
        offset -= 2;
        ram[offset] = (w >> 8) & 0xff;
        ram[offset + 1] = w & 0xff;
    }
}

static void crandom() {
    readexec_opername();
    alis._random_number = alis.varD7;
    if(alis._random_number == 0) {
        alis._random_number = sys_random();
        // test key/joy input, if zero, random is set to $64 ???
    }
}


// cloopX(jmp_offset, addname(ram_offset))
// decrement value in RAM[offset2]
// if obtained value is zero, then jump with jmp_offset
static void cloop(u32 offset) {
    alis.varD7 = -1;
    readexec_addname_swap();
    if(alis.sr.zero) {
        script_jump(offset);
    }
}

static void cloop8() {
    cloop(script_read8ext16());
}

static void cloop16() {
    cloop(script_read16());
}

static void cloop24() {
    cloop(script_read24());
}

static void cswitch1() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cswitch2() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cleave() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
//    **************************************************************
//    *                          FUNCTION                          *
//    **************************************************************
//    undefined OPCODE_CLEAVE_0x33()
//undefined         D0b:1          <RETURN>
//    OPCODE_CLEAVE_0x33
//00013206 4a 39 00        tst.b      (B_CSTOPRET).l
//01 95 a3
//0001320c 66 00 00 1c     bne.w      LAB_0001322a
//00013210 32 2e ff f4     move.w     (-0xc,A6),D1w
//00013214 67 00 00 34     beq.w      OPCODE_CRET_0x11
//00013218 42 6e ff f4     clr.w      (-0xc,A6)
//0001321c 2d 76 10        move.l     (0x0,A6,D1w*0x1),(-0x8,A6)
//00 ff f8
//00013222 58 41           addq.w     #0x4,D1w
//00013224 3d 41 ff f6     move.w     D1w,(-0xa,A6)
//00013228 4e 75           rts
//    LAB_0001322a                                    XREF[1]:     0001320c(j)
//0001322a 38 2e ff f4     move.w     (-0xc,A6),D4w
//0001322e 67 00 00 1a     beq.w      OPCODE_CRET_0x11
//00013232 42 6e ff f4     clr.w      (-0xc,A6)
//00013236 26 76 40 00     movea.l    (0x0,A6,D4w*0x1),A3
//0001323a 58 44           addq.w     #0x4,D4w
//0001323c 4e 75           rts

}

static void cprotect() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void casleep() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cclipping() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cswitching() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwlive() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cunload() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwakeup() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csleep() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void clive() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    alis._DAT_000195fa = 0;
    alis._DAT_000195fc = 0;
    alis._DAT_000195fe = 0;
    
    u16 d2 = script_read16();
    
    u8 * tmp = alis.bssChunk1;
    alis.bssChunk1 = alis.bssChunk3;
    alis.bssChunk3 = tmp;
    readexec_storename();
}

static void ckill() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cstop() {
    // debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    alis.script->running = 0;
}

static void cstopret() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cexit() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cload() {
    // get script ID
    u16 id = script_read16();
    if(id == 0) {
        // main script !
        readexec_opername_swap();
        
        // TODO: init some stuff ?
        
        // reset vm ?
    }
    else {
        // not main script, depack and load into vm
        u8 name[kNameMaxLen] = {0};
        script_read_until_zero(name);
        char * fpath = get_full_path((char *)name, alis.platform.path);
        sAlisScript * script = script_load((char *)fpath);
        alis.scriptID = id;
        alis.scripts[alis.scriptID] = script;
        //sAlisScript * script = script_load(fpath, 0x32047);
        free(fpath);
        //alis.script = script;
    }
}



// =============================================================================
void FUN_00013d82() {
//    clr.w      ($4,A0,D0)
//    move.w     (W_000195a0).l,D1
//
//    bne.w      __not_zero
//    move.w     D0,(W_000195a0).l
//    rts
//__not_zero:
//    move.w     D1,D2
//    move.w     ($4,A0,D2),D1
//    bne.w      __not_zero
//    move.w     D0,($4,A0,D2)
//    rts
}
// =============================================================================
void FUN_00013dda() {
//    move.b         ($21,A0),D0
//    ext.w          D0
//    move.b         ($25,A0),D1
//    ext.w          D1
//    muls.w         D1,D0
//    move.b         ($24,A0),D2
//    ext.w          D2
//    move.b         ($22,A0),D3
//    ext.w          D3
//    muls.w         D3,D2
//    sub.w          D2,D0
//    move.b         D0,($26,A0)
//    move.b         ($22,A0),D0
//    ext.w          D0
//    move.b         ($23,A0),D1
//    ext.w          D1
//    muls.w         D1,D0
//    move.b         ($25,A0),D2
//    ext.w          D2
//    move.b         ($20,A0),D3
//    ext.w          D3
//    muls.w         D3,D2
//    sub.w          D2,D0
//    move.b         D0,($27,A0)
//    move.b         ($20,A0),D0
//    ext.w          D0
//    move.b         ($24,A0),D1
//    ext.w          D1
//    muls.w         D1,D0
//    move.b         ($23,A0),D2
//    ext.w          D2
//    move.b         ($21,A0),D3
//    ext.w          D3
//    muls.w         D3,D2
//    sub.w          D2,D0
//    move.b         D0,($28,A0)
//    rts
//    move.b         ($21,A0),D0
//    ext.w          D0
//    move.b         ($25,A0),D1
//    ext.w          D1
//    muls.w         D1,D0
//    move.b         ($24,A0),D2
//    ext.w          D2
//    move.b         ($22,A0),D3
//    ext.w          D3
//    muls.w         D3,D2
}


// reads 35 bytes
static void cdefsc() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    /*
     ; code address: $139ca
     opcode_cdefsc:
         move.b         (A3)+,D0
         asl.w          #$8,D0
         move.b         (A3)+,D0
    */
    u16 offset = script_read16();
    /*
         movea.l        (ADDR_VSTACK).l,A0 ; correspond à a6 !!! / A0 vaut $224f0, contient $22690 soit vstack
     */
    u8 * ram = vram_ptr(alis.vram, 0);
    /*
         bset.b         #$6,(A0,D0)
     */
    *(ram + offset) &= ALIS_BIT_6;
    /*
         move.b         (A3)+,($1,A0,D0)
     */
    *(ram + offset + 1) = script_read8();
    
    /*
         moveq          #$1f,D1
         lea            ($6,A0,D0),A1

     __loop32:
         move.b         (A3)+,(A1)+
         dbf            D1,__loop32
    */
    u8 counter = 32;
    u8 * ptr = ram + offset + 6;
    while(counter--) {
        *ptr++ = script_read8();
    }
 
    /*
         movea.l        (ADDR_SCRIPT_0001955e).l,A1 ; qque part dans le script
         
         move.w         (W_00019562).l,D1
         
         beq.w          __error10
         move.w         ($4,A1,D1),(W_00019562).l
         
         
         move.w         D1,($2,A0,D0)
         clr.w          ($6,A1,D1)
         clr.w          ($4,A0,D0)
         move.b         ($1,A0,D0),($1,A1,D1)
         
         move.w         ($e,A0,D0),D2
         andi.w         #-$10,D2
         move.w         D2,($c,A1,D1)
         move.w         ($10,A0,D0),($e,A1,D1)
         
         move.w         #$7fff,($10,A1,D1)
         
         move.w         ($e,A0,D0),D2
         add.w          ($12,A0,D0),D2
         ori.w          #$f,D2
         move.w         D2,($16,A1,D1)
         move.w         ($10,A0,D0),D2
         add.w          ($14,A0,D0),D2
         move.w         D2,($18,A1,D1)
         clr.w          ($2a,A0,D0)
         clr.w          ($2c,A0,D0)
         clr.w          ($2e,A0,D0)
         bsr.w          FUN_00013d82
         lea            ($0,A0,D0),A0
         bsr.w          FUN_00013dda
         rts
         
     __error10:
         move.l     #$a,D0

     forever:
         bra forever
     */
}

static void cscreen() {
    u16 pos = script_read16();
    if (pos != alis._a6_minus_16) {
        alis._a6_minus_16 = pos;
    }
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cputnat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
//    **************************************************************
//    *                          FUNCTION                          *
//    **************************************************************
//    undefined OPCODE_CPUTNAT_0x49()
//undefined         D0b:1          <RETURN>
//    OPCODE_CPUTNAT_0x49
//00013e82 42 39 00        clr.b      (DAT_0001959f).l
//01 95 9f
//00013e88 13 ee ff        move.b     (-0x3,A6),(DAT_0001959c).l
//fd 00 01
//95 9c
//    LAB_00013e90                                    XREF[3]:     00013ef0(j), 00013f18(j),
//                                                                 00013f32(j)
//00013e90 61 00 36 da     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00013e94 33 c7 00        move.w     D7w,(DAT_00019588).l
//01 95 88
//00013e9a 61 00 36 d0     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00013e9e 33 c7 00        move.w     D7w,(DAT_0001958a).l
//01 95 8a
//00013ea4 61 00 36 c6     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00013ea8 33 c7 00        move.w     D7w,(DAT_0001958c).l
//01 95 8c
//00013eae 61 00 36 bc     bsr.w      FUN_READEXEC_OPERNAME_SAVE_D7                    undefined FUN_READEXEC_OPERNAME_
//00013eb2 61 00 36 ac     bsr.w      FUN_READEXEC_OPERNAME_PUSH_D7                    undefined FUN_READEXEC_OPERNAME_
//00013eb6 13 c6 00        move.b     D6b,(DAT_00019594).l
//01 95 94
//00013ebc 4e f9 00        jmp        FUN_00013f50.l                                   undefined FUN_00013f50()
//01 3f 50
//    -- Flow Override: CALL_RETURN (CALL_TERMINATOR)
    readexec_opername_saveD7();
    readexec_opername_saveD7();
    readexec_opername_saveD7();
    readexec_opername_saveD7();
    readexec_opername_saveD7();
}

static void cerase() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cerasen() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cset() {
    // log_debug("STUBBED");
//    OPCODE_CSET_0x4c
//00014652 61 00 2f 1a     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//00014656 3d 47 00 00     move.w     D7w,(0x0,A6)
//0001465a 61 00 2f 12     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//0001465e 3d 47 00 02     move.w     D7w,(0x2,A6)
//00014662 61 00 2f 0a     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//00014666 3d 47 00 04     move.w     D7w,(0x4,A6)
//0001466a 4e 75           rts
    readexec_opername();
    vram_write16(alis.vram, 0, alis.varD7);
    readexec_opername();
    vram_write16(alis.vram, 2, alis.varD7);
    readexec_opername();
    vram_write16(alis.vram, 4, alis.varD7);
}

static void cmov() {
    // log_debug("STUBBED");
//    OPCODE_CMOV_0x4d
//0001466c 61 00 2f 00     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//00014670 df 6e 00 00     add.w      D7w,(0x0,A6)
//00014674 61 00 2e f8     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//00014678 df 6e 00 02     add.w      D7w,(0x2,A6)
//0001467c 61 00 2e f0     bsr.w      FUN_READEXEC_OPERNAME                            undefined FUN_READEXEC_OPERNAME()
//00014680 df 6e 00 04     add.w      D7w,(0x4,A6)
//00014684 4e 75           rts
    readexec_opername();
    vram_add16(alis.vram, 0, alis.varD7);
    readexec_opername();
    vram_add16(alis.vram, 2, alis.varD7);
    readexec_opername();
    vram_add16(alis.vram, 4, alis.varD7);
}

static void copensc() {
//    **************************************************************
//    *                          FUNCTION                          *
//    **************************************************************
//    undefined OPCODE_COPENSC_0x4e()
//undefined         D0b:1          <RETURN>
//    OPCODE_COPENSC_0x4e
//00013d4c 10 1b           move.b     (A3)+,D0b
//00013d4e e1 40           asl.w      #0x8,D0w
//00013d50 10 1b           move.b     (A3)+,D0b
//00013d52 20 79 00        movea.l    (ADDR_VSTACK).l,A0
//01 95 7c
//00013d58 08 b0 00        bclr.b     0x6,(0x0,A0,D0w*0x1)
//06 00 00
//00013d5e 08 f0 00        bset.b     0x7,(0x0,A0,D0w*0x1)
//07 00 00
//00013d64 61 00 00 42     bsr.w      FUN_00013da8                                     undefined FUN_00013da8()
//00013d68 61 00 00 18     bsr.w      FUN_00013d82                                     undefined FUN_00013d82()
//00013d6c 4e 75           rts
    u16 id = script_read16();
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cclosesc() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cerasall() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cforme() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdelforme() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctstset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cftstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cftstset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csuccent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpredent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cnearent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cneartyp() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cnearmat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cviewent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cviewtyp() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cviewmat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void corient() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void crstent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csend() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscanclr() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscanon() {
    alis.vram->status.scan = 0;
}

static void cscanoff() {
    alis.vram->status.scan = 1;
    cscanclr();
}

static void cinteron() {
    alis.vram->status.inter = 0;
}

static void cinteroff() {
    alis.vram->status.inter = 1;
}

static void callentity() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpalette() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdefcolor() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctiming() {
    readexec_opername();
    alis._ctiming = (u8)(alis.varD7 & 0xff);
}

static void czap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cexplode() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cding() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cnoise() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cinitab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfopen() {
    u16 id = 0;
    if(*alis.script->pc == 0xff) {
//        ++(alis.script->pc);
        script_jump(1);
        readexec_opername_swap();
        readexec_opername();
    }
    else {
        char path[kPathMaxLen] = {0};
        strcpy(path, alis.platform.path);
        script_read_until_zero((u8 *)(path + strlen(alis.platform.path)));
        id = script_read16();
        alis.fp = sys_fopen((char *)path);
        if(alis.fp == NULL) {
            alis_error(ALIS_ERR_FOPEN, path);
        }
    }
}

static void cfclose() {
    if(sys_fclose(alis.fp) < 0) {
        alis_error(ALIS_ERR_FCLOSE);
    }
}

static void cfcreat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfdel() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfreadv() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfwritev() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfwritei() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfreadb() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfwriteb() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cplot() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdraw() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cbox() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cboxf() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cink() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpmove() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpmode() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpicture() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxyscroll() {
    readexec_opername();
    readexec_opername();
}

static void clinking() {
    readexec_opername();
    vram_write16(alis.vram, 0xffd6, alis.varD7);
}

static void cmouson() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmousoff() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmouse() {
    alis.mouse = sys_get_mouse();
    readexec_storename();
}

static void cdefmouse() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csetmouse() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdefvect() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csetvect() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void capproach() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cescape() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvtstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvftstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvmov() {
//    OPCODE_CVMOV_0x90
//00014686 10 2e 00 09     move.b     (0x9,A6),D0b
//0001468a 48 80           ext.w      D0w
//0001468c d1 6e 00 00     add.w      D0w,(0x0,A6)
//00014690 10 2e 00 0a     move.b     (0xa,A6),D0b
//00014694 48 80           ext.w      D0w
//00014696 d1 6e 00 02     add.w      D0w,(0x2,A6)
//0001469a 10 2e 00 0b     move.b     (0xb,A6),D0b
//0001469e 48 80           ext.w      D0w
//000146a0 d1 6e 00 04     add.w      D0w,(0x4,A6)
//000146a4 4e 75           rts
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdefworld() {
//    OPCODE_CDEFWORLD_0x91
//000173f0 10 1b           move.b     (A3)+,D0b
//000173f2 e1 40           asl.w      #0x8,D0w
//000173f4 10 1b           move.b     (A3)+,D0b
//000173f6 32 3c 00 05     move.w     #0x5,D1w
//    LAB_000173fa                                    XREF[1]:     000173fe(j)
//000173fa 1d 9b 00 00     move.b     (A3)+,(0x0,A6,D0w*0x1)
//000173fe 51 c9 ff fa     dbf        D1w,LAB_000173fa
//00017402 4e 75           rts
    u16 offset = script_read16();
    u8 counter = 5;
    while(counter--) {
        vram_write8(alis.vram, offset, script_read8());
    }
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cworld() {
//    OPCODE_CWORLD_0x92
//00017404 1d 5b ff de     move.b     (A3)+,(0xFFDE,A6)
//00017408 1d 5b ff df     move.b     (A3)+,(0xFFDF,A6)
//0001740c 4e 75           rts
    vram_write8(alis.vram, 0xffde, script_read8());
    vram_write8(alis.vram, 0xffdf, script_read8());
}

static void cfindmat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfindtyp() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmusic() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdelmusic() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ccadence() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csetvolum() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxinv() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxinvon() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxinvoff() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void clistent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csound() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmsound() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void credon() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void credoff() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdelsound() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwtstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwftstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctstform() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cxputat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmputat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmxput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmxputat() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmmusic() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmforme() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csettime() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cgettime() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvinput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csinput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void crunfilm() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvpicprint() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cspicprint() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cvputprint() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csputprint() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfont() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpaper() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctoblack() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
    readexec_opername_saveD7();
}

static void cmovcolor() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctopalet() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cnumput() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscheart() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscpos() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscsize() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cschoriz() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscvertic() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscreduce() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscscale() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void creducing() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscdump() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfindcla() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cnearcla() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cviewcla() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cinstru() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cminstru() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cordspr() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void calign() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cbackstar() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cstarring() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cengine() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cautobase() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cquality() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void chsprite() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cselpalet() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void clinepalet() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cautomode() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cautofile() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ccancel() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ccancall() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ccancen() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cblast() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscback() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscrolpage() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cmatent() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cshrink() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdefmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csetmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cputmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csavepal() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void csczoom() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void ctexmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void calloctab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfreetab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscantab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cneartab() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscsun() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cdarkpal() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscdark() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void caset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void camov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscaset() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscamov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscfollow() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscview() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cfilm() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cwalkmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void catstmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cavtstmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cavmov() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void caim() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cpointpix() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cchartmap() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void cscsky() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}

static void czoom() {
    debug(EDebugWarning, "\n%s STUBBED\n", __FUNCTION__);
}


// ============================================================================
#pragma mark - Unimplemented opcodes
// ============================================================================
static void cnul()      {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cesc1()     {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cesc2()     {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cesc3()     {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cclock()    {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cbreakpt()  {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cmul()      {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cdiv()      {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjsrabs()   {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjmpabs()   {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjsrind16() {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjsrind24() {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjmpind16() {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}
static void cjmpind24() {
    debug(EDebugVerbose, "%s: N/I", __FUNCTION__);
}


// ============================================================================
#pragma mark - Flow control - Subroutines
// ============================================================================
static void cret() {
    // return from subroutine (cjsr)
    // retrieve return address **OFFSET** from virtual stack
    u32 pc_offset = vram_pop32(alis.vram);
    alis.script->pc = alis.script->pc_org + pc_offset;
}

static void cjsr(u32 offset) {

    // save return **OFFSET**, not ADDRESS
    // TODO: dans la vm originale on empile la 'vraie' adresse du PC en 32 bits
    // Là j'ai pas la place (on est en 64 bits), donc j'empile l'offset
    // TODO: peut-on stocker une adresse de retour *virtuelle* ?
    // Sinon ça oblige à créer une pile virtuelle d'adresses
    //   dont la taille est platform-dependent
    u32 pc_offset = (u32)(alis.script->pc - alis.script->pc_org);
    vram_push32(alis.vram, pc_offset);
    script_jump(offset);
}

static void cjsr8() {
    // read byte, extend sign
    u16 offset = script_read8ext16();
    cjsr(offset);
}

static void cjsr16() {
    u16 offset = script_read16();
    cjsr(offset);
}

static void cjsr24() {
    u32 offset = script_read24();
    cjsr(offset);
}


// ============================================================================
#pragma mark - Flow control - Jump
// ============================================================================
static void cjmp(u32 offset) {
//    alis.pc += offset;
    script_jump(offset);
}

static void cjmp8() {
    cjmp(script_read8ext16());
}

static void cjmp16() {
    cjmp(script_read16());
}

static void cjmp24() {
    cjmp(script_read24());
}


// ============================================================================
#pragma mark - Flow control - Branch if zero
// ============================================================================
static void cbz(u32 offset) {
    if(alis.varD7 == 0) {
//        alis.pc += offset;
        script_jump(offset);
    }
}

static void cbz8() {
    cbz(script_read8ext16());
}

static void cbz16() {
    cbz(script_read16());
}
static void cbz24() {
    cbz(script_read24());
}


// ============================================================================
#pragma mark - Flow control - Branch if non-zero
// ============================================================================
static void cbnz(s32 offset) {
    if(alis.varD7 != 0) {
//        alis.pc += offset;
        script_jump(offset);
    }
}
static void cbnz8() {
    cbnz(script_read8ext16());
}

static void cbnz16() {
    cbnz(script_read16());
}

static void cbnz24() {
    cbnz(script_read24());
}


// ============================================================================
#pragma mark - Flow control - Branch if equal
// ============================================================================
static void cbeq(u32 offset) {
    if(alis.varD7 == alis.varD6) {
//        alis.pc += offset;
        script_jump(offset);
    }
}
static void cbeq8() {
    cbeq(script_read8ext16());
}
static void cbeq16() {
    cbeq(script_read16());
}
static void cbeq24() {
    cbeq(script_read24());
}


// ============================================================================
#pragma mark - Flow control - Branch if not equal
// ============================================================================
static void cbne(u32 offset) {
    if(alis.varD7 != alis.varD6) {
//        alis.pc += offset;
        script_jump(offset);
    }
}
static void cbne8() {
    cbne(script_read8ext16());
}
static void cbne16() {
    cbne(script_read16());
}
static void cbne24() {
    cbne(script_read24());
}


// ============================================================================
#pragma mark - Flow control - Start
// ============================================================================
static void cstart(u32 offset) {
//    OPCODE_CSTART_COMMON                            XREF[2]:     00013182(j), 00013202(j)
//0001318e 4a 39 00        tst.b      (B_CSTOPRET).l
//01 95 a3
//00013194 66 00 00 42     bne.w      LAB_000131d8
//00013198 4a 6e ff f4     tst.w      (-0xc,A6)
//0001319c 66 00 00 20     bne.w      LAB_000131be
//000131a0 32 2e ff f6     move.w     (-0xa,A6),D1w
//000131a4 59 41           subq.w     #0x4,D1w
//000131a6 3d 41 ff f4     move.w     D1w,(-0xc,A6)
//000131aa 3d 41 ff f6     move.w     D1w,(-0xa,A6)
//000131ae 2d ae ff        move.l     (-0x8,A6),(0x0,A6,D1w*0x1)
//f8 10 00
//000131b4 d0 8b           add.l      A3,D0
//000131b6 2d 40 ff f8     move.l     D0,(-0x8,A6)
//000131ba 60 00 00 0e     bra.w      LAB_000131ca
//    LAB_000131be                                    XREF[1]:     0001319c(j)
//000131be 3d 6e ff        move.w     (-0xc,A6),(-0xa,A6)
//f4 ff f6
//000131c4 d0 8b           add.l      A3,D0
//000131c6 2d 40 ff f8     move.l     D0,(-0x8,A6)
//    LAB_000131ca                                    XREF[1]:     000131ba(j)
//000131ca 1d 7c 00        move.b     #0x1,(-0x4,A6)
//01 ff fc
//000131d0 1d 7c 00        move.b     #0x1,(0xFFFF,A6)
//01 ff ff
//000131d6 4e 75           rts

    debug(EDebugWarning, "%s STUBBED", __FUNCTION__);
}
static void cstart8() {
    // read byte, extend sign to word, then to long
    cstart(script_read8ext32());
}

static void cstart16() {
    cstart(script_read16ext32());
}

static void cstart24() {
    cstart(script_read24());
}


// ============================================================================
#pragma mark - Opcode pointer table (256 values)
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
    DECL_OPCODE(0x18, cbeq8,        "branch if equal with 8-bit offset"),
    DECL_OPCODE(0x19, cbeq16,       "branch if equal with 16-bit offset"),
    DECL_OPCODE(0x1a, cbeq24,       "branch if equal with 24-bit offset"),
    DECL_OPCODE(0x1b, cbne8,        "branch if non-equal with 8-bit offset"),
    DECL_OPCODE(0x1c, cbne16,       "branch if non-equal with 16-bit offset"),
    DECL_OPCODE(0x1d, cbne24,       "branch if non-equal with 24-bit offset"),
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
    DECL_OPCODE(0x45, cload,        "Load and depack a script, set into vm"),
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
