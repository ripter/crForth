#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"
#include "../WordMetadata.h"

void Dot(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  printf("%ld ", a);
}
