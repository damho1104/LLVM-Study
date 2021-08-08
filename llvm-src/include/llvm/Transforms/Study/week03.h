#ifndef LLVM_TRANSFORMS_STUDY_WEEK03_H
#define LLVM_TRANSFORMS_STUDY_WEEK03_H
#include "llvm/IR/PassManager.h"

namespace llvm {


/// Legacy pass creation function for the above pass.
ModulePass *createSummarizeFunctionCallPass();

} // end namespace llvm
#endif