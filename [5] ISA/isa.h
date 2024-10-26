#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace isa {
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
}

using W8_t = uint8_t;
using W16_t = uint16_t;
using W32_t = uint32_t;
using W64_t = uint64_t;
using PTR_t = size_t;
using COORD_t = W32_t;
using COLOR_t = W32_t;
constexpr size_t REG_CNT = 256;

template<typename Type>
constexpr bool is_word_v = (std::is_same_v<Type, W8_t> || std::is_same_v<Type, W16_t> || std::is_same_v<Type, W32_t> ||
           std::is_same_v<Type, W64_t>);

class CPU;

class ISAObject {
public:
  virtual ~ISAObject() = default;
};

class Printable : public ISAObject {
public:
  virtual std::string str() = 0;
};

class Runnable : public Printable {
public:
  virtual Runnable* run(CPU& cpu) = 0;
  Runnable* next = nullptr;
};

template <typename Type>
  requires(is_word_v<Type>)
class Reg;
class Function;
class Label;

class CPU {
private:
  W64_t regs[REG_CNT];
public:
  std::array<Reg<W8_t>*, REG_CNT> LI;
  std::array<Reg<W16_t>*, REG_CNT> XI;
  std::array<Reg<W32_t>*, REG_CNT> EXI;
  std::array<Reg<W64_t>*, REG_CNT> RXI;
  std::vector<std::unique_ptr<ISAObject>> allocated;
  std::vector<Runnable*> callstack;
  std::map<std::string, Function*> functions;
  std::map<std::string, std::map<std::string, Label*>> labels;

  CPU();

  template <typename T, typename T2 = std::remove_reference_t<T>>
  T2* allocate(T&& t) {
    std::unique_ptr<T2> ptr = std::make_unique<T2>(std::forward<T>(t));
    T2* res = ptr.get();
    allocated.emplace_back(std::move(ptr));
    return res;
  }

  template <typename T>
  T& get_reg(size_t num) {
    if constexpr (std::endian::native == std::endian::big) {
      return reinterpret_cast<T*>(regs)[(num + 1) * sizeof(regs[num]) / sizeof(T) - 1];
    } else if constexpr (std::endian::native == std::endian::little) {
      return reinterpret_cast<T*>(regs)[num * sizeof(regs[num]) / sizeof(T)];
    } else {
      static_assert(false, "mixed-endian is not supported");
    }
  }
};

class Label : public Runnable {
protected:
  std::string name;

public:
  Label(std::string name);

  std::string str() override;

  Runnable* run(CPU& cpu) override;
};

template <typename Type>
class Value : virtual public Printable {
public:
  virtual Type eval(CPU&) = 0;
};

template <typename Type>
class Dest : virtual public Printable {
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
    cpu.get_reg<Type>(num) = value;
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
};

class Function : public Runnable {
protected:
  std::string name;
  size_t args_cnt;

public:
  Function(std::string name, size_t args_cnt);

  std::string str() override;
};

class LocalFunction : public Function {
public:
  std::map<std::string, Label*> labels;

  LocalFunction(std::string name, size_t args_cnt) : Function(std::move(name), args_cnt) {}

  Runnable* run(CPU& cpu) override;
};

template <typename Ret, typename... Args>
  requires((std::is_void_v<Ret> || std::is_integral_v<Ret>) && ... && (std::is_integral_v<Args>))
class ExternalFunction : public Function {
protected:
  std::function<Ret(Args...)> func;

public:
  std::map<std::string, Label*> labels;

  ExternalFunction(std::string name, std::function<Ret(Args...)> func)
      : Function(std::move(name), sizeof...(Args)),
        func(std::move(func)) {}

  Runnable* run(CPU& cpu) override {
    run_impl(cpu, typename helpers::Range<0, sizeof...(Args)>::list());

    auto next = cpu.callstack.back();
    cpu.callstack.pop_back();
    return next;
  }

private:
  template <size_t... Indexes>
  void run_impl(CPU& cpu, helpers::List<Indexes...>) {
    if constexpr (std::is_void_v<Ret>) {
      func(cpu.get_reg<Args>(Indexes)...);
    } else {
      cpu.get_reg<Ret>(0) = func(cpu.get_reg<Args>(Indexes)...);
    }
  }
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
class Arithmetic : public Instruction<Dest<Type>, Args...> {
  using Base = Instruction<Dest<Type>, Args...>;

protected:
  virtual Type calc(CPU& cpu) = 0;

public:
  Arithmetic(Dest<Type>* result, Args*... args) : Base(result, args...) {}

  virtual Runnable* run(CPU& cpu) {
    std::get<0>(Base::ops)->update(cpu, calc(cpu));
    return Base::next;
  }
};

template <typename Type>
class Add : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) + std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Add(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "add";
  }
};

template <typename Type>
class Sub : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) - std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Sub(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "sub";
  }
};

template <typename Type>
class Mul : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_signed_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_signed_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 * op2;
  }

public:
  Mul(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "mul";
  }
};

template <typename Type>
class UMul : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_unsigned_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_unsigned_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 * op2;
  }

public:
  UMul(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "umul";
  }
};

template <typename Type>
class Div : public Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>> {
  using Base = Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>>;

public:
  Div(Dest<Type>* div, Dest<Type>* rem, Value<Type>* op1, Value<Type>* op2) : Base(div, rem, op1, op2) {}

  Runnable* run(CPU& cpu) override {
    Type op1 = static_cast<std::make_signed_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_signed_t<Type>>(std::get<3>(Base::ops)->eval(cpu));
    std::get<0>(Base::ops)->update(cpu, op1 / op2);
    std::get<1>(Base::ops)->update(cpu, op1 % op2);
    return Base::next;
  }

  std::string name() override {
    return "div";
  }
};

template <typename Type>
class UDiv : public Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>> {
  using Base = Instruction<Dest<Type>, Dest<Type>, Value<Type>, Value<Type>>;

public:
  UDiv(Dest<Type>* div, Dest<Type>* rem, Value<Type>* op1, Value<Type>* op2) : Base(div, rem, op1, op2) {}

  Runnable* run(CPU& cpu) override {
    Type op1 = static_cast<std::make_unsigned_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_unsigned_t<Type>>(std::get<3>(Base::ops)->eval(cpu));
    std::get<0>(Base::ops)->update(cpu, op1 / op2);
    std::get<1>(Base::ops)->update(cpu, op1 % op2);
    return Base::next;
  }

  std::string name() override {
    return "udiv";
  }
};

template <typename Type>
class And : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) & std::get<2>(Base::ops)->eval(cpu);
  }

public:
  And(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "and";
  }
};

template <typename Type>
class Or : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) | std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Or(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "or";
  }
};

template <typename Type>
class Xor : public Arithmetic<Type, Value<Type>, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) ^ std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Xor(Dest<Type>* result, Value<Type>* op1, Value<Type>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "xor";
  }
};

template <typename Type, typename Type2>
class LSh : public Arithmetic<Type, Value<Type>, Value<Type2>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type2>>;

protected:
  Type calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) << std::get<2>(Base::ops)->eval(cpu);
  }

public:
  LSh(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "lsh";
  }
};

template <typename Type, typename Type2>
class RShL : public Arithmetic<Type, Value<Type>, Value<Type2>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type2>>;

protected:
  Type calc(CPU& cpu) override {
    return static_cast<std::make_unsigned_t<Type>>(std::get<1>(Base::ops)->eval(cpu)) >>
           std::get<2>(Base::ops)->eval(cpu);
  }

public:
  RShL(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "rshl";
  }
};

template <typename Type, typename Type2>
class RShA : public Arithmetic<Type, Value<Type>, Value<Type2>> {
  using Base = Arithmetic<Type, Value<Type>, Value<Type2>>;

protected:
  Type calc(CPU& cpu) override {
    return static_cast<std::make_signed_t<Type>>(std::get<1>(Base::ops)->eval(cpu)) >>
           std::get<2>(Base::ops)->eval(cpu);
  }

public:
  RShA(Dest<Type>* result, Value<Type>* op1, Value<Type2>* op2) : Base(result, op1, op2) {}

  std::string name() override {
    return "rsha";
  }
};

template <typename Type>
class Inv : public Arithmetic<Type, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return ~std::get<1>(Base::ops)->eval(cpu);
  }

public:
  Inv(Dest<Type>* result, Value<Type>* op1) : Base(result, op1) {}

  std::string name() override {
    return "inv";
  }
};

template <typename Type>
class Not : public Arithmetic<Type, Value<Type>> {
  using Base = Arithmetic<Type, Value<Type>>;

protected:
  Type calc(CPU& cpu) override {
    return !std::get<1>(Base::ops)->eval(cpu);
  }

public:
  Not(Dest<Type>* result, Value<Type>* op1) : Base(result, op1) {}

  std::string name() override {
    return "not";
  }
};

template <typename Type>
class Mv : public Instruction<Dest<Type>, Value<Type>> {
  using Base = Instruction<Dest<Type>, Value<Type>>;

public:
  Mv(Dest<Type>* dest, Value<Type>* op1) : Base(dest, op1) {}

  Runnable* run(CPU& cpu) override {
    std::get<0>(Base::ops)->update(cpu, std::get<1>(Base::ops)->eval(cpu));
    return Base::next;
  }

  std::string name() override {
    return "mv";
  }
};

template <typename CondType, typename Type>
class MvC : public Instruction<Value<CondType>, Dest<Type>, Value<Type>> {
  using Base = Instruction<Value<CondType>, Dest<Type>, Value<Type>>;

public:
  MvC(Value<CondType>* cond, Dest<Type>* dest, Value<Type>* op1) : Base(cond, dest, op1) {}

  Runnable* run(CPU& cpu) override {
    if (std::get<0>(Base::ops)->eval(cpu)) {
      std::get<1>(Base::ops)->update(cpu, std::get<2>(Base::ops)->eval(cpu));
    }
    return Base::next;
  }

  std::string name() override {
    return "mvc";
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
};

template <typename ResType, typename Type>
class Eq : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) == std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Eq(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "eq";
  }
};

template <typename ResType, typename Type>
class Neq : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    return std::get<1>(Base::ops)->eval(cpu) != std::get<2>(Base::ops)->eval(cpu);
  }

public:
  Neq(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "neq";
  }
};

template <typename ResType, typename Type>
class Lt : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_signed_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_signed_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 < op2;
  }

public:
  Lt(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "lt";
  }
};

template <typename ResType, typename Type>
class Le : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_signed_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_signed_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 <= op2;
  }

public:
  Le(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "le";
  }
};

template <typename ResType, typename Type>
class ULt : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_unsigned_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_unsigned_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 < op2;
  }

public:
  ULt(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "ult";
  }
};

template <typename ResType, typename Type>
class ULe : public Arithmetic<ResType, Value<Type>, Value<Type>> {
  using Base = Arithmetic<ResType, Value<Type>, Value<Type>>;

protected:
  ResType calc(CPU& cpu) override {
    Type op1 = static_cast<std::make_unsigned_t<Type>>(std::get<1>(Base::ops)->eval(cpu));
    Type op2 = static_cast<std::make_unsigned_t<Type>>(std::get<2>(Base::ops)->eval(cpu));
    return op1 <= op2;
  }

public:
  ULe(Dest<ResType>* dest, Value<Type>* op1, Value<Type>* op2) : Base(dest, op1, op2) {}

  std::string name() override {
    return "ule";
  }
};

class Drw : public Instruction<Value<COORD_t>, Value<COORD_t>, Value<COLOR_t>> {
  using Base = Instruction<Value<COORD_t>, Value<COORD_t>, Value<COLOR_t>>;

public:
  Drw(Value<COORD_t>* x, Value<COORD_t>* y, Value<COLOR_t>* color);

  std::string name() override;

  Runnable* run(CPU& cpu) override;
};

class Flsh : public Instruction<> {
  using Base = Instruction<>;

public:
  Flsh();

  std::string name() override;

  Runnable* run(CPU& cpu) override;
};

class Call : public Instruction<Function> {
  using Base = Instruction<Function>;

public:
  Call(Function* func);

  std::string name() override;

  Runnable* run(CPU& cpu) override;
};

class Ret : public Instruction<> {
  using Base = Instruction<>;

public:
  Ret();

  std::string name() override;

  Runnable* run(CPU& cpu) override;
};

class Jp : public Instruction<Label> {
  using Base = Instruction<Label>;

public:
  Jp(Label* label);

  std::string name() override;

  Runnable* run(CPU& cpu) override;
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
};

class Nop : public Instruction<> {
  using Base = Instruction<>;

public:
  Nop();

  std::string name() override;

  Runnable* run(CPU& cpu) override;
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