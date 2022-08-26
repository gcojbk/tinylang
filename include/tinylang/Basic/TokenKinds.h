#pragma once

namespace tinylang {
namespace tok {

enum TokenKind : unsigned short {
#define TOK(ID) ID,
#include "tinylang/Basic/TokenKinds.def"
#undef TOK
    NUM_TOKENS,
};

const char* GetTokenName(TokenKind kind);
const char* GetPunctuatorSpelling(TokenKind kind);
const char* GetKeywordSpelling(TokenKind kind);

}  // namespace tok
}  // namespace tinylang
