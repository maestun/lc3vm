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
#define kScriptStackSize        (1024 * sizeof(u32)) // TODO: arbitrary

#define kDepackFolder           "depack"
#define kDepackExtension        "bin"

// =============================================================================
// MARK: - SCRIPT
// =============================================================================
typedef struct {
    u16     ID;
    char    name[kPathMaxLen];
    u8 *    header;

    // offset to script origin in virtual ram
//    u32     org;

    // script data
    u8 *    data;
    u32     datalen;

    // script code
    u8 *    code;
    u32     codelen;
    
    // each script has its own stack ?
    u32     stack[kScriptStackSize];
    u32 *   sp;
    //u32     sp_org;
    
} sAlisScript;

sAlisScript *   script_load(const char * script_path);
void            script_unload(sAlisScript * script);

#endif /* script_h */
