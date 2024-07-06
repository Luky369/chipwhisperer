#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "debug-print.h"
#include "chacha.h"
#include "ecrypt-sync.h"

#define PT_LENGHT_IN_BYTES      64
#define KEY_LENGHT_IN_BYTES     32
#define NONCE_LENGHT_IN_BYTES   12
#define COUNTER_LENGHT_IN_BYTES 4

#define BITS_IN_BYTE 8

#define ROTATE(v,c) (ROTL32(v,c))
#define XOR(v,w) ((v) ^ (w))
#define PLUS(v,w) (U32V((v) + (w)))
#define PLUSONE(v) (PLUS((v),1))

#define QUARTERROUND(a,b,c,d) \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]),16); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]),12); \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]), 8); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]), 7);

int main() {
    ECRYPT_ctx ctx;
    unsigned char key[KEY_LENGHT_IN_BYTES];
    unsigned char counter[COUNTER_LENGHT_IN_BYTES] = {0x00, 0x00, 0x00, 0x00};
    unsigned char nonce[NONCE_LENGHT_IN_BYTES] = {0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};
    unsigned char pt[PT_LENGHT_IN_BYTES];
    unsigned char ciphertext[PT_LENGHT_IN_BYTES];

    // Seed the random number generator
    srand(time(NULL));

    //testing quarter round 
    u32 x[4] = {0x11111111, 0x01020304, 0x9b8d6f43, 0x01234567};
    QUARTERROUND(0,1,2,3);
    print_block_32t(x, 4);



    // Generate Key, PT
    for (int i = 0; i < KEY_LENGHT_IN_BYTES; i++) {
        // key[i] = rand() % 256;
        key[i] = i;
    }

    for (int i = 0; i < PT_LENGHT_IN_BYTES; i++) {
        // key[i] = rand() % 256;
        pt[i] = 0x11;
    }
    // Initialize the cipher with the key and IV
    ECRYPT_keysetup(&ctx, key, KEY_LENGHT_IN_BYTES * 8, 64);

    ECRYPT_countersetup(&ctx, counter);

    ECRYPT_noncesetup(&ctx, nonce);

    // Encrypt the plaintext
    ECRYPT_encrypt_bytes(&ctx, (const unsigned char *)pt, ciphertext, PT_LENGHT_IN_BYTES);

    // Print the key, IV, plaintext, and ciphertext
    print_hex("Key       ", key, sizeof(key));
    print_hex("Counter   ", counter, sizeof(counter));
    print_hex("Nonce     ", nonce, sizeof(nonce));

    printf("Plaintext\n");
    print_block_8t(pt, sizeof(pt));
    printf("Ciphertext\n");
    print_block_8t(ciphertext, sizeof(pt));

    return 0;
}