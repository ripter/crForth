#include "../crForth.h"

// ( -- )
// Sets the last word in the dictionary to be immediate.
void Latest(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  WordMetadata* lastItem = GetLastItemFromDictionary(&state->dict);
  PushToCellStack(&state->dataStack, (cell_t)lastItem->name);
}
