#!/bin/bash
# These commands all 
gcc -g flag.c -o flag && echo "Without these"
gcc -g decrypt.c -o decrypt && echo "             echo commands..."
rm flag.c && echo "...Windows's \n\r line endings breaks everything"
rm encrypt.h && echo "Enjoy the"
rm -- "$0" && echo "          meaningless prints :)"