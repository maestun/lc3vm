//
//  script.h
//  alis
//

#ifndef script_h
#define script_h

#include "config.h"

#define kMainScriptID           (0)
#define kMainScriptHeaderLen    (24 * sizeof(u8))
#define kScriptHeaderLen        (24 * sizeof(u8))
#define kScriptRAMSize          (0xffff * sizeof(u8)) // TODO: seems to be 65k ?

#define kDepackFolder           "depack"
#define kDepackExtension        "bin"

// =============================================================================
// MARK: - SCRIPT
// =============================================================================

typedef struct {
    // HEADER: 24 BYTES
    u16     ID;
    u8      _unknownBytes1[6];
    u16     _unknownOffset;
    u8      _unknownBytes2[14];
    
    char    name[kPathMaxLen];
    
    // for debug: addr of script in steem
    u32     org;
    
    // script data
    u8 *    data;
    u32     data_len;
    
    
    
    
//    u8 *    code_org; // the above + 24 bytes
//    u8 *    code;
    
    //u8 *    data;
    //u32     datalen;
//    u8 *    header;
//    u32     headerlen;

    
    u8      running;
    u8 *    pc_org;
    u8 *    pc;
} sAlisScript;


sAlisScript *   script_load(const char * script_path);
void            script_unload(sAlisScript * script);

//void            script_run(sAlisScript * script);

u32             script_pc(sAlisScript * script);


// read data from script, these will increase the virtual program counter
u8              script_read8(void);
s16             script_read8ext16(void);
s32             script_read8ext32(void);
u16             script_read16(void);
s32             script_read16ext32(void);
u32             script_read24(void);
void            script_read_bytes(u32 len, u8 * dest);
void            script_read_until_zero(u8 * dest);
void            script_jump(s32 offset);

void            script_debug(sAlisScript * script);
#endif /* script_h */
