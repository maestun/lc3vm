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

#define kVMHeaderLen            (16 * sizeof(u8))
#define kMaxVirtualRAMSize      (1024 * 1024 * sizeof(u8))
#define kMaxScripts             (UINT8_MAX)
#define kBSSChunkLen            (256)


// =============================================================================
// MARK: - SPECIAL OFFSETS IN ALIS RAM (A6)
// =============================================================================
#define AO_CLINKING             (0xffd6)
#define AO_SC_POSITION          (0xffea)
#define AO_LOC_TP               (0xfffe)
#define AO_LOC_TP               (0xffff)




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
    
    // true if vm is running
    u8              running;
    
    // host ram emulation
    u8 *            ram;
    
    // virtual program counter
    u8 *            pc;
    
    // virtual program counter origin
    u8 *            pc_org;

    // virtual stack (A4 ???)
    u8 *            stack;
    u8 *            stack_org;
    
    // loaded scripts
    sAlisScript *   scripts[kMaxScripts];
    u8              scriptID;
    
    // variables
    s16             varD6;
    s16             varD7;
    
    u8 *            bssChunk1;
    u8 *            bssChunk2;
    u8 *            bssChunk3;
    
    // helper: file pointer
    FILE *  fp;
    // helper: executed instructions count
    u32     icount;
    
    // system stuff
    mouse_t mouse;
    
    // unknown vars
    u32 DAT_000194fe;
    
    
    // A6 => contient adresse du début de la ram virtuelle (ou pile virtuelle ?)
    //       qui a l'air de faire 65k (0xffff) au total.
    // D4 => un offset qui dit où se trouve le pointeur de pile
    //       dans la ram virtuelle
    // par exemple pour main.ao a6 vaut $22690, et d4 vaut $ffff
    // donc le virtual stack pointer pointe à l'adresse $3268f
    
} sAlisVM;

extern sAlisVM alis;

// =============================================================================
// MARK: - API
// =============================================================================
void            alis_init(sPlatform platform);
u8              alis_main(void);
void            alis_deinit(void);
void            alis_start_script(sAlisScript * script);
void            alis_error(u8 errnum);

#endif /* alis_vm_h */
