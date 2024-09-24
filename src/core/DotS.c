#include <string.h>

#include "../KernelState.h"
#include "../Stack.h"


char* DotS(KernelState* state, char* word) {
  (void)word; // Unused parameter
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

  return NULL;
}
