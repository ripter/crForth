#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"
#include "../WordMetadata.h"

void Subtract(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  cell_t b = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, b - a);
}
