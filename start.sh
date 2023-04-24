#!/bin/bash
# These commands all 
gcc -g flag.c -o flag && echo "Without these echo commands..."
rm flag.c && echo "...Windows's '\n\r' line endings break everything"
rm encrypt.h && echo "Enjoy the"
rm -- "$0" && echo "          meaningless prints :)"