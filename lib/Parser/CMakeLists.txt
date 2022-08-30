set(LLVM_LINK_COMPONENTS support)

add_tinylang_library(tinylangParser Parser.cc LINK_LIBS tinylangBasic)
