#include "../crForth.h"

// ( x -- ) 
// Drops the top item from the stack.
// https://forth-standard.org/standard/core/DROP
void Drop(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  (void)PopFromCellStack(&state->dataStack);
}
