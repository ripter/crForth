#include <stdio.h>
#include "../crForth.h"

// ( -- c-addr )
// Represents a variable in the dictionary.
// Treats the wordMeta->data as a pointer to a cell_t
void Variable(KernelState* state) {
  // TODO: Get the data of the current word.
  CellStackPush(&state->dataStack, (Cell){(cell_t)&wordMeta->data, CELL_TYPE_VARIABLE});
}
