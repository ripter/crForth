#include "../KernelState.h"

// Branch is an immediate word.
char* Branch(KernelState *state, char* word) {
  (void)state; // Unused
  (void)word; // Unused
  return NULL;
}

// Branch if the top of the stack is not zero.
// Branch is an immediate word.
char* BranchNZ(KernelState *state, char* word) {
  // If there is no control word, initalize the "loop" by pushing two values, (shouldRun, loopCount).
  if (state->controlWord == NULL) {
    state->controlWord = word;
    // When we do know the count, do we run the word?
    cell_t top = PopCellStack(&state->dataStack);
    // Not Zero? Run the word.
    if (top != 0) {
      PushCellStack(&state->returnSack, true);
    } else {
      PushCellStack(&state->returnSack, false);
    }
    // We do not know the loop counter yet, so put a special value on the return stack.
    PushCellStack(&state->returnSack, -1);
    return NULL;
  }

  // Get the LoopCount from the Return Stack.
  cell_t loopCounter = PopCellStack(&state->returnSack);

  // The first word after us is the loop counter,
  // to find it, look for the special value on the return stack.
  if (loopCounter == -1) {
    cell_t num = (cell_t)atoi(word);
    PushCellStack(&state->returnSack, num);
    return NULL;
  }

  // Get the shouldRun from the Return Stack.
  bool shouldRun = (bool)PopCellStack(&state->returnSack);

  // If the loop counter is zero, we are done.
  if (loopCounter == 0) {
    state->controlWord = NULL;
    return NULL;
  }

  // Push the shouldRun back on the return stack.
  PushCellStack(&state->returnSack, shouldRun);
  // Decrement the loop counter and put it back on the return stack.
  PushCellStack(&state->returnSack, loopCounter - 1);

  // If the top of the stack is not zero, return the word to execute.
  if (shouldRun) {
    return word;
  }
  // else, skip the word.
  return NULL;
}
