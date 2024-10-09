#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) ( R: -- a-addr ) 
// Creates a new word in the dictionary with the given name.
// https://forth-standard.org/standard/core/CREATE
void Create(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Reserve 1 cell of variable space for the new word.
  char* newWordData = (char*)MemAlloc(sizeof(cell_t));
  // Create a new WordMeta for the newly created word.
  WordMetadata newWordMeta = InitWordMetadata(newName, (xt_func_ptr)Variable, false, newWordData);
  // Add the new word to the dictionary.
  AddWordToDictionary(&state->dict, newWordMeta);
  // Push the "address" of the new word onto the stack.
  char *name = newWordMeta.name;
  PushToCellStack(&state->returnStack, (Cell){(cell_t)name, CELL_TYPE_WORD});
}
