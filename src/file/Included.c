#include "../crForth.h"


// ( addr u -- )
// Loads and executes the file at the given path.
// Example: s" src/forth/CoreWords.fth" included
// https://forth-standard.org/standard/file/INCLUDED
void Included(KernelState *state) {
  Cell u = CellStackPop(&state->dataStack);
  Cell addr = CellStackPop(&state->dataStack);
  // Get the path string from the address and length.
  char path[u.value + 1];
  for (int i = 0; i < u.value; i++) {
    path[i] = (char)addr.value + i;
  }

  printf("Included: %s\n", path);
}
