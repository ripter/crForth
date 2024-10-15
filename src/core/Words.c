#include <stdio.h>

#include "../crForth.h"

// ( -- )
// Prints all the words in the dictionary.
void Words(KernelState* state) {
  GetKeysInDictionary(&state->dict);
  printf("\n");
}
