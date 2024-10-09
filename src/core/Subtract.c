#include <stdio.h>
#include "../crForth.h"

// ( a b -- c )
// Subtracts two numbers from the stack and pushes the result back to the stack.
void Subtract(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = PopFromCellStack(&state->dataStack);
  Cell b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, (Cell){b.value - a.value, CELL_TYPE_NUMBER});
}
