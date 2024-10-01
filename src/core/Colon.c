#include <stdio.h>
#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name --" )
// Create a new word in the dictionary with the given name.
// Switch to compile mode.
void Colon(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Create a text buffter to hold the word definition.
  char* wordDef = (char *)MemAlloc(MAX_WORD_LENGTH);
  // Create a new WordMeta for the newly created word.
  WordMetadata newWordMeta = InitWordMetadata(newName, (xt_func_ptr)DoForthString, false, wordDef);
  // Add the new word to the dictionary.
  AddWordToDictionary(&state->dict, newWordMeta);

  // Start Compile Mode
  state->IsInCompileMode = true;
}
