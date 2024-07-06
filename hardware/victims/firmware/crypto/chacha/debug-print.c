

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