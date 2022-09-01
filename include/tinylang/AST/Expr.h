#pragma once

#include "tinylang/AST/AST.h"

namespace tinylang {
class Expr;

class OperatorInfo {
 public:
    OperatorInfo()
        : loc_(), kind_(tok::unknown) {}
    OperatorInfo(llvm::SMLoc loc, tok::TokenKind kind)
        : loc_(loc), kind_(kind) {}

 public:
    llvm::SMLoc GetLoc() {
        return loc_;
    }

    tok::TokenKind GetKind() {
        return static_cast<tok::TokenKind>(kind_);
    }

 private:
    llvm::SMLoc loc_;
    std::uint32_t kind_;
};

class Expr : public AST {
 public:
    enum ExprKind {
        EK_Infix,
        EK_Prefix,
        EK_Int,
        EK_Bool,
        EK_Var,
        EK_Const,
        EK_Func,
    };

 public:
    Expr(ExprKind kind, TypeDecl* type)
        : kind_(kind), type_(type) {}

    ExprKind GetKind() {
        return kind_;
    }

    TypeDecl* GetType() {
        return type_;
    }

 private:
    ExprKind kind_;
    TypeDecl* type_;
};

class InfixExpr : public Expr {
 public:
    InfixExpr(Expr* left, Expr* right, OperatorInfo op, TypeDecl* type)
        : Expr(EK_Infix, type), left_(left), right_(right), op_(op) {}

 public:
    Expr* GetLeft() {
        return left_;
    }

    Expr* GetRight() {
        return right_;
    }

    const OperatorInfo& GetOperatorInfo() {
        return op_;
    }

 private:
    Expr* left_;
    Expr* right_;
    OperatorInfo op_;
};

class PrefixExpr : public Expr {
 public:
    PrefixExpr(Expr* expr, OperatorInfo op, TypeDecl* type)
        : Expr(EK_Prefix, type), expr_(expr), op_(op) {}

 public:
    Expr* GetExpr() {
        return expr_;
    }

    const OperatorInfo& GetOperatorInfo() {
        return op_;
    }

 private:
    Expr* expr_;
    OperatorInfo op_;
};

class IntLiteral : public Expr {
 public:
    IntLiteral(int val, TypeDecl* type) : Expr(EK_Int, type), val_(val) {}

 public:
    int GetIntVal() {
        return val_;
    }

 private:
    int val_;

};


class StringLiteral : public Expr {


};
}  // namespace tinylang
