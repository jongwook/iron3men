; ModuleID = '<stdin>'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@.str = private constant [9 x i8] c"%d %d %d\00", align 1

define i32 @main() nounwind {
entry:
  %retval = alloca i32
  %x = alloca i32
  %y = alloca i32
  %z = alloca i32
  %i = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  store i32 0, i32* %x, align 4
  store i32 0, i32* %y, align 4
  store i32 0, i32* %z, align 4
  store i32 0, i32* %i, align 4
  br label %bb9

bb:                                               ; preds = %bb9
  %0 = load i32* %x, align 4
  %1 = add nsw i32 %0, 1
  store i32 %1, i32* %x, align 4
  %2 = load i32* %z, align 4
  %3 = add nsw i32 %2, 1
  store i32 %3, i32* %z, align 4
  %4 = load i32* %i, align 4
  %5 = icmp sle i32 %4, 79
  br i1 %5, label %bb1, label %bb2

bb1:                                              ; preds = %bb
  %6 = load i32* %x, align 4
  %7 = add nsw i32 %6, 1
  store i32 %7, i32* %x, align 4
  %8 = load i32* %z, align 4
  %9 = add nsw i32 %8, 1
  store i32 %9, i32* %z, align 4
  br label %bb3

bb2:                                              ; preds = %bb
  %10 = load i32* %y, align 4
  %11 = add nsw i32 %10, 1
  store i32 %11, i32* %y, align 4
  %12 = load i32* %z, align 4
  %13 = sub nsw i32 %12, 1
  store i32 %13, i32* %z, align 4
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %14 = load i32* %i, align 4
  %15 = icmp sgt i32 %14, 10
  br i1 %15, label %bb4, label %bb5

bb4:                                              ; preds = %bb3
  %16 = load i32* %y, align 4
  %17 = add nsw i32 %16, 1
  store i32 %17, i32* %y, align 4
  %18 = load i32* %z, align 4
  %19 = sub nsw i32 %18, 1
  store i32 %19, i32* %z, align 4
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %20 = load i32* %x, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, i32* %x, align 4
  %22 = load i32* %z, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %z, align 4
  %24 = load i32* %i, align 4
  switch i32 %24, label %bb8 [
    i32 1, label %bb6
    i32 2, label %bb7
  ]

bb6:                                              ; preds = %bb5
  %25 = load i32* %x, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %x, align 4
  br label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %27 = load i32* %y, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %y, align 4
  br label %bb8

bb8:                                              ; preds = %bb7, %bb5
  %29 = load i32* %z, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, i32* %z, align 4
  %31 = load i32* %x, align 4
  %32 = load i32* %y, align 4
  %33 = load i32* %z, align 4
  %34 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([9 x i8]* @.str, i32 0, i32 0), i32 %31, i32 %32, i32 %33) nounwind
  %35 = load i32* %i, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %i, align 4
  br label %bb9

bb9:                                              ; preds = %bb8, %entry
  %37 = load i32* %i, align 4
  %38 = icmp sle i32 %37, 99
  br i1 %38, label %bb, label %bb10

bb10:                                             ; preds = %bb9
  br label %return

return:                                           ; preds = %bb10
  %retval11 = load i32* %retval
  ret i32 %retval11
}

declare i32 @printf(i8* noalias, ...) nounwind
