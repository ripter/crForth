#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( n -- )
// If n is greater than zero, reserve n address units of data space. 
// If n is less than zero, release | n | address units of data space. 
// If n is zero, leave the data-space pointer unchanged.
// https://forth-standard.org/standard/core/ALLOT
void Allot(KernelState* state) {
  // Attempt to get the address of the HERE temporary buffer.
  ForthWord *here = GetItemFromDictionary(&state->dict, TEMP_BUFFER_NAME);
  if (here == NULL) {
    // Create the buffer word.
    if (!AddWordToDictionary(&state->dict, CreateForthWord(TEMP_BUFFER_NAME, (xt_func_ptr)Variable, false, NULL))) {
      fprintf(state->errorStream, "Error: Unable to allot HERE buffer.\n");
      return;
    }
    // Get the new buffer.
    here = GetItemFromDictionary(&state->dict, TEMP_BUFFER_NAME);
  }
  // Get the value on the stack.
  Cell n = CellStackPop(&state->dataStack);
  if (n.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "Error: ALLOT expected a number on the stack.\n");
    return;
  }
  // Validate the new size.
  size_t newSize = GetStringBufferLength(here->data) + n.value;
  if (newSize < 0) {
    fprintf(state->errorStream, "Error: \"%ld ALLOT\" would result in the negative buffer size %ld.\n", n.value, newSize);
    return;
  }
  SetStringBufferLength(here->data, newSize);
  // // Is this new Alloc or ReAlloc?
  // if (here->dataBufferLength == 0) {
  //   here->data = MemAlloc(newSize);
  // } else {
  //   MemRealloc(here->data, newSize);
  // }
  // Check if the memory allocation was successful.
  // and update the buffer length.
  // if (here->data == NULL) {
  //   here->dataBufferLength = 0;
  //   fprintf(state->errorStream, "Error: Unable to change alloted memory from %ld to %ld.\n", here->dataBufferLength, newSize);
  // } else {
  //   here->dataBufferLength = newSize;
  //   // printf("Allocated %ld bytes of memory.\n", n.value);
  // }
}
