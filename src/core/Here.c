#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( -- c-addr u )
// Here returns the address of the next available space in the dictionary.
// It will continue to return the same address until the word is defined with CREATE.
// https://forth-standard.org/standard/core/HERE
void Here(KernelState *state) {
  // Compile pointer gives us the start of the buffer.
  cell_t here = (cell_t)state->compilePtr->s;
  // Use the buffer length to calculate the offset.
  size_t offset = GetStringBufferLength(state->compilePtr);
  // Push the address + offset to the stack.
  CellStackPush(&state->dataStack, (Cell){(cell_t)here + offset, CELL_TYPE_ADDRESS});
}
