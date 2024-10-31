#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( -- c-addr u )
// HERE returns an address + length of the scratch buffer.
// https://forth-standard.org/standard/core/HERE
void Here(KernelState *state) {
  CellValue start = (CellValue)state->hereBuffer;
  CellValue length = GetStringBufferLength(state->hereBuffer);
  // printf("\nHERE: 0x%lx + %ld = 0x%lx\t\"%s\"\n", start, length, (start + length), state->hereBuffer->s);
  // Push the address + length to the stack.
  CellStackPush(&state->dataStack, (Cell){start + length, CELL_TYPE_ADDRESS});
}
