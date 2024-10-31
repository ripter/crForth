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
  // printf("\n%ld ALLOT\n", n.value);
  if (n.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "Error: ALLOT expected a number on the stack.\n");
    return;
  }
  // Validate the new size.
  size_t currentSize = GetStringBufferLength(state->compilePtr);
  size_t newSize = currentSize + n.value;
  // printf("\n\tcurrentSize: %ld\n", currentSize);
  // printf("\n\tnewSize: %ld\n", newSize);
  if (newSize < 0) {
    fprintf(state->errorStream, "Error: \"%ld ALLOT\" would result in the negative buffer size %ld.\n", n.value, newSize);
    return;
  }
  // printf("\n\t0x%lx from %ld to %ld\n", (cell_t)state->compilePtr->s, currentSize, newSize);
  SetStringBufferLength(state->compilePtr, newSize);
}
