#include "CoreWords.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
void AddCoreWords(KernelState *state) {
  AddItem(&state->dict, "+", (xt_func_ptr)Add); 
  AddItem(&state->dict, ".", (xt_func_ptr)Dot);
  AddItem(&state->dict, "branch", (xt_func_ptr)Branch);
  AddItem(&state->dict, "branch?", (xt_func_ptr)BranchNZ);
}
