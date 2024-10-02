#include <string.h>
#include "CoreWords.h"

#include "../crForth.h"
#include "../WordMetadata.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
void AddCoreWords(KernelState *state) {
  AddWordToDictionary(&state->dict, InitWordMetadata("+",         (xt_func_ptr)Add,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("-",         (xt_func_ptr)Subtract,      false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".",         (xt_func_ptr)Dot,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("branch",    (xt_func_ptr)Branch,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("branch?",   (xt_func_ptr)BranchZ,       false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".s",        (xt_func_ptr)DotS,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(":",         (xt_func_ptr)Colon,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(";",         (xt_func_ptr)SemiColon,     true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("words",     (xt_func_ptr)Words,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("see",       (xt_func_ptr)See,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("immediate", (xt_func_ptr)Immediate,     false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("latest",    (xt_func_ptr)Latest,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("emit",      (xt_func_ptr)Emit,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("c@",        (xt_func_ptr)CFetch,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("create",    (xt_func_ptr)Create,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("does>",     (xt_func_ptr)Does,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("dup",       (xt_func_ptr)Dup,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("drop",      (xt_func_ptr)Drop,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("swap",      (xt_func_ptr)Swap,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(">r",        (xt_func_ptr)ToR,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("r>",        (xt_func_ptr)RFrom,         false,  NULL));
}
