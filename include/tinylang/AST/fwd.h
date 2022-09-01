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
class IntegerLiteral;
class BooleanLiteral;
class StringLiteral;
class VariableAccess;

/// statement
class Stmt;
class AssignmentStmt;
class IfStmt;
}  // namespace tinylang
