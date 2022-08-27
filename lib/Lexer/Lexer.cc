#include <llvm/Support/Compiler.h>
#include "tinylang/Lexer/Lexer.h"

namespace charinfo {
LLVM_READNONE inline bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\f' ||
           c == '\v' || c == '\r' || c == '\n';
}

LLVM_READNONE inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

LLVM_READNONE inline bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}
}  // namespace charinfo

namespace tinylang {
void Lexer::Next(Token &token) {
    while (*buffer_ptr_ && (charinfo::isWhitespace(*buffer_ptr_))) {
        ++buffer_ptr_;
    }

    if (*buffer_ptr_ == EOF) {
        token.kind_ = tok::eof;
        return;
    }

    if (!*buffer_ptr_) {
        token.kind_ = tok::unknown;
        return;
    }

    if (charinfo::isLetter(*buffer_ptr_)) {
        const char* end = buffer_ptr_ + 1;
        while (charinfo::isLetter(*end)) {
            end++;
        }
        llvm::StringRef name(buffer_ptr_, end - buffer_ptr_);
        tok::TokenKind kind = keyword_filter_.GetKeyword(name);
        if (kind == tok::unknown) {
            FormTokenWithChars(token, end, tok::identifier);
        } else {
            FormToken(token, end, kind);
        }
    } else if (charinfo::isDigit(*buffer_ptr_)) {
        const char* end = buffer_ptr_ + 1;
        while (charinfo::isDigit(*end)) {
            end++;
        }
        FormTokenWithChars(token, end, tok::integer_literal);
    } else {
        switch (*buffer_ptr_) {
#define CASE(P, TOK) case P: FormTokenWithChars(token, buffer_ptr_ + 1, TOK); break
            CASE('+', tok::plus);
            CASE('-', tok::minus);
            CASE('*', tok::star);
            CASE('/', tok::slash);
#undef  CASE
            case '<': {
                if (*(buffer_ptr_ + 1) == '=') {
                    FormTokenWithChars(token, buffer_ptr_ + 2, tok::less_equal);
                } else {
                    FormTokenWithChars(token, buffer_ptr_ + 1, tok::less);
                }
                break;
            }
            case '>': {
                if (*(buffer_ptr_ + 1) == '=') {
                    FormTokenWithChars(token, buffer_ptr_ + 2, tok::greater_equal);
                } else {
                    FormTokenWithChars(token, buffer_ptr_ + 1, tok::greater);
                }
                break;
            }
            default:
                FormTokenWithChars(token, buffer_ptr_ + 1, tok::unknown);
                break;
        }
    }
    return;
}

void Lexer::FormToken(Token& token, const char* tokEnd, tok::TokenKind kind) {
    token.kind_ = kind;
    buffer_ptr_ = tokEnd;
}

void Lexer::FormTokenWithChars(Token& token, const char* tokEnd, tok::TokenKind kind) {
    token.kind_ = kind;
    token.length_ = tokEnd - buffer_ptr_;
    buffer_ptr_ = tokEnd;
}
}  // namespace tinylang