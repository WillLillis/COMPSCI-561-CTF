#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSCODE_LEN 32

// fflush(stdout) has to be called with each printf call, otherwise the messages won't send properly over the network connection 
#define printf_flush(fmt,...) printf(fmt __VA_OPT__(,) __VA_ARGS__); fflush(stdout);

int main()
{
	fflush(stdin);
	// prompt and take in user input, sanitize if necessary
	printf_flush("Hello, user! Enter the string you would like to decrypt.\n");

	char user_in[MAX_PASSCODE_LEN];
	fgets(user_in, MAX_PASSCODE_LEN, stdin);
	if ((strlen(user_in) > 0) && (user_in[strlen(user_in) - 1] == '\n')) {
		user_in[strlen(user_in) - 1] = '\0';
	}

	printf("Inputted string: %s\n", user_in);

	/*
	* Your code goes here...
	*/

	return 0;
}