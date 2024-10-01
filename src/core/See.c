#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "../crForth.h"

// ( "<spaces>name" -- ) 
// Display the definition of the word with the given name.
// https://forth-standard.org/standard/tools/SEE
void See(KernelState* state, WordMetadata* wordMeta) {
  (void)wordMeta; // UNUSED
  // Get the Word name from the input stream.
  char wordName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordName, MAX_WORD_LENGTH);
  WordMetadata* meta = GetItemFromDictionary(&state->dict, wordName);

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
  // If the word is implemented in C, display a message.
  if (meta->data == NULL) {
    printf("Word '%s' is implemented in C.\n", meta->name);
    return;
  }
  // Display the word's definition.
  printf("\n: %s\n  %s\n; %s\n", TextToUpper(meta->name), meta->data, meta->isImmediate ? "IMMEDIATE" : "");
}
