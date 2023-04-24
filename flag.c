#include "encrypt.h"
#include "base64.h"

#define MAX_PASSCODE_LEN 32

// Flag:		   thisistheflag00
// Encrypted Flag: TA5YRwxHQQ4GAwkAVgYH

// sample solution to insert at the bottom of decrypt.c
//size_t size_out;
//char* decoded = base64_decode(user_in, strlen(user_in), &size_out);
//
//const char* key_buff = "8f14e45fceea167a5a36dedd4bea2543";
//for (int i = 0; i < size_out; i++) {
//	decoded[i] ^= key_buff[i];
//}
//
//printf("decrypted: %s\n", decoded);

int main()
{
	fflush(stdin);
	// prompt and take in user input, sanitize if necessary
	printf_flush("Hello, user! Enter the string you would like to encrypt.\n");
	char user_in[MAX_PASSCODE_LEN];
	fgets(user_in, MAX_PASSCODE_LEN, stdin);
	if ((strlen(user_in) > 0) && (user_in[strlen(user_in) - 1] == '\n')) {
		user_in[strlen(user_in) - 1] = '\0';
	}

	char* encrypted = NULL;
	if ((encrypted = encrypt(user_in, 0)) == NULL) {
		printf_flush("Error returned from encryption function!\n");
	} else {
		printf_flush("Encrypted: %s\n", encrypted);
	}

	free(encrypted);

	return 0;
}