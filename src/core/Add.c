#include <stdio.h>

#include "../crForth.h"

// ( a b -- c )
// Adds two numbers from the stack and pushes the result back to the stack.
void Add(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = PopFromCellStack(&state->dataStack);
  Cell b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, (Cell){a.value + b.value, a.type});
}
