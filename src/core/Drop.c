#include "../crForth.h"

// ( x -- ) 
// Drops the top item from the stack.
// https://forth-standard.org/standard/core/DROP
void Drop(KernelState *state) {
  (void)CellStackPop(&state->dataStack);
}
