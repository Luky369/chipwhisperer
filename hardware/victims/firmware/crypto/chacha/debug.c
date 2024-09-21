#include "debug.h"

#if defined(PLATFORM) && (PLATFORM == CW308_STM32F3)
#include "hal.h" 
#include "ecrypt-sync.h"
#include <stdio.h> // For vsnprintf
#include <stdarg.h> // For va_list


#define DEBUG_BUFFER_SIZE 256
#define WARNING_MESSAGE "Error: Debug message too long.\n"
void print_d(const char *format, ...) {
    char buffer[DEBUG_BUFFER_SIZE];
    va_list args;
    int length;

    va_start(args, format);
    length = vsnprintf(buffer, DEBUG_BUFFER_SIZE, format, args);
    va_end(args);

    // Check if the formatted string length exceeds the buffer size
    if (length >= DEBUG_BUFFER_SIZE) {
        // Print the warning message
        for (const char *ptr = WARNING_MESSAGE; *ptr != '\0'; ++ptr) {
            putch(*ptr);
        }
        return;
    }

    // Print the formatted string
    for (char *ptr = buffer; *ptr != '\0'; ++ptr) {
        putch(*ptr);
    }
}

void print_u8(const u8 *array, u32 length) {
    for (u32 i = 0; i < length; ++i) {
        print_d("%02X", array[i]);
    }
    putchar('\n');
}

#else // PC
#include <stdio.h>
#include "ecrypt-sync.h"
// Function to print data in hex format
void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

void print_block_8t(const u8* data, size_t len) {
    // Print the 32-bit words in little-endian format
    for (size_t i = 0; i < len; i += 16) {
        printf("       ");
        for (size_t j = i; j < i + 16; j += 4) {
            u32 word = (data[j + 3] << 24) | (data[j + 2] << 16) | (data[j + 1] << 8) | data[j];
            printf("%08x  ", word);
        }
        printf("\n");
    }
}

void print_block_32t(const u32* data, size_t len) {
    // Print the  sequence of 32-bit words
    printf("       ");
    for (size_t i = 0; i < len; ++i) {
        printf("%08x  ", data[i]);
        if ((i + 1) % 4 == 0) {
            printf("\n       ");
        }
    }
    printf("\n");
}
#endif //CW308_STM32F3 or PC