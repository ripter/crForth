#include "../crForth.h"

void Here(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  (void)state; // Unused parameter
  // PushToCellStack(&state->dataStack, (cell_t)state->dict.nextWord);
  printf("Here: %s\n", wordMeta->name);
}
