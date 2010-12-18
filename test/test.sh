#!/bin/bash
rm $1.ll $1.bc $1.ls.bc $1.lamp.bc $1.lamp.s $1.lamp.exe $1_opt.bc $1_final.bc $1_final.exe $1_final.s
llvm-gcc -emit-llvm -o $1.bc -c $1.c
llc < $1.bc > $1.s
llvm-dis < $1.bc > $1.orig.ll
opt -load ../Release+Profile/lib/libiron3men.so -sb-opt-loop < $1.bc > $1_final.bc
llc < $1_final.bc > $1_final.s
g++ -o $1_final.exe $1_final.s
./$1_final.exe
llvm-dis < $1_final.bc > $1.ll
