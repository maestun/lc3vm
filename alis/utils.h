//
//  utils.h
//  aodec
//
//  Created by zlot on 07/06/2018.
//  Copyright © 2018 zlot. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include "config.h"

long        get_file_size(char * file_name);
char *      strlower(char * str);
char *      strupper(char * str);
uint32_t    reverse_bytes_32(uint32_t value);
uint16_t    extend_w(uint8_t x);

#endif /* utils_h */
