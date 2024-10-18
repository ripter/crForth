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

  // Is there an empty here buffer to name?
  ForthWord *hereWord = GetItemFromDictionary(&state->dict, HERE_BUFFER_NAME);

  if (hereWord == NULL) {
    if (!AddWordToDictionary(&state->dict, InitWordMetadata(newName, (xt_func_ptr)Variable, false, NULL))) {
      fprintf(state->errorStream, "Error: Unable to create %s in the Dictionary.\n", newName);
      return;
    }
    return;
  } else {
    // Reanme the HERE buffer to the new name.
    if (!RenameItemInDictionary(&state->dict, HERE_BUFFER_NAME, newName)) {
      fprintf(state->errorStream, "Error: Unable to rename HERE buffer to %s\n", newName);
    }
  }

}
