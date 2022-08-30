#pragma once

#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"

namespace tinylang {
class AST;
class Expr;
class Factor;
class BinaryOp;
class WithDecl;

class ASTVisitor {
 public:
    virtual ~ASTVisitor() = default;

 public:
    virtual void visit(AST &) {};
    virtual void visit(Expr &) {};
    virtual void visit(Factor &) = 0;
    virtual void visit(BinaryOp &) = 0;
    virtual void visit(WithDecl &) = 0;
};


class AST {
 public:
    AST() = default;
    virtual ~AST() {}

    virtual void accept(ASTVisitor& visitor) = 0;
};


class Expr : public AST {
 public:
    Expr() {}
};


class Factor : public Expr {
 public:
    enum ValueKind {Ident, Number};

 public:
    Factor(ValueKind kind, llvm::StringRef val): kind_(kind), val_(val) {}

    ValueKind GetKind() {
        return kind_;
    }

    llvm::StringRef GetVal() {
        return val_;
    }

    void accept(ASTVisitor& visitor) override {
        visitor.visit(*this);
    }

 private:
    ValueKind kind_;
    llvm::StringRef val_;
};


class BinaryOp : public Expr {
 public:
    enum Operator { Plus, Minus, Mul, Div };

 public:
    BinaryOp(Operator op, Expr* left, Expr* right):
        op_(op), left_(left), right_(right) {}

    Expr* GetLeft() {
        return left_;
    }

    Expr* GetRight() {
        return right_;
    }

    Operator GetOperator() {
        return op_;
    }

    void accept(ASTVisitor& visitor) override {
        visitor.visit(*this);
    }

 private:
    Operator op_;
    Expr* left_;
    Expr* right_;
};


class WithDecl : public AST {
    using VarVector = llvm::SmallVector<llvm::StringRef, 8>;

 public:
    WithDecl(VarVector& vars, Expr* expr):
        vars_(vars), expr_(expr) {}

    Expr* GetExpr() {
        return expr_;;
    }

    VarVector::const_iterator begin() {
        return vars_.begin();
    }

    VarVector::const_iterator end() {
        return vars_.end();
    }

    void accept(ASTVisitor& visitor) override {
        visitor.visit(*this);
    }


 private:
    VarVector vars_;
    Expr*     expr_;
};
}  // namespace tinylang
