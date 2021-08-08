//===- CopyPrintfCall.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
#include <fstream>
using namespace llvm;

namespace llvm::Study::Week01
{
  namespace {
    std::vector<Instruction*> getPrintfCallInstList(Function &F){
      std::vector<Instruction*> printfCallInstList;
      for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
      {
        auto *inst = dyn_cast<Instruction>(instIter.getInstructionIterator());
        if (inst->getOpcode() != Instruction::Call)
        {
          continue;
        }
        auto *callInst = dyn_cast<CallInst>(inst);
        if(callInst->getCalledFunction()->getName() == "printf")
        {
          printfCallInstList.push_back(inst);
        }
      }
      return printfCallInstList;
    }

    std::string getNameWithoutExtFromFileName(const std::string& fileName){
      auto inx = fileName.rfind(".");
      if(inx != std::string::npos){
        return fileName.substr(0, inx);
      }
      return fileName;
    }

    std::string getModFileName(const std::string& fileName){
      return getNameWithoutExtFromFileName(fileName) + ".mod.ll";
    }

    void changeSourceFileName(Module& M){
      M.setSourceFileName(getModFileName(M.getSourceFileName()));
    }

    void printAndWriteModule(Module& M){
      std::string str;
      raw_string_ostream ostream(str);
      ostream << M;
      ostream.flush();

      std::ofstream writeFile;
      writeFile.open(M.getSourceFileName());
      if(writeFile.is_open()){
        writeFile << str;
        writeFile.close();
      }
      llvm::errs() << str;
    }
  }
  class CopyPrintfCall : public ModulePass
  {
  public:
    static char ID; // Pass identification
    CopyPrintfCall() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
      for (auto &function : M.getFunctionList())
      {
        runOnFunction(function);
      }
      changeSourceFileName(M);
      printAndWriteModule(M);
      return true;
    }

    virtual bool runOnFunction(Function &F)
    {
      llvm::errs() << F.getName() << "\n";
      for (auto &inst : getPrintfCallInstList(F))
      {
        auto callInst = dyn_cast<CallInst>(inst);
        SmallVector<OperandBundleDef, 1> newBundles;
        callInst->getOperandBundlesAsDefs(newBundles);
        auto newCallInst = CallInst::Create(callInst, newBundles);
        newCallInst->insertAfter(inst);
      }
      return true;
    }
  };
}

  char llvm::Study::Week01::CopyPrintfCall::ID = 0;
  static RegisterPass<llvm::Study::Week01::CopyPrintfCall> X("cpPrintf", "CopyPrintfCall Pass - created by LDH");