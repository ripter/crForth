#include "raylib.h"
#include "../crForth.h"

// ( x -- ) ( R: -- x )
// Move x to the return stack.
// https://forth-standard.org/standard/core/toR
void ToR(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->returnStack, a);
}
