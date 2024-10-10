; ModuleID = '../app/app.c'
source_filename = "../app/app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind sspstrong uwtable
define i32 @sqr(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #4
  ret i32 %2
}

declare i32 @f32_mul(i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define i32 @dot_prod(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4, i32 noundef %5) local_unnamed_addr #0 {
  %7 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %3) #4
  %8 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %4) #4
  %9 = tail call i32 @f32_add(i32 noundef %7, i32 noundef %8) #4
  %10 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %5) #4
  %11 = tail call i32 @f32_add(i32 noundef %9, i32 noundef %10) #4
  ret i32 %11
}

declare i32 @f32_add(i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define i32 @dist2(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #4
  %5 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %1) #4
  %6 = tail call i32 @f32_add(i32 noundef %4, i32 noundef %5) #4
  %7 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %2) #4
  %8 = tail call i32 @f32_add(i32 noundef %6, i32 noundef %7) #4
  ret i32 %8
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @qrsqrt(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_div(i32 noundef %0, i32 noundef 1073741824) #4
  %3 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #4
  %4 = lshr i32 %0, 1
  %5 = sub nsw i32 1597463007, %4
  %6 = tail call i32 @f32_mul(i32 noundef %5, i32 noundef %5) #4
  %7 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %6) #4
  %8 = tail call i32 @f32_sub(i32 noundef %3, i32 noundef %7) #4
  %9 = tail call i32 @f32_mul(i32 noundef %5, i32 noundef %8) #4
  ret i32 %9
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #2

declare i32 @f32_div(i32 noundef, i32 noundef) local_unnamed_addr #1

declare i32 @f32_sub(i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: nounwind sspstrong uwtable
define i32 @combine(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = tail call i32 @f32_sub(i32 noundef 1065353216, i32 noundef %2) #4
  %5 = and i32 %0, 16711680
  %6 = zext nneg i32 %5 to i64
  %7 = tail call i32 @f32_from_ll(i64 noundef %6) #4
  %8 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #4
  %9 = and i32 %1, 16711680
  %10 = zext nneg i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #4
  %12 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %4) #4
  %13 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %12) #4
  %14 = tail call i64 @f32_to_ll(i32 noundef %13) #4
  %15 = trunc i64 %14 to i32
  %16 = and i32 %0, 65280
  %17 = zext nneg i32 %16 to i64
  %18 = tail call i32 @f32_from_ll(i64 noundef %17) #4
  %19 = tail call i32 @f32_mul(i32 noundef %18, i32 noundef %2) #4
  %20 = and i32 %1, 65280
  %21 = zext nneg i32 %20 to i64
  %22 = tail call i32 @f32_from_ll(i64 noundef %21) #4
  %23 = tail call i32 @f32_mul(i32 noundef %22, i32 noundef %4) #4
  %24 = tail call i32 @f32_add(i32 noundef %19, i32 noundef %23) #4
  %25 = tail call i64 @f32_to_ll(i32 noundef %24) #4
  %26 = trunc i64 %25 to i32
  %27 = and i32 %0, 255
  %28 = zext nneg i32 %27 to i64
  %29 = tail call i32 @f32_from_ll(i64 noundef %28) #4
  %30 = tail call i32 @f32_mul(i32 noundef %29, i32 noundef %2) #4
  %31 = and i32 %1, 255
  %32 = zext nneg i32 %31 to i64
  %33 = tail call i32 @f32_from_ll(i64 noundef %32) #4
  %34 = tail call i32 @f32_mul(i32 noundef %33, i32 noundef %4) #4
  %35 = tail call i32 @f32_add(i32 noundef %30, i32 noundef %34) #4
  %36 = tail call i64 @f32_to_ll(i32 noundef %35) #4
  %37 = trunc i64 %36 to i32
  %38 = and i32 %15, 16711680
  %39 = and i32 %26, 65280
  %40 = or disjoint i32 %39, %38
  %41 = and i32 %37, 255
  %42 = or disjoint i32 %40, %41
  ret i32 %42
}

declare i64 @f32_to_ll(i32 noundef) local_unnamed_addr #1

declare i32 @f32_from_ll(i64 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define i32 @shadow(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = tail call i32 @combine(i32 noundef %0, i32 noundef 12303291, i32 noundef %1), !range !4
  ret i32 %3
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @reflection(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = icmp eq i32 %1, -1
  br i1 %4, label %48, label %5

5:                                                ; preds = %3
  %6 = and i32 %1, 16711680
  %7 = zext nneg i32 %6 to i64
  %8 = tail call i32 @f32_from_ll(i64 noundef %7) #4
  %9 = and i32 %0, 16711680
  %10 = zext nneg i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #4
  %12 = tail call i32 @f32_mul(i32 noundef %8, i32 noundef %11) #4
  %13 = tail call i32 @f32_mul(i32 noundef %12, i32 noundef %2) #4
  %14 = tail call i32 @f32_from_ll(i64 noundef 16711680) #4
  %15 = tail call i32 @f32_div(i32 noundef %13, i32 noundef %14) #4
  %16 = tail call i64 @f32_to_ll(i32 noundef %15) #4
  %17 = trunc i64 %16 to i32
  %18 = and i32 %17, 16711680
  %19 = and i32 %1, 65280
  %20 = zext nneg i32 %19 to i64
  %21 = tail call i32 @f32_from_ll(i64 noundef %20) #4
  %22 = and i32 %0, 65280
  %23 = zext nneg i32 %22 to i64
  %24 = tail call i32 @f32_from_ll(i64 noundef %23) #4
  %25 = tail call i32 @f32_mul(i32 noundef %21, i32 noundef %24) #4
  %26 = tail call i32 @f32_mul(i32 noundef %25, i32 noundef %2) #4
  %27 = tail call i32 @f32_from_ll(i64 noundef 65280) #4
  %28 = tail call i32 @f32_div(i32 noundef %26, i32 noundef %27) #4
  %29 = tail call i64 @f32_to_ll(i32 noundef %28) #4
  %30 = trunc i64 %29 to i32
  %31 = and i32 %30, 65280
  %32 = and i32 %1, 255
  %33 = zext nneg i32 %32 to i64
  %34 = tail call i32 @f32_from_ll(i64 noundef %33) #4
  %35 = and i32 %0, 255
  %36 = zext nneg i32 %35 to i64
  %37 = tail call i32 @f32_from_ll(i64 noundef %36) #4
  %38 = tail call i32 @f32_mul(i32 noundef %34, i32 noundef %37) #4
  %39 = tail call i32 @f32_mul(i32 noundef %38, i32 noundef %2) #4
  %40 = tail call i32 @f32_from_ll(i64 noundef 255) #4
  %41 = tail call i32 @f32_div(i32 noundef %39, i32 noundef %40) #4
  %42 = tail call i64 @f32_to_ll(i32 noundef %41) #4
  %43 = trunc i64 %42 to i32
  %44 = and i32 %43, 255
  %45 = or disjoint i32 %31, %18
  %46 = or disjoint i32 %45, %44
  %47 = tail call i32 @combine(i32 noundef %0, i32 noundef %46, i32 noundef %2), !range !4
  br label %48

48:                                               ; preds = %3, %5
  %49 = phi i32 [ %47, %5 ], [ %0, %3 ]
  ret i32 %49
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @ray_impl(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef readonly %2, ptr nocapture noundef readonly %3, ptr nocapture noundef readonly %4, ptr nocapture noundef readonly %5, i32 noundef %6, i32 noundef %7, i32 noundef %8, i32 noundef %9, i32 noundef %10, i32 noundef %11, i32 noundef %12, i32 noundef %13) local_unnamed_addr #0 {
  br label %15

15:                                               ; preds = %22, %14
  %16 = phi i32 [ %12, %14 ], [ %20, %22 ]
  %17 = phi i32 [ %8, %14 ], [ %28, %22 ]
  %18 = phi i32 [ %7, %14 ], [ %26, %22 ]
  %19 = phi i32 [ %6, %14 ], [ %24, %22 ]
  %20 = add i32 %16, -1
  %21 = icmp eq i32 %16, 0
  br i1 %21, label %131, label %32

22:                                               ; preds = %75
  %23 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %77) #4
  %24 = tail call i32 @f32_add(i32 noundef %19, i32 noundef %23) #4
  %25 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %77) #4
  %26 = tail call i32 @f32_add(i32 noundef %18, i32 noundef %25) #4
  %27 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %77) #4
  %28 = tail call i32 @f32_add(i32 noundef %17, i32 noundef %27) #4
  %29 = tail call i32 @f32_div(i32 noundef 1065353216, i32 noundef 1120403456) #4
  %30 = tail call signext i8 @f32_less(i32 noundef %77, i32 noundef %29) #4
  %31 = icmp eq i8 %30, 0
  br i1 %31, label %15, label %80

32:                                               ; preds = %15, %75
  %33 = phi i64 [ %78, %75 ], [ 0, %15 ]
  %34 = phi i32 [ %77, %75 ], [ 1203982336, %15 ]
  %35 = phi i32 [ %76, %75 ], [ 0, %15 ]
  %36 = getelementptr i32, ptr %0, i64 %33
  %37 = load i32, ptr %36, align 4, !tbaa !5
  %38 = tail call i32 @f32_sub(i32 noundef %37, i32 noundef %19) #4
  %39 = getelementptr i32, ptr %1, i64 %33
  %40 = load i32, ptr %39, align 4, !tbaa !5
  %41 = tail call i32 @f32_sub(i32 noundef %40, i32 noundef %18) #4
  %42 = getelementptr i32, ptr %2, i64 %33
  %43 = load i32, ptr %42, align 4, !tbaa !5
  %44 = tail call i32 @f32_sub(i32 noundef %43, i32 noundef %17) #4
  %45 = tail call i32 @f32_mul(i32 noundef %38, i32 noundef %38) #4
  %46 = tail call i32 @f32_mul(i32 noundef %41, i32 noundef %41) #4
  %47 = tail call i32 @f32_add(i32 noundef %45, i32 noundef %46) #4
  %48 = tail call i32 @f32_mul(i32 noundef %44, i32 noundef %44) #4
  %49 = tail call i32 @f32_add(i32 noundef %47, i32 noundef %48) #4
  %50 = tail call i32 @f32_div(i32 noundef %49, i32 noundef 1073741824) #4
  %51 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #4
  %52 = lshr i32 %49, 1
  %53 = sub nsw i32 1597463007, %52
  %54 = tail call i32 @f32_mul(i32 noundef %53, i32 noundef %53) #4
  %55 = tail call i32 @f32_mul(i32 noundef %50, i32 noundef %54) #4
  %56 = tail call i32 @f32_sub(i32 noundef %51, i32 noundef %55) #4
  %57 = tail call i32 @f32_mul(i32 noundef %53, i32 noundef %56) #4
  %58 = tail call i32 @f32_mul(i32 noundef %49, i32 noundef %57) #4
  %59 = getelementptr i32, ptr %3, i64 %33
  %60 = load i32, ptr %59, align 4, !tbaa !5
  %61 = tail call i32 @f32_sub(i32 noundef %58, i32 noundef %60) #4
  %62 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %38) #4
  %63 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %41) #4
  %64 = tail call i32 @f32_add(i32 noundef %62, i32 noundef %63) #4
  %65 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %44) #4
  %66 = tail call i32 @f32_add(i32 noundef %64, i32 noundef %65) #4
  %67 = tail call signext i8 @f32_less(i32 noundef %61, i32 noundef %34) #4
  %68 = icmp eq i8 %67, 0
  br i1 %68, label %75, label %69

69:                                               ; preds = %32
  %70 = tail call signext i8 @f32_less(i32 noundef 0, i32 noundef %66) #4
  %71 = icmp eq i8 %70, 0
  %72 = trunc i64 %33 to i32
  %73 = select i1 %71, i32 %35, i32 %72
  %74 = select i1 %71, i32 %34, i32 %61
  br label %75

75:                                               ; preds = %69, %32
  %76 = phi i32 [ %35, %32 ], [ %73, %69 ]
  %77 = phi i32 [ %34, %32 ], [ %74, %69 ]
  %78 = add nuw nsw i64 %33, 1
  %79 = icmp eq i64 %78, 3
  br i1 %79, label %22, label %32, !llvm.loop !9

80:                                               ; preds = %22
  %81 = sext i32 %76 to i64
  %82 = getelementptr i32, ptr %0, i64 %81
  %83 = load i32, ptr %82, align 4, !tbaa !5
  %84 = tail call i32 @f32_sub(i32 noundef %83, i32 noundef %24) #4
  %85 = getelementptr i32, ptr %1, i64 %81
  %86 = load i32, ptr %85, align 4, !tbaa !5
  %87 = tail call i32 @f32_sub(i32 noundef %86, i32 noundef %26) #4
  %88 = getelementptr i32, ptr %2, i64 %81
  %89 = load i32, ptr %88, align 4, !tbaa !5
  %90 = tail call i32 @f32_sub(i32 noundef %89, i32 noundef %28) #4
  %91 = tail call i32 @f32_mul(i32 noundef %84, i32 noundef %84) #4
  %92 = tail call i32 @f32_mul(i32 noundef %87, i32 noundef %87) #4
  %93 = tail call i32 @f32_add(i32 noundef %91, i32 noundef %92) #4
  %94 = tail call i32 @f32_mul(i32 noundef %90, i32 noundef %90) #4
  %95 = tail call i32 @f32_add(i32 noundef %93, i32 noundef %94) #4
  %96 = tail call i32 @f32_div(i32 noundef %95, i32 noundef 1073741824) #4
  %97 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #4
  %98 = lshr i32 %95, 1
  %99 = sub nsw i32 1597463007, %98
  %100 = tail call i32 @f32_mul(i32 noundef %99, i32 noundef %99) #4
  %101 = tail call i32 @f32_mul(i32 noundef %96, i32 noundef %100) #4
  %102 = tail call i32 @f32_sub(i32 noundef %97, i32 noundef %101) #4
  %103 = tail call i32 @f32_mul(i32 noundef %99, i32 noundef %102) #4
  %104 = tail call i32 @f32_mul(i32 noundef %84, i32 noundef %103) #4
  %105 = tail call i32 @f32_mul(i32 noundef %87, i32 noundef %103) #4
  %106 = tail call i32 @f32_mul(i32 noundef %90, i32 noundef %103) #4
  %107 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %104) #4
  %108 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %105) #4
  %109 = tail call i32 @f32_add(i32 noundef %107, i32 noundef %108) #4
  %110 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %106) #4
  %111 = tail call i32 @f32_add(i32 noundef %109, i32 noundef %110) #4
  %112 = tail call i32 @f32_mul(i32 noundef 1073741824, i32 noundef %111) #4
  %113 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %104) #4
  %114 = tail call i32 @f32_sub(i32 noundef %9, i32 noundef %113) #4
  %115 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %105) #4
  %116 = tail call i32 @f32_sub(i32 noundef %10, i32 noundef %115) #4
  %117 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %106) #4
  %118 = tail call i32 @f32_sub(i32 noundef %11, i32 noundef %117) #4
  %119 = icmp eq i32 %13, 0
  br i1 %119, label %123, label %120

120:                                              ; preds = %80
  %121 = add i32 %13, -1
  %122 = tail call i32 @ray_impl(ptr noundef nonnull %0, ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef nonnull %3, ptr noundef %4, ptr noundef %5, i32 noundef %24, i32 noundef %26, i32 noundef %28, i32 noundef %114, i32 noundef %116, i32 noundef %118, i32 noundef %20, i32 noundef %121)
  br label %123

123:                                              ; preds = %120, %80
  %124 = phi i32 [ %122, %120 ], [ -1, %80 ]
  %125 = getelementptr i32, ptr %5, i64 %81
  %126 = load i32, ptr %125, align 4, !tbaa !5
  %127 = getelementptr i32, ptr %4, i64 %81
  %128 = load i32, ptr %127, align 4, !tbaa !5
  %129 = tail call i32 @reflection(i32 noundef %126, i32 noundef %124, i32 noundef %128)
  %130 = tail call i32 @combine(i32 noundef %129, i32 noundef 12303291, i32 noundef %111), !range !4
  br label %131

131:                                              ; preds = %15, %123
  %132 = phi i32 [ %130, %123 ], [ -1, %15 ]
  ret i32 %132
}

declare signext i8 @f32_less(i32 noundef, i32 noundef) local_unnamed_addr #1

; Function Attrs: nounwind sspstrong uwtable
define i32 @ray(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef readonly %2, ptr nocapture noundef readonly %3, ptr nocapture noundef readonly %4, ptr nocapture noundef readonly %5, i32 noundef %6, i32 noundef %7) local_unnamed_addr #0 {
  %9 = add i32 %6, -250
  %10 = sext i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #4
  %12 = sub i32 250, %7
  %13 = sext i32 %12 to i64
  %14 = tail call i32 @f32_from_ll(i64 noundef %13) #4
  %15 = tail call i32 @f32_from_ll(i64 noundef 200) #4
  %16 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %11) #4
  %17 = tail call i32 @f32_mul(i32 noundef %14, i32 noundef %14) #4
  %18 = tail call i32 @f32_add(i32 noundef %16, i32 noundef %17) #4
  %19 = tail call i32 @f32_mul(i32 noundef %15, i32 noundef %15) #4
  %20 = tail call i32 @f32_add(i32 noundef %18, i32 noundef %19) #4
  %21 = tail call i32 @f32_div(i32 noundef %20, i32 noundef 1073741824) #4
  %22 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #4
  %23 = lshr i32 %20, 1
  %24 = sub nsw i32 1597463007, %23
  %25 = tail call i32 @f32_mul(i32 noundef %24, i32 noundef %24) #4
  %26 = tail call i32 @f32_mul(i32 noundef %21, i32 noundef %25) #4
  %27 = tail call i32 @f32_sub(i32 noundef %22, i32 noundef %26) #4
  %28 = tail call i32 @f32_mul(i32 noundef %24, i32 noundef %27) #4
  %29 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %28) #4
  %30 = tail call i32 @f32_mul(i32 noundef %14, i32 noundef %28) #4
  %31 = tail call i32 @f32_mul(i32 noundef %15, i32 noundef %28) #4
  %32 = tail call i32 @ray_impl(ptr noundef %0, ptr noundef %1, ptr noundef %2, ptr noundef %3, ptr noundef %4, ptr noundef %5, i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %29, i32 noundef %30, i32 noundef %31, i32 noundef 20, i32 noundef 10)
  %33 = icmp eq i32 %32, -1
  %34 = select i1 %33, i32 12303291, i32 %32
  ret i32 %34
}

; Function Attrs: nounwind sspstrong uwtable
define void @init(ptr nocapture noundef writeonly %0, ptr nocapture noundef writeonly %1, ptr nocapture noundef writeonly %2, ptr nocapture noundef writeonly %3, ptr nocapture noundef writeonly %4, ptr nocapture noundef writeonly %5) local_unnamed_addr #0 {
  store i32 -1041235968, ptr %0, align 4, !tbaa !5
  %7 = getelementptr i32, ptr %0, i64 1
  store i32 1106247680, ptr %7, align 4, !tbaa !5
  %8 = getelementptr i32, ptr %0, i64 2
  store i32 0, ptr %8, align 4, !tbaa !5
  store i32 0, ptr %1, align 4, !tbaa !5
  %9 = getelementptr i32, ptr %1, i64 1
  store i32 0, ptr %9, align 4, !tbaa !5
  %10 = getelementptr i32, ptr %1, i64 2
  store i32 1103626240, ptr %10, align 4, !tbaa !5
  %11 = getelementptr i32, ptr %2, i64 2
  store i32 1106247680, ptr %11, align 4, !tbaa !5
  %12 = getelementptr i32, ptr %2, i64 1
  store i32 1106247680, ptr %12, align 4, !tbaa !5
  store i32 1106247680, ptr %2, align 4, !tbaa !5
  %13 = getelementptr i32, ptr %3, i64 2
  store i32 1101004800, ptr %13, align 4, !tbaa !5
  %14 = getelementptr i32, ptr %3, i64 1
  store i32 1101004800, ptr %14, align 4, !tbaa !5
  store i32 1101004800, ptr %3, align 4, !tbaa !5
  %15 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1082130432) #4
  %16 = getelementptr i32, ptr %4, i64 2
  store i32 %15, ptr %16, align 4, !tbaa !5
  %17 = getelementptr i32, ptr %4, i64 1
  store i32 %15, ptr %17, align 4, !tbaa !5
  store i32 %15, ptr %4, align 4, !tbaa !5
  store i32 16711680, ptr %5, align 4, !tbaa !5
  %18 = getelementptr i32, ptr %5, i64 1
  store i32 16776960, ptr %18, align 4, !tbaa !5
  %19 = getelementptr i32, ptr %5, i64 2
  store i32 65280, ptr %19, align 4, !tbaa !5
  ret void
}

; Function Attrs: nounwind sspstrong uwtable
define void @app() local_unnamed_addr #0 {
  %1 = alloca [3 x i32], align 4
  %2 = alloca [3 x i32], align 4
  %3 = alloca [3 x i32], align 4
  %4 = alloca [3 x i32], align 4
  %5 = alloca [3 x i32], align 4
  %6 = alloca [3 x i32], align 4
  %7 = alloca [500 x [500 x i32]], align 16
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %1) #4
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %2) #4
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %3) #4
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %4) #4
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %5) #4
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %6) #4
  store i32 -1041235968, ptr %1, align 4, !tbaa !5
  %8 = getelementptr inbounds i32, ptr %1, i64 1
  store i32 1106247680, ptr %8, align 4, !tbaa !5
  %9 = getelementptr inbounds i32, ptr %1, i64 2
  store i32 0, ptr %9, align 4, !tbaa !5
  store i32 0, ptr %2, align 4, !tbaa !5
  %10 = getelementptr inbounds i32, ptr %2, i64 1
  store i32 0, ptr %10, align 4, !tbaa !5
  %11 = getelementptr inbounds i32, ptr %2, i64 2
  store i32 1103626240, ptr %11, align 4, !tbaa !5
  %12 = getelementptr inbounds i32, ptr %3, i64 2
  store i32 1106247680, ptr %12, align 4, !tbaa !5
  %13 = getelementptr inbounds i32, ptr %3, i64 1
  store i32 1106247680, ptr %13, align 4, !tbaa !5
  store i32 1106247680, ptr %3, align 4, !tbaa !5
  %14 = getelementptr inbounds i32, ptr %4, i64 2
  store i32 1101004800, ptr %14, align 4, !tbaa !5
  %15 = getelementptr inbounds i32, ptr %4, i64 1
  store i32 1101004800, ptr %15, align 4, !tbaa !5
  store i32 1101004800, ptr %4, align 4, !tbaa !5
  %16 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1082130432) #4
  %17 = getelementptr inbounds i32, ptr %5, i64 2
  store i32 %16, ptr %17, align 4, !tbaa !5
  %18 = getelementptr inbounds i32, ptr %5, i64 1
  store i32 %16, ptr %18, align 4, !tbaa !5
  store i32 %16, ptr %5, align 4, !tbaa !5
  store i32 16711680, ptr %6, align 4, !tbaa !5
  %19 = getelementptr inbounds i32, ptr %6, i64 1
  store i32 16776960, ptr %19, align 4, !tbaa !5
  %20 = getelementptr inbounds i32, ptr %6, i64 2
  store i32 65280, ptr %20, align 4, !tbaa !5
  call void @llvm.lifetime.start.p0(i64 1000000, ptr nonnull %7) #4
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(1000000) %7, i8 0, i64 1000000, i1 false), !tbaa !5
  br label %21

21:                                               ; preds = %0, %35
  %22 = phi i64 [ 0, %0 ], [ %36, %35 ]
  %23 = trunc i64 %22 to i32
  br label %25

24:                                               ; preds = %35
  call void @llvm.lifetime.end.p0(i64 1000000, ptr nonnull %7) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %6) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %5) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %4) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %3) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %2) #4
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %1) #4
  ret void

25:                                               ; preds = %21, %25
  %26 = phi i64 [ 0, %21 ], [ %30, %25 ]
  %27 = trunc i64 %26 to i32
  %28 = call i32 @ray(ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef nonnull %3, ptr noundef nonnull %4, ptr noundef nonnull %5, ptr noundef nonnull %6, i32 noundef %23, i32 noundef %27)
  %29 = getelementptr [500 x [500 x i32]], ptr %7, i64 0, i64 %22, i64 %26
  store i32 %28, ptr %29, align 4, !tbaa !5
  %30 = add nuw nsw i64 %26, 1
  %31 = icmp eq i64 %30, 500
  br i1 %31, label %32, label %25, !llvm.loop !11

32:                                               ; preds = %25, %38
  %33 = phi i64 [ %39, %38 ], [ 0, %25 ]
  %34 = trunc i64 %33 to i32
  br label %41

35:                                               ; preds = %38
  tail call void (...) @simFlush() #4
  %36 = add nuw nsw i64 %22, 1
  %37 = icmp eq i64 %36, 500
  br i1 %37, label %24, label %21, !llvm.loop !12

38:                                               ; preds = %41
  %39 = add nuw nsw i64 %33, 1
  %40 = icmp eq i64 %39, 500
  br i1 %40, label %35, label %32, !llvm.loop !13

41:                                               ; preds = %32, %41
  %42 = phi i64 [ 0, %32 ], [ %46, %41 ]
  %43 = getelementptr [500 x [500 x i32]], ptr %7, i64 0, i64 %33, i64 %42
  %44 = load i32, ptr %43, align 4, !tbaa !5
  %45 = trunc i64 %42 to i32
  tail call void @simPutPixel(i32 noundef %34, i32 noundef %45, i32 noundef %44) #4
  %46 = add nuw nsw i64 %42, 1
  %47 = icmp eq i64 %46, 500
  br i1 %47, label %38, label %41, !llvm.loop !14
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #1

declare void @simFlush(...) local_unnamed_addr #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #3

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #1 = { "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"uwtable", i32 2}
!3 = !{!"clang version 18.1.8"}
!4 = !{i32 0, i32 16777216}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
