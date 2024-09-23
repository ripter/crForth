#include "CoreWords.h"

void AddCoreWords(KernelState *state) {
  AddItem(&state->dict, "+", (xt_func_ptr)Add); 
  AddItem(&state->dict, ".", (xt_func_ptr)Dot);
}
