#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( n -- )
// If n is greater than zero, reserve n address units of data space. 
// If n is less than zero, release | n | address units of data space. 
// If n is zero, leave the data-space pointer unchanged.
// https://forth-standard.org/standard/core/ALLOT
void Allot(KernelState* state) {
  // Get the value on the stack.
  Cell n = CellStackPop(&state->dataStack);
  if (n.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "Error: ALLOT expected a number on the stack.\n");
    return;
  }
  // Validate the new size.
  size_t newSize = GetStringBufferLength(state->compilePtr) + n.value;
  if (newSize < 0) {
    fprintf(state->errorStream, "Error: \"%ld ALLOT\" would result in the negative buffer size %ld.\n", n.value, newSize);
    return;
  }
  SetStringBufferLength(state->compilePtr, newSize);
}
