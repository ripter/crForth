#include <stdio.h>
#include "../KernelState.h"

void Add(KernelState* state) {
  cell_t a = PopCellStack(&state->dataStack);
  cell_t b = PopCellStack(&state->dataStack);
  PushCellStack(&state->dataStack, a + b);
}
