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
#include "llvm/Transforms/Study/week03.h"
#include <fstream>
using namespace llvm;

namespace 
{
    class SummarizeFunctionCall : public ModulePass
    {
    public:
        static char ID; // Pass identification
        std::map<StringRef, unsigned int> callFuncMap;
        SummarizeFunctionCall() : ModulePass(ID)
        {
            initializeSummarizeFunctionCallPass(*PassRegistry::getPassRegistry());
        }

        virtual bool runOnModule(Module &M)
        {
            Function* mainFunc = nullptr;
            for (auto &function : M.getFunctionList())
            {
                if(function.getName() == "main"){
                    mainFunc = &function;
                }
                runOnFunction(function);
            }
            auto summarizeFunction = CreateAndInsertSummarizeFunction(M);
            if (mainFunc != nullptr)
            {
                CallInst::Create(FunctionType::get(Type::getVoidTy(M.getContext()), false),
                                 summarizeFunction)
                    ->insertBefore(&(mainFunc->getBasicBlockList().back().getInstList().back()));
            }
            return true;
        }

        virtual bool runOnFunction(Function &F)
        {
            for (auto instIter = inst_begin(F); instIter != inst_end(F); ++instIter)
            {
                auto *inst = dyn_cast<Instruction>(instIter.getInstructionIterator());
                if(inst->getOpcode() != Instruction::Call){
                    continue;
                }
                auto *callInst = dyn_cast<CallInst>(inst);
                StringRef funcName = callInst->getCalledFunction()->getName();
                if(callFuncMap.find(funcName) == callFuncMap.end()){
                    callFuncMap[funcName] = 1;
                }
                else{
                    callFuncMap[funcName]++;
                }
                
            }
            return true;
        }

        Function* CreateAndInsertSummarizeFunction(Module &M)
        {
            auto summarizeFunction = CreateAndInsertSummarizeFunctionPrototype(M);
            CreateSummarizeFunctionBody(M, M.getFunction("printf"), summarizeFunction);
            return summarizeFunction;
        }

        GlobalVariable *CreateStringConstant(Module& M, std::string stringValue)
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

        void CreateAndInsertPrintfIntoBasicBlock(Module& M, std::string message, Function* printfFunction, BasicBlock* bb){
            auto printfMessage = CreateStringConstant(M, message);
            auto arguments = CreatePrintfArgument(M, printfMessage);
            CallInst::Create(printfFunction->getFunctionType(),
                                 printfFunction,
                                 arguments,
                                 "",
                                 bb);
        }

        Function* CreateAndInsertSummarizeFunctionPrototype(Module& M)
        {
            auto& context = M.getContext();
            auto funcType = FunctionType::get(Type::getVoidTy(context), false);
            auto insertFunction = Function::Create(funcType, GlobalValue::LinkageTypes::InternalLinkage, "SummarizeCalledFuncInst", M);
            insertFunction->setCallingConv(CallingConv::C);
            return insertFunction;
        }

        void CreateSummarizeFunctionBody(Module& M, Function* printfFunction, Function* summarizeFunctionPrototype)
        {
            auto entryBasicblock = BasicBlock::Create(M.getContext(), "entry", summarizeFunctionPrototype);
            CreateAndInsertPrintfIntoBasicBlock(M, "\nPROFILE_COLLECT_FUNC_INFO-----", printfFunction, entryBasicblock);

            for (auto &iter : callFuncMap)
            {
                auto stringToInsert = iter.first.str() + " : " + std::to_string(iter.second);
                CreateAndInsertPrintfIntoBasicBlock(M, stringToInsert, printfFunction, entryBasicblock);
            }
            ReturnInst::Create(M.getContext(), entryBasicblock);
        }
    };
}

ModulePass *llvm::createSummarizeFunctionCallPass()
{
    return new SummarizeFunctionCall();
}

INITIALIZE_PASS(SummarizeFunctionCall, "SummarizeFunctionCall",
                "SummarizeFunctionCall", false, false)

char SummarizeFunctionCall::ID = 0;