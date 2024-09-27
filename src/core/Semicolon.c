#include <stdio.h>
#include "../crForth.h"

void SemiColon(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused
  // Stop Compile Mode
  state->IsInCompileMode = false;
  // Save the compiled code to the dictionary
  printf("TODO: Save compiled code to dictionary\n");
}
