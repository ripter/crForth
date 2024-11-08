#include <assert.h>
#include "../crForth.h"
#include "CoreWords.h"


// Changes the type on the last word in the dictionary,
// and starts compiling to it.
// https://forth-standard.org/standard/core/DOES
void Does(KernelState *state) {
  ForthWord *lastItem = GetLastItemFromDictionary(&state->dict);
  lastItem->func = (xt_func_ptr)DoForthStringAndReturnAddress;
  assert(lastItem->data != NULL); // The word should have a data pointer. 
  //TODO: Fix this, I just broke it to get compiling again. Tests are failing because of this.
  // state->compilePtr = lastItem->data;
  state->IsInCompileMode = true;
}
