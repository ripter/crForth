#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the return stack.
void DotSR(KernelState* state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  size_t returnStackSize = CellStackSize(&state->returnStack);

  printf("Return Stack: ");
  for (size_t i = 0; i < returnStackSize; i++) {
    cell_t value = ViewCellStack(&state->returnStack, i);
    printf("%ld ", value); 
  }
  printf(" \n");
}
