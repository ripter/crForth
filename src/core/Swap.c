#include "raylib.h"
#include "../crForth.h"

// ( a b -- b a )
// Swaps the top two items on the stack.
// https://forth-standard.org/standard/core/SWAP
void Swap(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  cell_t b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, a);
  PushToCellStack(&state->dataStack, b);
}
