#include "../KernelState.h"
#include "../Stack.h"

// ( C: "<spaces>number --" )
// Parse a number delimited by a space and skip the number of words specified by the parsed number.
// Branch is an immediate word that controls the flow by skipping words.
char* Branch(KernelState *state, char* word) {
  // first time we are called, we need to initialize the loop.
  if (word == NULL) {
    PushToCellStack(&state->returnStack, -1); // Sentinel value for the loop counter.
    PushToCellStack(&state->returnStack, (cell_t)Branch);
    // We are done, return NULL to finish processing this word and move to the next one.
    return NULL;
  }

  // Get the loop counter from the return stack.
  cell_t loopCounter = PopCellStack(&state->returnStack);

  // If it's the sentinel value, the word is the loop count.
  if (loopCounter == -1) {
    cell_t num = (cell_t)atoi(word);
    loopCounter = num; 
  }

  // If the loop counter is zero, we are done.
  if (loopCounter == 0) {
    return NULL;
  }

  // Decrement the loop and update the return stack.
  PushToCellStack(&state->returnStack, loopCounter - 1);
  PushToCellStack(&state->returnStack, (cell_t)Branch);
  return NULL;
}


// ( flag C: "<spaces>number" -- )
// When the flag is false, the branch? word skips the number of words specified by the parsed number.
// When the flag is true, the branch? word does nothing.
char* BranchZ(KernelState *state, char* word) {
  if (word != NULL) {
    // Consume the number and end the word.
    return NULL;
  }

  bool testValue = (bool)PopCellStack(&state->dataStack);
  if (testValue) {
    // We still need to consume the number.
    PushToCellStack(&state->returnStack, (cell_t)BranchZ);
    return NULL;
  }
  else {
    return Branch(state, NULL);
  }

  return NULL;
}
