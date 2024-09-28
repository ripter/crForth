#include <stdio.h>
#include "../crForth.h"

void Dot(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t a = PopFromCellStack(&state->dataStack);
  printf("%ld \n", a);
}
