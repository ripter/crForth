#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the data stack and return stack.
// https://forth-standard.org/standard/tools/DotS
void DotS(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  size_t stackSize = CellStackSize(&state->dataStack);
  size_t returnStackSize = CellStackSize(&state->returnStack);

  printf("Data Stack: ");
  for (size_t i = 0; i < stackSize; i++) {
    Cell cell = ViewCellStack(&state->dataStack, i);
    if (cell.type == CELL_TYPE_WORD) {
      printf("%s ", (char *)cell.value);
      // Consume length and address for the word
      // if (i + 1 < stackSize) {
      //   Cell length = value;
      //   Cell address = ViewCellStack(&state->dataStack, ++i);
      //   printf("%.*s ", (int)length.value, (char *)address.value);
      // }
    } else {
      printf("%ld ", cell.value);
    }
  }
  printf(" \n");

  printf("Return Stack: ");
  for (size_t i = 0; i < returnStackSize; i++) {
    Cell length = ViewCellStack(&state->returnStack, i);
    if (length.type == CELL_TYPE_WORD && i + 1 < returnStackSize) {
      Cell address = ViewCellStack(&state->returnStack, ++i);
      printf("%.*s ", (int)length.value, (char *)address.value);
    } else {
      printf("%ld ", length.value);
    }
  }
  printf(" \n");
}
