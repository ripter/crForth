#include <stdio.h>

#include "../crForth.h"

void See(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  // We need to get the word we want to look up.
  // Put see on the return stack so we can get the next word.
  if (wordMeta != NULL) {
    PushToCellStack(&state->returnStack, (cell_t)See);
    return;
  }

  WordMetadata* meta = GetItemFromDictionary(&state->dict, state->wordBuffer);
  if (meta == NULL) {
    printf("Word not found in dictionary: %s\n", state->wordBuffer);
    return;
  }
  if (meta->data == NULL) {
    printf("Word '%s' is implemented in C.\n", meta->name);
    return;
  }
  printf("\n: %s %s ;\n", meta->name, meta->data);
  state->wordBuffer[0] = '\0'; // Clear the word buffer.
}
