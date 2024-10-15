#include "../crForth.h"

// ( -- )
// Sets the last word in the dictionary to be immediate.
void Immediate(KernelState* state) {
  ForthWord *wordMeta = GetLastItemFromDictionary(&state->dict);
  wordMeta->isImmediate = true;
}
