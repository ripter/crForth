#include <stdio.h>

#include "../crForth.h"

// ( a b -- c )
// Adds two numbers from the stack and pushes the result back to the stack.
void Add(KernelState* state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value + b.value, a.type});
}
