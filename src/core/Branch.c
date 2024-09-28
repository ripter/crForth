#include "../crForth.h"

// ( C: "<spaces>number --" )
// Parse a number delimited by a space and skip the number of words specified by the parsed number.
// Branch is an immediate word that controls the flow by skipping words.
void Branch(KernelState *state, WordMetadata *wordMeta) {
  // first time we are called, we need to initialize the loop.
  if (wordMeta != NULL) {
    PushToCellStack(&state->returnStack, -1); // Sentinel value for the loop counter.
    PushToCellStack(&state->returnStack, (cell_t)Branch);
    return;
  }

  // Get the loop counter from the return stack.
  cell_t loopCounter = PopFromCellStack(&state->returnStack);

  // If it's the sentinel value, the word is the loop count.
  if (loopCounter == -1) {
    cell_t num = (cell_t)atoi(state->wordBuffer);
    loopCounter = num; 
  }

  // If the loop counter is zero, we are done.
  if (loopCounter == 0) {
    state->wordBuffer[0] = '\0'; // Clear the word buffer.
    return;
  }

  // Decrement the loop and update the return stack.
  PushToCellStack(&state->returnStack, loopCounter - 1);
  PushToCellStack(&state->returnStack, (cell_t)Branch);
  state->wordBuffer[0] = '\0'; // Clear the word buffer.
}


// ( flag C: "<spaces>number" -- )
// When the flag is false, the branch? word skips the number of words specified by the parsed number.
// When the flag is true, the branch? word does nothing.
void BranchZ(KernelState *state, WordMetadata *wordMeta) {
  // This will only happen if we are called as a result of a branch.
  // So we only need to consume the number and end the word.
  if (wordMeta == NULL) {
    state->wordBuffer[0] = '\0'; // Clear the word buffer.
    return;
  }

  bool testValue = (bool)PopFromCellStack(&state->dataStack);
  if (testValue) {
    // True means we do *NOT* skip the words after the branch. (aka we "run" the branch)
    // All we really need to do is skip the next word, which is the number of words to skip.
    PushToCellStack(&state->returnStack, (cell_t)BranchZ);
  }
  else {
    // False means we *DO* skip the words after the branch.
    Branch(state, wordMeta);
  }
}
