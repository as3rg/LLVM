#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Type.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <string>

using namespace llvm;

bool is_allowed(Module& M, Function& F) {
  std::string sourceName = M.getSourceFileName();
  if (sourceName != "code/app/app.c" && sourceName != "code/float32/float32.c" && sourceName != "code/float32/float32_math.c") 
    return false;
  std::string funcName = F.getName().str();
  return true && !F.isDeclaration();
}

struct CustomPass : public PassInfoMixin<CustomPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    LLVMContext &Ctx = M.getContext();
    IRBuilder<> builder(Ctx);

    ArrayRef<Type *> printParamTypes = {Type::getInt8Ty(Ctx)};
    FunctionCallee printFunc = M.getOrInsertFunction("puts", Type::getInt32Ty(Ctx), PointerType::get(Type::getInt8Ty(Ctx), 0));

    for (auto &F : M) {
      if (!is_allowed(M, F)) 
        continue;

      for (auto &B : F) {
        for (auto &I : B) {
          if (dyn_cast<PHINode>(&I)) continue;
          builder.SetInsertPoint(&I);
          for (auto &O : I.operands()) {
            if (auto *O2 = dyn_cast<Instruction>(O)) {
              Value *iPtr = builder.CreateGlobalStringPtr(std::string() + I.getOpcodeName() + " <- " + O2->getOpcodeName());
              builder.CreateCall(printFunc,{iPtr});
            }
          }
        }
      }
    }
    return PreservedAnalyses::none();
  };
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