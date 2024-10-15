#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( flag -- )  ( R: -- flag )
// If flag is false, skip until THEN or ELSE. 
// https://forth-standard.org/standard/core/IF
void IF(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  char word[MAX_WORD_LENGTH];
  Cell flag = CellStackPop(&state->dataStack);
  // Push the flag to the return stack so ELSE and THEN can use it.
  CellStackPush(&state->returnStack, flag);

  if (flag.value == FFALSE) {
    // printf("IF: flag is false, skipping until ELSE or THEN\n");
    // Skip until ELSE or THEN
    while (GetNextWord(state->inputStream, word, MAX_WORD_LENGTH)) {
      // printf("IF: skipping word: %s\n", word);
      if (TextIsEqual(word, "else") || TextIsEqual(word, "then")) {
        wordMeta = GetItemFromDictionary(&state->dict, word);
        // Run the else/then word and break out of the loop.
        // DoForthString(state, word, word); 
        wordMeta->func(state, wordMeta);
        break;
      }
    }
  }
}

// ( R: flag -- )
// If the flag is true, skip until THEN.
// https://forth-standard.org/standard/core/ELSE
void ELSE(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  char word[MAX_WORD_LENGTH];
  Cell flag = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, flag);
  if (flag.value != FFALSE) {
    // Skip until THEN
    while (GetNextWord(state->inputStream, word, MAX_WORD_LENGTH)) {
      if (TextIsEqual(word, "then")) {
        wordMeta = GetItemFromDictionary(&state->dict, word);
        wordMeta->func(state, wordMeta);
        break;
      }
    }
  }
}

// ( R: flag -- )
// Completes the IF/ELSE words.
// https://forth-standard.org/standard/core/THEN
void THEN(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  (void)state; // Unused parameter
  // Pop the flag value off the stack.
  (void)CellStackPop(&state->returnStack);
}

