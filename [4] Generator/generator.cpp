#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "app/sim.h"
#include <array>
#include <string>

using namespace llvm;

constexpr std::string RUN = "run";
constexpr std::string PRINT = "print";

int main(int argc, char* argv[]) {
  if (argc != 2 || argv[1] != PRINT && argv[1] != RUN) {
    outs() << "either \"print\" or \"run\" expected\n";
    return 1;
  }
  
  LLVMContext context;
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);
  Function *funcsqr = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "sqr", module);
  Function *funcdot_prod = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "dot_prod", module);
  Function *funcdist2 = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "dist2", module);
  Function *funcqrsqrt = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "qrsqrt", module);
  Function *funccombine = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "combine", module);
  Function *funcshadow = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "shadow", module);
  Function *funcreflection = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "reflection", module);
  Function *funcray_impl = Function::Create(FunctionType::get(Type::getInt32Ty(context), { PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "ray_impl", module);
  Function *funcray = Function::Create(FunctionType::get(Type::getInt32Ty(context), { PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "ray", module);
  Function *funcinit = Function::Create(FunctionType::get(Type::getVoidTy(context), { PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "init", module);
  Function *funcapp = Function::Create(FunctionType::get(Type::getVoidTy(context), {  }, false), Function::ExternalLinkage, "app", module);
  Function *funcllvm_lifetime_start_p0 = Function::Create(FunctionType::get(Type::getVoidTy(context), { Type::getInt64Ty(context), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "llvm.lifetime.start.p0", module);
  Function *funcllvm_memset_p0_i64 = Function::Create(FunctionType::get(Type::getVoidTy(context), { PointerType::get(context, 0), Type::getInt8Ty(context), Type::getInt64Ty(context), Type::getInt1Ty(context) }, false), Function::ExternalLinkage, "llvm.memset.p0.i64", module);
  Function *funcllvm_lifetime_end_p0 = Function::Create(FunctionType::get(Type::getVoidTy(context), { Type::getInt64Ty(context), PointerType::get(context, 0) }, false), Function::ExternalLinkage, "llvm.lifetime.end.p0", module);
  Function *funcsimFlush = Function::Create(FunctionType::get(Type::getVoidTy(context), {  }, false), Function::ExternalLinkage, "simFlush", module);
  Function *funcsimPutPixel = Function::Create(FunctionType::get(Type::getVoidTy(context), { Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "simPutPixel", module);
  Function *funcf32_add = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_add", module);
  Function *funcf32_less = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_less", module);
  Function *funcllvm_umin_i32 = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "llvm.umin.i32", module);
  Function *funcbuild_float = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt8Ty(context), Type::getInt32Ty(context), Type::getInt64Ty(context), Type::getInt8Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "build_float", module);
  Function *funcf32_is_nan = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_nan", module);
  Function *funcf32_is_inf = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_inf", module);
  Function *funcf32_is_zero = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_zero", module);
  Function *funcf32_negate = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_negate", module);
  Function *funcf32_sub = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_sub", module);
  Function *funcf32_mul = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_mul", module);
  Function *funcf32_div = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_div", module);
  Function *funcf32_is_qnan = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_qnan", module);
  Function *funcf32_is_snan = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_snan", module);
  Function *funcf32_is_subnormal = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_is_subnormal", module);
  Function *funcf32_equal = Function::Create(FunctionType::get(Type::getInt8Ty(context), { Type::getInt32Ty(context), Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_equal", module);
  Function *funcf32_to_ll = Function::Create(FunctionType::get(Type::getInt64Ty(context), { Type::getInt32Ty(context) }, false), Function::ExternalLinkage, "f32_to_ll", module);
  Function *funcf32_from_ll = Function::Create(FunctionType::get(Type::getInt32Ty(context), { Type::getInt64Ty(context) }, false), Function::ExternalLinkage, "f32_from_ll", module);
  Function *funcllvm_abs_i64 = Function::Create(FunctionType::get(Type::getInt64Ty(context), { Type::getInt64Ty(context), Type::getInt1Ty(context) }, false), Function::ExternalLinkage, "llvm.abs.i64", module);
  {
    Function *func = funcsqr;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #9
    Value *val2 = builder.CreateCall(funcf32_mul, {val0, val0});
    //   ret i32 %2
    builder.CreateRet(val2);
  }
  {
    Function *func = funcdot_prod;
    BasicBlock *val6 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    Value *val4 = func->getArg(4);
    Value *val5 = func->getArg(5);
    builder.SetInsertPoint(val6);
    //   %7 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %3) #9
    Value *val7 = builder.CreateCall(funcf32_mul, {val0, val3});
    //   %8 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %4) #9
    Value *val8 = builder.CreateCall(funcf32_mul, {val1, val4});
    //   %9 = tail call i32 @f32_add(i32 noundef %7, i32 noundef %8) #9
    Value *val9 = builder.CreateCall(funcf32_add, {val7, val8});
    //   %10 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %5) #9
    Value *val10 = builder.CreateCall(funcf32_mul, {val2, val5});
    //   %11 = tail call i32 @f32_add(i32 noundef %9, i32 noundef %10) #9
    Value *val11 = builder.CreateCall(funcf32_add, {val9, val10});
    //   ret i32 %11
    builder.CreateRet(val11);
  }
  {
    Function *func = funcdist2;
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    builder.SetInsertPoint(val3);
    //   %4 = tail call i32 @f32_mul(i32 noundef %0, i32 noundef %0) #9
    Value *val4 = builder.CreateCall(funcf32_mul, {val0, val0});
    //   %5 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %1) #9
    Value *val5 = builder.CreateCall(funcf32_mul, {val1, val1});
    //   %6 = tail call i32 @f32_add(i32 noundef %4, i32 noundef %5) #9
    Value *val6 = builder.CreateCall(funcf32_add, {val4, val5});
    //   %7 = tail call i32 @f32_mul(i32 noundef %2, i32 noundef %2) #9
    Value *val7 = builder.CreateCall(funcf32_mul, {val2, val2});
    //   %8 = tail call i32 @f32_add(i32 noundef %6, i32 noundef %7) #9
    Value *val8 = builder.CreateCall(funcf32_add, {val6, val7});
    //   ret i32 %8
    builder.CreateRet(val8);
  }
  {
    Function *func = funcqrsqrt;
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(valbuild_float_exit);
    //   %1 = tail call i32 @f32_div(i32 noundef %0, i32 noundef 1073741824) #9
    Value *val1 = builder.CreateCall(funcf32_div, {val0, builder.getInt32(1073741824)});
    //   %2 = lshr i32 %0, 1
    Value *val2 = builder.CreateLShr(val0, builder.getInt32(1), "", false);
    //   %3 = sub nsw i32 1597463007, %2
    Value *val3 = builder.CreateSub(builder.getInt32(1597463007), val2, "", false, true);
    //   %4 = tail call i32 @f32_mul(i32 noundef %3, i32 noundef %3) #9
    Value *val4 = builder.CreateCall(funcf32_mul, {val3, val3});
    //   %5 = tail call i32 @f32_mul(i32 noundef %1, i32 noundef %4) #9
    Value *val5 = builder.CreateCall(funcf32_mul, {val1, val4});
    //   %6 = and i32 %5, 2139095040
    Value *val6 = builder.CreateAnd(val5, builder.getInt32(2139095040), "");
    //   %7 = icmp ne i32 %6, 2139095040
    Value *val7 = builder.CreateICmpNE(val6, builder.getInt32(2139095040), "");
    //   %8 = and i32 %5, 8388607
    Value *val8 = builder.CreateAnd(val5, builder.getInt32(8388607), "");
    //   %9 = icmp eq i32 %8, 0
    Value *val9 = builder.CreateICmpEQ(val8, builder.getInt32(0), "");
    //   %10 = or i1 %7, %9
    Value *val10 = builder.CreateOr(val7, val9, "");
    //   %11 = xor i32 %5, -2147483648
    Value *val11 = builder.CreateXor(val5, builder.getInt32(-2147483648), "");
    //   %12 = select i1 %10, i32 %11, i32 %5
    Value *val12 = builder.CreateSelect(val10, val11, val5);
    //   %13 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %12)
    Value *val13 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val12});
    //   %14 = tail call i32 @f32_mul(i32 noundef %3, i32 noundef %13) #9
    Value *val14 = builder.CreateCall(funcf32_mul, {val3, val13});
    //   ret i32 %14
    builder.CreateRet(val14);
  }
  {
    Function *func = funccombine;
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val13 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i = BasicBlock::Create(context, "", func);
    BasicBlock *val28 = BasicBlock::Create(context, "", func);
    BasicBlock *val30 = BasicBlock::Create(context, "", func);
    BasicBlock *val37 = BasicBlock::Create(context, "", func);
    BasicBlock *val43 = BasicBlock::Create(context, "", func);
    BasicBlock *val47 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val56 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i1 = BasicBlock::Create(context, "", func);
    BasicBlock *val71 = BasicBlock::Create(context, "", func);
    BasicBlock *val73 = BasicBlock::Create(context, "", func);
    BasicBlock *val80 = BasicBlock::Create(context, "", func);
    BasicBlock *val86 = BasicBlock::Create(context, "", func);
    BasicBlock *val90 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit2 = BasicBlock::Create(context, "", func);
    BasicBlock *val101 = BasicBlock::Create(context, "", func);
    BasicBlock *val107 = BasicBlock::Create(context, "", func);
    BasicBlock *val109 = BasicBlock::Create(context, "", func);
    BasicBlock *val124 = BasicBlock::Create(context, "", func);
    BasicBlock *val126 = BasicBlock::Create(context, "", func);
    BasicBlock *val133 = BasicBlock::Create(context, "", func);
    BasicBlock *val135 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val143 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i3 = BasicBlock::Create(context, "", func);
    BasicBlock *val158 = BasicBlock::Create(context, "", func);
    BasicBlock *val160 = BasicBlock::Create(context, "", func);
    BasicBlock *val167 = BasicBlock::Create(context, "", func);
    BasicBlock *val173 = BasicBlock::Create(context, "", func);
    BasicBlock *val177 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit4 = BasicBlock::Create(context, "", func);
    BasicBlock *val186 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i5 = BasicBlock::Create(context, "", func);
    BasicBlock *val201 = BasicBlock::Create(context, "", func);
    BasicBlock *val203 = BasicBlock::Create(context, "", func);
    BasicBlock *val210 = BasicBlock::Create(context, "", func);
    BasicBlock *val216 = BasicBlock::Create(context, "", func);
    BasicBlock *val220 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit6 = BasicBlock::Create(context, "", func);
    BasicBlock *val231 = BasicBlock::Create(context, "", func);
    BasicBlock *val237 = BasicBlock::Create(context, "", func);
    BasicBlock *val239 = BasicBlock::Create(context, "", func);
    BasicBlock *val254 = BasicBlock::Create(context, "", func);
    BasicBlock *val256 = BasicBlock::Create(context, "", func);
    BasicBlock *val263 = BasicBlock::Create(context, "", func);
    BasicBlock *val265 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit7 = BasicBlock::Create(context, "", func);
    BasicBlock *val273 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i8_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i8 = BasicBlock::Create(context, "", func);
    BasicBlock *val288 = BasicBlock::Create(context, "", func);
    BasicBlock *val290 = BasicBlock::Create(context, "", func);
    BasicBlock *val297 = BasicBlock::Create(context, "", func);
    BasicBlock *val304 = BasicBlock::Create(context, "", func);
    BasicBlock *val308 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit9 = BasicBlock::Create(context, "", func);
    BasicBlock *val317 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i10_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i10 = BasicBlock::Create(context, "", func);
    BasicBlock *val332 = BasicBlock::Create(context, "", func);
    BasicBlock *val334 = BasicBlock::Create(context, "", func);
    BasicBlock *val341 = BasicBlock::Create(context, "", func);
    BasicBlock *val348 = BasicBlock::Create(context, "", func);
    BasicBlock *val352 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit11 = BasicBlock::Create(context, "", func);
    BasicBlock *val363 = BasicBlock::Create(context, "", func);
    BasicBlock *val369 = BasicBlock::Create(context, "", func);
    BasicBlock *val371 = BasicBlock::Create(context, "", func);
    BasicBlock *val386 = BasicBlock::Create(context, "", func);
    BasicBlock *val388 = BasicBlock::Create(context, "", func);
    BasicBlock *val395 = BasicBlock::Create(context, "", func);
    BasicBlock *val397 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit12 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    builder.SetInsertPoint(val3);
    //   %4 = and i32 %2, 2139095040
    Value *val4 = builder.CreateAnd(val2, builder.getInt32(2139095040), "");
    //   %5 = icmp ne i32 %4, 2139095040
    Value *val5 = builder.CreateICmpNE(val4, builder.getInt32(2139095040), "");
    //   %6 = and i32 %2, 8388607
    Value *val6 = builder.CreateAnd(val2, builder.getInt32(8388607), "");
    //   %7 = icmp eq i32 %6, 0
    Value *val7 = builder.CreateICmpEQ(val6, builder.getInt32(0), "");
    //   %8 = or i1 %5, %7
    Value *val8 = builder.CreateOr(val5, val7, "");
    //   %9 = xor i32 %2, -2147483648
    Value *val9 = builder.CreateXor(val2, builder.getInt32(-2147483648), "");
    //   %10 = select i1 %8, i32 %9, i32 %2
    Value *val10 = builder.CreateSelect(val8, val9, val2);
    //   %11 = tail call i32 @f32_add(i32 noundef 1065353216, i32 noundef %10)
    Value *val11 = builder.CreateCall(funcf32_add, {builder.getInt32(1065353216), val10});
    //   %12 = and i32 %0, 16711680
    Value *val12 = builder.CreateAnd(val0, builder.getInt32(16711680), "");
    //   %cond = icmp eq i32 %12, 0
    Value *valcond = builder.CreateICmpEQ(val12, builder.getInt32(0), "");
    //   br i1 %cond, label %f32_from_ll.exit, label %13
    builder.CreateCondBr(valcond, valf32_from_ll_exit, val13);
    builder.SetInsertPoint(val13);
    //   %14 = zext nneg i32 %12 to i64
    Value *val14 = builder.CreateZExt(val12, Type::getInt64Ty(context));
    //   %15 = shl nuw nsw i64 %14, 24
    Value *val15 = builder.CreateShl(val14, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i
    builder.CreateBr(val_preheader_i);
    builder.SetInsertPoint(val_preheader_i);
    //   %16 = phi i32 [ %22, %.preheader.i ], [ 0, %13 ]
    PHINode *val16 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %17 = phi i64 [ %23, %.preheader.i ], [ %15, %13 ]
    PHINode *val17 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %18 = phi i32 [ %24, %.preheader.i ], [ -1, %13 ]
    PHINode *val18 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %19 = trunc i64 %17 to i8
    Value *val19 = builder.CreateTrunc(val17, Type::getInt8Ty(context));
    //   %20 = and i8 %19, 1
    Value *val20 = builder.CreateAnd(val19, builder.getInt8(1), "");
    //   %21 = zext nneg i8 %20 to i32
    Value *val21 = builder.CreateZExt(val20, Type::getInt32Ty(context));
    //   %22 = add i32 %16, %21
    Value *val22 = builder.CreateAdd(val16, val21, "", false, false);
    //   %23 = lshr i64 %17, 1
    Value *val23 = builder.CreateLShr(val17, builder.getInt64(1ll), "", false);
    //   %24 = add i32 %18, 1
    Value *val24 = builder.CreateAdd(val18, builder.getInt32(1), "", false, false);
    //   %25 = icmp ugt i64 %17, 33554431
    Value *val25 = builder.CreateICmpUGT(val17, builder.getInt64(33554431ll), "");
    //   %26 = icmp slt i32 %24, -126
    Value *val26 = builder.CreateICmpSLT(val24, builder.getInt32(-126), "");
    //   %27 = select i1 %25, i1 true, i1 %26
    Value *val27 = builder.CreateSelect(val25, builder.getInt1(true), val26);
    //   br i1 %27, label %.preheader.i, label %28, !llvm.loop !4
    builder.CreateCondBr(val27, val_preheader_i, val28);
    builder.SetInsertPoint(val28);
    //   %29 = icmp eq i8 %20, 0
    Value *val29 = builder.CreateICmpEQ(val20, builder.getInt8(0), "");
    //   br i1 %29, label %37, label %30
    builder.CreateCondBr(val29, val37, val30);
    builder.SetInsertPoint(val30);
    //   %31 = icmp sgt i32 %22, 1
    Value *val31 = builder.CreateICmpSGT(val22, builder.getInt32(1), "");
    //   %32 = and i64 %17, 2
    Value *val32 = builder.CreateAnd(val17, builder.getInt64(2ll), "");
    //   %33 = icmp ne i64 %32, 0
    Value *val33 = builder.CreateICmpNE(val32, builder.getInt64(0ll), "");
    //   %34 = or i1 %33, %31
    Value *val34 = builder.CreateOr(val33, val31, "");
    //   %35 = zext i1 %34 to i64
    Value *val35 = builder.CreateZExt(val34, Type::getInt64Ty(context));
    //   %36 = add nuw nsw i64 %23, %35
    Value *val36 = builder.CreateAdd(val23, val35, "", true, true);
    //   br label %37
    builder.CreateBr(val37);
    builder.SetInsertPoint(val37);
    //   %38 = phi i64 [ %23, %28 ], [ %36, %30 ]
    PHINode *val38 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %39 = icmp ugt i64 %38, 16777215
    Value *val39 = builder.CreateICmpUGT(val38, builder.getInt64(16777215ll), "");
    //   %40 = zext i1 %39 to i32
    Value *val40 = builder.CreateZExt(val39, Type::getInt32Ty(context));
    //   %41 = add i32 %24, %40
    Value *val41 = builder.CreateAdd(val24, val40, "", false, false);
    //   %42 = icmp sgt i32 %41, 127
    Value *val42 = builder.CreateICmpSGT(val41, builder.getInt32(127), "");
    //   br i1 %42, label %f32_from_ll.exit, label %43
    builder.CreateCondBr(val42, valf32_from_ll_exit, val43);
    builder.SetInsertPoint(val43);
    //   %44 = select i1 %39, i64 8388608, i64 %38
    Value *val44 = builder.CreateSelect(val39, builder.getInt64(8388608ll), val38);
    //   %45 = icmp ugt i64 %44, 8388607
    Value *val45 = builder.CreateICmpUGT(val44, builder.getInt64(8388607ll), "");
    //   %46 = trunc i64 %44 to i32
    Value *val46 = builder.CreateTrunc(val44, Type::getInt32Ty(context));
    //   br i1 %45, label %47, label %f32_from_ll.exit
    builder.CreateCondBr(val45, val47, valf32_from_ll_exit);
    builder.SetInsertPoint(val47);
    //   %48 = and i32 %46, 8388607
    Value *val48 = builder.CreateAnd(val46, builder.getInt32(8388607), "");
    //   %49 = shl i32 %41, 23
    Value *val49 = builder.CreateShl(val41, builder.getInt32(23), "", false, false);
    //   %50 = add i32 %49, 1065353216
    Value *val50 = builder.CreateAdd(val49, builder.getInt32(1065353216), "", false, false);
    //   %51 = and i32 %50, 2139095040
    Value *val51 = builder.CreateAnd(val50, builder.getInt32(2139095040), "");
    //   %52 = or disjoint i32 %51, %48
    Value *val52 = builder.CreateOr(val51, val48, "");
    //   br label %f32_from_ll.exit
    builder.CreateBr(valf32_from_ll_exit);
    builder.SetInsertPoint(valf32_from_ll_exit);
    //   %53 = phi i32 [ 0, %3 ], [ %52, %47 ], [ 2139095040, %37 ], [ %46, %43 ]
    PHINode *val53 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %54 = tail call i32 @f32_mul(i32 noundef %53, i32 noundef %2) #9
    Value *val54 = builder.CreateCall(funcf32_mul, {val53, val2});
    //   %55 = and i32 %1, 16711680
    Value *val55 = builder.CreateAnd(val1, builder.getInt32(16711680), "");
    //   %cond13 = icmp eq i32 %55, 0
    Value *valcond13 = builder.CreateICmpEQ(val55, builder.getInt32(0), "");
    //   br i1 %cond13, label %f32_from_ll.exit2, label %56
    builder.CreateCondBr(valcond13, valf32_from_ll_exit2, val56);
    builder.SetInsertPoint(val56);
    //   %57 = zext nneg i32 %55 to i64
    Value *val57 = builder.CreateZExt(val55, Type::getInt64Ty(context));
    //   %58 = shl nuw nsw i64 %57, 24
    Value *val58 = builder.CreateShl(val57, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i1
    builder.CreateBr(val_preheader_i1);
    builder.SetInsertPoint(val_preheader_i1);
    //   %59 = phi i32 [ %65, %.preheader.i1 ], [ 0, %56 ]
    PHINode *val59 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %60 = phi i64 [ %66, %.preheader.i1 ], [ %58, %56 ]
    PHINode *val60 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %61 = phi i32 [ %67, %.preheader.i1 ], [ -1, %56 ]
    PHINode *val61 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %62 = trunc i64 %60 to i8
    Value *val62 = builder.CreateTrunc(val60, Type::getInt8Ty(context));
    //   %63 = and i8 %62, 1
    Value *val63 = builder.CreateAnd(val62, builder.getInt8(1), "");
    //   %64 = zext nneg i8 %63 to i32
    Value *val64 = builder.CreateZExt(val63, Type::getInt32Ty(context));
    //   %65 = add i32 %59, %64
    Value *val65 = builder.CreateAdd(val59, val64, "", false, false);
    //   %66 = lshr i64 %60, 1
    Value *val66 = builder.CreateLShr(val60, builder.getInt64(1ll), "", false);
    //   %67 = add i32 %61, 1
    Value *val67 = builder.CreateAdd(val61, builder.getInt32(1), "", false, false);
    //   %68 = icmp ugt i64 %60, 33554431
    Value *val68 = builder.CreateICmpUGT(val60, builder.getInt64(33554431ll), "");
    //   %69 = icmp slt i32 %67, -126
    Value *val69 = builder.CreateICmpSLT(val67, builder.getInt32(-126), "");
    //   %70 = select i1 %68, i1 true, i1 %69
    Value *val70 = builder.CreateSelect(val68, builder.getInt1(true), val69);
    //   br i1 %70, label %.preheader.i1, label %71, !llvm.loop !4
    builder.CreateCondBr(val70, val_preheader_i1, val71);
    builder.SetInsertPoint(val71);
    //   %72 = icmp eq i8 %63, 0
    Value *val72 = builder.CreateICmpEQ(val63, builder.getInt8(0), "");
    //   br i1 %72, label %80, label %73
    builder.CreateCondBr(val72, val80, val73);
    builder.SetInsertPoint(val73);
    //   %74 = icmp sgt i32 %65, 1
    Value *val74 = builder.CreateICmpSGT(val65, builder.getInt32(1), "");
    //   %75 = and i64 %60, 2
    Value *val75 = builder.CreateAnd(val60, builder.getInt64(2ll), "");
    //   %76 = icmp ne i64 %75, 0
    Value *val76 = builder.CreateICmpNE(val75, builder.getInt64(0ll), "");
    //   %77 = or i1 %76, %74
    Value *val77 = builder.CreateOr(val76, val74, "");
    //   %78 = zext i1 %77 to i64
    Value *val78 = builder.CreateZExt(val77, Type::getInt64Ty(context));
    //   %79 = add nuw nsw i64 %66, %78
    Value *val79 = builder.CreateAdd(val66, val78, "", true, true);
    //   br label %80
    builder.CreateBr(val80);
    builder.SetInsertPoint(val80);
    //   %81 = phi i64 [ %66, %71 ], [ %79, %73 ]
    PHINode *val81 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %82 = icmp ugt i64 %81, 16777215
    Value *val82 = builder.CreateICmpUGT(val81, builder.getInt64(16777215ll), "");
    //   %83 = zext i1 %82 to i32
    Value *val83 = builder.CreateZExt(val82, Type::getInt32Ty(context));
    //   %84 = add i32 %67, %83
    Value *val84 = builder.CreateAdd(val67, val83, "", false, false);
    //   %85 = icmp sgt i32 %84, 127
    Value *val85 = builder.CreateICmpSGT(val84, builder.getInt32(127), "");
    //   br i1 %85, label %f32_from_ll.exit2, label %86
    builder.CreateCondBr(val85, valf32_from_ll_exit2, val86);
    builder.SetInsertPoint(val86);
    //   %87 = select i1 %82, i64 8388608, i64 %81
    Value *val87 = builder.CreateSelect(val82, builder.getInt64(8388608ll), val81);
    //   %88 = icmp ugt i64 %87, 8388607
    Value *val88 = builder.CreateICmpUGT(val87, builder.getInt64(8388607ll), "");
    //   %89 = trunc i64 %87 to i32
    Value *val89 = builder.CreateTrunc(val87, Type::getInt32Ty(context));
    //   br i1 %88, label %90, label %f32_from_ll.exit2
    builder.CreateCondBr(val88, val90, valf32_from_ll_exit2);
    builder.SetInsertPoint(val90);
    //   %91 = and i32 %89, 8388607
    Value *val91 = builder.CreateAnd(val89, builder.getInt32(8388607), "");
    //   %92 = shl i32 %84, 23
    Value *val92 = builder.CreateShl(val84, builder.getInt32(23), "", false, false);
    //   %93 = add i32 %92, 1065353216
    Value *val93 = builder.CreateAdd(val92, builder.getInt32(1065353216), "", false, false);
    //   %94 = and i32 %93, 2139095040
    Value *val94 = builder.CreateAnd(val93, builder.getInt32(2139095040), "");
    //   %95 = or disjoint i32 %94, %91
    Value *val95 = builder.CreateOr(val94, val91, "");
    //   br label %f32_from_ll.exit2
    builder.CreateBr(valf32_from_ll_exit2);
    builder.SetInsertPoint(valf32_from_ll_exit2);
    //   %96 = phi i32 [ 0, %f32_from_ll.exit ], [ %95, %90 ], [ 2139095040, %80 ], [ %89, %86 ]
    PHINode *val96 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %97 = tail call i32 @f32_mul(i32 noundef %96, i32 noundef %11) #9
    Value *val97 = builder.CreateCall(funcf32_mul, {val96, val11});
    //   %98 = tail call i32 @f32_add(i32 noundef %54, i32 noundef %97) #9
    Value *val98 = builder.CreateCall(funcf32_add, {val54, val97});
    //   %99 = and i32 %98, 2147483647
    Value *val99 = builder.CreateAnd(val98, builder.getInt32(2147483647), "");
    //   %100 = icmp eq i32 %99, 2139095040
    Value *val100 = builder.CreateICmpEQ(val99, builder.getInt32(2139095040), "");
    //   br i1 %100, label %f32_to_ll.exit, label %101
    builder.CreateCondBr(val100, valf32_to_ll_exit, val101);
    builder.SetInsertPoint(val101);
    //   %102 = and i32 %98, 2139095040
    Value *val102 = builder.CreateAnd(val98, builder.getInt32(2139095040), "");
    //   %103 = icmp eq i32 %102, 2139095040
    Value *val103 = builder.CreateICmpEQ(val102, builder.getInt32(2139095040), "");
    //   %104 = and i32 %98, 8388607
    Value *val104 = builder.CreateAnd(val98, builder.getInt32(8388607), "");
    //   %105 = icmp ne i32 %104, 0
    Value *val105 = builder.CreateICmpNE(val104, builder.getInt32(0), "");
    //   %106 = and i1 %103, %105
    Value *val106 = builder.CreateAnd(val103, val105, "");
    //   br i1 %106, label %f32_to_ll.exit, label %107
    builder.CreateCondBr(val106, valf32_to_ll_exit, val107);
    builder.SetInsertPoint(val107);
    //   %108 = icmp eq i32 %99, 0
    Value *val108 = builder.CreateICmpEQ(val99, builder.getInt32(0), "");
    //   br i1 %108, label %f32_to_ll.exit, label %109
    builder.CreateCondBr(val108, valf32_to_ll_exit, val109);
    builder.SetInsertPoint(val109);
    //   %110 = zext nneg i32 %104 to i64
    Value *val110 = builder.CreateZExt(val104, Type::getInt64Ty(context));
    //   %111 = icmp ne i32 %102, 0
    Value *val111 = builder.CreateICmpNE(val102, builder.getInt32(0), "");
    //   %112 = icmp eq i32 %104, 0
    Value *val112 = builder.CreateICmpEQ(val104, builder.getInt32(0), "");
    //   %113 = or i1 %111, %112
    Value *val113 = builder.CreateOr(val111, val112, "");
    //   %114 = or disjoint i64 %110, 8388608
    Value *val114 = builder.CreateOr(val110, builder.getInt64(8388608ll), "");
    //   %115 = select i1 %113, i64 %114, i64 %110
    Value *val115 = builder.CreateSelect(val113, val114, val110);
    //   %116 = icmp eq i32 %102, 0
    Value *val116 = builder.CreateICmpEQ(val102, builder.getInt32(0), "");
    //   %117 = and i1 %116, %105
    Value *val117 = builder.CreateAnd(val116, val105, "");
    //   %118 = lshr i32 %98, 23
    Value *val118 = builder.CreateLShr(val98, builder.getInt32(23), "", false);
    //   %119 = and i32 %118, 255
    Value *val119 = builder.CreateAnd(val118, builder.getInt32(255), "");
    //   %120 = add nsw i32 %119, -127
    Value *val120 = builder.CreateAdd(val119, builder.getInt32(-127), "", false, true);
    //   %121 = select i1 %117, i32 -126, i32 %120
    Value *val121 = builder.CreateSelect(val117, builder.getInt32(-126), val120);
    //   %122 = add nsw i32 %121, -23
    Value *val122 = builder.CreateAdd(val121, builder.getInt32(-23), "", false, true);
    //   %123 = icmp slt i32 %121, -40
    Value *val123 = builder.CreateICmpSLT(val121, builder.getInt32(-40), "");
    //   br i1 %123, label %f32_to_ll.exit, label %124
    builder.CreateCondBr(val123, valf32_to_ll_exit, val124);
    builder.SetInsertPoint(val124);
    //   %125 = icmp slt i32 %121, 24
    Value *val125 = builder.CreateICmpSLT(val121, builder.getInt32(24), "");
    //   br i1 %125, label %126, label %133
    builder.CreateCondBr(val125, val126, val133);
    builder.SetInsertPoint(val126);
    //   %127 = sub nsw i32 23, %121
    Value *val127 = builder.CreateSub(builder.getInt32(23), val121, "", false, true);
    //   %128 = zext nneg i32 %127 to i64
    Value *val128 = builder.CreateZExt(val127, Type::getInt64Ty(context));
    //   %129 = lshr i64 %115, %128
    Value *val129 = builder.CreateLShr(val115, val128, "", false);
    //   %130 = sub nsw i64 0, %129
    Value *val130 = builder.CreateSub(builder.getInt64(0ll), val129, "", false, true);
    //   %131 = icmp slt i32 %98, 0
    Value *val131 = builder.CreateICmpSLT(val98, builder.getInt32(0), "");
    //   %132 = select i1 %131, i64 %130, i64 %129
    Value *val132 = builder.CreateSelect(val131, val130, val129);
    //   br label %f32_to_ll.exit
    builder.CreateBr(valf32_to_ll_exit);
    builder.SetInsertPoint(val133);
    //   %134 = icmp ult i32 %121, 63
    Value *val134 = builder.CreateICmpULT(val121, builder.getInt32(63), "");
    //   br i1 %134, label %135, label %f32_to_ll.exit
    builder.CreateCondBr(val134, val135, valf32_to_ll_exit);
    builder.SetInsertPoint(val135);
    //   %136 = zext nneg i32 %122 to i64
    Value *val136 = builder.CreateZExt(val122, Type::getInt64Ty(context));
    //   %137 = shl nuw nsw i64 %115, %136
    Value *val137 = builder.CreateShl(val115, val136, "", true, true);
    //   %138 = sub nsw i64 0, %137
    Value *val138 = builder.CreateSub(builder.getInt64(0ll), val137, "", false, true);
    //   %139 = icmp slt i32 %98, 0
    Value *val139 = builder.CreateICmpSLT(val98, builder.getInt32(0), "");
    //   %140 = select i1 %139, i64 %138, i64 %137
    Value *val140 = builder.CreateSelect(val139, val138, val137);
    //   br label %f32_to_ll.exit
    builder.CreateBr(valf32_to_ll_exit);
    builder.SetInsertPoint(valf32_to_ll_exit);
    //   %141 = phi i64 [ -9223372036854775808, %101 ], [ -9223372036854775808, %f32_from_ll.exit2 ], [ 0, %107 ], [ %132, %126 ], [ %140, %135 ], [ 0, %109 ], [ -9223372036854775808, %133 ]
    PHINode *val141 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %142 = and i32 %0, 65280
    Value *val142 = builder.CreateAnd(val0, builder.getInt32(65280), "");
    //   %cond14 = icmp eq i32 %142, 0
    Value *valcond14 = builder.CreateICmpEQ(val142, builder.getInt32(0), "");
    //   br i1 %cond14, label %f32_from_ll.exit4, label %143
    builder.CreateCondBr(valcond14, valf32_from_ll_exit4, val143);
    builder.SetInsertPoint(val143);
    //   %144 = zext nneg i32 %142 to i64
    Value *val144 = builder.CreateZExt(val142, Type::getInt64Ty(context));
    //   %145 = shl nuw nsw i64 %144, 24
    Value *val145 = builder.CreateShl(val144, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i3
    builder.CreateBr(val_preheader_i3);
    builder.SetInsertPoint(val_preheader_i3);
    //   %146 = phi i32 [ %152, %.preheader.i3 ], [ 0, %143 ]
    PHINode *val146 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %147 = phi i64 [ %153, %.preheader.i3 ], [ %145, %143 ]
    PHINode *val147 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %148 = phi i32 [ %154, %.preheader.i3 ], [ -1, %143 ]
    PHINode *val148 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %149 = trunc i64 %147 to i8
    Value *val149 = builder.CreateTrunc(val147, Type::getInt8Ty(context));
    //   %150 = and i8 %149, 1
    Value *val150 = builder.CreateAnd(val149, builder.getInt8(1), "");
    //   %151 = zext nneg i8 %150 to i32
    Value *val151 = builder.CreateZExt(val150, Type::getInt32Ty(context));
    //   %152 = add i32 %146, %151
    Value *val152 = builder.CreateAdd(val146, val151, "", false, false);
    //   %153 = lshr i64 %147, 1
    Value *val153 = builder.CreateLShr(val147, builder.getInt64(1ll), "", false);
    //   %154 = add i32 %148, 1
    Value *val154 = builder.CreateAdd(val148, builder.getInt32(1), "", false, false);
    //   %155 = icmp ugt i64 %147, 33554431
    Value *val155 = builder.CreateICmpUGT(val147, builder.getInt64(33554431ll), "");
    //   %156 = icmp slt i32 %154, -126
    Value *val156 = builder.CreateICmpSLT(val154, builder.getInt32(-126), "");
    //   %157 = select i1 %155, i1 true, i1 %156
    Value *val157 = builder.CreateSelect(val155, builder.getInt1(true), val156);
    //   br i1 %157, label %.preheader.i3, label %158, !llvm.loop !4
    builder.CreateCondBr(val157, val_preheader_i3, val158);
    builder.SetInsertPoint(val158);
    //   %159 = icmp eq i8 %150, 0
    Value *val159 = builder.CreateICmpEQ(val150, builder.getInt8(0), "");
    //   br i1 %159, label %167, label %160
    builder.CreateCondBr(val159, val167, val160);
    builder.SetInsertPoint(val160);
    //   %161 = icmp sgt i32 %152, 1
    Value *val161 = builder.CreateICmpSGT(val152, builder.getInt32(1), "");
    //   %162 = and i64 %147, 2
    Value *val162 = builder.CreateAnd(val147, builder.getInt64(2ll), "");
    //   %163 = icmp ne i64 %162, 0
    Value *val163 = builder.CreateICmpNE(val162, builder.getInt64(0ll), "");
    //   %164 = or i1 %163, %161
    Value *val164 = builder.CreateOr(val163, val161, "");
    //   %165 = zext i1 %164 to i64
    Value *val165 = builder.CreateZExt(val164, Type::getInt64Ty(context));
    //   %166 = add nuw nsw i64 %153, %165
    Value *val166 = builder.CreateAdd(val153, val165, "", true, true);
    //   br label %167
    builder.CreateBr(val167);
    builder.SetInsertPoint(val167);
    //   %168 = phi i64 [ %153, %158 ], [ %166, %160 ]
    PHINode *val168 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %169 = icmp ugt i64 %168, 16777215
    Value *val169 = builder.CreateICmpUGT(val168, builder.getInt64(16777215ll), "");
    //   %170 = zext i1 %169 to i32
    Value *val170 = builder.CreateZExt(val169, Type::getInt32Ty(context));
    //   %171 = add i32 %154, %170
    Value *val171 = builder.CreateAdd(val154, val170, "", false, false);
    //   %172 = icmp sgt i32 %171, 127
    Value *val172 = builder.CreateICmpSGT(val171, builder.getInt32(127), "");
    //   br i1 %172, label %f32_from_ll.exit4, label %173
    builder.CreateCondBr(val172, valf32_from_ll_exit4, val173);
    builder.SetInsertPoint(val173);
    //   %174 = select i1 %169, i64 8388608, i64 %168
    Value *val174 = builder.CreateSelect(val169, builder.getInt64(8388608ll), val168);
    //   %175 = icmp ugt i64 %174, 8388607
    Value *val175 = builder.CreateICmpUGT(val174, builder.getInt64(8388607ll), "");
    //   %176 = trunc i64 %174 to i32
    Value *val176 = builder.CreateTrunc(val174, Type::getInt32Ty(context));
    //   br i1 %175, label %177, label %f32_from_ll.exit4
    builder.CreateCondBr(val175, val177, valf32_from_ll_exit4);
    builder.SetInsertPoint(val177);
    //   %178 = and i32 %176, 8388607
    Value *val178 = builder.CreateAnd(val176, builder.getInt32(8388607), "");
    //   %179 = shl i32 %171, 23
    Value *val179 = builder.CreateShl(val171, builder.getInt32(23), "", false, false);
    //   %180 = add i32 %179, 1065353216
    Value *val180 = builder.CreateAdd(val179, builder.getInt32(1065353216), "", false, false);
    //   %181 = and i32 %180, 2139095040
    Value *val181 = builder.CreateAnd(val180, builder.getInt32(2139095040), "");
    //   %182 = or disjoint i32 %181, %178
    Value *val182 = builder.CreateOr(val181, val178, "");
    //   br label %f32_from_ll.exit4
    builder.CreateBr(valf32_from_ll_exit4);
    builder.SetInsertPoint(valf32_from_ll_exit4);
    //   %183 = phi i32 [ 0, %f32_to_ll.exit ], [ %182, %177 ], [ 2139095040, %167 ], [ %176, %173 ]
    PHINode *val183 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %184 = tail call i32 @f32_mul(i32 noundef %183, i32 noundef %2) #9
    Value *val184 = builder.CreateCall(funcf32_mul, {val183, val2});
    //   %185 = and i32 %1, 65280
    Value *val185 = builder.CreateAnd(val1, builder.getInt32(65280), "");
    //   %cond15 = icmp eq i32 %185, 0
    Value *valcond15 = builder.CreateICmpEQ(val185, builder.getInt32(0), "");
    //   br i1 %cond15, label %f32_from_ll.exit6, label %186
    builder.CreateCondBr(valcond15, valf32_from_ll_exit6, val186);
    builder.SetInsertPoint(val186);
    //   %187 = zext nneg i32 %185 to i64
    Value *val187 = builder.CreateZExt(val185, Type::getInt64Ty(context));
    //   %188 = shl nuw nsw i64 %187, 24
    Value *val188 = builder.CreateShl(val187, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i5
    builder.CreateBr(val_preheader_i5);
    builder.SetInsertPoint(val_preheader_i5);
    //   %189 = phi i32 [ %195, %.preheader.i5 ], [ 0, %186 ]
    PHINode *val189 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %190 = phi i64 [ %196, %.preheader.i5 ], [ %188, %186 ]
    PHINode *val190 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %191 = phi i32 [ %197, %.preheader.i5 ], [ -1, %186 ]
    PHINode *val191 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %192 = trunc i64 %190 to i8
    Value *val192 = builder.CreateTrunc(val190, Type::getInt8Ty(context));
    //   %193 = and i8 %192, 1
    Value *val193 = builder.CreateAnd(val192, builder.getInt8(1), "");
    //   %194 = zext nneg i8 %193 to i32
    Value *val194 = builder.CreateZExt(val193, Type::getInt32Ty(context));
    //   %195 = add i32 %189, %194
    Value *val195 = builder.CreateAdd(val189, val194, "", false, false);
    //   %196 = lshr i64 %190, 1
    Value *val196 = builder.CreateLShr(val190, builder.getInt64(1ll), "", false);
    //   %197 = add i32 %191, 1
    Value *val197 = builder.CreateAdd(val191, builder.getInt32(1), "", false, false);
    //   %198 = icmp ugt i64 %190, 33554431
    Value *val198 = builder.CreateICmpUGT(val190, builder.getInt64(33554431ll), "");
    //   %199 = icmp slt i32 %197, -126
    Value *val199 = builder.CreateICmpSLT(val197, builder.getInt32(-126), "");
    //   %200 = select i1 %198, i1 true, i1 %199
    Value *val200 = builder.CreateSelect(val198, builder.getInt1(true), val199);
    //   br i1 %200, label %.preheader.i5, label %201, !llvm.loop !4
    builder.CreateCondBr(val200, val_preheader_i5, val201);
    builder.SetInsertPoint(val201);
    //   %202 = icmp eq i8 %193, 0
    Value *val202 = builder.CreateICmpEQ(val193, builder.getInt8(0), "");
    //   br i1 %202, label %210, label %203
    builder.CreateCondBr(val202, val210, val203);
    builder.SetInsertPoint(val203);
    //   %204 = icmp sgt i32 %195, 1
    Value *val204 = builder.CreateICmpSGT(val195, builder.getInt32(1), "");
    //   %205 = and i64 %190, 2
    Value *val205 = builder.CreateAnd(val190, builder.getInt64(2ll), "");
    //   %206 = icmp ne i64 %205, 0
    Value *val206 = builder.CreateICmpNE(val205, builder.getInt64(0ll), "");
    //   %207 = or i1 %206, %204
    Value *val207 = builder.CreateOr(val206, val204, "");
    //   %208 = zext i1 %207 to i64
    Value *val208 = builder.CreateZExt(val207, Type::getInt64Ty(context));
    //   %209 = add nuw nsw i64 %196, %208
    Value *val209 = builder.CreateAdd(val196, val208, "", true, true);
    //   br label %210
    builder.CreateBr(val210);
    builder.SetInsertPoint(val210);
    //   %211 = phi i64 [ %196, %201 ], [ %209, %203 ]
    PHINode *val211 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %212 = icmp ugt i64 %211, 16777215
    Value *val212 = builder.CreateICmpUGT(val211, builder.getInt64(16777215ll), "");
    //   %213 = zext i1 %212 to i32
    Value *val213 = builder.CreateZExt(val212, Type::getInt32Ty(context));
    //   %214 = add i32 %197, %213
    Value *val214 = builder.CreateAdd(val197, val213, "", false, false);
    //   %215 = icmp sgt i32 %214, 127
    Value *val215 = builder.CreateICmpSGT(val214, builder.getInt32(127), "");
    //   br i1 %215, label %f32_from_ll.exit6, label %216
    builder.CreateCondBr(val215, valf32_from_ll_exit6, val216);
    builder.SetInsertPoint(val216);
    //   %217 = select i1 %212, i64 8388608, i64 %211
    Value *val217 = builder.CreateSelect(val212, builder.getInt64(8388608ll), val211);
    //   %218 = icmp ugt i64 %217, 8388607
    Value *val218 = builder.CreateICmpUGT(val217, builder.getInt64(8388607ll), "");
    //   %219 = trunc i64 %217 to i32
    Value *val219 = builder.CreateTrunc(val217, Type::getInt32Ty(context));
    //   br i1 %218, label %220, label %f32_from_ll.exit6
    builder.CreateCondBr(val218, val220, valf32_from_ll_exit6);
    builder.SetInsertPoint(val220);
    //   %221 = and i32 %219, 8388607
    Value *val221 = builder.CreateAnd(val219, builder.getInt32(8388607), "");
    //   %222 = shl i32 %214, 23
    Value *val222 = builder.CreateShl(val214, builder.getInt32(23), "", false, false);
    //   %223 = add i32 %222, 1065353216
    Value *val223 = builder.CreateAdd(val222, builder.getInt32(1065353216), "", false, false);
    //   %224 = and i32 %223, 2139095040
    Value *val224 = builder.CreateAnd(val223, builder.getInt32(2139095040), "");
    //   %225 = or disjoint i32 %224, %221
    Value *val225 = builder.CreateOr(val224, val221, "");
    //   br label %f32_from_ll.exit6
    builder.CreateBr(valf32_from_ll_exit6);
    builder.SetInsertPoint(valf32_from_ll_exit6);
    //   %226 = phi i32 [ 0, %f32_from_ll.exit4 ], [ %225, %220 ], [ 2139095040, %210 ], [ %219, %216 ]
    PHINode *val226 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %227 = tail call i32 @f32_mul(i32 noundef %226, i32 noundef %11) #9
    Value *val227 = builder.CreateCall(funcf32_mul, {val226, val11});
    //   %228 = tail call i32 @f32_add(i32 noundef %184, i32 noundef %227) #9
    Value *val228 = builder.CreateCall(funcf32_add, {val184, val227});
    //   %229 = and i32 %228, 2147483647
    Value *val229 = builder.CreateAnd(val228, builder.getInt32(2147483647), "");
    //   %230 = icmp eq i32 %229, 2139095040
    Value *val230 = builder.CreateICmpEQ(val229, builder.getInt32(2139095040), "");
    //   br i1 %230, label %f32_to_ll.exit7, label %231
    builder.CreateCondBr(val230, valf32_to_ll_exit7, val231);
    builder.SetInsertPoint(val231);
    //   %232 = and i32 %228, 2139095040
    Value *val232 = builder.CreateAnd(val228, builder.getInt32(2139095040), "");
    //   %233 = icmp eq i32 %232, 2139095040
    Value *val233 = builder.CreateICmpEQ(val232, builder.getInt32(2139095040), "");
    //   %234 = and i32 %228, 8388607
    Value *val234 = builder.CreateAnd(val228, builder.getInt32(8388607), "");
    //   %235 = icmp ne i32 %234, 0
    Value *val235 = builder.CreateICmpNE(val234, builder.getInt32(0), "");
    //   %236 = and i1 %233, %235
    Value *val236 = builder.CreateAnd(val233, val235, "");
    //   br i1 %236, label %f32_to_ll.exit7, label %237
    builder.CreateCondBr(val236, valf32_to_ll_exit7, val237);
    builder.SetInsertPoint(val237);
    //   %238 = icmp eq i32 %229, 0
    Value *val238 = builder.CreateICmpEQ(val229, builder.getInt32(0), "");
    //   br i1 %238, label %f32_to_ll.exit7, label %239
    builder.CreateCondBr(val238, valf32_to_ll_exit7, val239);
    builder.SetInsertPoint(val239);
    //   %240 = zext nneg i32 %234 to i64
    Value *val240 = builder.CreateZExt(val234, Type::getInt64Ty(context));
    //   %241 = icmp ne i32 %232, 0
    Value *val241 = builder.CreateICmpNE(val232, builder.getInt32(0), "");
    //   %242 = icmp eq i32 %234, 0
    Value *val242 = builder.CreateICmpEQ(val234, builder.getInt32(0), "");
    //   %243 = or i1 %241, %242
    Value *val243 = builder.CreateOr(val241, val242, "");
    //   %244 = or disjoint i64 %240, 8388608
    Value *val244 = builder.CreateOr(val240, builder.getInt64(8388608ll), "");
    //   %245 = select i1 %243, i64 %244, i64 %240
    Value *val245 = builder.CreateSelect(val243, val244, val240);
    //   %246 = icmp eq i32 %232, 0
    Value *val246 = builder.CreateICmpEQ(val232, builder.getInt32(0), "");
    //   %247 = and i1 %246, %235
    Value *val247 = builder.CreateAnd(val246, val235, "");
    //   %248 = lshr i32 %228, 23
    Value *val248 = builder.CreateLShr(val228, builder.getInt32(23), "", false);
    //   %249 = and i32 %248, 255
    Value *val249 = builder.CreateAnd(val248, builder.getInt32(255), "");
    //   %250 = add nsw i32 %249, -127
    Value *val250 = builder.CreateAdd(val249, builder.getInt32(-127), "", false, true);
    //   %251 = select i1 %247, i32 -126, i32 %250
    Value *val251 = builder.CreateSelect(val247, builder.getInt32(-126), val250);
    //   %252 = add nsw i32 %251, -23
    Value *val252 = builder.CreateAdd(val251, builder.getInt32(-23), "", false, true);
    //   %253 = icmp slt i32 %251, -40
    Value *val253 = builder.CreateICmpSLT(val251, builder.getInt32(-40), "");
    //   br i1 %253, label %f32_to_ll.exit7, label %254
    builder.CreateCondBr(val253, valf32_to_ll_exit7, val254);
    builder.SetInsertPoint(val254);
    //   %255 = icmp slt i32 %251, 24
    Value *val255 = builder.CreateICmpSLT(val251, builder.getInt32(24), "");
    //   br i1 %255, label %256, label %263
    builder.CreateCondBr(val255, val256, val263);
    builder.SetInsertPoint(val256);
    //   %257 = sub nsw i32 23, %251
    Value *val257 = builder.CreateSub(builder.getInt32(23), val251, "", false, true);
    //   %258 = zext nneg i32 %257 to i64
    Value *val258 = builder.CreateZExt(val257, Type::getInt64Ty(context));
    //   %259 = lshr i64 %245, %258
    Value *val259 = builder.CreateLShr(val245, val258, "", false);
    //   %260 = sub nsw i64 0, %259
    Value *val260 = builder.CreateSub(builder.getInt64(0ll), val259, "", false, true);
    //   %261 = icmp slt i32 %228, 0
    Value *val261 = builder.CreateICmpSLT(val228, builder.getInt32(0), "");
    //   %262 = select i1 %261, i64 %260, i64 %259
    Value *val262 = builder.CreateSelect(val261, val260, val259);
    //   br label %f32_to_ll.exit7
    builder.CreateBr(valf32_to_ll_exit7);
    builder.SetInsertPoint(val263);
    //   %264 = icmp ult i32 %251, 63
    Value *val264 = builder.CreateICmpULT(val251, builder.getInt32(63), "");
    //   br i1 %264, label %265, label %f32_to_ll.exit7
    builder.CreateCondBr(val264, val265, valf32_to_ll_exit7);
    builder.SetInsertPoint(val265);
    //   %266 = zext nneg i32 %252 to i64
    Value *val266 = builder.CreateZExt(val252, Type::getInt64Ty(context));
    //   %267 = shl nuw nsw i64 %245, %266
    Value *val267 = builder.CreateShl(val245, val266, "", true, true);
    //   %268 = sub nsw i64 0, %267
    Value *val268 = builder.CreateSub(builder.getInt64(0ll), val267, "", false, true);
    //   %269 = icmp slt i32 %228, 0
    Value *val269 = builder.CreateICmpSLT(val228, builder.getInt32(0), "");
    //   %270 = select i1 %269, i64 %268, i64 %267
    Value *val270 = builder.CreateSelect(val269, val268, val267);
    //   br label %f32_to_ll.exit7
    builder.CreateBr(valf32_to_ll_exit7);
    builder.SetInsertPoint(valf32_to_ll_exit7);
    //   %271 = phi i64 [ -9223372036854775808, %231 ], [ -9223372036854775808, %f32_from_ll.exit6 ], [ 0, %237 ], [ %262, %256 ], [ %270, %265 ], [ 0, %239 ], [ -9223372036854775808, %263 ]
    PHINode *val271 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %272 = and i32 %0, 255
    Value *val272 = builder.CreateAnd(val0, builder.getInt32(255), "");
    //   %cond16 = icmp eq i32 %272, 0
    Value *valcond16 = builder.CreateICmpEQ(val272, builder.getInt32(0), "");
    //   br i1 %cond16, label %f32_from_ll.exit9, label %273
    builder.CreateCondBr(valcond16, valf32_from_ll_exit9, val273);
    builder.SetInsertPoint(val273);
    //   %274 = shl i32 %0, 24
    Value *val274 = builder.CreateShl(val0, builder.getInt32(24), "", false, false);
    //   %.not = icmp eq i32 %274, 0
    Value *val_not = builder.CreateICmpEQ(val274, builder.getInt32(0), "");
    //   br i1 %.not, label %297, label %.preheader.i8.preheader
    builder.CreateCondBr(val_not, val297, val_preheader_i8_preheader);
    builder.SetInsertPoint(val_preheader_i8_preheader);
    //   %275 = zext i32 %274 to i64
    Value *val275 = builder.CreateZExt(val274, Type::getInt64Ty(context));
    //   br label %.preheader.i8
    builder.CreateBr(val_preheader_i8);
    builder.SetInsertPoint(val_preheader_i8);
    //   %276 = phi i32 [ %282, %.preheader.i8 ], [ 0, %.preheader.i8.preheader ]
    PHINode *val276 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %277 = phi i64 [ %283, %.preheader.i8 ], [ %275, %.preheader.i8.preheader ]
    PHINode *val277 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %278 = phi i32 [ %284, %.preheader.i8 ], [ -1, %.preheader.i8.preheader ]
    PHINode *val278 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %279 = trunc i64 %277 to i8
    Value *val279 = builder.CreateTrunc(val277, Type::getInt8Ty(context));
    //   %280 = and i8 %279, 1
    Value *val280 = builder.CreateAnd(val279, builder.getInt8(1), "");
    //   %281 = zext nneg i8 %280 to i32
    Value *val281 = builder.CreateZExt(val280, Type::getInt32Ty(context));
    //   %282 = add i32 %276, %281
    Value *val282 = builder.CreateAdd(val276, val281, "", false, false);
    //   %283 = lshr i64 %277, 1
    Value *val283 = builder.CreateLShr(val277, builder.getInt64(1ll), "", false);
    //   %284 = add i32 %278, 1
    Value *val284 = builder.CreateAdd(val278, builder.getInt32(1), "", false, false);
    //   %285 = icmp ugt i64 %277, 33554431
    Value *val285 = builder.CreateICmpUGT(val277, builder.getInt64(33554431ll), "");
    //   %286 = icmp slt i32 %284, -126
    Value *val286 = builder.CreateICmpSLT(val284, builder.getInt32(-126), "");
    //   %287 = select i1 %285, i1 true, i1 %286
    Value *val287 = builder.CreateSelect(val285, builder.getInt1(true), val286);
    //   br i1 %287, label %.preheader.i8, label %288, !llvm.loop !4
    builder.CreateCondBr(val287, val_preheader_i8, val288);
    builder.SetInsertPoint(val288);
    //   %289 = icmp eq i8 %280, 0
    Value *val289 = builder.CreateICmpEQ(val280, builder.getInt8(0), "");
    //   br i1 %289, label %297, label %290
    builder.CreateCondBr(val289, val297, val290);
    builder.SetInsertPoint(val290);
    //   %291 = icmp sgt i32 %282, 1
    Value *val291 = builder.CreateICmpSGT(val282, builder.getInt32(1), "");
    //   %292 = and i64 %277, 2
    Value *val292 = builder.CreateAnd(val277, builder.getInt64(2ll), "");
    //   %293 = icmp ne i64 %292, 0
    Value *val293 = builder.CreateICmpNE(val292, builder.getInt64(0ll), "");
    //   %294 = or i1 %293, %291
    Value *val294 = builder.CreateOr(val293, val291, "");
    //   %295 = zext i1 %294 to i64
    Value *val295 = builder.CreateZExt(val294, Type::getInt64Ty(context));
    //   %296 = add nuw nsw i64 %283, %295
    Value *val296 = builder.CreateAdd(val283, val295, "", true, true);
    //   br label %297
    builder.CreateBr(val297);
    builder.SetInsertPoint(val297);
    //   %298 = phi i32 [ %284, %288 ], [ %284, %290 ], [ -1, %273 ]
    PHINode *val298 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %299 = phi i64 [ %283, %288 ], [ %296, %290 ], [ 0, %273 ]
    PHINode *val299 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %300 = icmp ugt i64 %299, 16777215
    Value *val300 = builder.CreateICmpUGT(val299, builder.getInt64(16777215ll), "");
    //   %301 = zext i1 %300 to i32
    Value *val301 = builder.CreateZExt(val300, Type::getInt32Ty(context));
    //   %302 = add i32 %298, %301
    Value *val302 = builder.CreateAdd(val298, val301, "", false, false);
    //   %303 = icmp sgt i32 %302, 127
    Value *val303 = builder.CreateICmpSGT(val302, builder.getInt32(127), "");
    //   br i1 %303, label %f32_from_ll.exit9, label %304
    builder.CreateCondBr(val303, valf32_from_ll_exit9, val304);
    builder.SetInsertPoint(val304);
    //   %305 = select i1 %300, i64 8388608, i64 %299
    Value *val305 = builder.CreateSelect(val300, builder.getInt64(8388608ll), val299);
    //   %306 = icmp ugt i64 %305, 8388607
    Value *val306 = builder.CreateICmpUGT(val305, builder.getInt64(8388607ll), "");
    //   %307 = trunc i64 %305 to i32
    Value *val307 = builder.CreateTrunc(val305, Type::getInt32Ty(context));
    //   br i1 %306, label %308, label %f32_from_ll.exit9
    builder.CreateCondBr(val306, val308, valf32_from_ll_exit9);
    builder.SetInsertPoint(val308);
    //   %309 = and i32 %307, 8388607
    Value *val309 = builder.CreateAnd(val307, builder.getInt32(8388607), "");
    //   %310 = shl i32 %302, 23
    Value *val310 = builder.CreateShl(val302, builder.getInt32(23), "", false, false);
    //   %311 = add i32 %310, 1065353216
    Value *val311 = builder.CreateAdd(val310, builder.getInt32(1065353216), "", false, false);
    //   %312 = and i32 %311, 2139095040
    Value *val312 = builder.CreateAnd(val311, builder.getInt32(2139095040), "");
    //   %313 = or disjoint i32 %312, %309
    Value *val313 = builder.CreateOr(val312, val309, "");
    //   br label %f32_from_ll.exit9
    builder.CreateBr(valf32_from_ll_exit9);
    builder.SetInsertPoint(valf32_from_ll_exit9);
    //   %314 = phi i32 [ 0, %f32_to_ll.exit7 ], [ %313, %308 ], [ 2139095040, %297 ], [ %307, %304 ]
    PHINode *val314 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %315 = tail call i32 @f32_mul(i32 noundef %314, i32 noundef %2) #9
    Value *val315 = builder.CreateCall(funcf32_mul, {val314, val2});
    //   %316 = and i32 %1, 255
    Value *val316 = builder.CreateAnd(val1, builder.getInt32(255), "");
    //   %cond17 = icmp eq i32 %316, 0
    Value *valcond17 = builder.CreateICmpEQ(val316, builder.getInt32(0), "");
    //   br i1 %cond17, label %f32_from_ll.exit11, label %317
    builder.CreateCondBr(valcond17, valf32_from_ll_exit11, val317);
    builder.SetInsertPoint(val317);
    //   %318 = shl i32 %1, 24
    Value *val318 = builder.CreateShl(val1, builder.getInt32(24), "", false, false);
    //   %.not18 = icmp eq i32 %318, 0
    Value *val_not18 = builder.CreateICmpEQ(val318, builder.getInt32(0), "");
    //   br i1 %.not18, label %341, label %.preheader.i10.preheader
    builder.CreateCondBr(val_not18, val341, val_preheader_i10_preheader);
    builder.SetInsertPoint(val_preheader_i10_preheader);
    //   %319 = zext i32 %318 to i64
    Value *val319 = builder.CreateZExt(val318, Type::getInt64Ty(context));
    //   br label %.preheader.i10
    builder.CreateBr(val_preheader_i10);
    builder.SetInsertPoint(val_preheader_i10);
    //   %320 = phi i32 [ %326, %.preheader.i10 ], [ 0, %.preheader.i10.preheader ]
    PHINode *val320 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %321 = phi i64 [ %327, %.preheader.i10 ], [ %319, %.preheader.i10.preheader ]
    PHINode *val321 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %322 = phi i32 [ %328, %.preheader.i10 ], [ -1, %.preheader.i10.preheader ]
    PHINode *val322 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %323 = trunc i64 %321 to i8
    Value *val323 = builder.CreateTrunc(val321, Type::getInt8Ty(context));
    //   %324 = and i8 %323, 1
    Value *val324 = builder.CreateAnd(val323, builder.getInt8(1), "");
    //   %325 = zext nneg i8 %324 to i32
    Value *val325 = builder.CreateZExt(val324, Type::getInt32Ty(context));
    //   %326 = add i32 %320, %325
    Value *val326 = builder.CreateAdd(val320, val325, "", false, false);
    //   %327 = lshr i64 %321, 1
    Value *val327 = builder.CreateLShr(val321, builder.getInt64(1ll), "", false);
    //   %328 = add i32 %322, 1
    Value *val328 = builder.CreateAdd(val322, builder.getInt32(1), "", false, false);
    //   %329 = icmp ugt i64 %321, 33554431
    Value *val329 = builder.CreateICmpUGT(val321, builder.getInt64(33554431ll), "");
    //   %330 = icmp slt i32 %328, -126
    Value *val330 = builder.CreateICmpSLT(val328, builder.getInt32(-126), "");
    //   %331 = select i1 %329, i1 true, i1 %330
    Value *val331 = builder.CreateSelect(val329, builder.getInt1(true), val330);
    //   br i1 %331, label %.preheader.i10, label %332, !llvm.loop !4
    builder.CreateCondBr(val331, val_preheader_i10, val332);
    builder.SetInsertPoint(val332);
    //   %333 = icmp eq i8 %324, 0
    Value *val333 = builder.CreateICmpEQ(val324, builder.getInt8(0), "");
    //   br i1 %333, label %341, label %334
    builder.CreateCondBr(val333, val341, val334);
    builder.SetInsertPoint(val334);
    //   %335 = icmp sgt i32 %326, 1
    Value *val335 = builder.CreateICmpSGT(val326, builder.getInt32(1), "");
    //   %336 = and i64 %321, 2
    Value *val336 = builder.CreateAnd(val321, builder.getInt64(2ll), "");
    //   %337 = icmp ne i64 %336, 0
    Value *val337 = builder.CreateICmpNE(val336, builder.getInt64(0ll), "");
    //   %338 = or i1 %337, %335
    Value *val338 = builder.CreateOr(val337, val335, "");
    //   %339 = zext i1 %338 to i64
    Value *val339 = builder.CreateZExt(val338, Type::getInt64Ty(context));
    //   %340 = add nuw nsw i64 %327, %339
    Value *val340 = builder.CreateAdd(val327, val339, "", true, true);
    //   br label %341
    builder.CreateBr(val341);
    builder.SetInsertPoint(val341);
    //   %342 = phi i32 [ %328, %332 ], [ %328, %334 ], [ -1, %317 ]
    PHINode *val342 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %343 = phi i64 [ %327, %332 ], [ %340, %334 ], [ 0, %317 ]
    PHINode *val343 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %344 = icmp ugt i64 %343, 16777215
    Value *val344 = builder.CreateICmpUGT(val343, builder.getInt64(16777215ll), "");
    //   %345 = zext i1 %344 to i32
    Value *val345 = builder.CreateZExt(val344, Type::getInt32Ty(context));
    //   %346 = add i32 %342, %345
    Value *val346 = builder.CreateAdd(val342, val345, "", false, false);
    //   %347 = icmp sgt i32 %346, 127
    Value *val347 = builder.CreateICmpSGT(val346, builder.getInt32(127), "");
    //   br i1 %347, label %f32_from_ll.exit11, label %348
    builder.CreateCondBr(val347, valf32_from_ll_exit11, val348);
    builder.SetInsertPoint(val348);
    //   %349 = select i1 %344, i64 8388608, i64 %343
    Value *val349 = builder.CreateSelect(val344, builder.getInt64(8388608ll), val343);
    //   %350 = icmp ugt i64 %349, 8388607
    Value *val350 = builder.CreateICmpUGT(val349, builder.getInt64(8388607ll), "");
    //   %351 = trunc i64 %349 to i32
    Value *val351 = builder.CreateTrunc(val349, Type::getInt32Ty(context));
    //   br i1 %350, label %352, label %f32_from_ll.exit11
    builder.CreateCondBr(val350, val352, valf32_from_ll_exit11);
    builder.SetInsertPoint(val352);
    //   %353 = and i32 %351, 8388607
    Value *val353 = builder.CreateAnd(val351, builder.getInt32(8388607), "");
    //   %354 = shl i32 %346, 23
    Value *val354 = builder.CreateShl(val346, builder.getInt32(23), "", false, false);
    //   %355 = add i32 %354, 1065353216
    Value *val355 = builder.CreateAdd(val354, builder.getInt32(1065353216), "", false, false);
    //   %356 = and i32 %355, 2139095040
    Value *val356 = builder.CreateAnd(val355, builder.getInt32(2139095040), "");
    //   %357 = or disjoint i32 %356, %353
    Value *val357 = builder.CreateOr(val356, val353, "");
    //   br label %f32_from_ll.exit11
    builder.CreateBr(valf32_from_ll_exit11);
    builder.SetInsertPoint(valf32_from_ll_exit11);
    //   %358 = phi i32 [ 0, %f32_from_ll.exit9 ], [ %357, %352 ], [ 2139095040, %341 ], [ %351, %348 ]
    PHINode *val358 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %359 = tail call i32 @f32_mul(i32 noundef %358, i32 noundef %11) #9
    Value *val359 = builder.CreateCall(funcf32_mul, {val358, val11});
    //   %360 = tail call i32 @f32_add(i32 noundef %315, i32 noundef %359) #9
    Value *val360 = builder.CreateCall(funcf32_add, {val315, val359});
    //   %361 = and i32 %360, 2147483647
    Value *val361 = builder.CreateAnd(val360, builder.getInt32(2147483647), "");
    //   %362 = icmp eq i32 %361, 2139095040
    Value *val362 = builder.CreateICmpEQ(val361, builder.getInt32(2139095040), "");
    //   br i1 %362, label %f32_to_ll.exit12, label %363
    builder.CreateCondBr(val362, valf32_to_ll_exit12, val363);
    builder.SetInsertPoint(val363);
    //   %364 = and i32 %360, 2139095040
    Value *val364 = builder.CreateAnd(val360, builder.getInt32(2139095040), "");
    //   %365 = icmp eq i32 %364, 2139095040
    Value *val365 = builder.CreateICmpEQ(val364, builder.getInt32(2139095040), "");
    //   %366 = and i32 %360, 8388607
    Value *val366 = builder.CreateAnd(val360, builder.getInt32(8388607), "");
    //   %367 = icmp ne i32 %366, 0
    Value *val367 = builder.CreateICmpNE(val366, builder.getInt32(0), "");
    //   %368 = and i1 %365, %367
    Value *val368 = builder.CreateAnd(val365, val367, "");
    //   br i1 %368, label %f32_to_ll.exit12, label %369
    builder.CreateCondBr(val368, valf32_to_ll_exit12, val369);
    builder.SetInsertPoint(val369);
    //   %370 = icmp eq i32 %361, 0
    Value *val370 = builder.CreateICmpEQ(val361, builder.getInt32(0), "");
    //   br i1 %370, label %f32_to_ll.exit12, label %371
    builder.CreateCondBr(val370, valf32_to_ll_exit12, val371);
    builder.SetInsertPoint(val371);
    //   %372 = zext nneg i32 %366 to i64
    Value *val372 = builder.CreateZExt(val366, Type::getInt64Ty(context));
    //   %373 = icmp ne i32 %364, 0
    Value *val373 = builder.CreateICmpNE(val364, builder.getInt32(0), "");
    //   %374 = icmp eq i32 %366, 0
    Value *val374 = builder.CreateICmpEQ(val366, builder.getInt32(0), "");
    //   %375 = or i1 %373, %374
    Value *val375 = builder.CreateOr(val373, val374, "");
    //   %376 = or disjoint i64 %372, 8388608
    Value *val376 = builder.CreateOr(val372, builder.getInt64(8388608ll), "");
    //   %377 = select i1 %375, i64 %376, i64 %372
    Value *val377 = builder.CreateSelect(val375, val376, val372);
    //   %378 = icmp eq i32 %364, 0
    Value *val378 = builder.CreateICmpEQ(val364, builder.getInt32(0), "");
    //   %379 = and i1 %378, %367
    Value *val379 = builder.CreateAnd(val378, val367, "");
    //   %380 = lshr i32 %360, 23
    Value *val380 = builder.CreateLShr(val360, builder.getInt32(23), "", false);
    //   %381 = and i32 %380, 255
    Value *val381 = builder.CreateAnd(val380, builder.getInt32(255), "");
    //   %382 = add nsw i32 %381, -127
    Value *val382 = builder.CreateAdd(val381, builder.getInt32(-127), "", false, true);
    //   %383 = select i1 %379, i32 -126, i32 %382
    Value *val383 = builder.CreateSelect(val379, builder.getInt32(-126), val382);
    //   %384 = add nsw i32 %383, -23
    Value *val384 = builder.CreateAdd(val383, builder.getInt32(-23), "", false, true);
    //   %385 = icmp slt i32 %383, -40
    Value *val385 = builder.CreateICmpSLT(val383, builder.getInt32(-40), "");
    //   br i1 %385, label %f32_to_ll.exit12, label %386
    builder.CreateCondBr(val385, valf32_to_ll_exit12, val386);
    builder.SetInsertPoint(val386);
    //   %387 = icmp slt i32 %383, 24
    Value *val387 = builder.CreateICmpSLT(val383, builder.getInt32(24), "");
    //   br i1 %387, label %388, label %395
    builder.CreateCondBr(val387, val388, val395);
    builder.SetInsertPoint(val388);
    //   %389 = sub nsw i32 23, %383
    Value *val389 = builder.CreateSub(builder.getInt32(23), val383, "", false, true);
    //   %390 = zext nneg i32 %389 to i64
    Value *val390 = builder.CreateZExt(val389, Type::getInt64Ty(context));
    //   %391 = lshr i64 %377, %390
    Value *val391 = builder.CreateLShr(val377, val390, "", false);
    //   %392 = sub nsw i64 0, %391
    Value *val392 = builder.CreateSub(builder.getInt64(0ll), val391, "", false, true);
    //   %393 = icmp slt i32 %360, 0
    Value *val393 = builder.CreateICmpSLT(val360, builder.getInt32(0), "");
    //   %394 = select i1 %393, i64 %392, i64 %391
    Value *val394 = builder.CreateSelect(val393, val392, val391);
    //   br label %f32_to_ll.exit12
    builder.CreateBr(valf32_to_ll_exit12);
    builder.SetInsertPoint(val395);
    //   %396 = icmp ult i32 %383, 63
    Value *val396 = builder.CreateICmpULT(val383, builder.getInt32(63), "");
    //   br i1 %396, label %397, label %f32_to_ll.exit12
    builder.CreateCondBr(val396, val397, valf32_to_ll_exit12);
    builder.SetInsertPoint(val397);
    //   %398 = zext nneg i32 %384 to i64
    Value *val398 = builder.CreateZExt(val384, Type::getInt64Ty(context));
    //   %399 = shl nuw nsw i64 %377, %398
    Value *val399 = builder.CreateShl(val377, val398, "", true, true);
    //   %400 = sub nsw i64 0, %399
    Value *val400 = builder.CreateSub(builder.getInt64(0ll), val399, "", false, true);
    //   %401 = icmp slt i32 %360, 0
    Value *val401 = builder.CreateICmpSLT(val360, builder.getInt32(0), "");
    //   %402 = select i1 %401, i64 %400, i64 %399
    Value *val402 = builder.CreateSelect(val401, val400, val399);
    //   br label %f32_to_ll.exit12
    builder.CreateBr(valf32_to_ll_exit12);
    builder.SetInsertPoint(valf32_to_ll_exit12);
    //   %403 = phi i64 [ -9223372036854775808, %363 ], [ -9223372036854775808, %f32_from_ll.exit11 ], [ 0, %369 ], [ %394, %388 ], [ %402, %397 ], [ 0, %371 ], [ -9223372036854775808, %395 ]
    PHINode *val403 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %404 = trunc i64 %271 to i32
    Value *val404 = builder.CreateTrunc(val271, Type::getInt32Ty(context));
    //   %405 = trunc i64 %141 to i32
    Value *val405 = builder.CreateTrunc(val141, Type::getInt32Ty(context));
    //   %406 = trunc i64 %403 to i32
    Value *val406 = builder.CreateTrunc(val403, Type::getInt32Ty(context));
    //   %407 = and i32 %405, 16711680
    Value *val407 = builder.CreateAnd(val405, builder.getInt32(16711680), "");
    //   %408 = and i32 %404, 65280
    Value *val408 = builder.CreateAnd(val404, builder.getInt32(65280), "");
    //   %409 = or disjoint i32 %408, %407
    Value *val409 = builder.CreateOr(val408, val407, "");
    //   %410 = and i32 %406, 255
    Value *val410 = builder.CreateAnd(val406, builder.getInt32(255), "");
    //   %411 = or disjoint i32 %409, %410
    Value *val411 = builder.CreateOr(val409, val410, "");
    //   ret i32 %411
    builder.CreateRet(val411);
    val16->addIncoming(val22, val_preheader_i);
    val16->addIncoming(builder.getInt32(0), val13);
    val17->addIncoming(val23, val_preheader_i);
    val17->addIncoming(val15, val13);
    val18->addIncoming(val24, val_preheader_i);
    val18->addIncoming(builder.getInt32(-1), val13);
    val38->addIncoming(val23, val28);
    val38->addIncoming(val36, val30);
    val53->addIncoming(builder.getInt32(0), val3);
    val53->addIncoming(val52, val47);
    val53->addIncoming(builder.getInt32(2139095040), val37);
    val53->addIncoming(val46, val43);
    val59->addIncoming(val65, val_preheader_i1);
    val59->addIncoming(builder.getInt32(0), val56);
    val60->addIncoming(val66, val_preheader_i1);
    val60->addIncoming(val58, val56);
    val61->addIncoming(val67, val_preheader_i1);
    val61->addIncoming(builder.getInt32(-1), val56);
    val81->addIncoming(val66, val71);
    val81->addIncoming(val79, val73);
    val96->addIncoming(builder.getInt32(0), valf32_from_ll_exit);
    val96->addIncoming(val95, val90);
    val96->addIncoming(builder.getInt32(2139095040), val80);
    val96->addIncoming(val89, val86);
    val141->addIncoming(builder.getInt64(-9223372036854775808ll), val101);
    val141->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit2);
    val141->addIncoming(builder.getInt64(0ll), val107);
    val141->addIncoming(val132, val126);
    val141->addIncoming(val140, val135);
    val141->addIncoming(builder.getInt64(0ll), val109);
    val141->addIncoming(builder.getInt64(-9223372036854775808ll), val133);
    val146->addIncoming(val152, val_preheader_i3);
    val146->addIncoming(builder.getInt32(0), val143);
    val147->addIncoming(val153, val_preheader_i3);
    val147->addIncoming(val145, val143);
    val148->addIncoming(val154, val_preheader_i3);
    val148->addIncoming(builder.getInt32(-1), val143);
    val168->addIncoming(val153, val158);
    val168->addIncoming(val166, val160);
    val183->addIncoming(builder.getInt32(0), valf32_to_ll_exit);
    val183->addIncoming(val182, val177);
    val183->addIncoming(builder.getInt32(2139095040), val167);
    val183->addIncoming(val176, val173);
    val189->addIncoming(val195, val_preheader_i5);
    val189->addIncoming(builder.getInt32(0), val186);
    val190->addIncoming(val196, val_preheader_i5);
    val190->addIncoming(val188, val186);
    val191->addIncoming(val197, val_preheader_i5);
    val191->addIncoming(builder.getInt32(-1), val186);
    val211->addIncoming(val196, val201);
    val211->addIncoming(val209, val203);
    val226->addIncoming(builder.getInt32(0), valf32_from_ll_exit4);
    val226->addIncoming(val225, val220);
    val226->addIncoming(builder.getInt32(2139095040), val210);
    val226->addIncoming(val219, val216);
    val271->addIncoming(builder.getInt64(-9223372036854775808ll), val231);
    val271->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit6);
    val271->addIncoming(builder.getInt64(0ll), val237);
    val271->addIncoming(val262, val256);
    val271->addIncoming(val270, val265);
    val271->addIncoming(builder.getInt64(0ll), val239);
    val271->addIncoming(builder.getInt64(-9223372036854775808ll), val263);
    val276->addIncoming(val282, val_preheader_i8);
    val276->addIncoming(builder.getInt32(0), val_preheader_i8_preheader);
    val277->addIncoming(val283, val_preheader_i8);
    val277->addIncoming(val275, val_preheader_i8_preheader);
    val278->addIncoming(val284, val_preheader_i8);
    val278->addIncoming(builder.getInt32(-1), val_preheader_i8_preheader);
    val298->addIncoming(val284, val288);
    val298->addIncoming(val284, val290);
    val298->addIncoming(builder.getInt32(-1), val273);
    val299->addIncoming(val283, val288);
    val299->addIncoming(val296, val290);
    val299->addIncoming(builder.getInt64(0ll), val273);
    val314->addIncoming(builder.getInt32(0), valf32_to_ll_exit7);
    val314->addIncoming(val313, val308);
    val314->addIncoming(builder.getInt32(2139095040), val297);
    val314->addIncoming(val307, val304);
    val320->addIncoming(val326, val_preheader_i10);
    val320->addIncoming(builder.getInt32(0), val_preheader_i10_preheader);
    val321->addIncoming(val327, val_preheader_i10);
    val321->addIncoming(val319, val_preheader_i10_preheader);
    val322->addIncoming(val328, val_preheader_i10);
    val322->addIncoming(builder.getInt32(-1), val_preheader_i10_preheader);
    val342->addIncoming(val328, val332);
    val342->addIncoming(val328, val334);
    val342->addIncoming(builder.getInt32(-1), val317);
    val343->addIncoming(val327, val332);
    val343->addIncoming(val340, val334);
    val343->addIncoming(builder.getInt64(0ll), val317);
    val358->addIncoming(builder.getInt32(0), valf32_from_ll_exit9);
    val358->addIncoming(val357, val352);
    val358->addIncoming(builder.getInt32(2139095040), val341);
    val358->addIncoming(val351, val348);
    val403->addIncoming(builder.getInt64(-9223372036854775808ll), val363);
    val403->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit11);
    val403->addIncoming(builder.getInt64(0ll), val369);
    val403->addIncoming(val394, val388);
    val403->addIncoming(val402, val397);
    val403->addIncoming(builder.getInt64(0ll), val371);
    val403->addIncoming(builder.getInt64(-9223372036854775808ll), val395);
  }
  {
    Function *func = funcshadow;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = tail call i32 @combine(i32 noundef %0, i32 noundef 12303291, i32 noundef %1), !range !4
    Value *val3 = builder.CreateCall(funccombine, {val0, builder.getInt32(12303291), val1});
    //   ret i32 %3
    builder.CreateRet(val3);
  }
  {
    Function *func = funcreflection;
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val5 = BasicBlock::Create(context, "", func);
    BasicBlock *val7 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i = BasicBlock::Create(context, "", func);
    BasicBlock *val22 = BasicBlock::Create(context, "", func);
    BasicBlock *val24 = BasicBlock::Create(context, "", func);
    BasicBlock *val31 = BasicBlock::Create(context, "", func);
    BasicBlock *val37 = BasicBlock::Create(context, "", func);
    BasicBlock *val41 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val49 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i1 = BasicBlock::Create(context, "", func);
    BasicBlock *val64 = BasicBlock::Create(context, "", func);
    BasicBlock *val66 = BasicBlock::Create(context, "", func);
    BasicBlock *val73 = BasicBlock::Create(context, "", func);
    BasicBlock *val79 = BasicBlock::Create(context, "", func);
    BasicBlock *val83 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit2 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i3 = BasicBlock::Create(context, "", func);
    BasicBlock *val104 = BasicBlock::Create(context, "", func);
    BasicBlock *val106 = BasicBlock::Create(context, "", func);
    BasicBlock *val113 = BasicBlock::Create(context, "", func);
    BasicBlock *val119 = BasicBlock::Create(context, "", func);
    BasicBlock *val123 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit4 = BasicBlock::Create(context, "", func);
    BasicBlock *val133 = BasicBlock::Create(context, "", func);
    BasicBlock *val139 = BasicBlock::Create(context, "", func);
    BasicBlock *val141 = BasicBlock::Create(context, "", func);
    BasicBlock *val156 = BasicBlock::Create(context, "", func);
    BasicBlock *val158 = BasicBlock::Create(context, "", func);
    BasicBlock *val165 = BasicBlock::Create(context, "", func);
    BasicBlock *val167 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val177 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i5 = BasicBlock::Create(context, "", func);
    BasicBlock *val192 = BasicBlock::Create(context, "", func);
    BasicBlock *val194 = BasicBlock::Create(context, "", func);
    BasicBlock *val201 = BasicBlock::Create(context, "", func);
    BasicBlock *val207 = BasicBlock::Create(context, "", func);
    BasicBlock *val211 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit6 = BasicBlock::Create(context, "", func);
    BasicBlock *val219 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i7 = BasicBlock::Create(context, "", func);
    BasicBlock *val234 = BasicBlock::Create(context, "", func);
    BasicBlock *val236 = BasicBlock::Create(context, "", func);
    BasicBlock *val243 = BasicBlock::Create(context, "", func);
    BasicBlock *val249 = BasicBlock::Create(context, "", func);
    BasicBlock *val253 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit8 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i9 = BasicBlock::Create(context, "", func);
    BasicBlock *val274 = BasicBlock::Create(context, "", func);
    BasicBlock *val276 = BasicBlock::Create(context, "", func);
    BasicBlock *val283 = BasicBlock::Create(context, "", func);
    BasicBlock *val289 = BasicBlock::Create(context, "", func);
    BasicBlock *val293 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit10 = BasicBlock::Create(context, "", func);
    BasicBlock *val303 = BasicBlock::Create(context, "", func);
    BasicBlock *val309 = BasicBlock::Create(context, "", func);
    BasicBlock *val311 = BasicBlock::Create(context, "", func);
    BasicBlock *val326 = BasicBlock::Create(context, "", func);
    BasicBlock *val328 = BasicBlock::Create(context, "", func);
    BasicBlock *val335 = BasicBlock::Create(context, "", func);
    BasicBlock *val337 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit11 = BasicBlock::Create(context, "", func);
    BasicBlock *val347 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i12_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i12 = BasicBlock::Create(context, "", func);
    BasicBlock *val362 = BasicBlock::Create(context, "", func);
    BasicBlock *val364 = BasicBlock::Create(context, "", func);
    BasicBlock *val371 = BasicBlock::Create(context, "", func);
    BasicBlock *val378 = BasicBlock::Create(context, "", func);
    BasicBlock *val382 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit13 = BasicBlock::Create(context, "", func);
    BasicBlock *val390 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i14_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i14 = BasicBlock::Create(context, "", func);
    BasicBlock *val405 = BasicBlock::Create(context, "", func);
    BasicBlock *val407 = BasicBlock::Create(context, "", func);
    BasicBlock *val414 = BasicBlock::Create(context, "", func);
    BasicBlock *val421 = BasicBlock::Create(context, "", func);
    BasicBlock *val425 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit15 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i16 = BasicBlock::Create(context, "", func);
    BasicBlock *val446 = BasicBlock::Create(context, "", func);
    BasicBlock *val448 = BasicBlock::Create(context, "", func);
    BasicBlock *val455 = BasicBlock::Create(context, "", func);
    BasicBlock *val461 = BasicBlock::Create(context, "", func);
    BasicBlock *val465 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit17 = BasicBlock::Create(context, "", func);
    BasicBlock *val475 = BasicBlock::Create(context, "", func);
    BasicBlock *val481 = BasicBlock::Create(context, "", func);
    BasicBlock *val483 = BasicBlock::Create(context, "", func);
    BasicBlock *val498 = BasicBlock::Create(context, "", func);
    BasicBlock *val500 = BasicBlock::Create(context, "", func);
    BasicBlock *val507 = BasicBlock::Create(context, "", func);
    BasicBlock *val509 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_to_ll_exit18 = BasicBlock::Create(context, "", func);
    BasicBlock *val521 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    builder.SetInsertPoint(val3);
    //   %4 = icmp eq i32 %1, -1
    Value *val4 = builder.CreateICmpEQ(val1, builder.getInt32(-1), "");
    //   br i1 %4, label %521, label %5
    builder.CreateCondBr(val4, val521, val5);
    builder.SetInsertPoint(val5);
    //   %6 = and i32 %1, 16711680
    Value *val6 = builder.CreateAnd(val1, builder.getInt32(16711680), "");
    //   %cond = icmp eq i32 %6, 0
    Value *valcond = builder.CreateICmpEQ(val6, builder.getInt32(0), "");
    //   br i1 %cond, label %f32_from_ll.exit, label %7
    builder.CreateCondBr(valcond, valf32_from_ll_exit, val7);
    builder.SetInsertPoint(val7);
    //   %8 = zext nneg i32 %6 to i64
    Value *val8 = builder.CreateZExt(val6, Type::getInt64Ty(context));
    //   %9 = shl nuw nsw i64 %8, 24
    Value *val9 = builder.CreateShl(val8, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i
    builder.CreateBr(val_preheader_i);
    builder.SetInsertPoint(val_preheader_i);
    //   %10 = phi i32 [ %16, %.preheader.i ], [ 0, %7 ]
    PHINode *val10 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %11 = phi i64 [ %17, %.preheader.i ], [ %9, %7 ]
    PHINode *val11 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %12 = phi i32 [ %18, %.preheader.i ], [ -1, %7 ]
    PHINode *val12 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %13 = trunc i64 %11 to i8
    Value *val13 = builder.CreateTrunc(val11, Type::getInt8Ty(context));
    //   %14 = and i8 %13, 1
    Value *val14 = builder.CreateAnd(val13, builder.getInt8(1), "");
    //   %15 = zext nneg i8 %14 to i32
    Value *val15 = builder.CreateZExt(val14, Type::getInt32Ty(context));
    //   %16 = add i32 %10, %15
    Value *val16 = builder.CreateAdd(val10, val15, "", false, false);
    //   %17 = lshr i64 %11, 1
    Value *val17 = builder.CreateLShr(val11, builder.getInt64(1ll), "", false);
    //   %18 = add i32 %12, 1
    Value *val18 = builder.CreateAdd(val12, builder.getInt32(1), "", false, false);
    //   %19 = icmp ugt i64 %11, 33554431
    Value *val19 = builder.CreateICmpUGT(val11, builder.getInt64(33554431ll), "");
    //   %20 = icmp slt i32 %18, -126
    Value *val20 = builder.CreateICmpSLT(val18, builder.getInt32(-126), "");
    //   %21 = select i1 %19, i1 true, i1 %20
    Value *val21 = builder.CreateSelect(val19, builder.getInt1(true), val20);
    //   br i1 %21, label %.preheader.i, label %22, !llvm.loop !4
    builder.CreateCondBr(val21, val_preheader_i, val22);
    builder.SetInsertPoint(val22);
    //   %23 = icmp eq i8 %14, 0
    Value *val23 = builder.CreateICmpEQ(val14, builder.getInt8(0), "");
    //   br i1 %23, label %31, label %24
    builder.CreateCondBr(val23, val31, val24);
    builder.SetInsertPoint(val24);
    //   %25 = icmp sgt i32 %16, 1
    Value *val25 = builder.CreateICmpSGT(val16, builder.getInt32(1), "");
    //   %26 = and i64 %11, 2
    Value *val26 = builder.CreateAnd(val11, builder.getInt64(2ll), "");
    //   %27 = icmp ne i64 %26, 0
    Value *val27 = builder.CreateICmpNE(val26, builder.getInt64(0ll), "");
    //   %28 = or i1 %27, %25
    Value *val28 = builder.CreateOr(val27, val25, "");
    //   %29 = zext i1 %28 to i64
    Value *val29 = builder.CreateZExt(val28, Type::getInt64Ty(context));
    //   %30 = add nuw nsw i64 %17, %29
    Value *val30 = builder.CreateAdd(val17, val29, "", true, true);
    //   br label %31
    builder.CreateBr(val31);
    builder.SetInsertPoint(val31);
    //   %32 = phi i64 [ %17, %22 ], [ %30, %24 ]
    PHINode *val32 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %33 = icmp ugt i64 %32, 16777215
    Value *val33 = builder.CreateICmpUGT(val32, builder.getInt64(16777215ll), "");
    //   %34 = zext i1 %33 to i32
    Value *val34 = builder.CreateZExt(val33, Type::getInt32Ty(context));
    //   %35 = add i32 %18, %34
    Value *val35 = builder.CreateAdd(val18, val34, "", false, false);
    //   %36 = icmp sgt i32 %35, 127
    Value *val36 = builder.CreateICmpSGT(val35, builder.getInt32(127), "");
    //   br i1 %36, label %f32_from_ll.exit, label %37
    builder.CreateCondBr(val36, valf32_from_ll_exit, val37);
    builder.SetInsertPoint(val37);
    //   %38 = select i1 %33, i64 8388608, i64 %32
    Value *val38 = builder.CreateSelect(val33, builder.getInt64(8388608ll), val32);
    //   %39 = icmp ugt i64 %38, 8388607
    Value *val39 = builder.CreateICmpUGT(val38, builder.getInt64(8388607ll), "");
    //   %40 = trunc i64 %38 to i32
    Value *val40 = builder.CreateTrunc(val38, Type::getInt32Ty(context));
    //   br i1 %39, label %41, label %f32_from_ll.exit
    builder.CreateCondBr(val39, val41, valf32_from_ll_exit);
    builder.SetInsertPoint(val41);
    //   %42 = and i32 %40, 8388607
    Value *val42 = builder.CreateAnd(val40, builder.getInt32(8388607), "");
    //   %43 = shl i32 %35, 23
    Value *val43 = builder.CreateShl(val35, builder.getInt32(23), "", false, false);
    //   %44 = add i32 %43, 1065353216
    Value *val44 = builder.CreateAdd(val43, builder.getInt32(1065353216), "", false, false);
    //   %45 = and i32 %44, 2139095040
    Value *val45 = builder.CreateAnd(val44, builder.getInt32(2139095040), "");
    //   %46 = or disjoint i32 %45, %42
    Value *val46 = builder.CreateOr(val45, val42, "");
    //   br label %f32_from_ll.exit
    builder.CreateBr(valf32_from_ll_exit);
    builder.SetInsertPoint(valf32_from_ll_exit);
    //   %47 = phi i32 [ 0, %5 ], [ %46, %41 ], [ 2139095040, %31 ], [ %40, %37 ]
    PHINode *val47 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %48 = and i32 %0, 16711680
    Value *val48 = builder.CreateAnd(val0, builder.getInt32(16711680), "");
    //   %cond19 = icmp eq i32 %48, 0
    Value *valcond19 = builder.CreateICmpEQ(val48, builder.getInt32(0), "");
    //   br i1 %cond19, label %f32_from_ll.exit2, label %49
    builder.CreateCondBr(valcond19, valf32_from_ll_exit2, val49);
    builder.SetInsertPoint(val49);
    //   %50 = zext nneg i32 %48 to i64
    Value *val50 = builder.CreateZExt(val48, Type::getInt64Ty(context));
    //   %51 = shl nuw nsw i64 %50, 24
    Value *val51 = builder.CreateShl(val50, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i1
    builder.CreateBr(val_preheader_i1);
    builder.SetInsertPoint(val_preheader_i1);
    //   %52 = phi i32 [ %58, %.preheader.i1 ], [ 0, %49 ]
    PHINode *val52 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %53 = phi i64 [ %59, %.preheader.i1 ], [ %51, %49 ]
    PHINode *val53 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %54 = phi i32 [ %60, %.preheader.i1 ], [ -1, %49 ]
    PHINode *val54 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %55 = trunc i64 %53 to i8
    Value *val55 = builder.CreateTrunc(val53, Type::getInt8Ty(context));
    //   %56 = and i8 %55, 1
    Value *val56 = builder.CreateAnd(val55, builder.getInt8(1), "");
    //   %57 = zext nneg i8 %56 to i32
    Value *val57 = builder.CreateZExt(val56, Type::getInt32Ty(context));
    //   %58 = add i32 %52, %57
    Value *val58 = builder.CreateAdd(val52, val57, "", false, false);
    //   %59 = lshr i64 %53, 1
    Value *val59 = builder.CreateLShr(val53, builder.getInt64(1ll), "", false);
    //   %60 = add i32 %54, 1
    Value *val60 = builder.CreateAdd(val54, builder.getInt32(1), "", false, false);
    //   %61 = icmp ugt i64 %53, 33554431
    Value *val61 = builder.CreateICmpUGT(val53, builder.getInt64(33554431ll), "");
    //   %62 = icmp slt i32 %60, -126
    Value *val62 = builder.CreateICmpSLT(val60, builder.getInt32(-126), "");
    //   %63 = select i1 %61, i1 true, i1 %62
    Value *val63 = builder.CreateSelect(val61, builder.getInt1(true), val62);
    //   br i1 %63, label %.preheader.i1, label %64, !llvm.loop !4
    builder.CreateCondBr(val63, val_preheader_i1, val64);
    builder.SetInsertPoint(val64);
    //   %65 = icmp eq i8 %56, 0
    Value *val65 = builder.CreateICmpEQ(val56, builder.getInt8(0), "");
    //   br i1 %65, label %73, label %66
    builder.CreateCondBr(val65, val73, val66);
    builder.SetInsertPoint(val66);
    //   %67 = icmp sgt i32 %58, 1
    Value *val67 = builder.CreateICmpSGT(val58, builder.getInt32(1), "");
    //   %68 = and i64 %53, 2
    Value *val68 = builder.CreateAnd(val53, builder.getInt64(2ll), "");
    //   %69 = icmp ne i64 %68, 0
    Value *val69 = builder.CreateICmpNE(val68, builder.getInt64(0ll), "");
    //   %70 = or i1 %69, %67
    Value *val70 = builder.CreateOr(val69, val67, "");
    //   %71 = zext i1 %70 to i64
    Value *val71 = builder.CreateZExt(val70, Type::getInt64Ty(context));
    //   %72 = add nuw nsw i64 %59, %71
    Value *val72 = builder.CreateAdd(val59, val71, "", true, true);
    //   br label %73
    builder.CreateBr(val73);
    builder.SetInsertPoint(val73);
    //   %74 = phi i64 [ %59, %64 ], [ %72, %66 ]
    PHINode *val74 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %75 = icmp ugt i64 %74, 16777215
    Value *val75 = builder.CreateICmpUGT(val74, builder.getInt64(16777215ll), "");
    //   %76 = zext i1 %75 to i32
    Value *val76 = builder.CreateZExt(val75, Type::getInt32Ty(context));
    //   %77 = add i32 %60, %76
    Value *val77 = builder.CreateAdd(val60, val76, "", false, false);
    //   %78 = icmp sgt i32 %77, 127
    Value *val78 = builder.CreateICmpSGT(val77, builder.getInt32(127), "");
    //   br i1 %78, label %f32_from_ll.exit2, label %79
    builder.CreateCondBr(val78, valf32_from_ll_exit2, val79);
    builder.SetInsertPoint(val79);
    //   %80 = select i1 %75, i64 8388608, i64 %74
    Value *val80 = builder.CreateSelect(val75, builder.getInt64(8388608ll), val74);
    //   %81 = icmp ugt i64 %80, 8388607
    Value *val81 = builder.CreateICmpUGT(val80, builder.getInt64(8388607ll), "");
    //   %82 = trunc i64 %80 to i32
    Value *val82 = builder.CreateTrunc(val80, Type::getInt32Ty(context));
    //   br i1 %81, label %83, label %f32_from_ll.exit2
    builder.CreateCondBr(val81, val83, valf32_from_ll_exit2);
    builder.SetInsertPoint(val83);
    //   %84 = and i32 %82, 8388607
    Value *val84 = builder.CreateAnd(val82, builder.getInt32(8388607), "");
    //   %85 = shl i32 %77, 23
    Value *val85 = builder.CreateShl(val77, builder.getInt32(23), "", false, false);
    //   %86 = add i32 %85, 1065353216
    Value *val86 = builder.CreateAdd(val85, builder.getInt32(1065353216), "", false, false);
    //   %87 = and i32 %86, 2139095040
    Value *val87 = builder.CreateAnd(val86, builder.getInt32(2139095040), "");
    //   %88 = or disjoint i32 %87, %84
    Value *val88 = builder.CreateOr(val87, val84, "");
    //   br label %f32_from_ll.exit2
    builder.CreateBr(valf32_from_ll_exit2);
    builder.SetInsertPoint(valf32_from_ll_exit2);
    //   %89 = phi i32 [ 0, %f32_from_ll.exit ], [ %88, %83 ], [ 2139095040, %73 ], [ %82, %79 ]
    PHINode *val89 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %90 = tail call i32 @f32_mul(i32 noundef %47, i32 noundef %89) #9
    Value *val90 = builder.CreateCall(funcf32_mul, {val47, val89});
    //   %91 = tail call i32 @f32_mul(i32 noundef %90, i32 noundef %2) #9
    Value *val91 = builder.CreateCall(funcf32_mul, {val90, val2});
    //   br label %.preheader.i3
    builder.CreateBr(val_preheader_i3);
    builder.SetInsertPoint(val_preheader_i3);
    //   %92 = phi i32 [ %98, %.preheader.i3 ], [ 0, %f32_from_ll.exit2 ]
    PHINode *val92 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %93 = phi i64 [ %99, %.preheader.i3 ], [ 280375465082880, %f32_from_ll.exit2 ]
    PHINode *val93 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %94 = phi i32 [ %100, %.preheader.i3 ], [ -1, %f32_from_ll.exit2 ]
    PHINode *val94 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %95 = trunc i64 %93 to i8
    Value *val95 = builder.CreateTrunc(val93, Type::getInt8Ty(context));
    //   %96 = and i8 %95, 1
    Value *val96 = builder.CreateAnd(val95, builder.getInt8(1), "");
    //   %97 = zext nneg i8 %96 to i32
    Value *val97 = builder.CreateZExt(val96, Type::getInt32Ty(context));
    //   %98 = add i32 %92, %97
    Value *val98 = builder.CreateAdd(val92, val97, "", false, false);
    //   %99 = lshr i64 %93, 1
    Value *val99 = builder.CreateLShr(val93, builder.getInt64(1ll), "", false);
    //   %100 = add i32 %94, 1
    Value *val100 = builder.CreateAdd(val94, builder.getInt32(1), "", false, false);
    //   %101 = icmp ugt i64 %93, 33554431
    Value *val101 = builder.CreateICmpUGT(val93, builder.getInt64(33554431ll), "");
    //   %102 = icmp slt i32 %100, -126
    Value *val102 = builder.CreateICmpSLT(val100, builder.getInt32(-126), "");
    //   %103 = select i1 %101, i1 true, i1 %102
    Value *val103 = builder.CreateSelect(val101, builder.getInt1(true), val102);
    //   br i1 %103, label %.preheader.i3, label %104, !llvm.loop !4
    builder.CreateCondBr(val103, val_preheader_i3, val104);
    builder.SetInsertPoint(val104);
    //   %105 = icmp eq i8 %96, 0
    Value *val105 = builder.CreateICmpEQ(val96, builder.getInt8(0), "");
    //   br i1 %105, label %113, label %106
    builder.CreateCondBr(val105, val113, val106);
    builder.SetInsertPoint(val106);
    //   %107 = icmp sgt i32 %98, 1
    Value *val107 = builder.CreateICmpSGT(val98, builder.getInt32(1), "");
    //   %108 = and i64 %93, 2
    Value *val108 = builder.CreateAnd(val93, builder.getInt64(2ll), "");
    //   %109 = icmp ne i64 %108, 0
    Value *val109 = builder.CreateICmpNE(val108, builder.getInt64(0ll), "");
    //   %110 = or i1 %109, %107
    Value *val110 = builder.CreateOr(val109, val107, "");
    //   %111 = zext i1 %110 to i64
    Value *val111 = builder.CreateZExt(val110, Type::getInt64Ty(context));
    //   %112 = add nuw nsw i64 %99, %111
    Value *val112 = builder.CreateAdd(val99, val111, "", true, true);
    //   br label %113
    builder.CreateBr(val113);
    builder.SetInsertPoint(val113);
    //   %114 = phi i64 [ %99, %104 ], [ %112, %106 ]
    PHINode *val114 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %115 = icmp ugt i64 %114, 16777215
    Value *val115 = builder.CreateICmpUGT(val114, builder.getInt64(16777215ll), "");
    //   %116 = zext i1 %115 to i32
    Value *val116 = builder.CreateZExt(val115, Type::getInt32Ty(context));
    //   %117 = add i32 %100, %116
    Value *val117 = builder.CreateAdd(val100, val116, "", false, false);
    //   %118 = icmp sgt i32 %117, 127
    Value *val118 = builder.CreateICmpSGT(val117, builder.getInt32(127), "");
    //   br i1 %118, label %f32_from_ll.exit4, label %119
    builder.CreateCondBr(val118, valf32_from_ll_exit4, val119);
    builder.SetInsertPoint(val119);
    //   %120 = select i1 %115, i64 8388608, i64 %114
    Value *val120 = builder.CreateSelect(val115, builder.getInt64(8388608ll), val114);
    //   %121 = icmp ugt i64 %120, 8388607
    Value *val121 = builder.CreateICmpUGT(val120, builder.getInt64(8388607ll), "");
    //   %122 = trunc i64 %120 to i32
    Value *val122 = builder.CreateTrunc(val120, Type::getInt32Ty(context));
    //   br i1 %121, label %123, label %f32_from_ll.exit4
    builder.CreateCondBr(val121, val123, valf32_from_ll_exit4);
    builder.SetInsertPoint(val123);
    //   %124 = and i32 %122, 8388607
    Value *val124 = builder.CreateAnd(val122, builder.getInt32(8388607), "");
    //   %125 = shl i32 %117, 23
    Value *val125 = builder.CreateShl(val117, builder.getInt32(23), "", false, false);
    //   %126 = add i32 %125, 1065353216
    Value *val126 = builder.CreateAdd(val125, builder.getInt32(1065353216), "", false, false);
    //   %127 = and i32 %126, 2139095040
    Value *val127 = builder.CreateAnd(val126, builder.getInt32(2139095040), "");
    //   %128 = or disjoint i32 %127, %124
    Value *val128 = builder.CreateOr(val127, val124, "");
    //   br label %f32_from_ll.exit4
    builder.CreateBr(valf32_from_ll_exit4);
    builder.SetInsertPoint(valf32_from_ll_exit4);
    //   %129 = phi i32 [ %128, %123 ], [ 2139095040, %113 ], [ %122, %119 ]
    PHINode *val129 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %130 = tail call i32 @f32_div(i32 noundef %91, i32 noundef %129) #9
    Value *val130 = builder.CreateCall(funcf32_div, {val91, val129});
    //   %131 = and i32 %130, 2147483647
    Value *val131 = builder.CreateAnd(val130, builder.getInt32(2147483647), "");
    //   %132 = icmp eq i32 %131, 2139095040
    Value *val132 = builder.CreateICmpEQ(val131, builder.getInt32(2139095040), "");
    //   br i1 %132, label %f32_to_ll.exit, label %133
    builder.CreateCondBr(val132, valf32_to_ll_exit, val133);
    builder.SetInsertPoint(val133);
    //   %134 = and i32 %130, 2139095040
    Value *val134 = builder.CreateAnd(val130, builder.getInt32(2139095040), "");
    //   %135 = icmp eq i32 %134, 2139095040
    Value *val135 = builder.CreateICmpEQ(val134, builder.getInt32(2139095040), "");
    //   %136 = and i32 %130, 8388607
    Value *val136 = builder.CreateAnd(val130, builder.getInt32(8388607), "");
    //   %137 = icmp ne i32 %136, 0
    Value *val137 = builder.CreateICmpNE(val136, builder.getInt32(0), "");
    //   %138 = and i1 %135, %137
    Value *val138 = builder.CreateAnd(val135, val137, "");
    //   br i1 %138, label %f32_to_ll.exit, label %139
    builder.CreateCondBr(val138, valf32_to_ll_exit, val139);
    builder.SetInsertPoint(val139);
    //   %140 = icmp eq i32 %131, 0
    Value *val140 = builder.CreateICmpEQ(val131, builder.getInt32(0), "");
    //   br i1 %140, label %f32_to_ll.exit, label %141
    builder.CreateCondBr(val140, valf32_to_ll_exit, val141);
    builder.SetInsertPoint(val141);
    //   %142 = zext nneg i32 %136 to i64
    Value *val142 = builder.CreateZExt(val136, Type::getInt64Ty(context));
    //   %143 = icmp ne i32 %134, 0
    Value *val143 = builder.CreateICmpNE(val134, builder.getInt32(0), "");
    //   %144 = icmp eq i32 %136, 0
    Value *val144 = builder.CreateICmpEQ(val136, builder.getInt32(0), "");
    //   %145 = or i1 %143, %144
    Value *val145 = builder.CreateOr(val143, val144, "");
    //   %146 = or disjoint i64 %142, 8388608
    Value *val146 = builder.CreateOr(val142, builder.getInt64(8388608ll), "");
    //   %147 = select i1 %145, i64 %146, i64 %142
    Value *val147 = builder.CreateSelect(val145, val146, val142);
    //   %148 = icmp eq i32 %134, 0
    Value *val148 = builder.CreateICmpEQ(val134, builder.getInt32(0), "");
    //   %149 = and i1 %148, %137
    Value *val149 = builder.CreateAnd(val148, val137, "");
    //   %150 = lshr i32 %130, 23
    Value *val150 = builder.CreateLShr(val130, builder.getInt32(23), "", false);
    //   %151 = and i32 %150, 255
    Value *val151 = builder.CreateAnd(val150, builder.getInt32(255), "");
    //   %152 = add nsw i32 %151, -127
    Value *val152 = builder.CreateAdd(val151, builder.getInt32(-127), "", false, true);
    //   %153 = select i1 %149, i32 -126, i32 %152
    Value *val153 = builder.CreateSelect(val149, builder.getInt32(-126), val152);
    //   %154 = add nsw i32 %153, -23
    Value *val154 = builder.CreateAdd(val153, builder.getInt32(-23), "", false, true);
    //   %155 = icmp slt i32 %153, -40
    Value *val155 = builder.CreateICmpSLT(val153, builder.getInt32(-40), "");
    //   br i1 %155, label %f32_to_ll.exit, label %156
    builder.CreateCondBr(val155, valf32_to_ll_exit, val156);
    builder.SetInsertPoint(val156);
    //   %157 = icmp slt i32 %153, 24
    Value *val157 = builder.CreateICmpSLT(val153, builder.getInt32(24), "");
    //   br i1 %157, label %158, label %165
    builder.CreateCondBr(val157, val158, val165);
    builder.SetInsertPoint(val158);
    //   %159 = sub nsw i32 23, %153
    Value *val159 = builder.CreateSub(builder.getInt32(23), val153, "", false, true);
    //   %160 = zext nneg i32 %159 to i64
    Value *val160 = builder.CreateZExt(val159, Type::getInt64Ty(context));
    //   %161 = lshr i64 %147, %160
    Value *val161 = builder.CreateLShr(val147, val160, "", false);
    //   %162 = sub nsw i64 0, %161
    Value *val162 = builder.CreateSub(builder.getInt64(0ll), val161, "", false, true);
    //   %163 = icmp slt i32 %130, 0
    Value *val163 = builder.CreateICmpSLT(val130, builder.getInt32(0), "");
    //   %164 = select i1 %163, i64 %162, i64 %161
    Value *val164 = builder.CreateSelect(val163, val162, val161);
    //   br label %f32_to_ll.exit
    builder.CreateBr(valf32_to_ll_exit);
    builder.SetInsertPoint(val165);
    //   %166 = icmp ult i32 %153, 63
    Value *val166 = builder.CreateICmpULT(val153, builder.getInt32(63), "");
    //   br i1 %166, label %167, label %f32_to_ll.exit
    builder.CreateCondBr(val166, val167, valf32_to_ll_exit);
    builder.SetInsertPoint(val167);
    //   %168 = zext nneg i32 %154 to i64
    Value *val168 = builder.CreateZExt(val154, Type::getInt64Ty(context));
    //   %169 = shl nuw nsw i64 %147, %168
    Value *val169 = builder.CreateShl(val147, val168, "", true, true);
    //   %170 = sub nsw i64 0, %169
    Value *val170 = builder.CreateSub(builder.getInt64(0ll), val169, "", false, true);
    //   %171 = icmp slt i32 %130, 0
    Value *val171 = builder.CreateICmpSLT(val130, builder.getInt32(0), "");
    //   %172 = select i1 %171, i64 %170, i64 %169
    Value *val172 = builder.CreateSelect(val171, val170, val169);
    //   br label %f32_to_ll.exit
    builder.CreateBr(valf32_to_ll_exit);
    builder.SetInsertPoint(valf32_to_ll_exit);
    //   %173 = phi i64 [ -9223372036854775808, %133 ], [ -9223372036854775808, %f32_from_ll.exit4 ], [ 0, %139 ], [ %164, %158 ], [ %172, %167 ], [ 0, %141 ], [ -9223372036854775808, %165 ]
    PHINode *val173 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %174 = trunc i64 %173 to i32
    Value *val174 = builder.CreateTrunc(val173, Type::getInt32Ty(context));
    //   %175 = and i32 %174, 16711680
    Value *val175 = builder.CreateAnd(val174, builder.getInt32(16711680), "");
    //   %176 = and i32 %1, 65280
    Value *val176 = builder.CreateAnd(val1, builder.getInt32(65280), "");
    //   %cond20 = icmp eq i32 %176, 0
    Value *valcond20 = builder.CreateICmpEQ(val176, builder.getInt32(0), "");
    //   br i1 %cond20, label %f32_from_ll.exit6, label %177
    builder.CreateCondBr(valcond20, valf32_from_ll_exit6, val177);
    builder.SetInsertPoint(val177);
    //   %178 = zext nneg i32 %176 to i64
    Value *val178 = builder.CreateZExt(val176, Type::getInt64Ty(context));
    //   %179 = shl nuw nsw i64 %178, 24
    Value *val179 = builder.CreateShl(val178, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i5
    builder.CreateBr(val_preheader_i5);
    builder.SetInsertPoint(val_preheader_i5);
    //   %180 = phi i32 [ %186, %.preheader.i5 ], [ 0, %177 ]
    PHINode *val180 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %181 = phi i64 [ %187, %.preheader.i5 ], [ %179, %177 ]
    PHINode *val181 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %182 = phi i32 [ %188, %.preheader.i5 ], [ -1, %177 ]
    PHINode *val182 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %183 = trunc i64 %181 to i8
    Value *val183 = builder.CreateTrunc(val181, Type::getInt8Ty(context));
    //   %184 = and i8 %183, 1
    Value *val184 = builder.CreateAnd(val183, builder.getInt8(1), "");
    //   %185 = zext nneg i8 %184 to i32
    Value *val185 = builder.CreateZExt(val184, Type::getInt32Ty(context));
    //   %186 = add i32 %180, %185
    Value *val186 = builder.CreateAdd(val180, val185, "", false, false);
    //   %187 = lshr i64 %181, 1
    Value *val187 = builder.CreateLShr(val181, builder.getInt64(1ll), "", false);
    //   %188 = add i32 %182, 1
    Value *val188 = builder.CreateAdd(val182, builder.getInt32(1), "", false, false);
    //   %189 = icmp ugt i64 %181, 33554431
    Value *val189 = builder.CreateICmpUGT(val181, builder.getInt64(33554431ll), "");
    //   %190 = icmp slt i32 %188, -126
    Value *val190 = builder.CreateICmpSLT(val188, builder.getInt32(-126), "");
    //   %191 = select i1 %189, i1 true, i1 %190
    Value *val191 = builder.CreateSelect(val189, builder.getInt1(true), val190);
    //   br i1 %191, label %.preheader.i5, label %192, !llvm.loop !4
    builder.CreateCondBr(val191, val_preheader_i5, val192);
    builder.SetInsertPoint(val192);
    //   %193 = icmp eq i8 %184, 0
    Value *val193 = builder.CreateICmpEQ(val184, builder.getInt8(0), "");
    //   br i1 %193, label %201, label %194
    builder.CreateCondBr(val193, val201, val194);
    builder.SetInsertPoint(val194);
    //   %195 = icmp sgt i32 %186, 1
    Value *val195 = builder.CreateICmpSGT(val186, builder.getInt32(1), "");
    //   %196 = and i64 %181, 2
    Value *val196 = builder.CreateAnd(val181, builder.getInt64(2ll), "");
    //   %197 = icmp ne i64 %196, 0
    Value *val197 = builder.CreateICmpNE(val196, builder.getInt64(0ll), "");
    //   %198 = or i1 %197, %195
    Value *val198 = builder.CreateOr(val197, val195, "");
    //   %199 = zext i1 %198 to i64
    Value *val199 = builder.CreateZExt(val198, Type::getInt64Ty(context));
    //   %200 = add nuw nsw i64 %187, %199
    Value *val200 = builder.CreateAdd(val187, val199, "", true, true);
    //   br label %201
    builder.CreateBr(val201);
    builder.SetInsertPoint(val201);
    //   %202 = phi i64 [ %187, %192 ], [ %200, %194 ]
    PHINode *val202 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %203 = icmp ugt i64 %202, 16777215
    Value *val203 = builder.CreateICmpUGT(val202, builder.getInt64(16777215ll), "");
    //   %204 = zext i1 %203 to i32
    Value *val204 = builder.CreateZExt(val203, Type::getInt32Ty(context));
    //   %205 = add i32 %188, %204
    Value *val205 = builder.CreateAdd(val188, val204, "", false, false);
    //   %206 = icmp sgt i32 %205, 127
    Value *val206 = builder.CreateICmpSGT(val205, builder.getInt32(127), "");
    //   br i1 %206, label %f32_from_ll.exit6, label %207
    builder.CreateCondBr(val206, valf32_from_ll_exit6, val207);
    builder.SetInsertPoint(val207);
    //   %208 = select i1 %203, i64 8388608, i64 %202
    Value *val208 = builder.CreateSelect(val203, builder.getInt64(8388608ll), val202);
    //   %209 = icmp ugt i64 %208, 8388607
    Value *val209 = builder.CreateICmpUGT(val208, builder.getInt64(8388607ll), "");
    //   %210 = trunc i64 %208 to i32
    Value *val210 = builder.CreateTrunc(val208, Type::getInt32Ty(context));
    //   br i1 %209, label %211, label %f32_from_ll.exit6
    builder.CreateCondBr(val209, val211, valf32_from_ll_exit6);
    builder.SetInsertPoint(val211);
    //   %212 = and i32 %210, 8388607
    Value *val212 = builder.CreateAnd(val210, builder.getInt32(8388607), "");
    //   %213 = shl i32 %205, 23
    Value *val213 = builder.CreateShl(val205, builder.getInt32(23), "", false, false);
    //   %214 = add i32 %213, 1065353216
    Value *val214 = builder.CreateAdd(val213, builder.getInt32(1065353216), "", false, false);
    //   %215 = and i32 %214, 2139095040
    Value *val215 = builder.CreateAnd(val214, builder.getInt32(2139095040), "");
    //   %216 = or disjoint i32 %215, %212
    Value *val216 = builder.CreateOr(val215, val212, "");
    //   br label %f32_from_ll.exit6
    builder.CreateBr(valf32_from_ll_exit6);
    builder.SetInsertPoint(valf32_from_ll_exit6);
    //   %217 = phi i32 [ 0, %f32_to_ll.exit ], [ %216, %211 ], [ 2139095040, %201 ], [ %210, %207 ]
    PHINode *val217 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %218 = and i32 %0, 65280
    Value *val218 = builder.CreateAnd(val0, builder.getInt32(65280), "");
    //   %cond21 = icmp eq i32 %218, 0
    Value *valcond21 = builder.CreateICmpEQ(val218, builder.getInt32(0), "");
    //   br i1 %cond21, label %f32_from_ll.exit8, label %219
    builder.CreateCondBr(valcond21, valf32_from_ll_exit8, val219);
    builder.SetInsertPoint(val219);
    //   %220 = zext nneg i32 %218 to i64
    Value *val220 = builder.CreateZExt(val218, Type::getInt64Ty(context));
    //   %221 = shl nuw nsw i64 %220, 24
    Value *val221 = builder.CreateShl(val220, builder.getInt64(24ll), "", true, true);
    //   br label %.preheader.i7
    builder.CreateBr(val_preheader_i7);
    builder.SetInsertPoint(val_preheader_i7);
    //   %222 = phi i32 [ %228, %.preheader.i7 ], [ 0, %219 ]
    PHINode *val222 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %223 = phi i64 [ %229, %.preheader.i7 ], [ %221, %219 ]
    PHINode *val223 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %224 = phi i32 [ %230, %.preheader.i7 ], [ -1, %219 ]
    PHINode *val224 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %225 = trunc i64 %223 to i8
    Value *val225 = builder.CreateTrunc(val223, Type::getInt8Ty(context));
    //   %226 = and i8 %225, 1
    Value *val226 = builder.CreateAnd(val225, builder.getInt8(1), "");
    //   %227 = zext nneg i8 %226 to i32
    Value *val227 = builder.CreateZExt(val226, Type::getInt32Ty(context));
    //   %228 = add i32 %222, %227
    Value *val228 = builder.CreateAdd(val222, val227, "", false, false);
    //   %229 = lshr i64 %223, 1
    Value *val229 = builder.CreateLShr(val223, builder.getInt64(1ll), "", false);
    //   %230 = add i32 %224, 1
    Value *val230 = builder.CreateAdd(val224, builder.getInt32(1), "", false, false);
    //   %231 = icmp ugt i64 %223, 33554431
    Value *val231 = builder.CreateICmpUGT(val223, builder.getInt64(33554431ll), "");
    //   %232 = icmp slt i32 %230, -126
    Value *val232 = builder.CreateICmpSLT(val230, builder.getInt32(-126), "");
    //   %233 = select i1 %231, i1 true, i1 %232
    Value *val233 = builder.CreateSelect(val231, builder.getInt1(true), val232);
    //   br i1 %233, label %.preheader.i7, label %234, !llvm.loop !4
    builder.CreateCondBr(val233, val_preheader_i7, val234);
    builder.SetInsertPoint(val234);
    //   %235 = icmp eq i8 %226, 0
    Value *val235 = builder.CreateICmpEQ(val226, builder.getInt8(0), "");
    //   br i1 %235, label %243, label %236
    builder.CreateCondBr(val235, val243, val236);
    builder.SetInsertPoint(val236);
    //   %237 = icmp sgt i32 %228, 1
    Value *val237 = builder.CreateICmpSGT(val228, builder.getInt32(1), "");
    //   %238 = and i64 %223, 2
    Value *val238 = builder.CreateAnd(val223, builder.getInt64(2ll), "");
    //   %239 = icmp ne i64 %238, 0
    Value *val239 = builder.CreateICmpNE(val238, builder.getInt64(0ll), "");
    //   %240 = or i1 %239, %237
    Value *val240 = builder.CreateOr(val239, val237, "");
    //   %241 = zext i1 %240 to i64
    Value *val241 = builder.CreateZExt(val240, Type::getInt64Ty(context));
    //   %242 = add nuw nsw i64 %229, %241
    Value *val242 = builder.CreateAdd(val229, val241, "", true, true);
    //   br label %243
    builder.CreateBr(val243);
    builder.SetInsertPoint(val243);
    //   %244 = phi i64 [ %229, %234 ], [ %242, %236 ]
    PHINode *val244 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %245 = icmp ugt i64 %244, 16777215
    Value *val245 = builder.CreateICmpUGT(val244, builder.getInt64(16777215ll), "");
    //   %246 = zext i1 %245 to i32
    Value *val246 = builder.CreateZExt(val245, Type::getInt32Ty(context));
    //   %247 = add i32 %230, %246
    Value *val247 = builder.CreateAdd(val230, val246, "", false, false);
    //   %248 = icmp sgt i32 %247, 127
    Value *val248 = builder.CreateICmpSGT(val247, builder.getInt32(127), "");
    //   br i1 %248, label %f32_from_ll.exit8, label %249
    builder.CreateCondBr(val248, valf32_from_ll_exit8, val249);
    builder.SetInsertPoint(val249);
    //   %250 = select i1 %245, i64 8388608, i64 %244
    Value *val250 = builder.CreateSelect(val245, builder.getInt64(8388608ll), val244);
    //   %251 = icmp ugt i64 %250, 8388607
    Value *val251 = builder.CreateICmpUGT(val250, builder.getInt64(8388607ll), "");
    //   %252 = trunc i64 %250 to i32
    Value *val252 = builder.CreateTrunc(val250, Type::getInt32Ty(context));
    //   br i1 %251, label %253, label %f32_from_ll.exit8
    builder.CreateCondBr(val251, val253, valf32_from_ll_exit8);
    builder.SetInsertPoint(val253);
    //   %254 = and i32 %252, 8388607
    Value *val254 = builder.CreateAnd(val252, builder.getInt32(8388607), "");
    //   %255 = shl i32 %247, 23
    Value *val255 = builder.CreateShl(val247, builder.getInt32(23), "", false, false);
    //   %256 = add i32 %255, 1065353216
    Value *val256 = builder.CreateAdd(val255, builder.getInt32(1065353216), "", false, false);
    //   %257 = and i32 %256, 2139095040
    Value *val257 = builder.CreateAnd(val256, builder.getInt32(2139095040), "");
    //   %258 = or disjoint i32 %257, %254
    Value *val258 = builder.CreateOr(val257, val254, "");
    //   br label %f32_from_ll.exit8
    builder.CreateBr(valf32_from_ll_exit8);
    builder.SetInsertPoint(valf32_from_ll_exit8);
    //   %259 = phi i32 [ 0, %f32_from_ll.exit6 ], [ %258, %253 ], [ 2139095040, %243 ], [ %252, %249 ]
    PHINode *val259 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %260 = tail call i32 @f32_mul(i32 noundef %217, i32 noundef %259) #9
    Value *val260 = builder.CreateCall(funcf32_mul, {val217, val259});
    //   %261 = tail call i32 @f32_mul(i32 noundef %260, i32 noundef %2) #9
    Value *val261 = builder.CreateCall(funcf32_mul, {val260, val2});
    //   br label %.preheader.i9
    builder.CreateBr(val_preheader_i9);
    builder.SetInsertPoint(val_preheader_i9);
    //   %262 = phi i32 [ %268, %.preheader.i9 ], [ 0, %f32_from_ll.exit8 ]
    PHINode *val262 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %263 = phi i64 [ %269, %.preheader.i9 ], [ 1095216660480, %f32_from_ll.exit8 ]
    PHINode *val263 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %264 = phi i32 [ %270, %.preheader.i9 ], [ -1, %f32_from_ll.exit8 ]
    PHINode *val264 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %265 = trunc i64 %263 to i8
    Value *val265 = builder.CreateTrunc(val263, Type::getInt8Ty(context));
    //   %266 = and i8 %265, 1
    Value *val266 = builder.CreateAnd(val265, builder.getInt8(1), "");
    //   %267 = zext nneg i8 %266 to i32
    Value *val267 = builder.CreateZExt(val266, Type::getInt32Ty(context));
    //   %268 = add i32 %262, %267
    Value *val268 = builder.CreateAdd(val262, val267, "", false, false);
    //   %269 = lshr i64 %263, 1
    Value *val269 = builder.CreateLShr(val263, builder.getInt64(1ll), "", false);
    //   %270 = add i32 %264, 1
    Value *val270 = builder.CreateAdd(val264, builder.getInt32(1), "", false, false);
    //   %271 = icmp ugt i64 %263, 33554431
    Value *val271 = builder.CreateICmpUGT(val263, builder.getInt64(33554431ll), "");
    //   %272 = icmp slt i32 %270, -126
    Value *val272 = builder.CreateICmpSLT(val270, builder.getInt32(-126), "");
    //   %273 = select i1 %271, i1 true, i1 %272
    Value *val273 = builder.CreateSelect(val271, builder.getInt1(true), val272);
    //   br i1 %273, label %.preheader.i9, label %274, !llvm.loop !4
    builder.CreateCondBr(val273, val_preheader_i9, val274);
    builder.SetInsertPoint(val274);
    //   %275 = icmp eq i8 %266, 0
    Value *val275 = builder.CreateICmpEQ(val266, builder.getInt8(0), "");
    //   br i1 %275, label %283, label %276
    builder.CreateCondBr(val275, val283, val276);
    builder.SetInsertPoint(val276);
    //   %277 = icmp sgt i32 %268, 1
    Value *val277 = builder.CreateICmpSGT(val268, builder.getInt32(1), "");
    //   %278 = and i64 %263, 2
    Value *val278 = builder.CreateAnd(val263, builder.getInt64(2ll), "");
    //   %279 = icmp ne i64 %278, 0
    Value *val279 = builder.CreateICmpNE(val278, builder.getInt64(0ll), "");
    //   %280 = or i1 %279, %277
    Value *val280 = builder.CreateOr(val279, val277, "");
    //   %281 = zext i1 %280 to i64
    Value *val281 = builder.CreateZExt(val280, Type::getInt64Ty(context));
    //   %282 = add nuw nsw i64 %269, %281
    Value *val282 = builder.CreateAdd(val269, val281, "", true, true);
    //   br label %283
    builder.CreateBr(val283);
    builder.SetInsertPoint(val283);
    //   %284 = phi i64 [ %269, %274 ], [ %282, %276 ]
    PHINode *val284 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %285 = icmp ugt i64 %284, 16777215
    Value *val285 = builder.CreateICmpUGT(val284, builder.getInt64(16777215ll), "");
    //   %286 = zext i1 %285 to i32
    Value *val286 = builder.CreateZExt(val285, Type::getInt32Ty(context));
    //   %287 = add i32 %270, %286
    Value *val287 = builder.CreateAdd(val270, val286, "", false, false);
    //   %288 = icmp sgt i32 %287, 127
    Value *val288 = builder.CreateICmpSGT(val287, builder.getInt32(127), "");
    //   br i1 %288, label %f32_from_ll.exit10, label %289
    builder.CreateCondBr(val288, valf32_from_ll_exit10, val289);
    builder.SetInsertPoint(val289);
    //   %290 = select i1 %285, i64 8388608, i64 %284
    Value *val290 = builder.CreateSelect(val285, builder.getInt64(8388608ll), val284);
    //   %291 = icmp ugt i64 %290, 8388607
    Value *val291 = builder.CreateICmpUGT(val290, builder.getInt64(8388607ll), "");
    //   %292 = trunc i64 %290 to i32
    Value *val292 = builder.CreateTrunc(val290, Type::getInt32Ty(context));
    //   br i1 %291, label %293, label %f32_from_ll.exit10
    builder.CreateCondBr(val291, val293, valf32_from_ll_exit10);
    builder.SetInsertPoint(val293);
    //   %294 = and i32 %292, 8388607
    Value *val294 = builder.CreateAnd(val292, builder.getInt32(8388607), "");
    //   %295 = shl i32 %287, 23
    Value *val295 = builder.CreateShl(val287, builder.getInt32(23), "", false, false);
    //   %296 = add i32 %295, 1065353216
    Value *val296 = builder.CreateAdd(val295, builder.getInt32(1065353216), "", false, false);
    //   %297 = and i32 %296, 2139095040
    Value *val297 = builder.CreateAnd(val296, builder.getInt32(2139095040), "");
    //   %298 = or disjoint i32 %297, %294
    Value *val298 = builder.CreateOr(val297, val294, "");
    //   br label %f32_from_ll.exit10
    builder.CreateBr(valf32_from_ll_exit10);
    builder.SetInsertPoint(valf32_from_ll_exit10);
    //   %299 = phi i32 [ %298, %293 ], [ 2139095040, %283 ], [ %292, %289 ]
    PHINode *val299 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %300 = tail call i32 @f32_div(i32 noundef %261, i32 noundef %299) #9
    Value *val300 = builder.CreateCall(funcf32_div, {val261, val299});
    //   %301 = and i32 %300, 2147483647
    Value *val301 = builder.CreateAnd(val300, builder.getInt32(2147483647), "");
    //   %302 = icmp eq i32 %301, 2139095040
    Value *val302 = builder.CreateICmpEQ(val301, builder.getInt32(2139095040), "");
    //   br i1 %302, label %f32_to_ll.exit11, label %303
    builder.CreateCondBr(val302, valf32_to_ll_exit11, val303);
    builder.SetInsertPoint(val303);
    //   %304 = and i32 %300, 2139095040
    Value *val304 = builder.CreateAnd(val300, builder.getInt32(2139095040), "");
    //   %305 = icmp eq i32 %304, 2139095040
    Value *val305 = builder.CreateICmpEQ(val304, builder.getInt32(2139095040), "");
    //   %306 = and i32 %300, 8388607
    Value *val306 = builder.CreateAnd(val300, builder.getInt32(8388607), "");
    //   %307 = icmp ne i32 %306, 0
    Value *val307 = builder.CreateICmpNE(val306, builder.getInt32(0), "");
    //   %308 = and i1 %305, %307
    Value *val308 = builder.CreateAnd(val305, val307, "");
    //   br i1 %308, label %f32_to_ll.exit11, label %309
    builder.CreateCondBr(val308, valf32_to_ll_exit11, val309);
    builder.SetInsertPoint(val309);
    //   %310 = icmp eq i32 %301, 0
    Value *val310 = builder.CreateICmpEQ(val301, builder.getInt32(0), "");
    //   br i1 %310, label %f32_to_ll.exit11, label %311
    builder.CreateCondBr(val310, valf32_to_ll_exit11, val311);
    builder.SetInsertPoint(val311);
    //   %312 = zext nneg i32 %306 to i64
    Value *val312 = builder.CreateZExt(val306, Type::getInt64Ty(context));
    //   %313 = icmp ne i32 %304, 0
    Value *val313 = builder.CreateICmpNE(val304, builder.getInt32(0), "");
    //   %314 = icmp eq i32 %306, 0
    Value *val314 = builder.CreateICmpEQ(val306, builder.getInt32(0), "");
    //   %315 = or i1 %313, %314
    Value *val315 = builder.CreateOr(val313, val314, "");
    //   %316 = or disjoint i64 %312, 8388608
    Value *val316 = builder.CreateOr(val312, builder.getInt64(8388608ll), "");
    //   %317 = select i1 %315, i64 %316, i64 %312
    Value *val317 = builder.CreateSelect(val315, val316, val312);
    //   %318 = icmp eq i32 %304, 0
    Value *val318 = builder.CreateICmpEQ(val304, builder.getInt32(0), "");
    //   %319 = and i1 %318, %307
    Value *val319 = builder.CreateAnd(val318, val307, "");
    //   %320 = lshr i32 %300, 23
    Value *val320 = builder.CreateLShr(val300, builder.getInt32(23), "", false);
    //   %321 = and i32 %320, 255
    Value *val321 = builder.CreateAnd(val320, builder.getInt32(255), "");
    //   %322 = add nsw i32 %321, -127
    Value *val322 = builder.CreateAdd(val321, builder.getInt32(-127), "", false, true);
    //   %323 = select i1 %319, i32 -126, i32 %322
    Value *val323 = builder.CreateSelect(val319, builder.getInt32(-126), val322);
    //   %324 = add nsw i32 %323, -23
    Value *val324 = builder.CreateAdd(val323, builder.getInt32(-23), "", false, true);
    //   %325 = icmp slt i32 %323, -40
    Value *val325 = builder.CreateICmpSLT(val323, builder.getInt32(-40), "");
    //   br i1 %325, label %f32_to_ll.exit11, label %326
    builder.CreateCondBr(val325, valf32_to_ll_exit11, val326);
    builder.SetInsertPoint(val326);
    //   %327 = icmp slt i32 %323, 24
    Value *val327 = builder.CreateICmpSLT(val323, builder.getInt32(24), "");
    //   br i1 %327, label %328, label %335
    builder.CreateCondBr(val327, val328, val335);
    builder.SetInsertPoint(val328);
    //   %329 = sub nsw i32 23, %323
    Value *val329 = builder.CreateSub(builder.getInt32(23), val323, "", false, true);
    //   %330 = zext nneg i32 %329 to i64
    Value *val330 = builder.CreateZExt(val329, Type::getInt64Ty(context));
    //   %331 = lshr i64 %317, %330
    Value *val331 = builder.CreateLShr(val317, val330, "", false);
    //   %332 = sub nsw i64 0, %331
    Value *val332 = builder.CreateSub(builder.getInt64(0ll), val331, "", false, true);
    //   %333 = icmp slt i32 %300, 0
    Value *val333 = builder.CreateICmpSLT(val300, builder.getInt32(0), "");
    //   %334 = select i1 %333, i64 %332, i64 %331
    Value *val334 = builder.CreateSelect(val333, val332, val331);
    //   br label %f32_to_ll.exit11
    builder.CreateBr(valf32_to_ll_exit11);
    builder.SetInsertPoint(val335);
    //   %336 = icmp ult i32 %323, 63
    Value *val336 = builder.CreateICmpULT(val323, builder.getInt32(63), "");
    //   br i1 %336, label %337, label %f32_to_ll.exit11
    builder.CreateCondBr(val336, val337, valf32_to_ll_exit11);
    builder.SetInsertPoint(val337);
    //   %338 = zext nneg i32 %324 to i64
    Value *val338 = builder.CreateZExt(val324, Type::getInt64Ty(context));
    //   %339 = shl nuw nsw i64 %317, %338
    Value *val339 = builder.CreateShl(val317, val338, "", true, true);
    //   %340 = sub nsw i64 0, %339
    Value *val340 = builder.CreateSub(builder.getInt64(0ll), val339, "", false, true);
    //   %341 = icmp slt i32 %300, 0
    Value *val341 = builder.CreateICmpSLT(val300, builder.getInt32(0), "");
    //   %342 = select i1 %341, i64 %340, i64 %339
    Value *val342 = builder.CreateSelect(val341, val340, val339);
    //   br label %f32_to_ll.exit11
    builder.CreateBr(valf32_to_ll_exit11);
    builder.SetInsertPoint(valf32_to_ll_exit11);
    //   %343 = phi i64 [ -9223372036854775808, %303 ], [ -9223372036854775808, %f32_from_ll.exit10 ], [ 0, %309 ], [ %334, %328 ], [ %342, %337 ], [ 0, %311 ], [ -9223372036854775808, %335 ]
    PHINode *val343 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %344 = trunc i64 %343 to i32
    Value *val344 = builder.CreateTrunc(val343, Type::getInt32Ty(context));
    //   %345 = and i32 %344, 65280
    Value *val345 = builder.CreateAnd(val344, builder.getInt32(65280), "");
    //   %346 = and i32 %1, 255
    Value *val346 = builder.CreateAnd(val1, builder.getInt32(255), "");
    //   %cond22 = icmp eq i32 %346, 0
    Value *valcond22 = builder.CreateICmpEQ(val346, builder.getInt32(0), "");
    //   br i1 %cond22, label %f32_from_ll.exit13, label %347
    builder.CreateCondBr(valcond22, valf32_from_ll_exit13, val347);
    builder.SetInsertPoint(val347);
    //   %348 = shl i32 %1, 24
    Value *val348 = builder.CreateShl(val1, builder.getInt32(24), "", false, false);
    //   %.not = icmp eq i32 %348, 0
    Value *val_not = builder.CreateICmpEQ(val348, builder.getInt32(0), "");
    //   br i1 %.not, label %371, label %.preheader.i12.preheader
    builder.CreateCondBr(val_not, val371, val_preheader_i12_preheader);
    builder.SetInsertPoint(val_preheader_i12_preheader);
    //   %349 = zext i32 %348 to i64
    Value *val349 = builder.CreateZExt(val348, Type::getInt64Ty(context));
    //   br label %.preheader.i12
    builder.CreateBr(val_preheader_i12);
    builder.SetInsertPoint(val_preheader_i12);
    //   %350 = phi i32 [ %356, %.preheader.i12 ], [ 0, %.preheader.i12.preheader ]
    PHINode *val350 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %351 = phi i64 [ %357, %.preheader.i12 ], [ %349, %.preheader.i12.preheader ]
    PHINode *val351 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %352 = phi i32 [ %358, %.preheader.i12 ], [ -1, %.preheader.i12.preheader ]
    PHINode *val352 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %353 = trunc i64 %351 to i8
    Value *val353 = builder.CreateTrunc(val351, Type::getInt8Ty(context));
    //   %354 = and i8 %353, 1
    Value *val354 = builder.CreateAnd(val353, builder.getInt8(1), "");
    //   %355 = zext nneg i8 %354 to i32
    Value *val355 = builder.CreateZExt(val354, Type::getInt32Ty(context));
    //   %356 = add i32 %350, %355
    Value *val356 = builder.CreateAdd(val350, val355, "", false, false);
    //   %357 = lshr i64 %351, 1
    Value *val357 = builder.CreateLShr(val351, builder.getInt64(1ll), "", false);
    //   %358 = add i32 %352, 1
    Value *val358 = builder.CreateAdd(val352, builder.getInt32(1), "", false, false);
    //   %359 = icmp ugt i64 %351, 33554431
    Value *val359 = builder.CreateICmpUGT(val351, builder.getInt64(33554431ll), "");
    //   %360 = icmp slt i32 %358, -126
    Value *val360 = builder.CreateICmpSLT(val358, builder.getInt32(-126), "");
    //   %361 = select i1 %359, i1 true, i1 %360
    Value *val361 = builder.CreateSelect(val359, builder.getInt1(true), val360);
    //   br i1 %361, label %.preheader.i12, label %362, !llvm.loop !4
    builder.CreateCondBr(val361, val_preheader_i12, val362);
    builder.SetInsertPoint(val362);
    //   %363 = icmp eq i8 %354, 0
    Value *val363 = builder.CreateICmpEQ(val354, builder.getInt8(0), "");
    //   br i1 %363, label %371, label %364
    builder.CreateCondBr(val363, val371, val364);
    builder.SetInsertPoint(val364);
    //   %365 = icmp sgt i32 %356, 1
    Value *val365 = builder.CreateICmpSGT(val356, builder.getInt32(1), "");
    //   %366 = and i64 %351, 2
    Value *val366 = builder.CreateAnd(val351, builder.getInt64(2ll), "");
    //   %367 = icmp ne i64 %366, 0
    Value *val367 = builder.CreateICmpNE(val366, builder.getInt64(0ll), "");
    //   %368 = or i1 %367, %365
    Value *val368 = builder.CreateOr(val367, val365, "");
    //   %369 = zext i1 %368 to i64
    Value *val369 = builder.CreateZExt(val368, Type::getInt64Ty(context));
    //   %370 = add nuw nsw i64 %357, %369
    Value *val370 = builder.CreateAdd(val357, val369, "", true, true);
    //   br label %371
    builder.CreateBr(val371);
    builder.SetInsertPoint(val371);
    //   %372 = phi i32 [ %358, %362 ], [ %358, %364 ], [ -1, %347 ]
    PHINode *val372 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %373 = phi i64 [ %357, %362 ], [ %370, %364 ], [ 0, %347 ]
    PHINode *val373 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %374 = icmp ugt i64 %373, 16777215
    Value *val374 = builder.CreateICmpUGT(val373, builder.getInt64(16777215ll), "");
    //   %375 = zext i1 %374 to i32
    Value *val375 = builder.CreateZExt(val374, Type::getInt32Ty(context));
    //   %376 = add i32 %372, %375
    Value *val376 = builder.CreateAdd(val372, val375, "", false, false);
    //   %377 = icmp sgt i32 %376, 127
    Value *val377 = builder.CreateICmpSGT(val376, builder.getInt32(127), "");
    //   br i1 %377, label %f32_from_ll.exit13, label %378
    builder.CreateCondBr(val377, valf32_from_ll_exit13, val378);
    builder.SetInsertPoint(val378);
    //   %379 = select i1 %374, i64 8388608, i64 %373
    Value *val379 = builder.CreateSelect(val374, builder.getInt64(8388608ll), val373);
    //   %380 = icmp ugt i64 %379, 8388607
    Value *val380 = builder.CreateICmpUGT(val379, builder.getInt64(8388607ll), "");
    //   %381 = trunc i64 %379 to i32
    Value *val381 = builder.CreateTrunc(val379, Type::getInt32Ty(context));
    //   br i1 %380, label %382, label %f32_from_ll.exit13
    builder.CreateCondBr(val380, val382, valf32_from_ll_exit13);
    builder.SetInsertPoint(val382);
    //   %383 = and i32 %381, 8388607
    Value *val383 = builder.CreateAnd(val381, builder.getInt32(8388607), "");
    //   %384 = shl i32 %376, 23
    Value *val384 = builder.CreateShl(val376, builder.getInt32(23), "", false, false);
    //   %385 = add i32 %384, 1065353216
    Value *val385 = builder.CreateAdd(val384, builder.getInt32(1065353216), "", false, false);
    //   %386 = and i32 %385, 2139095040
    Value *val386 = builder.CreateAnd(val385, builder.getInt32(2139095040), "");
    //   %387 = or disjoint i32 %386, %383
    Value *val387 = builder.CreateOr(val386, val383, "");
    //   br label %f32_from_ll.exit13
    builder.CreateBr(valf32_from_ll_exit13);
    builder.SetInsertPoint(valf32_from_ll_exit13);
    //   %388 = phi i32 [ 0, %f32_to_ll.exit11 ], [ %387, %382 ], [ 2139095040, %371 ], [ %381, %378 ]
    PHINode *val388 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %389 = and i32 %0, 255
    Value *val389 = builder.CreateAnd(val0, builder.getInt32(255), "");
    //   %cond23 = icmp eq i32 %389, 0
    Value *valcond23 = builder.CreateICmpEQ(val389, builder.getInt32(0), "");
    //   br i1 %cond23, label %f32_from_ll.exit15, label %390
    builder.CreateCondBr(valcond23, valf32_from_ll_exit15, val390);
    builder.SetInsertPoint(val390);
    //   %391 = shl i32 %0, 24
    Value *val391 = builder.CreateShl(val0, builder.getInt32(24), "", false, false);
    //   %.not24 = icmp eq i32 %391, 0
    Value *val_not24 = builder.CreateICmpEQ(val391, builder.getInt32(0), "");
    //   br i1 %.not24, label %414, label %.preheader.i14.preheader
    builder.CreateCondBr(val_not24, val414, val_preheader_i14_preheader);
    builder.SetInsertPoint(val_preheader_i14_preheader);
    //   %392 = zext i32 %391 to i64
    Value *val392 = builder.CreateZExt(val391, Type::getInt64Ty(context));
    //   br label %.preheader.i14
    builder.CreateBr(val_preheader_i14);
    builder.SetInsertPoint(val_preheader_i14);
    //   %393 = phi i32 [ %399, %.preheader.i14 ], [ 0, %.preheader.i14.preheader ]
    PHINode *val393 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %394 = phi i64 [ %400, %.preheader.i14 ], [ %392, %.preheader.i14.preheader ]
    PHINode *val394 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %395 = phi i32 [ %401, %.preheader.i14 ], [ -1, %.preheader.i14.preheader ]
    PHINode *val395 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %396 = trunc i64 %394 to i8
    Value *val396 = builder.CreateTrunc(val394, Type::getInt8Ty(context));
    //   %397 = and i8 %396, 1
    Value *val397 = builder.CreateAnd(val396, builder.getInt8(1), "");
    //   %398 = zext nneg i8 %397 to i32
    Value *val398 = builder.CreateZExt(val397, Type::getInt32Ty(context));
    //   %399 = add i32 %393, %398
    Value *val399 = builder.CreateAdd(val393, val398, "", false, false);
    //   %400 = lshr i64 %394, 1
    Value *val400 = builder.CreateLShr(val394, builder.getInt64(1ll), "", false);
    //   %401 = add i32 %395, 1
    Value *val401 = builder.CreateAdd(val395, builder.getInt32(1), "", false, false);
    //   %402 = icmp ugt i64 %394, 33554431
    Value *val402 = builder.CreateICmpUGT(val394, builder.getInt64(33554431ll), "");
    //   %403 = icmp slt i32 %401, -126
    Value *val403 = builder.CreateICmpSLT(val401, builder.getInt32(-126), "");
    //   %404 = select i1 %402, i1 true, i1 %403
    Value *val404 = builder.CreateSelect(val402, builder.getInt1(true), val403);
    //   br i1 %404, label %.preheader.i14, label %405, !llvm.loop !4
    builder.CreateCondBr(val404, val_preheader_i14, val405);
    builder.SetInsertPoint(val405);
    //   %406 = icmp eq i8 %397, 0
    Value *val406 = builder.CreateICmpEQ(val397, builder.getInt8(0), "");
    //   br i1 %406, label %414, label %407
    builder.CreateCondBr(val406, val414, val407);
    builder.SetInsertPoint(val407);
    //   %408 = icmp sgt i32 %399, 1
    Value *val408 = builder.CreateICmpSGT(val399, builder.getInt32(1), "");
    //   %409 = and i64 %394, 2
    Value *val409 = builder.CreateAnd(val394, builder.getInt64(2ll), "");
    //   %410 = icmp ne i64 %409, 0
    Value *val410 = builder.CreateICmpNE(val409, builder.getInt64(0ll), "");
    //   %411 = or i1 %410, %408
    Value *val411 = builder.CreateOr(val410, val408, "");
    //   %412 = zext i1 %411 to i64
    Value *val412 = builder.CreateZExt(val411, Type::getInt64Ty(context));
    //   %413 = add nuw nsw i64 %400, %412
    Value *val413 = builder.CreateAdd(val400, val412, "", true, true);
    //   br label %414
    builder.CreateBr(val414);
    builder.SetInsertPoint(val414);
    //   %415 = phi i32 [ %401, %405 ], [ %401, %407 ], [ -1, %390 ]
    PHINode *val415 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %416 = phi i64 [ %400, %405 ], [ %413, %407 ], [ 0, %390 ]
    PHINode *val416 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %417 = icmp ugt i64 %416, 16777215
    Value *val417 = builder.CreateICmpUGT(val416, builder.getInt64(16777215ll), "");
    //   %418 = zext i1 %417 to i32
    Value *val418 = builder.CreateZExt(val417, Type::getInt32Ty(context));
    //   %419 = add i32 %415, %418
    Value *val419 = builder.CreateAdd(val415, val418, "", false, false);
    //   %420 = icmp sgt i32 %419, 127
    Value *val420 = builder.CreateICmpSGT(val419, builder.getInt32(127), "");
    //   br i1 %420, label %f32_from_ll.exit15, label %421
    builder.CreateCondBr(val420, valf32_from_ll_exit15, val421);
    builder.SetInsertPoint(val421);
    //   %422 = select i1 %417, i64 8388608, i64 %416
    Value *val422 = builder.CreateSelect(val417, builder.getInt64(8388608ll), val416);
    //   %423 = icmp ugt i64 %422, 8388607
    Value *val423 = builder.CreateICmpUGT(val422, builder.getInt64(8388607ll), "");
    //   %424 = trunc i64 %422 to i32
    Value *val424 = builder.CreateTrunc(val422, Type::getInt32Ty(context));
    //   br i1 %423, label %425, label %f32_from_ll.exit15
    builder.CreateCondBr(val423, val425, valf32_from_ll_exit15);
    builder.SetInsertPoint(val425);
    //   %426 = and i32 %424, 8388607
    Value *val426 = builder.CreateAnd(val424, builder.getInt32(8388607), "");
    //   %427 = shl i32 %419, 23
    Value *val427 = builder.CreateShl(val419, builder.getInt32(23), "", false, false);
    //   %428 = add i32 %427, 1065353216
    Value *val428 = builder.CreateAdd(val427, builder.getInt32(1065353216), "", false, false);
    //   %429 = and i32 %428, 2139095040
    Value *val429 = builder.CreateAnd(val428, builder.getInt32(2139095040), "");
    //   %430 = or disjoint i32 %429, %426
    Value *val430 = builder.CreateOr(val429, val426, "");
    //   br label %f32_from_ll.exit15
    builder.CreateBr(valf32_from_ll_exit15);
    builder.SetInsertPoint(valf32_from_ll_exit15);
    //   %431 = phi i32 [ 0, %f32_from_ll.exit13 ], [ %430, %425 ], [ 2139095040, %414 ], [ %424, %421 ]
    PHINode *val431 = builder.CreatePHI(Type::getInt32Ty(context), 4);
    //   %432 = tail call i32 @f32_mul(i32 noundef %388, i32 noundef %431) #9
    Value *val432 = builder.CreateCall(funcf32_mul, {val388, val431});
    //   %433 = tail call i32 @f32_mul(i32 noundef %432, i32 noundef %2) #9
    Value *val433 = builder.CreateCall(funcf32_mul, {val432, val2});
    //   br label %.preheader.i16
    builder.CreateBr(val_preheader_i16);
    builder.SetInsertPoint(val_preheader_i16);
    //   %434 = phi i32 [ %440, %.preheader.i16 ], [ 0, %f32_from_ll.exit15 ]
    PHINode *val434 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %435 = phi i64 [ %441, %.preheader.i16 ], [ 4278190080, %f32_from_ll.exit15 ]
    PHINode *val435 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %436 = phi i32 [ %442, %.preheader.i16 ], [ -1, %f32_from_ll.exit15 ]
    PHINode *val436 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %437 = trunc i64 %435 to i8
    Value *val437 = builder.CreateTrunc(val435, Type::getInt8Ty(context));
    //   %438 = and i8 %437, 1
    Value *val438 = builder.CreateAnd(val437, builder.getInt8(1), "");
    //   %439 = zext nneg i8 %438 to i32
    Value *val439 = builder.CreateZExt(val438, Type::getInt32Ty(context));
    //   %440 = add i32 %434, %439
    Value *val440 = builder.CreateAdd(val434, val439, "", false, false);
    //   %441 = lshr i64 %435, 1
    Value *val441 = builder.CreateLShr(val435, builder.getInt64(1ll), "", false);
    //   %442 = add i32 %436, 1
    Value *val442 = builder.CreateAdd(val436, builder.getInt32(1), "", false, false);
    //   %443 = icmp ugt i64 %435, 33554431
    Value *val443 = builder.CreateICmpUGT(val435, builder.getInt64(33554431ll), "");
    //   %444 = icmp slt i32 %442, -126
    Value *val444 = builder.CreateICmpSLT(val442, builder.getInt32(-126), "");
    //   %445 = select i1 %443, i1 true, i1 %444
    Value *val445 = builder.CreateSelect(val443, builder.getInt1(true), val444);
    //   br i1 %445, label %.preheader.i16, label %446, !llvm.loop !4
    builder.CreateCondBr(val445, val_preheader_i16, val446);
    builder.SetInsertPoint(val446);
    //   %447 = icmp eq i8 %438, 0
    Value *val447 = builder.CreateICmpEQ(val438, builder.getInt8(0), "");
    //   br i1 %447, label %455, label %448
    builder.CreateCondBr(val447, val455, val448);
    builder.SetInsertPoint(val448);
    //   %449 = icmp sgt i32 %440, 1
    Value *val449 = builder.CreateICmpSGT(val440, builder.getInt32(1), "");
    //   %450 = and i64 %435, 2
    Value *val450 = builder.CreateAnd(val435, builder.getInt64(2ll), "");
    //   %451 = icmp ne i64 %450, 0
    Value *val451 = builder.CreateICmpNE(val450, builder.getInt64(0ll), "");
    //   %452 = or i1 %451, %449
    Value *val452 = builder.CreateOr(val451, val449, "");
    //   %453 = zext i1 %452 to i64
    Value *val453 = builder.CreateZExt(val452, Type::getInt64Ty(context));
    //   %454 = add nuw nsw i64 %441, %453
    Value *val454 = builder.CreateAdd(val441, val453, "", true, true);
    //   br label %455
    builder.CreateBr(val455);
    builder.SetInsertPoint(val455);
    //   %456 = phi i64 [ %441, %446 ], [ %454, %448 ]
    PHINode *val456 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %457 = icmp ugt i64 %456, 16777215
    Value *val457 = builder.CreateICmpUGT(val456, builder.getInt64(16777215ll), "");
    //   %458 = zext i1 %457 to i32
    Value *val458 = builder.CreateZExt(val457, Type::getInt32Ty(context));
    //   %459 = add i32 %442, %458
    Value *val459 = builder.CreateAdd(val442, val458, "", false, false);
    //   %460 = icmp sgt i32 %459, 127
    Value *val460 = builder.CreateICmpSGT(val459, builder.getInt32(127), "");
    //   br i1 %460, label %f32_from_ll.exit17, label %461
    builder.CreateCondBr(val460, valf32_from_ll_exit17, val461);
    builder.SetInsertPoint(val461);
    //   %462 = select i1 %457, i64 8388608, i64 %456
    Value *val462 = builder.CreateSelect(val457, builder.getInt64(8388608ll), val456);
    //   %463 = icmp ugt i64 %462, 8388607
    Value *val463 = builder.CreateICmpUGT(val462, builder.getInt64(8388607ll), "");
    //   %464 = trunc i64 %462 to i32
    Value *val464 = builder.CreateTrunc(val462, Type::getInt32Ty(context));
    //   br i1 %463, label %465, label %f32_from_ll.exit17
    builder.CreateCondBr(val463, val465, valf32_from_ll_exit17);
    builder.SetInsertPoint(val465);
    //   %466 = and i32 %464, 8388607
    Value *val466 = builder.CreateAnd(val464, builder.getInt32(8388607), "");
    //   %467 = shl i32 %459, 23
    Value *val467 = builder.CreateShl(val459, builder.getInt32(23), "", false, false);
    //   %468 = add i32 %467, 1065353216
    Value *val468 = builder.CreateAdd(val467, builder.getInt32(1065353216), "", false, false);
    //   %469 = and i32 %468, 2139095040
    Value *val469 = builder.CreateAnd(val468, builder.getInt32(2139095040), "");
    //   %470 = or disjoint i32 %469, %466
    Value *val470 = builder.CreateOr(val469, val466, "");
    //   br label %f32_from_ll.exit17
    builder.CreateBr(valf32_from_ll_exit17);
    builder.SetInsertPoint(valf32_from_ll_exit17);
    //   %471 = phi i32 [ %470, %465 ], [ 2139095040, %455 ], [ %464, %461 ]
    PHINode *val471 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %472 = tail call i32 @f32_div(i32 noundef %433, i32 noundef %471) #9
    Value *val472 = builder.CreateCall(funcf32_div, {val433, val471});
    //   %473 = and i32 %472, 2147483647
    Value *val473 = builder.CreateAnd(val472, builder.getInt32(2147483647), "");
    //   %474 = icmp eq i32 %473, 2139095040
    Value *val474 = builder.CreateICmpEQ(val473, builder.getInt32(2139095040), "");
    //   br i1 %474, label %f32_to_ll.exit18, label %475
    builder.CreateCondBr(val474, valf32_to_ll_exit18, val475);
    builder.SetInsertPoint(val475);
    //   %476 = and i32 %472, 2139095040
    Value *val476 = builder.CreateAnd(val472, builder.getInt32(2139095040), "");
    //   %477 = icmp eq i32 %476, 2139095040
    Value *val477 = builder.CreateICmpEQ(val476, builder.getInt32(2139095040), "");
    //   %478 = and i32 %472, 8388607
    Value *val478 = builder.CreateAnd(val472, builder.getInt32(8388607), "");
    //   %479 = icmp ne i32 %478, 0
    Value *val479 = builder.CreateICmpNE(val478, builder.getInt32(0), "");
    //   %480 = and i1 %477, %479
    Value *val480 = builder.CreateAnd(val477, val479, "");
    //   br i1 %480, label %f32_to_ll.exit18, label %481
    builder.CreateCondBr(val480, valf32_to_ll_exit18, val481);
    builder.SetInsertPoint(val481);
    //   %482 = icmp eq i32 %473, 0
    Value *val482 = builder.CreateICmpEQ(val473, builder.getInt32(0), "");
    //   br i1 %482, label %f32_to_ll.exit18, label %483
    builder.CreateCondBr(val482, valf32_to_ll_exit18, val483);
    builder.SetInsertPoint(val483);
    //   %484 = zext nneg i32 %478 to i64
    Value *val484 = builder.CreateZExt(val478, Type::getInt64Ty(context));
    //   %485 = icmp ne i32 %476, 0
    Value *val485 = builder.CreateICmpNE(val476, builder.getInt32(0), "");
    //   %486 = icmp eq i32 %478, 0
    Value *val486 = builder.CreateICmpEQ(val478, builder.getInt32(0), "");
    //   %487 = or i1 %485, %486
    Value *val487 = builder.CreateOr(val485, val486, "");
    //   %488 = or disjoint i64 %484, 8388608
    Value *val488 = builder.CreateOr(val484, builder.getInt64(8388608ll), "");
    //   %489 = select i1 %487, i64 %488, i64 %484
    Value *val489 = builder.CreateSelect(val487, val488, val484);
    //   %490 = icmp eq i32 %476, 0
    Value *val490 = builder.CreateICmpEQ(val476, builder.getInt32(0), "");
    //   %491 = and i1 %490, %479
    Value *val491 = builder.CreateAnd(val490, val479, "");
    //   %492 = lshr i32 %472, 23
    Value *val492 = builder.CreateLShr(val472, builder.getInt32(23), "", false);
    //   %493 = and i32 %492, 255
    Value *val493 = builder.CreateAnd(val492, builder.getInt32(255), "");
    //   %494 = add nsw i32 %493, -127
    Value *val494 = builder.CreateAdd(val493, builder.getInt32(-127), "", false, true);
    //   %495 = select i1 %491, i32 -126, i32 %494
    Value *val495 = builder.CreateSelect(val491, builder.getInt32(-126), val494);
    //   %496 = add nsw i32 %495, -23
    Value *val496 = builder.CreateAdd(val495, builder.getInt32(-23), "", false, true);
    //   %497 = icmp slt i32 %495, -40
    Value *val497 = builder.CreateICmpSLT(val495, builder.getInt32(-40), "");
    //   br i1 %497, label %f32_to_ll.exit18, label %498
    builder.CreateCondBr(val497, valf32_to_ll_exit18, val498);
    builder.SetInsertPoint(val498);
    //   %499 = icmp slt i32 %495, 24
    Value *val499 = builder.CreateICmpSLT(val495, builder.getInt32(24), "");
    //   br i1 %499, label %500, label %507
    builder.CreateCondBr(val499, val500, val507);
    builder.SetInsertPoint(val500);
    //   %501 = sub nsw i32 23, %495
    Value *val501 = builder.CreateSub(builder.getInt32(23), val495, "", false, true);
    //   %502 = zext nneg i32 %501 to i64
    Value *val502 = builder.CreateZExt(val501, Type::getInt64Ty(context));
    //   %503 = lshr i64 %489, %502
    Value *val503 = builder.CreateLShr(val489, val502, "", false);
    //   %504 = sub nsw i64 0, %503
    Value *val504 = builder.CreateSub(builder.getInt64(0ll), val503, "", false, true);
    //   %505 = icmp slt i32 %472, 0
    Value *val505 = builder.CreateICmpSLT(val472, builder.getInt32(0), "");
    //   %506 = select i1 %505, i64 %504, i64 %503
    Value *val506 = builder.CreateSelect(val505, val504, val503);
    //   br label %f32_to_ll.exit18
    builder.CreateBr(valf32_to_ll_exit18);
    builder.SetInsertPoint(val507);
    //   %508 = icmp ult i32 %495, 63
    Value *val508 = builder.CreateICmpULT(val495, builder.getInt32(63), "");
    //   br i1 %508, label %509, label %f32_to_ll.exit18
    builder.CreateCondBr(val508, val509, valf32_to_ll_exit18);
    builder.SetInsertPoint(val509);
    //   %510 = zext nneg i32 %496 to i64
    Value *val510 = builder.CreateZExt(val496, Type::getInt64Ty(context));
    //   %511 = shl nuw nsw i64 %489, %510
    Value *val511 = builder.CreateShl(val489, val510, "", true, true);
    //   %512 = sub nsw i64 0, %511
    Value *val512 = builder.CreateSub(builder.getInt64(0ll), val511, "", false, true);
    //   %513 = icmp slt i32 %472, 0
    Value *val513 = builder.CreateICmpSLT(val472, builder.getInt32(0), "");
    //   %514 = select i1 %513, i64 %512, i64 %511
    Value *val514 = builder.CreateSelect(val513, val512, val511);
    //   br label %f32_to_ll.exit18
    builder.CreateBr(valf32_to_ll_exit18);
    builder.SetInsertPoint(valf32_to_ll_exit18);
    //   %515 = phi i64 [ -9223372036854775808, %475 ], [ -9223372036854775808, %f32_from_ll.exit17 ], [ 0, %481 ], [ %506, %500 ], [ %514, %509 ], [ 0, %483 ], [ -9223372036854775808, %507 ]
    PHINode *val515 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   %516 = trunc i64 %515 to i32
    Value *val516 = builder.CreateTrunc(val515, Type::getInt32Ty(context));
    //   %517 = and i32 %516, 255
    Value *val517 = builder.CreateAnd(val516, builder.getInt32(255), "");
    //   %518 = or disjoint i32 %345, %175
    Value *val518 = builder.CreateOr(val345, val175, "");
    //   %519 = or disjoint i32 %518, %517
    Value *val519 = builder.CreateOr(val518, val517, "");
    //   %520 = tail call i32 @combine(i32 noundef %0, i32 noundef %519, i32 noundef %2), !range !6
    Value *val520 = builder.CreateCall(funccombine, {val0, val519, val2});
    //   br label %521
    builder.CreateBr(val521);
    builder.SetInsertPoint(val521);
    //   %522 = phi i32 [ %520, %f32_to_ll.exit18 ], [ %0, %3 ]
    PHINode *val522 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   ret i32 %522
    builder.CreateRet(val522);
    val10->addIncoming(val16, val_preheader_i);
    val10->addIncoming(builder.getInt32(0), val7);
    val11->addIncoming(val17, val_preheader_i);
    val11->addIncoming(val9, val7);
    val12->addIncoming(val18, val_preheader_i);
    val12->addIncoming(builder.getInt32(-1), val7);
    val32->addIncoming(val17, val22);
    val32->addIncoming(val30, val24);
    val47->addIncoming(builder.getInt32(0), val5);
    val47->addIncoming(val46, val41);
    val47->addIncoming(builder.getInt32(2139095040), val31);
    val47->addIncoming(val40, val37);
    val52->addIncoming(val58, val_preheader_i1);
    val52->addIncoming(builder.getInt32(0), val49);
    val53->addIncoming(val59, val_preheader_i1);
    val53->addIncoming(val51, val49);
    val54->addIncoming(val60, val_preheader_i1);
    val54->addIncoming(builder.getInt32(-1), val49);
    val74->addIncoming(val59, val64);
    val74->addIncoming(val72, val66);
    val89->addIncoming(builder.getInt32(0), valf32_from_ll_exit);
    val89->addIncoming(val88, val83);
    val89->addIncoming(builder.getInt32(2139095040), val73);
    val89->addIncoming(val82, val79);
    val92->addIncoming(val98, val_preheader_i3);
    val92->addIncoming(builder.getInt32(0), valf32_from_ll_exit2);
    val93->addIncoming(val99, val_preheader_i3);
    val93->addIncoming(builder.getInt64(280375465082880ll), valf32_from_ll_exit2);
    val94->addIncoming(val100, val_preheader_i3);
    val94->addIncoming(builder.getInt32(-1), valf32_from_ll_exit2);
    val114->addIncoming(val99, val104);
    val114->addIncoming(val112, val106);
    val129->addIncoming(val128, val123);
    val129->addIncoming(builder.getInt32(2139095040), val113);
    val129->addIncoming(val122, val119);
    val173->addIncoming(builder.getInt64(-9223372036854775808ll), val133);
    val173->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit4);
    val173->addIncoming(builder.getInt64(0ll), val139);
    val173->addIncoming(val164, val158);
    val173->addIncoming(val172, val167);
    val173->addIncoming(builder.getInt64(0ll), val141);
    val173->addIncoming(builder.getInt64(-9223372036854775808ll), val165);
    val180->addIncoming(val186, val_preheader_i5);
    val180->addIncoming(builder.getInt32(0), val177);
    val181->addIncoming(val187, val_preheader_i5);
    val181->addIncoming(val179, val177);
    val182->addIncoming(val188, val_preheader_i5);
    val182->addIncoming(builder.getInt32(-1), val177);
    val202->addIncoming(val187, val192);
    val202->addIncoming(val200, val194);
    val217->addIncoming(builder.getInt32(0), valf32_to_ll_exit);
    val217->addIncoming(val216, val211);
    val217->addIncoming(builder.getInt32(2139095040), val201);
    val217->addIncoming(val210, val207);
    val222->addIncoming(val228, val_preheader_i7);
    val222->addIncoming(builder.getInt32(0), val219);
    val223->addIncoming(val229, val_preheader_i7);
    val223->addIncoming(val221, val219);
    val224->addIncoming(val230, val_preheader_i7);
    val224->addIncoming(builder.getInt32(-1), val219);
    val244->addIncoming(val229, val234);
    val244->addIncoming(val242, val236);
    val259->addIncoming(builder.getInt32(0), valf32_from_ll_exit6);
    val259->addIncoming(val258, val253);
    val259->addIncoming(builder.getInt32(2139095040), val243);
    val259->addIncoming(val252, val249);
    val262->addIncoming(val268, val_preheader_i9);
    val262->addIncoming(builder.getInt32(0), valf32_from_ll_exit8);
    val263->addIncoming(val269, val_preheader_i9);
    val263->addIncoming(builder.getInt64(1095216660480ll), valf32_from_ll_exit8);
    val264->addIncoming(val270, val_preheader_i9);
    val264->addIncoming(builder.getInt32(-1), valf32_from_ll_exit8);
    val284->addIncoming(val269, val274);
    val284->addIncoming(val282, val276);
    val299->addIncoming(val298, val293);
    val299->addIncoming(builder.getInt32(2139095040), val283);
    val299->addIncoming(val292, val289);
    val343->addIncoming(builder.getInt64(-9223372036854775808ll), val303);
    val343->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit10);
    val343->addIncoming(builder.getInt64(0ll), val309);
    val343->addIncoming(val334, val328);
    val343->addIncoming(val342, val337);
    val343->addIncoming(builder.getInt64(0ll), val311);
    val343->addIncoming(builder.getInt64(-9223372036854775808ll), val335);
    val350->addIncoming(val356, val_preheader_i12);
    val350->addIncoming(builder.getInt32(0), val_preheader_i12_preheader);
    val351->addIncoming(val357, val_preheader_i12);
    val351->addIncoming(val349, val_preheader_i12_preheader);
    val352->addIncoming(val358, val_preheader_i12);
    val352->addIncoming(builder.getInt32(-1), val_preheader_i12_preheader);
    val372->addIncoming(val358, val362);
    val372->addIncoming(val358, val364);
    val372->addIncoming(builder.getInt32(-1), val347);
    val373->addIncoming(val357, val362);
    val373->addIncoming(val370, val364);
    val373->addIncoming(builder.getInt64(0ll), val347);
    val388->addIncoming(builder.getInt32(0), valf32_to_ll_exit11);
    val388->addIncoming(val387, val382);
    val388->addIncoming(builder.getInt32(2139095040), val371);
    val388->addIncoming(val381, val378);
    val393->addIncoming(val399, val_preheader_i14);
    val393->addIncoming(builder.getInt32(0), val_preheader_i14_preheader);
    val394->addIncoming(val400, val_preheader_i14);
    val394->addIncoming(val392, val_preheader_i14_preheader);
    val395->addIncoming(val401, val_preheader_i14);
    val395->addIncoming(builder.getInt32(-1), val_preheader_i14_preheader);
    val415->addIncoming(val401, val405);
    val415->addIncoming(val401, val407);
    val415->addIncoming(builder.getInt32(-1), val390);
    val416->addIncoming(val400, val405);
    val416->addIncoming(val413, val407);
    val416->addIncoming(builder.getInt64(0ll), val390);
    val431->addIncoming(builder.getInt32(0), valf32_from_ll_exit13);
    val431->addIncoming(val430, val425);
    val431->addIncoming(builder.getInt32(2139095040), val414);
    val431->addIncoming(val424, val421);
    val434->addIncoming(val440, val_preheader_i16);
    val434->addIncoming(builder.getInt32(0), valf32_from_ll_exit15);
    val435->addIncoming(val441, val_preheader_i16);
    val435->addIncoming(builder.getInt64(4278190080ll), valf32_from_ll_exit15);
    val436->addIncoming(val442, val_preheader_i16);
    val436->addIncoming(builder.getInt32(-1), valf32_from_ll_exit15);
    val456->addIncoming(val441, val446);
    val456->addIncoming(val454, val448);
    val471->addIncoming(val470, val465);
    val471->addIncoming(builder.getInt32(2139095040), val455);
    val471->addIncoming(val464, val461);
    val515->addIncoming(builder.getInt64(-9223372036854775808ll), val475);
    val515->addIncoming(builder.getInt64(-9223372036854775808ll), valf32_from_ll_exit17);
    val515->addIncoming(builder.getInt64(0ll), val481);
    val515->addIncoming(val506, val500);
    val515->addIncoming(val514, val509);
    val515->addIncoming(builder.getInt64(0ll), val483);
    val515->addIncoming(builder.getInt64(-9223372036854775808ll), val507);
    val522->addIncoming(val520, valf32_to_ll_exit18);
    val522->addIncoming(val0, val3);
  }
  {
    Function *func = funcray_impl;
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val23 = BasicBlock::Create(context, "", func);
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit_thread11 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit_thread = BasicBlock::Create(context, "", func);
    BasicBlock *val148 = BasicBlock::Create(context, "", func);
    BasicBlock *val154 = BasicBlock::Create(context, "", func);
    BasicBlock *val160 = BasicBlock::Create(context, "", func);
    BasicBlock *val163 = BasicBlock::Create(context, "", func);
    BasicBlock *val169 = BasicBlock::Create(context, "", func);
    BasicBlock *val173 = BasicBlock::Create(context, "", func);
    BasicBlock *val176 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit2 = BasicBlock::Create(context, "", func);
    BasicBlock *val183 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit2_thread = BasicBlock::Create(context, "", func);
    BasicBlock *val238 = BasicBlock::Create(context, "", func);
    BasicBlock *val244 = BasicBlock::Create(context, "", func);
    BasicBlock *val250 = BasicBlock::Create(context, "", func);
    BasicBlock *val253 = BasicBlock::Create(context, "", func);
    BasicBlock *val259 = BasicBlock::Create(context, "", func);
    BasicBlock *val263 = BasicBlock::Create(context, "", func);
    BasicBlock *val266 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit4 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit5 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit4_thread = BasicBlock::Create(context, "", func);
    BasicBlock *val290 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_div_exit6 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i9 = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit_i8 = BasicBlock::Create(context, "", func);
    BasicBlock *val318 = BasicBlock::Create(context, "", func);
    BasicBlock *val325 = BasicBlock::Create(context, "", func);
    BasicBlock *val331 = BasicBlock::Create(context, "", func);
    BasicBlock *val335 = BasicBlock::Create(context, "", func);
    BasicBlock *valbuild_float_exit10 = BasicBlock::Create(context, "", func);
    BasicBlock *val347 = BasicBlock::Create(context, "", func);
    BasicBlock *val353 = BasicBlock::Create(context, "", func);
    BasicBlock *val359 = BasicBlock::Create(context, "", func);
    BasicBlock *val362 = BasicBlock::Create(context, "", func);
    BasicBlock *val368 = BasicBlock::Create(context, "", func);
    BasicBlock *val372 = BasicBlock::Create(context, "", func);
    BasicBlock *val375 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit7 = BasicBlock::Create(context, "", func);
    BasicBlock *val382 = BasicBlock::Create(context, "", func);
    BasicBlock *val470 = BasicBlock::Create(context, "", func);
    BasicBlock *val473 = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    Value *val4 = func->getArg(4);
    Value *val5 = func->getArg(5);
    Value *val6 = func->getArg(6);
    Value *val7 = func->getArg(7);
    Value *val8 = func->getArg(8);
    Value *val9 = func->getArg(9);
    Value *val10 = func->getArg(10);
    Value *val11 = func->getArg(11);
    Value *val12 = func->getArg(12);
    Value *val13 = func->getArg(13);
    builder.SetInsertPoint(val14);
    //   %15 = getelementptr i32, ptr %0, i64 1
    Value *val15 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(1ll)});
    builder.Insert(val15);
    //   %16 = getelementptr i32, ptr %1, i64 1
    Value *val16 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(1ll)});
    builder.Insert(val16);
    //   %17 = getelementptr i32, ptr %2, i64 1
    Value *val17 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(1ll)});
    builder.Insert(val17);
    //   %18 = getelementptr i32, ptr %3, i64 1
    Value *val18 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(1ll)});
    builder.Insert(val18);
    //   %19 = getelementptr i32, ptr %0, i64 2
    Value *val19 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(2ll)});
    builder.Insert(val19);
    //   %20 = getelementptr i32, ptr %1, i64 2
    Value *val20 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(2ll)});
    builder.Insert(val20);
    //   %21 = getelementptr i32, ptr %2, i64 2
    Value *val21 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(2ll)});
    builder.Insert(val21);
    //   %22 = getelementptr i32, ptr %3, i64 2
    Value *val22 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(2ll)});
    builder.Insert(val22);
    //   br label %23
    builder.CreateBr(val23);
    builder.SetInsertPoint(val23);
    //   %24 = phi i32 [ %12, %14 ], [ %28, %f32_less.exit7 ]
    PHINode *val24 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %25 = phi i32 [ %8, %14 ], [ %289, %f32_less.exit7 ]
    PHINode *val25 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %26 = phi i32 [ %7, %14 ], [ %287, %f32_less.exit7 ]
    PHINode *val26 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %27 = phi i32 [ %6, %14 ], [ %285, %f32_less.exit7 ]
    PHINode *val27 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %28 = add i32 %24, -1
    Value *val28 = builder.CreateAdd(val24, builder.getInt32(-1), "", false, false);
    //   %29 = icmp eq i32 %24, 0
    Value *val29 = builder.CreateICmpEQ(val24, builder.getInt32(0), "");
    //   br i1 %29, label %.loopexit, label %build_float.exit
    builder.CreateCondBr(val29, val_loopexit, valbuild_float_exit);
    builder.SetInsertPoint(valbuild_float_exit);
    //   %30 = load i32, ptr %0, align 4, !tbaa !4
    Value *val30 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val0, MaybeAlign(4));
    //   %31 = and i32 %27, 2139095040
    Value *val31 = builder.CreateAnd(val27, builder.getInt32(2139095040), "");
    //   %32 = icmp ne i32 %31, 2139095040
    Value *val32 = builder.CreateICmpNE(val31, builder.getInt32(2139095040), "");
    //   %33 = and i32 %27, 8388607
    Value *val33 = builder.CreateAnd(val27, builder.getInt32(8388607), "");
    //   %34 = icmp eq i32 %33, 0
    Value *val34 = builder.CreateICmpEQ(val33, builder.getInt32(0), "");
    //   %35 = or i1 %32, %34
    Value *val35 = builder.CreateOr(val32, val34, "");
    //   %36 = xor i32 %27, -2147483648
    Value *val36 = builder.CreateXor(val27, builder.getInt32(-2147483648), "");
    //   %37 = select i1 %35, i32 %36, i32 %27
    Value *val37 = builder.CreateSelect(val35, val36, val27);
    //   %38 = tail call i32 @f32_add(i32 noundef %30, i32 noundef %37)
    Value *val38 = builder.CreateCall(funcf32_add, {val30, val37});
    //   %39 = load i32, ptr %1, align 4, !tbaa !4
    Value *val39 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val1, MaybeAlign(4));
    //   %40 = and i32 %26, 2139095040
    Value *val40 = builder.CreateAnd(val26, builder.getInt32(2139095040), "");
    //   %41 = icmp ne i32 %40, 2139095040
    Value *val41 = builder.CreateICmpNE(val40, builder.getInt32(2139095040), "");
    //   %42 = and i32 %26, 8388607
    Value *val42 = builder.CreateAnd(val26, builder.getInt32(8388607), "");
    //   %43 = icmp eq i32 %42, 0
    Value *val43 = builder.CreateICmpEQ(val42, builder.getInt32(0), "");
    //   %44 = or i1 %41, %43
    Value *val44 = builder.CreateOr(val41, val43, "");
    //   %45 = xor i32 %26, -2147483648
    Value *val45 = builder.CreateXor(val26, builder.getInt32(-2147483648), "");
    //   %46 = select i1 %44, i32 %45, i32 %26
    Value *val46 = builder.CreateSelect(val44, val45, val26);
    //   %47 = tail call i32 @f32_add(i32 noundef %39, i32 noundef %46)
    Value *val47 = builder.CreateCall(funcf32_add, {val39, val46});
    //   %48 = load i32, ptr %2, align 4, !tbaa !4
    Value *val48 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val2, MaybeAlign(4));
    //   %49 = and i32 %25, 2139095040
    Value *val49 = builder.CreateAnd(val25, builder.getInt32(2139095040), "");
    //   %50 = icmp ne i32 %49, 2139095040
    Value *val50 = builder.CreateICmpNE(val49, builder.getInt32(2139095040), "");
    //   %51 = and i32 %25, 8388607
    Value *val51 = builder.CreateAnd(val25, builder.getInt32(8388607), "");
    //   %52 = icmp eq i32 %51, 0
    Value *val52 = builder.CreateICmpEQ(val51, builder.getInt32(0), "");
    //   %53 = or i1 %50, %52
    Value *val53 = builder.CreateOr(val50, val52, "");
    //   %54 = xor i32 %25, -2147483648
    Value *val54 = builder.CreateXor(val25, builder.getInt32(-2147483648), "");
    //   %55 = select i1 %53, i32 %54, i32 %25
    Value *val55 = builder.CreateSelect(val53, val54, val25);
    //   %56 = tail call i32 @f32_add(i32 noundef %48, i32 noundef %55)
    Value *val56 = builder.CreateCall(funcf32_add, {val48, val55});
    //   %57 = tail call i32 @f32_mul(i32 noundef %38, i32 noundef %38) #9
    Value *val57 = builder.CreateCall(funcf32_mul, {val38, val38});
    //   %58 = tail call i32 @f32_mul(i32 noundef %47, i32 noundef %47) #9
    Value *val58 = builder.CreateCall(funcf32_mul, {val47, val47});
    //   %59 = tail call i32 @f32_add(i32 noundef %57, i32 noundef %58) #9
    Value *val59 = builder.CreateCall(funcf32_add, {val57, val58});
    //   %60 = tail call i32 @f32_mul(i32 noundef %56, i32 noundef %56) #9
    Value *val60 = builder.CreateCall(funcf32_mul, {val56, val56});
    //   %61 = tail call i32 @f32_add(i32 noundef %59, i32 noundef %60) #9
    Value *val61 = builder.CreateCall(funcf32_add, {val59, val60});
    //   %62 = tail call i32 @f32_div(i32 noundef %61, i32 noundef 1073741824) #9
    Value *val62 = builder.CreateCall(funcf32_div, {val61, builder.getInt32(1073741824)});
    //   %63 = lshr i32 %61, 1
    Value *val63 = builder.CreateLShr(val61, builder.getInt32(1), "", false);
    //   %64 = sub nsw i32 1597463007, %63
    Value *val64 = builder.CreateSub(builder.getInt32(1597463007), val63, "", false, true);
    //   %65 = tail call i32 @f32_mul(i32 noundef %64, i32 noundef %64) #9
    Value *val65 = builder.CreateCall(funcf32_mul, {val64, val64});
    //   %66 = tail call i32 @f32_mul(i32 noundef %62, i32 noundef %65) #9
    Value *val66 = builder.CreateCall(funcf32_mul, {val62, val65});
    //   %67 = and i32 %66, 2139095040
    Value *val67 = builder.CreateAnd(val66, builder.getInt32(2139095040), "");
    //   %68 = icmp ne i32 %67, 2139095040
    Value *val68 = builder.CreateICmpNE(val67, builder.getInt32(2139095040), "");
    //   %69 = and i32 %66, 8388607
    Value *val69 = builder.CreateAnd(val66, builder.getInt32(8388607), "");
    //   %70 = icmp eq i32 %69, 0
    Value *val70 = builder.CreateICmpEQ(val69, builder.getInt32(0), "");
    //   %71 = or i1 %68, %70
    Value *val71 = builder.CreateOr(val68, val70, "");
    //   %72 = xor i32 %66, -2147483648
    Value *val72 = builder.CreateXor(val66, builder.getInt32(-2147483648), "");
    //   %73 = select i1 %71, i32 %72, i32 %66
    Value *val73 = builder.CreateSelect(val71, val72, val66);
    //   %74 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %73)
    Value *val74 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val73});
    //   %75 = tail call i32 @f32_mul(i32 noundef %64, i32 noundef %74) #9
    Value *val75 = builder.CreateCall(funcf32_mul, {val64, val74});
    //   %76 = tail call i32 @f32_mul(i32 noundef %61, i32 noundef %75) #9
    Value *val76 = builder.CreateCall(funcf32_mul, {val61, val75});
    //   %77 = load i32, ptr %3, align 4, !tbaa !4
    Value *val77 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val3, MaybeAlign(4));
    //   %78 = and i32 %77, 2139095040
    Value *val78 = builder.CreateAnd(val77, builder.getInt32(2139095040), "");
    //   %79 = icmp ne i32 %78, 2139095040
    Value *val79 = builder.CreateICmpNE(val78, builder.getInt32(2139095040), "");
    //   %80 = and i32 %77, 8388607
    Value *val80 = builder.CreateAnd(val77, builder.getInt32(8388607), "");
    //   %81 = icmp eq i32 %80, 0
    Value *val81 = builder.CreateICmpEQ(val80, builder.getInt32(0), "");
    //   %82 = or i1 %79, %81
    Value *val82 = builder.CreateOr(val79, val81, "");
    //   %83 = xor i32 %77, -2147483648
    Value *val83 = builder.CreateXor(val77, builder.getInt32(-2147483648), "");
    //   %84 = select i1 %82, i32 %83, i32 %77
    Value *val84 = builder.CreateSelect(val82, val83, val77);
    //   %85 = tail call i32 @f32_add(i32 noundef %76, i32 noundef %84)
    Value *val85 = builder.CreateCall(funcf32_add, {val76, val84});
    //   %86 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %38) #9
    Value *val86 = builder.CreateCall(funcf32_mul, {val9, val38});
    //   %87 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %47) #9
    Value *val87 = builder.CreateCall(funcf32_mul, {val10, val47});
    //   %88 = tail call i32 @f32_add(i32 noundef %86, i32 noundef %87) #9
    Value *val88 = builder.CreateCall(funcf32_add, {val86, val87});
    //   %89 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %56) #9
    Value *val89 = builder.CreateCall(funcf32_mul, {val11, val56});
    //   %90 = tail call i32 @f32_add(i32 noundef %88, i32 noundef %89) #9
    Value *val90 = builder.CreateCall(funcf32_add, {val88, val89});
    //   %91 = and i32 %85, 2139095040
    Value *val91 = builder.CreateAnd(val85, builder.getInt32(2139095040), "");
    //   %92 = icmp eq i32 %91, 2139095040
    Value *val92 = builder.CreateICmpEQ(val91, builder.getInt32(2139095040), "");
    //   %93 = and i32 %85, 8388607
    Value *val93 = builder.CreateAnd(val85, builder.getInt32(8388607), "");
    //   %94 = icmp ne i32 %93, 0
    Value *val94 = builder.CreateICmpNE(val93, builder.getInt32(0), "");
    //   %.not66 = and i1 %92, %94
    Value *val_not66 = builder.CreateAnd(val92, val94, "");
    //   %or.cond41 = icmp sgt i32 %85, 1203982335
    Value *valor_cond41 = builder.CreateICmpSGT(val85, builder.getInt32(1203982335), "");
    //   %or.cond101 = select i1 %.not66, i1 true, i1 %or.cond41
    Value *valor_cond101 = builder.CreateSelect(val_not66, builder.getInt1(true), valor_cond41);
    //   br i1 %or.cond101, label %f32_less.exit.thread, label %f32_less.exit.thread11
    builder.CreateCondBr(valor_cond101, valf32_less_exit_thread, valf32_less_exit_thread11);
    builder.SetInsertPoint(valf32_less_exit_thread11);
    //   %95 = and i32 %90, 2139095040
    Value *val95 = builder.CreateAnd(val90, builder.getInt32(2139095040), "");
    //   %96 = icmp ne i32 %95, 2139095040
    Value *val96 = builder.CreateICmpNE(val95, builder.getInt32(2139095040), "");
    //   %97 = and i32 %90, 8388607
    Value *val97 = builder.CreateAnd(val90, builder.getInt32(8388607), "");
    //   %98 = icmp eq i32 %97, 0
    Value *val98 = builder.CreateICmpEQ(val97, builder.getInt32(0), "");
    //   %.not31.not = or i1 %96, %98
    Value *val_not31_not = builder.CreateOr(val96, val98, "");
    //   %99 = and i32 %90, 2147483647
    Value *val99 = builder.CreateAnd(val90, builder.getInt32(2147483647), "");
    //   %100 = icmp ne i32 %99, 0
    Value *val100 = builder.CreateICmpNE(val99, builder.getInt32(0), "");
    //   %or.cond = select i1 %.not31.not, i1 %100, i1 false
    Value *valor_cond = builder.CreateSelect(val_not31_not, val100, builder.getInt1(false));
    //   %101 = icmp sgt i32 %90, -1
    Value *val101 = builder.CreateICmpSGT(val90, builder.getInt32(-1), "");
    //   %or.cond19 = select i1 %or.cond, i1 %101, i1 false
    Value *valor_cond19 = builder.CreateSelect(valor_cond, val101, builder.getInt1(false));
    //   %. = select i1 %or.cond19, i32 %85, i32 1203982336
    Value *val_ = builder.CreateSelect(valor_cond19, val85, builder.getInt32(1203982336));
    //   br label %f32_less.exit.thread
    builder.CreateBr(valf32_less_exit_thread);
    builder.SetInsertPoint(valf32_less_exit_thread);
    //   %102 = phi i32 [ 1203982336, %build_float.exit ], [ %., %f32_less.exit.thread11 ]
    PHINode *val102 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %103 = load i32, ptr %15, align 4, !tbaa !4
    Value *val103 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val15, MaybeAlign(4));
    //   %104 = tail call i32 @f32_add(i32 noundef %103, i32 noundef %37)
    Value *val104 = builder.CreateCall(funcf32_add, {val103, val37});
    //   %105 = load i32, ptr %16, align 4, !tbaa !4
    Value *val105 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val16, MaybeAlign(4));
    //   %106 = tail call i32 @f32_add(i32 noundef %105, i32 noundef %46)
    Value *val106 = builder.CreateCall(funcf32_add, {val105, val46});
    //   %107 = load i32, ptr %17, align 4, !tbaa !4
    Value *val107 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val17, MaybeAlign(4));
    //   %108 = tail call i32 @f32_add(i32 noundef %107, i32 noundef %55)
    Value *val108 = builder.CreateCall(funcf32_add, {val107, val55});
    //   %109 = tail call i32 @f32_mul(i32 noundef %104, i32 noundef %104) #9
    Value *val109 = builder.CreateCall(funcf32_mul, {val104, val104});
    //   %110 = tail call i32 @f32_mul(i32 noundef %106, i32 noundef %106) #9
    Value *val110 = builder.CreateCall(funcf32_mul, {val106, val106});
    //   %111 = tail call i32 @f32_add(i32 noundef %109, i32 noundef %110) #9
    Value *val111 = builder.CreateCall(funcf32_add, {val109, val110});
    //   %112 = tail call i32 @f32_mul(i32 noundef %108, i32 noundef %108) #9
    Value *val112 = builder.CreateCall(funcf32_mul, {val108, val108});
    //   %113 = tail call i32 @f32_add(i32 noundef %111, i32 noundef %112) #9
    Value *val113 = builder.CreateCall(funcf32_add, {val111, val112});
    //   %114 = tail call i32 @f32_div(i32 noundef %113, i32 noundef 1073741824) #9
    Value *val114 = builder.CreateCall(funcf32_div, {val113, builder.getInt32(1073741824)});
    //   %115 = lshr i32 %113, 1
    Value *val115 = builder.CreateLShr(val113, builder.getInt32(1), "", false);
    //   %116 = sub nsw i32 1597463007, %115
    Value *val116 = builder.CreateSub(builder.getInt32(1597463007), val115, "", false, true);
    //   %117 = tail call i32 @f32_mul(i32 noundef %116, i32 noundef %116) #9
    Value *val117 = builder.CreateCall(funcf32_mul, {val116, val116});
    //   %118 = tail call i32 @f32_mul(i32 noundef %114, i32 noundef %117) #9
    Value *val118 = builder.CreateCall(funcf32_mul, {val114, val117});
    //   %119 = and i32 %118, 2139095040
    Value *val119 = builder.CreateAnd(val118, builder.getInt32(2139095040), "");
    //   %120 = icmp ne i32 %119, 2139095040
    Value *val120 = builder.CreateICmpNE(val119, builder.getInt32(2139095040), "");
    //   %121 = and i32 %118, 8388607
    Value *val121 = builder.CreateAnd(val118, builder.getInt32(8388607), "");
    //   %122 = icmp eq i32 %121, 0
    Value *val122 = builder.CreateICmpEQ(val121, builder.getInt32(0), "");
    //   %123 = or i1 %120, %122
    Value *val123 = builder.CreateOr(val120, val122, "");
    //   %124 = xor i32 %118, -2147483648
    Value *val124 = builder.CreateXor(val118, builder.getInt32(-2147483648), "");
    //   %125 = select i1 %123, i32 %124, i32 %118
    Value *val125 = builder.CreateSelect(val123, val124, val118);
    //   %126 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %125)
    Value *val126 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val125});
    //   %127 = tail call i32 @f32_mul(i32 noundef %116, i32 noundef %126) #9
    Value *val127 = builder.CreateCall(funcf32_mul, {val116, val126});
    //   %128 = tail call i32 @f32_mul(i32 noundef %113, i32 noundef %127) #9
    Value *val128 = builder.CreateCall(funcf32_mul, {val113, val127});
    //   %129 = load i32, ptr %18, align 4, !tbaa !4
    Value *val129 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val18, MaybeAlign(4));
    //   %130 = and i32 %129, 2139095040
    Value *val130 = builder.CreateAnd(val129, builder.getInt32(2139095040), "");
    //   %131 = icmp ne i32 %130, 2139095040
    Value *val131 = builder.CreateICmpNE(val130, builder.getInt32(2139095040), "");
    //   %132 = and i32 %129, 8388607
    Value *val132 = builder.CreateAnd(val129, builder.getInt32(8388607), "");
    //   %133 = icmp eq i32 %132, 0
    Value *val133 = builder.CreateICmpEQ(val132, builder.getInt32(0), "");
    //   %134 = or i1 %131, %133
    Value *val134 = builder.CreateOr(val131, val133, "");
    //   %135 = xor i32 %129, -2147483648
    Value *val135 = builder.CreateXor(val129, builder.getInt32(-2147483648), "");
    //   %136 = select i1 %134, i32 %135, i32 %129
    Value *val136 = builder.CreateSelect(val134, val135, val129);
    //   %137 = tail call i32 @f32_add(i32 noundef %128, i32 noundef %136)
    Value *val137 = builder.CreateCall(funcf32_add, {val128, val136});
    //   %138 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %104) #9
    Value *val138 = builder.CreateCall(funcf32_mul, {val9, val104});
    //   %139 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %106) #9
    Value *val139 = builder.CreateCall(funcf32_mul, {val10, val106});
    //   %140 = tail call i32 @f32_add(i32 noundef %138, i32 noundef %139) #9
    Value *val140 = builder.CreateCall(funcf32_add, {val138, val139});
    //   %141 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %108) #9
    Value *val141 = builder.CreateCall(funcf32_mul, {val11, val108});
    //   %142 = tail call i32 @f32_add(i32 noundef %140, i32 noundef %141) #9
    Value *val142 = builder.CreateCall(funcf32_add, {val140, val141});
    //   %143 = and i32 %137, 2139095040
    Value *val143 = builder.CreateAnd(val137, builder.getInt32(2139095040), "");
    //   %144 = icmp ne i32 %143, 2139095040
    Value *val144 = builder.CreateICmpNE(val143, builder.getInt32(2139095040), "");
    //   %145 = and i32 %137, 8388607
    Value *val145 = builder.CreateAnd(val137, builder.getInt32(8388607), "");
    //   %146 = icmp eq i32 %145, 0
    Value *val146 = builder.CreateICmpEQ(val145, builder.getInt32(0), "");
    //   %147 = or i1 %144, %146
    Value *val147 = builder.CreateOr(val144, val146, "");
    //   br i1 %147, label %148, label %f32_less.exit2.thread
    builder.CreateCondBr(val147, val148, valf32_less_exit2_thread);
    builder.SetInsertPoint(val148);
    //   %149 = and i32 %102, 2139095040
    Value *val149 = builder.CreateAnd(val102, builder.getInt32(2139095040), "");
    //   %150 = icmp ne i32 %149, 2139095040
    Value *val150 = builder.CreateICmpNE(val149, builder.getInt32(2139095040), "");
    //   %151 = and i32 %102, 8388607
    Value *val151 = builder.CreateAnd(val102, builder.getInt32(8388607), "");
    //   %152 = icmp eq i32 %151, 0
    Value *val152 = builder.CreateICmpEQ(val151, builder.getInt32(0), "");
    //   %153 = or i1 %150, %152
    Value *val153 = builder.CreateOr(val150, val152, "");
    //   br i1 %153, label %154, label %f32_less.exit2.thread
    builder.CreateCondBr(val153, val154, valf32_less_exit2_thread);
    builder.SetInsertPoint(val154);
    //   %155 = and i32 %137, 2147483647
    Value *val155 = builder.CreateAnd(val137, builder.getInt32(2147483647), "");
    //   %156 = icmp eq i32 %155, 2139095040
    Value *val156 = builder.CreateICmpEQ(val155, builder.getInt32(2139095040), "");
    //   %157 = and i32 %102, 2147483647
    Value *val157 = builder.CreateAnd(val102, builder.getInt32(2147483647), "");
    //   %158 = icmp eq i32 %157, 2139095040
    Value *val158 = builder.CreateICmpEQ(val157, builder.getInt32(2139095040), "");
    //   %159 = and i1 %158, %156
    Value *val159 = builder.CreateAnd(val158, val156, "");
    //   br i1 %159, label %160, label %163
    builder.CreateCondBr(val159, val160, val163);
    builder.SetInsertPoint(val160);
    //   %161 = xor i32 %137, %102
    Value *val161 = builder.CreateXor(val137, val102, "");
    //   %162 = icmp sgt i32 %161, -1
    Value *val162 = builder.CreateICmpSGT(val161, builder.getInt32(-1), "");
    //   br i1 %162, label %f32_less.exit2.thread, label %169
    builder.CreateCondBr(val162, valf32_less_exit2_thread, val169);
    builder.SetInsertPoint(val163);
    //   %164 = or i32 %137, %102
    Value *val164 = builder.CreateOr(val137, val102, "");
    //   %165 = and i32 %164, 2147483647
    Value *val165 = builder.CreateAnd(val164, builder.getInt32(2147483647), "");
    //   %166 = icmp eq i32 %165, 0
    Value *val166 = builder.CreateICmpEQ(val165, builder.getInt32(0), "");
    //   %167 = icmp eq i32 %137, %102
    Value *val167 = builder.CreateICmpEQ(val137, val102, "");
    //   %168 = or i1 %167, %166
    Value *val168 = builder.CreateOr(val167, val166, "");
    //   br i1 %168, label %f32_less.exit2.thread, label %169
    builder.CreateCondBr(val168, valf32_less_exit2_thread, val169);
    builder.SetInsertPoint(val169);
    //   %170 = lshr i32 %137, 31
    Value *val170 = builder.CreateLShr(val137, builder.getInt32(31), "", false);
    //   %171 = lshr i32 %102, 31
    Value *val171 = builder.CreateLShr(val102, builder.getInt32(31), "", false);
    //   %172 = icmp eq i32 %170, %171
    Value *val172 = builder.CreateICmpEQ(val170, val171, "");
    //   br i1 %172, label %176, label %173
    builder.CreateCondBr(val172, val176, val173);
    builder.SetInsertPoint(val173);
    //   %174 = icmp ugt i32 %170, %171
    Value *val174 = builder.CreateICmpUGT(val170, val171, "");
    //   %175 = zext i1 %174 to i8
    Value *val175 = builder.CreateZExt(val174, Type::getInt8Ty(context));
    //   br label %f32_less.exit2
    builder.CreateBr(valf32_less_exit2);
    builder.SetInsertPoint(val176);
    //   %177 = icmp ult i32 %137, %102
    Value *val177 = builder.CreateICmpULT(val137, val102, "");
    //   %178 = zext i1 %177 to i32
    Value *val178 = builder.CreateZExt(val177, Type::getInt32Ty(context));
    //   %179 = xor i32 %170, %178
    Value *val179 = builder.CreateXor(val170, val178, "");
    //   %180 = trunc i32 %179 to i8
    Value *val180 = builder.CreateTrunc(val179, Type::getInt8Ty(context));
    //   br label %f32_less.exit2
    builder.CreateBr(valf32_less_exit2);
    builder.SetInsertPoint(valf32_less_exit2);
    //   %181 = phi i8 [ %175, %173 ], [ %180, %176 ]
    PHINode *val181 = builder.CreatePHI(Type::getInt8Ty(context), 2);
    //   %182 = icmp eq i8 %181, 0
    Value *val182 = builder.CreateICmpEQ(val181, builder.getInt8(0), "");
    //   br i1 %182, label %f32_less.exit2.thread, label %183
    builder.CreateCondBr(val182, valf32_less_exit2_thread, val183);
    builder.SetInsertPoint(val183);
    //   %184 = and i32 %142, 2139095040
    Value *val184 = builder.CreateAnd(val142, builder.getInt32(2139095040), "");
    //   %185 = icmp ne i32 %184, 2139095040
    Value *val185 = builder.CreateICmpNE(val184, builder.getInt32(2139095040), "");
    //   %186 = and i32 %142, 8388607
    Value *val186 = builder.CreateAnd(val142, builder.getInt32(8388607), "");
    //   %187 = icmp eq i32 %186, 0
    Value *val187 = builder.CreateICmpEQ(val186, builder.getInt32(0), "");
    //   %.not34.not = or i1 %185, %187
    Value *val_not34_not = builder.CreateOr(val185, val187, "");
    //   %188 = and i32 %142, 2147483647
    Value *val188 = builder.CreateAnd(val142, builder.getInt32(2147483647), "");
    //   %189 = icmp ne i32 %188, 0
    Value *val189 = builder.CreateICmpNE(val188, builder.getInt32(0), "");
    //   %or.cond22 = select i1 %.not34.not, i1 %189, i1 false
    Value *valor_cond22 = builder.CreateSelect(val_not34_not, val189, builder.getInt1(false));
    //   %190 = icmp sgt i32 %142, -1
    Value *val190 = builder.CreateICmpSGT(val142, builder.getInt32(-1), "");
    //   %or.cond24 = select i1 %or.cond22, i1 %190, i1 false
    Value *valor_cond24 = builder.CreateSelect(valor_cond22, val190, builder.getInt1(false));
    //   %spec.select = zext i1 %or.cond24 to i32
    Value *valspec_select = builder.CreateZExt(valor_cond24, Type::getInt32Ty(context));
    //   %spec.select42 = select i1 %or.cond24, i32 %137, i32 %102
    Value *valspec_select42 = builder.CreateSelect(valor_cond24, val137, val102);
    //   br label %f32_less.exit2.thread
    builder.CreateBr(valf32_less_exit2_thread);
    builder.SetInsertPoint(valf32_less_exit2_thread);
    //   %191 = phi i32 [ 0, %f32_less.exit2 ], [ 0, %163 ], [ 0, %148 ], [ 0, %f32_less.exit.thread ], [ 0, %160 ], [ %spec.select, %183 ]
    PHINode *val191 = builder.CreatePHI(Type::getInt32Ty(context), 6);
    //   %192 = phi i32 [ %102, %f32_less.exit2 ], [ %102, %163 ], [ %102, %148 ], [ %102, %f32_less.exit.thread ], [ %102, %160 ], [ %spec.select42, %183 ]
    PHINode *val192 = builder.CreatePHI(Type::getInt32Ty(context), 6);
    //   %193 = load i32, ptr %19, align 4, !tbaa !4
    Value *val193 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val19, MaybeAlign(4));
    //   %194 = tail call i32 @f32_add(i32 noundef %193, i32 noundef %37)
    Value *val194 = builder.CreateCall(funcf32_add, {val193, val37});
    //   %195 = load i32, ptr %20, align 4, !tbaa !4
    Value *val195 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val20, MaybeAlign(4));
    //   %196 = tail call i32 @f32_add(i32 noundef %195, i32 noundef %46)
    Value *val196 = builder.CreateCall(funcf32_add, {val195, val46});
    //   %197 = load i32, ptr %21, align 4, !tbaa !4
    Value *val197 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val21, MaybeAlign(4));
    //   %198 = tail call i32 @f32_add(i32 noundef %197, i32 noundef %55)
    Value *val198 = builder.CreateCall(funcf32_add, {val197, val55});
    //   %199 = tail call i32 @f32_mul(i32 noundef %194, i32 noundef %194) #9
    Value *val199 = builder.CreateCall(funcf32_mul, {val194, val194});
    //   %200 = tail call i32 @f32_mul(i32 noundef %196, i32 noundef %196) #9
    Value *val200 = builder.CreateCall(funcf32_mul, {val196, val196});
    //   %201 = tail call i32 @f32_add(i32 noundef %199, i32 noundef %200) #9
    Value *val201 = builder.CreateCall(funcf32_add, {val199, val200});
    //   %202 = tail call i32 @f32_mul(i32 noundef %198, i32 noundef %198) #9
    Value *val202 = builder.CreateCall(funcf32_mul, {val198, val198});
    //   %203 = tail call i32 @f32_add(i32 noundef %201, i32 noundef %202) #9
    Value *val203 = builder.CreateCall(funcf32_add, {val201, val202});
    //   %204 = tail call i32 @f32_div(i32 noundef %203, i32 noundef 1073741824) #9
    Value *val204 = builder.CreateCall(funcf32_div, {val203, builder.getInt32(1073741824)});
    //   %205 = lshr i32 %203, 1
    Value *val205 = builder.CreateLShr(val203, builder.getInt32(1), "", false);
    //   %206 = sub nsw i32 1597463007, %205
    Value *val206 = builder.CreateSub(builder.getInt32(1597463007), val205, "", false, true);
    //   %207 = tail call i32 @f32_mul(i32 noundef %206, i32 noundef %206) #9
    Value *val207 = builder.CreateCall(funcf32_mul, {val206, val206});
    //   %208 = tail call i32 @f32_mul(i32 noundef %204, i32 noundef %207) #9
    Value *val208 = builder.CreateCall(funcf32_mul, {val204, val207});
    //   %209 = and i32 %208, 2139095040
    Value *val209 = builder.CreateAnd(val208, builder.getInt32(2139095040), "");
    //   %210 = icmp ne i32 %209, 2139095040
    Value *val210 = builder.CreateICmpNE(val209, builder.getInt32(2139095040), "");
    //   %211 = and i32 %208, 8388607
    Value *val211 = builder.CreateAnd(val208, builder.getInt32(8388607), "");
    //   %212 = icmp eq i32 %211, 0
    Value *val212 = builder.CreateICmpEQ(val211, builder.getInt32(0), "");
    //   %213 = or i1 %210, %212
    Value *val213 = builder.CreateOr(val210, val212, "");
    //   %214 = xor i32 %208, -2147483648
    Value *val214 = builder.CreateXor(val208, builder.getInt32(-2147483648), "");
    //   %215 = select i1 %213, i32 %214, i32 %208
    Value *val215 = builder.CreateSelect(val213, val214, val208);
    //   %216 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %215)
    Value *val216 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val215});
    //   %217 = tail call i32 @f32_mul(i32 noundef %206, i32 noundef %216) #9
    Value *val217 = builder.CreateCall(funcf32_mul, {val206, val216});
    //   %218 = tail call i32 @f32_mul(i32 noundef %203, i32 noundef %217) #9
    Value *val218 = builder.CreateCall(funcf32_mul, {val203, val217});
    //   %219 = load i32, ptr %22, align 4, !tbaa !4
    Value *val219 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val22, MaybeAlign(4));
    //   %220 = and i32 %219, 2139095040
    Value *val220 = builder.CreateAnd(val219, builder.getInt32(2139095040), "");
    //   %221 = icmp ne i32 %220, 2139095040
    Value *val221 = builder.CreateICmpNE(val220, builder.getInt32(2139095040), "");
    //   %222 = and i32 %219, 8388607
    Value *val222 = builder.CreateAnd(val219, builder.getInt32(8388607), "");
    //   %223 = icmp eq i32 %222, 0
    Value *val223 = builder.CreateICmpEQ(val222, builder.getInt32(0), "");
    //   %224 = or i1 %221, %223
    Value *val224 = builder.CreateOr(val221, val223, "");
    //   %225 = xor i32 %219, -2147483648
    Value *val225 = builder.CreateXor(val219, builder.getInt32(-2147483648), "");
    //   %226 = select i1 %224, i32 %225, i32 %219
    Value *val226 = builder.CreateSelect(val224, val225, val219);
    //   %227 = tail call i32 @f32_add(i32 noundef %218, i32 noundef %226)
    Value *val227 = builder.CreateCall(funcf32_add, {val218, val226});
    //   %228 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %194) #9
    Value *val228 = builder.CreateCall(funcf32_mul, {val9, val194});
    //   %229 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %196) #9
    Value *val229 = builder.CreateCall(funcf32_mul, {val10, val196});
    //   %230 = tail call i32 @f32_add(i32 noundef %228, i32 noundef %229) #9
    Value *val230 = builder.CreateCall(funcf32_add, {val228, val229});
    //   %231 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %198) #9
    Value *val231 = builder.CreateCall(funcf32_mul, {val11, val198});
    //   %232 = tail call i32 @f32_add(i32 noundef %230, i32 noundef %231) #9
    Value *val232 = builder.CreateCall(funcf32_add, {val230, val231});
    //   %233 = and i32 %227, 2139095040
    Value *val233 = builder.CreateAnd(val227, builder.getInt32(2139095040), "");
    //   %234 = icmp ne i32 %233, 2139095040
    Value *val234 = builder.CreateICmpNE(val233, builder.getInt32(2139095040), "");
    //   %235 = and i32 %227, 8388607
    Value *val235 = builder.CreateAnd(val227, builder.getInt32(8388607), "");
    //   %236 = icmp eq i32 %235, 0
    Value *val236 = builder.CreateICmpEQ(val235, builder.getInt32(0), "");
    //   %237 = or i1 %234, %236
    Value *val237 = builder.CreateOr(val234, val236, "");
    //   br i1 %237, label %238, label %f32_less.exit4.thread
    builder.CreateCondBr(val237, val238, valf32_less_exit4_thread);
    builder.SetInsertPoint(val238);
    //   %239 = and i32 %192, 2139095040
    Value *val239 = builder.CreateAnd(val192, builder.getInt32(2139095040), "");
    //   %240 = icmp ne i32 %239, 2139095040
    Value *val240 = builder.CreateICmpNE(val239, builder.getInt32(2139095040), "");
    //   %241 = and i32 %192, 8388607
    Value *val241 = builder.CreateAnd(val192, builder.getInt32(8388607), "");
    //   %242 = icmp eq i32 %241, 0
    Value *val242 = builder.CreateICmpEQ(val241, builder.getInt32(0), "");
    //   %243 = or i1 %240, %242
    Value *val243 = builder.CreateOr(val240, val242, "");
    //   br i1 %243, label %244, label %f32_less.exit4.thread
    builder.CreateCondBr(val243, val244, valf32_less_exit4_thread);
    builder.SetInsertPoint(val244);
    //   %245 = and i32 %227, 2147483647
    Value *val245 = builder.CreateAnd(val227, builder.getInt32(2147483647), "");
    //   %246 = icmp eq i32 %245, 2139095040
    Value *val246 = builder.CreateICmpEQ(val245, builder.getInt32(2139095040), "");
    //   %247 = and i32 %192, 2147483647
    Value *val247 = builder.CreateAnd(val192, builder.getInt32(2147483647), "");
    //   %248 = icmp eq i32 %247, 2139095040
    Value *val248 = builder.CreateICmpEQ(val247, builder.getInt32(2139095040), "");
    //   %249 = and i1 %248, %246
    Value *val249 = builder.CreateAnd(val248, val246, "");
    //   br i1 %249, label %250, label %253
    builder.CreateCondBr(val249, val250, val253);
    builder.SetInsertPoint(val250);
    //   %251 = xor i32 %227, %192
    Value *val251 = builder.CreateXor(val227, val192, "");
    //   %252 = icmp sgt i32 %251, -1
    Value *val252 = builder.CreateICmpSGT(val251, builder.getInt32(-1), "");
    //   br i1 %252, label %f32_less.exit4.thread, label %259
    builder.CreateCondBr(val252, valf32_less_exit4_thread, val259);
    builder.SetInsertPoint(val253);
    //   %254 = or i32 %227, %192
    Value *val254 = builder.CreateOr(val227, val192, "");
    //   %255 = and i32 %254, 2147483647
    Value *val255 = builder.CreateAnd(val254, builder.getInt32(2147483647), "");
    //   %256 = icmp eq i32 %255, 0
    Value *val256 = builder.CreateICmpEQ(val255, builder.getInt32(0), "");
    //   %257 = icmp eq i32 %227, %192
    Value *val257 = builder.CreateICmpEQ(val227, val192, "");
    //   %258 = or i1 %257, %256
    Value *val258 = builder.CreateOr(val257, val256, "");
    //   br i1 %258, label %f32_less.exit4.thread, label %259
    builder.CreateCondBr(val258, valf32_less_exit4_thread, val259);
    builder.SetInsertPoint(val259);
    //   %260 = lshr i32 %227, 31
    Value *val260 = builder.CreateLShr(val227, builder.getInt32(31), "", false);
    //   %261 = lshr i32 %192, 31
    Value *val261 = builder.CreateLShr(val192, builder.getInt32(31), "", false);
    //   %262 = icmp eq i32 %260, %261
    Value *val262 = builder.CreateICmpEQ(val260, val261, "");
    //   br i1 %262, label %266, label %263
    builder.CreateCondBr(val262, val266, val263);
    builder.SetInsertPoint(val263);
    //   %264 = icmp ugt i32 %260, %261
    Value *val264 = builder.CreateICmpUGT(val260, val261, "");
    //   %265 = zext i1 %264 to i8
    Value *val265 = builder.CreateZExt(val264, Type::getInt8Ty(context));
    //   br label %f32_less.exit4
    builder.CreateBr(valf32_less_exit4);
    builder.SetInsertPoint(val266);
    //   %267 = icmp ult i32 %227, %192
    Value *val267 = builder.CreateICmpULT(val227, val192, "");
    //   %268 = zext i1 %267 to i32
    Value *val268 = builder.CreateZExt(val267, Type::getInt32Ty(context));
    //   %269 = xor i32 %260, %268
    Value *val269 = builder.CreateXor(val260, val268, "");
    //   %270 = trunc i32 %269 to i8
    Value *val270 = builder.CreateTrunc(val269, Type::getInt8Ty(context));
    //   br label %f32_less.exit4
    builder.CreateBr(valf32_less_exit4);
    builder.SetInsertPoint(valf32_less_exit4);
    //   %271 = phi i8 [ %265, %263 ], [ %270, %266 ]
    PHINode *val271 = builder.CreatePHI(Type::getInt8Ty(context), 2);
    //   %272 = icmp eq i8 %271, 0
    Value *val272 = builder.CreateICmpEQ(val271, builder.getInt8(0), "");
    //   br i1 %272, label %f32_less.exit4.thread, label %f32_less.exit5
    builder.CreateCondBr(val272, valf32_less_exit4_thread, valf32_less_exit5);
    builder.SetInsertPoint(valf32_less_exit5);
    //   %273 = and i32 %232, 2139095040
    Value *val273 = builder.CreateAnd(val232, builder.getInt32(2139095040), "");
    //   %274 = icmp eq i32 %273, 2139095040
    Value *val274 = builder.CreateICmpEQ(val273, builder.getInt32(2139095040), "");
    //   %275 = and i32 %232, 8388607
    Value *val275 = builder.CreateAnd(val232, builder.getInt32(8388607), "");
    //   %276 = icmp ne i32 %275, 0
    Value *val276 = builder.CreateICmpNE(val275, builder.getInt32(0), "");
    //   %.not37.not.not = and i1 %274, %276
    Value *val_not37_not_not = builder.CreateAnd(val274, val276, "");
    //   %277 = and i32 %232, 2147483647
    Value *val277 = builder.CreateAnd(val232, builder.getInt32(2147483647), "");
    //   %278 = icmp eq i32 %277, 0
    Value *val278 = builder.CreateICmpEQ(val277, builder.getInt32(0), "");
    //   %or.cond27 = select i1 %.not37.not.not, i1 true, i1 %278
    Value *valor_cond27 = builder.CreateSelect(val_not37_not_not, builder.getInt1(true), val278);
    //   %279 = icmp slt i32 %232, 0
    Value *val279 = builder.CreateICmpSLT(val232, builder.getInt32(0), "");
    //   %or.cond29 = select i1 %or.cond27, i1 true, i1 %279
    Value *valor_cond29 = builder.CreateSelect(valor_cond27, builder.getInt1(true), val279);
    //   %280 = select i1 %or.cond29, i32 %191, i32 2
    Value *val280 = builder.CreateSelect(valor_cond29, val191, builder.getInt32(2));
    //   %281 = select i1 %or.cond29, i32 %192, i32 %227
    Value *val281 = builder.CreateSelect(valor_cond29, val192, val227);
    //   br label %f32_less.exit4.thread
    builder.CreateBr(valf32_less_exit4_thread);
    builder.SetInsertPoint(valf32_less_exit4_thread);
    //   %282 = phi i32 [ %191, %f32_less.exit4 ], [ %280, %f32_less.exit5 ], [ %191, %253 ], [ %191, %238 ], [ %191, %f32_less.exit2.thread ], [ %191, %250 ]
    PHINode *val282 = builder.CreatePHI(Type::getInt32Ty(context), 6);
    //   %283 = phi i32 [ %192, %f32_less.exit4 ], [ %281, %f32_less.exit5 ], [ %192, %253 ], [ %192, %238 ], [ %192, %f32_less.exit2.thread ], [ %192, %250 ]
    PHINode *val283 = builder.CreatePHI(Type::getInt32Ty(context), 6);
    //   %284 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %283) #9
    Value *val284 = builder.CreateCall(funcf32_mul, {val9, val283});
    //   %285 = tail call i32 @f32_add(i32 noundef %27, i32 noundef %284) #9
    Value *val285 = builder.CreateCall(funcf32_add, {val27, val284});
    //   %286 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %283) #9
    Value *val286 = builder.CreateCall(funcf32_mul, {val10, val283});
    //   %287 = tail call i32 @f32_add(i32 noundef %26, i32 noundef %286) #9
    Value *val287 = builder.CreateCall(funcf32_add, {val26, val286});
    //   %288 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %283) #9
    Value *val288 = builder.CreateCall(funcf32_mul, {val11, val283});
    //   %289 = tail call i32 @f32_add(i32 noundef %25, i32 noundef %288) #9
    Value *val289 = builder.CreateCall(funcf32_add, {val25, val288});
    //   br label %290
    builder.CreateBr(val290);
    builder.SetInsertPoint(val290);
    //   %291 = phi i64 [ 8388608, %f32_less.exit4.thread ], [ %299, %290 ]
    PHINode *val291 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %292 = phi i64 [ 0, %f32_less.exit4.thread ], [ %298, %290 ]
    PHINode *val292 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %293 = phi i32 [ 17, %f32_less.exit4.thread ], [ %295, %290 ]
    PHINode *val293 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %294 = shl nuw nsw i64 %291, 24
    Value *val294 = builder.CreateShl(val291, builder.getInt64(24ll), "", true, true);
    //   %295 = add i32 %293, -24
    Value *val295 = builder.CreateAdd(val293, builder.getInt32(-24), "", false, false);
    //   %296 = shl nuw nsw i64 %292, 24
    Value *val296 = builder.CreateShl(val292, builder.getInt64(24ll), "", true, true);
    //   %297 = udiv i64 %294, 13107200
    Value *val297 = builder.CreateUDiv(val294, builder.getInt64(13107200ll), "", false);
    //   %298 = add nuw nsw i64 %297, %296
    Value *val298 = builder.CreateAdd(val297, val296, "", true, true);
    //   %299 = urem i64 %294, 13107200
    Value *val299 = builder.CreateURem(val294, builder.getInt64(13107200ll), "");
    //   %300 = icmp ult i64 %298, 16777216
    Value *val300 = builder.CreateICmpULT(val298, builder.getInt64(16777216ll), "");
    //   br i1 %300, label %290, label %f32_div.exit6, !llvm.loop !8
    builder.CreateCondBr(val300, val290, valf32_div_exit6);
    builder.SetInsertPoint(valf32_div_exit6);
    //   %301 = icmp ugt i64 %299, 6553600
    Value *val301 = builder.CreateICmpUGT(val299, builder.getInt64(6553600ll), "");
    //   %302 = icmp ne i64 %299, 0
    Value *val302 = builder.CreateICmpNE(val299, builder.getInt64(0ll), "");
    //   %303 = zext i1 %302 to i32
    Value *val303 = builder.CreateZExt(val302, Type::getInt32Ty(context));
    //   %304 = select i1 %301, i32 2, i32 %303
    Value *val304 = builder.CreateSelect(val301, builder.getInt32(2), val303);
    //   br label %.preheader.i9
    builder.CreateBr(val_preheader_i9);
    builder.SetInsertPoint(val_preheader_i9);
    //   %305 = phi i32 [ %311, %.preheader.i9 ], [ %304, %f32_div.exit6 ]
    PHINode *val305 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %306 = phi i64 [ %312, %.preheader.i9 ], [ %298, %f32_div.exit6 ]
    PHINode *val306 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %307 = phi i32 [ %313, %.preheader.i9 ], [ %295, %f32_div.exit6 ]
    PHINode *val307 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %308 = trunc i64 %306 to i8
    Value *val308 = builder.CreateTrunc(val306, Type::getInt8Ty(context));
    //   %309 = and i8 %308, 1
    Value *val309 = builder.CreateAnd(val308, builder.getInt8(1), "");
    //   %310 = zext nneg i8 %309 to i32
    Value *val310 = builder.CreateZExt(val309, Type::getInt32Ty(context));
    //   %311 = add i32 %305, %310
    Value *val311 = builder.CreateAdd(val305, val310, "", false, false);
    //   %312 = lshr i64 %306, 1
    Value *val312 = builder.CreateLShr(val306, builder.getInt64(1ll), "", false);
    //   %313 = add i32 %307, 1
    Value *val313 = builder.CreateAdd(val307, builder.getInt32(1), "", false, false);
    //   %314 = icmp ugt i64 %306, 33554431
    Value *val314 = builder.CreateICmpUGT(val306, builder.getInt64(33554431ll), "");
    //   %315 = icmp slt i32 %313, -126
    Value *val315 = builder.CreateICmpSLT(val313, builder.getInt32(-126), "");
    //   %316 = select i1 %314, i1 true, i1 %315
    Value *val316 = builder.CreateSelect(val314, builder.getInt1(true), val315);
    //   br i1 %316, label %.preheader.i9, label %.loopexit.i8, !llvm.loop !10
    builder.CreateCondBr(val316, val_preheader_i9, val_loopexit_i8);
    builder.SetInsertPoint(val_loopexit_i8);
    //   %317 = icmp eq i8 %309, 0
    Value *val317 = builder.CreateICmpEQ(val309, builder.getInt8(0), "");
    //   br i1 %317, label %325, label %318
    builder.CreateCondBr(val317, val325, val318);
    builder.SetInsertPoint(val318);
    //   %319 = icmp sgt i32 %311, 1
    Value *val319 = builder.CreateICmpSGT(val311, builder.getInt32(1), "");
    //   %320 = and i64 %306, 2
    Value *val320 = builder.CreateAnd(val306, builder.getInt64(2ll), "");
    //   %321 = icmp ne i64 %320, 0
    Value *val321 = builder.CreateICmpNE(val320, builder.getInt64(0ll), "");
    //   %322 = or i1 %321, %319
    Value *val322 = builder.CreateOr(val321, val319, "");
    //   %323 = zext i1 %322 to i64
    Value *val323 = builder.CreateZExt(val322, Type::getInt64Ty(context));
    //   %324 = add nuw nsw i64 %312, %323
    Value *val324 = builder.CreateAdd(val312, val323, "", true, true);
    //   br label %325
    builder.CreateBr(val325);
    builder.SetInsertPoint(val325);
    //   %326 = phi i64 [ %312, %.loopexit.i8 ], [ %324, %318 ]
    PHINode *val326 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %327 = icmp ugt i64 %326, 16777215
    Value *val327 = builder.CreateICmpUGT(val326, builder.getInt64(16777215ll), "");
    //   %328 = zext i1 %327 to i32
    Value *val328 = builder.CreateZExt(val327, Type::getInt32Ty(context));
    //   %329 = add i32 %313, %328
    Value *val329 = builder.CreateAdd(val313, val328, "", false, false);
    //   %330 = icmp sgt i32 %329, 127
    Value *val330 = builder.CreateICmpSGT(val329, builder.getInt32(127), "");
    //   br i1 %330, label %build_float.exit10, label %331
    builder.CreateCondBr(val330, valbuild_float_exit10, val331);
    builder.SetInsertPoint(val331);
    //   %332 = select i1 %327, i64 8388608, i64 %326
    Value *val332 = builder.CreateSelect(val327, builder.getInt64(8388608ll), val326);
    //   %333 = icmp ugt i64 %332, 8388607
    Value *val333 = builder.CreateICmpUGT(val332, builder.getInt64(8388607ll), "");
    //   %334 = trunc i64 %332 to i32
    Value *val334 = builder.CreateTrunc(val332, Type::getInt32Ty(context));
    //   br i1 %333, label %335, label %build_float.exit10
    builder.CreateCondBr(val333, val335, valbuild_float_exit10);
    builder.SetInsertPoint(val335);
    //   %336 = and i32 %334, 8388607
    Value *val336 = builder.CreateAnd(val334, builder.getInt32(8388607), "");
    //   %337 = shl i32 %329, 23
    Value *val337 = builder.CreateShl(val329, builder.getInt32(23), "", false, false);
    //   %338 = add i32 %337, 1065353216
    Value *val338 = builder.CreateAdd(val337, builder.getInt32(1065353216), "", false, false);
    //   %339 = and i32 %338, 2139095040
    Value *val339 = builder.CreateAnd(val338, builder.getInt32(2139095040), "");
    //   %340 = or disjoint i32 %339, %336
    Value *val340 = builder.CreateOr(val339, val336, "");
    //   br label %build_float.exit10
    builder.CreateBr(valbuild_float_exit10);
    builder.SetInsertPoint(valbuild_float_exit10);
    //   %341 = phi i32 [ %340, %335 ], [ 2139095040, %325 ], [ %334, %331 ]
    PHINode *val341 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %342 = and i32 %283, 2139095040
    Value *val342 = builder.CreateAnd(val283, builder.getInt32(2139095040), "");
    //   %343 = icmp ne i32 %342, 2139095040
    Value *val343 = builder.CreateICmpNE(val342, builder.getInt32(2139095040), "");
    //   %344 = and i32 %283, 8388607
    Value *val344 = builder.CreateAnd(val283, builder.getInt32(8388607), "");
    //   %345 = icmp eq i32 %344, 0
    Value *val345 = builder.CreateICmpEQ(val344, builder.getInt32(0), "");
    //   %346 = or i1 %343, %345
    Value *val346 = builder.CreateOr(val343, val345, "");
    //   br i1 %346, label %347, label %f32_less.exit7
    builder.CreateCondBr(val346, val347, valf32_less_exit7);
    builder.SetInsertPoint(val347);
    //   %348 = and i32 %341, 2139095040
    Value *val348 = builder.CreateAnd(val341, builder.getInt32(2139095040), "");
    //   %349 = icmp ne i32 %348, 2139095040
    Value *val349 = builder.CreateICmpNE(val348, builder.getInt32(2139095040), "");
    //   %350 = and i32 %341, 8388607
    Value *val350 = builder.CreateAnd(val341, builder.getInt32(8388607), "");
    //   %351 = icmp eq i32 %350, 0
    Value *val351 = builder.CreateICmpEQ(val350, builder.getInt32(0), "");
    //   %352 = or i1 %349, %351
    Value *val352 = builder.CreateOr(val349, val351, "");
    //   br i1 %352, label %353, label %f32_less.exit7
    builder.CreateCondBr(val352, val353, valf32_less_exit7);
    builder.SetInsertPoint(val353);
    //   %354 = and i32 %283, 2147483647
    Value *val354 = builder.CreateAnd(val283, builder.getInt32(2147483647), "");
    //   %355 = icmp eq i32 %354, 2139095040
    Value *val355 = builder.CreateICmpEQ(val354, builder.getInt32(2139095040), "");
    //   %356 = and i32 %341, 2147483647
    Value *val356 = builder.CreateAnd(val341, builder.getInt32(2147483647), "");
    //   %357 = icmp eq i32 %356, 2139095040
    Value *val357 = builder.CreateICmpEQ(val356, builder.getInt32(2139095040), "");
    //   %358 = and i1 %355, %357
    Value *val358 = builder.CreateAnd(val355, val357, "");
    //   br i1 %358, label %359, label %362
    builder.CreateCondBr(val358, val359, val362);
    builder.SetInsertPoint(val359);
    //   %360 = xor i32 %341, %283
    Value *val360 = builder.CreateXor(val341, val283, "");
    //   %361 = icmp sgt i32 %360, -1
    Value *val361 = builder.CreateICmpSGT(val360, builder.getInt32(-1), "");
    //   br i1 %361, label %f32_less.exit7, label %368
    builder.CreateCondBr(val361, valf32_less_exit7, val368);
    builder.SetInsertPoint(val362);
    //   %363 = or i32 %341, %283
    Value *val363 = builder.CreateOr(val341, val283, "");
    //   %364 = and i32 %363, 2147483647
    Value *val364 = builder.CreateAnd(val363, builder.getInt32(2147483647), "");
    //   %365 = icmp eq i32 %364, 0
    Value *val365 = builder.CreateICmpEQ(val364, builder.getInt32(0), "");
    //   %366 = icmp eq i32 %283, %341
    Value *val366 = builder.CreateICmpEQ(val283, val341, "");
    //   %367 = or i1 %366, %365
    Value *val367 = builder.CreateOr(val366, val365, "");
    //   br i1 %367, label %f32_less.exit7, label %368
    builder.CreateCondBr(val367, valf32_less_exit7, val368);
    builder.SetInsertPoint(val368);
    //   %369 = lshr i32 %283, 31
    Value *val369 = builder.CreateLShr(val283, builder.getInt32(31), "", false);
    //   %370 = lshr i32 %341, 31
    Value *val370 = builder.CreateLShr(val341, builder.getInt32(31), "", false);
    //   %371 = icmp eq i32 %369, %370
    Value *val371 = builder.CreateICmpEQ(val369, val370, "");
    //   br i1 %371, label %375, label %372
    builder.CreateCondBr(val371, val375, val372);
    builder.SetInsertPoint(val372);
    //   %373 = icmp ugt i32 %369, %370
    Value *val373 = builder.CreateICmpUGT(val369, val370, "");
    //   %374 = zext i1 %373 to i8
    Value *val374 = builder.CreateZExt(val373, Type::getInt8Ty(context));
    //   br label %f32_less.exit7
    builder.CreateBr(valf32_less_exit7);
    builder.SetInsertPoint(val375);
    //   %376 = icmp ult i32 %283, %341
    Value *val376 = builder.CreateICmpULT(val283, val341, "");
    //   %377 = zext i1 %376 to i32
    Value *val377 = builder.CreateZExt(val376, Type::getInt32Ty(context));
    //   %378 = xor i32 %369, %377
    Value *val378 = builder.CreateXor(val369, val377, "");
    //   %379 = trunc i32 %378 to i8
    Value *val379 = builder.CreateTrunc(val378, Type::getInt8Ty(context));
    //   br label %f32_less.exit7
    builder.CreateBr(valf32_less_exit7);
    builder.SetInsertPoint(valf32_less_exit7);
    //   %380 = phi i8 [ 0, %362 ], [ 0, %347 ], [ 0, %build_float.exit10 ], [ %374, %372 ], [ %379, %375 ], [ 0, %359 ]
    PHINode *val380 = builder.CreatePHI(Type::getInt8Ty(context), 6);
    //   %381 = icmp eq i8 %380, 0
    Value *val381 = builder.CreateICmpEQ(val380, builder.getInt8(0), "");
    //   br i1 %381, label %23, label %382
    builder.CreateCondBr(val381, val23, val382);
    builder.SetInsertPoint(val382);
    //   %383 = zext nneg i32 %282 to i64
    Value *val383 = builder.CreateZExt(val282, Type::getInt64Ty(context));
    //   %384 = getelementptr i32, ptr %0, i64 %383
    Value *val384 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {val383});
    builder.Insert(val384);
    //   %385 = load i32, ptr %384, align 4, !tbaa !4
    Value *val385 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val384, MaybeAlign(4));
    //   %386 = and i32 %285, 2139095040
    Value *val386 = builder.CreateAnd(val285, builder.getInt32(2139095040), "");
    //   %387 = icmp ne i32 %386, 2139095040
    Value *val387 = builder.CreateICmpNE(val386, builder.getInt32(2139095040), "");
    //   %388 = and i32 %285, 8388607
    Value *val388 = builder.CreateAnd(val285, builder.getInt32(8388607), "");
    //   %389 = icmp eq i32 %388, 0
    Value *val389 = builder.CreateICmpEQ(val388, builder.getInt32(0), "");
    //   %390 = or i1 %387, %389
    Value *val390 = builder.CreateOr(val387, val389, "");
    //   %391 = xor i32 %285, -2147483648
    Value *val391 = builder.CreateXor(val285, builder.getInt32(-2147483648), "");
    //   %392 = select i1 %390, i32 %391, i32 %285
    Value *val392 = builder.CreateSelect(val390, val391, val285);
    //   %393 = tail call i32 @f32_add(i32 noundef %385, i32 noundef %392)
    Value *val393 = builder.CreateCall(funcf32_add, {val385, val392});
    //   %394 = getelementptr i32, ptr %1, i64 %383
    Value *val394 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {val383});
    builder.Insert(val394);
    //   %395 = load i32, ptr %394, align 4, !tbaa !4
    Value *val395 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val394, MaybeAlign(4));
    //   %396 = and i32 %287, 2139095040
    Value *val396 = builder.CreateAnd(val287, builder.getInt32(2139095040), "");
    //   %397 = icmp ne i32 %396, 2139095040
    Value *val397 = builder.CreateICmpNE(val396, builder.getInt32(2139095040), "");
    //   %398 = and i32 %287, 8388607
    Value *val398 = builder.CreateAnd(val287, builder.getInt32(8388607), "");
    //   %399 = icmp eq i32 %398, 0
    Value *val399 = builder.CreateICmpEQ(val398, builder.getInt32(0), "");
    //   %400 = or i1 %397, %399
    Value *val400 = builder.CreateOr(val397, val399, "");
    //   %401 = xor i32 %287, -2147483648
    Value *val401 = builder.CreateXor(val287, builder.getInt32(-2147483648), "");
    //   %402 = select i1 %400, i32 %401, i32 %287
    Value *val402 = builder.CreateSelect(val400, val401, val287);
    //   %403 = tail call i32 @f32_add(i32 noundef %395, i32 noundef %402)
    Value *val403 = builder.CreateCall(funcf32_add, {val395, val402});
    //   %404 = getelementptr i32, ptr %2, i64 %383
    Value *val404 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {val383});
    builder.Insert(val404);
    //   %405 = load i32, ptr %404, align 4, !tbaa !4
    Value *val405 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val404, MaybeAlign(4));
    //   %406 = and i32 %289, 2139095040
    Value *val406 = builder.CreateAnd(val289, builder.getInt32(2139095040), "");
    //   %407 = icmp ne i32 %406, 2139095040
    Value *val407 = builder.CreateICmpNE(val406, builder.getInt32(2139095040), "");
    //   %408 = and i32 %289, 8388607
    Value *val408 = builder.CreateAnd(val289, builder.getInt32(8388607), "");
    //   %409 = icmp eq i32 %408, 0
    Value *val409 = builder.CreateICmpEQ(val408, builder.getInt32(0), "");
    //   %410 = or i1 %407, %409
    Value *val410 = builder.CreateOr(val407, val409, "");
    //   %411 = xor i32 %289, -2147483648
    Value *val411 = builder.CreateXor(val289, builder.getInt32(-2147483648), "");
    //   %412 = select i1 %410, i32 %411, i32 %289
    Value *val412 = builder.CreateSelect(val410, val411, val289);
    //   %413 = tail call i32 @f32_add(i32 noundef %405, i32 noundef %412)
    Value *val413 = builder.CreateCall(funcf32_add, {val405, val412});
    //   %414 = tail call i32 @f32_mul(i32 noundef %393, i32 noundef %393) #9
    Value *val414 = builder.CreateCall(funcf32_mul, {val393, val393});
    //   %415 = tail call i32 @f32_mul(i32 noundef %403, i32 noundef %403) #9
    Value *val415 = builder.CreateCall(funcf32_mul, {val403, val403});
    //   %416 = tail call i32 @f32_add(i32 noundef %414, i32 noundef %415) #9
    Value *val416 = builder.CreateCall(funcf32_add, {val414, val415});
    //   %417 = tail call i32 @f32_mul(i32 noundef %413, i32 noundef %413) #9
    Value *val417 = builder.CreateCall(funcf32_mul, {val413, val413});
    //   %418 = tail call i32 @f32_add(i32 noundef %416, i32 noundef %417) #9
    Value *val418 = builder.CreateCall(funcf32_add, {val416, val417});
    //   %419 = tail call i32 @f32_div(i32 noundef %418, i32 noundef 1073741824) #9
    Value *val419 = builder.CreateCall(funcf32_div, {val418, builder.getInt32(1073741824)});
    //   %420 = lshr i32 %418, 1
    Value *val420 = builder.CreateLShr(val418, builder.getInt32(1), "", false);
    //   %421 = sub nsw i32 1597463007, %420
    Value *val421 = builder.CreateSub(builder.getInt32(1597463007), val420, "", false, true);
    //   %422 = tail call i32 @f32_mul(i32 noundef %421, i32 noundef %421) #9
    Value *val422 = builder.CreateCall(funcf32_mul, {val421, val421});
    //   %423 = tail call i32 @f32_mul(i32 noundef %419, i32 noundef %422) #9
    Value *val423 = builder.CreateCall(funcf32_mul, {val419, val422});
    //   %424 = and i32 %423, 2139095040
    Value *val424 = builder.CreateAnd(val423, builder.getInt32(2139095040), "");
    //   %425 = icmp ne i32 %424, 2139095040
    Value *val425 = builder.CreateICmpNE(val424, builder.getInt32(2139095040), "");
    //   %426 = and i32 %423, 8388607
    Value *val426 = builder.CreateAnd(val423, builder.getInt32(8388607), "");
    //   %427 = icmp eq i32 %426, 0
    Value *val427 = builder.CreateICmpEQ(val426, builder.getInt32(0), "");
    //   %428 = or i1 %425, %427
    Value *val428 = builder.CreateOr(val425, val427, "");
    //   %429 = xor i32 %423, -2147483648
    Value *val429 = builder.CreateXor(val423, builder.getInt32(-2147483648), "");
    //   %430 = select i1 %428, i32 %429, i32 %423
    Value *val430 = builder.CreateSelect(val428, val429, val423);
    //   %431 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %430)
    Value *val431 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val430});
    //   %432 = tail call i32 @f32_mul(i32 noundef %421, i32 noundef %431) #9
    Value *val432 = builder.CreateCall(funcf32_mul, {val421, val431});
    //   %433 = tail call i32 @f32_mul(i32 noundef %393, i32 noundef %432) #9
    Value *val433 = builder.CreateCall(funcf32_mul, {val393, val432});
    //   %434 = tail call i32 @f32_mul(i32 noundef %403, i32 noundef %432) #9
    Value *val434 = builder.CreateCall(funcf32_mul, {val403, val432});
    //   %435 = tail call i32 @f32_mul(i32 noundef %413, i32 noundef %432) #9
    Value *val435 = builder.CreateCall(funcf32_mul, {val413, val432});
    //   %436 = tail call i32 @f32_mul(i32 noundef %9, i32 noundef %433) #9
    Value *val436 = builder.CreateCall(funcf32_mul, {val9, val433});
    //   %437 = tail call i32 @f32_mul(i32 noundef %10, i32 noundef %434) #9
    Value *val437 = builder.CreateCall(funcf32_mul, {val10, val434});
    //   %438 = tail call i32 @f32_add(i32 noundef %436, i32 noundef %437) #9
    Value *val438 = builder.CreateCall(funcf32_add, {val436, val437});
    //   %439 = tail call i32 @f32_mul(i32 noundef %11, i32 noundef %435) #9
    Value *val439 = builder.CreateCall(funcf32_mul, {val11, val435});
    //   %440 = tail call i32 @f32_add(i32 noundef %438, i32 noundef %439) #9
    Value *val440 = builder.CreateCall(funcf32_add, {val438, val439});
    //   %441 = tail call i32 @f32_mul(i32 noundef 1073741824, i32 noundef %440) #9
    Value *val441 = builder.CreateCall(funcf32_mul, {builder.getInt32(1073741824), val440});
    //   %442 = tail call i32 @f32_mul(i32 noundef %441, i32 noundef %433) #9
    Value *val442 = builder.CreateCall(funcf32_mul, {val441, val433});
    //   %443 = and i32 %442, 2139095040
    Value *val443 = builder.CreateAnd(val442, builder.getInt32(2139095040), "");
    //   %444 = icmp ne i32 %443, 2139095040
    Value *val444 = builder.CreateICmpNE(val443, builder.getInt32(2139095040), "");
    //   %445 = and i32 %442, 8388607
    Value *val445 = builder.CreateAnd(val442, builder.getInt32(8388607), "");
    //   %446 = icmp eq i32 %445, 0
    Value *val446 = builder.CreateICmpEQ(val445, builder.getInt32(0), "");
    //   %447 = or i1 %444, %446
    Value *val447 = builder.CreateOr(val444, val446, "");
    //   %448 = xor i32 %442, -2147483648
    Value *val448 = builder.CreateXor(val442, builder.getInt32(-2147483648), "");
    //   %449 = select i1 %447, i32 %448, i32 %442
    Value *val449 = builder.CreateSelect(val447, val448, val442);
    //   %450 = tail call i32 @f32_add(i32 noundef %9, i32 noundef %449)
    Value *val450 = builder.CreateCall(funcf32_add, {val9, val449});
    //   %451 = tail call i32 @f32_mul(i32 noundef %441, i32 noundef %434) #9
    Value *val451 = builder.CreateCall(funcf32_mul, {val441, val434});
    //   %452 = and i32 %451, 2139095040
    Value *val452 = builder.CreateAnd(val451, builder.getInt32(2139095040), "");
    //   %453 = icmp ne i32 %452, 2139095040
    Value *val453 = builder.CreateICmpNE(val452, builder.getInt32(2139095040), "");
    //   %454 = and i32 %451, 8388607
    Value *val454 = builder.CreateAnd(val451, builder.getInt32(8388607), "");
    //   %455 = icmp eq i32 %454, 0
    Value *val455 = builder.CreateICmpEQ(val454, builder.getInt32(0), "");
    //   %456 = or i1 %453, %455
    Value *val456 = builder.CreateOr(val453, val455, "");
    //   %457 = xor i32 %451, -2147483648
    Value *val457 = builder.CreateXor(val451, builder.getInt32(-2147483648), "");
    //   %458 = select i1 %456, i32 %457, i32 %451
    Value *val458 = builder.CreateSelect(val456, val457, val451);
    //   %459 = tail call i32 @f32_add(i32 noundef %10, i32 noundef %458)
    Value *val459 = builder.CreateCall(funcf32_add, {val10, val458});
    //   %460 = tail call i32 @f32_mul(i32 noundef %441, i32 noundef %435) #9
    Value *val460 = builder.CreateCall(funcf32_mul, {val441, val435});
    //   %461 = and i32 %460, 2139095040
    Value *val461 = builder.CreateAnd(val460, builder.getInt32(2139095040), "");
    //   %462 = icmp ne i32 %461, 2139095040
    Value *val462 = builder.CreateICmpNE(val461, builder.getInt32(2139095040), "");
    //   %463 = and i32 %460, 8388607
    Value *val463 = builder.CreateAnd(val460, builder.getInt32(8388607), "");
    //   %464 = icmp eq i32 %463, 0
    Value *val464 = builder.CreateICmpEQ(val463, builder.getInt32(0), "");
    //   %465 = or i1 %462, %464
    Value *val465 = builder.CreateOr(val462, val464, "");
    //   %466 = xor i32 %460, -2147483648
    Value *val466 = builder.CreateXor(val460, builder.getInt32(-2147483648), "");
    //   %467 = select i1 %465, i32 %466, i32 %460
    Value *val467 = builder.CreateSelect(val465, val466, val460);
    //   %468 = tail call i32 @f32_add(i32 noundef %11, i32 noundef %467)
    Value *val468 = builder.CreateCall(funcf32_add, {val11, val467});
    //   %469 = icmp eq i32 %13, 0
    Value *val469 = builder.CreateICmpEQ(val13, builder.getInt32(0), "");
    //   br i1 %469, label %473, label %470
    builder.CreateCondBr(val469, val473, val470);
    builder.SetInsertPoint(val470);
    //   %471 = add i32 %13, -1
    Value *val471 = builder.CreateAdd(val13, builder.getInt32(-1), "", false, false);
    //   %472 = tail call i32 @ray_impl(ptr noundef nonnull %0, ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef nonnull %3, ptr noundef %4, ptr noundef %5, i32 noundef %285, i32 noundef %287, i32 noundef %289, i32 noundef %450, i32 noundef %459, i32 noundef %468, i32 noundef %28, i32 noundef %471), !range !11
    Value *val472 = builder.CreateCall(funcray_impl, {val0, val1, val2, val3, val4, val5, val285, val287, val289, val450, val459, val468, val28, val471});
    //   br label %473
    builder.CreateBr(val473);
    builder.SetInsertPoint(val473);
    //   %474 = phi i32 [ %472, %470 ], [ -1, %382 ]
    PHINode *val474 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %475 = getelementptr i32, ptr %5, i64 %383
    Value *val475 = GetElementPtrInst::Create(Type::getInt32Ty(context), val5, {val383});
    builder.Insert(val475);
    //   %476 = load i32, ptr %475, align 4, !tbaa !4
    Value *val476 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val475, MaybeAlign(4));
    //   %477 = getelementptr i32, ptr %4, i64 %383
    Value *val477 = GetElementPtrInst::Create(Type::getInt32Ty(context), val4, {val383});
    builder.Insert(val477);
    //   %478 = load i32, ptr %477, align 4, !tbaa !4
    Value *val478 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val477, MaybeAlign(4));
    //   %479 = tail call i32 @reflection(i32 noundef %476, i32 noundef %474, i32 noundef %478)
    Value *val479 = builder.CreateCall(funcreflection, {val476, val474, val478});
    //   %480 = tail call i32 @combine(i32 noundef %479, i32 noundef 12303291, i32 noundef %440), !range !12
    Value *val480 = builder.CreateCall(funccombine, {val479, builder.getInt32(12303291), val440});
    //   br label %.loopexit
    builder.CreateBr(val_loopexit);
    builder.SetInsertPoint(val_loopexit);
    //   %481 = phi i32 [ %480, %473 ], [ -1, %23 ]
    PHINode *val481 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   ret i32 %481
    builder.CreateRet(val481);
    val24->addIncoming(val12, val14);
    val24->addIncoming(val28, valf32_less_exit7);
    val25->addIncoming(val8, val14);
    val25->addIncoming(val289, valf32_less_exit7);
    val26->addIncoming(val7, val14);
    val26->addIncoming(val287, valf32_less_exit7);
    val27->addIncoming(val6, val14);
    val27->addIncoming(val285, valf32_less_exit7);
    val102->addIncoming(builder.getInt32(1203982336), valbuild_float_exit);
    val102->addIncoming(val_, valf32_less_exit_thread11);
    val181->addIncoming(val175, val173);
    val181->addIncoming(val180, val176);
    val191->addIncoming(builder.getInt32(0), valf32_less_exit2);
    val191->addIncoming(builder.getInt32(0), val163);
    val191->addIncoming(builder.getInt32(0), val148);
    val191->addIncoming(builder.getInt32(0), valf32_less_exit_thread);
    val191->addIncoming(builder.getInt32(0), val160);
    val191->addIncoming(valspec_select, val183);
    val192->addIncoming(val102, valf32_less_exit2);
    val192->addIncoming(val102, val163);
    val192->addIncoming(val102, val148);
    val192->addIncoming(val102, valf32_less_exit_thread);
    val192->addIncoming(val102, val160);
    val192->addIncoming(valspec_select42, val183);
    val271->addIncoming(val265, val263);
    val271->addIncoming(val270, val266);
    val282->addIncoming(val191, valf32_less_exit4);
    val282->addIncoming(val280, valf32_less_exit5);
    val282->addIncoming(val191, val253);
    val282->addIncoming(val191, val238);
    val282->addIncoming(val191, valf32_less_exit2_thread);
    val282->addIncoming(val191, val250);
    val283->addIncoming(val192, valf32_less_exit4);
    val283->addIncoming(val281, valf32_less_exit5);
    val283->addIncoming(val192, val253);
    val283->addIncoming(val192, val238);
    val283->addIncoming(val192, valf32_less_exit2_thread);
    val283->addIncoming(val192, val250);
    val291->addIncoming(builder.getInt64(8388608ll), valf32_less_exit4_thread);
    val291->addIncoming(val299, val290);
    val292->addIncoming(builder.getInt64(0ll), valf32_less_exit4_thread);
    val292->addIncoming(val298, val290);
    val293->addIncoming(builder.getInt32(17), valf32_less_exit4_thread);
    val293->addIncoming(val295, val290);
    val305->addIncoming(val311, val_preheader_i9);
    val305->addIncoming(val304, valf32_div_exit6);
    val306->addIncoming(val312, val_preheader_i9);
    val306->addIncoming(val298, valf32_div_exit6);
    val307->addIncoming(val313, val_preheader_i9);
    val307->addIncoming(val295, valf32_div_exit6);
    val326->addIncoming(val312, val_loopexit_i8);
    val326->addIncoming(val324, val318);
    val341->addIncoming(val340, val335);
    val341->addIncoming(builder.getInt32(2139095040), val325);
    val341->addIncoming(val334, val331);
    val380->addIncoming(builder.getInt8(0), val362);
    val380->addIncoming(builder.getInt8(0), val347);
    val380->addIncoming(builder.getInt8(0), valbuild_float_exit10);
    val380->addIncoming(val374, val372);
    val380->addIncoming(val379, val375);
    val380->addIncoming(builder.getInt8(0), val359);
    val474->addIncoming(val472, val470);
    val474->addIncoming(builder.getInt32(-1), val382);
    val481->addIncoming(val480, val473);
    val481->addIncoming(builder.getInt32(-1), val23);
  }
  {
    Function *func = funcray;
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val10 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i = BasicBlock::Create(context, "", func);
    BasicBlock *val32 = BasicBlock::Create(context, "", func);
    BasicBlock *val34 = BasicBlock::Create(context, "", func);
    BasicBlock *val41 = BasicBlock::Create(context, "", func);
    BasicBlock *val48 = BasicBlock::Create(context, "", func);
    BasicBlock *val50 = BasicBlock::Create(context, "", func);
    BasicBlock *val54 = BasicBlock::Create(context, "", func);
    BasicBlock *val61 = BasicBlock::Create(context, "", func);
    BasicBlock *val63 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val68 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i1 = BasicBlock::Create(context, "", func);
    BasicBlock *val91 = BasicBlock::Create(context, "", func);
    BasicBlock *val93 = BasicBlock::Create(context, "", func);
    BasicBlock *val100 = BasicBlock::Create(context, "", func);
    BasicBlock *val107 = BasicBlock::Create(context, "", func);
    BasicBlock *val109 = BasicBlock::Create(context, "", func);
    BasicBlock *val113 = BasicBlock::Create(context, "", func);
    BasicBlock *val120 = BasicBlock::Create(context, "", func);
    BasicBlock *val122 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit2 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i3 = BasicBlock::Create(context, "", func);
    BasicBlock *val139 = BasicBlock::Create(context, "", func);
    BasicBlock *val141 = BasicBlock::Create(context, "", func);
    BasicBlock *val148 = BasicBlock::Create(context, "", func);
    BasicBlock *val154 = BasicBlock::Create(context, "", func);
    BasicBlock *val158 = BasicBlock::Create(context, "", func);
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    Value *val4 = func->getArg(4);
    Value *val5 = func->getArg(5);
    Value *val6 = func->getArg(6);
    Value *val7 = func->getArg(7);
    builder.SetInsertPoint(val8);
    //   %9 = add i32 %6, -250
    Value *val9 = builder.CreateAdd(val6, builder.getInt32(-250), "", false, false);
    //   %cond = icmp eq i32 %9, 0
    Value *valcond = builder.CreateICmpEQ(val9, builder.getInt32(0), "");
    //   br i1 %cond, label %f32_from_ll.exit, label %10
    builder.CreateCondBr(valcond, valf32_from_ll_exit, val10);
    builder.SetInsertPoint(val10);
    //   %11 = sext i32 %9 to i64
    Value *val11 = builder.CreateSExt(val9, Type::getInt64Ty(context));
    //   %12 = tail call i64 @llvm.abs.i64(i64 %11, i1 true)
    Value *val12 = builder.CreateCall(funcllvm_abs_i64, {val11, builder.getInt1(true)});
    //   %13 = icmp ult i64 %12, 16777216
    Value *val13 = builder.CreateICmpULT(val12, builder.getInt64(16777216ll), "");
    //   %14 = shl nuw nsw i64 %12, 24
    Value *val14 = builder.CreateShl(val12, builder.getInt64(24ll), "", true, true);
    //   %15 = select i1 %13, i64 %14, i64 %12
    Value *val15 = builder.CreateSelect(val13, val14, val12);
    //   %16 = select i1 %13, i32 -1, i32 23
    Value *val16 = builder.CreateSelect(val13, builder.getInt32(-1), builder.getInt32(23));
    //   %17 = lshr i64 %11, 63
    Value *val17 = builder.CreateLShr(val11, builder.getInt64(63ll), "", false);
    //   %18 = trunc i64 %17 to i32
    Value *val18 = builder.CreateTrunc(val17, Type::getInt32Ty(context));
    //   %19 = icmp ugt i64 %15, 16777215
    Value *val19 = builder.CreateICmpUGT(val15, builder.getInt64(16777215ll), "");
    //   br i1 %19, label %.preheader.i, label %41
    builder.CreateCondBr(val19, val_preheader_i, val41);
    builder.SetInsertPoint(val_preheader_i);
    //   %20 = phi i32 [ %26, %.preheader.i ], [ 0, %10 ]
    PHINode *val20 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %21 = phi i64 [ %27, %.preheader.i ], [ %15, %10 ]
    PHINode *val21 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %22 = phi i32 [ %28, %.preheader.i ], [ %16, %10 ]
    PHINode *val22 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %23 = trunc i64 %21 to i8
    Value *val23 = builder.CreateTrunc(val21, Type::getInt8Ty(context));
    //   %24 = and i8 %23, 1
    Value *val24 = builder.CreateAnd(val23, builder.getInt8(1), "");
    //   %25 = zext nneg i8 %24 to i32
    Value *val25 = builder.CreateZExt(val24, Type::getInt32Ty(context));
    //   %26 = add i32 %20, %25
    Value *val26 = builder.CreateAdd(val20, val25, "", false, false);
    //   %27 = lshr i64 %21, 1
    Value *val27 = builder.CreateLShr(val21, builder.getInt64(1ll), "", false);
    //   %28 = add i32 %22, 1
    Value *val28 = builder.CreateAdd(val22, builder.getInt32(1), "", false, false);
    //   %29 = icmp ugt i64 %21, 33554431
    Value *val29 = builder.CreateICmpUGT(val21, builder.getInt64(33554431ll), "");
    //   %30 = icmp slt i32 %28, -126
    Value *val30 = builder.CreateICmpSLT(val28, builder.getInt32(-126), "");
    //   %31 = select i1 %29, i1 true, i1 %30
    Value *val31 = builder.CreateSelect(val29, builder.getInt1(true), val30);
    //   br i1 %31, label %.preheader.i, label %32, !llvm.loop !4
    builder.CreateCondBr(val31, val_preheader_i, val32);
    builder.SetInsertPoint(val32);
    //   %33 = icmp eq i8 %24, 0
    Value *val33 = builder.CreateICmpEQ(val24, builder.getInt8(0), "");
    //   br i1 %33, label %41, label %34
    builder.CreateCondBr(val33, val41, val34);
    builder.SetInsertPoint(val34);
    //   %35 = icmp sgt i32 %26, 1
    Value *val35 = builder.CreateICmpSGT(val26, builder.getInt32(1), "");
    //   %36 = and i64 %21, 2
    Value *val36 = builder.CreateAnd(val21, builder.getInt64(2ll), "");
    //   %37 = icmp ne i64 %36, 0
    Value *val37 = builder.CreateICmpNE(val36, builder.getInt64(0ll), "");
    //   %38 = or i1 %37, %35
    Value *val38 = builder.CreateOr(val37, val35, "");
    //   %39 = zext i1 %38 to i64
    Value *val39 = builder.CreateZExt(val38, Type::getInt64Ty(context));
    //   %40 = add nuw nsw i64 %27, %39
    Value *val40 = builder.CreateAdd(val27, val39, "", true, true);
    //   br label %41
    builder.CreateBr(val41);
    builder.SetInsertPoint(val41);
    //   %42 = phi i32 [ %28, %32 ], [ %28, %34 ], [ %16, %10 ]
    PHINode *val42 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %43 = phi i64 [ %27, %32 ], [ %40, %34 ], [ %15, %10 ]
    PHINode *val43 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %44 = icmp ugt i64 %43, 16777215
    Value *val44 = builder.CreateICmpUGT(val43, builder.getInt64(16777215ll), "");
    //   %45 = zext i1 %44 to i32
    Value *val45 = builder.CreateZExt(val44, Type::getInt32Ty(context));
    //   %46 = add i32 %42, %45
    Value *val46 = builder.CreateAdd(val42, val45, "", false, false);
    //   %47 = icmp sgt i32 %46, 127
    Value *val47 = builder.CreateICmpSGT(val46, builder.getInt32(127), "");
    //   br i1 %47, label %48, label %50
    builder.CreateCondBr(val47, val48, val50);
    builder.SetInsertPoint(val48);
    //   %49 = shl nuw i32 %18, 31
    Value *val49 = builder.CreateShl(val18, builder.getInt32(31), "", true, false);
    //   br label %63
    builder.CreateBr(val63);
    builder.SetInsertPoint(val50);
    //   %51 = select i1 %44, i64 8388608, i64 %43
    Value *val51 = builder.CreateSelect(val44, builder.getInt64(8388608ll), val43);
    //   %52 = icmp ugt i64 %51, 8388607
    Value *val52 = builder.CreateICmpUGT(val51, builder.getInt64(8388607ll), "");
    //   %53 = trunc i64 %51 to i32
    Value *val53 = builder.CreateTrunc(val51, Type::getInt32Ty(context));
    //   br i1 %52, label %54, label %61
    builder.CreateCondBr(val52, val54, val61);
    builder.SetInsertPoint(val54);
    //   %55 = and i32 %53, 8388607
    Value *val55 = builder.CreateAnd(val53, builder.getInt32(8388607), "");
    //   %56 = shl i32 %46, 23
    Value *val56 = builder.CreateShl(val46, builder.getInt32(23), "", false, false);
    //   %57 = add i32 %56, 1065353216
    Value *val57 = builder.CreateAdd(val56, builder.getInt32(1065353216), "", false, false);
    //   %58 = and i32 %57, 2139095040
    Value *val58 = builder.CreateAnd(val57, builder.getInt32(2139095040), "");
    //   %59 = or disjoint i32 %58, %55
    Value *val59 = builder.CreateOr(val58, val55, "");
    //   %60 = shl nuw i32 %18, 31
    Value *val60 = builder.CreateShl(val18, builder.getInt32(31), "", true, false);
    //   br label %63
    builder.CreateBr(val63);
    builder.SetInsertPoint(val61);
    //   %62 = shl nuw i32 %18, 31
    Value *val62 = builder.CreateShl(val18, builder.getInt32(31), "", true, false);
    //   br label %63
    builder.CreateBr(val63);
    builder.SetInsertPoint(val63);
    //   %64 = phi i32 [ %53, %61 ], [ %60, %54 ], [ 2139095040, %48 ]
    PHINode *val64 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %65 = phi i32 [ %62, %61 ], [ %59, %54 ], [ %49, %48 ]
    PHINode *val65 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %66 = or disjoint i32 %65, %64
    Value *val66 = builder.CreateOr(val65, val64, "");
    //   br label %f32_from_ll.exit
    builder.CreateBr(valf32_from_ll_exit);
    builder.SetInsertPoint(valf32_from_ll_exit);
    //   %67 = phi i32 [ %66, %63 ], [ 0, %8 ]
    PHINode *val67 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %cond6 = icmp eq i32 %7, 250
    Value *valcond6 = builder.CreateICmpEQ(val7, builder.getInt32(250), "");
    //   br i1 %cond6, label %f32_from_ll.exit2, label %68
    builder.CreateCondBr(valcond6, valf32_from_ll_exit2, val68);
    builder.SetInsertPoint(val68);
    //   %69 = sub i32 250, %7
    Value *val69 = builder.CreateSub(builder.getInt32(250), val7, "", false, false);
    //   %70 = sext i32 %69 to i64
    Value *val70 = builder.CreateSExt(val69, Type::getInt64Ty(context));
    //   %71 = tail call i64 @llvm.abs.i64(i64 %70, i1 true)
    Value *val71 = builder.CreateCall(funcllvm_abs_i64, {val70, builder.getInt1(true)});
    //   %72 = icmp ult i64 %71, 16777216
    Value *val72 = builder.CreateICmpULT(val71, builder.getInt64(16777216ll), "");
    //   %73 = shl nuw nsw i64 %71, 24
    Value *val73 = builder.CreateShl(val71, builder.getInt64(24ll), "", true, true);
    //   %74 = select i1 %72, i64 %73, i64 %71
    Value *val74 = builder.CreateSelect(val72, val73, val71);
    //   %75 = select i1 %72, i32 -1, i32 23
    Value *val75 = builder.CreateSelect(val72, builder.getInt32(-1), builder.getInt32(23));
    //   %76 = lshr i64 %70, 63
    Value *val76 = builder.CreateLShr(val70, builder.getInt64(63ll), "", false);
    //   %77 = trunc i64 %76 to i32
    Value *val77 = builder.CreateTrunc(val76, Type::getInt32Ty(context));
    //   %78 = icmp ugt i64 %74, 16777215
    Value *val78 = builder.CreateICmpUGT(val74, builder.getInt64(16777215ll), "");
    //   br i1 %78, label %.preheader.i1, label %100
    builder.CreateCondBr(val78, val_preheader_i1, val100);
    builder.SetInsertPoint(val_preheader_i1);
    //   %79 = phi i32 [ %85, %.preheader.i1 ], [ 0, %68 ]
    PHINode *val79 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %80 = phi i64 [ %86, %.preheader.i1 ], [ %74, %68 ]
    PHINode *val80 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %81 = phi i32 [ %87, %.preheader.i1 ], [ %75, %68 ]
    PHINode *val81 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %82 = trunc i64 %80 to i8
    Value *val82 = builder.CreateTrunc(val80, Type::getInt8Ty(context));
    //   %83 = and i8 %82, 1
    Value *val83 = builder.CreateAnd(val82, builder.getInt8(1), "");
    //   %84 = zext nneg i8 %83 to i32
    Value *val84 = builder.CreateZExt(val83, Type::getInt32Ty(context));
    //   %85 = add i32 %79, %84
    Value *val85 = builder.CreateAdd(val79, val84, "", false, false);
    //   %86 = lshr i64 %80, 1
    Value *val86 = builder.CreateLShr(val80, builder.getInt64(1ll), "", false);
    //   %87 = add i32 %81, 1
    Value *val87 = builder.CreateAdd(val81, builder.getInt32(1), "", false, false);
    //   %88 = icmp ugt i64 %80, 33554431
    Value *val88 = builder.CreateICmpUGT(val80, builder.getInt64(33554431ll), "");
    //   %89 = icmp slt i32 %87, -126
    Value *val89 = builder.CreateICmpSLT(val87, builder.getInt32(-126), "");
    //   %90 = select i1 %88, i1 true, i1 %89
    Value *val90 = builder.CreateSelect(val88, builder.getInt1(true), val89);
    //   br i1 %90, label %.preheader.i1, label %91, !llvm.loop !4
    builder.CreateCondBr(val90, val_preheader_i1, val91);
    builder.SetInsertPoint(val91);
    //   %92 = icmp eq i8 %83, 0
    Value *val92 = builder.CreateICmpEQ(val83, builder.getInt8(0), "");
    //   br i1 %92, label %100, label %93
    builder.CreateCondBr(val92, val100, val93);
    builder.SetInsertPoint(val93);
    //   %94 = icmp sgt i32 %85, 1
    Value *val94 = builder.CreateICmpSGT(val85, builder.getInt32(1), "");
    //   %95 = and i64 %80, 2
    Value *val95 = builder.CreateAnd(val80, builder.getInt64(2ll), "");
    //   %96 = icmp ne i64 %95, 0
    Value *val96 = builder.CreateICmpNE(val95, builder.getInt64(0ll), "");
    //   %97 = or i1 %96, %94
    Value *val97 = builder.CreateOr(val96, val94, "");
    //   %98 = zext i1 %97 to i64
    Value *val98 = builder.CreateZExt(val97, Type::getInt64Ty(context));
    //   %99 = add nuw nsw i64 %86, %98
    Value *val99 = builder.CreateAdd(val86, val98, "", true, true);
    //   br label %100
    builder.CreateBr(val100);
    builder.SetInsertPoint(val100);
    //   %101 = phi i32 [ %87, %91 ], [ %87, %93 ], [ %75, %68 ]
    PHINode *val101 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %102 = phi i64 [ %86, %91 ], [ %99, %93 ], [ %74, %68 ]
    PHINode *val102 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %103 = icmp ugt i64 %102, 16777215
    Value *val103 = builder.CreateICmpUGT(val102, builder.getInt64(16777215ll), "");
    //   %104 = zext i1 %103 to i32
    Value *val104 = builder.CreateZExt(val103, Type::getInt32Ty(context));
    //   %105 = add i32 %101, %104
    Value *val105 = builder.CreateAdd(val101, val104, "", false, false);
    //   %106 = icmp sgt i32 %105, 127
    Value *val106 = builder.CreateICmpSGT(val105, builder.getInt32(127), "");
    //   br i1 %106, label %107, label %109
    builder.CreateCondBr(val106, val107, val109);
    builder.SetInsertPoint(val107);
    //   %108 = shl nuw i32 %77, 31
    Value *val108 = builder.CreateShl(val77, builder.getInt32(31), "", true, false);
    //   br label %122
    builder.CreateBr(val122);
    builder.SetInsertPoint(val109);
    //   %110 = select i1 %103, i64 8388608, i64 %102
    Value *val110 = builder.CreateSelect(val103, builder.getInt64(8388608ll), val102);
    //   %111 = icmp ugt i64 %110, 8388607
    Value *val111 = builder.CreateICmpUGT(val110, builder.getInt64(8388607ll), "");
    //   %112 = trunc i64 %110 to i32
    Value *val112 = builder.CreateTrunc(val110, Type::getInt32Ty(context));
    //   br i1 %111, label %113, label %120
    builder.CreateCondBr(val111, val113, val120);
    builder.SetInsertPoint(val113);
    //   %114 = and i32 %112, 8388607
    Value *val114 = builder.CreateAnd(val112, builder.getInt32(8388607), "");
    //   %115 = shl i32 %105, 23
    Value *val115 = builder.CreateShl(val105, builder.getInt32(23), "", false, false);
    //   %116 = add i32 %115, 1065353216
    Value *val116 = builder.CreateAdd(val115, builder.getInt32(1065353216), "", false, false);
    //   %117 = and i32 %116, 2139095040
    Value *val117 = builder.CreateAnd(val116, builder.getInt32(2139095040), "");
    //   %118 = or disjoint i32 %117, %114
    Value *val118 = builder.CreateOr(val117, val114, "");
    //   %119 = shl nuw i32 %77, 31
    Value *val119 = builder.CreateShl(val77, builder.getInt32(31), "", true, false);
    //   br label %122
    builder.CreateBr(val122);
    builder.SetInsertPoint(val120);
    //   %121 = shl nuw i32 %77, 31
    Value *val121 = builder.CreateShl(val77, builder.getInt32(31), "", true, false);
    //   br label %122
    builder.CreateBr(val122);
    builder.SetInsertPoint(val122);
    //   %123 = phi i32 [ %112, %120 ], [ %119, %113 ], [ 2139095040, %107 ]
    PHINode *val123 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %124 = phi i32 [ %121, %120 ], [ %118, %113 ], [ %108, %107 ]
    PHINode *val124 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %125 = or disjoint i32 %124, %123
    Value *val125 = builder.CreateOr(val124, val123, "");
    //   br label %f32_from_ll.exit2
    builder.CreateBr(valf32_from_ll_exit2);
    builder.SetInsertPoint(valf32_from_ll_exit2);
    //   %126 = phi i32 [ %125, %122 ], [ 0, %f32_from_ll.exit ]
    PHINode *val126 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   br label %.preheader.i3
    builder.CreateBr(val_preheader_i3);
    builder.SetInsertPoint(val_preheader_i3);
    //   %127 = phi i32 [ %133, %.preheader.i3 ], [ 0, %f32_from_ll.exit2 ]
    PHINode *val127 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %128 = phi i64 [ %134, %.preheader.i3 ], [ 3355443200, %f32_from_ll.exit2 ]
    PHINode *val128 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %129 = phi i32 [ %135, %.preheader.i3 ], [ -1, %f32_from_ll.exit2 ]
    PHINode *val129 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %130 = trunc i64 %128 to i8
    Value *val130 = builder.CreateTrunc(val128, Type::getInt8Ty(context));
    //   %131 = and i8 %130, 1
    Value *val131 = builder.CreateAnd(val130, builder.getInt8(1), "");
    //   %132 = zext nneg i8 %131 to i32
    Value *val132 = builder.CreateZExt(val131, Type::getInt32Ty(context));
    //   %133 = add i32 %127, %132
    Value *val133 = builder.CreateAdd(val127, val132, "", false, false);
    //   %134 = lshr i64 %128, 1
    Value *val134 = builder.CreateLShr(val128, builder.getInt64(1ll), "", false);
    //   %135 = add i32 %129, 1
    Value *val135 = builder.CreateAdd(val129, builder.getInt32(1), "", false, false);
    //   %136 = icmp ugt i64 %128, 33554431
    Value *val136 = builder.CreateICmpUGT(val128, builder.getInt64(33554431ll), "");
    //   %137 = icmp slt i32 %135, -126
    Value *val137 = builder.CreateICmpSLT(val135, builder.getInt32(-126), "");
    //   %138 = select i1 %136, i1 true, i1 %137
    Value *val138 = builder.CreateSelect(val136, builder.getInt1(true), val137);
    //   br i1 %138, label %.preheader.i3, label %139, !llvm.loop !4
    builder.CreateCondBr(val138, val_preheader_i3, val139);
    builder.SetInsertPoint(val139);
    //   %140 = icmp eq i8 %131, 0
    Value *val140 = builder.CreateICmpEQ(val131, builder.getInt8(0), "");
    //   br i1 %140, label %148, label %141
    builder.CreateCondBr(val140, val148, val141);
    builder.SetInsertPoint(val141);
    //   %142 = icmp sgt i32 %133, 1
    Value *val142 = builder.CreateICmpSGT(val133, builder.getInt32(1), "");
    //   %143 = and i64 %128, 2
    Value *val143 = builder.CreateAnd(val128, builder.getInt64(2ll), "");
    //   %144 = icmp ne i64 %143, 0
    Value *val144 = builder.CreateICmpNE(val143, builder.getInt64(0ll), "");
    //   %145 = or i1 %144, %142
    Value *val145 = builder.CreateOr(val144, val142, "");
    //   %146 = zext i1 %145 to i64
    Value *val146 = builder.CreateZExt(val145, Type::getInt64Ty(context));
    //   %147 = add nuw nsw i64 %134, %146
    Value *val147 = builder.CreateAdd(val134, val146, "", true, true);
    //   br label %148
    builder.CreateBr(val148);
    builder.SetInsertPoint(val148);
    //   %149 = phi i64 [ %134, %139 ], [ %147, %141 ]
    PHINode *val149 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %150 = icmp ugt i64 %149, 16777215
    Value *val150 = builder.CreateICmpUGT(val149, builder.getInt64(16777215ll), "");
    //   %151 = zext i1 %150 to i32
    Value *val151 = builder.CreateZExt(val150, Type::getInt32Ty(context));
    //   %152 = add i32 %135, %151
    Value *val152 = builder.CreateAdd(val135, val151, "", false, false);
    //   %153 = icmp sgt i32 %152, 127
    Value *val153 = builder.CreateICmpSGT(val152, builder.getInt32(127), "");
    //   br i1 %153, label %build_float.exit, label %154
    builder.CreateCondBr(val153, valbuild_float_exit, val154);
    builder.SetInsertPoint(val154);
    //   %155 = select i1 %150, i64 8388608, i64 %149
    Value *val155 = builder.CreateSelect(val150, builder.getInt64(8388608ll), val149);
    //   %156 = icmp ugt i64 %155, 8388607
    Value *val156 = builder.CreateICmpUGT(val155, builder.getInt64(8388607ll), "");
    //   %157 = trunc i64 %155 to i32
    Value *val157 = builder.CreateTrunc(val155, Type::getInt32Ty(context));
    //   br i1 %156, label %158, label %build_float.exit
    builder.CreateCondBr(val156, val158, valbuild_float_exit);
    builder.SetInsertPoint(val158);
    //   %159 = and i32 %157, 8388607
    Value *val159 = builder.CreateAnd(val157, builder.getInt32(8388607), "");
    //   %160 = shl i32 %152, 23
    Value *val160 = builder.CreateShl(val152, builder.getInt32(23), "", false, false);
    //   %161 = add i32 %160, 1065353216
    Value *val161 = builder.CreateAdd(val160, builder.getInt32(1065353216), "", false, false);
    //   %162 = and i32 %161, 2139095040
    Value *val162 = builder.CreateAnd(val161, builder.getInt32(2139095040), "");
    //   %163 = or disjoint i32 %162, %159
    Value *val163 = builder.CreateOr(val162, val159, "");
    //   br label %build_float.exit
    builder.CreateBr(valbuild_float_exit);
    builder.SetInsertPoint(valbuild_float_exit);
    //   %164 = phi i32 [ %163, %158 ], [ 2139095040, %148 ], [ %157, %154 ]
    PHINode *val164 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %165 = tail call i32 @f32_mul(i32 noundef %67, i32 noundef %67) #9
    Value *val165 = builder.CreateCall(funcf32_mul, {val67, val67});
    //   %166 = tail call i32 @f32_mul(i32 noundef %126, i32 noundef %126) #9
    Value *val166 = builder.CreateCall(funcf32_mul, {val126, val126});
    //   %167 = tail call i32 @f32_add(i32 noundef %165, i32 noundef %166) #9
    Value *val167 = builder.CreateCall(funcf32_add, {val165, val166});
    //   %168 = tail call i32 @f32_mul(i32 noundef %164, i32 noundef %164) #9
    Value *val168 = builder.CreateCall(funcf32_mul, {val164, val164});
    //   %169 = tail call i32 @f32_add(i32 noundef %167, i32 noundef %168) #9
    Value *val169 = builder.CreateCall(funcf32_add, {val167, val168});
    //   %170 = tail call i32 @f32_div(i32 noundef %169, i32 noundef 1073741824) #9
    Value *val170 = builder.CreateCall(funcf32_div, {val169, builder.getInt32(1073741824)});
    //   %171 = lshr i32 %169, 1
    Value *val171 = builder.CreateLShr(val169, builder.getInt32(1), "", false);
    //   %172 = sub nsw i32 1597463007, %171
    Value *val172 = builder.CreateSub(builder.getInt32(1597463007), val171, "", false, true);
    //   %173 = tail call i32 @f32_mul(i32 noundef %172, i32 noundef %172) #9
    Value *val173 = builder.CreateCall(funcf32_mul, {val172, val172});
    //   %174 = tail call i32 @f32_mul(i32 noundef %170, i32 noundef %173) #9
    Value *val174 = builder.CreateCall(funcf32_mul, {val170, val173});
    //   %175 = and i32 %174, 2139095040
    Value *val175 = builder.CreateAnd(val174, builder.getInt32(2139095040), "");
    //   %176 = icmp ne i32 %175, 2139095040
    Value *val176 = builder.CreateICmpNE(val175, builder.getInt32(2139095040), "");
    //   %177 = and i32 %174, 8388607
    Value *val177 = builder.CreateAnd(val174, builder.getInt32(8388607), "");
    //   %178 = icmp eq i32 %177, 0
    Value *val178 = builder.CreateICmpEQ(val177, builder.getInt32(0), "");
    //   %179 = or i1 %176, %178
    Value *val179 = builder.CreateOr(val176, val178, "");
    //   %180 = xor i32 %174, -2147483648
    Value *val180 = builder.CreateXor(val174, builder.getInt32(-2147483648), "");
    //   %181 = select i1 %179, i32 %180, i32 %174
    Value *val181 = builder.CreateSelect(val179, val180, val174);
    //   %182 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %181)
    Value *val182 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val181});
    //   %183 = tail call i32 @f32_mul(i32 noundef %172, i32 noundef %182) #9
    Value *val183 = builder.CreateCall(funcf32_mul, {val172, val182});
    //   %184 = tail call i32 @f32_mul(i32 noundef %67, i32 noundef %183) #9
    Value *val184 = builder.CreateCall(funcf32_mul, {val67, val183});
    //   %185 = tail call i32 @f32_mul(i32 noundef %126, i32 noundef %183) #9
    Value *val185 = builder.CreateCall(funcf32_mul, {val126, val183});
    //   %186 = tail call i32 @f32_mul(i32 noundef %164, i32 noundef %183) #9
    Value *val186 = builder.CreateCall(funcf32_mul, {val164, val183});
    //   %187 = tail call i32 @ray_impl(ptr noundef %0, ptr noundef %1, ptr noundef %2, ptr noundef %3, ptr noundef %4, ptr noundef %5, i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %184, i32 noundef %185, i32 noundef %186, i32 noundef 20, i32 noundef 10), !range !6
    Value *val187 = builder.CreateCall(funcray_impl, {val0, val1, val2, val3, val4, val5, builder.getInt32(0), builder.getInt32(0), builder.getInt32(0), val184, val185, val186, builder.getInt32(20), builder.getInt32(10)});
    //   %188 = icmp eq i32 %187, -1
    Value *val188 = builder.CreateICmpEQ(val187, builder.getInt32(-1), "");
    //   %189 = select i1 %188, i32 12303291, i32 %187
    Value *val189 = builder.CreateSelect(val188, builder.getInt32(12303291), val187);
    //   ret i32 %189
    builder.CreateRet(val189);
    val20->addIncoming(val26, val_preheader_i);
    val20->addIncoming(builder.getInt32(0), val10);
    val21->addIncoming(val27, val_preheader_i);
    val21->addIncoming(val15, val10);
    val22->addIncoming(val28, val_preheader_i);
    val22->addIncoming(val16, val10);
    val42->addIncoming(val28, val32);
    val42->addIncoming(val28, val34);
    val42->addIncoming(val16, val10);
    val43->addIncoming(val27, val32);
    val43->addIncoming(val40, val34);
    val43->addIncoming(val15, val10);
    val64->addIncoming(val53, val61);
    val64->addIncoming(val60, val54);
    val64->addIncoming(builder.getInt32(2139095040), val48);
    val65->addIncoming(val62, val61);
    val65->addIncoming(val59, val54);
    val65->addIncoming(val49, val48);
    val67->addIncoming(val66, val63);
    val67->addIncoming(builder.getInt32(0), val8);
    val79->addIncoming(val85, val_preheader_i1);
    val79->addIncoming(builder.getInt32(0), val68);
    val80->addIncoming(val86, val_preheader_i1);
    val80->addIncoming(val74, val68);
    val81->addIncoming(val87, val_preheader_i1);
    val81->addIncoming(val75, val68);
    val101->addIncoming(val87, val91);
    val101->addIncoming(val87, val93);
    val101->addIncoming(val75, val68);
    val102->addIncoming(val86, val91);
    val102->addIncoming(val99, val93);
    val102->addIncoming(val74, val68);
    val123->addIncoming(val112, val120);
    val123->addIncoming(val119, val113);
    val123->addIncoming(builder.getInt32(2139095040), val107);
    val124->addIncoming(val121, val120);
    val124->addIncoming(val118, val113);
    val124->addIncoming(val108, val107);
    val126->addIncoming(val125, val122);
    val126->addIncoming(builder.getInt32(0), valf32_from_ll_exit);
    val127->addIncoming(val133, val_preheader_i3);
    val127->addIncoming(builder.getInt32(0), valf32_from_ll_exit2);
    val128->addIncoming(val134, val_preheader_i3);
    val128->addIncoming(builder.getInt64(3355443200ll), valf32_from_ll_exit2);
    val129->addIncoming(val135, val_preheader_i3);
    val129->addIncoming(builder.getInt32(-1), valf32_from_ll_exit2);
    val149->addIncoming(val134, val139);
    val149->addIncoming(val147, val141);
    val164->addIncoming(val163, val158);
    val164->addIncoming(builder.getInt32(2139095040), val148);
    val164->addIncoming(val157, val154);
  }
  {
    Function *func = funcinit;
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    Value *val4 = func->getArg(4);
    Value *val5 = func->getArg(5);
    builder.SetInsertPoint(valbuild_float_exit);
    //   store i32 -1041235968, ptr %0, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(-1041235968), val0, MaybeAlign(4));
    //   %6 = getelementptr i32, ptr %0, i64 1
    Value *val6 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(1ll)});
    builder.Insert(val6);
    //   store i32 1106247680, ptr %6, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val6, MaybeAlign(4));
    //   %7 = getelementptr i32, ptr %0, i64 2
    Value *val7 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(2ll)});
    builder.Insert(val7);
    //   store i32 0, ptr %7, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val7, MaybeAlign(4));
    //   store i32 0, ptr %1, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val1, MaybeAlign(4));
    //   %8 = getelementptr i32, ptr %1, i64 1
    Value *val8 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(1ll)});
    builder.Insert(val8);
    //   store i32 0, ptr %8, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val8, MaybeAlign(4));
    //   %9 = getelementptr i32, ptr %1, i64 2
    Value *val9 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(2ll)});
    builder.Insert(val9);
    //   store i32 1103626240, ptr %9, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1103626240), val9, MaybeAlign(4));
    //   %10 = getelementptr i32, ptr %2, i64 2
    Value *val10 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(2ll)});
    builder.Insert(val10);
    //   store i32 1106247680, ptr %10, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val10, MaybeAlign(4));
    //   %11 = getelementptr i32, ptr %2, i64 1
    Value *val11 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(1ll)});
    builder.Insert(val11);
    //   store i32 1106247680, ptr %11, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val11, MaybeAlign(4));
    //   store i32 1106247680, ptr %2, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val2, MaybeAlign(4));
    //   %12 = getelementptr i32, ptr %3, i64 2
    Value *val12 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(2ll)});
    builder.Insert(val12);
    //   store i32 1101004800, ptr %12, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val12, MaybeAlign(4));
    //   %13 = getelementptr i32, ptr %3, i64 1
    Value *val13 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(1ll)});
    builder.Insert(val13);
    //   store i32 1101004800, ptr %13, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val13, MaybeAlign(4));
    //   store i32 1101004800, ptr %3, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val3, MaybeAlign(4));
    //   %14 = getelementptr i32, ptr %4, i64 2
    Value *val14 = GetElementPtrInst::Create(Type::getInt32Ty(context), val4, {builder.getInt64(2ll)});
    builder.Insert(val14);
    //   store i32 1061158912, ptr %14, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val14, MaybeAlign(4));
    //   %15 = getelementptr i32, ptr %4, i64 1
    Value *val15 = GetElementPtrInst::Create(Type::getInt32Ty(context), val4, {builder.getInt64(1ll)});
    builder.Insert(val15);
    //   store i32 1061158912, ptr %15, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val15, MaybeAlign(4));
    //   store i32 1061158912, ptr %4, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val4, MaybeAlign(4));
    //   store i32 16711680, ptr %5, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(16711680), val5, MaybeAlign(4));
    //   %16 = getelementptr i32, ptr %5, i64 1
    Value *val16 = GetElementPtrInst::Create(Type::getInt32Ty(context), val5, {builder.getInt64(1ll)});
    builder.Insert(val16);
    //   store i32 16776960, ptr %16, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(16776960), val16, MaybeAlign(4));
    //   %17 = getelementptr i32, ptr %5, i64 2
    Value *val17 = GetElementPtrInst::Create(Type::getInt32Ty(context), val5, {builder.getInt64(2ll)});
    builder.Insert(val17);
    //   store i32 65280, ptr %17, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(65280), val17, MaybeAlign(4));
    //   ret void
    builder.CreateRetVoid();
  }
  {
    Function *func = funcapp;
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val19 = BasicBlock::Create(context, "", func);
    BasicBlock *val29 = BasicBlock::Create(context, "", func);
    BasicBlock *val30 = BasicBlock::Create(context, "", func);
    BasicBlock *val32 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i = BasicBlock::Create(context, "", func);
    BasicBlock *val45 = BasicBlock::Create(context, "", func);
    BasicBlock *val47 = BasicBlock::Create(context, "", func);
    BasicBlock *val54 = BasicBlock::Create(context, "", func);
    BasicBlock *val61 = BasicBlock::Create(context, "", func);
    BasicBlock *val65 = BasicBlock::Create(context, "", func);
    BasicBlock *val71 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val76 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i2 = BasicBlock::Create(context, "", func);
    BasicBlock *val98 = BasicBlock::Create(context, "", func);
    BasicBlock *val100 = BasicBlock::Create(context, "", func);
    BasicBlock *val107 = BasicBlock::Create(context, "", func);
    BasicBlock *val114 = BasicBlock::Create(context, "", func);
    BasicBlock *val116 = BasicBlock::Create(context, "", func);
    BasicBlock *val120 = BasicBlock::Create(context, "", func);
    BasicBlock *val127 = BasicBlock::Create(context, "", func);
    BasicBlock *val129 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_from_ll_exit3 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i4 = BasicBlock::Create(context, "", func);
    BasicBlock *val146 = BasicBlock::Create(context, "", func);
    BasicBlock *val148 = BasicBlock::Create(context, "", func);
    BasicBlock *val155 = BasicBlock::Create(context, "", func);
    BasicBlock *val161 = BasicBlock::Create(context, "", func);
    BasicBlock *val165 = BasicBlock::Create(context, "", func);
    BasicBlock *valbuild_float_exit10 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val202 = BasicBlock::Create(context, "", func);
    BasicBlock *val205 = BasicBlock::Create(context, "", func);
    BasicBlock *val208 = BasicBlock::Create(context, "", func);
    builder.SetInsertPoint(valbuild_float_exit);
    //   %0 = alloca [3 x i32], align 4
    Value *val0 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %1 = alloca [3 x i32], align 4
    Value *val1 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %2 = alloca [3 x i32], align 4
    Value *val2 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %3 = alloca [3 x i32], align 4
    Value *val3 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %4 = alloca [3 x i32], align 4
    Value *val4 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %5 = alloca [3 x i32], align 4
    Value *val5 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 3));
    //   %6 = alloca [500 x [500 x i32]], align 16
    Value *val6 = builder.CreateAlloca(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 500), 500));
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %0) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val0});
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %1) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val1});
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %2) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val2});
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %3) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val3});
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %4) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val4});
    //   call void @llvm.lifetime.start.p0(i64 12, ptr nonnull %5) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(12ll), val5});
    //   store i32 -1041235968, ptr %0, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(-1041235968), val0, MaybeAlign(4));
    //   %7 = getelementptr inbounds i32, ptr %0, i64 1
    Value *val7 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(1ll)});
    builder.Insert(val7);
    //   store i32 1106247680, ptr %7, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val7, MaybeAlign(4));
    //   %8 = getelementptr inbounds i32, ptr %0, i64 2
    Value *val8 = GetElementPtrInst::Create(Type::getInt32Ty(context), val0, {builder.getInt64(2ll)});
    builder.Insert(val8);
    //   store i32 0, ptr %8, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val8, MaybeAlign(4));
    //   store i32 0, ptr %1, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val1, MaybeAlign(4));
    //   %9 = getelementptr inbounds i32, ptr %1, i64 1
    Value *val9 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(1ll)});
    builder.Insert(val9);
    //   store i32 0, ptr %9, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(0), val9, MaybeAlign(4));
    //   %10 = getelementptr inbounds i32, ptr %1, i64 2
    Value *val10 = GetElementPtrInst::Create(Type::getInt32Ty(context), val1, {builder.getInt64(2ll)});
    builder.Insert(val10);
    //   store i32 1103626240, ptr %10, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1103626240), val10, MaybeAlign(4));
    //   %11 = getelementptr inbounds i32, ptr %2, i64 2
    Value *val11 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(2ll)});
    builder.Insert(val11);
    //   store i32 1106247680, ptr %11, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val11, MaybeAlign(4));
    //   %12 = getelementptr inbounds i32, ptr %2, i64 1
    Value *val12 = GetElementPtrInst::Create(Type::getInt32Ty(context), val2, {builder.getInt64(1ll)});
    builder.Insert(val12);
    //   store i32 1106247680, ptr %12, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val12, MaybeAlign(4));
    //   store i32 1106247680, ptr %2, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1106247680), val2, MaybeAlign(4));
    //   %13 = getelementptr inbounds i32, ptr %3, i64 2
    Value *val13 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(2ll)});
    builder.Insert(val13);
    //   store i32 1101004800, ptr %13, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val13, MaybeAlign(4));
    //   %14 = getelementptr inbounds i32, ptr %3, i64 1
    Value *val14 = GetElementPtrInst::Create(Type::getInt32Ty(context), val3, {builder.getInt64(1ll)});
    builder.Insert(val14);
    //   store i32 1101004800, ptr %14, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val14, MaybeAlign(4));
    //   store i32 1101004800, ptr %3, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1101004800), val3, MaybeAlign(4));
    //   %15 = getelementptr inbounds i32, ptr %4, i64 2
    Value *val15 = GetElementPtrInst::Create(Type::getInt32Ty(context), val4, {builder.getInt64(2ll)});
    builder.Insert(val15);
    //   store i32 1061158912, ptr %15, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val15, MaybeAlign(4));
    //   %16 = getelementptr inbounds i32, ptr %4, i64 1
    Value *val16 = GetElementPtrInst::Create(Type::getInt32Ty(context), val4, {builder.getInt64(1ll)});
    builder.Insert(val16);
    //   store i32 1061158912, ptr %16, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val16, MaybeAlign(4));
    //   store i32 1061158912, ptr %4, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(1061158912), val4, MaybeAlign(4));
    //   store i32 16711680, ptr %5, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(16711680), val5, MaybeAlign(4));
    //   %17 = getelementptr inbounds i32, ptr %5, i64 1
    Value *val17 = GetElementPtrInst::Create(Type::getInt32Ty(context), val5, {builder.getInt64(1ll)});
    builder.Insert(val17);
    //   store i32 16776960, ptr %17, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(16776960), val17, MaybeAlign(4));
    //   %18 = getelementptr inbounds i32, ptr %5, i64 2
    Value *val18 = GetElementPtrInst::Create(Type::getInt32Ty(context), val5, {builder.getInt64(2ll)});
    builder.Insert(val18);
    //   store i32 65280, ptr %18, align 4, !tbaa !4
    builder.CreateAlignedStore(builder.getInt32(65280), val18, MaybeAlign(4));
    //   call void @llvm.lifetime.start.p0(i64 1000000, ptr nonnull %6) #9
    builder.CreateCall(funcllvm_lifetime_start_p0, {builder.getInt64(1000000ll), val6});
    //   call void @llvm.memset.p0.i64(ptr noundef nonnull align 16 dereferenceable(1000000) %6, i8 0, i64 1000000, i1 false), !tbaa !4
    builder.CreateCall(funcllvm_memset_p0_i64, {val6, builder.getInt8(0), builder.getInt64(1000000ll), builder.getInt1(false)});
    //   br label %19
    builder.CreateBr(val19);
    builder.SetInsertPoint(val19);
    //   %20 = phi i64 [ 0, %build_float.exit ], [ %203, %202 ]
    PHINode *val20 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %21 = add nsw i64 %20, -250
    Value *val21 = builder.CreateAdd(val20, builder.getInt64(-250ll), "", false, true);
    //   %cond11 = icmp eq i64 %20, 250
    Value *valcond11 = builder.CreateICmpEQ(val20, builder.getInt64(250ll), "");
    //   %22 = tail call i64 @llvm.abs.i64(i64 %21, i1 true)
    Value *val22 = builder.CreateCall(funcllvm_abs_i64, {val21, builder.getInt1(true)});
    //   %23 = icmp ult i64 %22, 16777216
    Value *val23 = builder.CreateICmpULT(val22, builder.getInt64(16777216ll), "");
    //   %24 = shl nuw nsw i64 %22, 24
    Value *val24 = builder.CreateShl(val22, builder.getInt64(24ll), "", true, true);
    //   %25 = select i1 %23, i64 %24, i64 %22
    Value *val25 = builder.CreateSelect(val23, val24, val22);
    //   %26 = select i1 %23, i32 -1, i32 23
    Value *val26 = builder.CreateSelect(val23, builder.getInt32(-1), builder.getInt32(23));
    //   %27 = icmp ugt i64 %25, 16777215
    Value *val27 = builder.CreateICmpUGT(val25, builder.getInt64(16777215ll), "");
    //   %sh.diff = lshr i64 %21, 32
    Value *valsh_diff = builder.CreateLShr(val21, builder.getInt64(32ll), "", false);
    //   %tr.sh.diff = trunc i64 %sh.diff to i32
    Value *valtr_sh_diff = builder.CreateTrunc(valsh_diff, Type::getInt32Ty(context));
    //   %28 = and i32 %tr.sh.diff, -2147483648
    Value *val28 = builder.CreateAnd(valtr_sh_diff, builder.getInt32(-2147483648), "");
    //   br label %30
    builder.CreateBr(val30);
    builder.SetInsertPoint(val29);
    //   call void @llvm.lifetime.end.p0(i64 1000000, ptr nonnull %6) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(1000000ll), val6});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %5) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val5});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %4) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val4});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %3) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val3});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %2) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val2});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %1) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val1});
    //   call void @llvm.lifetime.end.p0(i64 12, ptr nonnull %0) #9
    builder.CreateCall(funcllvm_lifetime_end_p0, {builder.getInt64(12ll), val0});
    //   ret void
    builder.CreateRetVoid();
    builder.SetInsertPoint(val30);
    //   %31 = phi i64 [ 0, %19 ], [ %198, %build_float.exit10 ]
    PHINode *val31 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   br i1 %cond11, label %f32_from_ll.exit, label %32
    builder.CreateCondBr(valcond11, valf32_from_ll_exit, val32);
    builder.SetInsertPoint(val32);
    //   br i1 %27, label %.preheader.i, label %54
    builder.CreateCondBr(val27, val_preheader_i, val54);
    builder.SetInsertPoint(val_preheader_i);
    //   %33 = phi i32 [ %39, %.preheader.i ], [ 0, %32 ]
    PHINode *val33 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %34 = phi i64 [ %40, %.preheader.i ], [ %25, %32 ]
    PHINode *val34 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %35 = phi i32 [ %41, %.preheader.i ], [ %26, %32 ]
    PHINode *val35 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %36 = trunc i64 %34 to i8
    Value *val36 = builder.CreateTrunc(val34, Type::getInt8Ty(context));
    //   %37 = and i8 %36, 1
    Value *val37 = builder.CreateAnd(val36, builder.getInt8(1), "");
    //   %38 = zext nneg i8 %37 to i32
    Value *val38 = builder.CreateZExt(val37, Type::getInt32Ty(context));
    //   %39 = add i32 %33, %38
    Value *val39 = builder.CreateAdd(val33, val38, "", false, false);
    //   %40 = lshr i64 %34, 1
    Value *val40 = builder.CreateLShr(val34, builder.getInt64(1ll), "", false);
    //   %41 = add i32 %35, 1
    Value *val41 = builder.CreateAdd(val35, builder.getInt32(1), "", false, false);
    //   %42 = icmp ugt i64 %34, 33554431
    Value *val42 = builder.CreateICmpUGT(val34, builder.getInt64(33554431ll), "");
    //   %43 = icmp slt i32 %41, -126
    Value *val43 = builder.CreateICmpSLT(val41, builder.getInt32(-126), "");
    //   %44 = select i1 %42, i1 true, i1 %43
    Value *val44 = builder.CreateSelect(val42, builder.getInt1(true), val43);
    //   br i1 %44, label %.preheader.i, label %45, !llvm.loop !8
    builder.CreateCondBr(val44, val_preheader_i, val45);
    builder.SetInsertPoint(val45);
    //   %46 = icmp eq i8 %37, 0
    Value *val46 = builder.CreateICmpEQ(val37, builder.getInt8(0), "");
    //   br i1 %46, label %54, label %47
    builder.CreateCondBr(val46, val54, val47);
    builder.SetInsertPoint(val47);
    //   %48 = icmp sgt i32 %39, 1
    Value *val48 = builder.CreateICmpSGT(val39, builder.getInt32(1), "");
    //   %49 = and i64 %34, 2
    Value *val49 = builder.CreateAnd(val34, builder.getInt64(2ll), "");
    //   %50 = icmp ne i64 %49, 0
    Value *val50 = builder.CreateICmpNE(val49, builder.getInt64(0ll), "");
    //   %51 = or i1 %50, %48
    Value *val51 = builder.CreateOr(val50, val48, "");
    //   %52 = zext i1 %51 to i64
    Value *val52 = builder.CreateZExt(val51, Type::getInt64Ty(context));
    //   %53 = add nuw nsw i64 %40, %52
    Value *val53 = builder.CreateAdd(val40, val52, "", true, true);
    //   br label %54
    builder.CreateBr(val54);
    builder.SetInsertPoint(val54);
    //   %55 = phi i32 [ %41, %45 ], [ %41, %47 ], [ %26, %32 ]
    PHINode *val55 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %56 = phi i64 [ %40, %45 ], [ %53, %47 ], [ %25, %32 ]
    PHINode *val56 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %57 = icmp ugt i64 %56, 16777215
    Value *val57 = builder.CreateICmpUGT(val56, builder.getInt64(16777215ll), "");
    //   %58 = zext i1 %57 to i32
    Value *val58 = builder.CreateZExt(val57, Type::getInt32Ty(context));
    //   %59 = add i32 %55, %58
    Value *val59 = builder.CreateAdd(val55, val58, "", false, false);
    //   %60 = icmp sgt i32 %59, 127
    Value *val60 = builder.CreateICmpSGT(val59, builder.getInt32(127), "");
    //   br i1 %60, label %71, label %61
    builder.CreateCondBr(val60, val71, val61);
    builder.SetInsertPoint(val61);
    //   %62 = select i1 %57, i64 8388608, i64 %56
    Value *val62 = builder.CreateSelect(val57, builder.getInt64(8388608ll), val56);
    //   %63 = icmp ugt i64 %62, 8388607
    Value *val63 = builder.CreateICmpUGT(val62, builder.getInt64(8388607ll), "");
    //   %64 = trunc i64 %62 to i32
    Value *val64 = builder.CreateTrunc(val62, Type::getInt32Ty(context));
    //   br i1 %63, label %65, label %71
    builder.CreateCondBr(val63, val65, val71);
    builder.SetInsertPoint(val65);
    //   %66 = and i32 %64, 8388607
    Value *val66 = builder.CreateAnd(val64, builder.getInt32(8388607), "");
    //   %67 = shl i32 %59, 23
    Value *val67 = builder.CreateShl(val59, builder.getInt32(23), "", false, false);
    //   %68 = add i32 %67, 1065353216
    Value *val68 = builder.CreateAdd(val67, builder.getInt32(1065353216), "", false, false);
    //   %69 = and i32 %68, 2139095040
    Value *val69 = builder.CreateAnd(val68, builder.getInt32(2139095040), "");
    //   %70 = or disjoint i32 %69, %66
    Value *val70 = builder.CreateOr(val69, val66, "");
    //   br label %71
    builder.CreateBr(val71);
    builder.SetInsertPoint(val71);
    //   %72 = phi i32 [ %28, %65 ], [ 2139095040, %54 ], [ %64, %61 ]
    PHINode *val72 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %73 = phi i32 [ %70, %65 ], [ %28, %54 ], [ %28, %61 ]
    PHINode *val73 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %74 = or disjoint i32 %73, %72
    Value *val74 = builder.CreateOr(val73, val72, "");
    //   br label %f32_from_ll.exit
    builder.CreateBr(valf32_from_ll_exit);
    builder.SetInsertPoint(valf32_from_ll_exit);
    //   %75 = phi i32 [ %74, %71 ], [ 0, %30 ]
    PHINode *val75 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %cond = icmp eq i64 %31, 250
    Value *valcond = builder.CreateICmpEQ(val31, builder.getInt64(250ll), "");
    //   br i1 %cond, label %f32_from_ll.exit3, label %76
    builder.CreateCondBr(valcond, valf32_from_ll_exit3, val76);
    builder.SetInsertPoint(val76);
    //   %77 = sub nsw i64 250, %31
    Value *val77 = builder.CreateSub(builder.getInt64(250ll), val31, "", false, true);
    //   %78 = tail call i64 @llvm.abs.i64(i64 %77, i1 true)
    Value *val78 = builder.CreateCall(funcllvm_abs_i64, {val77, builder.getInt1(true)});
    //   %79 = icmp ult i64 %78, 16777216
    Value *val79 = builder.CreateICmpULT(val78, builder.getInt64(16777216ll), "");
    //   %80 = shl nuw nsw i64 %78, 24
    Value *val80 = builder.CreateShl(val78, builder.getInt64(24ll), "", true, true);
    //   %81 = select i1 %79, i64 %80, i64 %78
    Value *val81 = builder.CreateSelect(val79, val80, val78);
    //   %82 = select i1 %79, i32 -1, i32 23
    Value *val82 = builder.CreateSelect(val79, builder.getInt32(-1), builder.getInt32(23));
    //   %83 = lshr i64 %77, 63
    Value *val83 = builder.CreateLShr(val77, builder.getInt64(63ll), "", false);
    //   %84 = trunc i64 %83 to i32
    Value *val84 = builder.CreateTrunc(val83, Type::getInt32Ty(context));
    //   %85 = icmp ugt i64 %81, 16777215
    Value *val85 = builder.CreateICmpUGT(val81, builder.getInt64(16777215ll), "");
    //   br i1 %85, label %.preheader.i2, label %107
    builder.CreateCondBr(val85, val_preheader_i2, val107);
    builder.SetInsertPoint(val_preheader_i2);
    //   %86 = phi i32 [ %92, %.preheader.i2 ], [ 0, %76 ]
    PHINode *val86 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %87 = phi i64 [ %93, %.preheader.i2 ], [ %81, %76 ]
    PHINode *val87 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %88 = phi i32 [ %94, %.preheader.i2 ], [ %82, %76 ]
    PHINode *val88 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %89 = trunc i64 %87 to i8
    Value *val89 = builder.CreateTrunc(val87, Type::getInt8Ty(context));
    //   %90 = and i8 %89, 1
    Value *val90 = builder.CreateAnd(val89, builder.getInt8(1), "");
    //   %91 = zext nneg i8 %90 to i32
    Value *val91 = builder.CreateZExt(val90, Type::getInt32Ty(context));
    //   %92 = add i32 %86, %91
    Value *val92 = builder.CreateAdd(val86, val91, "", false, false);
    //   %93 = lshr i64 %87, 1
    Value *val93 = builder.CreateLShr(val87, builder.getInt64(1ll), "", false);
    //   %94 = add i32 %88, 1
    Value *val94 = builder.CreateAdd(val88, builder.getInt32(1), "", false, false);
    //   %95 = icmp ugt i64 %87, 33554431
    Value *val95 = builder.CreateICmpUGT(val87, builder.getInt64(33554431ll), "");
    //   %96 = icmp slt i32 %94, -126
    Value *val96 = builder.CreateICmpSLT(val94, builder.getInt32(-126), "");
    //   %97 = select i1 %95, i1 true, i1 %96
    Value *val97 = builder.CreateSelect(val95, builder.getInt1(true), val96);
    //   br i1 %97, label %.preheader.i2, label %98, !llvm.loop !8
    builder.CreateCondBr(val97, val_preheader_i2, val98);
    builder.SetInsertPoint(val98);
    //   %99 = icmp eq i8 %90, 0
    Value *val99 = builder.CreateICmpEQ(val90, builder.getInt8(0), "");
    //   br i1 %99, label %107, label %100
    builder.CreateCondBr(val99, val107, val100);
    builder.SetInsertPoint(val100);
    //   %101 = icmp sgt i32 %92, 1
    Value *val101 = builder.CreateICmpSGT(val92, builder.getInt32(1), "");
    //   %102 = and i64 %87, 2
    Value *val102 = builder.CreateAnd(val87, builder.getInt64(2ll), "");
    //   %103 = icmp ne i64 %102, 0
    Value *val103 = builder.CreateICmpNE(val102, builder.getInt64(0ll), "");
    //   %104 = or i1 %103, %101
    Value *val104 = builder.CreateOr(val103, val101, "");
    //   %105 = zext i1 %104 to i64
    Value *val105 = builder.CreateZExt(val104, Type::getInt64Ty(context));
    //   %106 = add nuw nsw i64 %93, %105
    Value *val106 = builder.CreateAdd(val93, val105, "", true, true);
    //   br label %107
    builder.CreateBr(val107);
    builder.SetInsertPoint(val107);
    //   %108 = phi i32 [ %94, %98 ], [ %94, %100 ], [ %82, %76 ]
    PHINode *val108 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %109 = phi i64 [ %93, %98 ], [ %106, %100 ], [ %81, %76 ]
    PHINode *val109 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %110 = icmp ugt i64 %109, 16777215
    Value *val110 = builder.CreateICmpUGT(val109, builder.getInt64(16777215ll), "");
    //   %111 = zext i1 %110 to i32
    Value *val111 = builder.CreateZExt(val110, Type::getInt32Ty(context));
    //   %112 = add i32 %108, %111
    Value *val112 = builder.CreateAdd(val108, val111, "", false, false);
    //   %113 = icmp sgt i32 %112, 127
    Value *val113 = builder.CreateICmpSGT(val112, builder.getInt32(127), "");
    //   br i1 %113, label %114, label %116
    builder.CreateCondBr(val113, val114, val116);
    builder.SetInsertPoint(val114);
    //   %115 = shl nuw i32 %84, 31
    Value *val115 = builder.CreateShl(val84, builder.getInt32(31), "", true, false);
    //   br label %129
    builder.CreateBr(val129);
    builder.SetInsertPoint(val116);
    //   %117 = select i1 %110, i64 8388608, i64 %109
    Value *val117 = builder.CreateSelect(val110, builder.getInt64(8388608ll), val109);
    //   %118 = icmp ugt i64 %117, 8388607
    Value *val118 = builder.CreateICmpUGT(val117, builder.getInt64(8388607ll), "");
    //   %119 = trunc i64 %117 to i32
    Value *val119 = builder.CreateTrunc(val117, Type::getInt32Ty(context));
    //   br i1 %118, label %120, label %127
    builder.CreateCondBr(val118, val120, val127);
    builder.SetInsertPoint(val120);
    //   %121 = and i32 %119, 8388607
    Value *val121 = builder.CreateAnd(val119, builder.getInt32(8388607), "");
    //   %122 = shl i32 %112, 23
    Value *val122 = builder.CreateShl(val112, builder.getInt32(23), "", false, false);
    //   %123 = add i32 %122, 1065353216
    Value *val123 = builder.CreateAdd(val122, builder.getInt32(1065353216), "", false, false);
    //   %124 = and i32 %123, 2139095040
    Value *val124 = builder.CreateAnd(val123, builder.getInt32(2139095040), "");
    //   %125 = or disjoint i32 %124, %121
    Value *val125 = builder.CreateOr(val124, val121, "");
    //   %126 = shl nuw i32 %84, 31
    Value *val126 = builder.CreateShl(val84, builder.getInt32(31), "", true, false);
    //   br label %129
    builder.CreateBr(val129);
    builder.SetInsertPoint(val127);
    //   %128 = shl nuw i32 %84, 31
    Value *val128 = builder.CreateShl(val84, builder.getInt32(31), "", true, false);
    //   br label %129
    builder.CreateBr(val129);
    builder.SetInsertPoint(val129);
    //   %130 = phi i32 [ %119, %127 ], [ %126, %120 ], [ 2139095040, %114 ]
    PHINode *val130 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %131 = phi i32 [ %128, %127 ], [ %125, %120 ], [ %115, %114 ]
    PHINode *val131 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %132 = or disjoint i32 %131, %130
    Value *val132 = builder.CreateOr(val131, val130, "");
    //   br label %f32_from_ll.exit3
    builder.CreateBr(valf32_from_ll_exit3);
    builder.SetInsertPoint(valf32_from_ll_exit3);
    //   %133 = phi i32 [ %132, %129 ], [ 0, %f32_from_ll.exit ]
    PHINode *val133 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   br label %.preheader.i4
    builder.CreateBr(val_preheader_i4);
    builder.SetInsertPoint(val_preheader_i4);
    //   %134 = phi i32 [ %140, %.preheader.i4 ], [ 0, %f32_from_ll.exit3 ]
    PHINode *val134 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %135 = phi i64 [ %141, %.preheader.i4 ], [ 3355443200, %f32_from_ll.exit3 ]
    PHINode *val135 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %136 = phi i32 [ %142, %.preheader.i4 ], [ -1, %f32_from_ll.exit3 ]
    PHINode *val136 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %137 = trunc i64 %135 to i8
    Value *val137 = builder.CreateTrunc(val135, Type::getInt8Ty(context));
    //   %138 = and i8 %137, 1
    Value *val138 = builder.CreateAnd(val137, builder.getInt8(1), "");
    //   %139 = zext nneg i8 %138 to i32
    Value *val139 = builder.CreateZExt(val138, Type::getInt32Ty(context));
    //   %140 = add i32 %134, %139
    Value *val140 = builder.CreateAdd(val134, val139, "", false, false);
    //   %141 = lshr i64 %135, 1
    Value *val141 = builder.CreateLShr(val135, builder.getInt64(1ll), "", false);
    //   %142 = add i32 %136, 1
    Value *val142 = builder.CreateAdd(val136, builder.getInt32(1), "", false, false);
    //   %143 = icmp ugt i64 %135, 33554431
    Value *val143 = builder.CreateICmpUGT(val135, builder.getInt64(33554431ll), "");
    //   %144 = icmp slt i32 %142, -126
    Value *val144 = builder.CreateICmpSLT(val142, builder.getInt32(-126), "");
    //   %145 = select i1 %143, i1 true, i1 %144
    Value *val145 = builder.CreateSelect(val143, builder.getInt1(true), val144);
    //   br i1 %145, label %.preheader.i4, label %146, !llvm.loop !8
    builder.CreateCondBr(val145, val_preheader_i4, val146);
    builder.SetInsertPoint(val146);
    //   %147 = icmp eq i8 %138, 0
    Value *val147 = builder.CreateICmpEQ(val138, builder.getInt8(0), "");
    //   br i1 %147, label %155, label %148
    builder.CreateCondBr(val147, val155, val148);
    builder.SetInsertPoint(val148);
    //   %149 = icmp sgt i32 %140, 1
    Value *val149 = builder.CreateICmpSGT(val140, builder.getInt32(1), "");
    //   %150 = and i64 %135, 2
    Value *val150 = builder.CreateAnd(val135, builder.getInt64(2ll), "");
    //   %151 = icmp ne i64 %150, 0
    Value *val151 = builder.CreateICmpNE(val150, builder.getInt64(0ll), "");
    //   %152 = or i1 %151, %149
    Value *val152 = builder.CreateOr(val151, val149, "");
    //   %153 = zext i1 %152 to i64
    Value *val153 = builder.CreateZExt(val152, Type::getInt64Ty(context));
    //   %154 = add nuw nsw i64 %141, %153
    Value *val154 = builder.CreateAdd(val141, val153, "", true, true);
    //   br label %155
    builder.CreateBr(val155);
    builder.SetInsertPoint(val155);
    //   %156 = phi i64 [ %141, %146 ], [ %154, %148 ]
    PHINode *val156 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %157 = icmp ugt i64 %156, 16777215
    Value *val157 = builder.CreateICmpUGT(val156, builder.getInt64(16777215ll), "");
    //   %158 = zext i1 %157 to i32
    Value *val158 = builder.CreateZExt(val157, Type::getInt32Ty(context));
    //   %159 = add i32 %142, %158
    Value *val159 = builder.CreateAdd(val142, val158, "", false, false);
    //   %160 = icmp sgt i32 %159, 127
    Value *val160 = builder.CreateICmpSGT(val159, builder.getInt32(127), "");
    //   br i1 %160, label %build_float.exit10, label %161
    builder.CreateCondBr(val160, valbuild_float_exit10, val161);
    builder.SetInsertPoint(val161);
    //   %162 = select i1 %157, i64 8388608, i64 %156
    Value *val162 = builder.CreateSelect(val157, builder.getInt64(8388608ll), val156);
    //   %163 = icmp ugt i64 %162, 8388607
    Value *val163 = builder.CreateICmpUGT(val162, builder.getInt64(8388607ll), "");
    //   %164 = trunc i64 %162 to i32
    Value *val164 = builder.CreateTrunc(val162, Type::getInt32Ty(context));
    //   br i1 %163, label %165, label %build_float.exit10
    builder.CreateCondBr(val163, val165, valbuild_float_exit10);
    builder.SetInsertPoint(val165);
    //   %166 = and i32 %164, 8388607
    Value *val166 = builder.CreateAnd(val164, builder.getInt32(8388607), "");
    //   %167 = shl i32 %159, 23
    Value *val167 = builder.CreateShl(val159, builder.getInt32(23), "", false, false);
    //   %168 = add i32 %167, 1065353216
    Value *val168 = builder.CreateAdd(val167, builder.getInt32(1065353216), "", false, false);
    //   %169 = and i32 %168, 2139095040
    Value *val169 = builder.CreateAnd(val168, builder.getInt32(2139095040), "");
    //   %170 = or disjoint i32 %169, %166
    Value *val170 = builder.CreateOr(val169, val166, "");
    //   br label %build_float.exit10
    builder.CreateBr(valbuild_float_exit10);
    builder.SetInsertPoint(valbuild_float_exit10);
    //   %171 = phi i32 [ %170, %165 ], [ 2139095040, %155 ], [ %164, %161 ]
    PHINode *val171 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %172 = tail call i32 @f32_mul(i32 noundef %75, i32 noundef %75) #9
    Value *val172 = builder.CreateCall(funcf32_mul, {val75, val75});
    //   %173 = tail call i32 @f32_mul(i32 noundef %133, i32 noundef %133) #9
    Value *val173 = builder.CreateCall(funcf32_mul, {val133, val133});
    //   %174 = tail call i32 @f32_add(i32 noundef %172, i32 noundef %173) #9
    Value *val174 = builder.CreateCall(funcf32_add, {val172, val173});
    //   %175 = tail call i32 @f32_mul(i32 noundef %171, i32 noundef %171) #9
    Value *val175 = builder.CreateCall(funcf32_mul, {val171, val171});
    //   %176 = tail call i32 @f32_add(i32 noundef %174, i32 noundef %175) #9
    Value *val176 = builder.CreateCall(funcf32_add, {val174, val175});
    //   %177 = tail call i32 @f32_div(i32 noundef %176, i32 noundef 1073741824) #9
    Value *val177 = builder.CreateCall(funcf32_div, {val176, builder.getInt32(1073741824)});
    //   %178 = lshr i32 %176, 1
    Value *val178 = builder.CreateLShr(val176, builder.getInt32(1), "", false);
    //   %179 = sub nsw i32 1597463007, %178
    Value *val179 = builder.CreateSub(builder.getInt32(1597463007), val178, "", false, true);
    //   %180 = tail call i32 @f32_mul(i32 noundef %179, i32 noundef %179) #9
    Value *val180 = builder.CreateCall(funcf32_mul, {val179, val179});
    //   %181 = tail call i32 @f32_mul(i32 noundef %177, i32 noundef %180) #9
    Value *val181 = builder.CreateCall(funcf32_mul, {val177, val180});
    //   %182 = and i32 %181, 2139095040
    Value *val182 = builder.CreateAnd(val181, builder.getInt32(2139095040), "");
    //   %183 = icmp ne i32 %182, 2139095040
    Value *val183 = builder.CreateICmpNE(val182, builder.getInt32(2139095040), "");
    //   %184 = and i32 %181, 8388607
    Value *val184 = builder.CreateAnd(val181, builder.getInt32(8388607), "");
    //   %185 = icmp eq i32 %184, 0
    Value *val185 = builder.CreateICmpEQ(val184, builder.getInt32(0), "");
    //   %186 = or i1 %183, %185
    Value *val186 = builder.CreateOr(val183, val185, "");
    //   %187 = xor i32 %181, -2147483648
    Value *val187 = builder.CreateXor(val181, builder.getInt32(-2147483648), "");
    //   %188 = select i1 %186, i32 %187, i32 %181
    Value *val188 = builder.CreateSelect(val186, val187, val181);
    //   %189 = tail call i32 @f32_add(i32 noundef 1069547520, i32 noundef %188)
    Value *val189 = builder.CreateCall(funcf32_add, {builder.getInt32(1069547520), val188});
    //   %190 = tail call i32 @f32_mul(i32 noundef %179, i32 noundef %189) #9
    Value *val190 = builder.CreateCall(funcf32_mul, {val179, val189});
    //   %191 = tail call i32 @f32_mul(i32 noundef %75, i32 noundef %190) #9
    Value *val191 = builder.CreateCall(funcf32_mul, {val75, val190});
    //   %192 = tail call i32 @f32_mul(i32 noundef %133, i32 noundef %190) #9
    Value *val192 = builder.CreateCall(funcf32_mul, {val133, val190});
    //   %193 = tail call i32 @f32_mul(i32 noundef %171, i32 noundef %190) #9
    Value *val193 = builder.CreateCall(funcf32_mul, {val171, val190});
    //   %194 = call i32 @ray_impl(ptr noundef nonnull %0, ptr noundef nonnull %1, ptr noundef nonnull %2, ptr noundef nonnull %3, ptr noundef nonnull %4, ptr noundef nonnull %5, i32 noundef 0, i32 noundef 0, i32 noundef 0, i32 noundef %191, i32 noundef %192, i32 noundef %193, i32 noundef 20, i32 noundef 10), !range !10
    Value *val194 = builder.CreateCall(funcray_impl, {val0, val1, val2, val3, val4, val5, builder.getInt32(0), builder.getInt32(0), builder.getInt32(0), val191, val192, val193, builder.getInt32(20), builder.getInt32(10)});
    //   %195 = icmp eq i32 %194, -1
    Value *val195 = builder.CreateICmpEQ(val194, builder.getInt32(-1), "");
    //   %196 = select i1 %195, i32 12303291, i32 %194
    Value *val196 = builder.CreateSelect(val195, builder.getInt32(12303291), val194);
    //   %197 = getelementptr [500 x [500 x i32]], ptr %6, i64 0, i64 %20, i64 %31
    Value *val197 = GetElementPtrInst::Create(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 500), 500), val6, {builder.getInt64(0ll), val20, val31});
    builder.Insert(val197);
    //   store i32 %196, ptr %197, align 4, !tbaa !4
    builder.CreateAlignedStore(val196, val197, MaybeAlign(4));
    //   %198 = add nuw nsw i64 %31, 1
    Value *val198 = builder.CreateAdd(val31, builder.getInt64(1ll), "", true, true);
    //   %199 = icmp eq i64 %198, 500
    Value *val199 = builder.CreateICmpEQ(val198, builder.getInt64(500ll), "");
    //   br i1 %199, label %.preheader, label %30, !llvm.loop !11
    builder.CreateCondBr(val199, val_preheader, val30);
    builder.SetInsertPoint(val_preheader);
    //   %200 = phi i64 [ %206, %205 ], [ 0, %build_float.exit10 ]
    PHINode *val200 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %201 = trunc i64 %200 to i32
    Value *val201 = builder.CreateTrunc(val200, Type::getInt32Ty(context));
    //   br label %208
    builder.CreateBr(val208);
    builder.SetInsertPoint(val202);
    //   tail call void (...) @simFlush() #9
    builder.CreateCall(funcsimFlush, {});
    //   %203 = add nuw nsw i64 %20, 1
    Value *val203 = builder.CreateAdd(val20, builder.getInt64(1ll), "", true, true);
    //   %204 = icmp eq i64 %203, 500
    Value *val204 = builder.CreateICmpEQ(val203, builder.getInt64(500ll), "");
    //   br i1 %204, label %29, label %19, !llvm.loop !12
    builder.CreateCondBr(val204, val29, val19);
    builder.SetInsertPoint(val205);
    //   %206 = add nuw nsw i64 %200, 1
    Value *val206 = builder.CreateAdd(val200, builder.getInt64(1ll), "", true, true);
    //   %207 = icmp eq i64 %206, 500
    Value *val207 = builder.CreateICmpEQ(val206, builder.getInt64(500ll), "");
    //   br i1 %207, label %202, label %.preheader, !llvm.loop !13
    builder.CreateCondBr(val207, val202, val_preheader);
    builder.SetInsertPoint(val208);
    //   %209 = phi i64 [ 0, %.preheader ], [ %213, %208 ]
    PHINode *val209 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %210 = getelementptr [500 x [500 x i32]], ptr %6, i64 0, i64 %200, i64 %209
    Value *val210 = GetElementPtrInst::Create(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 500), 500), val6, {builder.getInt64(0ll), val200, val209});
    builder.Insert(val210);
    //   %211 = load i32, ptr %210, align 4, !tbaa !4
    Value *val211 = builder.CreateAlignedLoad(Type::getInt32Ty(context), val210, MaybeAlign(4));
    //   %212 = trunc i64 %209 to i32
    Value *val212 = builder.CreateTrunc(val209, Type::getInt32Ty(context));
    //   tail call void @simPutPixel(i32 noundef %201, i32 noundef %212, i32 noundef %211) #9
    builder.CreateCall(funcsimPutPixel, {val201, val212, val211});
    //   %213 = add nuw nsw i64 %209, 1
    Value *val213 = builder.CreateAdd(val209, builder.getInt64(1ll), "", true, true);
    //   %214 = icmp eq i64 %213, 500
    Value *val214 = builder.CreateICmpEQ(val213, builder.getInt64(500ll), "");
    //   br i1 %214, label %205, label %208, !llvm.loop !14
    builder.CreateCondBr(val214, val205, val208);
    val20->addIncoming(builder.getInt64(0ll), valbuild_float_exit);
    val20->addIncoming(val203, val202);
    val31->addIncoming(builder.getInt64(0ll), val19);
    val31->addIncoming(val198, valbuild_float_exit10);
    val33->addIncoming(val39, val_preheader_i);
    val33->addIncoming(builder.getInt32(0), val32);
    val34->addIncoming(val40, val_preheader_i);
    val34->addIncoming(val25, val32);
    val35->addIncoming(val41, val_preheader_i);
    val35->addIncoming(val26, val32);
    val55->addIncoming(val41, val45);
    val55->addIncoming(val41, val47);
    val55->addIncoming(val26, val32);
    val56->addIncoming(val40, val45);
    val56->addIncoming(val53, val47);
    val56->addIncoming(val25, val32);
    val72->addIncoming(val28, val65);
    val72->addIncoming(builder.getInt32(2139095040), val54);
    val72->addIncoming(val64, val61);
    val73->addIncoming(val70, val65);
    val73->addIncoming(val28, val54);
    val73->addIncoming(val28, val61);
    val75->addIncoming(val74, val71);
    val75->addIncoming(builder.getInt32(0), val30);
    val86->addIncoming(val92, val_preheader_i2);
    val86->addIncoming(builder.getInt32(0), val76);
    val87->addIncoming(val93, val_preheader_i2);
    val87->addIncoming(val81, val76);
    val88->addIncoming(val94, val_preheader_i2);
    val88->addIncoming(val82, val76);
    val108->addIncoming(val94, val98);
    val108->addIncoming(val94, val100);
    val108->addIncoming(val82, val76);
    val109->addIncoming(val93, val98);
    val109->addIncoming(val106, val100);
    val109->addIncoming(val81, val76);
    val130->addIncoming(val119, val127);
    val130->addIncoming(val126, val120);
    val130->addIncoming(builder.getInt32(2139095040), val114);
    val131->addIncoming(val128, val127);
    val131->addIncoming(val125, val120);
    val131->addIncoming(val115, val114);
    val133->addIncoming(val132, val129);
    val133->addIncoming(builder.getInt32(0), valf32_from_ll_exit);
    val134->addIncoming(val140, val_preheader_i4);
    val134->addIncoming(builder.getInt32(0), valf32_from_ll_exit3);
    val135->addIncoming(val141, val_preheader_i4);
    val135->addIncoming(builder.getInt64(3355443200ll), valf32_from_ll_exit3);
    val136->addIncoming(val142, val_preheader_i4);
    val136->addIncoming(builder.getInt32(-1), valf32_from_ll_exit3);
    val156->addIncoming(val141, val146);
    val156->addIncoming(val154, val148);
    val171->addIncoming(val170, val165);
    val171->addIncoming(builder.getInt32(2139095040), val155);
    val171->addIncoming(val164, val161);
    val200->addIncoming(val206, val205);
    val200->addIncoming(builder.getInt64(0ll), valbuild_float_exit10);
    val209->addIncoming(builder.getInt64(0ll), val_preheader);
    val209->addIncoming(val213, val208);
  }
  {
    Function *func = funcf32_add;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val18 = BasicBlock::Create(context, "", func);
    BasicBlock *val20 = BasicBlock::Create(context, "", func);
    BasicBlock *val24 = BasicBlock::Create(context, "", func);
    BasicBlock *val25 = BasicBlock::Create(context, "", func);
    BasicBlock *valf32_less_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val75 = BasicBlock::Create(context, "", func);
    BasicBlock *val100 = BasicBlock::Create(context, "", func);
    BasicBlock *val102 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit = BasicBlock::Create(context, "", func);
    BasicBlock *val119 = BasicBlock::Create(context, "", func);
    BasicBlock *val120 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %0, 2139095040
    Value *val3 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %4 = icmp ne i32 %3, 2139095040
    Value *val4 = builder.CreateICmpNE(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %0, 8388607
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %6 = icmp eq i32 %5, 0
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %7 = or i1 %4, %6
    Value *val7 = builder.CreateOr(val4, val6, "");
    //   br i1 %7, label %8, label %120
    builder.CreateCondBr(val7, val8, val120);
    builder.SetInsertPoint(val8);
    //   %9 = and i32 %1, 2139095040
    Value *val9 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %10 = icmp ne i32 %9, 2139095040
    Value *val10 = builder.CreateICmpNE(val9, builder.getInt32(2139095040), "");
    //   %11 = and i32 %1, 8388607
    Value *val11 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %12 = icmp eq i32 %11, 0
    Value *val12 = builder.CreateICmpEQ(val11, builder.getInt32(0), "");
    //   %13 = or i1 %10, %12
    Value *val13 = builder.CreateOr(val10, val12, "");
    //   br i1 %13, label %14, label %120
    builder.CreateCondBr(val13, val14, val120);
    builder.SetInsertPoint(val14);
    //   %15 = and i32 %0, 2147483647
    Value *val15 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %16 = icmp eq i32 %15, 2139095040
    Value *val16 = builder.CreateICmpEQ(val15, builder.getInt32(2139095040), "");
    //   %17 = and i32 %1, 2147483647
    Value *val17 = builder.CreateAnd(val1, builder.getInt32(2147483647), "");
    //   br i1 %16, label %18, label %24
    builder.CreateCondBr(val16, val18, val24);
    builder.SetInsertPoint(val18);
    //   %19 = icmp eq i32 %17, 2139095040
    Value *val19 = builder.CreateICmpEQ(val17, builder.getInt32(2139095040), "");
    //   br i1 %19, label %20, label %120
    builder.CreateCondBr(val19, val20, val120);
    builder.SetInsertPoint(val20);
    //   %21 = xor i32 %1, %0
    Value *val21 = builder.CreateXor(val1, val0, "");
    //   %22 = icmp sgt i32 %21, -1
    Value *val22 = builder.CreateICmpSGT(val21, builder.getInt32(-1), "");
    //   %23 = select i1 %22, i32 %0, i32 -1
    Value *val23 = builder.CreateSelect(val22, val0, builder.getInt32(-1));
    //   br label %120
    builder.CreateBr(val120);
    builder.SetInsertPoint(val24);
    //   switch i32 %17, label %25 [     i32 0, label %120     i32 2139095040, label %119   ]
    SwitchInst *s0 = builder.CreateSwitch(val17, val25);
    builder.SetInsertPoint(val25);
    //   %26 = icmp eq i32 %15, 0
    Value *val26 = builder.CreateICmpEQ(val15, builder.getInt32(0), "");
    //   br i1 %26, label %120, label %f32_less.exit
    builder.CreateCondBr(val26, val120, valf32_less_exit);
    builder.SetInsertPoint(valf32_less_exit);
    //   %27 = icmp uge i32 %15, %17
    Value *val27 = builder.CreateICmpUGE(val15, val17, "");
    //   %28 = icmp eq i32 %9, 2139095040
    Value *val28 = builder.CreateICmpEQ(val9, builder.getInt32(2139095040), "");
    //   %29 = icmp ne i32 %11, 0
    Value *val29 = builder.CreateICmpNE(val11, builder.getInt32(0), "");
    //   %.not6 = and i1 %28, %29
    Value *val_not6 = builder.CreateAnd(val28, val29, "");
    //   %spec.select = or i1 %27, %.not6
    Value *valspec_select = builder.CreateOr(val27, val_not6, "");
    //   %30 = select i1 %spec.select, i32 %1, i32 %0
    Value *val30 = builder.CreateSelect(valspec_select, val1, val0);
    //   %31 = select i1 %spec.select, i32 %0, i32 %1
    Value *val31 = builder.CreateSelect(valspec_select, val0, val1);
    //   %32 = and i32 %31, 8388607
    Value *val32 = builder.CreateAnd(val31, builder.getInt32(8388607), "");
    //   %33 = zext nneg i32 %32 to i64
    Value *val33 = builder.CreateZExt(val32, Type::getInt64Ty(context));
    //   %34 = and i32 %31, 2139095040
    Value *val34 = builder.CreateAnd(val31, builder.getInt32(2139095040), "");
    //   %35 = icmp ne i32 %34, 0
    Value *val35 = builder.CreateICmpNE(val34, builder.getInt32(0), "");
    //   %36 = icmp eq i32 %32, 0
    Value *val36 = builder.CreateICmpEQ(val32, builder.getInt32(0), "");
    //   %37 = or i1 %35, %36
    Value *val37 = builder.CreateOr(val35, val36, "");
    //   %38 = and i32 %31, 2147483647
    Value *val38 = builder.CreateAnd(val31, builder.getInt32(2147483647), "");
    //   %39 = icmp eq i32 %38, 0
    Value *val39 = builder.CreateICmpEQ(val38, builder.getInt32(0), "");
    //   %40 = or disjoint i64 %33, 8388608
    Value *val40 = builder.CreateOr(val33, builder.getInt64(8388608ll), "");
    //   %41 = select i1 %39, i64 %33, i64 %40
    Value *val41 = builder.CreateSelect(val39, val33, val40);
    //   %42 = select i1 %37, i64 %41, i64 %33
    Value *val42 = builder.CreateSelect(val37, val41, val33);
    //   %43 = and i32 %30, 8388607
    Value *val43 = builder.CreateAnd(val30, builder.getInt32(8388607), "");
    //   %44 = zext nneg i32 %43 to i64
    Value *val44 = builder.CreateZExt(val43, Type::getInt64Ty(context));
    //   %45 = and i32 %30, 2139095040
    Value *val45 = builder.CreateAnd(val30, builder.getInt32(2139095040), "");
    //   %46 = icmp ne i32 %45, 0
    Value *val46 = builder.CreateICmpNE(val45, builder.getInt32(0), "");
    //   %47 = icmp eq i32 %43, 0
    Value *val47 = builder.CreateICmpEQ(val43, builder.getInt32(0), "");
    //   %48 = or i1 %46, %47
    Value *val48 = builder.CreateOr(val46, val47, "");
    //   %49 = and i32 %30, 2147483647
    Value *val49 = builder.CreateAnd(val30, builder.getInt32(2147483647), "");
    //   %50 = icmp eq i32 %49, 0
    Value *val50 = builder.CreateICmpEQ(val49, builder.getInt32(0), "");
    //   %51 = or disjoint i64 %44, 8388608
    Value *val51 = builder.CreateOr(val44, builder.getInt64(8388608ll), "");
    //   %52 = select i1 %50, i64 %44, i64 %51
    Value *val52 = builder.CreateSelect(val50, val44, val51);
    //   %53 = select i1 %48, i64 %52, i64 %44
    Value *val53 = builder.CreateSelect(val48, val52, val44);
    //   %54 = icmp eq i32 %34, 0
    Value *val54 = builder.CreateICmpEQ(val34, builder.getInt32(0), "");
    //   %55 = icmp ne i32 %32, 0
    Value *val55 = builder.CreateICmpNE(val32, builder.getInt32(0), "");
    //   %56 = and i1 %54, %55
    Value *val56 = builder.CreateAnd(val54, val55, "");
    //   %57 = or i1 %39, %56
    Value *val57 = builder.CreateOr(val39, val56, "");
    //   %58 = lshr i32 %31, 23
    Value *val58 = builder.CreateLShr(val31, builder.getInt32(23), "", false);
    //   %59 = and i32 %58, 255
    Value *val59 = builder.CreateAnd(val58, builder.getInt32(255), "");
    //   %60 = add nsw i32 %59, -127
    Value *val60 = builder.CreateAdd(val59, builder.getInt32(-127), "", false, true);
    //   %61 = select i1 %57, i32 -126, i32 %60
    Value *val61 = builder.CreateSelect(val57, builder.getInt32(-126), val60);
    //   %62 = icmp eq i32 %45, 0
    Value *val62 = builder.CreateICmpEQ(val45, builder.getInt32(0), "");
    //   %63 = icmp ne i32 %43, 0
    Value *val63 = builder.CreateICmpNE(val43, builder.getInt32(0), "");
    //   %64 = and i1 %62, %63
    Value *val64 = builder.CreateAnd(val62, val63, "");
    //   %65 = or i1 %50, %64
    Value *val65 = builder.CreateOr(val50, val64, "");
    //   %66 = lshr i32 %30, 23
    Value *val66 = builder.CreateLShr(val30, builder.getInt32(23), "", false);
    //   %67 = and i32 %66, 255
    Value *val67 = builder.CreateAnd(val66, builder.getInt32(255), "");
    //   %68 = add nsw i32 %67, -127
    Value *val68 = builder.CreateAdd(val67, builder.getInt32(-127), "", false, true);
    //   %69 = select i1 %65, i32 -126, i32 %68
    Value *val69 = builder.CreateSelect(val65, builder.getInt32(-126), val68);
    //   %70 = lshr i32 %31, 31
    Value *val70 = builder.CreateLShr(val31, builder.getInt32(31), "", false);
    //   %71 = trunc i32 %70 to i8
    Value *val71 = builder.CreateTrunc(val70, Type::getInt8Ty(context));
    //   %72 = lshr i32 %30, 31
    Value *val72 = builder.CreateLShr(val30, builder.getInt32(31), "", false);
    //   %73 = icmp eq i32 %70, %72
    Value *val73 = builder.CreateICmpEQ(val70, val72, "");
    //   %74 = sub nsw i32 %61, %69
    Value *val74 = builder.CreateSub(val61, val69, "", false, true);
    //   br i1 %73, label %75, label %100
    builder.CreateCondBr(val73, val75, val100);
    builder.SetInsertPoint(val75);
    //   %76 = tail call noundef i32 @llvm.umin.i32(i32 %74, i32 24)
    Value *val76 = builder.CreateCall(funcllvm_umin_i32, {val74, builder.getInt32(24)});
    //   %77 = zext nneg i32 %76 to i64
    Value *val77 = builder.CreateZExt(val76, Type::getInt64Ty(context));
    //   %78 = sub nsw i32 %74, %76
    Value *val78 = builder.CreateSub(val74, val76, "", false, true);
    //   %79 = tail call noundef i32 @llvm.umin.i32(i32 %78, i32 24)
    Value *val79 = builder.CreateCall(funcllvm_umin_i32, {val78, builder.getInt32(24)});
    //   %80 = zext nneg i32 %79 to i64
    Value *val80 = builder.CreateZExt(val79, Type::getInt64Ty(context));
    //   %81 = shl nuw nsw i64 %42, %77
    Value *val81 = builder.CreateShl(val42, val77, "", true, true);
    //   %82 = sub nsw i32 %61, %76
    Value *val82 = builder.CreateSub(val61, val76, "", false, true);
    //   %83 = lshr i64 %53, %80
    Value *val83 = builder.CreateLShr(val53, val80, "", false);
    //   %84 = add nuw nsw i64 %83, %81
    Value *val84 = builder.CreateAdd(val83, val81, "", true, true);
    //   %85 = add nsw i64 %80, -1
    Value *val85 = builder.CreateAdd(val80, builder.getInt64(-1ll), "", false, true);
    //   %86 = lshr i64 %53, %85
    Value *val86 = builder.CreateLShr(val53, val85, "", false);
    //   %87 = trunc i64 %86 to i8
    Value *val87 = builder.CreateTrunc(val86, Type::getInt8Ty(context));
    //   %88 = and i8 %87, 1
    Value *val88 = builder.CreateAnd(val87, builder.getInt8(1), "");
    //   %89 = shl nsw i32 -1, %79
    Value *val89 = builder.CreateShl(builder.getInt32(-1), val79, "", false, true);
    //   %90 = xor i32 %89, -1
    Value *val90 = builder.CreateXor(val89, builder.getInt32(-1), "");
    //   %91 = zext nneg i32 %90 to i64
    Value *val91 = builder.CreateZExt(val90, Type::getInt64Ty(context));
    //   %92 = and i64 %53, %91
    Value *val92 = builder.CreateAnd(val53, val91, "");
    //   %93 = zext nneg i8 %88 to i32
    Value *val93 = builder.CreateZExt(val88, Type::getInt32Ty(context));
    //   %94 = trunc i64 %85 to i32
    Value *val94 = builder.CreateTrunc(val85, Type::getInt32Ty(context));
    //   %95 = shl nuw nsw i32 %93, %94
    Value *val95 = builder.CreateShl(val93, val94, "", true, true);
    //   %96 = zext nneg i32 %95 to i64
    Value *val96 = builder.CreateZExt(val95, Type::getInt64Ty(context));
    //   %97 = icmp ugt i64 %92, %96
    Value *val97 = builder.CreateICmpUGT(val92, val96, "");
    //   %98 = zext i1 %97 to i32
    Value *val98 = builder.CreateZExt(val97, Type::getInt32Ty(context));
    //   %99 = tail call fastcc i32 @build_float(i8 noundef signext %71, i32 noundef %82, i64 noundef %84, i8 noundef signext %88, i32 noundef %98)
    Value *val99 = builder.CreateCall(funcbuild_float, {val71, val82, val84, val88, val98});
    //   br label %120
    builder.CreateBr(val120);
    builder.SetInsertPoint(val100);
    //   %101 = icmp ugt i32 %74, 24
    Value *val101 = builder.CreateICmpUGT(val74, builder.getInt32(24), "");
    //   br i1 %101, label %120, label %102
    builder.CreateCondBr(val101, val120, val102);
    builder.SetInsertPoint(val102);
    //   %103 = zext nneg i32 %74 to i64
    Value *val103 = builder.CreateZExt(val74, Type::getInt64Ty(context));
    //   %104 = shl nuw nsw i64 %42, %103
    Value *val104 = builder.CreateShl(val42, val103, "", true, true);
    //   %105 = sub nsw i64 %104, %53
    Value *val105 = builder.CreateSub(val104, val53, "", false, true);
    //   %106 = icmp ult i64 %105, 16777216
    Value *val106 = builder.CreateICmpULT(val105, builder.getInt64(16777216ll), "");
    //   %107 = icmp sgt i32 %69, -126
    Value *val107 = builder.CreateICmpSGT(val69, builder.getInt32(-126), "");
    //   %108 = select i1 %106, i1 %107, i1 false
    Value *val108 = builder.CreateSelect(val106, val107, builder.getInt1(false));
    //   br i1 %108, label %.preheader, label %.loopexit
    builder.CreateCondBr(val108, val_preheader, val_loopexit);
    builder.SetInsertPoint(val_preheader);
    //   %109 = phi i64 [ %111, %.preheader ], [ %105, %102 ]
    PHINode *val109 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %110 = phi i32 [ %112, %.preheader ], [ %68, %102 ]
    PHINode *val110 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %111 = shl nuw nsw i64 %109, 1
    Value *val111 = builder.CreateShl(val109, builder.getInt64(1ll), "", true, true);
    //   %112 = add nsw i32 %110, -1
    Value *val112 = builder.CreateAdd(val110, builder.getInt32(-1), "", false, true);
    //   %113 = icmp ult i64 %109, 8388608
    Value *val113 = builder.CreateICmpULT(val109, builder.getInt64(8388608ll), "");
    //   %114 = icmp sgt i32 %110, -125
    Value *val114 = builder.CreateICmpSGT(val110, builder.getInt32(-125), "");
    //   %115 = select i1 %113, i1 %114, i1 false
    Value *val115 = builder.CreateSelect(val113, val114, builder.getInt1(false));
    //   br i1 %115, label %.preheader, label %.loopexit, !llvm.loop !4
    builder.CreateCondBr(val115, val_preheader, val_loopexit);
    builder.SetInsertPoint(val_loopexit);
    //   %116 = phi i32 [ %69, %102 ], [ %112, %.preheader ]
    PHINode *val116 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %117 = phi i64 [ %105, %102 ], [ %111, %.preheader ]
    PHINode *val117 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %118 = tail call fastcc i32 @build_float(i8 noundef signext %71, i32 noundef %116, i64 noundef %117, i8 noundef signext 0, i32 noundef 0)
    Value *val118 = builder.CreateCall(funcbuild_float, {val71, val116, val117, builder.getInt8(0), builder.getInt32(0)});
    //   br label %120
    builder.CreateBr(val120);
    builder.SetInsertPoint(val119);
    //   br label %120
    builder.CreateBr(val120);
    builder.SetInsertPoint(val120);
    //   %121 = phi i32 [ %23, %20 ], [ -1, %8 ], [ -1, %2 ], [ %0, %24 ], [ %1, %25 ], [ %99, %75 ], [ %118, %.loopexit ], [ %31, %100 ], [ %0, %18 ], [ %1, %119 ]
    PHINode *val121 = builder.CreatePHI(Type::getInt32Ty(context), 10);
    //   ret i32 %121
    builder.CreateRet(val121);
    s0->addCase(builder.getInt32(0), val120);
    s0->addCase(builder.getInt32(2139095040), val119);
    val109->addIncoming(val111, val_preheader);
    val109->addIncoming(val105, val102);
    val110->addIncoming(val112, val_preheader);
    val110->addIncoming(val68, val102);
    val116->addIncoming(val69, val102);
    val116->addIncoming(val112, val_preheader);
    val117->addIncoming(val105, val102);
    val117->addIncoming(val111, val_preheader);
    val121->addIncoming(val23, val20);
    val121->addIncoming(builder.getInt32(-1), val8);
    val121->addIncoming(builder.getInt32(-1), val2);
    val121->addIncoming(val0, val24);
    val121->addIncoming(val1, val25);
    val121->addIncoming(val99, val75);
    val121->addIncoming(val118, val_loopexit);
    val121->addIncoming(val31, val100);
    val121->addIncoming(val0, val18);
    val121->addIncoming(val1, val119);
  }
  {
    Function *func = funcf32_less;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val20 = BasicBlock::Create(context, "", func);
    BasicBlock *val23 = BasicBlock::Create(context, "", func);
    BasicBlock *val29 = BasicBlock::Create(context, "", func);
    BasicBlock *val33 = BasicBlock::Create(context, "", func);
    BasicBlock *val36 = BasicBlock::Create(context, "", func);
    BasicBlock *val41 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %0, 2139095040
    Value *val3 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %4 = icmp ne i32 %3, 2139095040
    Value *val4 = builder.CreateICmpNE(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %0, 8388607
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %6 = icmp eq i32 %5, 0
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %7 = or i1 %4, %6
    Value *val7 = builder.CreateOr(val4, val6, "");
    //   br i1 %7, label %8, label %41
    builder.CreateCondBr(val7, val8, val41);
    builder.SetInsertPoint(val8);
    //   %9 = and i32 %1, 2139095040
    Value *val9 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %10 = icmp ne i32 %9, 2139095040
    Value *val10 = builder.CreateICmpNE(val9, builder.getInt32(2139095040), "");
    //   %11 = and i32 %1, 8388607
    Value *val11 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %12 = icmp eq i32 %11, 0
    Value *val12 = builder.CreateICmpEQ(val11, builder.getInt32(0), "");
    //   %13 = or i1 %10, %12
    Value *val13 = builder.CreateOr(val10, val12, "");
    //   br i1 %13, label %14, label %41
    builder.CreateCondBr(val13, val14, val41);
    builder.SetInsertPoint(val14);
    //   %15 = and i32 %0, 2147483647
    Value *val15 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %16 = icmp eq i32 %15, 2139095040
    Value *val16 = builder.CreateICmpEQ(val15, builder.getInt32(2139095040), "");
    //   %17 = and i32 %1, 2147483647
    Value *val17 = builder.CreateAnd(val1, builder.getInt32(2147483647), "");
    //   %18 = icmp eq i32 %17, 2139095040
    Value *val18 = builder.CreateICmpEQ(val17, builder.getInt32(2139095040), "");
    //   %19 = and i1 %16, %18
    Value *val19 = builder.CreateAnd(val16, val18, "");
    //   br i1 %19, label %20, label %23
    builder.CreateCondBr(val19, val20, val23);
    builder.SetInsertPoint(val20);
    //   %21 = xor i32 %1, %0
    Value *val21 = builder.CreateXor(val1, val0, "");
    //   %22 = icmp sgt i32 %21, -1
    Value *val22 = builder.CreateICmpSGT(val21, builder.getInt32(-1), "");
    //   br i1 %22, label %41, label %29
    builder.CreateCondBr(val22, val41, val29);
    builder.SetInsertPoint(val23);
    //   %24 = or i32 %1, %0
    Value *val24 = builder.CreateOr(val1, val0, "");
    //   %25 = and i32 %24, 2147483647
    Value *val25 = builder.CreateAnd(val24, builder.getInt32(2147483647), "");
    //   %26 = icmp eq i32 %25, 0
    Value *val26 = builder.CreateICmpEQ(val25, builder.getInt32(0), "");
    //   %27 = icmp eq i32 %0, %1
    Value *val27 = builder.CreateICmpEQ(val0, val1, "");
    //   %28 = or i1 %27, %26
    Value *val28 = builder.CreateOr(val27, val26, "");
    //   br i1 %28, label %41, label %29
    builder.CreateCondBr(val28, val41, val29);
    builder.SetInsertPoint(val29);
    //   %30 = lshr i32 %0, 31
    Value *val30 = builder.CreateLShr(val0, builder.getInt32(31), "", false);
    //   %31 = lshr i32 %1, 31
    Value *val31 = builder.CreateLShr(val1, builder.getInt32(31), "", false);
    //   %32 = icmp eq i32 %30, %31
    Value *val32 = builder.CreateICmpEQ(val30, val31, "");
    //   br i1 %32, label %36, label %33
    builder.CreateCondBr(val32, val36, val33);
    builder.SetInsertPoint(val33);
    //   %34 = icmp ugt i32 %30, %31
    Value *val34 = builder.CreateICmpUGT(val30, val31, "");
    //   %35 = zext i1 %34 to i8
    Value *val35 = builder.CreateZExt(val34, Type::getInt8Ty(context));
    //   br label %41
    builder.CreateBr(val41);
    builder.SetInsertPoint(val36);
    //   %37 = icmp ult i32 %0, %1
    Value *val37 = builder.CreateICmpULT(val0, val1, "");
    //   %38 = zext i1 %37 to i32
    Value *val38 = builder.CreateZExt(val37, Type::getInt32Ty(context));
    //   %39 = xor i32 %30, %38
    Value *val39 = builder.CreateXor(val30, val38, "");
    //   %40 = trunc i32 %39 to i8
    Value *val40 = builder.CreateTrunc(val39, Type::getInt8Ty(context));
    //   br label %41
    builder.CreateBr(val41);
    builder.SetInsertPoint(val41);
    //   %42 = phi i8 [ 0, %23 ], [ 0, %8 ], [ 0, %2 ], [ %35, %33 ], [ %40, %36 ], [ 0, %20 ]
    PHINode *val42 = builder.CreatePHI(Type::getInt8Ty(context), 6);
    //   ret i8 %42
    builder.CreateRet(val42);
    val42->addIncoming(builder.getInt8(0), val23);
    val42->addIncoming(builder.getInt8(0), val8);
    val42->addIncoming(builder.getInt8(0), val2);
    val42->addIncoming(val35, val33);
    val42->addIncoming(val40, val36);
    val42->addIncoming(builder.getInt8(0), val20);
  }
  {
    Function *func = funcbuild_float;
    BasicBlock *val5 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit = BasicBlock::Create(context, "", func);
    BasicBlock *val26 = BasicBlock::Create(context, "", func);
    BasicBlock *val33 = BasicBlock::Create(context, "", func);
    BasicBlock *val39 = BasicBlock::Create(context, "", func);
    BasicBlock *val42 = BasicBlock::Create(context, "", func);
    BasicBlock *val46 = BasicBlock::Create(context, "", func);
    BasicBlock *val54 = BasicBlock::Create(context, "", func);
    BasicBlock *val57 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    Value *val2 = func->getArg(2);
    Value *val3 = func->getArg(3);
    Value *val4 = func->getArg(4);
    builder.SetInsertPoint(val5);
    //   %6 = icmp ugt i64 %2, 16777215
    Value *val6 = builder.CreateICmpUGT(val2, builder.getInt64(16777215ll), "");
    //   %7 = icmp slt i32 %1, -126
    Value *val7 = builder.CreateICmpSLT(val1, builder.getInt32(-126), "");
    //   %8 = or i1 %7, %6
    Value *val8 = builder.CreateOr(val7, val6, "");
    //   br i1 %8, label %.preheader, label %.loopexit
    builder.CreateCondBr(val8, val_preheader, val_loopexit);
    builder.SetInsertPoint(val_preheader);
    //   %9 = phi i32 [ %15, %.preheader ], [ %4, %5 ]
    PHINode *val9 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %10 = phi i64 [ %16, %.preheader ], [ %2, %5 ]
    PHINode *val10 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %11 = phi i32 [ %17, %.preheader ], [ %1, %5 ]
    PHINode *val11 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %12 = trunc i64 %10 to i8
    Value *val12 = builder.CreateTrunc(val10, Type::getInt8Ty(context));
    //   %13 = and i8 %12, 1
    Value *val13 = builder.CreateAnd(val12, builder.getInt8(1), "");
    //   %14 = zext nneg i8 %13 to i32
    Value *val14 = builder.CreateZExt(val13, Type::getInt32Ty(context));
    //   %15 = add i32 %9, %14
    Value *val15 = builder.CreateAdd(val9, val14, "", false, false);
    //   %16 = lshr i64 %10, 1
    Value *val16 = builder.CreateLShr(val10, builder.getInt64(1ll), "", false);
    //   %17 = add i32 %11, 1
    Value *val17 = builder.CreateAdd(val11, builder.getInt32(1), "", false, false);
    //   %18 = icmp ugt i64 %10, 33554431
    Value *val18 = builder.CreateICmpUGT(val10, builder.getInt64(33554431ll), "");
    //   %19 = icmp slt i32 %17, -126
    Value *val19 = builder.CreateICmpSLT(val17, builder.getInt32(-126), "");
    //   %20 = select i1 %18, i1 true, i1 %19
    Value *val20 = builder.CreateSelect(val18, builder.getInt1(true), val19);
    //   br i1 %20, label %.preheader, label %.loopexit, !llvm.loop !4
    builder.CreateCondBr(val20, val_preheader, val_loopexit);
    builder.SetInsertPoint(val_loopexit);
    //   %21 = phi i32 [ %1, %5 ], [ %17, %.preheader ]
    PHINode *val21 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %22 = phi i64 [ %2, %5 ], [ %16, %.preheader ]
    PHINode *val22 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %23 = phi i8 [ %3, %5 ], [ %13, %.preheader ]
    PHINode *val23 = builder.CreatePHI(Type::getInt8Ty(context), 2);
    //   %24 = phi i32 [ %4, %5 ], [ %15, %.preheader ]
    PHINode *val24 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %25 = icmp eq i8 %23, 0
    Value *val25 = builder.CreateICmpEQ(val23, builder.getInt8(0), "");
    //   br i1 %25, label %33, label %26
    builder.CreateCondBr(val25, val33, val26);
    builder.SetInsertPoint(val26);
    //   %27 = icmp sgt i32 %24, 1
    Value *val27 = builder.CreateICmpSGT(val24, builder.getInt32(1), "");
    //   %28 = and i64 %22, 1
    Value *val28 = builder.CreateAnd(val22, builder.getInt64(1ll), "");
    //   %29 = icmp ne i64 %28, 0
    Value *val29 = builder.CreateICmpNE(val28, builder.getInt64(0ll), "");
    //   %30 = or i1 %29, %27
    Value *val30 = builder.CreateOr(val29, val27, "");
    //   %31 = zext i1 %30 to i64
    Value *val31 = builder.CreateZExt(val30, Type::getInt64Ty(context));
    //   %32 = add nuw nsw i64 %22, %31
    Value *val32 = builder.CreateAdd(val22, val31, "", true, true);
    //   br label %33
    builder.CreateBr(val33);
    builder.SetInsertPoint(val33);
    //   %34 = phi i64 [ %22, %.loopexit ], [ %32, %26 ]
    PHINode *val34 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %35 = icmp ugt i64 %34, 16777215
    Value *val35 = builder.CreateICmpUGT(val34, builder.getInt64(16777215ll), "");
    //   %36 = zext i1 %35 to i32
    Value *val36 = builder.CreateZExt(val35, Type::getInt32Ty(context));
    //   %37 = add i32 %21, %36
    Value *val37 = builder.CreateAdd(val21, val36, "", false, false);
    //   %38 = icmp sgt i32 %37, 127
    Value *val38 = builder.CreateICmpSGT(val37, builder.getInt32(127), "");
    //   br i1 %38, label %39, label %42
    builder.CreateCondBr(val38, val39, val42);
    builder.SetInsertPoint(val39);
    //   %40 = zext nneg i8 %0 to i32
    Value *val40 = builder.CreateZExt(val0, Type::getInt32Ty(context));
    //   %41 = shl nuw i32 %40, 31
    Value *val41 = builder.CreateShl(val40, builder.getInt32(31), "", true, false);
    //   br label %57
    builder.CreateBr(val57);
    builder.SetInsertPoint(val42);
    //   %43 = select i1 %35, i64 8388608, i64 %34
    Value *val43 = builder.CreateSelect(val35, builder.getInt64(8388608ll), val34);
    //   %44 = icmp ugt i64 %43, 8388607
    Value *val44 = builder.CreateICmpUGT(val43, builder.getInt64(8388607ll), "");
    //   %45 = trunc i64 %43 to i32
    Value *val45 = builder.CreateTrunc(val43, Type::getInt32Ty(context));
    //   br i1 %44, label %46, label %54
    builder.CreateCondBr(val44, val46, val54);
    builder.SetInsertPoint(val46);
    //   %47 = and i32 %45, 8388607
    Value *val47 = builder.CreateAnd(val45, builder.getInt32(8388607), "");
    //   %48 = shl i32 %37, 23
    Value *val48 = builder.CreateShl(val37, builder.getInt32(23), "", false, false);
    //   %49 = add i32 %48, 1065353216
    Value *val49 = builder.CreateAdd(val48, builder.getInt32(1065353216), "", false, false);
    //   %50 = and i32 %49, 2139095040
    Value *val50 = builder.CreateAnd(val49, builder.getInt32(2139095040), "");
    //   %51 = or disjoint i32 %50, %47
    Value *val51 = builder.CreateOr(val50, val47, "");
    //   %52 = zext nneg i8 %0 to i32
    Value *val52 = builder.CreateZExt(val0, Type::getInt32Ty(context));
    //   %53 = shl nuw i32 %52, 31
    Value *val53 = builder.CreateShl(val52, builder.getInt32(31), "", true, false);
    //   br label %57
    builder.CreateBr(val57);
    builder.SetInsertPoint(val54);
    //   %55 = zext nneg i8 %0 to i32
    Value *val55 = builder.CreateZExt(val0, Type::getInt32Ty(context));
    //   %56 = shl nuw i32 %55, 31
    Value *val56 = builder.CreateShl(val55, builder.getInt32(31), "", true, false);
    //   br label %57
    builder.CreateBr(val57);
    builder.SetInsertPoint(val57);
    //   %58 = phi i32 [ %45, %54 ], [ %53, %46 ], [ 2139095040, %39 ]
    PHINode *val58 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %59 = phi i32 [ %56, %54 ], [ %51, %46 ], [ %41, %39 ]
    PHINode *val59 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %60 = or disjoint i32 %59, %58
    Value *val60 = builder.CreateOr(val59, val58, "");
    //   ret i32 %60
    builder.CreateRet(val60);
    val9->addIncoming(val15, val_preheader);
    val9->addIncoming(val4, val5);
    val10->addIncoming(val16, val_preheader);
    val10->addIncoming(val2, val5);
    val11->addIncoming(val17, val_preheader);
    val11->addIncoming(val1, val5);
    val21->addIncoming(val1, val5);
    val21->addIncoming(val17, val_preheader);
    val22->addIncoming(val2, val5);
    val22->addIncoming(val16, val_preheader);
    val23->addIncoming(val3, val5);
    val23->addIncoming(val13, val_preheader);
    val24->addIncoming(val4, val5);
    val24->addIncoming(val15, val_preheader);
    val34->addIncoming(val22, val_loopexit);
    val34->addIncoming(val32, val26);
    val58->addIncoming(val45, val54);
    val58->addIncoming(val53, val46);
    val58->addIncoming(builder.getInt32(2139095040), val39);
    val59->addIncoming(val56, val54);
    val59->addIncoming(val51, val46);
    val59->addIncoming(val41, val39);
  }
  {
    Function *func = funcf32_is_nan;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2139095040
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %3 = icmp eq i32 %2, 2139095040
    Value *val3 = builder.CreateICmpEQ(val2, builder.getInt32(2139095040), "");
    //   %4 = and i32 %0, 8388607
    Value *val4 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %5 = icmp ne i32 %4, 0
    Value *val5 = builder.CreateICmpNE(val4, builder.getInt32(0), "");
    //   %6 = and i1 %3, %5
    Value *val6 = builder.CreateAnd(val3, val5, "");
    //   %7 = zext i1 %6 to i8
    Value *val7 = builder.CreateZExt(val6, Type::getInt8Ty(context));
    //   ret i8 %7
    builder.CreateRet(val7);
  }
  {
    Function *func = funcf32_is_inf;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2147483647
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %3 = icmp eq i32 %2, 2139095040
    Value *val3 = builder.CreateICmpEQ(val2, builder.getInt32(2139095040), "");
    //   %4 = zext i1 %3 to i8
    Value *val4 = builder.CreateZExt(val3, Type::getInt8Ty(context));
    //   ret i8 %4
    builder.CreateRet(val4);
  }
  {
    Function *func = funcf32_is_zero;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2147483647
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %3 = icmp eq i32 %2, 0
    Value *val3 = builder.CreateICmpEQ(val2, builder.getInt32(0), "");
    //   %4 = zext i1 %3 to i8
    Value *val4 = builder.CreateZExt(val3, Type::getInt8Ty(context));
    //   ret i8 %4
    builder.CreateRet(val4);
  }
  {
    Function *func = funcf32_negate;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2139095040
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %3 = icmp ne i32 %2, 2139095040
    Value *val3 = builder.CreateICmpNE(val2, builder.getInt32(2139095040), "");
    //   %4 = and i32 %0, 8388607
    Value *val4 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %5 = icmp eq i32 %4, 0
    Value *val5 = builder.CreateICmpEQ(val4, builder.getInt32(0), "");
    //   %6 = or i1 %3, %5
    Value *val6 = builder.CreateOr(val3, val5, "");
    //   %7 = xor i32 %0, -2147483648
    Value *val7 = builder.CreateXor(val0, builder.getInt32(-2147483648), "");
    //   %8 = select i1 %6, i32 %7, i32 %0
    Value *val8 = builder.CreateSelect(val6, val7, val0);
    //   ret i32 %8
    builder.CreateRet(val8);
  }
  {
    Function *func = funcf32_sub;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %1, 2139095040
    Value *val3 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %4 = icmp ne i32 %3, 2139095040
    Value *val4 = builder.CreateICmpNE(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %1, 8388607
    Value *val5 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %6 = icmp eq i32 %5, 0
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %7 = or i1 %4, %6
    Value *val7 = builder.CreateOr(val4, val6, "");
    //   %8 = xor i32 %1, -2147483648
    Value *val8 = builder.CreateXor(val1, builder.getInt32(-2147483648), "");
    //   %9 = select i1 %7, i32 %8, i32 %1
    Value *val9 = builder.CreateSelect(val7, val8, val1);
    //   %10 = tail call i32 @f32_add(i32 noundef %0, i32 noundef %9)
    Value *val10 = builder.CreateCall(funcf32_add, {val0, val9});
    //   ret i32 %10
    builder.CreateRet(val10);
  }
  {
    Function *func = funcf32_mul;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val23 = BasicBlock::Create(context, "", func);
    BasicBlock *val24 = BasicBlock::Create(context, "", func);
    BasicBlock *val28 = BasicBlock::Create(context, "", func);
    BasicBlock *val31 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader_i = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit_i = BasicBlock::Create(context, "", func);
    BasicBlock *val74 = BasicBlock::Create(context, "", func);
    BasicBlock *val_loopexit_i_thread = BasicBlock::Create(context, "", func);
    BasicBlock *val87 = BasicBlock::Create(context, "", func);
    BasicBlock *val91 = BasicBlock::Create(context, "", func);
    BasicBlock *valbuild_float_exit = BasicBlock::Create(context, "", func);
    BasicBlock *val100 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %0, 2139095040
    Value *val3 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %4 = icmp eq i32 %3, 2139095040
    Value *val4 = builder.CreateICmpEQ(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %0, 8388607
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %6 = icmp ne i32 %5, 0
    Value *val6 = builder.CreateICmpNE(val5, builder.getInt32(0), "");
    //   %7 = and i1 %4, %6
    Value *val7 = builder.CreateAnd(val4, val6, "");
    //   br i1 %7, label %100, label %8
    builder.CreateCondBr(val7, val100, val8);
    builder.SetInsertPoint(val8);
    //   %9 = and i32 %1, 2139095040
    Value *val9 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %10 = icmp eq i32 %9, 2139095040
    Value *val10 = builder.CreateICmpEQ(val9, builder.getInt32(2139095040), "");
    //   %11 = and i32 %1, 8388607
    Value *val11 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %12 = icmp ne i32 %11, 0
    Value *val12 = builder.CreateICmpNE(val11, builder.getInt32(0), "");
    //   %13 = and i1 %10, %12
    Value *val13 = builder.CreateAnd(val10, val12, "");
    //   br i1 %13, label %100, label %14
    builder.CreateCondBr(val13, val100, val14);
    builder.SetInsertPoint(val14);
    //   %15 = and i32 %0, 2147483647
    Value *val15 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %16 = icmp eq i32 %15, 2139095040
    Value *val16 = builder.CreateICmpEQ(val15, builder.getInt32(2139095040), "");
    //   %17 = and i32 %1, 2147483647
    Value *val17 = builder.CreateAnd(val1, builder.getInt32(2147483647), "");
    //   %18 = icmp eq i32 %17, 2139095040
    Value *val18 = builder.CreateICmpEQ(val17, builder.getInt32(2139095040), "");
    //   %19 = or i1 %16, %18
    Value *val19 = builder.CreateOr(val16, val18, "");
    //   %20 = icmp eq i32 %15, 0
    Value *val20 = builder.CreateICmpEQ(val15, builder.getInt32(0), "");
    //   %21 = icmp eq i32 %17, 0
    Value *val21 = builder.CreateICmpEQ(val17, builder.getInt32(0), "");
    //   %22 = or i1 %20, %21
    Value *val22 = builder.CreateOr(val20, val21, "");
    //   br i1 %19, label %23, label %28
    builder.CreateCondBr(val19, val23, val28);
    builder.SetInsertPoint(val23);
    //   br i1 %22, label %100, label %24
    builder.CreateCondBr(val22, val100, val24);
    builder.SetInsertPoint(val24);
    //   %25 = xor i32 %1, %0
    Value *val25 = builder.CreateXor(val1, val0, "");
    //   %26 = and i32 %25, -2147483648
    Value *val26 = builder.CreateAnd(val25, builder.getInt32(-2147483648), "");
    //   %27 = or disjoint i32 %26, 2139095040
    Value *val27 = builder.CreateOr(val26, builder.getInt32(2139095040), "");
    //   br label %100
    builder.CreateBr(val100);
    builder.SetInsertPoint(val28);
    //   %29 = xor i32 %1, %0
    Value *val29 = builder.CreateXor(val1, val0, "");
    //   %30 = and i32 %29, -2147483648
    Value *val30 = builder.CreateAnd(val29, builder.getInt32(-2147483648), "");
    //   br i1 %22, label %100, label %31
    builder.CreateCondBr(val22, val100, val31);
    builder.SetInsertPoint(val31);
    //   %32 = zext nneg i32 %5 to i64
    Value *val32 = builder.CreateZExt(val5, Type::getInt64Ty(context));
    //   %33 = icmp ne i32 %3, 0
    Value *val33 = builder.CreateICmpNE(val3, builder.getInt32(0), "");
    //   %34 = icmp eq i32 %5, 0
    Value *val34 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %35 = or i1 %33, %34
    Value *val35 = builder.CreateOr(val33, val34, "");
    //   %36 = or disjoint i64 %32, 8388608
    Value *val36 = builder.CreateOr(val32, builder.getInt64(8388608ll), "");
    //   %37 = select i1 %35, i64 %36, i64 %32
    Value *val37 = builder.CreateSelect(val35, val36, val32);
    //   %38 = zext nneg i32 %11 to i64
    Value *val38 = builder.CreateZExt(val11, Type::getInt64Ty(context));
    //   %39 = icmp ne i32 %9, 0
    Value *val39 = builder.CreateICmpNE(val9, builder.getInt32(0), "");
    //   %40 = icmp eq i32 %11, 0
    Value *val40 = builder.CreateICmpEQ(val11, builder.getInt32(0), "");
    //   %41 = or i1 %39, %40
    Value *val41 = builder.CreateOr(val39, val40, "");
    //   %42 = or disjoint i64 %38, 8388608
    Value *val42 = builder.CreateOr(val38, builder.getInt64(8388608ll), "");
    //   %43 = select i1 %41, i64 %42, i64 %38
    Value *val43 = builder.CreateSelect(val41, val42, val38);
    //   %44 = mul nuw nsw i64 %43, %37
    Value *val44 = builder.CreateMul(val43, val37, "", true, true);
    //   %45 = icmp eq i32 %3, 0
    Value *val45 = builder.CreateICmpEQ(val3, builder.getInt32(0), "");
    //   %46 = and i1 %45, %6
    Value *val46 = builder.CreateAnd(val45, val6, "");
    //   %47 = lshr i32 %0, 23
    Value *val47 = builder.CreateLShr(val0, builder.getInt32(23), "", false);
    //   %48 = and i32 %47, 255
    Value *val48 = builder.CreateAnd(val47, builder.getInt32(255), "");
    //   %49 = add nsw i32 %48, -127
    Value *val49 = builder.CreateAdd(val48, builder.getInt32(-127), "", false, true);
    //   %50 = select i1 %46, i32 -126, i32 %49
    Value *val50 = builder.CreateSelect(val46, builder.getInt32(-126), val49);
    //   %51 = icmp eq i32 %9, 0
    Value *val51 = builder.CreateICmpEQ(val9, builder.getInt32(0), "");
    //   %52 = and i1 %51, %12
    Value *val52 = builder.CreateAnd(val51, val12, "");
    //   %53 = lshr i32 %1, 23
    Value *val53 = builder.CreateLShr(val1, builder.getInt32(23), "", false);
    //   %54 = and i32 %53, 255
    Value *val54 = builder.CreateAnd(val53, builder.getInt32(255), "");
    //   %55 = add nsw i32 %54, -150
    Value *val55 = builder.CreateAdd(val54, builder.getInt32(-150), "", false, true);
    //   %56 = select i1 %52, i32 -149, i32 %55
    Value *val56 = builder.CreateSelect(val52, builder.getInt32(-149), val55);
    //   %57 = add nsw i32 %56, %50
    Value *val57 = builder.CreateAdd(val56, val50, "", false, true);
    //   %58 = icmp ugt i64 %44, 16777215
    Value *val58 = builder.CreateICmpUGT(val44, builder.getInt64(16777215ll), "");
    //   %59 = icmp slt i32 %57, -126
    Value *val59 = builder.CreateICmpSLT(val57, builder.getInt32(-126), "");
    //   %60 = or i1 %59, %58
    Value *val60 = builder.CreateOr(val59, val58, "");
    //   br i1 %60, label %.preheader.i, label %.loopexit.i.thread
    builder.CreateCondBr(val60, val_preheader_i, val_loopexit_i_thread);
    builder.SetInsertPoint(val_preheader_i);
    //   %61 = phi i32 [ %67, %.preheader.i ], [ 0, %31 ]
    PHINode *val61 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %62 = phi i64 [ %68, %.preheader.i ], [ %44, %31 ]
    PHINode *val62 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %63 = phi i32 [ %69, %.preheader.i ], [ %57, %31 ]
    PHINode *val63 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %64 = trunc i64 %62 to i8
    Value *val64 = builder.CreateTrunc(val62, Type::getInt8Ty(context));
    //   %65 = and i8 %64, 1
    Value *val65 = builder.CreateAnd(val64, builder.getInt8(1), "");
    //   %66 = zext nneg i8 %65 to i32
    Value *val66 = builder.CreateZExt(val65, Type::getInt32Ty(context));
    //   %67 = add i32 %61, %66
    Value *val67 = builder.CreateAdd(val61, val66, "", false, false);
    //   %68 = lshr i64 %62, 1
    Value *val68 = builder.CreateLShr(val62, builder.getInt64(1ll), "", false);
    //   %69 = add i32 %63, 1
    Value *val69 = builder.CreateAdd(val63, builder.getInt32(1), "", false, false);
    //   %70 = icmp ugt i64 %62, 33554431
    Value *val70 = builder.CreateICmpUGT(val62, builder.getInt64(33554431ll), "");
    //   %71 = icmp slt i32 %69, -126
    Value *val71 = builder.CreateICmpSLT(val69, builder.getInt32(-126), "");
    //   %72 = select i1 %70, i1 true, i1 %71
    Value *val72 = builder.CreateSelect(val70, builder.getInt1(true), val71);
    //   br i1 %72, label %.preheader.i, label %.loopexit.i, !llvm.loop !4
    builder.CreateCondBr(val72, val_preheader_i, val_loopexit_i);
    builder.SetInsertPoint(val_loopexit_i);
    //   %73 = icmp eq i8 %65, 0
    Value *val73 = builder.CreateICmpEQ(val65, builder.getInt8(0), "");
    //   br i1 %73, label %.loopexit.i.thread, label %74
    builder.CreateCondBr(val73, val_loopexit_i_thread, val74);
    builder.SetInsertPoint(val74);
    //   %75 = icmp sgt i32 %67, 1
    Value *val75 = builder.CreateICmpSGT(val67, builder.getInt32(1), "");
    //   %76 = and i64 %62, 2
    Value *val76 = builder.CreateAnd(val62, builder.getInt64(2ll), "");
    //   %77 = icmp ne i64 %76, 0
    Value *val77 = builder.CreateICmpNE(val76, builder.getInt64(0ll), "");
    //   %78 = or i1 %77, %75
    Value *val78 = builder.CreateOr(val77, val75, "");
    //   %79 = zext i1 %78 to i64
    Value *val79 = builder.CreateZExt(val78, Type::getInt64Ty(context));
    //   %80 = add nuw nsw i64 %68, %79
    Value *val80 = builder.CreateAdd(val68, val79, "", true, true);
    //   br label %.loopexit.i.thread
    builder.CreateBr(val_loopexit_i_thread);
    builder.SetInsertPoint(val_loopexit_i_thread);
    //   %81 = phi i32 [ %69, %.loopexit.i ], [ %69, %74 ], [ %57, %31 ]
    PHINode *val81 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %82 = phi i64 [ %68, %.loopexit.i ], [ %80, %74 ], [ %44, %31 ]
    PHINode *val82 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %83 = icmp ugt i64 %82, 16777215
    Value *val83 = builder.CreateICmpUGT(val82, builder.getInt64(16777215ll), "");
    //   %84 = zext i1 %83 to i32
    Value *val84 = builder.CreateZExt(val83, Type::getInt32Ty(context));
    //   %85 = add i32 %81, %84
    Value *val85 = builder.CreateAdd(val81, val84, "", false, false);
    //   %86 = icmp sgt i32 %85, 127
    Value *val86 = builder.CreateICmpSGT(val85, builder.getInt32(127), "");
    //   br i1 %86, label %build_float.exit, label %87
    builder.CreateCondBr(val86, valbuild_float_exit, val87);
    builder.SetInsertPoint(val87);
    //   %88 = select i1 %83, i64 8388608, i64 %82
    Value *val88 = builder.CreateSelect(val83, builder.getInt64(8388608ll), val82);
    //   %89 = icmp ugt i64 %88, 8388607
    Value *val89 = builder.CreateICmpUGT(val88, builder.getInt64(8388607ll), "");
    //   %90 = trunc i64 %88 to i32
    Value *val90 = builder.CreateTrunc(val88, Type::getInt32Ty(context));
    //   br i1 %89, label %91, label %build_float.exit
    builder.CreateCondBr(val89, val91, valbuild_float_exit);
    builder.SetInsertPoint(val91);
    //   %92 = and i32 %90, 8388607
    Value *val92 = builder.CreateAnd(val90, builder.getInt32(8388607), "");
    //   %93 = shl i32 %85, 23
    Value *val93 = builder.CreateShl(val85, builder.getInt32(23), "", false, false);
    //   %94 = add i32 %93, 1065353216
    Value *val94 = builder.CreateAdd(val93, builder.getInt32(1065353216), "", false, false);
    //   %95 = and i32 %94, 2139095040
    Value *val95 = builder.CreateAnd(val94, builder.getInt32(2139095040), "");
    //   %96 = or disjoint i32 %95, %92
    Value *val96 = builder.CreateOr(val95, val92, "");
    //   br label %build_float.exit
    builder.CreateBr(valbuild_float_exit);
    builder.SetInsertPoint(valbuild_float_exit);
    //   %97 = phi i32 [ %30, %91 ], [ 2139095040, %.loopexit.i.thread ], [ %90, %87 ]
    PHINode *val97 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %98 = phi i32 [ %96, %91 ], [ %30, %.loopexit.i.thread ], [ %30, %87 ]
    PHINode *val98 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %99 = or disjoint i32 %98, %97
    Value *val99 = builder.CreateOr(val98, val97, "");
    //   br label %100
    builder.CreateBr(val100);
    builder.SetInsertPoint(val100);
    //   %101 = phi i32 [ %27, %24 ], [ %99, %build_float.exit ], [ -1, %8 ], [ -1, %2 ], [ -1, %23 ], [ %30, %28 ]
    PHINode *val101 = builder.CreatePHI(Type::getInt32Ty(context), 6);
    //   ret i32 %101
    builder.CreateRet(val101);
    val61->addIncoming(val67, val_preheader_i);
    val61->addIncoming(builder.getInt32(0), val31);
    val62->addIncoming(val68, val_preheader_i);
    val62->addIncoming(val44, val31);
    val63->addIncoming(val69, val_preheader_i);
    val63->addIncoming(val57, val31);
    val81->addIncoming(val69, val_loopexit_i);
    val81->addIncoming(val69, val74);
    val81->addIncoming(val57, val31);
    val82->addIncoming(val68, val_loopexit_i);
    val82->addIncoming(val80, val74);
    val82->addIncoming(val44, val31);
    val97->addIncoming(val30, val91);
    val97->addIncoming(builder.getInt32(2139095040), val_loopexit_i_thread);
    val97->addIncoming(val90, val87);
    val98->addIncoming(val96, val91);
    val98->addIncoming(val30, val_loopexit_i_thread);
    val98->addIncoming(val30, val87);
    val101->addIncoming(val27, val24);
    val101->addIncoming(val99, valbuild_float_exit);
    val101->addIncoming(builder.getInt32(-1), val8);
    val101->addIncoming(builder.getInt32(-1), val2);
    val101->addIncoming(builder.getInt32(-1), val23);
    val101->addIncoming(val30, val28);
  }
  {
    Function *func = funcf32_div;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val20 = BasicBlock::Create(context, "", func);
    BasicBlock *val25 = BasicBlock::Create(context, "", func);
    BasicBlock *val28 = BasicBlock::Create(context, "", func);
    BasicBlock *val32 = BasicBlock::Create(context, "", func);
    BasicBlock *val35 = BasicBlock::Create(context, "", func);
    BasicBlock *val37 = BasicBlock::Create(context, "", func);
    BasicBlock *val63 = BasicBlock::Create(context, "", func);
    BasicBlock *val74 = BasicBlock::Create(context, "", func);
    BasicBlock *val85 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %0, 2139095040
    Value *val3 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %4 = icmp eq i32 %3, 2139095040
    Value *val4 = builder.CreateICmpEQ(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %0, 8388607
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %6 = icmp ne i32 %5, 0
    Value *val6 = builder.CreateICmpNE(val5, builder.getInt32(0), "");
    //   %7 = and i1 %4, %6
    Value *val7 = builder.CreateAnd(val4, val6, "");
    //   br i1 %7, label %85, label %8
    builder.CreateCondBr(val7, val85, val8);
    builder.SetInsertPoint(val8);
    //   %9 = and i32 %1, 2139095040
    Value *val9 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %10 = icmp eq i32 %9, 2139095040
    Value *val10 = builder.CreateICmpEQ(val9, builder.getInt32(2139095040), "");
    //   %11 = and i32 %1, 8388607
    Value *val11 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %12 = icmp ne i32 %11, 0
    Value *val12 = builder.CreateICmpNE(val11, builder.getInt32(0), "");
    //   %13 = and i1 %10, %12
    Value *val13 = builder.CreateAnd(val10, val12, "");
    //   br i1 %13, label %85, label %14
    builder.CreateCondBr(val13, val85, val14);
    builder.SetInsertPoint(val14);
    //   %15 = and i32 %0, 2147483647
    Value *val15 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %16 = icmp eq i32 %15, 2139095040
    Value *val16 = builder.CreateICmpEQ(val15, builder.getInt32(2139095040), "");
    //   %17 = and i32 %1, 2147483647
    Value *val17 = builder.CreateAnd(val1, builder.getInt32(2147483647), "");
    //   %18 = icmp eq i32 %17, 2139095040
    Value *val18 = builder.CreateICmpEQ(val17, builder.getInt32(2139095040), "");
    //   %19 = and i1 %16, %18
    Value *val19 = builder.CreateAnd(val16, val18, "");
    //   br i1 %19, label %85, label %20
    builder.CreateCondBr(val19, val85, val20);
    builder.SetInsertPoint(val20);
    //   %21 = icmp eq i32 %15, 0
    Value *val21 = builder.CreateICmpEQ(val15, builder.getInt32(0), "");
    //   %22 = or i32 %1, %0
    Value *val22 = builder.CreateOr(val1, val0, "");
    //   %23 = and i32 %22, 2147483647
    Value *val23 = builder.CreateAnd(val22, builder.getInt32(2147483647), "");
    //   %24 = icmp eq i32 %23, 0
    Value *val24 = builder.CreateICmpEQ(val23, builder.getInt32(0), "");
    //   br i1 %24, label %85, label %25
    builder.CreateCondBr(val24, val85, val25);
    builder.SetInsertPoint(val25);
    //   %26 = icmp eq i32 %17, 0
    Value *val26 = builder.CreateICmpEQ(val17, builder.getInt32(0), "");
    //   %27 = or i1 %16, %26
    Value *val27 = builder.CreateOr(val16, val26, "");
    //   br i1 %27, label %28, label %32
    builder.CreateCondBr(val27, val28, val32);
    builder.SetInsertPoint(val28);
    //   %29 = xor i32 %1, %0
    Value *val29 = builder.CreateXor(val1, val0, "");
    //   %30 = and i32 %29, -2147483648
    Value *val30 = builder.CreateAnd(val29, builder.getInt32(-2147483648), "");
    //   %31 = or disjoint i32 %30, 2139095040
    Value *val31 = builder.CreateOr(val30, builder.getInt32(2139095040), "");
    //   br label %85
    builder.CreateBr(val85);
    builder.SetInsertPoint(val32);
    //   %33 = or i1 %21, %18
    Value *val33 = builder.CreateOr(val21, val18, "");
    //   %34 = xor i32 %1, %0
    Value *val34 = builder.CreateXor(val1, val0, "");
    //   br i1 %33, label %35, label %37
    builder.CreateCondBr(val33, val35, val37);
    builder.SetInsertPoint(val35);
    //   %36 = and i32 %34, -2147483648
    Value *val36 = builder.CreateAnd(val34, builder.getInt32(-2147483648), "");
    //   br label %85
    builder.CreateBr(val85);
    builder.SetInsertPoint(val37);
    //   %38 = zext nneg i32 %5 to i64
    Value *val38 = builder.CreateZExt(val5, Type::getInt64Ty(context));
    //   %39 = icmp ne i32 %3, 0
    Value *val39 = builder.CreateICmpNE(val3, builder.getInt32(0), "");
    //   %40 = icmp eq i32 %5, 0
    Value *val40 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %41 = or i1 %39, %40
    Value *val41 = builder.CreateOr(val39, val40, "");
    //   %42 = or disjoint i64 %38, 8388608
    Value *val42 = builder.CreateOr(val38, builder.getInt64(8388608ll), "");
    //   %43 = select i1 %41, i64 %42, i64 %38
    Value *val43 = builder.CreateSelect(val41, val42, val38);
    //   %44 = zext nneg i32 %11 to i64
    Value *val44 = builder.CreateZExt(val11, Type::getInt64Ty(context));
    //   %45 = icmp ne i32 %9, 0
    Value *val45 = builder.CreateICmpNE(val9, builder.getInt32(0), "");
    //   %46 = icmp eq i32 %11, 0
    Value *val46 = builder.CreateICmpEQ(val11, builder.getInt32(0), "");
    //   %47 = or i1 %45, %46
    Value *val47 = builder.CreateOr(val45, val46, "");
    //   %48 = or disjoint i64 %44, 8388608
    Value *val48 = builder.CreateOr(val44, builder.getInt64(8388608ll), "");
    //   %49 = select i1 %47, i64 %48, i64 %44
    Value *val49 = builder.CreateSelect(val47, val48, val44);
    //   %50 = icmp eq i32 %3, 0
    Value *val50 = builder.CreateICmpEQ(val3, builder.getInt32(0), "");
    //   %51 = and i1 %50, %6
    Value *val51 = builder.CreateAnd(val50, val6, "");
    //   %52 = lshr i32 %0, 23
    Value *val52 = builder.CreateLShr(val0, builder.getInt32(23), "", false);
    //   %53 = and i32 %52, 255
    Value *val53 = builder.CreateAnd(val52, builder.getInt32(255), "");
    //   %54 = add nsw i32 %53, -104
    Value *val54 = builder.CreateAdd(val53, builder.getInt32(-104), "", false, true);
    //   %55 = icmp eq i32 %9, 0
    Value *val55 = builder.CreateICmpEQ(val9, builder.getInt32(0), "");
    //   %56 = and i1 %55, %12
    Value *val56 = builder.CreateAnd(val55, val12, "");
    //   %57 = lshr i32 %1, 23
    Value *val57 = builder.CreateLShr(val1, builder.getInt32(23), "", false);
    //   %58 = and i32 %57, 255
    Value *val58 = builder.CreateAnd(val57, builder.getInt32(255), "");
    //   %59 = sub nsw i32 127, %58
    Value *val59 = builder.CreateSub(builder.getInt32(127), val58, "", false, true);
    //   %60 = select i1 %56, i32 126, i32 %59
    Value *val60 = builder.CreateSelect(val56, builder.getInt32(126), val59);
    //   %61 = select i1 %51, i32 -103, i32 %54
    Value *val61 = builder.CreateSelect(val51, builder.getInt32(-103), val54);
    //   %62 = add nsw i32 %60, %61
    Value *val62 = builder.CreateAdd(val60, val61, "", false, true);
    //   br label %63
    builder.CreateBr(val63);
    builder.SetInsertPoint(val63);
    //   %64 = phi i64 [ %43, %37 ], [ %72, %63 ]
    PHINode *val64 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %65 = phi i64 [ 0, %37 ], [ %71, %63 ]
    PHINode *val65 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %66 = phi i32 [ %62, %37 ], [ %68, %63 ]
    PHINode *val66 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %67 = shl nuw nsw i64 %64, 24
    Value *val67 = builder.CreateShl(val64, builder.getInt64(24ll), "", true, true);
    //   %68 = add i32 %66, -24
    Value *val68 = builder.CreateAdd(val66, builder.getInt32(-24), "", false, false);
    //   %69 = shl nuw nsw i64 %65, 24
    Value *val69 = builder.CreateShl(val65, builder.getInt64(24ll), "", true, true);
    //   %70 = udiv i64 %67, %49
    Value *val70 = builder.CreateUDiv(val67, val49, "", false);
    //   %71 = add nuw nsw i64 %70, %69
    Value *val71 = builder.CreateAdd(val70, val69, "", true, true);
    //   %72 = urem i64 %67, %49
    Value *val72 = builder.CreateURem(val67, val49, "");
    //   %73 = icmp ult i64 %71, 16777216
    Value *val73 = builder.CreateICmpULT(val71, builder.getInt64(16777216ll), "");
    //   br i1 %73, label %63, label %74, !llvm.loop !4
    builder.CreateCondBr(val73, val63, val74);
    builder.SetInsertPoint(val74);
    //   %75 = lshr i32 %34, 31
    Value *val75 = builder.CreateLShr(val34, builder.getInt32(31), "", false);
    //   %76 = trunc i32 %75 to i8
    Value *val76 = builder.CreateTrunc(val75, Type::getInt8Ty(context));
    //   %77 = shl nuw nsw i64 %72, 1
    Value *val77 = builder.CreateShl(val72, builder.getInt64(1ll), "", true, true);
    //   %78 = icmp uge i64 %77, %49
    Value *val78 = builder.CreateICmpUGE(val77, val49, "");
    //   %79 = zext i1 %78 to i8
    Value *val79 = builder.CreateZExt(val78, Type::getInt8Ty(context));
    //   %80 = icmp ugt i64 %77, %49
    Value *val80 = builder.CreateICmpUGT(val77, val49, "");
    //   %81 = icmp ne i64 %72, 0
    Value *val81 = builder.CreateICmpNE(val72, builder.getInt64(0ll), "");
    //   %82 = zext i1 %81 to i32
    Value *val82 = builder.CreateZExt(val81, Type::getInt32Ty(context));
    //   %83 = select i1 %80, i32 2, i32 %82
    Value *val83 = builder.CreateSelect(val80, builder.getInt32(2), val82);
    //   %84 = tail call fastcc i32 @build_float(i8 noundef signext %76, i32 noundef %68, i64 noundef %71, i8 noundef signext %79, i32 noundef %83)
    Value *val84 = builder.CreateCall(funcbuild_float, {val76, val68, val71, val79, val83});
    //   br label %85
    builder.CreateBr(val85);
    builder.SetInsertPoint(val85);
    //   %86 = phi i32 [ %31, %28 ], [ %36, %35 ], [ %84, %74 ], [ -1, %8 ], [ -1, %2 ], [ -1, %14 ], [ -1, %20 ]
    PHINode *val86 = builder.CreatePHI(Type::getInt32Ty(context), 7);
    //   ret i32 %86
    builder.CreateRet(val86);
    val64->addIncoming(val43, val37);
    val64->addIncoming(val72, val63);
    val65->addIncoming(builder.getInt64(0ll), val37);
    val65->addIncoming(val71, val63);
    val66->addIncoming(val62, val37);
    val66->addIncoming(val68, val63);
    val86->addIncoming(val31, val28);
    val86->addIncoming(val36, val35);
    val86->addIncoming(val84, val74);
    val86->addIncoming(builder.getInt32(-1), val8);
    val86->addIncoming(builder.getInt32(-1), val2);
    val86->addIncoming(builder.getInt32(-1), val14);
    val86->addIncoming(builder.getInt32(-1), val20);
  }
  {
    Function *func = funcf32_is_qnan;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2139095040
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %3 = icmp ne i32 %2, 2139095040
    Value *val3 = builder.CreateICmpNE(val2, builder.getInt32(2139095040), "");
    //   %4 = and i32 %0, 8388607
    Value *val4 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %5 = icmp eq i32 %4, 0
    Value *val5 = builder.CreateICmpEQ(val4, builder.getInt32(0), "");
    //   %6 = or i1 %3, %5
    Value *val6 = builder.CreateOr(val3, val5, "");
    //   %7 = lshr i32 %0, 31
    Value *val7 = builder.CreateLShr(val0, builder.getInt32(31), "", false);
    //   %8 = trunc i32 %7 to i8
    Value *val8 = builder.CreateTrunc(val7, Type::getInt8Ty(context));
    //   %9 = select i1 %6, i8 0, i8 %8
    Value *val9 = builder.CreateSelect(val6, builder.getInt8(0), val8);
    //   ret i8 %9
    builder.CreateRet(val9);
  }
  {
    Function *func = funcf32_is_snan;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2139095040
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %3 = icmp ne i32 %2, 2139095040
    Value *val3 = builder.CreateICmpNE(val2, builder.getInt32(2139095040), "");
    //   %4 = and i32 %0, 8388607
    Value *val4 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %5 = icmp eq i32 %4, 0
    Value *val5 = builder.CreateICmpEQ(val4, builder.getInt32(0), "");
    //   %6 = or i1 %3, %5
    Value *val6 = builder.CreateOr(val3, val5, "");
    //   %7 = lshr i32 %0, 31
    Value *val7 = builder.CreateLShr(val0, builder.getInt32(31), "", false);
    //   %8 = trunc i32 %7 to i8
    Value *val8 = builder.CreateTrunc(val7, Type::getInt8Ty(context));
    //   %9 = xor i8 %8, 1
    Value *val9 = builder.CreateXor(val8, builder.getInt8(1), "");
    //   %10 = select i1 %6, i8 0, i8 %9
    Value *val10 = builder.CreateSelect(val6, builder.getInt8(0), val9);
    //   ret i8 %10
    builder.CreateRet(val10);
  }
  {
    Function *func = funcf32_is_subnormal;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2139095040
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %3 = icmp eq i32 %2, 0
    Value *val3 = builder.CreateICmpEQ(val2, builder.getInt32(0), "");
    //   %4 = and i32 %0, 8388607
    Value *val4 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %5 = icmp ne i32 %4, 0
    Value *val5 = builder.CreateICmpNE(val4, builder.getInt32(0), "");
    //   %6 = and i1 %3, %5
    Value *val6 = builder.CreateAnd(val3, val5, "");
    //   %7 = zext i1 %6 to i8
    Value *val7 = builder.CreateZExt(val6, Type::getInt8Ty(context));
    //   ret i8 %7
    builder.CreateRet(val7);
  }
  {
    Function *func = funcf32_equal;
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val8 = BasicBlock::Create(context, "", func);
    BasicBlock *val14 = BasicBlock::Create(context, "", func);
    BasicBlock *val20 = BasicBlock::Create(context, "", func);
    BasicBlock *val23 = BasicBlock::Create(context, "", func);
    BasicBlock *val29 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    Value *val1 = func->getArg(1);
    builder.SetInsertPoint(val2);
    //   %3 = and i32 %0, 2139095040
    Value *val3 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %4 = icmp ne i32 %3, 2139095040
    Value *val4 = builder.CreateICmpNE(val3, builder.getInt32(2139095040), "");
    //   %5 = and i32 %0, 8388607
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %6 = icmp eq i32 %5, 0
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %7 = or i1 %4, %6
    Value *val7 = builder.CreateOr(val4, val6, "");
    //   br i1 %7, label %8, label %29
    builder.CreateCondBr(val7, val8, val29);
    builder.SetInsertPoint(val8);
    //   %9 = and i32 %1, 2139095040
    Value *val9 = builder.CreateAnd(val1, builder.getInt32(2139095040), "");
    //   %10 = icmp ne i32 %9, 2139095040
    Value *val10 = builder.CreateICmpNE(val9, builder.getInt32(2139095040), "");
    //   %11 = and i32 %1, 8388607
    Value *val11 = builder.CreateAnd(val1, builder.getInt32(8388607), "");
    //   %12 = icmp eq i32 %11, 0
    Value *val12 = builder.CreateICmpEQ(val11, builder.getInt32(0), "");
    //   %13 = or i1 %10, %12
    Value *val13 = builder.CreateOr(val10, val12, "");
    //   br i1 %13, label %14, label %29
    builder.CreateCondBr(val13, val14, val29);
    builder.SetInsertPoint(val14);
    //   %15 = and i32 %0, 2147483647
    Value *val15 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %16 = icmp eq i32 %15, 2139095040
    Value *val16 = builder.CreateICmpEQ(val15, builder.getInt32(2139095040), "");
    //   %17 = and i32 %1, 2147483647
    Value *val17 = builder.CreateAnd(val1, builder.getInt32(2147483647), "");
    //   %18 = icmp eq i32 %17, 2139095040
    Value *val18 = builder.CreateICmpEQ(val17, builder.getInt32(2139095040), "");
    //   %19 = and i1 %16, %18
    Value *val19 = builder.CreateAnd(val16, val18, "");
    //   br i1 %19, label %20, label %23
    builder.CreateCondBr(val19, val20, val23);
    builder.SetInsertPoint(val20);
    //   %21 = xor i32 %1, %0
    Value *val21 = builder.CreateXor(val1, val0, "");
    //   %22 = icmp sgt i32 %21, -1
    Value *val22 = builder.CreateICmpSGT(val21, builder.getInt32(-1), "");
    //   br label %29
    builder.CreateBr(val29);
    builder.SetInsertPoint(val23);
    //   %24 = or i32 %1, %0
    Value *val24 = builder.CreateOr(val1, val0, "");
    //   %25 = and i32 %24, 2147483647
    Value *val25 = builder.CreateAnd(val24, builder.getInt32(2147483647), "");
    //   %26 = icmp eq i32 %25, 0
    Value *val26 = builder.CreateICmpEQ(val25, builder.getInt32(0), "");
    //   %27 = icmp eq i32 %0, %1
    Value *val27 = builder.CreateICmpEQ(val0, val1, "");
    //   %28 = or i1 %27, %26
    Value *val28 = builder.CreateOr(val27, val26, "");
    //   br label %29
    builder.CreateBr(val29);
    builder.SetInsertPoint(val29);
    //   %30 = phi i1 [ %22, %20 ], [ false, %8 ], [ false, %2 ], [ %28, %23 ]
    PHINode *val30 = builder.CreatePHI(Type::getInt1Ty(context), 4);
    //   %31 = zext i1 %30 to i8
    Value *val31 = builder.CreateZExt(val30, Type::getInt8Ty(context));
    //   ret i8 %31
    builder.CreateRet(val31);
    val30->addIncoming(val22, val20);
    val30->addIncoming(builder.getInt1(false), val8);
    val30->addIncoming(builder.getInt1(false), val2);
    val30->addIncoming(val28, val23);
  }
  {
    Function *func = funcf32_to_ll;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    BasicBlock *val4 = BasicBlock::Create(context, "", func);
    BasicBlock *val10 = BasicBlock::Create(context, "", func);
    BasicBlock *val12 = BasicBlock::Create(context, "", func);
    BasicBlock *val27 = BasicBlock::Create(context, "", func);
    BasicBlock *val29 = BasicBlock::Create(context, "", func);
    BasicBlock *val36 = BasicBlock::Create(context, "", func);
    BasicBlock *val38 = BasicBlock::Create(context, "", func);
    BasicBlock *val44 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   %2 = and i32 %0, 2147483647
    Value *val2 = builder.CreateAnd(val0, builder.getInt32(2147483647), "");
    //   %3 = icmp eq i32 %2, 2139095040
    Value *val3 = builder.CreateICmpEQ(val2, builder.getInt32(2139095040), "");
    //   br i1 %3, label %44, label %4
    builder.CreateCondBr(val3, val44, val4);
    builder.SetInsertPoint(val4);
    //   %5 = and i32 %0, 2139095040
    Value *val5 = builder.CreateAnd(val0, builder.getInt32(2139095040), "");
    //   %6 = icmp eq i32 %5, 2139095040
    Value *val6 = builder.CreateICmpEQ(val5, builder.getInt32(2139095040), "");
    //   %7 = and i32 %0, 8388607
    Value *val7 = builder.CreateAnd(val0, builder.getInt32(8388607), "");
    //   %8 = icmp ne i32 %7, 0
    Value *val8 = builder.CreateICmpNE(val7, builder.getInt32(0), "");
    //   %9 = and i1 %6, %8
    Value *val9 = builder.CreateAnd(val6, val8, "");
    //   br i1 %9, label %44, label %10
    builder.CreateCondBr(val9, val44, val10);
    builder.SetInsertPoint(val10);
    //   %11 = icmp eq i32 %2, 0
    Value *val11 = builder.CreateICmpEQ(val2, builder.getInt32(0), "");
    //   br i1 %11, label %44, label %12
    builder.CreateCondBr(val11, val44, val12);
    builder.SetInsertPoint(val12);
    //   %13 = zext nneg i32 %7 to i64
    Value *val13 = builder.CreateZExt(val7, Type::getInt64Ty(context));
    //   %14 = icmp ne i32 %5, 0
    Value *val14 = builder.CreateICmpNE(val5, builder.getInt32(0), "");
    //   %15 = icmp eq i32 %7, 0
    Value *val15 = builder.CreateICmpEQ(val7, builder.getInt32(0), "");
    //   %16 = or i1 %14, %15
    Value *val16 = builder.CreateOr(val14, val15, "");
    //   %17 = or disjoint i64 %13, 8388608
    Value *val17 = builder.CreateOr(val13, builder.getInt64(8388608ll), "");
    //   %18 = select i1 %16, i64 %17, i64 %13
    Value *val18 = builder.CreateSelect(val16, val17, val13);
    //   %19 = icmp eq i32 %5, 0
    Value *val19 = builder.CreateICmpEQ(val5, builder.getInt32(0), "");
    //   %20 = and i1 %19, %8
    Value *val20 = builder.CreateAnd(val19, val8, "");
    //   %21 = lshr i32 %0, 23
    Value *val21 = builder.CreateLShr(val0, builder.getInt32(23), "", false);
    //   %22 = and i32 %21, 255
    Value *val22 = builder.CreateAnd(val21, builder.getInt32(255), "");
    //   %23 = add nsw i32 %22, -127
    Value *val23 = builder.CreateAdd(val22, builder.getInt32(-127), "", false, true);
    //   %24 = select i1 %20, i32 -126, i32 %23
    Value *val24 = builder.CreateSelect(val20, builder.getInt32(-126), val23);
    //   %25 = add nsw i32 %24, -23
    Value *val25 = builder.CreateAdd(val24, builder.getInt32(-23), "", false, true);
    //   %26 = icmp slt i32 %24, -40
    Value *val26 = builder.CreateICmpSLT(val24, builder.getInt32(-40), "");
    //   br i1 %26, label %44, label %27
    builder.CreateCondBr(val26, val44, val27);
    builder.SetInsertPoint(val27);
    //   %28 = icmp slt i32 %24, 24
    Value *val28 = builder.CreateICmpSLT(val24, builder.getInt32(24), "");
    //   br i1 %28, label %29, label %36
    builder.CreateCondBr(val28, val29, val36);
    builder.SetInsertPoint(val29);
    //   %30 = sub nsw i32 23, %24
    Value *val30 = builder.CreateSub(builder.getInt32(23), val24, "", false, true);
    //   %31 = zext nneg i32 %30 to i64
    Value *val31 = builder.CreateZExt(val30, Type::getInt64Ty(context));
    //   %32 = lshr i64 %18, %31
    Value *val32 = builder.CreateLShr(val18, val31, "", false);
    //   %33 = sub nsw i64 0, %32
    Value *val33 = builder.CreateSub(builder.getInt64(0ll), val32, "", false, true);
    //   %34 = icmp slt i32 %0, 0
    Value *val34 = builder.CreateICmpSLT(val0, builder.getInt32(0), "");
    //   %35 = select i1 %34, i64 %33, i64 %32
    Value *val35 = builder.CreateSelect(val34, val33, val32);
    //   br label %44
    builder.CreateBr(val44);
    builder.SetInsertPoint(val36);
    //   %37 = icmp ult i32 %24, 63
    Value *val37 = builder.CreateICmpULT(val24, builder.getInt32(63), "");
    //   br i1 %37, label %38, label %44
    builder.CreateCondBr(val37, val38, val44);
    builder.SetInsertPoint(val38);
    //   %39 = zext nneg i32 %25 to i64
    Value *val39 = builder.CreateZExt(val25, Type::getInt64Ty(context));
    //   %40 = shl nuw nsw i64 %18, %39
    Value *val40 = builder.CreateShl(val18, val39, "", true, true);
    //   %41 = sub nsw i64 0, %40
    Value *val41 = builder.CreateSub(builder.getInt64(0ll), val40, "", false, true);
    //   %42 = icmp slt i32 %0, 0
    Value *val42 = builder.CreateICmpSLT(val0, builder.getInt32(0), "");
    //   %43 = select i1 %42, i64 %41, i64 %40
    Value *val43 = builder.CreateSelect(val42, val41, val40);
    //   br label %44
    builder.CreateBr(val44);
    builder.SetInsertPoint(val44);
    //   %45 = phi i64 [ -9223372036854775808, %4 ], [ -9223372036854775808, %1 ], [ 0, %10 ], [ %35, %29 ], [ %43, %38 ], [ 0, %12 ], [ -9223372036854775808, %36 ]
    PHINode *val45 = builder.CreatePHI(Type::getInt64Ty(context), 7);
    //   ret i64 %45
    builder.CreateRet(val45);
    val45->addIncoming(builder.getInt64(-9223372036854775808ll), val4);
    val45->addIncoming(builder.getInt64(-9223372036854775808ll), val1);
    val45->addIncoming(builder.getInt64(0ll), val10);
    val45->addIncoming(val35, val29);
    val45->addIncoming(val43, val38);
    val45->addIncoming(builder.getInt64(0ll), val12);
    val45->addIncoming(builder.getInt64(-9223372036854775808ll), val36);
  }
  {
    Function *func = funcf32_from_ll;
    BasicBlock *val1 = BasicBlock::Create(context, "", func);
    BasicBlock *val2 = BasicBlock::Create(context, "", func);
    BasicBlock *val3 = BasicBlock::Create(context, "", func);
    BasicBlock *val_preheader = BasicBlock::Create(context, "", func);
    BasicBlock *val24 = BasicBlock::Create(context, "", func);
    BasicBlock *val26 = BasicBlock::Create(context, "", func);
    BasicBlock *val33 = BasicBlock::Create(context, "", func);
    BasicBlock *val40 = BasicBlock::Create(context, "", func);
    BasicBlock *val42 = BasicBlock::Create(context, "", func);
    BasicBlock *val46 = BasicBlock::Create(context, "", func);
    BasicBlock *val53 = BasicBlock::Create(context, "", func);
    BasicBlock *val55 = BasicBlock::Create(context, "", func);
    BasicBlock *val59 = BasicBlock::Create(context, "", func);
    Value *val0 = func->getArg(0);
    builder.SetInsertPoint(val1);
    //   switch i64 %0, label %3 [     i64 -9223372036854775808, label %2     i64 0, label %59   ]
    SwitchInst *s0 = builder.CreateSwitch(val0, val3);
    builder.SetInsertPoint(val2);
    //   br label %59
    builder.CreateBr(val59);
    builder.SetInsertPoint(val3);
    //   %4 = tail call i64 @llvm.abs.i64(i64 %0, i1 true)
    Value *val4 = builder.CreateCall(funcllvm_abs_i64, {val0, builder.getInt1(true)});
    //   %5 = icmp ult i64 %4, 16777216
    Value *val5 = builder.CreateICmpULT(val4, builder.getInt64(16777216ll), "");
    //   %6 = shl nuw nsw i64 %4, 24
    Value *val6 = builder.CreateShl(val4, builder.getInt64(24ll), "", true, true);
    //   %7 = select i1 %5, i64 %6, i64 %4
    Value *val7 = builder.CreateSelect(val5, val6, val4);
    //   %8 = select i1 %5, i32 -1, i32 23
    Value *val8 = builder.CreateSelect(val5, builder.getInt32(-1), builder.getInt32(23));
    //   %9 = lshr i64 %0, 63
    Value *val9 = builder.CreateLShr(val0, builder.getInt64(63ll), "", false);
    //   %10 = trunc i64 %9 to i32
    Value *val10 = builder.CreateTrunc(val9, Type::getInt32Ty(context));
    //   %11 = icmp ugt i64 %7, 16777215
    Value *val11 = builder.CreateICmpUGT(val7, builder.getInt64(16777215ll), "");
    //   br i1 %11, label %.preheader, label %33
    builder.CreateCondBr(val11, val_preheader, val33);
    builder.SetInsertPoint(val_preheader);
    //   %12 = phi i32 [ %18, %.preheader ], [ 0, %3 ]
    PHINode *val12 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %13 = phi i64 [ %19, %.preheader ], [ %7, %3 ]
    PHINode *val13 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    //   %14 = phi i32 [ %20, %.preheader ], [ %8, %3 ]
    PHINode *val14 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    //   %15 = trunc i64 %13 to i8
    Value *val15 = builder.CreateTrunc(val13, Type::getInt8Ty(context));
    //   %16 = and i8 %15, 1
    Value *val16 = builder.CreateAnd(val15, builder.getInt8(1), "");
    //   %17 = zext nneg i8 %16 to i32
    Value *val17 = builder.CreateZExt(val16, Type::getInt32Ty(context));
    //   %18 = add i32 %12, %17
    Value *val18 = builder.CreateAdd(val12, val17, "", false, false);
    //   %19 = lshr i64 %13, 1
    Value *val19 = builder.CreateLShr(val13, builder.getInt64(1ll), "", false);
    //   %20 = add i32 %14, 1
    Value *val20 = builder.CreateAdd(val14, builder.getInt32(1), "", false, false);
    //   %21 = icmp ugt i64 %13, 33554431
    Value *val21 = builder.CreateICmpUGT(val13, builder.getInt64(33554431ll), "");
    //   %22 = icmp slt i32 %20, -126
    Value *val22 = builder.CreateICmpSLT(val20, builder.getInt32(-126), "");
    //   %23 = select i1 %21, i1 true, i1 %22
    Value *val23 = builder.CreateSelect(val21, builder.getInt1(true), val22);
    //   br i1 %23, label %.preheader, label %24, !llvm.loop !4
    builder.CreateCondBr(val23, val_preheader, val24);
    builder.SetInsertPoint(val24);
    //   %25 = icmp eq i8 %16, 0
    Value *val25 = builder.CreateICmpEQ(val16, builder.getInt8(0), "");
    //   br i1 %25, label %33, label %26
    builder.CreateCondBr(val25, val33, val26);
    builder.SetInsertPoint(val26);
    //   %27 = icmp sgt i32 %18, 1
    Value *val27 = builder.CreateICmpSGT(val18, builder.getInt32(1), "");
    //   %28 = and i64 %13, 2
    Value *val28 = builder.CreateAnd(val13, builder.getInt64(2ll), "");
    //   %29 = icmp ne i64 %28, 0
    Value *val29 = builder.CreateICmpNE(val28, builder.getInt64(0ll), "");
    //   %30 = or i1 %29, %27
    Value *val30 = builder.CreateOr(val29, val27, "");
    //   %31 = zext i1 %30 to i64
    Value *val31 = builder.CreateZExt(val30, Type::getInt64Ty(context));
    //   %32 = add nuw nsw i64 %19, %31
    Value *val32 = builder.CreateAdd(val19, val31, "", true, true);
    //   br label %33
    builder.CreateBr(val33);
    builder.SetInsertPoint(val33);
    //   %34 = phi i32 [ %20, %24 ], [ %20, %26 ], [ %8, %3 ]
    PHINode *val34 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %35 = phi i64 [ %19, %24 ], [ %32, %26 ], [ %7, %3 ]
    PHINode *val35 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    //   %36 = icmp ugt i64 %35, 16777215
    Value *val36 = builder.CreateICmpUGT(val35, builder.getInt64(16777215ll), "");
    //   %37 = zext i1 %36 to i32
    Value *val37 = builder.CreateZExt(val36, Type::getInt32Ty(context));
    //   %38 = add i32 %34, %37
    Value *val38 = builder.CreateAdd(val34, val37, "", false, false);
    //   %39 = icmp sgt i32 %38, 127
    Value *val39 = builder.CreateICmpSGT(val38, builder.getInt32(127), "");
    //   br i1 %39, label %40, label %42
    builder.CreateCondBr(val39, val40, val42);
    builder.SetInsertPoint(val40);
    //   %41 = shl nuw i32 %10, 31
    Value *val41 = builder.CreateShl(val10, builder.getInt32(31), "", true, false);
    //   br label %55
    builder.CreateBr(val55);
    builder.SetInsertPoint(val42);
    //   %43 = select i1 %36, i64 8388608, i64 %35
    Value *val43 = builder.CreateSelect(val36, builder.getInt64(8388608ll), val35);
    //   %44 = icmp ugt i64 %43, 8388607
    Value *val44 = builder.CreateICmpUGT(val43, builder.getInt64(8388607ll), "");
    //   %45 = trunc i64 %43 to i32
    Value *val45 = builder.CreateTrunc(val43, Type::getInt32Ty(context));
    //   br i1 %44, label %46, label %53
    builder.CreateCondBr(val44, val46, val53);
    builder.SetInsertPoint(val46);
    //   %47 = and i32 %45, 8388607
    Value *val47 = builder.CreateAnd(val45, builder.getInt32(8388607), "");
    //   %48 = shl i32 %38, 23
    Value *val48 = builder.CreateShl(val38, builder.getInt32(23), "", false, false);
    //   %49 = add i32 %48, 1065353216
    Value *val49 = builder.CreateAdd(val48, builder.getInt32(1065353216), "", false, false);
    //   %50 = and i32 %49, 2139095040
    Value *val50 = builder.CreateAnd(val49, builder.getInt32(2139095040), "");
    //   %51 = or disjoint i32 %50, %47
    Value *val51 = builder.CreateOr(val50, val47, "");
    //   %52 = shl nuw i32 %10, 31
    Value *val52 = builder.CreateShl(val10, builder.getInt32(31), "", true, false);
    //   br label %55
    builder.CreateBr(val55);
    builder.SetInsertPoint(val53);
    //   %54 = shl nuw i32 %10, 31
    Value *val54 = builder.CreateShl(val10, builder.getInt32(31), "", true, false);
    //   br label %55
    builder.CreateBr(val55);
    builder.SetInsertPoint(val55);
    //   %56 = phi i32 [ %45, %53 ], [ %52, %46 ], [ 2139095040, %40 ]
    PHINode *val56 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %57 = phi i32 [ %54, %53 ], [ %51, %46 ], [ %41, %40 ]
    PHINode *val57 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   %58 = or disjoint i32 %57, %56
    Value *val58 = builder.CreateOr(val57, val56, "");
    //   br label %59
    builder.CreateBr(val59);
    builder.SetInsertPoint(val59);
    //   %60 = phi i32 [ -2147483647, %2 ], [ %58, %55 ], [ 0, %1 ]
    PHINode *val60 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    //   ret i32 %60
    builder.CreateRet(val60);
    s0->addCase(builder.getInt64(-9223372036854775808ll), val2);
    s0->addCase(builder.getInt64(0ll), val59);
    val12->addIncoming(val18, val_preheader);
    val12->addIncoming(builder.getInt32(0), val3);
    val13->addIncoming(val19, val_preheader);
    val13->addIncoming(val7, val3);
    val14->addIncoming(val20, val_preheader);
    val14->addIncoming(val8, val3);
    val34->addIncoming(val20, val24);
    val34->addIncoming(val20, val26);
    val34->addIncoming(val8, val3);
    val35->addIncoming(val19, val24);
    val35->addIncoming(val32, val26);
    val35->addIncoming(val7, val3);
    val56->addIncoming(val45, val53);
    val56->addIncoming(val52, val46);
    val56->addIncoming(builder.getInt32(2139095040), val40);
    val57->addIncoming(val54, val53);
    val57->addIncoming(val51, val46);
    val57->addIncoming(val41, val40);
    val60->addIncoming(builder.getInt32(-2147483647), val2);
    val60->addIncoming(val58, val55);
    val60->addIncoming(builder.getInt32(0), val1);
  }
  if (std::string(argv[1]) == PRINT) {
    module->print(outs(), nullptr);
    return 0;
  } else if (std::string(argv[1]) == RUN) {
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> void * {
      if (fnName == "simPutPixel") {
        return reinterpret_cast<void *>(simPutPixel);
      }
      if (fnName == "simFlush") {
        return reinterpret_cast<void *>(simFlush);
      }
      return nullptr;
    });
    ee->finalizeObject();
    simInit();
    ee->runFunction(funcapp, {});
    simExit();
    return 0;
  }
}
