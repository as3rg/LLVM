#include <array>
#include <cstddef>
#include <cstdint>
#include <map>
#include <string>
#include <type_traits>
#include <vector>
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"

namespace isa {
using W8_t = uint8_t;
using W16_t = uint16_t;
using W32_t = uint32_t;
using W64_t = uint64_t;
using PTR_t = size_t;
using REG_t = W64_t;
using COORD_t = W32_t;
using COLOR_t = W32_t;
constexpr size_t REG_CNT = 256;

namespace helpers {
  template <size_t... indexes>
  struct List {};

  template <typename L1, typename L2>
  struct Join;

  template <size_t... L1Ops, size_t... L2Ops>
  struct Join<List<L1Ops...>, List<L2Ops...>> {
    using list = List<L1Ops..., L2Ops...>;
  };

  template <size_t frm, size_t to>
  struct Range {
    using list = Join<List<frm>, typename Range<frm + 1, to>::list>::list;
  };

  template <size_t frm, size_t to>
    requires(frm >= to)
  struct Range<frm, to> {
    using list = List<>;
  };

  template<typename Type>
  llvm::Type* getType(llvm::IRBuilder<>* builder) {
    if constexpr (std::is_same_v<Type, W8_t>) {
      return builder->getInt8Ty();
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return builder->getInt16Ty();
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return builder->getInt32Ty();
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return builder->getInt64Ty();
    } else {
      return nullptr;
    }
  }

  template<typename Type>
  llvm::Value* getTypeConst(llvm::IRBuilder<>* builder, Type val) {
    if constexpr (std::is_same_v<Type, W8_t>) {
      return builder->getInt8(val);
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return builder->getInt16(val);
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return builder->getInt32(val);
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return builder->getInt64(val);
    } else {
      return nullptr;
    }
  }
}

template<typename Type>
constexpr bool is_word_v = (std::is_same_v<Type, W8_t> || std::is_same_v<Type, W16_t> || std::is_same_v<Type, W32_t> ||
           std::is_same_v<Type, W64_t>);

class CPU;
class LLVMContext;
class LLVMFuncContext;

class ISAObject {
protected:
  ISAObject() = default;
public:
  virtual ~ISAObject() = default;
};

class Printable : virtual public ISAObject {
public:
  virtual std::string str() = 0;
};

template<typename Ret, typename Context>
class IRCompilable : virtual public ISAObject {
public:
  virtual Ret compile(Context* context) = 0;
};

class Runnable : public Printable, public IRCompilable<void, LLVMFuncContext> {
public:
  virtual Runnable* run(CPU& cpu) = 0;
  Runnable* next = nullptr;
};

template <typename Type>
  requires(is_word_v<Type>)
class Reg;
class Function;
class Label;

class LLVMContext {
public:
  llvm::IRBuilder<> *builder;
  llvm::Module *module;
  std::map<std::string, llvm::Function*> functions;
  std::map<std::string, llvm::Function*> function_declarations;
  std::map<std::string, std::map<std::string, llvm::BasicBlock*>> blocks;
};

class LLVMFuncContext {
public:
  LLVMContext* global;
  std::array<llvm::Value*, isa::REG_CNT> registers;
  Function* func;
  llvm::BasicBlock* block;
  bool jumped = false;
};

class LLVMReadContext {
  public:
  LLVMFuncContext* funcContext;
};

class LLVMWriteContext {
  public:
  LLVMFuncContext* funcContext;
  llvm::Value* value;
};

class CallFrame {
  public:
  Runnable* ret_point;
  size_t args_cnt;
  REG_t regs[REG_CNT];
};

class CPU {
private:
  REG_t regs[REG_CNT];
public:
  std::vector<CallFrame> callstack;

  template <typename T>
  T get_reg(size_t num) {
    if constexpr (std::endian::native == std::endian::big) {
      return reinterpret_cast<T*>(regs)[(num + 1) * sizeof(regs[num]) / sizeof(T) - 1];
    } else if constexpr (std::endian::native == std::endian::little) {
      return reinterpret_cast<T*>(regs)[num * sizeof(regs[num]) / sizeof(T)];
    } else {
      static_assert(false, "mixed-endian is not supported");
    }
  }

  template <typename T>
  void set_reg(size_t num, T value) {
    regs[num] = 0;
    if constexpr (std::endian::native == std::endian::big) {
      reinterpret_cast<T*>(regs)[(num + 1) * sizeof(regs[num]) / sizeof(T) - 1] = value;
    } else if constexpr (std::endian::native == std::endian::little) {
      reinterpret_cast<T*>(regs)[num * sizeof(regs[num]) / sizeof(T)] = value;
    } else {
      static_assert(false, "mixed-endian is not supported");
    }
  }
};

template <typename Type>
class Value : virtual public Printable, public IRCompilable<llvm::Value*, LLVMReadContext> {
public:
  virtual Type eval(CPU&) = 0;
};

template <typename Type>
class Dest : virtual public Printable, public IRCompilable<void, LLVMWriteContext> {
public:
  virtual void update(CPU& cpu, Type value) = 0;
};

template <typename Type>
class DestValue : public Value<Type>, public Dest<Type> {};

template <typename Type>
  requires(is_word_v<Type>)
class Reg : public DestValue<Type> {
protected:
  Type num;

public:
  Reg(Type num) : num(num) {}

  void update(CPU& cpu, Type value) override {
    cpu.set_reg<Type>(num, value);
  }

  Type eval(CPU& cpu) override {
    return cpu.get_reg<Type>(num);
  }

  std::string str() override {
    if constexpr (std::is_same_v<Type, W8_t>) {
      return "l" + std::to_string(num);
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return "x" + std::to_string(num);
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return "ex" + std::to_string(num);
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return "rx" + std::to_string(num);
    } else {
      return "?" + std::to_string(num);
    }
  }

  llvm::Value* compile(LLVMReadContext* context) override {
    auto* builder = context->funcContext->global->builder;
    llvm::Value* val = builder->CreateLoad(llvm::Type::getInt64Ty(builder->getContext()), context->funcContext->registers[num]);
    return builder->CreateTrunc(val, helpers::getType<Type>(builder));
  }

  void compile(LLVMWriteContext* context) override {
    auto* builder = context->funcContext->global->builder;
    llvm::Value* val = builder->CreateZExt(context->value, llvm::Type::getInt64Ty(builder->getContext()));
    builder->CreateStore(val, context->funcContext->registers[num]);
  }
};

class Function : public Printable, public IRCompilable<llvm::Function*, LLVMContext> {
protected:
  std::string name_;
  size_t args_cnt;

public:
  Runnable* next = nullptr;

  Function(std::string name, size_t args_cnt);

  std::string str() override;

  std::string name();

  size_t args();

  Runnable* run(CPU& cpu);

  llvm::Function* compile_as_value(LLVMFuncContext* context);

  llvm::Function* compile(LLVMContext* context) override;
};

class Label : public Runnable {
protected:
  std::string name_;

public:
  Label(std::string name);

  std::string str() override;

  std::string name();

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;

  llvm::BasicBlock* compile_as_value(LLVMFuncContext* context);
};

template <typename Type>
  requires(std::is_same_v<Type, W8_t> || std::is_same_v<Type, W16_t> || std::is_same_v<Type, W32_t> ||
           std::is_same_v<Type, W64_t>)
class Const : public Value<Type> {
private:
  Type value;

public:
  Const(Type&& value) : value(value) {}

  std::string str() override {
    using std::to_string;
    std::string name = to_string(value);
    if constexpr (std::is_same_v<Type, W8_t>) {
      return "(w8) " + name;
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return "(w16) " + name;
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return "(w32) " + name;
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return "(w64) " + name;
    } else {
      return "(?) " + name;
    }
  }

  Type eval(CPU&) override {
    return value;
  }

  llvm::Value* compile(LLVMReadContext* context) override {
    if constexpr (std::is_same_v<Type, W8_t>) {
      return context->funcContext->global->builder->getInt8(value);
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return context->funcContext->global->builder->getInt16(value);
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return context->funcContext->global->builder->getInt32(value);
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return context->funcContext->global->builder->getInt64(value);
    } else {
      return nullptr;
    }
  }
};

template <typename Type>
  requires(std::is_same_v<Type, W8_t> || std::is_same_v<Type, W16_t> || std::is_same_v<Type, W32_t> ||
           std::is_same_v<Type, W64_t>)
class Ptr : public DestValue<Type> {
private:
  Reg<PTR_t>* addr;

public:
  Ptr(Reg<PTR_t>* addr) : addr(addr) {}

  std::string str() override {
    std::string name = "*" + addr->str();
    if constexpr (std::is_same_v<Type, W8_t>) {
      return "(w8) " + name;
    } else if constexpr (std::is_same_v<Type, W16_t>) {
      return "(w16) " + name;
    } else if constexpr (std::is_same_v<Type, W32_t>) {
      return "(w32) " + name;
    } else if constexpr (std::is_same_v<Type, W64_t>) {
      return "(w64) " + name;
    } else {
      return "(?) " + name;
    }
  }

  void update(CPU& cpu, Type value) override {
    *reinterpret_cast<Type*>(addr->eval(cpu)) = value;
  }

  Type eval(CPU& cpu) override {
    return *reinterpret_cast<Type*>(addr->eval(cpu));
  }

  llvm::Value* compile(LLVMReadContext* context) override {
    auto* builder = context->funcContext->global->builder;
    llvm::Value* val = addr->compile(context);
    val = builder->CreateIntToPtr(val, helpers::getType<Type>(builder)->getPointerTo());
    return builder->CreateLoad(helpers::getType<Type>(builder), val);
  }

  void compile(LLVMWriteContext* context) override {
    auto* builder = context->funcContext->global->builder;
    LLVMReadContext readCxt {context->funcContext};

    llvm::Value* val = addr->compile(&readCxt);
    val = builder->CreateIntToPtr(val, helpers::getType<Type>(builder)->getPointerTo());
    
    builder->CreateStore(context->value, val);
  }
};

template <typename... Ops>
requires (true && ... && std::is_base_of_v<Printable, Ops>)
class Instruction : public Runnable {
protected:
  std::tuple<Ops*...> ops;

public:
  Instruction(Ops*... ops) : ops(ops...) {}

  virtual std::string name() = 0;

  std::string str() override {
    return name() + std::apply(str_ops<Ops...>, ops);
  }

private:
  template<typename... TS>
  static std::string str_ops(TS*... ts) {
    if constexpr (sizeof...(TS)) {
      return str_ops_impl(ts...);
    } else {
      return "";
    }
  }

  template<typename T, typename... TS>
  static std::string str_ops_impl(T* t, TS*... ts) {
    if constexpr (sizeof...(TS)) {
      return " " + t->str() + "," + str_ops_impl<TS...>(ts...);
    } else {
      return " " + t->str();
    }
  }
};

template <typename Type, typename... Args>
class Arithmetic : public Instruction<Dest<Type>, Value<Args>...> {
  using Base = Instruction<Dest<Type>, Value<Args>...>;

protected:
  virtual Type calc(Args... args) = 0;

public:
  Arithmetic(Dest<Type>* result, Value<Args>*... args) : Base(result, args...) {}

  virtual Runnable* run(CPU& cpu) override {
    return run_impl(cpu, typename helpers::Range<1, 1 + sizeof...(Args)>::list{});
  }

  void compile(LLVMFuncContext* context) override {
    compile_impl(context, typename helpers::Range<1, 1 + sizeof...(Args)>::list{});
  }

protected:
  template<size_t... Indexes>
  Runnable* run_impl(CPU& cpu, helpers::List<Indexes...>) {
    std::get<0>(Base::ops)->update(cpu, calc(std::get<Indexes>(Base::ops)->eval(cpu)...));
    return Base::next;
  }

  template<size_t... Indexes>
  void compile_impl(LLVMFuncContext* context, helpers::List<Indexes...>) {
    LLVMReadContext readCxt{context};
    llvm::Value* res = compile_build(context->global->builder, {std::get<Indexes>(Base::ops)->compile(&readCxt)...});
    LLVMWriteContext writeCxt{context, res};
    std::get<0>(Base::ops)->compile(&writeCxt);
  }

  virtual llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, sizeof...(Args)> ops);
};

template <typename Type>
class Add : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    return op1 + op2;
  }

public:
  Add(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "add";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateAdd(ops[0], ops[1]);
  }
};

template <typename Type>
class Sub : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    return op1 - op2;
  }

public:
  Sub(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "sub";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateSub(ops[0], ops[1]);
  }
};

template <typename Type>
class Mul : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    using SignedType = std::make_signed_t<Type>;
    return static_cast<SignedType>(op1) * static_cast<SignedType>(op2);
  }

public:
  Mul(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "mul";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateMul(ops[0], ops[1]);
  }
};

template <typename Type>
class Div : public Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>> {
  using Base = Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>>;

public:
  Div(Dest<Type>* div, Dest<Type>* rem, Value<Type>* op1, Value<Type>* op2) : Base(div, rem, op1, op2) {}

  Runnable* run(CPU& cpu) override {
    using SignedType = std::make_signed_t<Type>;
    Type op1 = static_cast<SignedType>(std::get<2>(Base::ops)->eval(cpu));
    Type op2 = static_cast<SignedType>(std::get<3>(Base::ops)->eval(cpu));
    std::get<0>(Base::ops)->update(cpu, op1 / op2);
    std::get<1>(Base::ops)->update(cpu, op1 % op2);
    return Base::next;
  }

  std::string name() override {
    return "div";
  }

  void compile(LLVMFuncContext* context) override {
    auto* builder = context->global->builder;
    LLVMReadContext readCxt{context};
    llvm::Value* op1 = std::get<2>(Base::ops)->compile(&readCxt);
    llvm::Value* op2 = std::get<3>(Base::ops)->compile(&readCxt);
    llvm::Value* res1 = builder->CreateSDiv(op1, op2);
    llvm::Value* res2 = builder->CreateSRem(op1, op2);
    LLVMWriteContext writeCxt{context, res1};
    std::get<0>(Base::ops)->compile(&writeCxt);
    writeCxt = {context, res2};
    std::get<1>(Base::ops)->compile(&writeCxt);
  }
};

template <typename Type>
class UDiv : public Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>> {
  using Base = Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>>;

public:
  UDiv(Dest<Type>* div, Dest<Type>* rem, Value<Type>* op1, Value<Type>* op2) : Base(div, rem, op1, op2) {}

  Runnable* run(CPU& cpu) override {
    using UnsignedType = std::make_unsigned_t<Type>;
    Type op1 = static_cast<UnsignedType>(std::get<2>(Base::ops)->eval(cpu));
    Type op2 = static_cast<UnsignedType>(std::get<3>(Base::ops)->eval(cpu));
    std::get<0>(Base::ops)->update(cpu, op1 / op2);
    std::get<1>(Base::ops)->update(cpu, op1 % op2);
    return Base::next;
  }

  std::string name() override {
    return "udiv";
  }

  void compile(LLVMFuncContext* context) override {
    auto* builder = context->global->builder;
    LLVMReadContext readCxt{context};
    llvm::Value* op1 = std::get<2>(Base::ops)->compile(&readCxt);
    llvm::Value* op2 = std::get<3>(Base::ops)->compile(&readCxt);
    llvm::Value* res1 = builder->CreateUDiv(op1, op2);
    llvm::Value* res2 = builder->CreateURem(op1, op2);
    LLVMWriteContext writeCxt{context, res1};
    std::get<0>(Base::ops)->compile(&writeCxt);
    writeCxt = {context, res2};
    std::get<1>(Base::ops)->compile(&writeCxt);
  }
};

template <typename Type>
class And : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    return op1 & op2;
  }

public:
  And(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "and";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateAnd(ops[0], ops[1]);
  }
};

template <typename Type>
class Or : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    return op1 | op2;
  }

public:
  Or(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "or";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateOr(ops[0], ops[1]);
  }
};

template <typename Type>
class Xor : public Arithmetic<Type, Type, Type> {
  using Base = Arithmetic<Type, Type, Type>;

protected:
  Type calc(Type op1, Type op2) override {
    return op1 ^ op2;
  }

public:
  Xor(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "xor";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateXor(ops[0], ops[1]);
  }
};

template <typename Type, typename Type2>
class LSh : public Arithmetic<Type, Type, Type2> {
  using Base = Arithmetic<Type, Type, Type2>;

protected:
  Type calc(Type op1, Type2 op2) override {
    return op1 << op2;
  }

public:
  LSh(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "lsh";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateShl(ops[0], builder->CreateSExtOrTrunc(ops[1], ops[0]->getType()));
  }
};

template <typename Type, typename Type2>
class RShL : public Arithmetic<Type, Type, Type2> {
  using Base = Arithmetic<Type, Type, Type2>;

protected:
  Type calc(Type op1, Type2 op2) override {
    return static_cast<std::make_unsigned_t<Type>>(op1) >> op2;
  }

public:
  RShL(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "rshl";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateLShr(ops[0], builder->CreateSExtOrTrunc(ops[1], ops[0]->getType()));
  }
};

template <typename Type, typename Type2>
class RShA : public Arithmetic<Type, Type, Type2> {
  using Base = Arithmetic<Type, Type, Type2>;

protected:
  Type calc(Type op1, Type2 op2) override {
    return static_cast<std::make_signed_t<Type>>(op1) >> op2;
  }

public:
  RShA(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "rsha";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateAShr(ops[0], builder->CreateSExtOrTrunc(ops[1], ops[0]->getType()));
  }
};

template <typename Type>
class Mv : public Arithmetic<Type, Type> {
  using Base = Arithmetic<Type, Type>;

protected:
  Type calc(Type op) override {
    return op;
  }

public:
  Mv(Dest<Type>* dest, Value<Type>* op1) : Base(dest, op1) {}

  std::string name() override {
    return "mv";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 1> ops) override {
    return ops[0];
  }
};

template <typename CondType, typename Type>
class MvC : public Instruction<Value<CondType>, DestValue<Type>, Value<Type>> {
  using Base = Instruction<Value<CondType>, DestValue<Type>, Value<Type>>;

public:
  MvC(Value<CondType>* cond, DestValue<Type>* dest, Value<Type>* op1) : Base(cond, dest, op1) {}

  Runnable* run(CPU& cpu) override {
    if (std::get<0>(Base::ops)->eval(cpu)) {
      std::get<1>(Base::ops)->update(cpu, std::get<2>(Base::ops)->eval(cpu));
    }
    return Base::next;
  }

  std::string name() override {
    return "mvc";
  }

  void compile(LLVMFuncContext* context) override {
    auto* builder = context->global->builder;
    LLVMReadContext readCxt{context};
    llvm::Value* cond = std::get<0>(Base::ops)->compile(&readCxt);
    llvm::Value* old_v = static_cast<Value<Type>*>(std::get<1>(Base::ops))->compile(&readCxt);
    llvm::Value* new_v = std::get<2>(Base::ops)->compile(&readCxt);
    llvm::Value* res = builder->CreateSelect(cond, new_v, old_v);
    LLVMWriteContext writeCxt{context, res};
    static_cast<Dest<Type>*>(std::get<1>(Base::ops))->compile(&writeCxt);
  }
};

template <typename Type>
class Swp : public Instruction<DestValue<Type>, DestValue<Type>> {
  using Base = Instruction<DestValue<Type>, DestValue<Type>>;

public:
  Swp(DestValue<Type>* op1, DestValue<Type>* op2) : Base(op1, op2) {}

  Runnable* run(CPU& cpu) override {
    Type op1 = std::get<0>(Base::ops)->eval(cpu);
    Type op2 = std::get<1>(Base::ops)->eval(cpu);
    std::get<0>(Base::ops)->update(cpu, op2);
    std::get<1>(Base::ops)->update(cpu, op1);
    return Base::next;
  }

  std::string name() override {
    return "swp";
  }

  void compile(LLVMFuncContext* context) override {
    auto* builder = context->global->builder;
    LLVMReadContext readCxt{context};
    llvm::Value* v1 = static_cast<Value<Type>*>(std::get<0>(Base::ops))->compile(&readCxt);
    llvm::Value* v2 = static_cast<Value<Type>*>(std::get<1>(Base::ops))->compile(&readCxt);
    LLVMWriteContext writeCxt{context, v1};
    static_cast<Dest<Type>*>(std::get<1>(Base::ops))->compile(&writeCxt);
    writeCxt = {context, v2};
    static_cast<Dest<Type>*>(std::get<0>(Base::ops))->compile(&writeCxt);
  }
};

template <typename ResType, typename Type>
class Eq : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    return op1 == op2;
  }

public:
  Eq(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "eq";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpEQ(ops[0], ops[1]);
  }
};

template <typename ResType, typename Type>
class Neq : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    return op1 != op2;
  }

public:
  Neq(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "neq";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpNE(ops[0], ops[1]);
  }
};

template <typename ResType, typename Type>
class Lt : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    using SignedType = std::make_signed_t<Type>;
    return static_cast<SignedType>(op1) < static_cast<SignedType>(op2);
  }

public:
  Lt(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "lt";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpSLT(ops[0], ops[1]);
  }
};

template <typename ResType, typename Type>
class Le : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    using SignedType = std::make_signed_t<Type>;
    return static_cast<SignedType>(op1) <= static_cast<SignedType>(op2);
  }

public:
  Le(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "le";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpSLE(ops[0], ops[1]);
  }
};

template <typename ResType, typename Type>
class ULt : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    using UnsignedType = std::make_unsigned_t<Type>;
    return static_cast<UnsignedType>(op1) < static_cast<UnsignedType>(op2);
  }

public:
  ULt(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "ult";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpULT(ops[0], ops[1]);
  }
};

template <typename ResType, typename Type>
class ULe : public Arithmetic<ResType, Type, Type> {
  using Base = Arithmetic<ResType, Type, Type>;

protected:
  ResType calc(Type op1, Type op2) override {
    using UnsignedType = std::make_unsigned_t<Type>;
    return static_cast<UnsignedType>(op1) <= static_cast<UnsignedType>(op2);
  }

public:
  ULe(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "ule";
  }

protected:
  llvm::Value* compile_build(llvm::IRBuilder<>* builder, std::array<llvm::Value*, 2> ops) override {
    return builder->CreateICmpULE(ops[0], ops[1]);
  }
};

class Drw : public Instruction<Value<COORD_t>, Value<COORD_t>, Value<COLOR_t>> {
  using Base = Instruction<Value<COORD_t>, Value<COORD_t>, Value<COLOR_t>>;

public:
  Drw(Value<COORD_t>* x, Value<COORD_t>* y, Value<COLOR_t>* color);

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

class Flsh : public Instruction<> {
  using Base = Instruction<>;

public:
  Flsh();

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

class Call : public Instruction<Function> {
  using Base = Instruction<Function>;

public:
  Call(Function* func);

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

class Ret : public Instruction<> {
  using Base = Instruction<>;

public:
  Ret();

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

class Jp : public Instruction<Label> {
  using Base = Instruction<Label>;

public:
  Jp(Label* label);

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

template <typename CondType>
class JpC : public Instruction<Value<CondType>, Label> {
  using Base = Instruction<Value<CondType>, Label>;

public:
  JpC(Value<CondType>* cond, Label* label) : Base(cond, label) {}

  std::string name() override {
    return "jpc";
  }

  Runnable* run(CPU& cpu) override {
    if (std::get<0>(Base::ops)->eval(cpu)) {
      return std::get<1>(Base::ops);
    }
    return Base::next;
  }

  void compile(LLVMFuncContext* context) override {
    auto* builder = context->global->builder;
    auto* func = context->func->compile_as_value(context);
    llvm::BasicBlock* next_block = llvm::BasicBlock::Create(builder->getContext(), "", func);
    
    LLVMReadContext readCxt{context};
    auto* cond = std::get<0>(Base::ops)->compile(&readCxt);
    auto* lbl = std::get<1>(Base::ops)->compile_as_value(context);
    cond = builder->CreateICmpNE(cond, helpers::getTypeConst<CondType>(builder, 0));
    builder->CreateCondBr(cond, lbl, next_block);
    context->block = next_block;
    builder->SetInsertPoint(context->block);
  }
};

class Nop : public Instruction<> {
  using Base = Instruction<>;

public:
  Nop();

  std::string name() override;

  Runnable* run(CPU& cpu) override;

  void compile(LLVMFuncContext* context) override;
};

void run(CPU& cpu, Function* entry_point, bool sdl = true);

template <typename T, typename... TS>
  requires(std::is_base_of_v<Runnable, T> && ... && std::is_base_of_v<Runnable, TS>)
Runnable* runnable(T* t, TS*... ts) {
  if constexpr (sizeof...(ts)) {
    t->next = runnable(ts...);
  }
  return t;
}
} // namespace isa