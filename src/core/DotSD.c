#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the data stack.
// https://forth-standard.org/standard/tools/DotS
void DotSD(KernelState* state) {
  size_t stackSize = CellStackSize(&state->dataStack);

  printf("Data Stack: ");
  for (size_t i = 0; i < stackSize; i++) {
    Cell value = CellStackPeek(&state->dataStack, i);
    printf("%ld ", value.value); 
  }
  printf(" \n");
}
