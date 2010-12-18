; ModuleID = '<stdin>'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@.str = private constant [10 x i8] c"%d %d %d \00", align 1
@.str1 = private constant [5 x i8] c"%ld\0A\00", align 1

define i32 @main() nounwind {
bb.nph:
  %0 = tail call i32 @clock() nounwind
  br label %bb

bb:                                               ; preds = %bb9_new, %bb9, %bb.nph
  %1 = phi i32 [ 0, %bb.nph ], [ %13, %bb9 ], [ %22, %bb9_new ]
  %z.021 = phi i32 [ 0, %bb.nph ], [ %z.2, %bb9 ], [ %z.2_new, %bb9_new ]
  %x.020 = phi i32 [ 0, %bb.nph ], [ %x.6, %bb9 ], [ %x.6_new, %bb9_new ]
  %y.119 = phi i32 [ 0, %bb.nph ], [ %y.5, %bb9 ], [ %y.5_new, %bb9_new ]
  %2 = icmp slt i32 %1, 1999999999
  %3 = add nsw i32 %z.021, 2
  %4 = zext i1 %2 to i32
  %5 = xor i32 %4, 1
  %x.1.v = select i1 %2, i32 2, i32 1
  %z.1 = select i1 %2, i32 %3, i32 %z.021
  %6 = icmp sgt i32 %1, 200000000
  %7 = zext i1 %6 to i32
  %y.0 = add i32 %7, %y.119
  %y.2 = add i32 %y.0, %5
  %8 = xor i32 %7, 1
  %x.1 = add i32 %x.1.v, %x.020
  %x.2 = add i32 %x.1, %8
  %k.0 = select i1 %6, i32 3, i32 1
  %9 = add nsw i32 %x.2, 3
  %x.5 = select i1 %2, i32 %9, i32 %x.2
  %z.2.v = select i1 %2, i32 1, i32 -1
  %10 = add nsw i32 %z.1, %z.2.v
  %z.2 = add i32 %10, %k.0
  %y.4 = add i32 %5, %7
  %y.5 = add i32 %y.4, %y.2
  %x.6 = add i32 %x.5, %8
  switch i32 %1, label %bb9 [
    i32 1, label %bb7
    i32 2, label %bb8
  ]

bb7:                                              ; preds = %bb
  %11 = add nsw i32 %x.2, 1
  br label %bb8

bb8:                                              ; preds = %bb7, %bb
  %x.3 = phi i32 [ %x.2, %bb ], [ %11, %bb7 ]
  %k.2 = phi i32 [ %k.0, %bb ], [ 3, %bb7 ]
  %12 = add nsw i32 %y.2, 1
  br label %bb9_new

bb9:                                              ; preds = %bb
  %13 = add nsw i32 %1, 1
  %exitcond = icmp eq i32 %13, 2000000000
  br i1 %exitcond, label %bb17, label %bb

bb17:                                             ; preds = %bb9
  %14 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i32 0, i32 0), i32 %x.6, i32 %y.5, i32 %z.2) nounwind
  %15 = tail call i32 @putchar(i32 10) nounwind
  %16 = tail call i32 @clock() nounwind
  %17 = sub nsw i32 %16, %0
  %18 = sdiv i32 %17, 1000
  %19 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 %18) nounwind
  ret i32 undef

bb9_new:                                          ; preds = %bb8
  %20 = add nsw i32 %x.3, 3
  %x.5_new = select i1 %2, i32 %20, i32 %x.3
  %z.2.v_new = select i1 %2, i32 1, i32 -1
  %21 = add nsw i32 %z.1, %z.2.v_new
  %z.2_new = add i32 %21, %k.2
  %y.4_new = add i32 %5, %7
  %y.5_new = add i32 %y.4_new, %12
  %x.6_new = add i32 %x.5_new, %8
  %22 = add nsw i32 %1, 1
  %exitcond_new = icmp eq i32 %22, 2000000000
  br i1 %exitcond_new, label %bb17_new, label %bb

bb17_new:                                         ; preds = %bb9_new
  %23 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i32 0, i32 0), i32 %x.6_new, i32 %y.5_new, i32 %z.2_new) nounwind
  %24 = tail call i32 @putchar(i32 10) nounwind
  %25 = tail call i32 @clock() nounwind
  %26 = sub nsw i32 %25, %0
  %27 = sdiv i32 %26, 1000
  %28 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 %27) nounwind
  ret i32 undef
}

declare i32 @clock() nounwind

declare i32 @printf(i8* nocapture, ...) nounwind

declare i32 @putchar(i32) nounwind
