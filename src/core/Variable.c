#include <stdio.h>
#include "../crForth.h"

// ( -- c-addr )
// Represents a variable in the dictionary.
// Treats the wordMeta->data as a pointer to a cell_t
void Variable(KernelState* state, WordMetadata *wordMeta) {
  CellStackPush(&state->dataStack, (Cell){(cell_t)&wordMeta->data, CELL_TYPE_VARIABLE});
}
