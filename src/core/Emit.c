#include "../crForth.h"

// ( x -- )
// Prints X to the STDOUT.
void Emit(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  Cell tos = PopFromCellStack(&state->dataStack);
  printf("%c", (char)tos.value);
}
