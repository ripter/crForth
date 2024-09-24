#include "../KernelState.h"

// ( C: "<spaces>number --" )
// Parse a number delimited by a space and skip the number of words specified by the parsed number.
// Branch is an immediate word that controls the flow by skipping words.
char* Branch(KernelState *state, char* word) {
  // first time we are called, we need to initialize the loop.
  if (word == NULL) {
    PushCellStack(&state->returnStack, -1); // Sentinel value for the loop counter.
    PushCellStack(&state->returnStack, (cell_t)Branch);
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
  PushCellStack(&state->returnStack, loopCounter - 1);
  PushCellStack(&state->returnStack, (cell_t)Branch);
  return NULL;
}



// Branch if the top of the stack is not zero.
// Branch is an immediate word.
char* BranchNZ(KernelState *state, char* word) {
  (void)word;
  bool testValue = (bool)PopCellStack(&state->dataStack);

  if (testValue) {
    printf("BranchNZ: Running the branch code.\n");
    return NULL;
  }
  else {
    printf("BranchNZ: Skipping branch code.\n");
    return Branch(state, NULL);
  }

  return NULL;
}
