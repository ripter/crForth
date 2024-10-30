#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) 
// Creates a Variable in the dictionary as name.
// If there is data in the HERE buffer, it will be the value of the variable.
// Variables return their address when called.
// https://forth-standard.org/standard/core/CREATE
void Create(KernelState *state) {
  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Create the new Forth Word.
  ForthWord newWord = CreateForthWord(newName, (xt_func_ptr)Variable, false, NULL);
  // Add the new word to the dictionary.
  if (!AddWordToDictionary(&state->dict, newWord)) {
    fprintf(state->errorStream, "Error: Unable to create %s in the Dictionary.\n", newName);
    return;
  }

  // Move the compile pointer to the new word.
  state->compilePtr = newWord.data; 
}
