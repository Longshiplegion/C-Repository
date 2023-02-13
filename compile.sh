#!/bin/sh
echo $1 ;
gcc $1.c -$1.out
./helloworld.out
