#ifndef CHACHA_H
#define CHACHA_H

#include "ecrypt-config.h"
#include "ecrypt-sync.h"

void ECRYPT_init(void);

void ECRYPT_keysetup(ECRYPT_ctx *x, const u8 *k, u32 kbits, u32 ivbits);

void ECRYPT_ivsetup(ECRYPT_ctx *x, const u8 *iv);

// Added by Lukas Danek to be consistent with ChaCha20 description in RFC 7539
void ECRYPT_countersetup(ECRYPT_ctx *x,const u8 *counter);
void ECRYPT_noncesetup(ECRYPT_ctx *x,const u8 *nonce);

void ECRYPT_encrypt_bytes(ECRYPT_ctx *x, const u8 *m, u8 *c, u32 bytes);

void ECRYPT_decrypt_bytes(ECRYPT_ctx *x, const u8 *c, u8 *m, u32 bytes);

void ECRYPT_keystream_bytes(ECRYPT_ctx *x, u8 *stream, u32 bytes);

#endif // CHACHA_H