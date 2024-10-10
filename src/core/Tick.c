#include "raylib.h"
#include "../crForth.h"

// ( "<spaces>name" -- c-addr u ) 
// In a typical Forth system, this would fetch the XT of the word from the dictionary.
// In crForth, the word is pushed to the stack as a string. Instead of having address, we use the name.
// https://forth-standard.org/standard/core/Tick
void Tick(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  // Consume the next word
  char wordBuffer[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);

  // Look up the word in the dictionary
  WordMetadata* foundWordMeta = GetItemFromDictionary(&state->dict, wordBuffer);
  if (foundWordMeta != NULL) {
    CellStackPush(&state->dataStack, (Cell){(cell_t)foundWordMeta->name, CELL_TYPE_WORD});
    CellStackPush(&state->dataStack, (Cell){TextLength(foundWordMeta->name), CELL_TYPE_NUMBER});
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", wordBuffer);
  }
}
