#pragma once

#include "tinylang/Lexer/Token.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/MemoryBuffer.h"
#include <llvm/ADT/StringMap.h>

namespace tinylang {
class KeywordFilter {
 public:
    void AddKeyword(llvm::StringRef keyword, tok::TokenKind token_code) {
        keyword_table_.insert({keyword, token_code});
    }

    void AddKeyWords() {
#define KEYWORDS(NAME, FLAGS) AddKeyword(llvm::StringRef(#NAME), tok::kw_##NAME);
#include "tinylang/Basic/TokenKinds.def"
#undef  KEYWORDS
    }

    tok::TokenKind GetKeyword(llvm::StringRef name,
                        tok::TokenKind default_token_code = tok::TokenKind::unknown) {
        auto ret = default_token_code;
        auto findit = keyword_table_.find(name);
        if (findit != keyword_table_.end()) {
            ret = findit->second;
        }
        return ret;
    }

 private:
    llvm::StringMap<tok::TokenKind> keyword_table_;
};

class Lexer {
 public:
    Lexer(const llvm::StringRef& buffer) {
        buffer_start_ = buffer.begin();
        buffer_ptr_ = buffer_start_;
        keyword_filter_.AddKeyWords();
    }

    void Next(Token& token);

 private:
    void FormToken(Token& token, const char* tokEnd, tok::TokenKind kind);
    void FormTokenWithChars(Token& token, const char* tokEnd, tok::TokenKind kind);

 private:
    const char* buffer_start_;
    const char* buffer_ptr_;
    KeywordFilter keyword_filter_;
};
}  // namespace tinylang