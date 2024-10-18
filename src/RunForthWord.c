#include <raylib.h>
#include "crForth.h"

// Runs the Forth system with the given string.
void RunForthWord(KernelState *state, const char *forthWord) {
  char previousWord[MAX_WORD_LENGTH];
  // Get the word from the dictionary
  ForthWord *word = GetItemFromDictionary(&state->dict, forthWord);
  if (word == NULL) {
    fprintf(state->errorStream, "Error: Word not found: %s\n", forthWord);
    return;
  }

  // Switch the "current" word to the found word
  TextCopy(previousWord, state->wordBuffer);
  TextCopy(state->wordBuffer, word->name);
  // Execute the word
  word->func(state);
  // Restore the previous word
  TextCopy(state->wordBuffer, previousWord);
}
