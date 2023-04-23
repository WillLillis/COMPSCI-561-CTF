#include "encrypt.h"
#include "base64.h"

#define MAX_PASSCODE_LEN 32

// thisistheflag00
// dGhpc2lzdGhlZmxhZzAw
// eHiqd3m{eHim[nyi[{Bx

// sample solution for decrypt.c
/*const char* key_buff = "8f14e45fceea167a5a36dedd4bea2543";
size_t len = strlen(user_in);
for (int i = 0; i < len; i++){
	user_in[i] = user_in[i] - 1;
}

printf("Decrypted string: %s\n", user_in);

size_t size_out;
char* decoded = base64_decode(user_in, len, &size_out);
if (decoded == NULL) printf("Base64 decode error!\n");*/

// use command line args instead of fgets?
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
		printf_flush("Encrypted flag: %s\n", encrypted);
	}

	return 0;
}