#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the data stack.
// https://forth-standard.org/standard/tools/DotS
void DotSD(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  size_t stackSize = CellStackSize(&state->dataStack);

  printf("Data Stack: ");
  for (size_t i = 0; i < stackSize; i++) {
    cell_t value = ViewCellStack(&state->dataStack, i);
    printf("%ld ", value); 
  }
  printf(" \n");
}
