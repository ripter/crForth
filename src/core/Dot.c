#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"

char* Dot(KernelState* state, char* word) {
  (void)word; // UNUSED
  cell_t a = PopCellStack(&state->dataStack);
  printf("%ld\n", a);
  return NULL;
}