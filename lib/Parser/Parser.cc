#include "tinylang/Parser/Parser.h"

namespace tinylang {
AST *Parser::Parse() {
    Expect(tok::eof);
    return nullptr;
}
}  // namespace tinylang
