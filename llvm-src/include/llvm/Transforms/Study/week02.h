#ifndef LLVM_TRANSFORMS_STUDY_WEEK02_H
#define LLVM_TRANSFORMS_STUDY_WEEK02_H
#include "llvm/IR/PassManager.h"

namespace llvm {


/// Legacy pass creation function for the above pass.
ModulePass *createInsertFunctionCallPass();

} // end namespace llvm
#endif