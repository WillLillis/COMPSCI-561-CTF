#!/bin/bash

gcc flag.c -o flag # need c++20 for variadic function like macros to work
rm flag.c # remove the source code file after compilation
rm encrypt.h # ^
#rm -- "$0" # having this works fine for the first build, but breaks with subsequent calls to "docker-compose up"
ncat -lvkp 54321 -e "/usr/bin/bash" # open a listening port for the user to connect to