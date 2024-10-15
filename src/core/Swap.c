#include "raylib.h"
#include "../crForth.h"

// ( a b -- b a )
// Swaps the top two items on the stack.
// https://forth-standard.org/standard/core/SWAP
void Swap(KernelState* state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value, CELL_TYPE_NUMBER});
  CellStackPush(&state->dataStack, (Cell){b.value, CELL_TYPE_NUMBER});
}
