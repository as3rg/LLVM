#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "isa-parser.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/raw_ostream.h"
#include <array>
#include <string>
#include <iostream>
#include "sim.h"

llvm::Value* create_register(llvm::IRBuilder<>& builder) {
  return builder.CreateAlloca(llvm::Type::getInt64Ty(builder.getContext()));
}

llvm::Value* load_reg(llvm::IRBuilder<>& builder, const std::array<llvm::Value*, isa::REG_CNT>& registers, size_t num, llvm::Type* type) {
  llvm::Value* val = builder.CreateLoad(llvm::Type::getInt64Ty(builder.getContext()), registers[num]);
  return builder.CreateTrunc(val, type);
}

void store_reg(llvm::IRBuilder<>& builder, const std::array<llvm::Value*, isa::REG_CNT>& registers, size_t num, llvm::Value* value) {
  llvm::Value* val = builder.CreateZExt(value, llvm::Type::getInt64Ty(builder.getContext()));
  builder.CreateStore(val, registers[num]);
}

template <typename... Types>
struct Pack {};

template <size_t arg_cnt, template<typename...> typename I, typename... Ops, typename... TS>
bool try_apply(const auto& func, isa::Runnable* value, Pack<Ops...> ops, Pack<TS...> pack = {}) {
  if constexpr (arg_cnt == sizeof...(TS)) {
    if (I<TS...>* v = dynamic_cast<I<TS...>*>(value)) {
      func(v);
      return true;
    } else {
      return false;
    }
  } else {
    return (false || ... || (try_apply<arg_cnt, I>(func, value, ops, Pack<TS..., Ops>{})));
  }
}

constexpr std::string RUN_IR = "run-ir";
constexpr std::string PRINT_IR = "print-ir";
constexpr std::string RUN_ISA = "run-isa";
constexpr std::string PRINT_ISA = "print-isa";

int main(int argc, char* argv[]) {
  if (argc != 2 || argv[1] != PRINT_ISA && argv[1] != RUN_ISA && argv[1] != PRINT_IR && argv[1] != RUN_IR) {
    llvm::outs() << "either \"" << PRINT_IR << "\" or \"" << RUN_IR << "\" or \"" << PRINT_ISA << "\" or \"" << RUN_ISA << "\" expected\n";
    return 1;
  }
  std::vector<std::string> lines;
  for (size_t line_num = 0; ; ++line_num) {
    std::string line;
    std::getline(std::cin, line);
    if (!std::cin) {
      break;
    }
    lines.emplace_back(line); 
  }

  ParsingContext pcxt;
  int code = parse(pcxt, lines);
  if (code) return 1;

  if (argv[1] == PRINT_ISA) {
    for (auto [_, func] : pcxt.functions) {
      llvm::outs() << func->str() << "\n";
      for (isa::Runnable* next = func->next; next; next = next->next) {
        llvm::outs() << next->str() << "\n";
      }
      llvm::outs() << "\n";
    }
    return 0;  
  } else if (argv[1] == RUN_ISA) {
    isa::Function* func = pcxt.functions["#app(0)"];
    if (!func) {
      llvm::errs() << "#app(0) not found\n";
      return 1;
    }
    isa::CPU cpu;
    simInit();
    isa::run(cpu, func, true);
    simExit();
    return 0;
  }

  llvm::LLVMContext context {};
  llvm::Module *module = new llvm::Module("app.c", context);
  llvm::IRBuilder<> builder(context);

  isa::LLVMContext cxt{&builder, module, {}, {}};

  for (auto [fname, func] : pcxt.functions) {
    func->compile(&cxt);
  }
  
  if (argv[1] == PRINT_IR) {
    module->print(llvm::outs(), nullptr);
    return 0;
  } else if (argv[1] == RUN_IR) {
    llvm::Function* func = cxt.functions["#app(0)"];
    if (!func) {
      llvm::errs() << "#app(0) not found\n";
      return 1;
    }

    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    llvm::ExecutionEngine *ee = llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();
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
    ee->runFunction(func, {});
    simExit();
    return 0;
  }
}
