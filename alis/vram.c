//
//  vram.c
//  alis
//
//  Created by developer on 23/11/2020.
//  Copyright © 2020 Zlot. All rights reserved.
//

#include "vram.h"

sVRAM vram;

// =============================================================================
// MARK: - Virtual RAM
// =============================================================================
u8 vram_read8(u16 offset) {
    return *(u8 *)(vram.ram + offset);
}

u16 vram_read16(u16 offset) {
    return *(u16 *)(vram.ram + offset);
}

void vram_write8(u16 offset, u8 value) {
    *(u8 *)(vram.ram + offset) = value;
}

void vram_write16(u16 offset, u16 value) {
    *(u16 *)(vram.ram + offset) = value;
}

void vram_add8(u16 offset, u8 value) {
    *(u8 *)(vram.ram + offset) += value;
}

void vram_add16(u16 offset, u16 value) {
    *(u16 *)(vram.ram + offset) += value;
}

void vram_push8(u8 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u8);
    *(u8 *)(alis.scripts[alis.scriptID]->sp) = value;
}

void vram_push16(u16 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u16);
    *(u16 *)(alis.scripts[alis.scriptID]->sp) = value;
}

void vram_push32(u32 value) {
    alis.scripts[alis.scriptID]->sp -= sizeof(u32);
    *(u32 *)(alis.scripts[alis.scriptID]->sp) = value;
}

u8 vram_pop8() {
    u8 ret = *(u8 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u8);
    return ret;
}

u16 vram_pop16() {
    u16 ret = *(u16 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u16);
    return ret;
}

u32 vram_pop32() {
    u32 ret = *(u32 *)(alis.scripts[alis.scriptID]->sp);
    alis.scripts[alis.scriptID]->sp += sizeof(u32);
    return ret;
}
