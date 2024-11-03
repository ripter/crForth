#include "../crForth.h"

// ( x -- )
// Prints X to the STDOUT.
// https://forth-standard.org/standard/core/EMIT
void Emit(KernelState* state) {
  Cell tos = CellStackPop(&state->dataStack);
  fprintf(state->outputStream, "%c", (char)tos.value);
}
