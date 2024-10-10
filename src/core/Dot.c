#include <stdio.h>
#include "../crForth.h"

// ( a -- )
// Print the top of the stack.
void Dot(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  Cell a = CellStackPop(&state->dataStack);
  printf("%ld \n", a.value);
}
