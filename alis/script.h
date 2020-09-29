//
//  script.h
//  alis
//

#ifndef script_h
#define script_h

#include "config.h"

#define kMainScriptID           (0)
#define kMainScriptHeaderLen    (24 * sizeof(u8))
#define kScriptHeaderLen        (8 * sizeof(u8))
#define kScriptStackSize        (0xffff * sizeof(u8)) // TODO: seems to be 65k ?

#define kDepackFolder           "depack"
#define kDepackExtension        "bin"

// =============================================================================
// MARK: - SCRIPT
// =============================================================================
typedef struct {
    u16     ID;
    char    name[kPathMaxLen];
    // script data
    u8 *    data;
    u32     datalen;
//    u8 *    header;
    u32     headerlen;


    // script code
//    u8 *    code;
//    u32     codelen;

    /*
     VIRTUAL RAM / STACK
     TODO: Each script has its own 65k virtual ram,
        located at address contained in A6 register.
        There's also a stack pointer where we store 32-bit return addresses,
        the address of this pointer is (A6 + D4).
        
     
     A6 = vram_org / virtual ram
     |                           vstack_ptr
     | <-- D4 = stack offset --> |
     v                           v
     _______________________ ... _____
     |_|_|_|_|_|_|_|_|_|_|_| ... |_|_|
     
     <---------- 65k bytes ---------->
    */
    
    u8 *    vram_org;   // A6 register
    u8 *    vstack_ptr; // pointer to virtual stack (A6 + D4)
    
} sAlisScript;

sAlisScript *   script_load(const char * script_path);
void            script_unload(sAlisScript * script);

#endif /* script_h */
