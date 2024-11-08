#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( limit index -- ) ( R: -- do-sys ) 
// Compilation: ( R: -- do-sys )
// Set up loop control parameters with index and limit. 
// Anything already on the return stack becomes unavailable until the loop-control parameters are discarded. 
// https://forth-standard.org/standard/core/DO
void DO(KernelState *state) {
  DoSys *doSys = CreateDoSys();

  // Is the kernel in compile mode?
  // If so, this is a nested loop, so we need to postpone the word "do" to the current definition.
  // We still need to create the DoSys struct and push it onto the return stack so we can find it later.
  if (state->IsInCompileMode) {
    printf("DO: Found Nested Loop");
    AppendWordToString(state->compilePtr, "do");
    doSys->isNested = true;
    CellStackPush(&state->returnStack, (Cell){(CellValue)doSys, CELL_TYPE_DO_SYS});
    return;
  }

  printf("DO: Setting up Do-Sys");
  //
  // Runtime Mode
  // Pop the stack to setup the loop control parameters.
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);
  if (index.type != CELL_TYPE_NUMBER || limit.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "DO: Expected two numbers on the data stack, but got \"%s\" and \"%s\".\n", CellTypeToName(index.type), CellTypeToName(limit.type));
    return;
  }
  doSys->limit = limit.value;
  doSys->index = index.value;

  // Start compiling to the DoSys struct.
  state->compilePtr = doSys->src;
  state->IsInCompileMode = true;
  // Push the DoSys struct onto the return stack.
  CellStackPush(&state->returnStack, (Cell){(CellValue)doSys, CELL_TYPE_DO_SYS});
}


// (R: DoSys -- | DoSys )
// Compilation: ( R: DoSys -- )
// Runs the loop body until the index is equal to or greater than the limit.
// https://forth-standard.org/standard/core/LOOP
void LOOP(KernelState *state) {
  // Get the DoSys struct from the return stack.
  Cell cellDoSys = CellStackPop(&state->returnStack);
  if (cellDoSys.type != CELL_TYPE_DO_SYS) {
    fprintf(state->errorStream, "Expected a DoSys struct on the return stack, but got \"%d\".\n", cellDoSys.type);
    return;
  }
  DoSys *doSys = (DoSys *)cellDoSys.value;

  // If this is a nested loop, we need to postpone the word "loop" to the current definition.
  // We can free the DoSys struct now, as we are done with it.
  if (doSys->isNested) {
    // printf("LOOP: Found Nested Loop: src=%s\nFreed The DoSys.\n", GetStringValue(doSys->src));
    AppendWordToString(state->compilePtr, "loop");
    FreeDoSys(doSys);
    return;
  }

  // Interpret Mode
  // Stop compiling the loop body.
  state->IsInCompileMode = false;
  // Push the DoSys struct back onto the return stack.
  CellStackPush(&state->returnStack, cellDoSys);

  // Run the loop!
  // index and limit can be modified by the loop body.
  while (doSys->index < doSys->limit) {
    printf("LOOP: Running Loop Body: index=%ld, limit=%ld, src=%s\n", doSys->index, doSys->limit, GetStringValue(doSys->src));
    // Run the loop body. This can update the doSys struct.
    RunForthOnString(state, doSys->src);
    // Increment the loop index.
    doSys->index += 1;
  }

  // Post loop cleanup
  // Pop and Free the DoSys struct.
  (void)CellStackPop(&state->returnStack);
  FreeDoSys(doSys);


  // Peek, is the the top now something we can point the compilePtr at?
  if (CellStackSize(&state->returnStack) == 0) {
    return;
  }
  Cell peekCell = CellStackPeekTop(&state->returnStack);
  if (peekCell.type == CELL_TYPE_DO_SYS) {
    printf("LOOP: Found DoSys struct on the return stack.\n");
    state->compilePtr = ((DoSys *)peekCell.value)->src;
  } else if (peekCell.type == CELL_TYPE_COLON_SYS) {
    printf("LOOP: Found ColonSys struct on the return stack.\n");
    state->compilePtr = ((ColonSys *)peekCell.value)->src;
  }
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
    if (cell.type != CELL_TYPE_DO_SYS) {
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
    if (cell.type != CELL_TYPE_DO_SYS) {
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


// ( R: DoSys -- )
// Exit the current loop.
// This will also destroy any System structs on the return stack until it finds the DoSys struct.
// https://forth-standard.org/standard/core/LEAVE
void Leave(KernelState *state) {
  bool foundDoSys = false;
  // End the current stream/branch/loop.
  fseek(state->inputStream, 0, SEEK_END);

  while (!foundDoSys && CellStackSize(&state->returnStack) > 0) {
    Cell cell = CellStackPop(&state->returnStack);
    if (cell.type == CELL_TYPE_DO_SYS) {
      foundDoSys = true;
      FreeDoSys((DoSys *)cell.value);
    } else if (cell.type == CELL_TYPE_ORIG_SYS) {
      FreeOrigSys((OrigSys *)cell.value);
    } else {
      fprintf(state->errorStream, "LEAVE: Unable to free cell of type '%s'.\n", CellTypeToName(cell.type));
    }
  }
}

