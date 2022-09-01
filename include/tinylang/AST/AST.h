#pragma once

#include <vector>
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"
#include "tinylang/Lexer/Token.h"
#include "tinylang/AST/fwd.h"

namespace tinylang {

using DeclList = std::vector<Decl*>;
using ExprList = std::vector<Expr*>;
using StmtList = std::vector<Stmt*>;

class ASTVisitor {
 public:
    virtual ~ASTVisitor() = default;

 public:
    virtual void visit(AST &) {};
    virtual void visit(Expr &) {};
};

class AST {
 public:
    AST() = default;
    virtual ~AST() {}

    virtual void accept(ASTVisitor& visitor) = 0;
};
}  // namespace tinylang
