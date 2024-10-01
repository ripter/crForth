#include "../crForth.h"

// ( -- )
// Sets the last word in the dictionary to be immediate.
void Immediate(KernelState* state, WordMetadata* wordMeta) {
  wordMeta = GetLastItemFromDictionary(&state->dict);
  wordMeta->isImmediate = true;
}
