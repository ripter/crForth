#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) ( R: -- a-addr ) 
// Names the unanmed word pointed to by HERE.
// https://forth-standard.org/standard/core/CREATE
void Create(KernelState *state) {
  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Reanme the HERE buffer to the new name.
  if (!RenameItemInDictionary(&state->dict, HERE_BUFFER_NAME, newName)) {
    fprintf(state->errorStream, "Error: Unable to rename HERE buffer to %s\n", newName);
  }
}
