#include "raylib.h"
#include "../crForth.h"

// ( a b -- b a )
// Swaps the top two items on the stack.
// https://forth-standard.org/standard/core/SWAP
void Swap(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = PopFromCellStack(&state->dataStack);
  Cell b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, (Cell){a.value, CELL_TYPE_NUMBER});
  PushToCellStack(&state->dataStack, (Cell){b.value, CELL_TYPE_NUMBER});
}
