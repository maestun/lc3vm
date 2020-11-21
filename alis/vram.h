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
    
    u8      ram[kVirtualRAMSize];        // VRAM_START
} sVRAM;


extern sVRAM vram;


u8      vram_read8(u16 offset);
u16     vram_read16(u16 offset);
u32     vram_read32(u16 offset);

void    vram_write8(u16 offset, u8 value);
void    vram_write16(u16 offset, u16 value);

void    vram_add8(u16 offset, u8 value);
void    vram_add16(u16 offset, u16 value);

void    vram_push8(u8 value);
void    vram_push16(u16 value);
void    vram_push32(u32 value);

u16     vram_pop16(void);
u8      vram_pop8(void);
u32     vram_pop32(void);

#endif /* vram_h */
