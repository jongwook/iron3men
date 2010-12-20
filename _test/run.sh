#! /bin/bash

llvm-gcc -emit-llvm -c test.c -o test.bc -O3 
opt -f -load ../Release+Profile/lib/libiron3men.so -super test.bc > test.opt.bc
llvm-dis test.bc -o test.ll
llvm-dis test.opt.bc -o test.opt.ll
llc test.opt.bc -o test.s
gcc test.s -o test


