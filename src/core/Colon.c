#include <stdio.h>
#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

void Colon(KernelState *state, WordMetadata *wordMeta) {
  // First time : is called, we need to consume the next word to get the name of the new word.
  // So push Colon back onto the return stack and return NULL.
  if (wordMeta != NULL) {
    PushToCellStack(&state->returnStack, (cell_t)Colon);
    return;
  }

  // Second time : is called, we need to consume the next word to get the name of the new word.
  // Create a text buffter to hold the word definition.
  char* wordDef = (char *)MemAlloc(MAX_WORD_LENGTH);
  // Create a new WordMeta for the newly created word.
  WordMetadata newWordMeta = InitWordMetadata(state->wordBuffer, (xt_func_ptr)DoForthString, false, wordDef);
  // Add the new word to the dictionary.
  AddWordToDictionary(&state->dict, newWordMeta);

  // Start Compile Mode
  state->IsInCompileMode = true;
  state->wordBuffer[0] = '\0'; // Clear the word buffer.
}
