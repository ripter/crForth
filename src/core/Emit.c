#include "../crForth.h"

// ( x -- )
// Prints X to the STDOUT.
void Emit(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t tos = PopFromCellStack(&state->dataStack);
  printf("%c", (char)tos);
}
