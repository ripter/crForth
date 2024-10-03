#include "raylib.h"
#include "../crForth.h"

// ( n1 n2 -- flag ) 
// flag is true if n1 is greater than n2; otherwise flag is false.
// https://forth-standard.org/standard/core/more
void GreaterThan(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t b = PopFromCellStack(&state->dataStack);
  cell_t a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, a > b ? FTRUE : FFALSE);
}


// ( n1 n2 -- flag )
// flag is true if n1 is less than n2; otherwise flag is false.
// https://forth-standard.org/standard/core/less
void LessThan(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t b = PopFromCellStack(&state->dataStack);
  cell_t a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, a < b ? FTRUE : FFALSE);
}

void NotEqual(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t b = PopFromCellStack(&state->dataStack);
  cell_t a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, a != b ? FTRUE : FFALSE);
}

void Equal(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  cell_t b = PopFromCellStack(&state->dataStack);
  cell_t a = PopFromCellStack(&state->dataStack);
  PushToCellStack(&state->dataStack, a == b ? FTRUE : FFALSE);
}
