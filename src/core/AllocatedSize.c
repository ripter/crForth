#include "../crForth.h"

// ( addr -- size )
// Returns the size of the memory block allocated at addr.
void AllocatedSize(KernelState *state) {
  Cell addr = CellStackPop(&state->dataStack);
  if (addr.type != CELL_TYPE_ADDRESS) {
    fprintf(state->errorStream, "Error: ALLOCATED-SIZE expected an address on the stack.\n");
    return;
  }
  ForthWord *word = GetItemFromDictionary(&state->dict, (char *)addr.value);
  CellStackPush(&state->dataStack, (Cell){(cell_t)GetStringBufferLength(word->data), CELL_TYPE_NUMBER});
}
