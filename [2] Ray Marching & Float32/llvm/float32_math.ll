; ModuleID = '../float32/float32_math.c'
source_filename = "../float32/float32_math.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_sin(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #2
  br label %4

3:                                                ; preds = %4
  ret i32 %9

4:                                                ; preds = %1, %4
  %5 = phi i32 [ 0, %1 ], [ %16, %4 ]
  %6 = phi i32 [ 1065353216, %1 ], [ %13, %4 ]
  %7 = phi i32 [ %0, %1 ], [ %15, %4 ]
  %8 = phi i32 [ 0, %1 ], [ %9, %4 ]
  %9 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %7) #2
  %10 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #2
  %11 = tail call i32 @f32_add(i32 noundef %6, i32 noundef 1065353216) #2
  %12 = tail call i32 @f32_div(i32 noundef %10, i32 noundef %11) #2
  %13 = tail call i32 @f32_add(i32 noundef %11, i32 noundef 1065353216) #2
  %14 = tail call i32 @f32_div(i32 noundef %12, i32 noundef %13) #2
  %15 = tail call i32 @f32_negate(i32 noundef %14) #2
  %16 = add nuw nsw i32 %5, 1
  %17 = icmp eq i32 %16, 100
  br i1 %17, label %3, label %4, !llvm.loop !4
}

declare i32 @f32_mul(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @f32_add(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @f32_div(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @f32_negate(i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_cos(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #2
  br label %4

3:                                                ; preds = %4
  ret i32 %9

4:                                                ; preds = %1, %4
  %5 = phi i32 [ 0, %1 ], [ %16, %4 ]
  %6 = phi i32 [ 0, %1 ], [ %13, %4 ]
  %7 = phi i32 [ 1065353216, %1 ], [ %15, %4 ]
  %8 = phi i32 [ 0, %1 ], [ %9, %4 ]
  %9 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %7) #2
  %10 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #2
  %11 = tail call i32 @f32_add(i32 noundef %6, i32 noundef 1065353216) #2
  %12 = tail call i32 @f32_div(i32 noundef %10, i32 noundef %11) #2
  %13 = tail call i32 @f32_add(i32 noundef %11, i32 noundef 1065353216) #2
  %14 = tail call i32 @f32_div(i32 noundef %12, i32 noundef %13) #2
  %15 = tail call i32 @f32_negate(i32 noundef %14) #2
  %16 = add nuw nsw i32 %5, 1
  %17 = icmp eq i32 %16, 100
  br i1 %17, label %3, label %4, !llvm.loop !6
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_tan(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_sin(i32 noundef %0)
  %3 = tail call i32 @f32_cos(i32 noundef %0)
  %4 = tail call i32 @f32_div(i32 noundef %2, i32 noundef %3) #2
  ret i32 %4
}

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{!"clang version 18.1.8"}
!4 = distinct !{!4, !5}
!5 = !{!"llvm.loop.mustprogress"}
!6 = distinct !{!6, !5}
