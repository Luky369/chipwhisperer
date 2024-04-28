#include <stdio.h>
#include <stdint.h>
#include "openssl_endian.h"
#include "openssl_chacha.h"


#define LEN 64

#define KEY_LEN_BYTES 32

#define WORD_BYTE_COUNT 4

#define KEY_LEN_WORDS KEY_LEN_BYTES / WORD_BYTE_COUNT

#define COUNTER_CONST 0x01
#define NONCE_0 0
#define NONCE_1 0x4a
#define NONCE_2 0x09



#define U8TO32_LE(p)                                                           \
    (((uint64_t)((p)[0])) | ((uint64_t)((p)[1]) << 8) |                        \
     ((uint64_t)((p)[2]) << 16) | ((uint64_t)((p)[3]) << 24))


#define U8TO32_BE(p)                                                           \
    (((uint32_t)((p)[0]) << 24) | ((uint32_t)((p)[1]) << 16) |                \
     ((uint32_t)((p)[2]) << 8) | ((uint32_t)((p)[3])))



void chacha(const void *in, const size_t inlen, const void *k, uint8_t *out,
            const size_t outlen) {
	
	unsigned int counter[4] = {COUNTER_CONST,NONCE_2,NONCE_1,NONCE_0};
	const unsigned char *in_uc = (const unsigned char *)in;
    const unsigned char *k_uc  = (const unsigned char *)k;
	unsigned int k_ui[8];


	DECLARE_IS_ENDIAN;

	for (size_t i = 0; i < KEY_LEN_WORDS; ++i) {
		if (IS_LITTLE_ENDIAN) {
			k_ui[i] = U8TO32_LE(k_uc + i * WORD_BYTE_COUNT);
		} else {
			k_ui[i] = U8TO32_BE(k_uc + i * WORD_BYTE_COUNT);		
		}
    }

#ifdef DEBUG
    printf("\nKEY - int: ");
    for (size_t i = 0; i < KEY_LEN_WORDS; ++i) {
        printf("%08X ",k_ui[i]);
    }
    printf("\n");
#endif
	ChaCha20_ctr32((unsigned char *)out, in_uc, inlen, k_ui, counter);

}


#ifdef PC_DEBUG
int main (int argc, char *argv[]) {
    // ChaCha20_ctr32(unsigned char *out, const unsigned char *inp, size_t len,
                    // const unsigned int key[8], const unsigned int counter[4])
    unsigned char out[LEN];
    unsigned char inp[LEN];
    size_t len = LEN;

    uint8_t key[KEY_LEN_BYTES] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
        0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    for (size_t i = 0; i < LEN; ++i) {
        inp[i] = 0x01;
    }
    
    chacha(inp, len, key, out, len);

    printf("INP: ");
    for (size_t i = 0; i < LEN; ++i) {
        printf("%02X ",inp[i]);
    }
    printf("\n");

    printf("OUT: ");
    for (size_t i = 0; i < LEN; ++i) {
        printf("%02X ",out[i]);
    }
    printf("\n");
    
    return 0;
}
#endif //PC_DEBUG