#include "tinylang/Basic/Diagnostic.h"

using namespace tinylang;

namespace {

    const char* DiagnosticText[] = {
#define DIAG(ID, LEVEL, MSG) MSG,
#include "tinylang/Basic/Diagnostic.def"
#undef DIAG
    };

    llvm::SourceMgr::DiagKind DiagnosticKind[] = {
#define DIAG(ID, LEVEL, MSG) llvm::SourceMgr::DK_##LEVEL
#include "tinylang/Basic/Diagnostic.def"
#undef DIAG
    };
}  // namespace

const char*
diag::DiagnosticEngine::GetDiagnosticText(unsigned diag_id) {
    return DiagnosticText[diag_id];
}

llvm::SourceMgr::DiagKind
diag::DiagnosticEngine::GetDiagnosticKind(unsigned diag_id) {
    return DiagnosticKind[diag_id];
}

