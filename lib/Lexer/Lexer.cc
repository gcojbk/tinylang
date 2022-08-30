#include <llvm/Support/Compiler.h>
#include "tinylang/Lexer/Lexer.h"

namespace charinfo {
LLVM_READNONE inline bool isASCII(char c) {
    return static_cast<unsigned char>(c) <= 127;
}

LLVM_READNONE inline bool isVerticalWhitespace(char c) {
    return isASCII(c) && (c == '\r' || c == '\n');
}

LLVM_READNONE inline bool isHorizontalWhitespace(char c) {
    return isASCII(c) && (c == ' ' || c == '\t' ||
                          c == '\f' || c == '\v');
}

LLVM_READNONE inline bool isWhitespace(char c) {
    return isHorizontalWhitespace(c) ||
           isVerticalWhitespace(c);
}

LLVM_READNONE inline bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

LLVM_READNONE inline bool isHexDigit(char c) {
    return isASCII(c) &&
           (isDigit(c) || (c >= 'A' && c <= 'F'));
}

LLVM_READNONE inline bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

LLVM_READNONE inline bool isIdentifierHead(char c) {
    return isLetter(c) || c == '_';
}

LLVM_READNONE inline bool isIdentifierBody(char c) {
    return isIdentifierHead(c) || isDigit(c);
}
}  // namespace charinfo

namespace tinylang {
void KeywordFilter::AddKeyword(llvm::StringRef keyword,
                               tok::TokenKind token_code) {
    keyword_table_.insert({keyword, token_code});
}

void KeywordFilter::AddKeyWords() {
#define KEYWORDS(NAME, FLAGS)                                                  \
    AddKeyword(llvm::StringRef(#NAME), tok::kw_##NAME);
#include "tinylang/Basic/TokenKinds.def"
#undef KEYWORDS
}

void Lexer::Next(Token &token) {
    while (*buffer_ptr_ && (charinfo::isWhitespace(*buffer_ptr_))) {
        ++buffer_ptr_;
    }

    if (*buffer_ptr_ == EOF || !*buffer_ptr_) {
        token.kind_ = tok::eof;
        return;
    }

    if (charinfo::isIdentifierHead(*buffer_ptr_)) {
        Identifier(token);
        return;
    } else if (charinfo::isDigit(*buffer_ptr_)) {
        Number(token);
        return;
    } else if (*buffer_ptr_ == '"') {
        String(token);
        return;
    } else {
        switch (*buffer_ptr_) {
#define CASE(P, TOK) case P: FormToken(token, buffer_ptr_ + 1, TOK); break
            CASE('=', tok::equal);
            CASE('+', tok::plus);
            CASE('-', tok::minus);
            CASE('*', tok::star);
            CASE('/', tok::slash);
            CASE(',', tok::comma);
            CASE(';', tok::semi);
            CASE('.', tok::period);
            CASE('(', tok::l_paren);
            CASE(')', tok::r_paren);
#undef  CASE
            case ':': {
                if (*(buffer_ptr_ + 1) == '=') {
                    FormToken(token, buffer_ptr_ + 2, tok::colon_equal);
                } else {
                    FormToken(token, buffer_ptr_ + 1, tok::colon);
                }
                break;
            }
            case '<': {
                if (*(buffer_ptr_ + 1) == '=') {
                    FormToken(token, buffer_ptr_ + 2, tok::less_equal);
                } else {
                    FormToken(token, buffer_ptr_ + 1, tok::less);
                }
                break;
            }
            case '>': {
                if (*(buffer_ptr_ + 1) == '=') {
                    FormToken(token, buffer_ptr_ + 2, tok::greater_equal);
                } else {
                    FormToken(token, buffer_ptr_ + 1, tok::greater);
                }
                break;
            }
            default:
                FormToken(token, buffer_ptr_ + 1, tok::unknown);
                break;
        }
    }
    return;
}

void Lexer::Identifier(Token& token) {
    const char* end = buffer_ptr_ + 1;
    while (charinfo::isIdentifierBody(*end)) {
        end++;
    }
    llvm::StringRef name(buffer_ptr_, end - buffer_ptr_);
    tok::TokenKind kind = keyword_filter_.GetKeyword(name);
    if (kind == tok::unknown) {
        FormToken(token, end, tok::identifier);
    } else {
        FormToken(token, end, kind);
    }
}

void Lexer::Number(Token& token) {
    /// TODO: support hex num.
    const char* end = buffer_ptr_ + 1;
    while (charinfo::isDigit(*end)) {
        end++;
    }
    FormToken(token, end, tok::integer_literal);
}

void Lexer::String(Token& token) {
    const char* end = buffer_ptr_ + 1;
    while (*end && *end != '"') {
        end++;
    }
    FormToken(token, end + 1, tok::string_literal);
}

void Lexer::Comment(Token& token) {
    /// TODO: support comment parser
}

void Lexer::FormToken(Token& token, const char* tokEnd, tok::TokenKind kind) {
    token.kind_ = kind;
    token.ptr_ = buffer_ptr_;
    token.length_ = tokEnd - buffer_ptr_;
    buffer_ptr_ = tokEnd;
}
} // namespace tinylang
