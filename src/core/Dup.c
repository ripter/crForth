#include "../crForth.h"

// ( x -- x x ) 
// Duplicates the top item on the stack.
// https://forth-standard.org/standard/core/DUP
void Dup(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  cell_t topItem = PopFromCellStack(&state->dataStack);
  // Duplicate the top item and push it back to the stack.
  PushToCellStack(&state->dataStack, topItem);
  PushToCellStack(&state->dataStack, topItem);
}
