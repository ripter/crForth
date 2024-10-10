#include "../crForth.h"

// ( x -- x x ) 
// Duplicates the top item on the stack.
// https://forth-standard.org/standard/core/DUP
void Dup(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  Cell topItem = CellStackPop(&state->dataStack);
  // Duplicate the top item and push it back to the stack.
  CellStackPush(&state->dataStack, (Cell){topItem.value, topItem.type});
  CellStackPush(&state->dataStack, (Cell){topItem.value, topItem.type});
}
