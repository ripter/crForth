#include "raylib.h"
#include "../crForth.h"

// ( -- x ) ( R: x -- ) 
// Move x from the return stack to the data stack. 
// https://forth-standard.org/standard/core/Rfrom
void RFrom(KernelState* state) {
  Cell a = CellStackPop(&state->returnStack);
  CellStackPush(&state->dataStack, (Cell){a.value, a.type});
}
