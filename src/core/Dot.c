#include <stdio.h>
#include "../crForth.h"

// ( a -- )
// Prints the top of stack to outputStream
void Dot(KernelState* state) {
  Cell a = CellStackPop(&state->dataStack);
  // If there is nothing on the stack, return
  if (a.type == CELL_TYPE_EMPTY) {
    return;
  } 
  fprintf(state->outputStream, "%ld ", a.value);
}
