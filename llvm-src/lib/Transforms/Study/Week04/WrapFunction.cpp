//===- CopyPrintfCall.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/InitializePasses.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Transforms/Study/week04.h"
using namespace llvm;

namespace
{
    class WrapFunction : public ModulePass
    {
    private:
        bool printFlag_;

    public:
        static char ID; // Pass identification
        std::vector<CallInst *> callInstructionList;
        WrapFunction(bool printFlag = false) : ModulePass(ID)
        {
            printFlag_ = printFlag;
            initializeWrapFunctionPass(*PassRegistry::getPassRegistry());
        }

        virtual bool runOnModule(Module &M)
        {
            auto flagString = (printFlag_ == true) ? "true\n" : "false\n";
            llvm::errs() << "fwrap_func Option with guide: " << flagString;
            for (auto &function : M.getFunctionList())
            {
                collectCallInstFromFunction(function);
            }
            for (auto &callInst : callInstructionList)
            {
                auto wrapperFunction = CreateAndInsertWrapperFunction(M, callInst);
                callInst->setCalledFunction(wrapperFunction);
            }
            return true;
        }

        void collectCallInstFromFunction(Function &F)
        {
            for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
            {
                auto *inst = dyn_cast<Instruction>(instIter.getInstructionIterator());
                if (inst->getOpcode() != Instruction::Call)
                {
                    continue;
                }
                auto callInst = dyn_cast<CallInst>(inst);
                callInstructionList.push_back(callInst);
            }
        }

        Function *CreateAndInsertWrapperFunction(Module &M, CallInst *callInst)
        {
            auto functionName = "__call_" + callInst->getCalledFunction()->getName().str();
            Function *result = M.getFunction(functionName);
            if (result != nullptr)
            {
                return result;
            }
            auto wrapperFunction = CreateOrGetWrapperFunctionPrototype(M,
                                                                       functionName,
                                                                       callInst);
            CreateWrapperFunctionBody(M,
                                      M.getFunction("printf"),
                                      wrapperFunction,
                                      callInst);
            return wrapperFunction;
        }

        GlobalVariable *CreateStringConstant(Module &M, std::string stringValue)
        {
            auto stringToInsert = stringValue + "\n";
            auto stringConstant = ConstantDataArray::getString(M.getContext(), stringToInsert, true);
            auto globalVariable = new GlobalVariable(M, stringConstant->getType(), true, GlobalValue::PrivateLinkage, stringConstant, ".str");
            globalVariable->setAlignment(MaybeAlign(1));
            return globalVariable;
        }

        std::vector<Value *> CreatePrintfArgument(Module &M, GlobalVariable *variable)
        {
            auto constantZero = ConstantInt::get(M.getContext(), APInt(64, StringRef("0"), 10));
            std::vector<Constant *> value = {constantZero, constantZero};
            auto printfArgument = ConstantExpr::getGetElementPtr(variable->getInitializer()->getType(), variable, value);
            return {printfArgument};
        }

        void CreateAndInsertPrintfIntoBasicBlock(Module &M, std::string message, Function *printfFunction, BasicBlock *bb)
        {
            auto printfMessage = CreateStringConstant(M, message);
            auto arguments = CreatePrintfArgument(M, printfMessage);
            CallInst::Create(printfFunction->getFunctionType(),
                             printfFunction,
                             arguments,
                             "",
                             bb);
        }

        Function *CreateOrGetWrapperFunctionPrototype(Module &M, std::string functionName, CallInst *callInst)
        {
            auto result = Function::Create(callInst->getFunctionType(),
                                           GlobalValue::LinkageTypes::InternalLinkage,
                                           functionName,
                                           M);
            result->setCallingConv(CallingConv::C);
            return result;
        }

        void CreateWrapperFunctionBody(Module &M, Function *printfFunction, Function *wrapperFunctionPrototype, CallInst *callInst)
        {
            auto entryBasicblock = BasicBlock::Create(M.getContext(), "entry", wrapperFunctionPrototype);
            if (printFlag_)
            {
                CreateAndInsertPrintfIntoBasicBlock(M,
                                                    "call " + callInst->getCalledFunction()->getName().str() + " function",
                                                    printfFunction,
                                                    entryBasicblock);
            }
            std::vector<Value *> args(callInst->arg_begin(), callInst->arg_end());
            auto newCall = CallInst::Create(callInst->getFunctionType(),
                                            callInst->getCalledFunction(),
                                            args,
                                            "",
                                            entryBasicblock);
            if (callInst->getType()->isVoidTy())
            {
                ReturnInst::Create(M.getContext(),
                                   entryBasicblock);
            }
            else
            {
                ReturnInst::Create(M.getContext(),
                                   newCall,
                                   entryBasicblock);
            }
        }
    };
}

ModulePass *llvm::createWrapFunctionPass(bool printFlag)
{
    return new WrapFunction(printFlag);
}

INITIALIZE_PASS(WrapFunction, "printFlag",
                "WrapFunction", false, false)

char WrapFunction::ID = 0;