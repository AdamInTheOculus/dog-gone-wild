#!/bin/bash

# Ensure there is only 1 extra argument
if [ $# -ne 1 ]
    then
        echo "Usage: sh leak.sh [main | hash]"
        exit 1
fi

# Clean up existing code
make clean

if [ "$1" = "main" ];
then
    make
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/main
elif [ "$1" = "hash" ];
then
    make hash
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/hash
else
    echo "Invalid argument. Nothing happened."
    exit 1
fi
