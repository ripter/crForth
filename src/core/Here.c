#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( -- c-addr u )
// Here returns the address of the next available space in the dictionary.
// It will continue to return the same address until the word is defined with CREATE.
// https://forth-standard.org/standard/core/HERE
void Here(KernelState *state) {
  // Is there a compile pointer?
  if (state->compilePtr == NULL) {
    // Point at the latest word in the dictionary.
    // ForthWord *latest = GetLastItemFromDictionary(&state->dict);
    // state->compilePtr = latest->data;
    // printf("\nSetting HERE to the latest word in the dictionary.\n");
    printf("\n\nOOPS no compile pointer\n\n");
    return;
  }
  // Compile pointer gives us the start of the buffer.
  CellValue here = (CellValue)state->compilePtr->s;
  // Use the buffer length to calculate the offset.
  size_t offset = GetStringBufferLength(state->compilePtr);
  printf("\nHERE: 0x%lx + %ld = 0x%lx\t\"%s\"\n", here, offset, (here + offset), state->compilePtr->s);
  // Push the address + offset to the stack.
  CellStackPush(&state->dataStack, (Cell){(CellValue)here + offset, CELL_TYPE_ADDRESS});
}
