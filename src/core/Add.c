#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"

char* Add(KernelState* state, char* word) {
  (void)word; // UNUSED
  cell_t a = PopCellStack(&state->dataStack);
  cell_t b = PopCellStack(&state->dataStack);
  PushCellStack(&state->dataStack, a + b);
  return NULL;
}
