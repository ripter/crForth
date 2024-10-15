#include "../crForth.h"

// ( c-addr u -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state) {
  (void)CellStackPop(&state->dataStack);       // u
  Cell word = CellStackPop(&state->dataStack); // c-addr

  // Get the word from the dictionary
  ForthWord *foundWordMeta = GetItemFromDictionary(&state->dict, (const char *)word.value);
  if (foundWordMeta != NULL) {
    foundWordMeta->func(state, foundWordMeta);
  } else {
    fprintf(state->errorStream, "Error: Word not found: %s\n", (char *)word.value);
  }
}
