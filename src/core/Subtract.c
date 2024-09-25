#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"

char* Subtract(KernelState* state, char* word) {
  (void)word; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  cell_t b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, b - a);
  return NULL;
}
