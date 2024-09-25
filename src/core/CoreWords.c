#include "../crForth.h"
#include "CoreWords.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
void AddCoreWords(KernelState *state) {
  AddItemToDictionary(&state->dict, "+",        (xt_func_ptr)Add); 
  AddItemToDictionary(&state->dict, "-",        (xt_func_ptr)Subtract);
  AddItemToDictionary(&state->dict, ".",        (xt_func_ptr)Dot);
  AddItemToDictionary(&state->dict, "branch",   (xt_func_ptr)Branch);
  AddItemToDictionary(&state->dict, "branch?",  (xt_func_ptr)BranchZ);
  AddItemToDictionary(&state->dict, ".s",       (xt_func_ptr)DotS);
  AddItemToDictionary(&state->dict, ":",        (xt_func_ptr)Colon);
  AddItemToDictionary(&state->dict, ";",        (xt_func_ptr)SemiColon);
}
