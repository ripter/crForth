#include "raylib.h"
#include "../crForth.h"

// ( x -- ) ( R: -- x )
// Move x to the return stack.
// https://forth-standard.org/standard/core/toR
void ToR(KernelState* state) {
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->returnStack, (Cell){a.value, a.type});
}
