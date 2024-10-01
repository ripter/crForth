#include "../crForth.h"

// ( "<spaces>number" -- )
// Parse a number delimited by a space and skip the number of words specified by the parsed number.
// Branch is an immediate word that controls the flow by skipping words.
void Branch(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  // Consume the next word, which is the number of words to skip.
  char wordBuffer[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
  cell_t num; 
  ConvertWordToNumber(wordBuffer, &num);

  // Skip the number of words specified by the parsed number.
  for (cell_t i = 0; i < num; i++) {
    GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
  }
}

// ( flag "<spaces>number" -- )
// When the flag is false, the branch? word skips the number of words specified by the parsed number.
// When the flag is true, the branch? word does nothing.
void BranchZ(KernelState *state, WordMetadata *wordMeta) {
  // char wordBuffer[MAX_WORD_LENGTH];
  bool testValue = (bool)PopFromCellStack(&state->dataStack);

  // False means we *DO* skip the words after the branch.
  if (!testValue) {
    Branch(state, wordMeta);
  }
  else {
    // Consume the next word, which is the number of words to skip.
    char wordBuffer[MAX_WORD_LENGTH];
    GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
  }
}
