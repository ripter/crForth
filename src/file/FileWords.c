#include "FileWords.h"

void AddFileWords(KernelState *state) {
  AddWordToDictionary(&state->dict, CreateForthWord("included", (xt_func_ptr)Included, false, NULL));
}

