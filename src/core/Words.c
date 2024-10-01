#include <stdio.h>

#include "../crForth.h"

// ( -- )
// Prints all the words in the dictionary.
void Words(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  GetKeysInDictionary(&state->dict);
  printf("\n");
}
