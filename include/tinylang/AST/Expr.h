#pragma once

#include "tinylang/AST/AST.h"
#include "tinylang/AST/Decl.h"

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
        EK_String,
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

class IntegerLiteral : public Expr {
 public:
    IntegerLiteral(llvm::SMLoc loc, llvm::APSInt& val, TypeDecl* type)
        : Expr(EK_Int, type), loc_(loc), val_(val) {}

 public:
    llvm::APSInt GetValue() {
        return val_;
    }

 private:
    llvm::SMLoc loc_;
    llvm::APSInt val_;
};

class BooleanLiteral : public Expr {
 public:
    BooleanLiteral(bool val, TypeDecl* type)
        : Expr(EK_Bool, type), val_(val) {}

 public:
    bool GetValue() {
        return val_;
    }

 private:
    bool val_;
};

class StringLiteral : public Expr {
 public:
    StringLiteral(llvm::SMLoc loc, llvm::StringRef& val, TypeDecl* type)
        : Expr(EK_String, type), loc_(loc), val_(val) {}

 public:
    llvm::StringRef GetValue() {
        return val_;
    }

 private:
    llvm::SMLoc loc_;
    llvm::StringRef val_;
};

class VariableAccess : public Expr {
 public:
    explicit VariableAccess(VariableDecl* var)
        : Expr(EK_Var, var->GetType()), var_(var) {}
    explicit VariableAccess(FormalParameterDecl* var)
        : Expr(EK_Var, var->GetType()), var_(var) {}

 public:
    Decl* GetDecl() {
        return var_;
    }

 private:
    Decl* var_;
};
}  // namespace tinylang
