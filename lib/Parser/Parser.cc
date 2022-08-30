#include "tinylang/Parser/Parser.h"

namespace tinylang {
AST *Parser::Parse() {
    Expect(tok::eof);
    return nullptr;
}

Expr *Parser::ParseExpr() {
    Expr* left = ParseTerm();
    while (token_.IsOneOf(tok::plus, tok::minus)) {
        auto op = token_.Is(tok::plus) ? BinaryOp::Plus : BinaryOp::Minus;
        Advance();
        Expr* right = ParseTerm();
        left = new BinaryOp(op, left, right);
    }
    return left;
}

Expr *Parser::ParseTerm() {
    Expr* left = ParseFactor();
    while (token_.IsOneOf(tok::star, tok::slash)) {
        auto op = token_.Is(tok::star) ? BinaryOp::Mul : BinaryOp::Div;
        Advance();
        Expr* right = ParseFactor();
        left = new BinaryOp(op, left, right);
    }
    return left;
}

Expr *Parser::ParseFactor() {
    Expr* res = nullptr;
    switch (token_.GetKind()) {
        case tok::identifier:
            res  = new Factor(Factor::Ident, token_.GetText());
            Advance();
            break;
        case tok::integer_literal:
            res  = new Factor(Factor::Number, token_.GetText());
            Advance();
            break;
        case tok::l_paren: {
            Advance();
            res = ParseExpr();
            if (Consume(tok::r_paren)) {
                break;
            }
            [[fallthrough]];
        }
        default: {
            if (!res) {
                Error();
            }
            /// TODO: error handling
            break;
        }
    }
    return res;
}
}  // namespace tinylang
