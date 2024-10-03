#include "../crForth.h"

// ( c-addr u -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  cell_t length = PopFromCellStack(&state->dataStack);      // u
  char *word = (char *)PopFromCellStack(&state->dataStack); // c-addr

  // Get the word from the dictionary
  WordMetadata *foundWordMeta = GetItemFromDictionary(&state->dict, word);
  if (foundWordMeta != NULL) {
    foundWordMeta->func(state, foundWordMeta);
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", word);
  }
}
