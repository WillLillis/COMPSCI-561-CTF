#include "encrypt.h"

#define MAX_PASSCODE_LEN 64

// thisistheflag!
// ymnxnxymjkqfl&

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