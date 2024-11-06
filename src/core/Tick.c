#include "raylib.h"
#include "../crForth.h"

// ( "<spaces>name" -- XT ) 
// Find name and return XT, the execution token for name.
// ' xyz EXECUTE is equivalent to xyz. 
// https://forth-standard.org/standard/core/Tick
void Tick(KernelState *state) {
  // Consume the next word
  char wordBuffer[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);

  // Look up the word in the dictionary
  ForthWord* foundWordMeta = GetItemFromDictionary(&state->dict, wordBuffer);
  if (foundWordMeta != NULL) {
    CellStackPush(&state->dataStack, (Cell){(CellValue)foundWordMeta->data, CELL_TYPE_XT});
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", wordBuffer);
  }
}
