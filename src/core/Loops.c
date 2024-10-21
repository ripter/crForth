#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( limit index -- ) ( R: -- do-sys ) 
// Set up loop control parameters with index and limit. 
// Anything already on the return stack becomes unavailable until the loop-control parameters are discarded. 
// https://forth-standard.org/standard/core/DO
void DO(KernelState *state) {
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);

  // Create a new DoSys struct to hold the loop control parameters.
  DoSys *doSys = MemAlloc(sizeof(DoSys));
  doSys->limit = limit.value;
  doSys->index = index.value;
  doSys->loopSrc = NULL;

  // Push the DoSys struct onto the return stack.
  CellStackPush(&state->returnStack, (Cell){(cell_t)doSys, CELL_TYPE_DOSYS});

  // We need a new word to compile the loop body into.
  ForthWord loopBody = InitWordMetadata("loop-i-body", (xt_func_ptr)DoForthDataString, false, NULL);
  AddWordToDictionary(&state->dict, loopBody);

  // Start Compiling, this will cause the next words to be "compiled" into the word at the Top of the Dictionary.
  // The Top of the Dictionary is the last word added, which is the loop body.
  state->IsInCompileMode = true;
}

// ( -- n )
// n is a copy of the current (innermost) loop index.
// https://forth-standard.org/standard/core/I
void I(KernelState *state) {
  Cell cellDoSys = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, cellDoSys);
  DoSys *doSys = (DoSys *)cellDoSys.value;
  CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
}


// https://forth-standard.org/standard/core/LOOP
void LOOP_OG(KernelState *state) {
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
  RunForthWord(state, "loop-i-body");

  // Increment the index and push it back onto the return stack.
  // printf("LOOP: Incrementing index\n");
  limit = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, (Cell){index.value + 1, CELL_TYPE_NUMBER});
  // CellStackPush(&state->returnStack, limit);
  // printf("LOOP: Repeat\n");
  // Run Loop again.
  LOOP_OG(state);
}

void LOOP3(KernelState *state) {
  // Stop compiling
  state->IsInCompileMode = false;

  printf("Running LOOP\tReturnStack Size: %ld\n", CellStackSize(&state->returnStack));
  // Run the loop body
  RunForthWord(state, "loop-i-body");

  // Get the loop control parameters from the return stack.
  Cell index = CellStackPop(&state->returnStack);
  Cell limit = CellStackPop(&state->returnStack);
  printf("LOOP:\tlimit: %ld\tindex: %ld\n", limit.value, index.value);

  // Can we exit the loop?
  if (index.value >= limit.value) {
    printf("LOOP: Done\n");
    return;
  }
  printf("LOOP: Again\n");
  // Increment the loop index and push it back onto the return stack.
  CellStackPush(&state->returnStack, limit);
  CellStackPush(&state->returnStack, (Cell){index.value + 1, CELL_TYPE_NUMBER});
  // Run the loop again.
  LOOP3(state);
}

void LOOP(KernelState *state) {
  // Stop compiling the loop body.
  state->IsInCompileMode = false;
  // Get the DoSys struct from the return stack.
  Cell cellDoSys = CellStackPop(&state->returnStack);
  if (cellDoSys.type != CELL_TYPE_DOSYS) {
    fprintf(state->errorStream, "Expected a DoSys struct on the return stack, but got \"%d\".\n", cellDoSys.type);
    return;
  }
  DoSys *doSys = (DoSys *)cellDoSys.value;
  // Grab the recently compiled loop body and put it in the DoSys struct.
  ForthWord *loopBody = GetLastItemFromDictionary(&state->dict);
  // Take ownership of the loop body data.
  doSys->loopSrc = loopBody->data;
  loopBody->data = NULL; // Prevent FreeForthWord from freeing the data.

  // Push the DoSys struct back onto the return stack.
  // This enables other words to access the loop control parameters.
  CellStackPush(&state->returnStack, cellDoSys);

  // Run the loop!
  // index and limit can be modified by the loop body.
  while (doSys->index < doSys->limit) {
    // Run the loop body. This can update the doSys struct.
    RunForthString(state, doSys->loopSrc, TextLength(doSys->loopSrc));
    // Increment the loop index.
    doSys->index += 1;
  }

  // Free the loop body data.
  MemFree(doSys->loopSrc);
  MemFree(doSys);
}

// ( R: limit index -- limit' index' )
// Exit the current loop.
// https://forth-standard.org/standard/core/LEAVE
void Leave(KernelState *state) {
  DoSys *doSys = NULL;
  bool foundDoSys = false;
  // printf("LEAVE\n");
  Cell cell = {0, CELL_TYPE_NUMBER};

  do {
    // If there is nothing left on the stack, bail.
    if (IsCellStackEmpty(&state->returnStack)) {
      fprintf(state->errorStream, "LEAVE: No DoSys struct found on the return stack.\n");
      break;
    }
    // Find the DoSys struct on the return stack.
    cell = CellStackPop(&state->returnStack);
    if (cell.type == CELL_TYPE_DOSYS) {
      doSys = (DoSys *)cell.value;
      foundDoSys = true;
    }
    // We can drop any values on the return stack until we find the DoSys struct.
    else {
      // TODO: cleanup based on the cell type.
    }
  } while (foundDoSys);

  if (foundDoSys) {
    // change the loop control parameters to exit the loop.
    doSys->index = doSys->limit - 1; // -1 because the loop will increment the index.
    // Push the Cell struct back onto the return stack.
    CellStackPush(&state->returnStack, cell);
  }
}

