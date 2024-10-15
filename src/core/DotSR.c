#include <stdio.h>
#include <string.h>
#include "../crForth.h"


// ( -- )
// Prints the contents of the return stack.
void DotSR(KernelState* state) {
  size_t returnStackSize = CellStackSize(&state->returnStack);

  printf("Return Stack: ");
  for (size_t i = 0; i < returnStackSize; i++) {
    Cell value = CellStackPeek(&state->returnStack, i);
    printf("%ld ", value.value); 
  }
  printf(" \n");
}
