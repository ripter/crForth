#include "../crForth.h"

// ( x -- )
// Prints X to the STDOUT.
void Emit(KernelState* state, ForthWord* wordMeta) {
  (void)wordMeta; // UNUSED
  Cell tos = CellStackPop(&state->dataStack);
  printf("%c", (char)tos.value);
}
