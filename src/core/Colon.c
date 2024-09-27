#include <stdio.h>
#include "../crForth.h"

void Colon(KernelState *state, WordMetadata *wordMeta) {
  // First time : is called, we need to consume the next word to get the name of the new word.
  // So push Colon back onto the return stack and return NULL.
  if (wordMeta == NULL) {
    PushToCellStack(&state->returnStack, (cell_t)Colon);
    return;
  }

  // Second time : is called, we need to consume the next word to get the name of the new word.
  printf("TODO: Add new word to Dictionary: %s\n", wordMeta->name);
  // Start Compile Mode
  state->IsInCompileMode = true;
}
