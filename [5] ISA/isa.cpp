#include "isa.h"

#include "sim.h"

#include <format>

std::string isa::Label::str() {
  return "%" + name;
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
  cpu.callstack.push_back(Base::next);
  return std::get<0>(Base::ops);
}

isa::Ret::Ret() : Base() {}

std::string isa::Ret::name() {
  return "ret";
}

isa::Runnable* isa::Ret::run(CPU& cpu) {
  auto next = cpu.callstack.back();
  cpu.callstack.pop_back();
  return next;
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

isa::Function::Function(std::string name, size_t args_cnt) : name(name), args_cnt(args_cnt) {}

std::string isa::Function::str() {
  return std::format("#{}({})", name, args_cnt);
}

isa::Label::Label(std::string name) : name(name) {}

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