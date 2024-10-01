#include <stdio.h>
#include "../crForth.h"

// ( -- )
// Stops Compile Mode
void SemiColon(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused
  // Stop Compile Mode
  state->IsInCompileMode = false;
}
