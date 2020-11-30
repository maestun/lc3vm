//
//  vram.h
//  alis
//
//  Created by developer on 23/11/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#ifndef vram_h
#define vram_h

#include "config.h"
#include "script.h"

#define kVirtualRAMSize         (0xffff * sizeof(u8))

typedef struct {
    // VRAM_START - 0x24
    struct {
        u8 scan:1;
        u8 inter:1;
        u8 _bit2:1;
        u8 _bit3:1;
        u8 _bit4:1;
        u8 _bit5:1;
        u8 _bit6:1;
        u8 _bit7:1;
    } status;
    
    // adresse dans la ram hote de l'origine du script
    // header inclus
    u32     script_org_ptr_addr;// VRAM_START - 0x14
    
    // offset de la pile virtuelle dans la ram virtuelle
    // registre D4
    u16     stack_offset;       // VRAM_START - 0x0a
    
    // adresse dans la ram hote du pointeur de script
    // registre A3
    u32     script_ptr_addr;    // VRAM_START - 0x08
    
    u8      ram[kVirtualRAMSize];   // VRAM_START
} sVRAM;


sVRAM * vram_init(void);
void    vram_deinit(sVRAM * vram);

u8 *    vram_ptr(sVRAM * vram, u16 offset);

u8      vram_read8(sVRAM * vram, u16 offset);
s16     vram_read8ext16(sVRAM * vram, u16 offset);
s32     vram_read8ext32(sVRAM * vram, u16 offset);
u16     vram_read16(sVRAM * vram, u16 offset);
s32     vram_read16ext32(sVRAM * vram, u16 offset);
u32     vram_read32(sVRAM * vram, u16 offset);
void    vram_readp(sVRAM * vram, u16 offset, u8 * dst_ptr);

void    vram_write8(sVRAM * vram, u16 offset, u8 value);
void    vram_write16(sVRAM * vram, u16 offset, u16 value);
void    vram_writep(sVRAM * vram, u16 offset, u8 * src_ptr);

void    vram_setbit(sVRAM * vram, u16 offset, u8 bit);
void    vram_clrbit(sVRAM * vram, u16 offset, u8 bit);

void    vram_add8(sVRAM * vram, u16 offset, u8 value);
void    vram_add16(sVRAM * vram, u16 offset, u16 value);

void    vram_push32(sVRAM * vram, u32 value);
u32     vram_peek32(sVRAM * vram);
u32     vram_pop32(sVRAM * vram);

void    vram_save_script_state(sVRAM * vram, sAlisScript * script);

void    vram_debug(sVRAM * vram);

#endif /* vram_h */
