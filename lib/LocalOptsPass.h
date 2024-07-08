//===-- LocalOpts.h - Example Transformations ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This header provides the declaration of local optimization functions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_LOCALOPTS_H
#define LLVM_TRANSFORMS_UTILS_LOCALOPTS_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class FunctionPass;

class LocalOptsPass : public PassInfoMixin<LocalOptsPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // end namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_LOCALOPTS_H