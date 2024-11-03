#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) 
// Display the definition of the word with the given name.
// https://forth-standard.org/standard/tools/SEE
void See(KernelState* state) {
  // Get the Word name from the input stream.
  char wordName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordName, MAX_WORD_LENGTH);
  ForthWord* word = GetItemFromDictionary(&state->dict, wordName);

  // If the word was not found, check if it's a number.
  if (word == NULL) {
    if (IsNumber(wordName)) {
      CellValue num = (CellValue)atoi(wordName);
      fprintf(state->outputStream, "Literal: %ld\n", num);
      return;
    }
    fprintf(state->outputStream, "Word not found in dictionary: '%s'\n", wordName);
    return;
  }

  // Does it have a data buffer?
  size_t bufferSize = GetStringLength(word->data);

  // Is is a Variable?
  if (word->func == (xt_func_ptr)Variable) {
    fprintf(state->outputStream, "Variable<%ld>: %s\n", bufferSize, word->name);
    return;
  }
  // If the word is implemented in C, display a message.
  if (bufferSize == 0) {
    fprintf(state->outputStream, "Word '%s' is implemented in C.\n", word->name);
    return;
  }
  // Display the word's definition.
  fprintf(state->outputStream, "\n: %s\n  %s\n; %s\n", TextToUpper(word->name), GetStringValue(word->data), word->isImmediate ? "IMMEDIATE" : "");
}
