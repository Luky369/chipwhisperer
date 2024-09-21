#ifndef DEBUG_H
#define DEBUG_H

#if defined(PLATFORM) && (PLATFORM == CW308_STM32F3)
#include "ecrypt-sync.h"
#include <stdarg.h>

// Function to print formatted debug strings via UART
void print_d(const char *format, ...);
void print_u8(const u8 *array, u32 length);

#else // PC
#include <stdio.h>
#include "ecrypt-sync.h"

// Function to print data in hex format
void print_hex(const char *label, const unsigned char *data, size_t len);

void print_block_8t(const u8* data, size_t len);

void print_block_32t(const u32* data, size_t len);
#endif //CW308_STM32F3 or PC

#endif //DEBUG_H