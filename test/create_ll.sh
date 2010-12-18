#!/bin/bash
llvm-gcc -O3 -emit-llvm -o $1.bc -c $1.c
llvm-dis < $1.bc > $1.ll
