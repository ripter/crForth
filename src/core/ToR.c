#include "raylib.h"
#include "../crForth.h"

// ( x -- ) ( R: -- x )
// Move x to the return stack.
// https://forth-standard.org/standard/core/toR
void ToR(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->returnStack, (Cell){a.value, CELL_TYPE_NUMBER});
}
