#include <stdio.h>
#include "../crForth.h"

void SemiColon(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused
  // Stop Compile Mode
  state->IsInCompileMode = false;
}
