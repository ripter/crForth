#include "raylib.h"
#include "../crForth.h"

// ( -- XT )
// Pushes the latest (newest) word in the dictionary to the stack.
void Latest(KernelState* state) {
  ForthWord* word = GetLastItemFromDictionary(&state->dict);
  // CellStackPush(&state->dataStack, (Cell){(CellValue)lastItem->name, CELL_TYPE_WORD});
  // CellStackPush(&state->dataStack, (Cell){TextLength(lastItem->name), CELL_TYPE_NUMBER});

  //TODO: This code block is duplicated in Tick.c. Refactor to a common function.
  // Is it a Word Defined in Forth?
  if (GetStringLength(word->data) > 0) {
    CellStackPush(&state->dataStack, (Cell){(CellValue)word->data, CELL_TYPE_XT});
  }
  // C defined string.
  else {
    CellStackPush(&state->dataStack, (Cell){(CellValue)CreateString(word->name), CELL_TYPE_XT});
  }
}
