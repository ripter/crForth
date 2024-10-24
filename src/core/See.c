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
  ForthWord* meta = GetItemFromDictionary(&state->dict, wordName);
  size_t bufferSize = GetStringBufferLength(meta->data);

  // If the word was not found, check if it's a number.
  if (meta == NULL) {
    if (IsNumber(wordName)) {
      cell_t num = (cell_t)atoi(wordName);
      printf("Literal: %ld\n", num);
      return;
    }
    printf("Word not found in dictionary: '%s'\n", wordName);
    return;
  }
  // Is is a Variable?
  if (meta->func == (xt_func_ptr)Variable) {
    printf("Variable<%ld>: %s\n", bufferSize, meta->name);
    return;
  }
  // Is it HERE?
  if (meta->func == (xt_func_ptr)Here) {
    // Get the HERE buffer instead of the HERE word.
    meta = GetItemFromDictionary(&state->dict, HERE_BUFFER_NAME);
    printf("HERE<%ld>: %s\n", bufferSize, GetStringValue(meta->data));
    return;
  }
  // If the word is implemented in C, display a message.
  if (bufferSize == 0) {
    printf("Word '%s' is implemented in C.\n", meta->name);
    return;
  }
  // Display the word's definition.
  printf("\n: %s\n  %s\n; %s\n", TextToUpper(meta->name), GetStringValue(meta->data), meta->isImmediate ? "IMMEDIATE" : "");
}
