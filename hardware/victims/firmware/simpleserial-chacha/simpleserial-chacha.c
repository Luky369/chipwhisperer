/*
    This file is part of the ChipWhisperer Example Targets
    Copyright (C) 2012-2017 NewAE Technology Inc.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#undef DEBUG_CHACHA

#include "chacha.h"
#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>
#include <stdlib.h>

#define KEY_LENGTH     32
#define COUNTER_LENGTH 4
#define NONCE_LENGTH   12
// #define DEFAULT_KEY     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
#define DEFAULT_KEY     0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
#define DEFAULT_COUNTER 0,0,0,0
#define DEFAULT_NONCE   0,0,0,9,0,0,0,0x4a,0,0,0,0
// #define DEFAULT_NONCE   0,0,0,0,0,0,0,0,0,0,0,0

#define PT_LENGHT 64
#define CT_LENGHT PT_LENGHT

static uint8_t key[KEY_LENGTH]         = {DEFAULT_KEY};
static uint8_t counter[COUNTER_LENGTH] = {DEFAULT_COUNTER};
static uint8_t nonce[NONCE_LENGTH]     = {DEFAULT_NONCE};
static ECRYPT_ctx ctx;


uint8_t update_key(uint8_t* k, uint8_t len)
{
	for(int i = 0; i < KEY_LENGTH; i++)
	{
		key[i] = k[i];
	}
    ECRYPT_keysetup(&ctx, key, KEY_LENGTH * 8, 96);
	return 0x00;
}

uint8_t update_counter(uint8_t* c, uint8_t len)
{
	for(int i = 0; i < COUNTER_LENGTH; i++)
	{
		counter[i] = c[i];
	}
    ECRYPT_countersetup(&ctx, counter);
	return 0x00;
}


uint8_t update_nonce(uint8_t* n, uint8_t len)
{
	for(int i = 0; i < NONCE_LENGTH; i++)
	{
		nonce[i] = n[i];
	}
    ECRYPT_noncesetup(&ctx, nonce);
	return 0x00;
}


uint8_t encrypt(uint8_t* pt, uint8_t len)
{
	uint8_t ct[CT_LENGHT];
    ECRYPT_countersetup(&ctx, counter);
    trigger_high();
    ECRYPT_encrypt_bytes(&ctx, (const unsigned char *)pt, ct, len);
	trigger_low();
	simpleserial_put('r', CT_LENGHT, ct);
    
    return 0x00;
}

uint8_t no_op(uint8_t* x, uint8_t len)
{
    return 0x00;
}

int main(void)
{
    #ifdef DEBUG_CHACHA
    putch('\n');
    putch('\n');
    putch('\n');
    #endif //DEBUG

    platform_init();
    init_uart();
    trigger_setup();
    trigger_low();

    ECRYPT_keysetup(&ctx, key, KEY_LENGTH * 8, 96);
    ECRYPT_countersetup(&ctx, counter);
    ECRYPT_noncesetup(&ctx, nonce);

    /* Uncomment this to get a HELLO message for debug */
    #ifdef DEBUG_CHACHA
    putch('\n');
    putch('s');
    putch('t');
    putch('a');
    putch('r');
    putch('t');
    putch('\n');
    #endif

	simpleserial_init();
    simpleserial_addcmd('k', KEY_LENGTH,     update_key);
    simpleserial_addcmd('n', NONCE_LENGTH,   update_nonce);
    simpleserial_addcmd('c', COUNTER_LENGTH, update_counter);
    simpleserial_addcmd('p', PT_LENGHT,      encrypt);
    simpleserial_addcmd('x', 0,              no_op);
    
    while(1) {
        simpleserial_get();
    }
}
