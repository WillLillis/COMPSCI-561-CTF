#pragma once
#if defined(_WIN32)
	#include <cstdint>
	#include <cstdio>
	#include <cstdlib>
	#include <cstring.h>
#else
	#include <stdint.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
#endif 

// fflush(stdout) has to be called with each printf call, otherwise the messages won't send properly over the network connection 
#define printf_flush(fmt,...) printf(fmt __VA_OPT__(,) __VA_ARGS__); fflush(stdout);

char* encrypt(const char* input, uint8_t key)
{
	if (key == 0) {
		printf_flush("Value of 0 passed for argument 'key'. Using default key value 42!\n");
		key = 42;
	}

	size_t input_len = strlen(input);

	char* out = (char*)malloc(input_len + 1); // + 1 for null terminator
	if (out == NULL) {
		printf_flush("Memory allocation failure! Requested %zu bytes.\n", strlen(input) + 1);
		return NULL;
	}

	memset(out, '\0', input_len + 1);

	for (int i = 0; i < input_len; i++) {
		out[i] = input[i] + key;
	}

	return out;
}