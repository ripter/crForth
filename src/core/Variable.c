#include <stdio.h>
#include "../crForth.h"

// ( -- c-addr )
// Represents a variable in the dictionary.
// Treats the wordMeta->data as a pointer to a cell_t
void Variable(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // UNUSED
  PushToCellStack(&state->dataStack, (cell_t)&wordMeta->data);
}
