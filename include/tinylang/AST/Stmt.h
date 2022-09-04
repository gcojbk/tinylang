#pragma once

#include "tinylang/AST/AST.h"

namespace tinylang {
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

class ProcedureCallStmt : public Stmt {
 public:
    ProcedureCallStmt(ProcedureDecl* decl, ExprList& params)
        : Stmt(SK_ProcCall), proc_(decl), params_(params) {}

    ProcedureDecl* GetDecl() {
        return proc_;
    }

    const ExprList& GetParams() {
        return params_;
    }

 private:
    ProcedureDecl* proc_;
    ExprList params_;
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

class ReturnStmt : public Stmt {
 public:
    ReturnStmt(Expr* ret_val)
        : Stmt(SK_Return), ret_val_(ret_val) {}

 public:
    Expr* GetRetVal() {
        return ret_val_;
    }

 private:
    Expr* ret_val_;
};
}  // namespace tinylang
