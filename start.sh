#!/bin/bash

gcc flag.c -o flag # need c++20 for variadic function like macros to work
rm flag.c # remove the source code file after compilation
ncat -lvkp 54321 -e "/usr/bin/bash" # open a listening port for the user to connect to