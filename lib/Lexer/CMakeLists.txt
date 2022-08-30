set(LLVM_LINK_COMPONENTS support)

add_tinylang_library(tinylangLexer Lexer.cc LINK_LIBS tinylangBasic)
