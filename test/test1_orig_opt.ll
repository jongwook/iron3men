; ModuleID = '<stdin>'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:32:64-f32:32:32-f64:32:64-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-linux-gnu"

@.str = private constant [10 x i8] c"%d %d %d \00", align 1
@.str1 = private constant [5 x i8] c"%ld\0A\00", align 1

define i32 @main() nounwind {
bb.nph:
  %0 = tail call i32 @clock() nounwind
  br label %bb

bb:                                               ; preds = %bb9, %bb.nph
  %1 = phi i32 [ 0, %bb.nph ], [ %14, %bb9 ]
  %z.021 = phi i32 [ 0, %bb.nph ], [ %z.2, %bb9 ]
  %x.020 = phi i32 [ 0, %bb.nph ], [ %x.6, %bb9 ]
  %y.119 = phi i32 [ 0, %bb.nph ], [ %y.5, %bb9 ]
  %2 = icmp slt i32 %1, 1499999999
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
  %9 = srem i32 %1, 20
  switch i32 %9, label %bb9 [
    i32 1, label %bb7
    i32 2, label %bb8
  ]

bb7:                                              ; preds = %bb
  %10 = add nsw i32 %x.2, 1
  br label %bb8

bb8:                                              ; preds = %bb7, %bb
  %x.3 = phi i32 [ %x.2, %bb ], [ %10, %bb7 ]
  %k.2 = phi i32 [ %k.0, %bb ], [ 3, %bb7 ]
  %11 = add nsw i32 %y.2, 1
  br label %bb9

bb9:                                              ; preds = %bb8, %bb
  %y.3 = phi i32 [ %y.2, %bb ], [ %11, %bb8 ]
  %x.4 = phi i32 [ %x.2, %bb ], [ %x.3, %bb8 ]
  %k.3 = phi i32 [ %k.0, %bb ], [ %k.2, %bb8 ]
  %12 = add nsw i32 %x.4, 3
  %x.5 = select i1 %2, i32 %12, i32 %x.4
  %z.2.v = select i1 %2, i32 1, i32 -1
  %13 = add nsw i32 %z.1, %z.2.v
  %z.2 = add i32 %13, %k.3
  %y.4 = add i32 %5, %7
  %y.5 = add i32 %y.4, %y.3
  %x.6 = add i32 %x.5, %8
  %14 = add nsw i32 %1, 1
  %exitcond1 = icmp eq i32 2000000000, %14
  br i1 %exitcond1, label %bb17, label %bb

bb17:                                             ; preds = %bb9
  %x.6.lcssa = phi i32 [ %x.6, %bb9 ]
  %y.5.lcssa = phi i32 [ %y.5, %bb9 ]
  %z.2.lcssa = phi i32 [ %z.2, %bb9 ]
  %15 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i32 0, i32 0), i32 %x.6.lcssa, i32 %y.5.lcssa, i32 %z.2.lcssa) nounwind
  %16 = tail call i32 @putchar(i32 10) nounwind
  %17 = tail call i32 @clock() nounwind
  %18 = sub nsw i32 %17, %0
  %19 = sdiv i32 %18, 1000
  %20 = tail call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([5 x i8]* @.str1, i32 0, i32 0), i32 %19) nounwind
  ret i32 undef
}

declare i32 @clock() nounwind

declare i32 @printf(i8* nocapture, ...) nounwind

declare i32 @putchar(i32) nounwind
