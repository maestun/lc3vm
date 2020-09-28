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
    sPlatform   platform;
    
    // header loaded from main script
    u8          header[kVMHeaderLen];
    
    // true if vm is running
    u8          running;
    
    // virtual program counter
    u8 *        pc;
    // pointer to script origin in virtual ram
    u8 *        pc_org;
    
    // loaded scripts
    sAlisScript *   scripts[kMaxScripts];
    u8              scriptID;
    
    // vm stack (A4 ???)
    u8 *        vm_stack;
    
    
    // virtual stack pointer
//    u32 *   sp;
//    // pointer to virtual stack origin in virtual ram (TODO: A6 ??)
//    u32 *   sp_org;
    
    // scene pointer
    // u8 *    scene_ptr; // A0
    
    // variables
    s16     varD6;
    s16     varD7;
    u16     varD4; // address of return for ctl loop
    
    u8      bssChunk1[256];
    u8      bssChunk2[256];
    u8      bssChunk3[256];
    
    // helper: file pointer
    FILE *  fp;
    // helper: executed instructions count
    u32     icount;
    
    // system stuff
    mouse_t mouse;
    
    
    
    
    
    
    
    
    // unknown vars
    u32 DAT_000194fe;
    
    
    
} sAlisVM;

extern sAlisVM alis;

// =============================================================================
// MARK: - API
// =============================================================================
void            alis_init(sPlatform platform);
u8              alis_main(void);
void            alis_deinit(void);
void            alis_start_script(sAlisScript * script);


#endif /* alis_vm_h */
