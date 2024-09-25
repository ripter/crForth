#include <string.h>
#include "CoreWords.h"

#include "../crForth.h"
#include "../WordMetadata.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
void AddCoreWords(KernelState *state) {
  AddItemToDictionary(&state->dict, "+",        (WordMetadata){(xt_func_ptr)Add,        false, NULL}); 
  AddItemToDictionary(&state->dict, "-",        (WordMetadata){(xt_func_ptr)Subtract,   false, NULL});
  AddItemToDictionary(&state->dict, ".",        (WordMetadata){(xt_func_ptr)Dot,        false, NULL});
  AddItemToDictionary(&state->dict, "branch",   (WordMetadata){(xt_func_ptr)Branch,     false, NULL});
  AddItemToDictionary(&state->dict, "branch?",  (WordMetadata){(xt_func_ptr)BranchZ,    false, NULL});
  AddItemToDictionary(&state->dict, ".s",       (WordMetadata){(xt_func_ptr)DotS,       false, NULL});
  AddItemToDictionary(&state->dict, ":",        (WordMetadata){(xt_func_ptr)Colon,      false, NULL});
  AddItemToDictionary(&state->dict, ";",        (WordMetadata){(xt_func_ptr)SemiColon,  false, NULL});
}
