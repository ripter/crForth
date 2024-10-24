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
  if (CellStackSize(&state->returnStack) == 0) {
    fprintf(state->errorStream, "\nI: found empty return stack, nothing to do.\n");
    return;
  }

  // Get the DoSys struct from the return stack and put it back.
  // Maybe in the future, we can just peek at the top of the stack.
  Cell cell = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, cell);
  // Check if the top of the return stack is a DoSys struct.
  if (cell.type != CELL_TYPE_DOSYS) {
    fprintf(state->errorStream, "\nExpected a DoSys struct on the return stack, but got \"%d\".\n", cell.type);
    return;
  }
  // Get the index from the DoSys struct and push it to the data stack.
  DoSys *doSys = (DoSys *)cell.value;
  CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
}

// ( -- n ) 
// https://forth-standard.org/standard/core/J
void J(KernelState *state) {
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize < 2) {
    fprintf(state->errorStream, "\nJ: No outer loop available.\n");
    return;
  }
  int count = 0; // We want to find the 2nd DoSys struct on the return stack.
  for (size_t i=0; i < stackSize; i++) {
    Cell cell = CellStackPeek(&state->returnStack, i);
    // Skip any non-DoSys structs.
    if (cell.type != CELL_TYPE_DOSYS) {
      continue;
    }
    // Skip the first DoSys struct.
    if (count == 0) { 
      count++; 
      continue;
    }
    // Found it! Get the index from the DoSys struct and push it to the data stack.
    DoSys *doSys = (DoSys *)cell.value;
    CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
    printf("J: Found the 2nd DoSys struct on the return stack. Index: %ld\n", doSys->index);
    break;
  }
}

// (R: do-sys -- )
// Runs the loop body until the index is equal to or greater than the limit.
// https://forth-standard.org/standard/core/LOOP
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
  // Remove the loop body from the dictionary.
  RemoveItemFromDictionary(&state->dict, "loop-i-body");

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

  // Pop the DoSys struct off the return stack.
  cellDoSys = CellStackPop(&state->returnStack);
  // Free the loop body data.
  MemFree(doSys->loopSrc);
  MemFree(doSys);
}

// Exit the current loop.
// This will also destroy any System structs on the return stack until it finds the DoSys struct.
// https://forth-standard.org/standard/core/LEAVE
void Leave(KernelState *state) {
  DoSys *doSys = NULL;
  bool foundDoSys = false;
  Cell cell;

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
      // cleanup based on the cell type. Otherwise, we could leak memory.
      if (cell.type == CELL_TYPE_IFSYS) {
        MemFree((IfSys *)cell.value);
      }
    }
  } while (foundDoSys == false);

  if (foundDoSys) {
    // change the loop control parameters to exit the loop.
    doSys->index = doSys->limit - 1; // -1 because the loop will increment the index.
    // Push the Cell struct back onto the return stack.
    CellStackPush(&state->returnStack, cell);
    // Skip to the end
    fseek(state->inputStream, 0, SEEK_END);
  } else {
    printf("LEAVE: No DoSys struct was found on the return stack.\n");
  }
}

