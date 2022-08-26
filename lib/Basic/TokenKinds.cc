#include "tinylang/Basic/TokenKinds.h"
#include "llvm/Support/ErrorHandling.h"

using namespace tinylang;

static const char* const TokenNames[] = {
#define TOK(ID) #ID,
#define KEYWORD(ID, FLAG) #ID,
#include "tinylang/Basic/TokenKinds.def"
    nullptr,
};

const char* tok::GetTokenName(TokenKind kind) {
    return TokenNames[kind];
}

const char* tok::GetPunctuatorSpelling(TokenKind kind) {
    switch (kind) {
#define PUNCTUATOR(ID, SP) case ID: return SP;
#include "tinylang/Basic/TokenKinds.def"
        default:
            break;
    }
    return nullptr;
}

const char* tok::GetKeywordSpelling(TokenKind kind) {
    switch (kind) {
#define KEYWORD(ID, FLAG) case kw_##ID: return #ID;
#include "tinylang/Basic/TokenKinds.def"
        default:
            break;
    }
    return nullptr;
}
