#include "raylib.h"
#include "../crForth.h"

// ( -- c-addr u )
// Pushes the branch name and length to the stack.
// https://forth-standard.org/standard/core/HERE
void Here(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  PushToCellStack(&state->dataStack, (Cell){(cell_t)state->branchBuffer, CELL_TYPE_WORD});
  PushToCellStack(&state->dataStack, (Cell){TextLength(state->branchBuffer), CELL_TYPE_NUMBER});
}
