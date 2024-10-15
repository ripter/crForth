#include "raylib.h"
#include "../crForth.h"

// ( n1 n2 -- flag ) 
// flag is true if n1 is greater than n2; otherwise flag is false.
// https://forth-standard.org/standard/core/more
void GreaterThan(KernelState* state) {
  Cell b = CellStackPop(&state->dataStack);
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value > b.value ? FTRUE : FFALSE, CELL_TYPE_BOOL});
}


// ( n1 n2 -- flag )
// flag is true if n1 is less than n2; otherwise flag is false.
// https://forth-standard.org/standard/core/less
void LessThan(KernelState* state) {
  Cell b = CellStackPop(&state->dataStack);
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value < b.value ? FTRUE : FFALSE, CELL_TYPE_BOOL});
}

void NotEqual(KernelState* state) {
  Cell b = CellStackPop(&state->dataStack);
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value != b.value ? FTRUE : FFALSE, CELL_TYPE_BOOL});
}

void Equal(KernelState* state) {
  Cell b = CellStackPop(&state->dataStack);
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value == b.value ? FTRUE : FFALSE, CELL_TYPE_BOOL});
}

// ( x -- flag )
// flag is true if and only if x is equal to zero.
// https://forth-standard.org/standard/core/ZeroEqual
void ZeroEquals(KernelState* state) {
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value == 0 ? FTRUE : FFALSE, CELL_TYPE_BOOL});
}
