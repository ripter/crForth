#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( limit index -- ) ( R: -- loop-sys ) 
// Set up loop control parameters with index and limit. 
// Anything already on the return stack becomes unavailable until the loop-control parameters are discarded. 
// https://forth-standard.org/standard/core/DO
void DO(KernelState *state) {
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);
  // printf("DO:\tlimit: %ld\tindex: %ld\n", limit.value, index.value);

  CellStackPush(&state->returnStack, limit);
  CellStackPush(&state->returnStack, index);

  // We need a new word to compile the loop body into.
  ForthWord loopBody = InitWordMetadata("loop-i-body", (xt_func_ptr)DoForthDataString, false, NULL);
  AddWordToDictionary(&state->dict, loopBody);
  // Start Compiling, this will cause the next words to be "compiled" into the word at the Top of the Dictionary.
  state->IsInCompileMode = true;
}

// ( -- n )
// n is a copy of the current (innermost) loop index.
// https://forth-standard.org/standard/core/I
void I(KernelState *state) {
  Cell index = CellStackPop(&state->returnStack);
  CellStackPush(&state->dataStack, index);
  CellStackPush(&state->returnStack, index);
  // printf("I: %ld\n", index.value);
}


// https://forth-standard.org/standard/core/LOOP
void LOOP(KernelState *state) {
  // Stop compiling
  state->IsInCompileMode = false;

  // Pop the loop control parameters from the return stack.
  Cell index = CellStackPop(&state->returnStack);
  Cell limit = CellStackPop(&state->returnStack);
  // printf("LOOP:\tlimit: %ld\tindex: %ld\n", limit.value, index.value);

  // Check if the loop is done.
  if (index.value >= limit.value) {
    // printf("LOOP: Done\n");
    // Nothing left to do, return.
    return;
  }
  // printf("LOOP: Running loop body\n");
  // Put the limit and index back on the return stack for the loop body.
  CellStackPush(&state->returnStack, limit);
  CellStackPush(&state->returnStack, index);
  // Run the loop body again.
  ForthWord *loopBody = GetItemFromDictionary(&state->dict, "loop-i-body");
  loopBody->func(state);

  // Increment the index and push it back onto the return stack.
  // printf("LOOP: Incrementing index\n");
  limit = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, (Cell){index.value + 1, CELL_TYPE_NUMBER});
  // CellStackPush(&state->returnStack, limit);

  // printf("LOOP: Repeat\n");
  // Run Loop again.
  LOOP(state);
}
