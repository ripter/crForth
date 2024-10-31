#include "raylib.h"
#include "../crForth.h"

// ( -- c-addr u )
// Pushes the latest word in the dictionary to the stack.
void Latest(KernelState* state) {
  ForthWord* lastItem = GetLastItemFromDictionary(&state->dict);
  CellStackPush(&state->dataStack, (Cell){(CellValue)lastItem->name, CELL_TYPE_WORD});
  CellStackPush(&state->dataStack, (Cell){TextLength(lastItem->name), CELL_TYPE_NUMBER});
}
