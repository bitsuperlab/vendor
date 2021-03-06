#include "src/v8.h"

#if V8_TARGET_ARCH_MIPS

// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if V8_TARGET_ARCH_MIPS

#include "src/assembler.h"
#include "src/frames.h"
#include "src/mips/assembler-mips-inl.h"
#include "src/mips/assembler-mips.h"
#include "src/mips/frames-mips.h"

namespace v8 {
namespace internal {


Register JavaScriptFrame::fp_register() { return v8::internal::fp; }
Register JavaScriptFrame::context_register() { return cp; }
Register JavaScriptFrame::constant_pool_pointer_register() {
  UNREACHABLE();
  return no_reg;
}


Register StubFailureTrampolineFrame::fp_register() { return v8::internal::fp; }
Register StubFailureTrampolineFrame::context_register() { return cp; }
Register StubFailureTrampolineFrame::constant_pool_pointer_register() {
  UNREACHABLE();
  return no_reg;
}


}  // namespace internal
}  // namespace v8

#endif  // V8_TARGET_ARCH_MIPS


#endif  // V8_TARGET_ARCH_MIPS