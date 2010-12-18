#!/bin/bash
rm llvmprof.out
llvm-gcc -O3 -emit-llvm $1.c -c -o $1.bc
llvm-dis < $1.bc > $1_orig.ll
opt -q -insert-edge-profiling -f $1.bc -o $1.profile.bc
llc -f $1.profile.bc -o $1.profile.s	
g++ -O3 -o $1.profile $1.profile.s ../../../Release+Profile/lib/profile_rt.so
./$1.profile
llvm-prof $1.bc llvmprof.out 
opt -f -load ../Release+Profile/lib/libiron3men.so -profile-loader -profile-info-file=llvmprof.out -sb-opt-loop $1.bc -o $1_final.bc
llc < $1_final.bc > $1_final.s
g++ -o $1_final.exe $1_final.s
llvm-dis < $1_final.bc > $1_final.ll
##g++ -O3 -o $1.profile $1.profile.s ../Release+Profile/lib/libiron3men.so
#llvm-prof $1.bc llvmprof.out

opt -f -die -adce -correlated-propagation -dse $1_final.bc -o $1_final_opt.bc
opt -f -die -adce -correlated-propagation -dse $1.bc -o $1_orig_opt.bc
llvm-dis < $1_final_opt.bc > $1_final_opt.ll
llvm-dis < $1_orig_opt.bc > $1_orig_opt.ll

llc < $1_final_opt.bc > $1_final_opt.s
llc < $1_orig_opt.bc > $1_orig_opt.s
llc < $1.bc > $1.s
g++ -O3 -o $1.exe $1.s
g++ -O3 -o $1_final_opt.exe $1_final_opt.s
g++ -O3 -o $1_orig_opt.exe $1_orig_opt.s
