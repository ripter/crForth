#include <stdio.h>

#include "../KernelState.h"
#include "../Stack.h"

void Dot(KernelState* state) {
  cell_t a = PopCellStack(&state->dataStack);
  printf("%ld\n", a);
  // int a = PopInt(state->dataStack);
  // printf("%d\n", a);
}
