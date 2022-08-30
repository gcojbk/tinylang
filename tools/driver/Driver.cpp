
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"
#include "tinylang/Basic/Version.h"
#include "tinylang/Parser/Parser.h"


static llvm::cl::opt<std::string> Input(llvm::cl::Positional,
                                        llvm::cl::desc("<Input expression>"),
                                        llvm::cl::init(""));


int main(int argc, const char** argv) {
    llvm::InitLLVM X(argc, argv);
    llvm::cl::ParseCommandLineOptions(argc, argv, "tinylang - the expression compiler\n");
    tinylang::Lexer lexer(Input);
    tinylang::Parser parser(lexer);
    [[maybe_unused]]auto node = parser.Parse();
    // if (!node || parser.HasError()) {
    //     llvm::errs() << "Syntax errors occured\n";
    //     return 1;
    // }

    // Sema semantic;
    // if (semantic.Semantic(node)) {
    //     llvm::errs() << "Semantic errors occured\n";
    //     return 1;
    // }

    // CodeGen codegen;
    // codegen.Compile(node);
    return 0;
}