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
  if (IsCellStackEmpty(&state->returnStack)) {
    fprintf(state->errorStream, ERR_EMPTY_STACK);
    return;
  }
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



// ( n1 -- ) ( R: u c-addr -- )
// Branches to the address on the return stack if n1 is not zero.
// The address and length are in reverse order so they don't require a swap when moving from/to the data stack.
void BranchNZ(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter
  if (IsCellStackEmpty(&state->dataStack)) {
    fprintf(state->errorStream, "Error: ?branch requires a test value on the stack.\n");
    return;
  }
  if (IsCellStackEmpty(&state->returnStack)) {
    fprintf(state->errorStream, "Error: ?branch requires an address on the return stack.\n");
    return;
  }
  Cell testValue = CellStackPop(&state->dataStack);
  Cell word = CellStackPop(&state->returnStack);
  Cell length = CellStackPop(&state->returnStack);
  if (!IsNullTerminatedString((const char *)word.value, length.value)) {
    fprintf(state->errorStream, "Error: Return Stack did not contain an address.\n");
    return;
  }

  if (testValue.value) {
    DoForthString(state, (const char *)word.value, (const char *)word.value);
  }
}
