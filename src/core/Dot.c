#include <stdio.h>
#include "../crForth.h"

// ( a -- )
// Prints the top of stack to outputStream
void Dot(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = CellStackPop(&state->dataStack);
  fprintf(state->outputStream, "%ld ", a.value);
}
