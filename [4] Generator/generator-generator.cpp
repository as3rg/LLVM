#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <format>
#include <numeric>
#include <string>
#include <utility>

using namespace llvm;

struct Result {
  std::string header;
  std::string body;
  std::string footer;
};

template <typename... Args>
void addStr(size_t offset, std::string &target, const std::string &format) {
  target.append(std::string(offset * 2, ' '));
  target.append(format);
}

template <typename... Args>
  requires(sizeof...(Args) > 0)
void addStr(size_t offset, std::string &target,
            std::format_string<Args...> format, Args &&...args) {
  addStr(offset, target, std::format(format, std::forward<Args &&>(args)...));
}

template <typename... Args>
void addLine(size_t offset, std::string &target, const std::string &format) {
  addStr(offset, target, format);
  target.append("\n");
}

template <typename... Args>
  requires(sizeof...(Args) > 0)
void addLine(size_t offset, std::string &target,
             std::format_string<Args...> format, Args &&...args) {
  addStr(offset, target, std::move(format), std::forward<Args &&>(args)...);
  target.append("\n");
}

std::string getType(LLVMContext &C, Type *type) {
  if (type == Type::getVoidTy(C))
    return "Type::getVoidTy(context)";
  if (type == Type::getInt1Ty(C))
    return "Type::getInt1Ty(context)";
  if (type == Type::getInt8Ty(C))
    return "Type::getInt8Ty(context)";
  if (type == Type::getInt16Ty(C))
    return "Type::getInt16Ty(context)";
  if (type == Type::getInt32Ty(C))
    return "Type::getInt32Ty(context)";
  if (type == Type::getInt64Ty(C))
    return "Type::getInt64Ty(context)";
  if (type->isArrayTy())
    return std::format("ArrayType::get({}, {})",
                       getType(C, type->getArrayElementType()),
                       type->getArrayNumElements());
  if (type == PointerType::get(C, 0))
    return "PointerType::get(context, 0)";
  return "";
}

std::string getValue(const Value &val) {
  std::string block_address;
  raw_string_ostream string_stream(block_address);
  val.printAsOperand(string_stream, false);
  std::string res = string_stream.str();
  std::replace(res.begin(), res.end(), '.', '_');
  return res;
}

std::string getPrint(const Instruction &i) {
  std::string block_address;
  raw_string_ostream string_stream(block_address);
  i.print(string_stream);
  return string_stream.str();
}

std::string getOperand(const Value *val) {
  std::string sval = getValue(*val);
  if (sval.starts_with("%")) {
    return "val" + sval.substr(1);
  } else {
    Type *t = val->getType();
    if (t == Type::getInt1Ty(val->getContext())) {
      return std::format("builder.getInt1({})", sval);
    }
    if (t == Type::getInt8Ty(val->getContext())) {
      return std::format("builder.getInt8({})", sval);
    }
    if (t == Type::getInt16Ty(val->getContext())) {
      return std::format("builder.getInt16({})", sval);
    }
    if (t == Type::getInt32Ty(val->getContext())) {
      return std::format("builder.getInt32({})", sval);
    }
    if (t == Type::getInt64Ty(val->getContext())) {
      return std::format("builder.getInt64({}ll)", sval);
    }
    return "";
  }
}

template <typename T> inline std::string as_string(const std::string_view v) {
  return {v.data(), v.size()};
}

std::string getFuncName(std::string s) {
  std::replace(s.begin(), s.end(), '.', '_');
  return "func" + s;
}

struct CustomPass : public PassInfoMixin<CustomPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    LLVMContext &Ctx = M.getContext();
    IRBuilder<> builder(Ctx);

    Result global;

    addLine(0, global.header,
            "#include \"llvm/ExecutionEngine/ExecutionEngine.h\"");
    addLine(0, global.header,
            "#include \"llvm/ExecutionEngine/GenericValue.h\"");
    addLine(0, global.header, "#include \"llvm/IR/IRBuilder.h\"");
    addLine(0, global.header, "#include \"llvm/IR/LLVMContext.h\"");
    addLine(0, global.header, "#include \"llvm/IR/Module.h\"");
    addLine(0, global.header, "#include <array>");
    addLine(0, global.header, "#include <string>");
    addLine(0, global.header, "");
    addLine(0, global.header, "void simInit();");
    addLine(0, global.header, "void simExit();");
    addLine(0, global.header, "void simFlush();");
    addLine(0, global.header, "void simPutPixel(int x, int y, int argb);");
    addLine(0, global.header, "");
    addLine(0, global.header, "using namespace llvm;");
    addLine(0, global.header, "");
    addLine(0, global.header, "constexpr std::string RUN = \"run\";");
    addLine(0, global.header, "constexpr std::string PRINT = \"print\";");
    addLine(0, global.header, "");
    addLine(0, global.header, "int main(int argc, char* argv[]) {");
    addLine(1, global.header, "if (argc != 2 || argv[1] != PRINT && argv[1] != RUN) {");
    addLine(2, global.header, "outs() << \"either \\\"print\\\" or \\\"run\\\" expected\\n\";");
    addLine(2, global.header, "return 1;");
    addLine(1, global.header, "}");
    addLine(1, global.header, "");
    addLine(1, global.header, "LLVMContext context;");
    addLine(1, global.header,
            "Module *module = new Module(\"app.c\", context);");
    addLine(1, global.header, "IRBuilder<> builder(context);");

    addLine(1, global.footer, "if (std::string(argv[1]) == PRINT) {");
    addLine(2, global.footer, "module->print(outs(), nullptr);");
    addLine(2, global.footer, "return 0;");
    addLine(1, global.footer, "} else if (std::string(argv[1]) == RUN) {");
    addLine(2, global.footer, "LLVMInitializeNativeTarget();");
    addLine(2, global.footer, "LLVMInitializeNativeAsmPrinter();");
    addLine(2, global.footer,
            "ExecutionEngine *ee = "
            "EngineBuilder(std::unique_ptr<Module>(module)).create();");
    addLine(2, global.footer,
            "ee->InstallLazyFunctionCreator([=](const std::string &fnName) -> "
            "void * {");
    addLine(3, global.footer, "if (fnName == \"simInit\") {");
    addLine(4, global.footer, "return reinterpret_cast<void *>(simInit);");
    addLine(3, global.footer, "}");
    addLine(3, global.footer, "if (fnName == \"simExit\") {");
    addLine(4, global.footer, "return reinterpret_cast<void *>(simExit);");
    addLine(3, global.footer, "}");
    addLine(3, global.footer, "if (fnName == \"simPutPixel\") {");
    addLine(4, global.footer, "return reinterpret_cast<void *>(simPutPixel);");
    addLine(3, global.footer, "}");
    addLine(3, global.footer, "if (fnName == \"simFlush\") {");
    addLine(4, global.footer, "return reinterpret_cast<void *>(simFlush);");
    addLine(3, global.footer, "}");
    addLine(3, global.footer, "return nullptr;");
    addLine(2, global.footer, "});");
    addLine(2, global.footer, "ee->finalizeObject();");
    addLine(2, global.footer, "ee->runFunction(funcmain, {});");
    addLine(2, global.footer, "return 0;");
    addLine(1, global.footer, "}");
    addLine(0, global.footer, "}");

    for (auto &F : M) {
      Result func;

      {
        std::string args =
            std::accumulate(F.args().begin(), F.args().end(), std::string(),
                            [&Ctx](const std::string &ss, auto &&arg) {
                              std::string s = getType(Ctx, arg.getType());
                              return ss.empty() ? s : ss + ", " + s;
                            });
        std::string name = getFuncName(F.getName().str());
        addLine(1, global.header,
                "Function *{} = Function::Create(FunctionType::get({}, {{ "
                "{} }}, false), Function::ExternalLinkage, \"{}\", module);",
                name, getType(Ctx, F.getReturnType()), args, F.getName().str());
        addLine(2, func.header, "Function *func = {};", name);

        for (uint i = 0; i < F.arg_size(); ++i) {
          addLine(2, func.body, "Value *val{} = func->getArg({});", i, i);
        }
      }
      if (F.isDeclaration())
        continue;
      for (auto &B : F) {
        {
          std::string i = getOperand(&B);
          addLine(2, func.header,
                  "BasicBlock *{} = BasicBlock::Create(context, \"\", func);",
                  i);
          addLine(2, func.body, "builder.SetInsertPoint({});", i);
        }
        for (auto &I : B) {
          std::string result;
          if (!I.use_empty())
            result += std::format("Value *{} = ", getOperand(&I));
          switch (I.getOpcode()) {
          case Instruction::Add:
            result += std::format("builder.CreateAdd({}, {}, \"\", {}, {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)),
                                  I.hasNoUnsignedWrap(), I.hasNoSignedWrap());
            break;
          case Instruction::Sub:
            result += std::format("builder.CreateSub({}, {}, \"\", {}, {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)),
                                  I.hasNoUnsignedWrap(), I.hasNoSignedWrap());
            break;
          case Instruction::Mul:
            result += std::format("builder.CreateMul({}, {}, \"\", {}, {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)),
                                  I.hasNoUnsignedWrap(), I.hasNoSignedWrap());
            break;
          case Instruction::Shl:
            result += std::format("builder.CreateShl({}, {}, \"\", {}, {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)),
                                  I.hasNoUnsignedWrap(), I.hasNoSignedWrap());
            break;
          case Instruction::Or:
            result += std::format("builder.CreateOr({}, {}, \"\")",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)));
            break;
          case Instruction::And:
            result += std::format("builder.CreateAnd({}, {}, \"\")",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)));
            break;
          case Instruction::Xor:
            result += std::format("builder.CreateXor({}, {}, \"\")",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)));
            break;
          case Instruction::URem:
            result += std::format("builder.CreateURem({}, {}, \"\")",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)));
            break;
          case Instruction::LShr:
            result += std::format("builder.CreateLShr({}, {}, \"\", {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)), I.isExact());
            break;
          case Instruction::UDiv:
            result += std::format("builder.CreateUDiv({}, {}, \"\", {})",
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)), I.isExact());
            break;
          case Instruction::ICmp: {
            std::string pred = ICmpInst::getPredicateName(
                                   dyn_cast<ICmpInst>(&I)->getPredicate())
                                   .str();
            std::transform(pred.begin(), pred.end(), pred.begin(), ::toupper);
            result += std::format("builder.CreateICmp{}({}, {}, \"\")", pred,
                                  getOperand(I.getOperand(0)),
                                  getOperand(I.getOperand(1)));
          } break;
          case Instruction::Ret: {
            Value *val = dyn_cast<ReturnInst>(&I)->getReturnValue();
            if (val)
              result += std::format("builder.CreateRet({})", getOperand(val));
            else
              result += "builder.CreateRetVoid()";
          } break;
          case Instruction::Br: {
            BranchInst *op = dyn_cast<BranchInst>(&I);
            if (op->isConditional()) {
              result += std::format("builder.CreateCondBr({}, {}, {})",
                                    getOperand(op->getOperand(0)),
                                    getOperand(op->getOperand(2)),
                                    getOperand(op->getOperand(1)));
            } else {
              result += std::format("builder.CreateBr({})",
                                    getOperand(op->getOperand(0)));
            }
          } break;
          case Instruction::ZExt:
            result += std::format(
                "builder.CreateZExt({}, {})", getOperand(I.getOperand(0)),
                getType(Ctx, dyn_cast<CastInst>(&I)->getDestTy()));
            break;
          case Instruction::Trunc:
            result += std::format(
                "builder.CreateTrunc({}, {})", getOperand(I.getOperand(0)),
                getType(Ctx, dyn_cast<CastInst>(&I)->getDestTy()));
            break;
          case Instruction::SExt:
            result += std::format(
                "builder.CreateSExt({}, {})", getOperand(I.getOperand(0)),
                getType(Ctx, dyn_cast<CastInst>(&I)->getDestTy()));
            break;
          case Instruction::Call: {
            CallInst *f = dyn_cast<CallInst>(&I);
            std::string args = std::accumulate(
                f->args().begin(), f->args().end(), std::string(),
                [&Ctx](const std::string &ss, auto &&arg) {
                  std::string s = getOperand(arg);
                  return ss.empty() ? s : ss + ", " + s;
                });
            result += std::format(
                "builder.CreateCall({}, {{{}}})",
                getFuncName(f->getCalledFunction()->getName().str()), args);
          } break;
          case Instruction::Load: {
            LoadInst *op = dyn_cast<LoadInst>(&I);
            result += std::format(
                "builder.CreateAlignedLoad({}, {}, MaybeAlign({}))",
                getType(Ctx, op->getType()), getOperand(op->getOperand(0)),
                op->getAlign().value());

          } break;
          case Instruction::Store: {
            StoreInst *op = dyn_cast<StoreInst>(&I);
            result += std::format(
                "builder.CreateAlignedStore({}, {}, MaybeAlign({}))",
                getOperand(op->getOperand(0)), getOperand(op->getOperand(1)),
                op->getAlign().value());

          } break;
          case Instruction::Select: {
            SelectInst *op = dyn_cast<SelectInst>(&I);
            result += std::format("builder.CreateSelect({}, {}, {})",
                                  getOperand(op->getOperand(0)),
                                  getOperand(op->getOperand(1)),
                                  getOperand(op->getOperand(2)));

          } break;
          case Instruction::Alloca: {
            AllocaInst *op = dyn_cast<AllocaInst>(&I);
            result += std::format("builder.CreateAlloca({})",
                                  getType(Ctx, op->getAllocatedType()));
          } break;
          case Instruction::PHI: {
            PHINode *op = dyn_cast<PHINode>(&I);
            result = std::format("PHINode *{} = builder.CreatePHI({}, {})",
                                 getOperand(&I), getType(Ctx, op->getType()),
                                 op->getNumIncomingValues());
            for (int i = 0; i < op->getNumIncomingValues(); ++i) {
              addLine(2, func.footer, "{}->addIncoming({}, {});",
                      getOperand(&I), getOperand(op->getIncomingValue(i)),
                      getOperand(op->getIncomingBlock(i)));
            }
          } break;
          case Instruction::GetElementPtr: {
            GetElementPtrInst *op = dyn_cast<GetElementPtrInst>(&I);
            std::string args =
                std::accumulate(op->op_begin() + 1, op->op_end(), std::string(),
                                [&Ctx](const std::string &ss, auto &&arg) {
                                  std::string s = getOperand(arg);
                                  return ss.empty() ? s : ss + ", " + s;
                                });
            result +=
                std::format("GetElementPtrInst::Create({}, {}, {{{}}});\n",
                            getType(Ctx, op->getSourceElementType()),
                            getOperand(op->getOperand(0)), args);
            addStr(2, result, "builder.Insert({})", getOperand(&I));
          } break;
          case Instruction::Switch: {
            SwitchInst *op = dyn_cast<SwitchInst>(&I);
            static int switchNum = 0;
            result += std::format(
                "SwitchInst *s{} = builder.CreateSwitch({}, {})", switchNum,
                getOperand(op->getOperand(0)), getOperand(op->getOperand(1)));
            for (auto &v : op->cases()) {
              addLine(2, func.footer, "s{}->addCase({}, {});", switchNum,
                      getOperand(v.getCaseValue()),
                      getOperand(v.getCaseSuccessor()));
            }
          } break;
          default:
            I.print(errs());
            errs() << "\n";
            result += "wtf";
            break;
          }
          result += ";";

          std::string comment = getPrint(I);
          std::replace(comment.begin(), comment.end(), '\n', ' ');
          addLine(2, func.body, "// " + comment);
          addLine(2, func.body, result);
        }
      }
      addLine(1, global.body, "{");
      global.body += func.header + func.body + func.footer;
      addLine(1, global.body, "}");
    }
    outs() << global.header << global.body << global.footer;
    return PreservedAnalyses::none();
  };

  static bool isRequired() { return true; }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(CustomPass{});
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "CustomPlugin", "0.0.1", callback};
};

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}