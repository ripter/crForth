#include <stdio.h>

#include "../crForth.h"

void Words(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  GetKeysInDictionary(&state->dict);
  printf("\n");
}
