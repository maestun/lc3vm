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
extern sAlisOpcode opcodes[];


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
    
    // virtual ram data
    u8          memory[kMaxVirtualRAMSize];
    // pointer to virtual ram origin
    u8 *        memory_org;

    // virtual program counter
    u32     pc;
    // pointer to script origin in virtual ram
    u8 *    pc_org;
    
    // virtual stack pointer
    u8 *    sp;
    // pointer to virtual stack origin in virtual ram
    u8 *    sp_org;
    
    // scene pointer
    u8 *    scene_ptr; // A0
    
    // variables
    s16     varD6;
    s16     varD7;
    
    // helper: file pointer
    FILE *  fp;
    // helper: executed instructions count
    u32     icount;
    
    // system stuff
    mouse_t mouse;
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
