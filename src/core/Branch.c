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
  Cell num = CellStackPop(&state->dataStack);

  if (num.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "Error: Skip requires a number on the stack.\n");
    return;
  }

  // Skip the number of words specified by the parsed number.
  for (cell_t i = 0; i < num.value; i++) {
    GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
  }
}

// ( n1 n2 -- )
// Skips n2 words in the input stream if n1 is 0.
void SkipOnZero(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  Cell num2 = CellStackPop(&state->dataStack);
  Cell num1 = CellStackPop(&state->dataStack);

  // Skip the number of words specified by the parsed number.
  if (num1.value == 0) {
    for (cell_t i = 0; i < num2.value; i++) {
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
  BAIL_IF_EMPTY_RETURN_STACK();

  Cell word = CellStackPop(&state->returnStack);
  Cell length = CellStackPop(&state->returnStack);
  if (word.type != CELL_TYPE_WORD || length.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, ERR_INVALID_WORD_ON_RETURN_STACK);
    return;
  }
  if (!IsNullTerminatedString((const char *)word.value, length.value+1)) {
    fprintf(state->errorStream, ERR_WORD_NOT_FOUND, (char *)word.value);
    return;
  }

  DoForthString(state, (const char *)word.value, (const char *)word.value);
}



// ( flag -- ) ( R: u c-addr -- )
// Branches to the address on the return stack if flag is true.
// The address and length are in reverse order so they don't require a swap when moving from/to the data stack.
// Example: ' + >r >r 10 9 -1 ?branch
void BranchNZ(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  // Pop the flag off the data stack.
  BAIL_IF_EMPTY_DATA_STACK();
  Cell flag = CellStackPop(&state->dataStack);

  // Pop the address and length off the return stack.
  BAIL_IF_RETURN_STACK_LESS_THAN(2);
  Cell word = CellStackPop(&state->returnStack);
  Cell length = CellStackPop(&state->returnStack);
  if (word.type != CELL_TYPE_WORD || length.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, ERR_INVALID_WORD_ON_RETURN_STACK);
    return;
  }

  // If the flag is true, branch to the address on the return stack.
  if (flag.value) {
    WordMetadata *meta = GetItemFromDictionary(&state->dict, (const char *)word.value);
    meta->func(state, meta);
  }
}
