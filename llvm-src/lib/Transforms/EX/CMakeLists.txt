add_llvm_library(LLVMEX MODULE BUILDTREE_ONLY
  EX.cpp

  DEPENDS
  intrinsics_gen
  opt
  )

add_dependencies(LLVMEX intrinsics_gen)
