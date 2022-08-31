#pragma once

#include "tinylang/AST/AST.h"

namespace tinylang {
class Stmt;

class Stmt : public AST {
 public:
    enum StmtKind {
        SK_Assign,
        SK_ProcCall,
        SK_If,
        SK_While,
        SK_Return,
    };

 protected:
    Stmt(StmtKind kind): kind_(kind) {}

 public:
    StmtKind GetKind() {
        return kind_;
    }

 private:
    StmtKind kind_;
};

class AssignmentStmt : public Stmt {
 public:
    AssignmentStmt(VariableDecl* var, Expr* expr)
        : Stmt(SK_Assign), var_(var), expr_(expr) {}

    VariableDecl* GetVar() {
        return var_;
    }

    Expr* GetExpr() {
        return expr_;
    }

 private:
    VariableDecl* var_;
    Expr* expr_;
};

class IfStmt : public Stmt {
 public:
    IfStmt(Expr* condition, StmtList& if_stmts, StmtList& else_stmts)
        : Stmt(SK_If), condition_(condition), if_stmts_(if_stmts), else_stmts_(else_stmts) {}

 public:
    Expr* GetCond() {
        return condition_;
    }

    const StmtList& GetIfStmts() {
        return if_stmts_;
    }

    const StmtList& GetElseStmts() {
        return else_stmts_;
    }

 private:
    Expr* condition_;
    StmtList if_stmts_;
    StmtList else_stmts_;
};

}  // namespace tinylang
