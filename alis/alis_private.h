//
//  alis_private.h
//  lc3vm
//

#ifndef alis_private_h
#define alis_private_h

#include "alis.h"
#include "debug.h"
#include "sys/sys.h"

#define     ALIS_BIT_0      (0)
#define     ALIS_BIT_1      (1)
#define     ALIS_BIT_2      (2)
#define     ALIS_BIT_3      (3)
#define     ALIS_BIT_4      (4)
#define     ALIS_BIT_5      (5)
#define     ALIS_BIT_6      (6)
#define     ALIS_BIT_7      (7)

alisRet readexec_opcode(void);
alisRet readexec_opername(void);
alisRet readexec_storename(void);
alisRet readexec_addname(void);
alisRet readexec_opername_saveD7(void);
alisRet readexec_addname_swap(void);
alisRet readexec_opername_swap(void);


extern sAlisOpcode  opcodes[];
extern sAlisOpcode  opernames[];
extern sAlisOpcode  storenames[];
extern sAlisOpcode  addnames[];
extern sAlisError   errors[];

// handle data from virtual ram
//u8      vram_read8(u16 offset);
//u16     vram_read16(u16 offset);
//u32     vram_read32(u16 offset);
//
//void    vram_write8(u16 offset, u8 value);
//void    vram_write16(u16 offset, u16 value);
//
//void    vram_add8(u16 offset, u8 value);
//void    vram_add16(u16 offset, u16 value);
//
//void    vram_push32(u32 value);
//u32     vram_pop32(void);

// common opcode helpers
extern u16  loctc_common(u16 offset);
extern u16  locti_common(u16 offset);
extern u16  loctp_common(u16 offset);
extern void oeval(void);
extern void ofin(void);

#endif /* alis_private_h */
