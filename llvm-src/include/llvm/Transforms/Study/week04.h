#ifndef LLVM_TRANSFORMS_STUDY_WEEK04_H
#define LLVM_TRANSFORMS_STUDY_WEEK04_H
#include "llvm/IR/PassManager.h"

namespace llvm {


/// Legacy pass creation function for the above pass.
ModulePass *createWrapFunctionPass(bool printFlag);

} // end namespace llvm
#endif