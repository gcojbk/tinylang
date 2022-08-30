#pragma once

#include "tinylang/AST/AST.h"
#include "tinylang/Lexer/Lexer.h"
#include "llvm/Support/raw_ostream.h"

namespace tinylang {
class Parser {
 public:
    Parser(Lexer& lexer): lexer_(lexer), has_error_(false) {
        Advance();
    }

    bool HasError() const {
        return has_error_;
    }

    AST *Parse();

  private:
    void Error() {
        llvm::errs() << "Error: unexpected " << token_.GetText() << '\n';
        has_error_ = true;
    }

    void Advance() {
        lexer_.Next(token_);
    }

    bool Expect(tok::TokenKind kind) {
        if (token_.GetKind() != kind) {
            Error();
            return false;
        }
        return true;
    }

    bool Consume(tok::TokenKind kind) {
        if (!Expect(kind)) {
            return false;
        }
        Advance();
        return true;
    }

 private:
   Expr *ParseExpr();
   Expr *ParseTerm();
   Expr *ParseFactor();

 private:
    Lexer& lexer_;
    Token token_;
    bool  has_error_;
};
}  // namespace tinylang
