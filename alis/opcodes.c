//
//  opcodes.c
//  alis
//
//

#include "alis.h"
#include "alis_private.h"
#include "utils.h"

// =============================================================================
#pragma mark - Helpers
// =============================================================================
static void cstart(u32 offset) {
    // TODO: check OP_CSTART in asm source
}


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
    debug(EDebugInfo, "cvprint STUBBED\n");
}

static void csprinti() {
    debug(EDebugInfo, "csprinti STUBBED\n");
}

static void csprinta() {
    debug(EDebugInfo, "csprinta STUBBED\n");
}

static void clocate() {
    debug(EDebugInfo, "clocate STUBBED\n");
}

static void ctab() {
    debug(EDebugInfo, "ctab STUBBED\n");
}

// ???
// read x bytes
static void cdim() {

    u8 * ram = (u8 *)alis.scripts[alis.scriptID]->ram;
    
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
    debug(EDebugInfo, "crandom STUBBED\n");
}

static void cloop8() {
    u8 * pc_save = alis.pc;
    alis.pc += 1;
    alis.varD7 = 0xff;
    readexec_addname_swap();
    if(alis.varD7/* TODO: check that condition code is not zero */) {
        alis.pc = pc_save;
        alis.pc += extend_w(script_read8());
    }
}

static void cloop16() {
    u8 * pc_save = alis.pc;
    alis.pc += 2;
    alis.varD7 = 0xff;
    readexec_addname_swap();
    if(alis.varD7/* TODO: check that condition code is not zero */) {
        alis.pc = pc_save;
        alis.pc += script_read16();
    }
}

static void cloop24() {
    u8 * pc_save = alis.pc;
    alis.pc += 3;
    alis.varD7 = 0xff;
    readexec_addname_swap();
    if(alis.varD7/* TODO: check that condition code is not zero */) {
        alis.pc = pc_save;
        alis.pc += script_read24();
    }
}

static void cswitch1() {
    debug(EDebugInfo, "cswitch1 STUBBED\n");
}

static void cswitch2() {
    debug(EDebugInfo, "cswitch2 STUBBED\n");
}

static void cleave() {
    debug(EDebugInfo, "cleave STUBBED\n");
}

static void cprotect() {
    debug(EDebugInfo, "cprotect STUBBED\n");
}

static void casleep() {
    debug(EDebugInfo, "casleep STUBBED\n");
}

static void cscmov() {
    debug(EDebugInfo, "cscmov STUBBED\n");
}

static void cscset() {
    debug(EDebugInfo, "cscset STUBBED\n");
}

static void cclipping() {
    debug(EDebugInfo, "cclipping STUBBED\n");
}

static void cswitching() {
    debug(EDebugInfo, "cswitching STUBBED\n");
}

static void cwlive() {
    debug(EDebugInfo, "cwlive STUBBED\n");
}

static void cunload() {
    debug(EDebugInfo, "cunload STUBBED\n");
}

static void cwakeup() {
    debug(EDebugInfo, "cwakeup STUBBED\n");
}

static void csleep() {
    debug(EDebugInfo, "csleep STUBBED\n");
}

static void clive() {
    debug(EDebugInfo, "clive STUBBED\n");
}

static void ckill() {
    debug(EDebugInfo, "ckill STUBBED\n");
}

static void cstop() {
    debug(EDebugInfo, "cstop: STUBBED\n");
}

static void cstopret() {
    debug(EDebugInfo, "cstopret STUBBED\n");
}

static void cexit() {
    debug(EDebugInfo, "cexit STUBBED\n");
}

static void cload() {
    // get script ID
    u16 id = script_read16();
    
    // get file name
    char * name = (char *)alis.pc;
    size_t len = strlen(name);
    
    // load script into vm
    sAlisScript * script = script_load(name);
    alis.scripts[id] = script;
    alis.pc += len;
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
    u8 * ram = alis.scripts[alis.scriptID]->ram;
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
    debug(EDebugInfo, "cdefsc STUBBED\n");
}

static void cscreen() {
    debug(EDebugInfo, "cscreen STUBBED\n");
}

static void cput() {
    debug(EDebugInfo, "cput STUBBED\n");
}

static void cputnat() {
    debug(EDebugInfo, "cputnat STUBBED\n");
}

static void cerase() {
    debug(EDebugInfo, "cerase STUBBED\n");
}

static void cerasen() {
    debug(EDebugInfo, "cerasen STUBBED\n");
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
    write16(0, alis.varD7);
    readexec_opername();
    write16(2, alis.varD7);
    readexec_opername();
    write16(4, alis.varD7);
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
    add16(0, alis.varD7);
    readexec_opername();
    add16(2, alis.varD7);
    readexec_opername();
    add16(4, alis.varD7);
}

static void copensc() {
    debug(EDebugInfo, "copensc STUBBED\n");
}

static void cclosesc() {
    debug(EDebugInfo, "cclosesc STUBBED\n");
}

static void cerasall() {
    debug(EDebugInfo, "cerasall STUBBED\n");
}

static void cforme() {
    debug(EDebugInfo, "cforme STUBBED\n");
}

static void cdelforme() {
    debug(EDebugInfo, "cdelforme STUBBED\n");
}

static void ctstmov() {
    debug(EDebugInfo, "ctstmov STUBBED\n");
}

static void ctstset() {
    debug(EDebugInfo, "ctstset STUBBED\n");
}

static void cftstmov() {
    debug(EDebugInfo, "cftstmov STUBBED\n");
}

static void cftstset() {
    debug(EDebugInfo, "cftstset STUBBED\n");
}

static void csuccent() {
    debug(EDebugInfo, "csuccent STUBBED\n");
}

static void cpredent() {
    debug(EDebugInfo, "cpredent STUBBED\n");
}

static void cnearent() {
    debug(EDebugInfo, "cnearent STUBBED\n");
}

static void cneartyp() {
    debug(EDebugInfo, "cneartyp STUBBED\n");
}

static void cnearmat() {
    debug(EDebugInfo, "cnearmat STUBBED\n");
}

static void cviewent() {
    debug(EDebugInfo, "cviewent STUBBED\n");
}

static void cviewtyp() {
    debug(EDebugInfo, "cviewtyp STUBBED\n");
}

static void cviewmat() {
    debug(EDebugInfo, "cviewmat STUBBED\n");
}

static void corient() {
    debug(EDebugInfo, "corient STUBBED\n");
}

static void crstent() {
    debug(EDebugInfo, "crstent STUBBED\n");
}

static void csend() {
    debug(EDebugInfo, "csend STUBBED\n");
}

static void cscanon() {
    debug(EDebugInfo, "cscanon STUBBED\n");
}

static void cscanoff() {
    debug(EDebugInfo, "cscanoff STUBBED\n");
}

static void cinteron() {
    debug(EDebugInfo, "cinteron STUBBED\n");
}

static void cinteroff() {
    debug(EDebugInfo, "cinteroff STUBBED\n");
}

static void cscanclr() {
    debug(EDebugInfo, "cscanclr STUBBED\n");
}

static void callentity() {
    debug(EDebugInfo, "callentity STUBBED\n");
}

static void cpalette() {
    debug(EDebugInfo, "cpalette STUBBED\n");
}

static void cdefcolor() {
    debug(EDebugInfo, "cdefcolor STUBBED\n");
}

static void ctiming() {
    debug(EDebugInfo, "ctiming STUBBED\n");
}

static void czap() {
    debug(EDebugInfo, "czap STUBBED\n");
}

static void cexplode() {
    debug(EDebugInfo, "cexplode STUBBED\n");
}

static void cding() {
    debug(EDebugInfo, "cding STUBBED\n");
}

static void cnoise() {
    debug(EDebugInfo, "cnoise STUBBED\n");
}

static void cinitab() {
    debug(EDebugInfo, "cinitab STUBBED\n");
}

static void cfopen() {
    u16 id = 0;
    if(*alis.pc == 0xff) {
        ++alis.pc;
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
    debug(EDebugInfo, "cfcreat STUBBED\n");
}

static void cfdel() {
    debug(EDebugInfo, "cfdel STUBBED\n");
}

static void cfreadv() {
    debug(EDebugInfo, "cfreadv STUBBED\n");
}

static void cfwritev() {
    debug(EDebugInfo, "cfwritev STUBBED\n");
}

static void cfwritei() {
    debug(EDebugInfo, "cfwritei STUBBED\n");
}

static void cfreadb() {
    debug(EDebugInfo, "cfreadb STUBBED\n");
}

static void cfwriteb() {
    debug(EDebugInfo, "cfwriteb STUBBED\n");
}

static void cplot() {
    debug(EDebugInfo, "cplot STUBBED\n");
}

static void cdraw() {
    debug(EDebugInfo, "cdraw STUBBED\n");
}

static void cbox() {
    debug(EDebugInfo, "cbox STUBBED\n");
}

static void cboxf() {
    debug(EDebugInfo, "cboxf STUBBED\n");
}

static void cink() {
    debug(EDebugInfo, "cinf STUBBED\n");
}

static void cpset() {
    debug(EDebugInfo, "cpset STUBBED\n");
}

static void cpmove() {
    debug(EDebugInfo, "cpmove STUBBED\n");
}

static void cpmode() {
    debug(EDebugInfo, "cpmode STUBBED\n");
}

static void cpicture() {
    debug(EDebugInfo, "cpicture STUBBED\n");
}

static void cxyscroll() {
    readexec_opername();
    readexec_opername();
}

static void clinking() {
    readexec_opername();
    write16(0xffd6, alis.varD7);
}

static void cmouson() {
    debug(EDebugInfo, "cmouson STUBBED\n");
}

static void cmousoff() {
    debug(EDebugInfo, "cmousoff STUBBED\n");
}

static void cmouse() {
    alis.mouse = sys_get_mouse();
    readexec_storename();
}

static void cdefmouse() {
    debug(EDebugInfo, "cdefmouse STUBBED\n");
}

static void csetmouse() {
    debug(EDebugInfo, "csetmouse STUBBED\n");
}

static void cdefvect() {
    debug(EDebugInfo, "cdefvect STUBBED\n");
}

static void csetvect() {
    debug(EDebugInfo, "csetvect STUBBED\n");
}

static void capproach() {
    debug(EDebugInfo, "capproach STUBBED\n");
}

static void cescape() {
    debug(EDebugInfo, "cescape STUBBED\n");
}

static void cvtstmov() {
    debug(EDebugInfo, "cvtstmov STUBBED\n");
}

static void cvftstmov() {
    debug(EDebugInfo, "cvftstmov STUBBED\n");
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
    debug(EDebugInfo, "cvmov STUBBED\n");
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
        write8(offset, script_read8());
    }
    debug(EDebugInfo, "cdefworld STUBBED\n");
}

static void cworld() {
//    OPCODE_CWORLD_0x92
//00017404 1d 5b ff de     move.b     (A3)+,(0xFFDE,A6)
//00017408 1d 5b ff df     move.b     (A3)+,(0xFFDF,A6)
//0001740c 4e 75           rts
    write8(0xffde, script_read8());
    write8(0xffdf, script_read8());
}

static void cfindmat() {
    debug(EDebugInfo, "cfindmat STUBBED\n");
}

static void cfindtyp() {
    debug(EDebugInfo, "cfindtyp STUBBED\n");
}

static void cmusic() {
    debug(EDebugInfo, "cmusic STUBBED\n");
}

static void cdelmusic() {
    debug(EDebugInfo, "cdelmusic STUBBED\n");
}

static void ccadence() {
    debug(EDebugInfo, "ccadence STUBBED\n");
}

static void csetvolum() {
    debug(EDebugInfo, "csetvolum STUBBED\n");
}

static void cxinv() {
    debug(EDebugInfo, "cxinv STUBBED\n");
}

static void cxinvon() {
    debug(EDebugInfo, "cxinvon STUBBED\n");
}

static void cxinvoff() {
    debug(EDebugInfo, "cxinvoff STUBBED\n");
}

static void clistent() {
    debug(EDebugInfo, "clistent STUBBED\n");
}

static void csound() {
    debug(EDebugInfo, "csound STUBBED\n");
}

static void cmsound() {
    debug(EDebugInfo, "cmsound STUBBED\n");
}

static void credon() {
    debug(EDebugInfo, "credon STUBBED\n");
}

static void credoff() {
    debug(EDebugInfo, "credoff STUBBED\n");
}

static void cdelsound() {
    debug(EDebugInfo, "cdelsound STUBBED\n");
}

static void cwmov() {
    debug(EDebugInfo, "cwmov STUBBED\n");
}

static void cwtstmov() {
    debug(EDebugInfo, "ctstmov STUBBED\n");
}

static void cwftstmov() {
    debug(EDebugInfo, "cwftstmov STUBBED\n");
}

static void ctstform() {
    debug(EDebugInfo, "ctstform STUBBED\n");
}

static void cxput() {
    debug(EDebugInfo, "cxput STUBBED\n");
}

static void cxputat() {
    debug(EDebugInfo, "cxputat STUBBED\n");
}

static void cmput() {
    debug(EDebugInfo, "cmput STUBBED\n");
}

static void cmputat() {
    debug(EDebugInfo, "cmputat STUBBED\n");
}

static void cmxput() {
    debug(EDebugInfo, "cmxput STUBBED\n");
}

static void cmxputat() {
    debug(EDebugInfo, "cmxputat STUBBED\n");
}

static void cmmusic() {
    debug(EDebugInfo, "cmmusic STUBBED\n");
}

static void cmforme() {
    debug(EDebugInfo, "cmforme STUBBED\n");
}

static void csettime() {
    debug(EDebugInfo, "csettime STUBBED\n");
}

static void cgettime() {
    debug(EDebugInfo, "cgettime STUBBED\n");
}

static void cvinput() {
    debug(EDebugInfo, "cvinput STUBBED\n");
}

static void csinput() {
    debug(EDebugInfo, "csinput STUBBED\n");
}

static void crunfilm() {
    debug(EDebugInfo, "crunfilm STUBBED\n");
}

static void cvpicprint() {
    debug(EDebugInfo, "cvpicprint STUBBED\n");
}

static void cspicprint() {
    debug(EDebugInfo, "cspicprint STUBBED\n");
}

static void cvputprint() {
    debug(EDebugInfo, "cvputprint STUBBED\n");
}

static void csputprint() {
    debug(EDebugInfo, "csputprint STUBBED\n");
}

static void cfont() {
    debug(EDebugInfo, "cfont STUBBED\n");
}

static void cpaper() {
    debug(EDebugInfo, "cpaper STUBBED\n");
}

static void ctoblack() {
    debug(EDebugInfo, "ctoblack STUBBED\n");
}

static void cmovcolor() {
    debug(EDebugInfo, "cmovcolor STUBBED\n");
}

static void ctopalet() {
    debug(EDebugInfo, "ctopalet STUBBED\n");
}

static void cnumput() {
    debug(EDebugInfo, "cnumput STUBBED\n");
}

static void cscheart() {
    debug(EDebugInfo, "cscheart STUBBED\n");
}

static void cscpos() {
    debug(EDebugInfo, "cscpos STUBBED\n");
}

static void cscsize() {
    debug(EDebugInfo, "cscsize STUBBED\n");
}

static void cschoriz() {
    debug(EDebugInfo, "cschoriz STUBBED\n");
}

static void cscvertic() {
    debug(EDebugInfo, "cscvertic STUBBED\n");
}

static void cscreduce() {
    debug(EDebugInfo, "cscreduce STUBBED\n");
}

static void cscscale() {
    debug(EDebugInfo, "cscscale STUBBED\n");
}

static void creducing() {
    debug(EDebugInfo, "creducing STUBBED\n");
}

static void cscmap() {
    debug(EDebugInfo, "cscmap STUBBED\n");
}

static void cscdump() {
    debug(EDebugInfo, "cscdump STUBBED\n");
}

static void cfindcla() {
    debug(EDebugInfo, "cfindcla STUBBED\n");
}

static void cnearcla() {
    debug(EDebugInfo, "cnearcla STUBBED\n");
}

static void cviewcla() {
    debug(EDebugInfo, "cviewcla STUBBED\n");
}

static void cinstru() {
    debug(EDebugInfo, "cinstru STUBBED\n");
}

static void cminstru() {
    debug(EDebugInfo, "cminstru STUBBED\n");
}

static void cordspr() {
    debug(EDebugInfo, "cordspr STUBBED\n");
}

static void calign() {
    debug(EDebugInfo, "calign STUBBED\n");
}

static void cbackstar() {
    debug(EDebugInfo, "cbackstar STUBBED\n");
}

static void cstarring() {
    debug(EDebugInfo, "cstarring STUBBED\n");
}

static void cengine() {
    debug(EDebugInfo, "cengine STUBBED\n");
}

static void cautobase() {
    debug(EDebugInfo, "cautobase STUBBED\n");
}

static void cquality() {
    debug(EDebugInfo, "cquality STUBBED\n");
}

static void chsprite() {
    debug(EDebugInfo, "chsprite STUBBED\n");
}

static void cselpalet() {
    debug(EDebugInfo, "cselpalet STUBBED\n");
}

static void clinepalet() {
    debug(EDebugInfo, "clinepalet STUBBED\n");
}

static void cautomode() {
    debug(EDebugInfo, "cautomode STUBBED\n");
}

static void cautofile() {
    debug(EDebugInfo, "cautofile STUBBED\n");
}

static void ccancel() {
    debug(EDebugInfo, "ccancel STUBBED\n");
}

static void ccancall() {
    debug(EDebugInfo, "ccancall STUBBED\n");
}

static void ccancen() {
    debug(EDebugInfo, "ccancen STUBBED\n");
}

static void cblast() {
    debug(EDebugInfo, "cblast STUBBED\n");
}

static void cscback() {
    debug(EDebugInfo, "cscback STUBBED\n");
}

static void cscrolpage() {
    debug(EDebugInfo, "cscrolpage STUBBED\n");
}

static void cmatent() {
    debug(EDebugInfo, "cmatent STUBBED\n");
}

static void cshrink() {
    debug(EDebugInfo, "cshrink STUBBED\n");
}

static void cdefmap() {
    debug(EDebugInfo, "cdefmap STUBBED\n");
}

static void csetmap() {
    debug(EDebugInfo, "csetmap STUBBED\n");
}

static void cputmap() {
    debug(EDebugInfo, "cputmap STUBBED\n");
}

static void csavepal() {
    debug(EDebugInfo, "csavepal STUBBED\n");
}

static void csczoom() {
    debug(EDebugInfo, "csczoom STUBBED\n");
}

static void ctexmap() {
    debug(EDebugInfo, "ctexmap STUBBED\n");
}

static void calloctab() {
    debug(EDebugInfo, "calloctab STUBBED\n");
}

static void cfreetab() {
    debug(EDebugInfo, "cfreetab STUBBED\n");
}

static void cscantab() {
    debug(EDebugInfo, "cscantab STUBBED\n");
}

static void cneartab() {
    debug(EDebugInfo, "cneartab STUBBED\n");
}

static void cscsun() {
    debug(EDebugInfo, "cscsun STUBBED\n");
}

static void cdarkpal() {
    debug(EDebugInfo, "cdarkpal STUBBED\n");
}

static void cscdark() {
    debug(EDebugInfo, "cscdark STUBBED\n");
}

static void caset() {
    debug(EDebugInfo, "caset STUBBED\n");
}

static void camov() {
    debug(EDebugInfo, "camov STUBBED\n");
}

static void cscaset() {
    debug(EDebugInfo, "cscaset STUBBED\n");
}

static void cscamov() {
    debug(EDebugInfo, "cscamov STUBBED\n");
}

static void cscfollow() {
    debug(EDebugInfo, "cscfollow STUBBED\n");
}

static void cscview() {
    debug(EDebugInfo, "cscview STUBBED\n");
}

static void cfilm() {
    debug(EDebugInfo, "cfilm STUBBED\n");
}

static void cwalkmap() {
    debug(EDebugInfo, "cwalkmap STUBBED\n");
}

static void catstmap() {
    debug(EDebugInfo, "catstmap STUBBED\n");
}

static void cavtstmov() {
    debug(EDebugInfo, "cavtstmov STUBBED\n");
}

static void cavmov() {
    debug(EDebugInfo, "cavmov STUBBED\n");
}

static void caim() {
    debug(EDebugInfo, "caim STUBBED\n");
}

static void cpointpix() {
    debug(EDebugInfo, "cpointpix STUBBED\n");
}

static void cchartmap() {
    debug(EDebugInfo, "cchartmap STUBBED\n");
}

static void cscsky() {
    debug(EDebugInfo, "cscsky STUBBED\n");
}

static void czoom() {
    debug(EDebugInfo, "czoom STUBBED\n");
}


// ============================================================================
#pragma mark - Empty opcodes
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
#pragma mark - Flow control opcodes
// ============================================================================
static void cret() {
    // return from subroutine (cjsr)
    // retrieve return address offset from virtual stack
//    sAlisScript * script = alis.scripts[alis.scriptID];
//    u32 pc_offset = *(u32 *)(script->vram + script->vstack_offset);
//    alis.pc = alis.pc_org + pc_offset;
//
//    script->vstack_offset += 4;
    
    // retrieve return address **OFFSET** from virtual stack
    u32 pc_offset = pop32();
    alis.pc = alis.pc_org + pc_offset;
}

static void cjsr(u32 offset) {

    // save return **OFFSET**, not ADDRESS
    // TODO: dans la vm originale on empile la 'vraie' adresse du PC en 32 bits
    // Là j'ai pas la place (on est en 64 bits), donc j'empile l'offset
    // TODO: peut-on stocker une adresse de retour *virtuelle* ?
    // Sinon ça oblige à créer une pile virtuelle d'adresses
    //   dont la taille est platform-dependent
//    sAlisScript * script = alis.scripts[alis.scriptID];

//    script->vstack_offset -= 4;
    
    u32 pc_offset = (u32)(alis.pc - alis.pc_org);
    push32(pc_offset);
    //*(u32 *)(script->vram + script->vstack_offset) = pc_offset;
    
    // jump
    alis.pc += offset;
}

static void cjsr8() {
    // read byte, extend sign
    u16 offset = extend_w(script_read8());
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

static void cjmp8() {
    u16 offset = extend_w(script_read8());
    alis.pc += offset;
}

static void cjmp16() {
    u16 offset = script_read16();
    alis.pc += offset;
}

static void cjmp24() {
    u32 offset = script_read24();
    alis.pc += offset;
}

static void cbz8() {
    u16 offset = script_read8();
    if(alis.varD7 == 0) {
        offset = extend_w(script_read8());
        alis.pc += offset;
    }
}

static void cbz16() {
    u16 offset = script_read16();
    if(alis.varD7 == 0) {
        alis.pc += offset;
    }
}
static void cbz24() {
    u32 offset = script_read24();
    if(alis.varD7 == 0) {
        alis.pc += offset;
    }
}

static void cbnz8() {
    u16 offset = script_read8();
    if(alis.varD7) {
        offset = extend_w(script_read8());
        alis.pc += offset;
    }
}

static void cbnz16() {
    u16 offset = script_read16();
    if(alis.varD7) {
        alis.pc += offset;
    }
}

static void cbnz24() {
    u32 offset = script_read24();
    if(alis.varD7) {
        alis.pc += offset;
    }
}
static void cbeq8() {
    u16 offset = script_read8();
    if(alis.varD7 == alis.varD6) {
        offset = extend_w(script_read8());
        alis.pc += offset;
    }
}
static void cbeq16() {
    u16 offset = script_read16();
    if(alis.varD7 == alis.varD6) {
        alis.pc += offset;
    }
}
static void cbeq24() {
    u32 offset = script_read24();
    if(alis.varD7 == alis.varD6) {
        alis.pc += offset;
    }
}
static void cbne8() {
    u16 offset = script_read8();
    if(alis.varD7 != alis.varD6) {
        offset = extend_w(script_read8());
        alis.pc += offset;
    }
}
static void cbne16() {
    u16 offset = script_read16();
    if(alis.varD7 != alis.varD6) {
        alis.pc += offset;
    }
}
static void cbne24() {
    u32 offset = script_read24();
    if(alis.varD7 != alis.varD6) {
        alis.pc += offset;
    }
}

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
