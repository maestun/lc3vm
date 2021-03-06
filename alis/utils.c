//
//  utils.c
//  aodec
//
//  Created by zlot on 07/06/2018.
//  Copyright © 2018 zlot. All rights reserved.
//

#include "utils.h"

char * get_full_path(char * file_name, char * path) {
    char * full_path = malloc(kPathMaxLen * sizeof(char));
    memset(full_path, 0, kPathMaxLen);
    sprintf(full_path, "%s%c%s", path, kPathSeparator, file_name);
    return full_path;
}

s16 sign_extend(s16 x, int bit_count) {
    if ((x >> (bit_count - 1)) & 1) {
        x |= (0xFFFF << bit_count);
    }
    return x;
}

s16 extend_w(s8 x) {
    return sign_extend(x, 8);
}

s32 extend_l(s16 val) {
    return val + (BIT_CHK(val, 7) ? 0xffff0000 : 0);
}

u32 reverse_bytes_32(s32 value) {
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 | (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

long get_file_size(char * file_name) {
    long sz = -1;
    FILE * fp = fopen(file_name, "r");
    if(fp) {
        fseek(fp, 0L, SEEK_END);
        sz = ftell(fp);
        fclose(fp);
    }
    return sz;
}


char * strlower(char * str) {
    char * ptr = str;
    if(ptr) {
        for ( ; *ptr; ++ptr)
            *ptr = tolower(*ptr);
    }
    return str;
}


char * strupper(char * str) {
    char * ptr = str;
    if(ptr) {
        for ( ; *ptr; ++ptr)
            *ptr = toupper(*ptr);
    }
    return str;
}
