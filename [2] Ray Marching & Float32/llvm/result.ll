; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind sspstrong uwtable
define i32 @sqr(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #7
  ret i32 %2
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @dot_prod(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4, i32 noundef %5) local_unnamed_addr #0 {
  %7 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %3) #7
  %8 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %4) #7
  %9 = tail call i32 @f32_add(i32 noundef %7, i32 noundef %8) #7
  %10 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %5) #7
  %11 = tail call i32 @f32_add(i32 noundef %9, i32 noundef %10) #7
  ret i32 %11
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @dist2(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #7
  %5 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %1) #7
  %6 = tail call i32 @f32_add(i32 noundef %4, i32 noundef %5) #7
  %7 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %2) #7
  %8 = tail call i32 @f32_add(i32 noundef %6, i32 noundef %7) #7
  ret i32 %8
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @qrsqrt(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_div(i32 noundef %0, i32 noundef 1073741824) #7
  %3 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #7
  %4 = lshr i32 %0, 1
  %5 = sub nsw i32 1597463007, %4
  %6 = tail call i32 @f32_mul(i32 noundef %5, i32 noundef %5) #7
  %7 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %6) #7
  %8 = tail call i32 @f32_sub(i32 noundef %3, i32 noundef %7) #7
  %9 = tail call i32 @f32_mul(i32 noundef %5, i32 noundef %8) #7
  ret i32 %9
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @combine(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = tail call i32 @f32_sub(i32 noundef 1065353216, i32 noundef %2) #7
  %5 = and i32 %0, 16711680
  %6 = zext nneg i32 %5 to i64
  %7 = tail call i32 @f32_from_ll(i64 noundef %6) #7
  %8 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #7
  %9 = and i32 %1, 16711680
  %10 = zext nneg i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #7
  %12 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %4) #7
  %13 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %12) #7
  %14 = tail call i64 @f32_to_ll(i32 noundef %13) #7
  %15 = trunc i64 %14 to i32
  %16 = and i32 %0, 65280
  %17 = zext nneg i32 %16 to i64
  %18 = tail call i32 @f32_from_ll(i64 noundef %17) #7
  %19 = tail call i32 @f32_mul(i32 noundef %18, i32 noundef %2) #7
  %20 = and i32 %1, 65280
  %21 = zext nneg i32 %20 to i64
  %22 = tail call i32 @f32_from_ll(i64 noundef %21) #7
  %23 = tail call i32 @f32_mul(i32 noundef %22, i32 noundef %4) #7
  %24 = tail call i32 @f32_add(i32 noundef %19, i32 noundef %23) #7
  %25 = tail call i64 @f32_to_ll(i32 noundef %24) #7
  %26 = trunc i64 %25 to i32
  %27 = and i32 %0, 255
  %28 = zext nneg i32 %27 to i64
  %29 = tail call i32 @f32_from_ll(i64 noundef %28) #7
  %30 = tail call i32 @f32_mul(i32 noundef %29, i32 noundef %2) #7
  %31 = and i32 %1, 255
  %32 = zext nneg i32 %31 to i64
  %33 = tail call i32 @f32_from_ll(i64 noundef %32) #7
  %34 = tail call i32 @f32_mul(i32 noundef %33, i32 noundef %4) #7
  %35 = tail call i32 @f32_add(i32 noundef %30, i32 noundef %34) #7
  %36 = tail call i64 @f32_to_ll(i32 noundef %35) #7
  %37 = trunc i64 %36 to i32
  %38 = and i32 %15, 16711680
  %39 = and i32 %26, 65280
  %40 = or disjoint i32 %39, %38
  %41 = and i32 %37, 255
  %42 = or disjoint i32 %40, %41
  ret i32 %42
}

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
  %8 = tail call i32 @f32_from_ll(i64 noundef %7) #7
  %9 = and i32 %0, 16711680
  %10 = zext nneg i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #7
  %12 = tail call i32 @f32_mul(i32 noundef %8, i32 noundef %11) #7
  %13 = tail call i32 @f32_mul(i32 noundef %12, i32 noundef %2) #7
  %14 = tail call i32 @f32_from_ll(i64 noundef 16711680) #7
  %15 = tail call i32 @f32_div(i32 noundef %13, i32 noundef %14) #7
  %16 = tail call i64 @f32_to_ll(i32 noundef %15) #7
  %17 = trunc i64 %16 to i32
  %18 = and i32 %17, 16711680
  %19 = and i32 %1, 65280
  %20 = zext nneg i32 %19 to i64
  %21 = tail call i32 @f32_from_ll(i64 noundef %20) #7
  %22 = and i32 %0, 65280
  %23 = zext nneg i32 %22 to i64
  %24 = tail call i32 @f32_from_ll(i64 noundef %23) #7
  %25 = tail call i32 @f32_mul(i32 noundef %21, i32 noundef %24) #7
  %26 = tail call i32 @f32_mul(i32 noundef %25, i32 noundef %2) #7
  %27 = tail call i32 @f32_from_ll(i64 noundef 65280) #7
  %28 = tail call i32 @f32_div(i32 noundef %26, i32 noundef %27) #7
  %29 = tail call i64 @f32_to_ll(i32 noundef %28) #7
  %30 = trunc i64 %29 to i32
  %31 = and i32 %30, 65280
  %32 = and i32 %1, 255
  %33 = zext nneg i32 %32 to i64
  %34 = tail call i32 @f32_from_ll(i64 noundef %33) #7
  %35 = and i32 %0, 255
  %36 = zext nneg i32 %35 to i64
  %37 = tail call i32 @f32_from_ll(i64 noundef %36) #7
  %38 = tail call i32 @f32_mul(i32 noundef %34, i32 noundef %37) #7
  %39 = tail call i32 @f32_mul(i32 noundef %38, i32 noundef %2) #7
  %40 = tail call i32 @f32_from_ll(i64 noundef 255) #7
  %41 = tail call i32 @f32_div(i32 noundef %39, i32 noundef %40) #7
  %42 = tail call i64 @f32_to_ll(i32 noundef %41) #7
  %43 = trunc i64 %42 to i32
  %44 = and i32 %43, 255
  %45 = or disjoint i32 %31, %18
  %46 = or disjoint i32 %45, %44
  %47 = tail call i32 @combine(i32 noundef %0, i32 noundef %46, i32 noundef %2), !range !4
  br label %48

48:                                               ; preds = %5, %3
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
  %23 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %77) #7
  %24 = tail call i32 @f32_add(i32 noundef %19, i32 noundef %23) #7
  %25 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %77) #7
  %26 = tail call i32 @f32_add(i32 noundef %18, i32 noundef %25) #7
  %27 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %77) #7
  %28 = tail call i32 @f32_add(i32 noundef %17, i32 noundef %27) #7
  %29 = tail call i32 @f32_div(i32 noundef 1065353216, i32 noundef 1120403456) #7
  %30 = tail call signext i8 @f32_less(i32 noundef %77, i32 noundef %29) #7
  %31 = icmp eq i8 %30, 0
  br i1 %31, label %15, label %80

32:                                               ; preds = %75, %15
  %33 = phi i64 [ %78, %75 ], [ 0, %15 ]
  %34 = phi i32 [ %77, %75 ], [ 1203982336, %15 ]
  %35 = phi i32 [ %76, %75 ], [ 0, %15 ]
  %36 = getelementptr i32, ptr %0, i64 %33
  %37 = load i32, ptr %36, align 4, !tbaa !5
  %38 = tail call i32 @f32_sub(i32 noundef %37, i32 noundef %19) #7
  %39 = getelementptr i32, ptr %1, i64 %33
  %40 = load i32, ptr %39, align 4, !tbaa !5
  %41 = tail call i32 @f32_sub(i32 noundef %40, i32 noundef %18) #7
  %42 = getelementptr i32, ptr %2, i64 %33
  %43 = load i32, ptr %42, align 4, !tbaa !5
  %44 = tail call i32 @f32_sub(i32 noundef %43, i32 noundef %17) #7
  %45 = tail call i32 @f32_mul(i32 noundef %38, i32 noundef %38) #7
  %46 = tail call i32 @f32_mul(i32 noundef %41, i32 noundef %41) #7
  %47 = tail call i32 @f32_add(i32 noundef %45, i32 noundef %46) #7
  %48 = tail call i32 @f32_mul(i32 noundef %44, i32 noundef %44) #7
  %49 = tail call i32 @f32_add(i32 noundef %47, i32 noundef %48) #7
  %50 = tail call i32 @f32_div(i32 noundef %49, i32 noundef 1073741824) #7
  %51 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #7
  %52 = lshr i32 %49, 1
  %53 = sub nsw i32 1597463007, %52
  %54 = tail call i32 @f32_mul(i32 noundef %53, i32 noundef %53) #7
  %55 = tail call i32 @f32_mul(i32 noundef %50, i32 noundef %54) #7
  %56 = tail call i32 @f32_sub(i32 noundef %51, i32 noundef %55) #7
  %57 = tail call i32 @f32_mul(i32 noundef %53, i32 noundef %56) #7
  %58 = tail call i32 @f32_mul(i32 noundef %49, i32 noundef %57) #7
  %59 = getelementptr i32, ptr %3, i64 %33
  %60 = load i32, ptr %59, align 4, !tbaa !5
  %61 = tail call i32 @f32_sub(i32 noundef %58, i32 noundef %60) #7
  %62 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %38) #7
  %63 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %41) #7
  %64 = tail call i32 @f32_add(i32 noundef %62, i32 noundef %63) #7
  %65 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %44) #7
  %66 = tail call i32 @f32_add(i32 noundef %64, i32 noundef %65) #7
  %67 = tail call signext i8 @f32_less(i32 noundef %61, i32 noundef %34) #7
  %68 = icmp eq i8 %67, 0
  br i1 %68, label %75, label %69

69:                                               ; preds = %32
  %70 = tail call signext i8 @f32_less(i32 noundef 0, i32 noundef %66) #7
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
  %84 = tail call i32 @f32_sub(i32 noundef %83, i32 noundef %24) #7
  %85 = getelementptr i32, ptr %1, i64 %81
  %86 = load i32, ptr %85, align 4, !tbaa !5
  %87 = tail call i32 @f32_sub(i32 noundef %86, i32 noundef %26) #7
  %88 = getelementptr i32, ptr %2, i64 %81
  %89 = load i32, ptr %88, align 4, !tbaa !5
  %90 = tail call i32 @f32_sub(i32 noundef %89, i32 noundef %28) #7
  %91 = tail call i32 @f32_mul(i32 noundef %84, i32 noundef %84) #7
  %92 = tail call i32 @f32_mul(i32 noundef %87, i32 noundef %87) #7
  %93 = tail call i32 @f32_add(i32 noundef %91, i32 noundef %92) #7
  %94 = tail call i32 @f32_mul(i32 noundef %90, i32 noundef %90) #7
  %95 = tail call i32 @f32_add(i32 noundef %93, i32 noundef %94) #7
  %96 = tail call i32 @f32_div(i32 noundef %95, i32 noundef 1073741824) #7
  %97 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #7
  %98 = lshr i32 %95, 1
  %99 = sub nsw i32 1597463007, %98
  %100 = tail call i32 @f32_mul(i32 noundef %99, i32 noundef %99) #7
  %101 = tail call i32 @f32_mul(i32 noundef %96, i32 noundef %100) #7
  %102 = tail call i32 @f32_sub(i32 noundef %97, i32 noundef %101) #7
  %103 = tail call i32 @f32_mul(i32 noundef %99, i32 noundef %102) #7
  %104 = tail call i32 @f32_mul(i32 noundef %84, i32 noundef %103) #7
  %105 = tail call i32 @f32_mul(i32 noundef %87, i32 noundef %103) #7
  %106 = tail call i32 @f32_mul(i32 noundef %90, i32 noundef %103) #7
  %107 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %104) #7
  %108 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %105) #7
  %109 = tail call i32 @f32_add(i32 noundef %107, i32 noundef %108) #7
  %110 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %106) #7
  %111 = tail call i32 @f32_add(i32 noundef %109, i32 noundef %110) #7
  %112 = tail call i32 @f32_mul(i32 noundef 1073741824, i32 noundef %111) #7
  %113 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %104) #7
  %114 = tail call i32 @f32_sub(i32 noundef %9, i32 noundef %113) #7
  %115 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %105) #7
  %116 = tail call i32 @f32_sub(i32 noundef %10, i32 noundef %115) #7
  %117 = tail call i32 @f32_mul(i32 noundef %112, i32 noundef %106) #7
  %118 = tail call i32 @f32_sub(i32 noundef %11, i32 noundef %117) #7
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

131:                                              ; preds = %123, %15
  %132 = phi i32 [ %130, %123 ], [ -1, %15 ]
  ret i32 %132
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @ray(ptr nocapture noundef readonly %0, ptr nocapture noundef readonly %1, ptr nocapture noundef readonly %2, ptr nocapture noundef readonly %3, ptr nocapture noundef readonly %4, ptr nocapture noundef readonly %5, i32 noundef %6, i32 noundef %7) local_unnamed_addr #0 {
  %9 = add i32 %6, -250
  %10 = sext i32 %9 to i64
  %11 = tail call i32 @f32_from_ll(i64 noundef %10) #7
  %12 = sub i32 250, %7
  %13 = sext i32 %12 to i64
  %14 = tail call i32 @f32_from_ll(i64 noundef %13) #7
  %15 = tail call i32 @f32_from_ll(i64 noundef 200) #7
  %16 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %11) #7
  %17 = tail call i32 @f32_mul(i32 noundef %14, i32 noundef %14) #7
  %18 = tail call i32 @f32_add(i32 noundef %16, i32 noundef %17) #7
  %19 = tail call i32 @f32_mul(i32 noundef %15, i32 noundef %15) #7
  %20 = tail call i32 @f32_add(i32 noundef %18, i32 noundef %19) #7
  %21 = tail call i32 @f32_div(i32 noundef %20, i32 noundef 1073741824) #7
  %22 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1073741824) #7
  %23 = lshr i32 %20, 1
  %24 = sub nsw i32 1597463007, %23
  %25 = tail call i32 @f32_mul(i32 noundef %24, i32 noundef %24) #7
  %26 = tail call i32 @f32_mul(i32 noundef %21, i32 noundef %25) #7
  %27 = tail call i32 @f32_sub(i32 noundef %22, i32 noundef %26) #7
  %28 = tail call i32 @f32_mul(i32 noundef %24, i32 noundef %27) #7
  %29 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %28) #7
  %30 = tail call i32 @f32_mul(i32 noundef %14, i32 noundef %28) #7
  %31 = tail call i32 @f32_mul(i32 noundef %15, i32 noundef %28) #7
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
  %15 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1082130432) #7
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
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %1) #7
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %2) #7
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %3) #7
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %4) #7
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %5) #7
  call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %6) #7
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
  %16 = tail call i32 @f32_div(i32 noundef 1077936128, i32 noundef 1082130432) #7
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
  call void @llvm.lifetime.start.p0(i64 1000000, ptr nonnull %7) #7
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(1000000) %7, i8 0, i64 1000000, i1 false), !tbaa !5
  br label %21

21:                                               ; preds = %35, %0
  %22 = phi i64 [ 0, %0 ], [ %36, %35 ]
  %23 = trunc i64 %22 to i32
  br label %25

24:                                               ; preds = %35
  call void @llvm.lifetime.end.p0(i64 1000000, ptr nonnull %7) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %6) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %5) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %4) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %3) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %2) #7
  call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %1) #7
  ret void

25:                                               ; preds = %25, %21
  %26 = phi i64 [ 0, %21 ], [ %30, %25 ]
  %27 = trunc i64 %26 to i32
  %28 = call i32 @ray(ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef nonnull %3, ptr noundef nonnull %4, ptr noundef nonnull %5, ptr noundef nonnull %6, i32 noundef %23, i32 noundef %27)
  %29 = getelementptr [500 x [500 x i32]], ptr %7, i64 0, i64 %22, i64 %26
  store i32 %28, ptr %29, align 4, !tbaa !5
  %30 = add nuw nsw i64 %26, 1
  %31 = icmp eq i64 %30, 500
  br i1 %31, label %32, label %25, !llvm.loop !11

32:                                               ; preds = %38, %25
  %33 = phi i64 [ %39, %38 ], [ 0, %25 ]
  %34 = trunc i64 %33 to i32
  br label %41

35:                                               ; preds = %38
  tail call void (...) @simFlush() #7
  %36 = add nuw nsw i64 %22, 1
  %37 = icmp eq i64 %36, 500
  br i1 %37, label %24, label %21, !llvm.loop !12

38:                                               ; preds = %41
  %39 = add nuw nsw i64 %33, 1
  %40 = icmp eq i64 %39, 500
  br i1 %40, label %35, label %32, !llvm.loop !13

41:                                               ; preds = %41, %32
  %42 = phi i64 [ 0, %32 ], [ %46, %41 ]
  %43 = getelementptr [500 x [500 x i32]], ptr %7, i64 0, i64 %33, i64 %42
  %44 = load i32, ptr %43, align 4, !tbaa !5
  %45 = trunc i64 %42 to i32
  tail call void @simPutPixel(i32 noundef %34, i32 noundef %45, i32 noundef %44) #7
  %46 = add nuw nsw i64 %42, 1
  %47 = icmp eq i64 %46, 500
  br i1 %47, label %38, label %41, !llvm.loop !14
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #2

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

declare void @simFlush(...) local_unnamed_addr #3

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #3

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define i32 @f32_add(i32 noundef %0, i32 noundef %1) local_unnamed_addr #4 {
  %3 = and i32 %0, 2139095040
  %4 = icmp ne i32 %3, 2139095040
  %5 = and i32 %0, 8388607
  %6 = icmp eq i32 %5, 0
  %7 = or i1 %4, %6
  br i1 %7, label %8, label %122

8:                                                ; preds = %2
  %9 = and i32 %1, 2139095040
  %10 = icmp ne i32 %9, 2139095040
  %11 = and i32 %1, 8388607
  %12 = icmp eq i32 %11, 0
  %13 = or i1 %10, %12
  br i1 %13, label %14, label %122

14:                                               ; preds = %8
  %15 = and i32 %0, 2147483647
  %16 = icmp eq i32 %15, 2139095040
  %17 = and i32 %1, 2147483647
  br i1 %16, label %18, label %24

18:                                               ; preds = %14
  %19 = icmp eq i32 %17, 2139095040
  br i1 %19, label %20, label %122

20:                                               ; preds = %18
  %21 = xor i32 %1, %0
  %22 = icmp sgt i32 %21, -1
  %23 = select i1 %22, i32 %0, i32 -1
  br label %122

24:                                               ; preds = %14
  switch i32 %17, label %25 [
    i32 0, label %122
    i32 2139095040, label %121
  ]

25:                                               ; preds = %24
  %26 = icmp eq i32 %15, 0
  br i1 %26, label %122, label %27

27:                                               ; preds = %25
  %28 = tail call signext i8 @f32_less(i32 noundef %15, i32 noundef %17), !range !15
  %29 = icmp eq i8 %28, 0
  %30 = select i1 %29, i32 %1, i32 %0
  %31 = select i1 %29, i32 %0, i32 %1
  %32 = and i32 %31, 8388607
  %33 = zext nneg i32 %32 to i64
  %34 = and i32 %31, 2139095040
  %35 = icmp ne i32 %34, 0
  %36 = icmp eq i32 %32, 0
  %37 = or i1 %35, %36
  %38 = and i32 %31, 2147483647
  %39 = icmp eq i32 %38, 0
  %40 = or disjoint i64 %33, 8388608
  %41 = select i1 %39, i64 %33, i64 %40
  %42 = select i1 %37, i64 %41, i64 %33
  %43 = and i32 %30, 8388607
  %44 = zext nneg i32 %43 to i64
  %45 = and i32 %30, 2139095040
  %46 = icmp ne i32 %45, 0
  %47 = icmp eq i32 %43, 0
  %48 = or i1 %46, %47
  %49 = and i32 %30, 2147483647
  %50 = icmp eq i32 %49, 0
  %51 = or disjoint i64 %44, 8388608
  %52 = select i1 %50, i64 %44, i64 %51
  %53 = select i1 %48, i64 %52, i64 %44
  %54 = icmp eq i32 %34, 0
  %55 = icmp ne i32 %32, 0
  %56 = and i1 %54, %55
  %57 = or i1 %39, %56
  %58 = lshr i32 %31, 23
  %59 = and i32 %58, 255
  %60 = add nsw i32 %59, -127
  %61 = select i1 %57, i32 -126, i32 %60
  %62 = icmp eq i32 %45, 0
  %63 = icmp ne i32 %43, 0
  %64 = and i1 %62, %63
  %65 = or i1 %50, %64
  %66 = lshr i32 %30, 23
  %67 = and i32 %66, 255
  %68 = add nsw i32 %67, -127
  %69 = select i1 %65, i32 -126, i32 %68
  %70 = lshr i32 %31, 31
  %71 = trunc i32 %70 to i8
  %72 = lshr i32 %30, 31
  %73 = icmp eq i32 %70, %72
  %74 = sub nsw i32 %61, %69
  br i1 %73, label %75, label %100

75:                                               ; preds = %27
  %76 = tail call noundef i32 @llvm.umin.i32(i32 %74, i32 24)
  %77 = zext nneg i32 %76 to i64
  %78 = sub nsw i32 %74, %76
  %79 = tail call noundef i32 @llvm.umin.i32(i32 %78, i32 24)
  %80 = zext nneg i32 %79 to i64
  %81 = shl nuw nsw i64 %42, %77
  %82 = sub nsw i32 %61, %76
  %83 = lshr i64 %53, %80
  %84 = add nuw nsw i64 %83, %81
  %85 = add nsw i64 %80, -1
  %86 = lshr i64 %53, %85
  %87 = trunc i64 %86 to i8
  %88 = and i8 %87, 1
  %89 = shl nsw i32 -1, %79
  %90 = xor i32 %89, -1
  %91 = zext nneg i32 %90 to i64
  %92 = and i64 %53, %91
  %93 = zext nneg i8 %88 to i32
  %94 = trunc i64 %85 to i32
  %95 = shl nuw nsw i32 %93, %94
  %96 = zext nneg i32 %95 to i64
  %97 = icmp ugt i64 %92, %96
  %98 = zext i1 %97 to i32
  %99 = tail call fastcc i32 @build_float(i8 noundef signext %71, i32 noundef %82, i64 noundef %84, i8 noundef signext %88, i32 noundef %98)
  br label %122

100:                                              ; preds = %27
  %101 = icmp ugt i32 %74, 24
  br i1 %101, label %122, label %102

102:                                              ; preds = %100
  %103 = zext nneg i32 %74 to i64
  %104 = shl nuw nsw i64 %42, %103
  %105 = sub nsw i64 %104, %53
  %106 = icmp ult i64 %105, 16777216
  %107 = icmp sgt i32 %69, -126
  %108 = select i1 %106, i1 %107, i1 false
  br i1 %108, label %109, label %117

109:                                              ; preds = %109, %102
  %110 = phi i64 [ %112, %109 ], [ %105, %102 ]
  %111 = phi i32 [ %113, %109 ], [ %68, %102 ]
  %112 = shl nuw nsw i64 %110, 1
  %113 = add nsw i32 %111, -1
  %114 = icmp ult i64 %110, 8388608
  %115 = icmp sgt i32 %111, -125
  %116 = select i1 %114, i1 %115, i1 false
  br i1 %116, label %109, label %117, !llvm.loop !16

117:                                              ; preds = %109, %102
  %118 = phi i32 [ %69, %102 ], [ %113, %109 ]
  %119 = phi i64 [ %105, %102 ], [ %112, %109 ]
  %120 = tail call fastcc i32 @build_float(i8 noundef signext %71, i32 noundef %118, i64 noundef %119, i8 noundef signext 0, i32 noundef 0)
  br label %122

121:                                              ; preds = %24
  br label %122

122:                                              ; preds = %121, %117, %100, %75, %25, %24, %20, %18, %8, %2
  %123 = phi i32 [ %23, %20 ], [ -1, %8 ], [ -1, %2 ], [ %0, %24 ], [ %1, %25 ], [ %99, %75 ], [ %120, %117 ], [ %31, %100 ], [ %0, %18 ], [ %1, %121 ]
  ret i32 %123
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_less(i32 noundef %0, i32 noundef %1) local_unnamed_addr #5 {
  %3 = and i32 %0, 2139095040
  %4 = icmp ne i32 %3, 2139095040
  %5 = and i32 %0, 8388607
  %6 = icmp eq i32 %5, 0
  %7 = or i1 %4, %6
  br i1 %7, label %8, label %41

8:                                                ; preds = %2
  %9 = and i32 %1, 2139095040
  %10 = icmp ne i32 %9, 2139095040
  %11 = and i32 %1, 8388607
  %12 = icmp eq i32 %11, 0
  %13 = or i1 %10, %12
  br i1 %13, label %14, label %41

14:                                               ; preds = %8
  %15 = and i32 %0, 2147483647
  %16 = icmp eq i32 %15, 2139095040
  %17 = and i32 %1, 2147483647
  %18 = icmp eq i32 %17, 2139095040
  %19 = and i1 %16, %18
  br i1 %19, label %20, label %23

20:                                               ; preds = %14
  %21 = xor i32 %1, %0
  %22 = icmp sgt i32 %21, -1
  br i1 %22, label %41, label %29

23:                                               ; preds = %14
  %24 = or i32 %1, %0
  %25 = and i32 %24, 2147483647
  %26 = icmp eq i32 %25, 0
  %27 = icmp eq i32 %0, %1
  %28 = or i1 %27, %26
  br i1 %28, label %41, label %29

29:                                               ; preds = %23, %20
  %30 = lshr i32 %0, 31
  %31 = lshr i32 %1, 31
  %32 = icmp eq i32 %30, %31
  br i1 %32, label %36, label %33

33:                                               ; preds = %29
  %34 = icmp ugt i32 %30, %31
  %35 = zext i1 %34 to i8
  br label %41

36:                                               ; preds = %29
  %37 = icmp ult i32 %0, %1
  %38 = zext i1 %37 to i32
  %39 = xor i32 %30, %38
  %40 = trunc i32 %39 to i8
  br label %41

41:                                               ; preds = %36, %33, %23, %20, %8, %2
  %42 = phi i8 [ 0, %23 ], [ 0, %8 ], [ 0, %2 ], [ %35, %33 ], [ %40, %36 ], [ 0, %20 ]
  ret i8 %42
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umin.i32(i32, i32) #6

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define internal fastcc i32 @build_float(i8 noundef signext %0, i32 noundef %1, i64 noundef %2, i8 noundef signext %3, i32 noundef %4) unnamed_addr #4 {
  %6 = icmp ugt i64 %2, 16777215
  %7 = icmp slt i32 %1, -126
  %8 = or i1 %6, %7
  br i1 %8, label %9, label %22

9:                                                ; preds = %9, %5
  %10 = phi i32 [ %16, %9 ], [ %4, %5 ]
  %11 = phi i64 [ %17, %9 ], [ %2, %5 ]
  %12 = phi i32 [ %18, %9 ], [ %1, %5 ]
  %13 = trunc i64 %11 to i8
  %14 = and i8 %13, 1
  %15 = zext nneg i8 %14 to i32
  %16 = add i32 %10, %15
  %17 = lshr i64 %11, 1
  %18 = add i32 %12, 1
  %19 = icmp ugt i64 %11, 33554431
  %20 = icmp slt i32 %18, -126
  %21 = select i1 %19, i1 true, i1 %20
  br i1 %21, label %9, label %22, !llvm.loop !17

22:                                               ; preds = %9, %5
  %23 = phi i32 [ %1, %5 ], [ %18, %9 ]
  %24 = phi i64 [ %2, %5 ], [ %17, %9 ]
  %25 = phi i8 [ %3, %5 ], [ %14, %9 ]
  %26 = phi i32 [ %4, %5 ], [ %16, %9 ]
  %27 = icmp eq i8 %25, 0
  br i1 %27, label %35, label %28

28:                                               ; preds = %22
  %29 = icmp sgt i32 %26, 1
  %30 = and i64 %24, 1
  %31 = icmp ne i64 %30, 0
  %32 = or i1 %31, %29
  %33 = zext i1 %32 to i64
  %34 = add nuw nsw i64 %24, %33
  br label %35

35:                                               ; preds = %28, %22
  %36 = phi i64 [ %24, %22 ], [ %34, %28 ]
  %37 = icmp ugt i64 %36, 16777215
  %38 = zext i1 %37 to i32
  %39 = add i32 %23, %38
  %40 = icmp sgt i32 %39, 127
  br i1 %40, label %41, label %44

41:                                               ; preds = %35
  %42 = zext nneg i8 %0 to i32
  %43 = shl i32 %42, 31
  br label %59

44:                                               ; preds = %35
  %45 = select i1 %37, i64 8388608, i64 %36
  %46 = icmp ugt i64 %45, 8388607
  %47 = trunc i64 %45 to i32
  br i1 %46, label %48, label %56

48:                                               ; preds = %44
  %49 = and i32 %47, 8388607
  %50 = shl i32 %39, 23
  %51 = add i32 %50, 1065353216
  %52 = and i32 %51, 2139095040
  %53 = or disjoint i32 %49, %52
  %54 = zext nneg i8 %0 to i32
  %55 = shl i32 %54, 31
  br label %59

56:                                               ; preds = %44
  %57 = zext nneg i8 %0 to i32
  %58 = shl i32 %57, 31
  br label %59

59:                                               ; preds = %56, %48, %41
  %60 = phi i32 [ %47, %56 ], [ %55, %48 ], [ 2139095040, %41 ]
  %61 = phi i32 [ %58, %56 ], [ %53, %48 ], [ %43, %41 ]
  %62 = or disjoint i32 %61, %60
  ret i32 %62
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_nan(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2139095040
  %3 = icmp eq i32 %2, 2139095040
  %4 = and i32 %0, 8388607
  %5 = icmp ne i32 %4, 0
  %6 = and i1 %3, %5
  %7 = zext i1 %6 to i8
  ret i8 %7
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_inf(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2147483647
  %3 = icmp eq i32 %2, 2139095040
  %4 = zext i1 %3 to i8
  ret i8 %4
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_zero(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2147483647
  %3 = icmp eq i32 %2, 0
  %4 = zext i1 %3 to i8
  ret i8 %4
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef i32 @f32_negate(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2139095040
  %3 = icmp ne i32 %2, 2139095040
  %4 = and i32 %0, 8388607
  %5 = icmp eq i32 %4, 0
  %6 = or i1 %3, %5
  %7 = xor i32 %0, -2147483648
  %8 = select i1 %6, i32 %7, i32 %0
  ret i32 %8
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define i32 @f32_sub(i32 noundef %0, i32 noundef %1) local_unnamed_addr #4 {
  %3 = and i32 %1, 2139095040
  %4 = icmp ne i32 %3, 2139095040
  %5 = and i32 %1, 8388607
  %6 = icmp eq i32 %5, 0
  %7 = or i1 %4, %6
  %8 = xor i32 %1, -2147483648
  %9 = select i1 %7, i32 %8, i32 %1
  %10 = tail call i32 @f32_add(i32 noundef %0, i32 noundef %9)
  ret i32 %10
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define i32 @f32_mul(i32 noundef %0, i32 noundef %1) local_unnamed_addr #4 {
  %3 = and i32 %0, 2139095040
  %4 = icmp eq i32 %3, 2139095040
  %5 = and i32 %0, 8388607
  %6 = icmp ne i32 %5, 0
  %7 = and i1 %4, %6
  br i1 %7, label %67, label %8

8:                                                ; preds = %2
  %9 = and i32 %1, 2139095040
  %10 = icmp eq i32 %9, 2139095040
  %11 = and i32 %1, 8388607
  %12 = icmp ne i32 %11, 0
  %13 = and i1 %10, %12
  br i1 %13, label %67, label %14

14:                                               ; preds = %8
  %15 = and i32 %0, 2147483647
  %16 = icmp eq i32 %15, 2139095040
  %17 = and i32 %1, 2147483647
  %18 = icmp eq i32 %17, 2139095040
  %19 = or i1 %16, %18
  br i1 %19, label %20, label %30

20:                                               ; preds = %14
  %21 = icmp eq i32 %15, 0
  %22 = icmp eq i32 %17, 0
  %23 = or i1 %21, %22
  br i1 %23, label %67, label %24

24:                                               ; preds = %20
  %25 = or i1 %16, %18
  br i1 %25, label %26, label %30

26:                                               ; preds = %24
  %27 = xor i32 %1, %0
  %28 = and i32 %27, -2147483648
  %29 = or disjoint i32 %28, 2139095040
  br label %67

30:                                               ; preds = %24, %14
  %31 = icmp eq i32 %15, 0
  %32 = icmp eq i32 %17, 0
  %33 = or i1 %31, %32
  %34 = xor i32 %1, %0
  br i1 %33, label %35, label %37

35:                                               ; preds = %30
  %36 = and i32 %34, -2147483648
  br label %67

37:                                               ; preds = %30
  %38 = lshr i32 %34, 31
  %39 = trunc i32 %38 to i8
  %40 = zext nneg i32 %5 to i64
  %41 = icmp ne i32 %3, 0
  %42 = icmp eq i32 %5, 0
  %43 = or i1 %41, %42
  %44 = or disjoint i64 %40, 8388608
  %45 = select i1 %43, i64 %44, i64 %40
  %46 = zext nneg i32 %11 to i64
  %47 = icmp ne i32 %9, 0
  %48 = icmp eq i32 %11, 0
  %49 = or i1 %47, %48
  %50 = or disjoint i64 %46, 8388608
  %51 = select i1 %49, i64 %50, i64 %46
  %52 = mul nuw nsw i64 %45, %51
  %53 = icmp eq i32 %3, 0
  %54 = and i1 %53, %6
  %55 = lshr i32 %0, 23
  %56 = and i32 %55, 255
  %57 = add nsw i32 %56, -127
  %58 = select i1 %54, i32 -126, i32 %57
  %59 = icmp eq i32 %9, 0
  %60 = and i1 %59, %12
  %61 = lshr i32 %1, 23
  %62 = and i32 %61, 255
  %63 = add nsw i32 %62, -150
  %64 = select i1 %60, i32 -149, i32 %63
  %65 = add nsw i32 %64, %58
  %66 = tail call fastcc i32 @build_float(i8 noundef signext %39, i32 noundef %65, i64 noundef %52, i8 noundef signext 0, i32 noundef 0)
  br label %67

67:                                               ; preds = %37, %35, %26, %20, %8, %2
  %68 = phi i32 [ %29, %26 ], [ %36, %35 ], [ %66, %37 ], [ -1, %8 ], [ -1, %2 ], [ -1, %20 ]
  ret i32 %68
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define i32 @f32_div(i32 noundef %0, i32 noundef %1) local_unnamed_addr #4 {
  %3 = and i32 %0, 2139095040
  %4 = icmp eq i32 %3, 2139095040
  %5 = and i32 %0, 8388607
  %6 = icmp ne i32 %5, 0
  %7 = and i1 %4, %6
  br i1 %7, label %85, label %8

8:                                                ; preds = %2
  %9 = and i32 %1, 2139095040
  %10 = icmp eq i32 %9, 2139095040
  %11 = and i32 %1, 8388607
  %12 = icmp ne i32 %11, 0
  %13 = and i1 %10, %12
  br i1 %13, label %85, label %14

14:                                               ; preds = %8
  %15 = and i32 %0, 2147483647
  %16 = icmp eq i32 %15, 2139095040
  %17 = and i32 %1, 2147483647
  %18 = icmp eq i32 %17, 2139095040
  %19 = and i1 %16, %18
  br i1 %19, label %85, label %20

20:                                               ; preds = %14
  %21 = icmp eq i32 %15, 0
  %22 = or i32 %0, %1
  %23 = and i32 %22, 2147483647
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %85, label %25

25:                                               ; preds = %20
  %26 = icmp eq i32 %17, 0
  %27 = or i1 %16, %26
  br i1 %27, label %28, label %32

28:                                               ; preds = %25
  %29 = xor i32 %1, %0
  %30 = and i32 %29, -2147483648
  %31 = or disjoint i32 %30, 2139095040
  br label %85

32:                                               ; preds = %25
  %33 = or i1 %21, %18
  %34 = xor i32 %1, %0
  br i1 %33, label %35, label %37

35:                                               ; preds = %32
  %36 = and i32 %34, -2147483648
  br label %85

37:                                               ; preds = %32
  %38 = lshr i32 %34, 31
  %39 = zext nneg i32 %5 to i64
  %40 = icmp ne i32 %3, 0
  %41 = icmp eq i32 %5, 0
  %42 = or i1 %40, %41
  %43 = or disjoint i64 %39, 8388608
  %44 = select i1 %42, i64 %43, i64 %39
  %45 = zext nneg i32 %11 to i64
  %46 = icmp ne i32 %9, 0
  %47 = icmp eq i32 %11, 0
  %48 = or i1 %46, %47
  %49 = or disjoint i64 %45, 8388608
  %50 = select i1 %48, i64 %49, i64 %45
  %51 = icmp eq i32 %3, 0
  %52 = and i1 %51, %6
  %53 = lshr i32 %0, 23
  %54 = and i32 %53, 255
  %55 = add nsw i32 %54, -104
  %56 = icmp eq i32 %9, 0
  %57 = and i1 %56, %12
  %58 = lshr i32 %1, 23
  %59 = and i32 %58, 255
  %60 = sub nsw i32 127, %59
  %61 = select i1 %57, i32 126, i32 %60
  %62 = select i1 %52, i32 -103, i32 %55
  %63 = add nsw i32 %62, %61
  br label %64

64:                                               ; preds = %64, %37
  %65 = phi i64 [ %44, %37 ], [ %73, %64 ]
  %66 = phi i64 [ 0, %37 ], [ %72, %64 ]
  %67 = phi i32 [ %63, %37 ], [ %69, %64 ]
  %68 = shl nuw nsw i64 %65, 24
  %69 = add i32 %67, -24
  %70 = shl nuw nsw i64 %66, 24
  %71 = udiv i64 %68, %50
  %72 = add nuw nsw i64 %71, %70
  %73 = urem i64 %68, %50
  %74 = icmp ult i64 %72, 16777216
  br i1 %74, label %64, label %75, !llvm.loop !18

75:                                               ; preds = %64
  %76 = trunc i32 %38 to i8
  %77 = shl nuw nsw i64 %73, 1
  %78 = icmp uge i64 %77, %50
  %79 = zext i1 %78 to i8
  %80 = icmp ugt i64 %77, %50
  %81 = icmp ne i64 %73, 0
  %82 = zext i1 %81 to i32
  %83 = select i1 %80, i32 2, i32 %82
  %84 = tail call fastcc i32 @build_float(i8 noundef signext %76, i32 noundef %69, i64 noundef %72, i8 noundef signext %79, i32 noundef %83)
  br label %85

85:                                               ; preds = %75, %35, %28, %20, %14, %8, %2
  %86 = phi i32 [ %31, %28 ], [ %36, %35 ], [ %84, %75 ], [ -1, %8 ], [ -1, %2 ], [ -1, %14 ], [ -1, %20 ]
  ret i32 %86
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_qnan(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2139095040
  %3 = icmp ne i32 %2, 2139095040
  %4 = and i32 %0, 8388607
  %5 = icmp eq i32 %4, 0
  %6 = or i1 %3, %5
  %7 = lshr i32 %0, 31
  %8 = trunc i32 %7 to i8
  %9 = select i1 %6, i8 0, i8 %8
  ret i8 %9
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_snan(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2139095040
  %3 = icmp ne i32 %2, 2139095040
  %4 = and i32 %0, 8388607
  %5 = icmp eq i32 %4, 0
  %6 = or i1 %3, %5
  %7 = lshr i32 %0, 31
  %8 = trunc i32 %7 to i8
  %9 = xor i8 %8, 1
  %10 = select i1 %6, i8 0, i8 %9
  ret i8 %10
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define noundef signext i8 @f32_is_subnormal(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2139095040
  %3 = icmp eq i32 %2, 0
  %4 = and i32 %0, 8388607
  %5 = icmp ne i32 %4, 0
  %6 = and i1 %3, %5
  %7 = zext i1 %6 to i8
  ret i8 %7
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define signext i8 @f32_equal(i32 noundef %0, i32 noundef %1) local_unnamed_addr #5 {
  %3 = and i32 %0, 2139095040
  %4 = icmp ne i32 %3, 2139095040
  %5 = and i32 %0, 8388607
  %6 = icmp eq i32 %5, 0
  %7 = or i1 %4, %6
  br i1 %7, label %8, label %29

8:                                                ; preds = %2
  %9 = and i32 %1, 2139095040
  %10 = icmp ne i32 %9, 2139095040
  %11 = and i32 %1, 8388607
  %12 = icmp eq i32 %11, 0
  %13 = or i1 %10, %12
  br i1 %13, label %14, label %29

14:                                               ; preds = %8
  %15 = and i32 %0, 2147483647
  %16 = icmp eq i32 %15, 2139095040
  %17 = and i32 %1, 2147483647
  %18 = icmp eq i32 %17, 2139095040
  %19 = and i1 %16, %18
  br i1 %19, label %20, label %23

20:                                               ; preds = %14
  %21 = xor i32 %1, %0
  %22 = icmp sgt i32 %21, -1
  br label %29

23:                                               ; preds = %14
  %24 = or i32 %0, %1
  %25 = and i32 %24, 2147483647
  %26 = icmp eq i32 %25, 0
  %27 = icmp eq i32 %0, %1
  %28 = or i1 %26, %27
  br label %29

29:                                               ; preds = %23, %20, %8, %2
  %30 = phi i1 [ %22, %20 ], [ false, %8 ], [ false, %2 ], [ %28, %23 ]
  %31 = zext i1 %30 to i8
  ret i8 %31
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define i64 @f32_to_ll(i32 noundef %0) local_unnamed_addr #5 {
  %2 = and i32 %0, 2147483647
  %3 = icmp eq i32 %2, 2139095040
  br i1 %3, label %44, label %4

4:                                                ; preds = %1
  %5 = and i32 %0, 2139095040
  %6 = icmp eq i32 %5, 2139095040
  %7 = and i32 %0, 8388607
  %8 = icmp ne i32 %7, 0
  %9 = and i1 %6, %8
  br i1 %9, label %44, label %10

10:                                               ; preds = %4
  %11 = icmp eq i32 %2, 0
  br i1 %11, label %44, label %12

12:                                               ; preds = %10
  %13 = zext nneg i32 %7 to i64
  %14 = icmp ne i32 %5, 0
  %15 = icmp eq i32 %7, 0
  %16 = or i1 %14, %15
  %17 = or disjoint i64 %13, 8388608
  %18 = select i1 %16, i64 %17, i64 %13
  %19 = icmp eq i32 %5, 0
  %20 = and i1 %19, %8
  %21 = lshr i32 %0, 23
  %22 = and i32 %21, 255
  %23 = add nsw i32 %22, -127
  %24 = select i1 %20, i32 -126, i32 %23
  %25 = add nsw i32 %24, -23
  %26 = icmp slt i32 %24, -40
  br i1 %26, label %44, label %27

27:                                               ; preds = %12
  %28 = icmp slt i32 %24, 24
  br i1 %28, label %29, label %36

29:                                               ; preds = %27
  %30 = sub nsw i32 23, %24
  %31 = zext nneg i32 %30 to i64
  %32 = lshr i64 %18, %31
  %33 = sub nsw i64 0, %32
  %34 = icmp slt i32 %0, 0
  %35 = select i1 %34, i64 %33, i64 %32
  br label %44

36:                                               ; preds = %27
  %37 = icmp ult i32 %24, 63
  br i1 %37, label %38, label %44

38:                                               ; preds = %36
  %39 = zext nneg i32 %25 to i64
  %40 = shl nuw nsw i64 %18, %39
  %41 = sub nsw i64 0, %40
  %42 = icmp slt i32 %0, 0
  %43 = select i1 %42, i64 %41, i64 %40
  br label %44

44:                                               ; preds = %38, %36, %29, %12, %10, %4, %1
  %45 = phi i64 [ -9223372036854775808, %4 ], [ -9223372036854775808, %1 ], [ 0, %10 ], [ %35, %29 ], [ %43, %38 ], [ 0, %12 ], [ -9223372036854775808, %36 ]
  ret i64 %45
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define i32 @f32_from_ll(i64 noundef %0) local_unnamed_addr #4 {
  switch i64 %0, label %3 [
    i64 -9223372036854775808, label %2
    i64 0, label %60
  ]

2:                                                ; preds = %1
  br label %60

3:                                                ; preds = %1
  %4 = tail call i64 @llvm.abs.i64(i64 %0, i1 true)
  %5 = icmp ult i64 %4, 16777216
  %6 = shl nuw nsw i64 %4, 24
  %7 = select i1 %5, i64 %6, i64 %4
  %8 = select i1 %5, i32 -1, i32 23
  %9 = lshr i64 %0, 63
  %10 = trunc i64 %9 to i32
  %11 = icmp ugt i64 %7, 16777215
  br i1 %11, label %12, label %34

12:                                               ; preds = %12, %3
  %13 = phi i32 [ %19, %12 ], [ 0, %3 ]
  %14 = phi i64 [ %20, %12 ], [ %7, %3 ]
  %15 = phi i32 [ %21, %12 ], [ %8, %3 ]
  %16 = trunc i64 %14 to i8
  %17 = and i8 %16, 1
  %18 = zext nneg i8 %17 to i32
  %19 = add i32 %13, %18
  %20 = lshr i64 %14, 1
  %21 = add i32 %15, 1
  %22 = icmp ugt i64 %14, 33554431
  %23 = icmp slt i32 %21, -126
  %24 = select i1 %22, i1 true, i1 %23
  br i1 %24, label %12, label %25, !llvm.loop !17

25:                                               ; preds = %12
  %26 = icmp eq i8 %17, 0
  br i1 %26, label %34, label %27

27:                                               ; preds = %25
  %28 = icmp sgt i32 %19, 1
  %29 = and i64 %14, 2
  %30 = icmp ne i64 %29, 0
  %31 = or i1 %30, %28
  %32 = zext i1 %31 to i64
  %33 = add nuw nsw i64 %20, %32
  br label %34

34:                                               ; preds = %27, %25, %3
  %35 = phi i32 [ %21, %25 ], [ %21, %27 ], [ %8, %3 ]
  %36 = phi i64 [ %20, %25 ], [ %33, %27 ], [ %7, %3 ]
  %37 = icmp ugt i64 %36, 16777215
  %38 = zext i1 %37 to i32
  %39 = add i32 %35, %38
  %40 = icmp sgt i32 %39, 127
  br i1 %40, label %41, label %43

41:                                               ; preds = %34
  %42 = shl nuw i32 %10, 31
  br label %56

43:                                               ; preds = %34
  %44 = select i1 %37, i64 8388608, i64 %36
  %45 = icmp ugt i64 %44, 8388607
  %46 = trunc i64 %44 to i32
  br i1 %45, label %47, label %54

47:                                               ; preds = %43
  %48 = and i32 %46, 8388607
  %49 = shl i32 %39, 23
  %50 = add i32 %49, 1065353216
  %51 = and i32 %50, 2139095040
  %52 = or disjoint i32 %51, %48
  %53 = shl nuw i32 %10, 31
  br label %56

54:                                               ; preds = %43
  %55 = shl nuw i32 %10, 31
  br label %56

56:                                               ; preds = %54, %47, %41
  %57 = phi i32 [ %46, %54 ], [ %53, %47 ], [ 2139095040, %41 ]
  %58 = phi i32 [ %55, %54 ], [ %52, %47 ], [ %42, %41 ]
  %59 = or disjoint i32 %58, %57
  br label %60

60:                                               ; preds = %56, %2, %1
  %61 = phi i32 [ -2147483647, %2 ], [ %59, %56 ], [ 0, %1 ]
  ret i32 %61
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.abs.i64(i64, i1 immarg) #6

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_sin(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #7
  br label %4

3:                                                ; preds = %4
  ret i32 %9

4:                                                ; preds = %4, %1
  %5 = phi i32 [ 0, %1 ], [ %16, %4 ]
  %6 = phi i32 [ 1065353216, %1 ], [ %13, %4 ]
  %7 = phi i32 [ %0, %1 ], [ %15, %4 ]
  %8 = phi i32 [ 0, %1 ], [ %9, %4 ]
  %9 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %7) #7
  %10 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #7
  %11 = tail call i32 @f32_add(i32 noundef %6, i32 noundef 1065353216) #7
  %12 = tail call i32 @f32_div(i32 noundef %10, i32 noundef %11) #7
  %13 = tail call i32 @f32_add(i32 noundef %11, i32 noundef 1065353216) #7
  %14 = tail call i32 @f32_div(i32 noundef %12, i32 noundef %13) #7
  %15 = tail call i32 @f32_negate(i32 noundef %14) #7
  %16 = add nuw nsw i32 %5, 1
  %17 = icmp eq i32 %16, 100
  br i1 %17, label %3, label %4, !llvm.loop !19
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_cos(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #7
  br label %4

3:                                                ; preds = %4
  ret i32 %9

4:                                                ; preds = %4, %1
  %5 = phi i32 [ 0, %1 ], [ %16, %4 ]
  %6 = phi i32 [ 0, %1 ], [ %13, %4 ]
  %7 = phi i32 [ 1065353216, %1 ], [ %15, %4 ]
  %8 = phi i32 [ 0, %1 ], [ %9, %4 ]
  %9 = tail call i32 @f32_add(i32 noundef %8, i32 noundef %7) #7
  %10 = tail call i32 @f32_mul(i32 noundef %7, i32 noundef %2) #7
  %11 = tail call i32 @f32_add(i32 noundef %6, i32 noundef 1065353216) #7
  %12 = tail call i32 @f32_div(i32 noundef %10, i32 noundef %11) #7
  %13 = tail call i32 @f32_add(i32 noundef %11, i32 noundef 1065353216) #7
  %14 = tail call i32 @f32_div(i32 noundef %12, i32 noundef %13) #7
  %15 = tail call i32 @f32_negate(i32 noundef %14) #7
  %16 = add nuw nsw i32 %5, 1
  %17 = icmp eq i32 %16, 100
  br i1 %17, label %3, label %4, !llvm.loop !20
}

; Function Attrs: nounwind sspstrong uwtable
define i32 @f32_tan(i32 noundef %0) local_unnamed_addr #0 {
  %2 = tail call i32 @f32_sin(i32 noundef %0)
  %3 = tail call i32 @f32_cos(i32 noundef %0)
  %4 = tail call i32 @f32_div(i32 noundef %2, i32 noundef %3) #7
  ret i32 %4
}

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #1 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #3 = { "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #4 = { nofree norecurse nosync nounwind sspstrong memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #5 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="4" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "zero-call-used-regs"="used-gpr" }
attributes #6 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #7 = { nounwind }

!llvm.ident = !{!0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}

!0 = !{!"clang version 18.1.8"}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
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
!15 = !{i8 0, i8 2}
!16 = distinct !{!16, !10}
!17 = distinct !{!17, !10}
!18 = distinct !{!18, !10}
!19 = distinct !{!19, !10}
!20 = distinct !{!20, !10}
