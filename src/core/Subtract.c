#include <stdio.h>
#include "../crForth.h"

// ( a b -- c )
// Subtracts two numbers from the stack and pushes the result back to the stack.
void Subtract(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  cell_t b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, b - a);
}
