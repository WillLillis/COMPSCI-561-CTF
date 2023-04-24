#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <unistd.h>
#include "base64.h"

// fflush(stdout) has to be called with each printf call, otherwise the messages won't send properly over the network connection 
// at least while using netcat, ssh seems to be fine with normal printf calls
#define printf_flush(fmt,...) printf(fmt __VA_OPT__(,) __VA_ARGS__); fflush(stdout);

char* encrypt(const char* input, uint8_t key)
{
	const char* hint_buff1 = "HINT1: The encryption algorithm works by performing a bitwise XOR,"
	"character by character, with the key buffer. (For example, encrypted[i] = plaintext[i] ^ keybuffer[i]) The result of this is then encoded using base64 encoding.";
	const char* hint_buff2 = "HINT2: Value of 0 passed for argument 'key'. Using default key value MD5(7) to consturct key buffer";
	//const char* key_buff = "8f14e45fceea167a5a36dedd4bea2543";
	// have to do this so the MD5 hash doesn't show up when the user runs strings on the binary
	// don't want to make things too easy
	char* key_buff; 

	EVP_MD_CTX* mdctx;
	unsigned char* md5_digest;
	unsigned int md5_digest_len = EVP_MD_size(EVP_md5());
	mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

	if (key == 0) {
		//printf("Value of 0 passed for argument 'key'. Using default key value MD5(7) to consturct key buffer\n");
		key_buff = (char*)malloc(32 + 1);
		if (key_buff == NULL) {
			printf("Allocation error!\n");
			return NULL;
		}
		
		key_buff[0] = '8';
		key_buff[1] = 'f';
		key_buff[2] = '1';
		key_buff[3] = '4';
		key_buff[4] = 'e';
		key_buff[5] = '4';
		key_buff[6] = '5';
		key_buff[7] = 'f';
		key_buff[8] = 'c';
		key_buff[9] = 'e';
		key_buff[10] = 'e';
		key_buff[11] = 'a';
		key_buff[12] = '1';
		key_buff[13] = '6';
		key_buff[14] = '7';
		key_buff[15] = 'a';
		key_buff[16] = '5';
		key_buff[17] = 'a';
		key_buff[18] = '3';
		key_buff[19] = '6';
		key_buff[20] = 'd';
		key_buff[21] = 'e';
		key_buff[22] = 'd';
		key_buff[23] = 'd';
		key_buff[24] = '4';
		key_buff[25] = 'b';
		key_buff[26] = 'e';
		key_buff[27] = 'a';
		key_buff[28] = '2';
		key_buff[29] = '5';
		key_buff[30] = '4';
		key_buff[31] = '3';
		key_buff[32] = '\0';
	} else {
		printf("Non-zero key value entered, using key value %d to compute key_buff.\n", key);

		EVP_DigestUpdate(mdctx, (char*)&key, sizeof(key));

		// this MD5 calculation gives different results from the online calculators... 
		// doesn't matter for the sake of the CTF, but I'm not sure why
		key_buff = (char*)OPENSSL_malloc(md5_digest_len);
		EVP_DigestFinal_ex(mdctx, key_buff, &md5_digest_len);
		EVP_MD_CTX_free(mdctx);
	}

	char* input_tmp = (char*)malloc(strlen(input) + 1);
	if (input_tmp == NULL) {
		printf("Allocation error!\n");
		return NULL;
	}

	memset(input_tmp, '\0', strlen(input) + 1);
	strcpy(input_tmp, input);
	
	//printf("Input: %s\n", input_tmp);

	size_t len = strlen(input_tmp);
	for (int i = 0; i < len; i++) {
		input_tmp[i] ^= key_buff[i];
	}

	free(key_buff);

	//printf("Encrypted: %s\n", input_tmp);

	size_t size_out;
	char* encoded_data = base64_encode(input_tmp, len, &size_out);

	free(input_tmp);

	//printf("Encoded: %s\n", encoded_data);

	return encoded_data;
}