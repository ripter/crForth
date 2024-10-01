#include "../crForth.h"
#include "CoreWords.h"


// Sets or Replaces the definition of the last word in the dictionary.
// https://forth-standard.org/standard/core/DOES
void Does(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  WordMetadata *lastItem = GetLastItemFromDictionary(&state->dict);
  lastItem->func = (xt_func_ptr)DoForthString;
  state->IsInCompileMode = true;
}
