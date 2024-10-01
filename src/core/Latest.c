#include "../crForth.h"

// ( -- c-addr u )
// Pushes the latest word in the dictionary to the stack.
void Latest(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  WordMetadata* lastItem = GetLastItemFromDictionary(&state->dict);
  PushToCellStack(&state->dataStack, (cell_t)lastItem->name);
  PushToCellStack(&state->dataStack, (cell_t)strlen(lastItem->name));
}
