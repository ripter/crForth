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
    cell_t value = ViewCellStack(&state->dataStack, i);
    printf("%ld ", value); 
  }
  printf(" \n");

  printf("Return Stack: ");
  for (size_t i = 0; i < returnStackSize; i++) {
    cell_t value = ViewCellStack(&state->returnStack, i);
    printf("%ld ", value); 
  }
  printf(" \n");
}
