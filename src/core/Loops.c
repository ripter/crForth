#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( limit index -- ) ( R: -- do-sys ) 
// Set up loop control parameters with index and limit. 
// Anything already on the return stack becomes unavailable until the loop-control parameters are discarded. 
// https://forth-standard.org/standard/core/DO
void DO(KernelState *state) {
  // Create a new DoSys struct to hold the loop control parameters.
  DoSys *doSys = CreateDoSys();

  //
  // Compile Mode
  // When in Compile Mode, postpone thte word "do" to the current definition.
  if (state->IsInCompileMode) {
    printf("DO: already compiling, postponing the word \"do\".\n");
    // Put a nested DoSys struct on the return stack so LOOP can find it.
    // doSys->isNested = true;
    // CellStackPush(&state->returnStack, (Cell){(CellValue)doSys, CELL_TYPE_DOSYS});
    AppendToString(state->compilePtr, "do ");
    return;
  }

  //
  // Interpret Mode
  // Pop the stack to setup the loop control parameters.
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);
  if (index.type != CELL_TYPE_NUMBER || limit.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "DO: Expected two numbers on the data stack, but got \"%s\" and \"%s\".\n", CellTypeToName(index.type), CellTypeToName(limit.type));
    return;
  }
  doSys->limit = limit.value;
  doSys->index = index.value;
  // Push the DoSys struct onto the return stack.
  CellStackPush(&state->returnStack, (Cell){(CellValue)doSys, CELL_TYPE_DOSYS});
  // Start compiling to the DoSys struct.
  state->compilePtr = doSys->loopSrc;
  state->IsInCompileMode = true;
}

// ( -- n )
// n is a copy of the current (innermost) loop index.
// https://forth-standard.org/standard/core/I
void I(KernelState *state) {
  // Loop for the first DoSys struct on the return stack.
  size_t stackSize = CellStackSize(&state->returnStack); 
  if (stackSize == 0) {
    fprintf(state->errorStream, "I: No DoSys struct found on the return stack.\n");
    return;
  }
  for (size_t i=stackSize-1; i >= 0; i--) {
    Cell cell = CellStackPeek(&state->returnStack, i);
    // Skip any non-DoSys structs.
    if (cell.type != CELL_TYPE_DOSYS) {
      continue;
    }
    // Found it! Get the index from the DoSys struct and push it to the data stack.
    DoSys *doSys = (DoSys *)cell.value;
    CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
    break;
  }
}

// ( -- n ) 
// https://forth-standard.org/standard/core/J
void J(KernelState *state) {
  // Loop for the second DoSys struct on the return stack.
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize < 2) {
    fprintf(state->errorStream,
            stackSize == 0
                ? "J: No DoSys struct found on the return stack.\n"
                : "J: Only one DoSys struct found on the return stack.\n");
    return;
  }
  int foundCount = 0;
  for (size_t i = stackSize - 1; i >= 0; i--) {
    Cell cell = CellStackPeek(&state->returnStack, i);
    // Skip any non-DoSys structs.
    if (cell.type != CELL_TYPE_DOSYS) {
      continue;
    }
    // Skip the first DoSys struct.
    if (foundCount == 0) {
      foundCount++;
      continue;
    }
    // Found it! Get the index from the DoSys struct and push it to the data
    // stack.
    DoSys *doSys = (DoSys *)cell.value;
    CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
    break;
  }
}

// (R: do-sys -- )
// Runs the loop body until the index is equal to or greater than the limit.
// https://forth-standard.org/standard/core/LOOP
void LOOP(KernelState *state) {
  // DOs and Colon definitions mean we are in compile mode, or at least it's not useful to check for compile mode.
  // Instead we need to loop through the return stack to find the DoSys struct.
  size_t rstackSize = CellStackSize(&state->returnStack);
  // If there is nothing on the return stack, postpone the word "loop" to the current definition.
  if (rstackSize == 0) {
    printf("LOOP: No DoSys struct found on the return stack.\n");
    AppendToString(state->compilePtr, "loop ");
    return;
  }

  // Get the DoSys struct from the return stack.
  Cell cellDoSys = CellStackPop(&state->returnStack);
  if (cellDoSys.type != CELL_TYPE_DOSYS) {
    fprintf(state->errorStream, "Expected a DoSys struct on the return stack, but got \"%d\".\n", cellDoSys.type);
    return;
  }
  DoSys *doSys = (DoSys *)cellDoSys.value;

  // 
  // Compile Mode
  // Is this a nested loop?
  if (doSys->isNested) {
    // Postpone the word "loop" to the current definition.
    AppendToString(state->compilePtr, "loop ");
    return;
  }

  // 
  // Interpret Mode
  // Stop compiling the loop body.
  state->IsInCompileMode = false;
  // Push the DoSys struct back onto the return stack.
  CellStackPush(&state->returnStack, cellDoSys);
  // Run the loop!
  // index and limit can be modified by the loop body.
  while (doSys->index < doSys->limit) {
    // Run the loop body. This can update the doSys struct.
    RunForthString(state, GetStringValue(doSys->loopSrc), GetStringLength(doSys->loopSrc));
    // Increment the loop index.
    doSys->index += 1;
  }

  // Clean up after the loop.
  // Pop the DoSys struct off the return stack, we are done with it.
  (void)CellStackPop(&state->returnStack);
  // Try to get an outer loop.
  Cell cellOuterDoSys = CellStackPeek(&state->returnStack, 0);
  // Restore the compile pointer to the outer loop or the latest word.
  if (cellOuterDoSys.type == CELL_TYPE_DOSYS) {
    DoSys *outerDoSys = (DoSys *)cellOuterDoSys.value;
    state->compilePtr = outerDoSys->loopSrc;
  } else {
    ForthWord *latestWord = GetLastItemFromDictionary(&state->dict);
    state->compilePtr = latestWord->data;
  }

  // Free the loop body data.
  FreeDoSys(doSys);
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

