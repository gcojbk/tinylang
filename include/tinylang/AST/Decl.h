#pragma once

#include "tinylang/AST/AST.h"

namespace tinylang {
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

    TypeDecl* GetRetType() {
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
}  // namespace tinylang
