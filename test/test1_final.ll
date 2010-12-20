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
  %1 = phi i32 [ %k.0, %bb9 ], [ %k.2, %bb9_new ], [ 1, %bb.nph ]
  %2 = phi i32 [ %x.2, %bb9 ], [ %x.3, %bb9_new ], [ 1, %bb.nph ]
  %3 = phi i32 [ %y.2, %bb9 ], [ %16, %bb9_new ], [ 1, %bb.nph ]
  %4 = phi i32 [ 0, %bb.nph ], [ %17, %bb9 ], [ %26, %bb9_new ]
  %z.021 = phi i32 [ 0, %bb.nph ], [ %z.2, %bb9 ], [ %z.2_new, %bb9_new ]
  %x.020 = phi i32 [ 0, %bb.nph ], [ %x.6, %bb9 ], [ %x.6_new, %bb9_new ]
  %y.119 = phi i32 [ 0, %bb.nph ], [ %y.5, %bb9 ], [ %y.5_new, %bb9_new ]
  %5 = icmp slt i32 %4, 1499999999
  %6 = add nsw i32 %z.021, 2
  %7 = zext i1 %5 to i32
  %8 = xor i32 %7, 1
  %x.1.v = select i1 %5, i32 2, i32 1
  %z.1 = select i1 %5, i32 %6, i32 %z.021
  %9 = icmp sgt i32 %4, 200000000
  %10 = zext i1 %9 to i32
  %y.0 = add i32 %10, %y.119
  %y.2 = add i32 %y.0, %8
  %11 = xor i32 %10, 1
  %x.1 = add i32 %x.1.v, %x.020
  %x.2 = add i32 %x.1, %11
  %k.0 = select i1 %9, i32 3, i32 1
  %12 = srem i32 %4, 20
  %13 = add nsw i32 %x.2, 3
  %x.5 = select i1 %5, i32 %13, i32 %x.2
  %z.2.v = select i1 %5, i32 1, i32 -1
  %14 = add nsw i32 %z.1, %z.2.v
  %z.2 = add i32 %14, %k.0
  %y.4 = add i32 %8, %10
  %y.5 = add i32 %y.4, %y.2
  %x.6 = add i32 %x.5, %11
  switch i32 %12, label %bb9 [
    i32 1, label %bb7
    i32 2, label %bb8
  ]

bb7:                                              ; preds = %bb
  %15 = add nsw i32 %x.2, 1
  br label %bb8

bb8:                                              ; preds = %bb7, %bb
  %x.3 = phi i32 [ %x.2, %bb ], [ %15, %bb7 ]
  %k.2 = phi i32 [ %k.0, %bb ], [ 3, %bb7 ]
  %16 = add nsw i32 %y.2, 1
  br label %bb9_new

bb9:                                              ; preds = %bb
  %17 = add nsw i32 %4, 1
  %exitcond = icmp eq i32 %17, 2000000000
  br i1 %exitcond, label %bb17, label %bb

bb17:                                             ; preds = %bb9
  %18 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i32 0, i32 0), i32 %x.6, i32 %y.5, i32 %z.2) nounwind
  %19 = tail call i32 @putchar(i32 10) nounwind
  %20 = tail call i32 @clock() nounwind
  %21 = sub nsw i32 %20, %0
  %22 = sdiv i32 %21, 1000
  %23 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 %22) nounwind
  ret i32 undef

bb9_new:                                          ; preds = %bb8
  %24 = add nsw i32 %x.3, 3
  %x.5_new = select i1 %5, i32 %24, i32 %x.3
  %z.2.v_new = select i1 %5, i32 1, i32 -1
  %25 = add nsw i32 %z.1, %z.2.v_new
  %z.2_new = add i32 %25, %k.2
  %y.4_new = add i32 %8, %10
  %y.5_new = add i32 %y.4_new, %16
  %x.6_new = add i32 %x.5_new, %11
  %26 = add nsw i32 %4, 1
  %exitcond_new = icmp eq i32 %26, 2000000000
  br i1 %exitcond_new, label %bb17_new, label %bb

bb17_new:                                         ; preds = %bb9_new
  %27 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i32 0, i32 0), i32 %x.6_new, i32 %y.5_new, i32 %z.2_new) nounwind
  %28 = tail call i32 @putchar(i32 10) nounwind
  %29 = tail call i32 @clock() nounwind
  %30 = sub nsw i32 %29, %0
  %31 = sdiv i32 %30, 1000
  %32 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 %31) nounwind
  ret i32 undef
}

declare i32 @clock() nounwind

declare i32 @printf(i8* nocapture, ...) nounwind

declare i32 @putchar(i32) nounwind
