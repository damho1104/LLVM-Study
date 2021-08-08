add_llvm_library(LLVMWeek01 MODULE BUILDTREE_ONLY
  CopyPrintfCall.cpp

  DEPENDS
  intrinsics_gen
  opt
  )
