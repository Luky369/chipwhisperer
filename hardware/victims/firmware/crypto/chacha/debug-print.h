#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <stdio.h>
#include "ecrypt-sync.h"


// Function to print data in hex format
void print_hex(const char *label, const unsigned char *data, size_t len);

void print_block_8t(const u8* data, size_t len);

void print_block_32t(const u32* data, size_t len);

#endif //DEBUG_PRINT_H