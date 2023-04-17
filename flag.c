#if defined(_WIN32)
	#include <cstdio>
	#include <cstdbool>
	#include <cstdlib>
	#include <cstring>
#else
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include <string.h>
#endif 

#define MAX_PASSCODE_LEN 64
#define MAX_CMD_BUFF_LEN 256

// rewrite?
	// give user access to encrypted flag, and source code used to encrypt the key
	// leave encrypted key in as a comment, let them reverse engineer it

// fflush(stdout) has to be called with each printf call, otherwise the messages won't send properly over the network connection 
#define printf_flush(fmt,...) printf(fmt __VA_OPT__(,) __VA_ARGS__); fflush(stdout);
// to encrypt:
	// echo "thisistheflag!" | openssl enc -base64 -e -aes-256-cbc -salt -pass pass:supersecurepasscodenoonewillguessever -pbkdf2 -out flag.enc
// to decrypt: 
	// cat flag.enc | openssl enc -base64 -d -aes-256-cbc -salt -pass pass:supersecurepasscodenoonewillguessever -pbkdf2

// strings binary_file_name | less

bool pass_check(const char* input)
{
	if (strcmp(input, "supersecurepasscodenoonewillguessever") == 0) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	fflush(stdin);
	// prompt and take in user input, sanitize if necessary
	printf_flush("Hello, user! Enter the passcode in order to decrypt the file! (Less than 64 characters)\n");
	char user_in[MAX_PASSCODE_LEN];
	fgets(user_in, MAX_PASSCODE_LEN, stdin);
	if ((strlen(user_in) > 0) && (user_in[strlen(user_in) - 1] == '\n')) {
		user_in[strlen(user_in) - 1] = '\0';
	}

	// prepare the buffer to make a command line call
	char cmd_buff[MAX_CMD_BUFF_LEN] = "cat flag.enc | openssl enc -base64 -d -aes-256-cbc -salt -pass pass:";
	// copy the user supplied passcode into the buffer
	memcpy(cmd_buff + strlen(cmd_buff), user_in, strlen(user_in));
	// add the last cli argument
	memcpy(cmd_buff + strlen(cmd_buff), " -pbkdf2", strlen(" -pbkdf2"));
	
	if (pass_check(user_in)) {
		printf_flush("Congratulations! Decrypting the file now!\nFlag: ");
		system(cmd_buff);
	} else {
		printf_flush("Bad passcode!\n");;
	}

	return 0;
}