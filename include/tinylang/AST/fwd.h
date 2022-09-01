#pragma once

namespace tinylang {
class AST;

/// declaration
class Decl;
class ModuleDecl;
class ConstantDecl;
class TypeDecl;
class VariableDecl;
class FormalParameterDecl;
class ProcedureDecl;

/// expression
class Expr;
class InfixExpr;
class PrefixExpr;
class IntLiteral;
class StringLiteral;

/// statement
class Stmt;
class AssignmentStmt;
class IfStmt;
}  // namespace tinylang
