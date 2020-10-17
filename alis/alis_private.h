//
//  alis_private.h
//  lc3vm
//

#ifndef alis_private_h
#define alis_private_h

#include "alis.h"
#include "debug.h"
#include "sys.h"


#define     ALIS_BIT_0      (0)
#define     ALIS_BIT_1      (1)
#define     ALIS_BIT_2      (2)
#define     ALIS_BIT_3      (3)
#define     ALIS_BIT_4      (4)
#define     ALIS_BIT_5      (5)
#define     ALIS_BIT_6      (6)
#define     ALIS_BIT_7      (7)

// read data from script, these will increase the virtual program counter
u8      script_read8(void) ;
u16     script_read16(void);
u32     script_read24(void);
void    script_read_bytes(u32 len, u8 * dest);
void    script_read_until_zero(u8 * dest);


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

extern void oeval(void);

// handle data from virtual ram
u8      read8(u16 offset);
u16     read16(u16 offset);
u32     read32(u16 offset);

void write8(u16 offset, u8 value);
void write16(u16 offset, u16 value);

void add8(u16 offset, u8 value);
void add16(u16 offset, u16 value);

void push8(u8 value);
void push16(u16 value);
void push32(u32 value);

u16     pop16(void);
u8      pop8(void);
u32     pop32(void);

#endif /* alis_private_h */
