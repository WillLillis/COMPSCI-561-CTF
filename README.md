# COMPSCI-561-CTF

## Description

The CTF can be started by running ``docker-compose build`` followed by ``docker-compose up``. 
The user can then SSH into the container as ``labuser``, using password ``labuser``. 

Upon landing in the target machine, you will notice there are four files of interest in the /home/labuser directory. The first
is a program binary, ``flag``. The second is ``flag.enc``. The file ``flag.enc`` contains the flag for this CTF, but
its contents have been encrypted using the ``flag`` binary! There is also ``decrypt.c``, which includes code to
read in a user’s text. The remaining portion of the code used to decrypt the flag has been intentionally left
out by the owner of the machine! Finally, there is a C header file, ``base64.h``. This includes some helpful
functions that will perform base64 encoding/decoding.

## Solving

The encrypted flag (as given in ``flag.enc``) is "TA5YRwxHQQ4GAwkAVgYH". The unecrypted flag to be "captured" is "thisistheflag00". While there are many ways to go about solving this CTF, I intended for this process to proceed as follows.

- The user runs ``strings flag`` and discovers two hints left in the program binary. These hints are:

	- "HINT1: The encryption algorithm works by performing a bitwise XOR,"
	"character by character, with the key buffer. The result of this is then encoded using base64 encoding."

	- "HINT2: Value of 0 passed for argument 'key'. Using default key value MD5(7) to construct key buffer";

- With these hints, the user can then figure out the encryption algorithm and deduce that MD5 hash of 7, "8f14e45fceea167a5a36dedd4bea2543", was used as the key buffer.

- Because XOR is a reversible operation, the user could then write some code (either using ``decrypt.c`` or something else) to decrypt the flag. Some sample code that accomplishes this is included in ``decrypt_solved.c``. The decryption portion of this code is:

```C
size_t size_out;
char* decoded = base64_decode(user_in, strlen(user_in), &size_out);
	
const char* key_buff = "8f14e45fceea167a5a36dedd4bea2543"; // MD5(7)
for (int i = 0; i < size_out; i++) {
	decoded[i] ^= key_buff[i];
}
```