//===- Ex.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/InstIterator.h"
#include "llvm/Analysis/ScalarEvolution.h"
//#include "llvm/Analysis/Dominators.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
using namespace llvm;

namespace {
  class EX : public ModulePass {
		public:
    static char ID; // Pass identification
    EX() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M) {
			for(auto& function : M.getFunctionList()){
				errs() << "Function Name: " << function.getName() << "\n";
			}
      return true;
    }
  };
}

char EX::ID = 0;
static RegisterPass<EX> X("ex", "EX Pass - created by LDH");


// namespace {
// 	class EX2 : public FunctionPass {
// 		public:
// 			static char ID;
// 			EX2() : FunctionPass(ID) {}

// 			virtual bool runOnFunction(Function &F){
// 				DominatorTree *DT = &getAnalysis<DominatorTree>();
// 				Module *M = F.getParent();
// 				Module::iterator fi = M->begin();
// 				Function *F1 = fi;
// 				Function *F2 = ++fi;

// 				BasicBlock *FB1 = F1->begin();
// 				BasicBlock *FB2 = F2->begin();

// 				if(DT->dominates(FB1, FB2)){
// 					errs() << "aa\n";
// 				}
// 				else
// 					errs() << "bb\n";


// /*
// 				for(Function::iterator Ff=F.begin() ; Ff != F.end() ; Ff++){
// 					start = Ff;
// 					for(Function::iterator Fi=F.begin() ; Fi != F.end() ; Fi++){
// 						bb = Fi;
// 						if(DT->dominates(start, bb)){
// 							errs() << "'" << start->getName() << "' dominates '" << bb->getName() << "' : yes\n";
// 						}
// 						else
// 							errs() << "'" << start->getName() << "' dominates '" << bb->getName() << "' : no\n";
// 					}
// 					errs() << "\n\n";
// 				}*/
// 				return true;
// 			}

// 			virtual void getAnalysisUsage(AnalysisUsage &AU) const {
// 				AU.addRequired<DominatorTree>();
// 			}
// 	};
// }

// char EX2::ID = 0;
// static RegisterPass<EX2> Y("ex2", "EX2 Pass - created by LDH");


// namespace {
// 	class EX3 : public FunctionPass {
// 		public:
// 			static char ID;
// 			EX3() : FunctionPass(ID) {}

// 			virtual bool runOnFunction(Function &F){
// 				DominanceFrontier *DF = &getAnalysis<DominanceFrontier>();

// 				DF->dump();
// 				return true;
// 			}

// 			virtual void getAnalysisUsage(AnalysisUsage &AU) const {
// 				AU.addRequired<DominanceFrontier>();
// 			}
// 	};
// }

// char EX3::ID = 0;
// static RegisterPass<EX3> Z("ex3", "EX3 Pass - created by LDH");

