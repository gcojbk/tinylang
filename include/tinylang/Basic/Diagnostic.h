#pragma once

// #include "tinylang/Basic/LLVM.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/SMLoc.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <utility>

namespace tinylang {
namespace diag {

enum {
    #define DIAG(ID, Level, Msg) ID,
    #include "tinylang/Basic/Diagnostic.def"
};

class DiagnosticEngine {
 public:
    DiagnosticEngine(llvm::SourceMgr& src_mgr):
        src_mgr_(src_mgr), num_errors_(0) {}

    unsigned NumErrors() {
        return num_errors_;
    }

    template <typename... Args>
    void Report(llvm::SMLoc loc, unsigned diag_id, Args&&... args) {
        std::string msg = llvm::formatv(GetDiagnosticText(diag_id), std::forward<Args>(args)...);
        auto kind = GetDiagnosticKind(diag_id);
        src_mgr_.PrintMessage(loc, kind, msg);
        if (kind == llvm::SourceMgr::DK_Error) {
            num_errors_++;
        }
    }

 private:
    static const char* GetDiagnosticText(unsigned diag_id);
    static llvm::SourceMgr::DiagKind GetDiagnosticKind(unsigned diag_id);

 private:
    llvm::SourceMgr& src_mgr_;
    unsigned num_errors_;
};

}  // namespace diag
}  // namespace tinylang
