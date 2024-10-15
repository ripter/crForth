#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the data stack and return stack.
// https://forth-standard.org/standard/tools/DotS
void DotS(KernelState* state) {
  size_t stackSize = CellStackSize(&state->dataStack);
  size_t returnStackSize = CellStackSize(&state->returnStack);

  printf("Data Stack: ");
  for (size_t i = 0; i < stackSize; i++) {
    Cell cell = CellStackPeek(&state->dataStack, i);
    if (cell.type == CELL_TYPE_WORD) {
      printf("%s ", (char *)cell.value);
      // skip the length
      i++;
    } else {
      printf("%ld ", cell.value);
    }
  }
  printf(" \n");

  printf("Return Stack: ");
  for (size_t i = 0; i < returnStackSize; i++) {
    Cell cell = CellStackPeek(&state->returnStack, i);
    if (cell.type == CELL_TYPE_WORD) {
      printf("%s ", (char *)cell.value);
    } else {
      printf("%ld ", cell.value);
    }
  }
  printf(" \n");
}
