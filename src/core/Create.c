#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) 
// Creates a new word in the dictionary with the given name.
// https://forth-standard.org/standard/core/CREATE
void Create(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  (void)state; // Unused parameter

  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Create a new WordMeta for the newly created word.
  WordMetadata newWordMeta = InitWordMetadata(newName, (xt_func_ptr)Nothing, false, NULL);
  // Add the new word to the dictionary.
  AddWordToDictionary(&state->dict, newWordMeta);
}
