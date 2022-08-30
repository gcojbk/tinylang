#pragma once

#include <vector>
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/SMLoc.h"
#include "tinylang/Lexer/Token.h"

namespace tinylang {
class AST;
class Decl;
class ModuleDecl;
class ConstantDecl;
class TypeDecl;
class VariableDecl;
class FormalParameterDecl;
class ProcedureDecl;
class Stmt;
class Expr;

using DeclList = std::vector<Decl*>;
using StmtList = std::vector<Stmt*>;
using ExprList = std::vector<Expr*>;

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

class Decl : public AST {
 public:
    enum DeclKind {
        DK_Module,
        DK_Const,
        DK_Type,
        DK_Var,
        DK_Param,
    };

 public:
    Decl(DeclKind kind, llvm::SMLoc loc, llvm::StringRef name)
        : kind_(kind), loc_(loc), name_(name) {}

 public:
    DeclKind GetKind() {
        return kind_;
    }

    llvm::SMLoc GetLoc() {
        return loc_;
    }

    llvm::StringRef GetName() {
        return name_;
    }

 private:
    DeclKind kind_;

 protected:
    llvm::SMLoc loc_;
    llvm::StringRef name_;
};

class ModuleDecl : public Decl {
 public:
    ModuleDecl(llvm::SMLoc loc, llvm::StringRef name):
        Decl(DK_Module, loc, name) {};

 public:
    const DeclList& GetDecls() {
        return decls_;
    }

    const StmtList& GetStmts() {
        return stmts_;
    }

 private:
    DeclList decls_;
    StmtList stmts_;
};

class ConstantDecl : public Decl {
 public:
    ConstantDecl(llvm::SMLoc loc, llvm::StringRef name, Expr* value):
        Decl(DK_Module, loc, name), value_(value) {};

 public:
    Expr* GetValue() {
        return value_;
    }

 private:
    Expr* value_;
};

class TypeDecl : public Decl {
 public:
    TypeDecl(llvm::SMLoc loc, llvm::StringRef name):
        Decl(DK_Type, loc, name) {};
};

class VariableDecl : public Decl {
 public:
    VariableDecl(llvm::SMLoc loc, llvm::StringRef name, TypeDecl* type):
        Decl(DK_Var, loc, name), type_(type) {};

 public:
    TypeDecl* GetType() {
        return type_;
    }

 private:
    TypeDecl* type_;
};

class FormalParameterDecl : public Decl {
 public:
    FormalParameterDecl(llvm::SMLoc loc, llvm::StringRef name, TypeDecl* type, bool is_var):
        Decl(DK_Param, loc, name), type_(type), is_val_(is_var) {};

 public:
    TypeDecl* GetType() {
        return type_;
    }

    bool IsVar() {
        return is_val_;
    }

 private:
    TypeDecl* type_;
    bool is_val_;
};

class ProcedureDecl : public Decl {
 public:
    ProcedureDecl(llvm::SMLoc loc, llvm::StringRef name):
        Decl(DK_Param, loc, name) {};

 public:
    std::vector<FormalParameterDecl*> GetFormalParams() {
        return formal_params_;
    }

    TypeDecl* GetType() {
        return type_;
    }

    const DeclList& GetDecls() {
        return decls_;
    }

    const StmtList& GetStmts() {
        return stmts_;
    }

 private:
    std::vector<FormalParameterDecl*> formal_params_;
    TypeDecl* type_;
    DeclList decls_;
    StmtList stmts_;
};

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
}  // namespace tinylang
