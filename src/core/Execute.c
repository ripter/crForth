#include <raylib.h>
#include "../crForth.h"

// ( c-addr u -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state) {
  char previousWord[MAX_WORD_LENGTH];
  (void)CellStackPop(&state->dataStack);       // u
  Cell word = CellStackPop(&state->dataStack); // c-addr

  // Get the word from the dictionary
  ForthWord *foundWordMeta = GetItemFromDictionary(&state->dict, (const char *)word.value);
  if (foundWordMeta != NULL) {
    // Switch the "current" word to the found word
    TextCopy(previousWord, state->wordBuffer); 
    TextCopy(state->wordBuffer, foundWordMeta->name);
    // Execute the word
    foundWordMeta->func(state);
    // Restore the previous word
    TextCopy(state->wordBuffer, previousWord);
    // Clear the previous word buffer to prevent accidental use.
    previousWord[0] = '\0';
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", (char *)word.value);
  }
}
