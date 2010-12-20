#!/bin/bash
rm $1.bc $1.ls.bc $1.lamp.bc $1.lamp.s $1.lamp.exe $1_opt.bc $1_final.bc $1_final.exe $1_final.s
llvm-gcc -emit-llvm -o $1.bc -c $1.c
llc < $1.bc > $1.s
opt -loopsimplify < $1.bc  > $1.ls.bc
opt -load ../Release+Profile/lib/lib583hw2.so -lamp-insts  -insert-lamp-profiling -insert-lamp-loop-profiling  -insert-lamp-init < $1.ls.bc > $1.lamp.bc
llc < $1.lamp.bc > $1.lamp.s
g++ -o $1.lamp.exe $1.lamp.s lamp_hooks.o
./$1.lamp.exe $2
opt -load ../Release+Profile/lib/lib583hw2.so -lamp-inst-cnt -lamp-map-loop -lamp-load-profile -hw2pass < $1.ls.bc > $1_opt.bc
opt -mem2reg < $1_opt.bc > $1_final.bc
llc < $1_final.bc > $1_final.s
g++ -o $1_final.exe $1_final.s
./$1_final.exe
llvm-dis < $1.bc > $1.ll
