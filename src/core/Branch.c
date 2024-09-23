#include "../KernelState.h"


char* BranchNZ(KernelState *state, char* word) {
  cell_t a = PopCellStack(&state->dataStack);
  if (a != 0) {
    return word;
  }
  return NULL;
}
