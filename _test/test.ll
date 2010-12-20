; ModuleID = 'test.bc'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@.str = private constant [6 x i8] c"%d %d\00", align 1
@.str1 = private constant [4 x i8] c"%d\0A\00", align 1

define i32 @main(i32 %argc, i8** nocapture %argv) nounwind {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %0 = call i32 (i8*, ...)* @"\01__isoc99_scanf"(i8* noalias getelementptr inbounds ([6 x i8]* @.str, i32 0, i32 0), i32* %a, i32* %b) nounwind
  %1 = load i32* %a, align 4
  %2 = mul nsw i32 %1, %1
  %3 = load i32* %b, align 4
  %4 = shl i32 %1, 1
  %tmp = add i32 %4, %3
  %tmp2 = mul i32 %tmp, %3
  %5 = add nsw i32 %tmp2, %2
  %6 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([4 x i8]* @.str1, i32 0, i32 0), i32 %5) nounwind
  ret i32 undef
}

declare i32 @"\01__isoc99_scanf"(i8* nocapture, ...) nounwind

declare i32 @printf(i8* nocapture, ...) nounwind
