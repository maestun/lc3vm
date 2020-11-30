//
//  alis_vm.h
//  lc3vm
//

#ifndef alis_vm_h
#define alis_vm_h

#include "config.h"
#include "debug.h"
#include "platform.h"
#include "script.h"
#include "sys.h"
#include "vram.h"


#define kVMHeaderLen            (16 * sizeof(u8))
#define kHostRAMSize            (1024 * 1024 * sizeof(u8))
#define kVirtualRAMSize         (0xffff * sizeof(u8))
#define kMaxScripts             (256)
#define kBSSChunkLen            (256)



// =============================================================================
// MARK: - ERROR CODES
// =============================================================================
#define ALIS_ERR_FOPEN          (0x01)
#define ALIS_ERR_FWRITE         (0x07)
#define ALIS_ERR_FCREATE        (0x08)
#define ALIS_ERR_FDELETE        (0x09)
#define ALIS_ERR_CDEFSC         (0x0a)
#define ALIS_ERR_FREAD          (0x0d)
#define ALIS_ERR_FCLOSE         (0x0e)
#define ALIS_ERR_FSEEK          (0x00)


typedef struct {
    u8      errnum;
    char    name[kNameMaxLen];
    char    descfmt[kDescMaxLen];
} sAlisError;


// =============================================================================
// MARK: - SPECIAL OFFSETS IN ALIS RAM (A6)
// =============================================================================
#define AO_CLINKING             (0xffd6)
#define AO_SC_POSITION          (0xffea)
#define AO_LOC_TP               (0xfffe)


// =============================================================================
// MARK: - OPCODES
// =============================================================================
typedef void    alisRet;
typedef alisRet (*alisOpcode)(void);

#define DECL_OPCODE(n, f, d)    { n, f, #f, d }

typedef struct {
    u8          code;
    alisOpcode  fptr;
    char        name[kNameMaxLen];
    char        desc[kDescMaxLen];
} sAlisOpcode;

// =============================================================================
// MARK: - VM
// =============================================================================
typedef struct {
    // platform
    sPlatform       platform;
    
    // TODO: vm header, loaded from main script ?
    u8              header[kVMHeaderLen];
    
    // true if disasm only
    u8              disasm;
    
    // true if vm is running
    u8              running;
    
    // virtual program counter
//    u8 *            pc;
//    u8 *            pc_org;
    
    // virtual 16-bit accumulator (A4)
    s16 *           acc;
    s16 *           acc_org;
    
    // virtual ram
    /*
     VIRTUAL RAM / STACK
        located at address contained in A6 register.
        There's also a stack pointer where we store 32-bit return addresses,
        the address of this pointer is (A6 + D4).
     
     A6 = vram / virtual ram
     |                           sp
     | <-- D4 = stack offset --> |
     v                           v
     _______________________ ... _____
     |_|_|_|_|_|_|_|_|_|_|_| ... |_|_|
     
     <---------- 65k bytes ---------->
    */
    sVRAM * vram;
//    u8              vram[kVirtualRAMSize];
//    u32             sp_offset;
//    struct {
//        u8 scan: 1;
//        u8 inter: 1;
//    }  status;
//    // adresse dans la ram hote de l'origine du script
//    // header inclus
//    u32     script_org_ptr_addr;// VRAM_START - 0x14
//
//    // offset de la pile virtuelle dans la ram virtuelle
//    // registre D4
//    u16     stack_offset;       // VRAM_START - 0x0a
//
//    // adresse dans la ram hote du pointeur de script
//    // registre A3
//    u32     script_ptr_addr;    // VRAM_START - 0x08

    
    // loaded scripts
    sAlisScript *   scripts[kMaxScripts];
    u8              scriptID;
    sAlisScript *   script;
    
    u8              nextScriptID;
    
    // virtual registers
    s16             varD6;
    s16             varD7;
    
    // virtual array registers
    u8 *            bssChunk1;
    u8 *            bssChunk2;
    u8 *            bssChunk3;
    
    // helper: executed instructions count
    u32     icount;
        
    // unknown vars
    u32 DAT_000194fe;
    
    struct {
        u8 zero: 1;
        u8 neg: 1;
    } sr;
    
    
    // A6 => contient adresse du début de la ram virtuelle (ou pile virtuelle ?)
    //       qui a l'air de faire 65k (0xffff) au total.
    // D4 => un offset qui dit où se trouve le pointeur de pile
    //       dans la ram virtuelle
    // par exemple pour main.ao a6 vaut $22690, et d4 vaut $ffff
    // donc le virtual stack pointer pointe à l'adresse $3268f
    
    
    // helpers
    u8          oeval_loop;
    
    // system helpers
    FILE *      fp;
    
    // unknown variables
    u8          _cclipping;
    u8          _ctiming;
    u16         _a6_minus_16;
    u16         _random_number;
    u8          _xinvon; // (-0x3,A6)
    
    u16         _DAT_000195fa;
    u16         _DAT_000195fc;
    u16         _DAT_000195fe;
        
    // system stuff
    // mouse_t     mouse;
    pixelbuf_t  pixelbuf;
} sAlisVM;

extern sAlisVM alis;

extern u32 script_addrs[kMaxScripts];


// =============================================================================
// MARK: - API
// =============================================================================
void            alis_init(sPlatform platform);
u8              alis_main(void);
void            alis_deinit(void);
//sAlisScript *   alis_load_script(const char * name, const u32 org);
void            alis_start_script(sAlisScript * script);
void            alis_error(u8 errnum, ...);
void            alis_debug(void);
void            alis_debug_ram(void);
void            alis_debug_addr(u16 addr);

#endif /* alis_vm_h */


