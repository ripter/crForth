#include <stdio.h>
#include <string.h>
#include "../crForth.h"



// ( -- )
// Prints the contents of the data stack and return stack.
// https://forth-standard.org/standard/tools/DotS
void DotS(KernelState* state) {
  size_t stackSize = CellStackSize(&state->dataStack);
  size_t returnStackSize = CellStackSize(&state->returnStack);

  fprintf(state->outputStream, "Data Stack<%ld>: ", stackSize);
  for (size_t i = 0; i < stackSize; i++) {
    Cell cell = CellStackPeek(&state->dataStack, i);
    Cell nextCell = (Cell){0};
    if (i + 1 < stackSize) {
      nextCell = CellStackPeek(&state->dataStack, i + 1);
    }
    // Words are 2 cells, the first is the address, the second is the length on the stack.
    if (cell.type == CELL_TYPE_WORD && nextCell.type == CELL_TYPE_NUMBER) {
     fprintf(state->outputStream, "%s ", (char *)cell.value);
      i++; // skip the length
    } else {
     fprintf(state->outputStream, "%ld ", cell.value);
    }
  }
  fprintf(state->outputStream, " \n");

  fprintf(state->outputStream, "Return Stack<%ld>: ", returnStackSize);
  for (size_t i = 0; i < returnStackSize; i++) {
    Cell cell = CellStackPeek(&state->returnStack, i);
    Cell nextCell = (Cell){0};
    if (i + 1 < returnStackSize) {
      nextCell = CellStackPeek(&state->returnStack, i + 1);
    }
    // Words are in reverse order on the return stack. The length is first, then the address.
    if (cell.type == CELL_TYPE_NUMBER && nextCell.type == CELL_TYPE_WORD) {
      fprintf(state->outputStream, "%s ", (char *)nextCell.value);
      i++; // skip the word
    } else {
      fprintf(state->outputStream, "%ld ", cell.value);
    }
  }
  fprintf(state->outputStream, " \n");
}
