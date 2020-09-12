//
//  alis_private.h
//  lc3vm
//

#ifndef alis_private_h
#define alis_private_h

#include "alis.h"

u8 read8(void) ;
u16 read16(void);
u32 read24(void);
void readBytes(u32 len, u8 * dest);
void readToZero(u8 * dest);
uint16_t sign_extend(uint16_t x, int bit_count);
uint16_t extend_w(uint8_t x);

alisRet readexec_opcode(void);
alisRet readexec_opname(void);
alisRet readexec_storename(void);
alisRet readexec_addname(void);

extern sAlisOpcode opcodes[];
extern sAlisOpcode opernames[];
extern sAlisOpcode storenames[];
extern sAlisOpcode addnames[];

#endif /* alis_private_h */
