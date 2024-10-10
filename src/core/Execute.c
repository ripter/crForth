#include "../crForth.h"

// ( c-addr u -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta;                                           // Unused parameter
  (void)PopFromCellStack(&state->dataStack);                // u
  Cell word = PopFromCellStack(&state->dataStack); // c-addr

  // Get the word from the dictionary
  WordMetadata *foundWordMeta = GetItemFromDictionary(&state->dict, (const char *)word.value);
  if (foundWordMeta != NULL) {
    foundWordMeta->func(state, foundWordMeta);
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", (char *)word.value);
  }
}
