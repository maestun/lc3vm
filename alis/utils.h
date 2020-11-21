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

char *      get_full_path(char * file_name, char * path);
long        get_file_size(char * file_name);
char *      strlower(char * str);
char *      strupper(char * str);
u32         reverse_bytes_32(u32 value);
u16         extend_w(u8 value);
u32         extend_l(u16 value);

#endif /* utils_h */
