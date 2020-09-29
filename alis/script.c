//
//  script.c
//  alis
//

#include "alis.h"
#include "asm.h"
#include "debug.h"
#include "platform.h"
#include "script.h"
#include "utils.h"


static uint8_t * p_depak = NULL;
static uint8_t * p_depak_end = NULL;
static uint8_t * p_pak = NULL;
static uint8_t * p_pak_end = NULL;
static uint8_t * p_dic;


// =============================================================================
// MARK: - Depacker
// =============================================================================

// byte 0 -> magic
// byte 1..3 -> depacked size (24 bits)
#define HEADER_MAGIC_LEN_SZ (sizeof(uint32_t))
// byte 4..5 -> main script if zero
#define HEADER_CHECK_SZ     (sizeof(uint16_t))
// if main: byte 6..21 -> main header
#define HEADER_MAIN_SZ      kMainScriptHeaderLen
// if main: byte 22..29 -> dic
// if not main: byte 6..13 -> dic
#define HEADER_DIC_SZ       (2 * sizeof(uint32_t))

// TODO: valid only for big endian
int is_packed(uint8_t * pak_buffer) {
    return (pak_buffer[0] & 0xf0) == 0xa0;
}

uint32_t get_depacked_size(uint8_t * pak_buffer) {
    return (pak_buffer[1] << 16) + (pak_buffer[2] << 8) + pak_buffer[3];
}

int is_main(uint8_t * pak_buffer) {
    return !((pak_buffer[HEADER_MAGIC_LEN_SZ] << 8) + pak_buffer[HEADER_MAGIC_LEN_SZ + 1]);
}


void depak_11() {
//    printf("depak_11 ($163a8)\n");
    ADDREG_B(d0, d7);               // ADD.B     D0,D7
    CLRREG_W(d5);                      // CLR.W     D5
    ROLREG_L(d7, d5);               // ROL.L     D7,D5
    SWAP(d5);                       // SWAP      D5
//    if(p_pak > p_pak_end) {         // CMPA.L    A4,A0
//        get_moar_data(); // BGE       _DEPACK_GET_MORE_DATA ; read 32k bytes
//    }

// _DEPACK_12:
    uint16_t w = *p_pak;
    w <<= 8;
    w += *(p_pak + 1);
//    printf("depak11: read word 0x%x at address 0x%x\n", w, (uint32_t)p_pak);
    p_pak += 2;
    MOVE_W(w, d5);                  // MOVE.W    (A0)+,D5
//    MOVE(W, 0, p_pak++, d5)

    SWAP(d5);                       // SWAP      D5

    SUBREG_B(d7, d0);               // SUB.B     D7,D0
    MOVEQ(16, d7);                  // MOVEQ     #$10,D7
    ROLREG_L(d0, d5);               // ROL.L     D0,D5

    SUBREG_B(d0, d7);               // SUB.B     D0,D7
}


void depak_2() {
//    printf("depak_2 ($1639e)\n");
    SUBREG_B(d0, d7);               // SUB.B     D0,D7
    if((int8_t)BYTE(d7) < 0) {      // BMI.S     _DEPACK_11
        depak_11();
    }
    else {
        CLRREG_W(d5);                      // CLR.W     D5
        ROLREG_L(d0, d5);               // ROL.L     D0,D5
    }
}


void depak(uint8_t * aPakBuffer, // A0
           uint8_t * aDepakBuffer, // A1 -> pointe sur byte courant, A2 pointe sur dernier byte
           size_t aPakSize,
           size_t aDepakSize, // D1
           uint8_t * aDic) { // A5

//    printf("DEPACK: unpacking...\n");
//    printf("PAK buffer start: 0x%08x\n", (uint32_t) aPakBuffer);
//    printf("PAK buffer size: %ld\n", aPakSize);
//    printf("PAK buffer end: 0x%08x\n", (uint32_t)(aPakBuffer + aPakSize));
//    printf("DEPAK buffer start: 0x%08x\n", (uint32_t)aDepakBuffer);
//    printf("DEPAK buffer size: %ld\n", aDepakSize);
//    printf("DEPAK buffer end: 0x%08x\n", (uint32_t)(aDepakBuffer + aDepakSize));

    int16_t offset = 0;
    uint8_t tmp_b = 0;

    p_depak = aDepakBuffer; // A1
    p_depak_end = aDepakBuffer + aDepakSize - 1; // A2
    p_pak = aPakBuffer; // A0
    p_pak_end = aPakBuffer + aPakSize; // A4
    p_dic = aDic;

    CLRREG_W(d7);

_depak_start:
//    printf("depak_start ($1632e)\n");
    if(p_depak > p_depak_end) {     // CMPA.L    A2,A1
        goto _depak_end;            // BGT       FN_DEPACK_END ; si a2 (adresse fin decrunch) > a1 (adresse debut decrunch) alors fin
    }
    MOVEQ(1, d0);                   // MOVEQ     #1,D0
    depak_2();                      // BSR.S     _DEPACK_2
    if(BYTE(d5) == 0) {             // TST.B     D5
        goto _depak_3;              // BEQ.S     _DEPACK_3
    }
    MOVEQ(0, d2);                   // MOVEQ     #0,D2

_depak_4:
//    printf("depak_4 ($1633e)\n");
    MOVEQ(2, d0);                   // MOVEQ     #2,D0
    depak_2();                      // BSR.S     _DEPACK_2
    ADDREG_W(d5, d2);               // ADD.W     D5,D2
    if(WORD(d5) == 3) {             // CMP.W     #3,D5
        goto _depak_4;              // BEQ.S     _DEPACK_4
    }

_depak_5:
//    printf("depak_5 ($1634a)\n");
    MOVEQ(8, d0);                   // MOVEQ     #8,D0
    depak_2();                      // BSR.S     _DEPACK_2
    *p_depak = BYTE(d5);            // MOVE.B    D5,(A1)+      ; ecriture d'un octet depack :)

//    printf("depak5: wrote %uth byte (0x%02x) at address 0x%08x\n", depak_counter++, BYTE(d5), (uint32_t)p_depak);

    p_depak++;
    SUB_W(1, d2);
    if((int16_t)WORD(d2) >= 0) {             // DBF       D2,_DEPACK_5
        goto _depak_5;
    }

    if(p_depak > p_depak_end) {     // CMPA.L    A2,A1
        goto _depak_end;            // BGT       FN_DEPACK_END ; si a2 (adresse fin decrunch) > a1 (adresse debut decrunch) alors fin
    }

_depak_3:
//    printf("depak_3 ($1635a)\n");
    MOVEQ(3, d0);                   // MOVEQ     #3,D0
    depak_2();
    CLRREG_W(d0);                      // CLR.W     D0

//    printf("Dic: byte %d is 0x%02x\n", WORD(d5), p_dic[WORD(d5)]);
    MOVE_B(p_dic[WORD(d5)], d0);    // MOVE.B    0(A5,D5.W),D0

    ANDI_W(3, d5);                  // ANDI.W    #3,D5
    if(WORD(d5) == 0) {
        goto _depak_7;              // BEQ       _DEPACK_7
    }
//    MOVEREG_W(d5, d2);              // MOVE.W    D5,D2
    MOVE(W, 0, d5, d2);

    depak_2();                      // BSR.S     _DEPACK_2

_depak_8:
//    printf("depak_8 ($1636e)\n");
    NEG_W(d5);                      // NEG.W     D5

_depak_9:

    // MOVE.B    -1(A1,D5.W),(A1)+ ; ecriture d'un octet depack :)
    offset = WORD(d5) * -1;
    offset++;
    tmp_b = *(p_depak - offset);
    *p_depak = tmp_b;
//    printf("depak9: wrote %uth byte (0x%02x) at address 0x%08x\n", depak_counter++, tmp_b, (uint32_t)p_depak);
    p_depak++;


    SUB_W(1, d2);
    if((int16_t)WORD(d2) >= 0) {    // DBF       D2,_DEPACK_9
        goto _depak_9;
    }
    goto _depak_start;              // BRA       _DEPACK_START

_depak_7:
//    printf("depak_7\n");
    depak_2();                      // BSR       _DEPACK_2
    // MOVEREG_W(d5, d3);              // MOVE.W    D5,D3
    MOVE(W, 0, d5, d3);

    CLRREG_W(d2);                      // CLR.W     D2

_depak_10:
//    printf("depak_10\n");
    MOVEQ(3, d0);                   // MOVEQ     #3,D0
    depak_2();                      // BSR.S     _DEPACK_6

    ADDREG_W(d5, d2);               // ADD.W     D5,D2
    if(WORD(d5) == 7) {             // CMP.W     #7,D5
        goto _depak_10;             // BEQ.S     _DEPACK_10
    }

//    MOVEREG_W(d3, d5);              // MOVE.W    D3,D5
    MOVE(W, 0, d3, d5);

    ADDQ_W(4, d2);                  // ADDQ.W    #4,D2

    goto _depak_8;                  // BRA.S     _DEPACK_8

_depak_end:
//    printf("depak_end\n");
    return;
}


// =============================================================================
// MARK: - Script API
// =============================================================================

/*
 PACKED SCRIPT FILE FORMAT
 byte(s)    len     role
 -------------------------------------------------------------------------------
 0          1       if high nibble is A, file is packed (b[0] & 0xf0 == 0xa0)
 1..3       3       depacked size
 4...5      2       if zero, this is the main script
 
 (main only)
 6...21     16      main header bytes
 22...29    8       depack dictionary
 30...xx    ?       packed data
 
 (other)
 6...13     8       depack dictionary
 14...xx    ?       packed data

 
 UNPACKED SCRIPT FILE FORMAT
 byte(s)    len     role
 -------------------------------------------------------------------------------
 0...23     24      header bytes
 24...xx    ?       unpacked data (1st word is ID, must be zero)
 */
sAlisScript * script_load(const char * script_path) {
    sAlisScript * script = NULL;
    FILE * fp = fopen(script_path, "rb");
    if (fp) {
        debug(EDebugVerbose,
                   "Loading script file: %s\n", script_path);
        
        // get script file size
        fseek(fp, 0L, SEEK_END);
        u32 sz = (u32)ftell(fp);
        rewind(fp);

        // read file into buffer
        u8 * buf = malloc(sz * sizeof(u8));
        fread(buf, sizeof(u8), sz, fp);
        
        u8 main = 0;
        
        // decrunch if needed
        u8 * data = buf;
        if(is_packed(buf)) {
            debug(EDebugVerbose, "Unpacking file...\n");
            
            u32 depaksz = get_depacked_size(buf);
            if(is_main(buf)) {
                // main script: load main header into vm
                debug(EDebugVerbose, "Main script detected\nHeader:");
                main = 1;
                for(uint8_t idx = 0; idx < kVMHeaderLen; idx++) {
                    alis.header[idx] = buf[HEADER_MAGIC_LEN_SZ + HEADER_CHECK_SZ + idx];
                    debug(EDebugVerbose, " 0x%02x", alis.header[idx]);
                }
                debug(EDebugVerbose, "\n");
            }

            // alloc and depack
            u8 dic_offset = HEADER_MAGIC_LEN_SZ +
                            HEADER_CHECK_SZ +
                            (main ? kVMHeaderLen : 0);
            u8 pak_offset = dic_offset + HEADER_DIC_SZ;
            u8 * depakbuf = malloc(depaksz * sizeof(u8));
            depak(buf + pak_offset,
                  depakbuf,
                  sz - pak_offset,
                  depaksz,
                  &buf[dic_offset]);
            
            debug(EDebugVerbose,
                       "Unpacking done in %ld bytes (~%d%% packing ratio)\n",
                       depaksz, 100 - (100 * sz) / depaksz);
            
            // cleanup
            data = depakbuf;
            sz = depaksz;
            free(buf);
            buf = NULL;
        }
        
        // init script
        script = (sAlisScript *)malloc(sizeof(sAlisScript));
        strcpy(script->name, strrchr(script_path, kPathSeparator) + 1);
//        script->org = 0; // TODO: determine origin in virtual ram
        script->ID = (data[0] << 8) + data[1]; // TODO: thats a guess
        script->data = data;
        script->datalen = sz;
        script->headerlen = (main ? kMainScriptHeaderLen : kScriptHeaderLen);  // TODO: thats a guess
//        script->code = script->data + headersz;
//        script->codelen = sz - headersz;
//        script->header = script->data;
        script->vram_org = (u8 *)malloc(kScriptStackSize * sizeof(u8));
        script->vstack_ptr = script->vram_org;
        
        // cleanup
        fclose(fp);
    }
    return script;
}

void script_unload(sAlisScript * script) {
    free(script->vram_org);
    free(script->data);
    free(script);
}

