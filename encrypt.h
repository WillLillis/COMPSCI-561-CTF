#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

// fflush(stdout) has to be called with each printf call, otherwise the messages won't send properly over the network connection 
#define printf_flush(fmt,...) printf(fmt __VA_OPT__(,) __VA_ARGS__); fflush(stdout);

// make this even easier?
// unroll the loop and make it a constant number of characters?
void do_encrypt(const char* input, char* out, size_t input_len, int key)
{
	for (int i = 0; i < input_len; i++) {
		out[i] = input[i] + key;
	}
}

char* encrypt(const char* input, uint8_t key)
{
	const char* hint_buff1 = "Value of 0 passed for argument 'key'. Using default key value 1!\n";
	const char* hint_buff2 = "Reminder: The encryption alg first encodes the string using base64 encoding, then adds 1 to each character in turn.";
	//const char* key_buff;
	if (key == 0) {
		printf_flush("Value of 0 passed for argument 'key'. Using default key value 1!\n");
		key = 1;
		//key_buff = "8f14e45fceea167a5a36dedd4bea2543";
	} 
	
	printf("Input: %s\n", input);
	
	size_t size_out;
	char* encoded_data = base64_encode(input, strlen(input), &size_out);
	
	printf("Encoded: %s\n", encoded_data);

	size_t len = strlen(encoded_data);
	for (int i = 0; i < len; i++) {
		encoded_data[i] += key;
	}

	printf("Encrypted: %s\n", encoded_data);

	return encoded_data;
}