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


u8 read8(void) ;
u16 read16(void);
u32 read24(void);
void readBytes(u32 len, u8 * dest);
void readToZero(u8 * dest);
uint16_t sign_extend(uint16_t x, int bit_count);
uint16_t extend_w(uint8_t x);

alisRet readexec_opcode(void);
alisRet readexec_opername(void);
alisRet readexec_storename(void);
alisRet readexec_addname(void);
alisRet readexec_opername_saveD7(void);
alisRet readexec_addname_swap(void);
alisRet readexec_opername_swap(void);

extern sAlisOpcode opcodes[];
extern sAlisOpcode opernames[];
extern sAlisOpcode storenames[];
extern sAlisOpcode addnames[];

extern void oeval(void);

void write8(u16 offset, u8 value);
void write16(u16 offset, u16 value);

void add8(u16 offset, u8 value);
void add16(u16 offset, u16 value);

u16 pop16(void);
u8 pop8(void);

#endif /* alis_private_h */
