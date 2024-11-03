#include "isa.h"

#include "sim.h"

#include <format>

std::string isa::Label::str() {
  return "%" + name_;
}

std::string isa::Flsh::name() {
  return "flsh";
}

isa::Runnable* isa::Flsh::run(CPU& cpu) {
  simFlush();
  return Base::next;
}

isa::Flsh::Flsh() : Base() {}

isa::Call::Call(Function* func) : Base(func) {}

std::string isa::Call::name() {
  return "call";
}

isa::Runnable* isa::Call::run(CPU& cpu) {
  auto func = std::get<0>(Base::ops);
  CallFrame frame{Base::next, std::min((size_t) 1, func->args())};
  for (size_t i = func->args(); i < REG_CNT; ++i) {
    frame.regs[i] = cpu.get_reg<REG_t>(i);
  }
  cpu.callstack.push_back(frame);
  return func->next;
}

isa::Ret::Ret() : Base() {}

std::string isa::Ret::name() {
  return "ret";
}

isa::Runnable* isa::Ret::run(CPU& cpu) {
  auto frame = cpu.callstack.back();
  cpu.callstack.pop_back();
  for (size_t i = frame.args_cnt; i < REG_CNT; ++i) {
    cpu.set_reg(i, frame.regs[i]);
  }
  return frame.ret_point;
}

isa::Jp::Jp(Label* label) : Base(label) {}

std::string isa::Jp::name() {
  return "jp";
}

isa::Runnable* isa::Jp::run(CPU& cpu) {
  return std::get<0>(Base::ops);
}

std::string isa::Nop::name() {
  return "nop";
}

isa::Nop::Nop() : Base() {}

isa::Runnable* isa::Nop::run(CPU& cpu) {
  return Base::next;
}

isa::Runnable* isa::Label::run(CPU& cpu) {
  return next;
}

isa::Runnable* isa::LocalFunction::run(CPU& cpu) {
  return next;
}

isa::Function::Function(std::string name, size_t args_cnt) : name_(name), args_cnt(args_cnt) {}

std::string isa::Function::str() {
  return std::format("#{}({})", name_, args_cnt);
}

isa::Label::Label(std::string name) : name_(name) {}

isa::CPU::CPU() {
  for (size_t i = 0; i < REG_CNT; ++i) {
    LI[i] = allocate(Reg<W8_t>(i));
    XI[i] = allocate(Reg<W16_t>(i));
    EXI[i] = allocate(Reg<W32_t>(i));
    RXI[i] = allocate(Reg<W64_t>(i));
  }
}

isa::Runnable* isa::Drw::run(CPU& cpu) {
  simPutPixel(std::get<0>(Base::ops)->eval(cpu), std::get<1>(Base::ops)->eval(cpu), std::get<2>(Base::ops)->eval(cpu));
  return Base::next;
}

std::string isa::Drw::name() {
  return "drw";
}

isa::Drw::Drw(Value<COORD_t>* x, Value<COORD_t>* y, Value<COLOR_t>* color) : Base(x, y, color) {}

void isa::run(CPU& cpu, Function* func, bool sdl) {
  if (sdl)
    simInit();
  Call call(func);
  Runnable* next = &call;
  while (next != nullptr) {
    next = next->run(cpu);
  }
  if (sdl)
    simExit();
}

size_t isa::Function::args() {
  return args_cnt;
}

std::string isa::Function::name() {
  return name_;
}

std::string isa::Label::name() {
  return name_;
}

void isa::Ret::compile(LLVMFuncContext* context) {
  auto* builder = context->global->builder;
  llvm::Type* type = helpers::getType<W64_t>(builder);
  llvm::Value* v = builder->CreateLoad(type, context->registers[0]);
  builder->CreateRet(v);
  context->jumped = true;
}

void isa::Jp::compile(LLVMFuncContext* context) {
  auto* builder = context->global->builder;
  auto* lbl = std::get<0>(Base::ops);
  builder->CreateBr(lbl->compile_as_value(context));
  context->jumped = true;
}

void isa::Nop::compile(LLVMFuncContext* context) {
}

void isa::Call::compile(LLVMFuncContext* context) {
  auto* builder = context->global->builder;
  auto* func = std::get<0>(Base::ops);
  auto* llvmfunc = func->compile_as_value(context);
  std::vector<llvm::Value*> args;
  LLVMReadContext readCxt{context};
  for (size_t i = 0; i < func->args(); ++i) {
    args.push_back(Reg<REG_t>(i).compile(&readCxt));
  }
  auto* res = builder->CreateCall(llvmfunc, args);

  LLVMWriteContext writeCxt{context, res};
  Reg<REG_t>(0).compile(&writeCxt);
}

void isa::Flsh::compile(LLVMFuncContext* context) {
  auto* builder = context->global->builder;
  static auto* func = llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), {  }, false), llvm::Function::ExternalLinkage, "simFlush", context->global->module);
  builder->CreateCall(func);
}

void isa::Drw::compile(LLVMFuncContext* context) {
  auto* builder = context->global->builder;
  auto* w32type = builder->getInt32Ty();
  static auto* func = llvm::Function::Create(llvm::FunctionType::get(builder->getVoidTy(), { w32type, w32type, w32type }, false), llvm::Function::ExternalLinkage, "simPutPixel", context->global->module);

  LLVMReadContext readCxt{context};
  builder->CreateCall(func, {std::get<0>(Base::ops)->compile(&readCxt), std::get<1>(Base::ops)->compile(&readCxt), std::get<2>(Base::ops)->compile(&readCxt)});
}

llvm::Function* isa::Function::compile_as_value(LLVMFuncContext* context) {
  return context->global->functions[str()];
}

void isa::Label::compile(LLVMFuncContext* context) {
  llvm::BasicBlock* next_block = context->global->blocks[context->func->str()][str()];
  if (!context->jumped) {
    context->global->builder->CreateBr(next_block);
  }
  context->jumped = false;
  context->block = next_block;
  context->global->builder->SetInsertPoint(context->block);
}

llvm::BasicBlock* isa::Label::compile_as_value(LLVMFuncContext* context) {
  return context->global->blocks[context->func->str()][str()];
}

llvm::Function* isa::LocalFunction::compile(LLVMContext* context) {
  auto* builder = context->builder;
  llvm::BasicBlock* block = context->blocks[str()][""];
  builder->SetInsertPoint(block);

  LLVMFuncContext cxt{context, {}, this, block};

  for (size_t i = 0; i < isa::REG_CNT; ++i) {
    cxt.registers[i] = builder->CreateAlloca(llvm::Type::getInt64Ty(builder->getContext()));
  }
  llvm::Function* func = compile_as_value(&cxt);

  for (size_t i = 0; i < args(); ++i) {
    llvm::Type* type = helpers::getType<W64_t>(builder);
    llvm::Value* v = builder->CreateZExt(func->getArg(i), type);
    builder->CreateStore(v, cxt.registers[i]);
  }

  for (Runnable* next = this->next; next; next = next->next) {
    next->compile(&cxt);
  }

  return func;
}
