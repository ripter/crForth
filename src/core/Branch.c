/**
 * Branch.c
 * 
 * Branching in crForth is a bit different than in other Forths.
 * crForth is a streaming Forth, which means that it reads words from a stream and processes them.
 * There is no loading code into a buffer and then executing it. There is no Intstruction Pointer or Program Counter.
 * While words may allocate memory, a word's XT is only accessible from the dictionary.
 * 
 */
#include "../crForth.h"
#include "CoreWords.h"


// ( n -- )
// Skip the next n words in the input stream.
void Skip(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  char wordBuffer[MAX_WORD_LENGTH];
  cell_t num = PopFromCellStack(&state->dataStack);

  // Skip the number of words specified by the parsed number.
  for (cell_t i = 0; i < num; i++) {
    GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
  }
}

// ( n1 n2 -- )
// Skips n2 words in the input stream if n1 is 0.
void SkipOnZero(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  cell_t num2 = PopFromCellStack(&state->dataStack);
  cell_t num1 = PopFromCellStack(&state->dataStack);

  // Skip the number of words specified by the parsed number.
  if (num1 == 0) {
    for (cell_t i = 0; i < num2; i++) {
      char wordBuffer[MAX_WORD_LENGTH];
      GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
    }
  }
}


// ( R: u c-addr -- )
// Branches to the address on the return stack.
// The address and length are in reverse order so they don't require a swap when moving from/to the data stack.
void Branch(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  char* word = (char *)PopFromCellStack(&state->returnStack);
  cell_t length = PopFromCellStack(&state->returnStack);

  DoForthString(state, word, word);
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
