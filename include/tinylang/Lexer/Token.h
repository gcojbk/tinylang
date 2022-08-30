#pragma once

#include <cstddef>
#include <llvm/ADT/StringRef.h>
#include <llvm/Support/SMLoc.h>
#include "tinylang/Basic/TokenKinds.h"

namespace tinylang {
class Lexer;

class Token {
    friend class Lexer;

 public:
    const char* GetText() const {
        return ptr_;
    }

    tok::TokenKind GetKind() const {
        return kind_;
    }

    size_t GetLength() const {
        return length_;
    }

    llvm::SMLoc GetLocation() const {
        return llvm::SMLoc::getFromPointer(ptr_);
    }

    llvm::StringRef GetIdentifier() const {
        assert(Is(tok::identifier) && "Cannot get identifier from non-identifier");
        return llvm::StringRef(ptr_, length_);
    }

    llvm::StringRef GetLiteralData() const {
        assert(Is(tok::integer_literal) && "Cannot get literal data from non-literal");
        return llvm::StringRef(ptr_, length_);
    }

    bool Is(tok::TokenKind kind) const {
        return kind_ == kind;
    }

    bool IsOneOf(tok::TokenKind k1, tok::TokenKind k2) const {
        return Is(k1) || Is(k2);
    }

    template<typename... Ts>
    bool IsOneOf(tok::TokenKind k1, tok::TokenKind k2, Ts... ks) const {
        return Is(k1) || IsOneOf(k2, ks...);
    }

 private:
    const char* ptr_;
    size_t length_;
    tok::TokenKind kind_;
};
}  // namespace tinylang
