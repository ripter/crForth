#include "raylib.h"
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- XT ) 
// Find name and return XT, the execution token for name.
// ' xyz EXECUTE is equivalent to xyz. 
// https://forth-standard.org/standard/core/Tick
void Tick(KernelState *state) {
  // Consume the next word
  char wordBuffer[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);

  // Look up the word in the dictionary
  ForthWord* word = GetItemFromDictionary(&state->dict, wordBuffer);
  if (word == NULL) {
    fprintf(state->errorStream, "Error: Word not found: %s\n", wordBuffer);
    return;
  }

  //TODO: This code block is duplicated in Latest.c. Refactor to a common function.
  // Is it a Word Defined in Forth?
  if (GetStringLength(word->data) > 0) {
    CellStackPush(&state->dataStack, (Cell){(CellValue)word->data, CELL_TYPE_XT});
  }
  // C defined string.
  else {
    CellStackPush(&state->dataStack, (Cell){(CellValue)CreateString(word->name), CELL_TYPE_XT});
  }
}
