#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( limit index -- ) ( C: -- LoopSys ) 
// Compilation: ( C: -- DoSys )
// Set up loop control parameters with index and limit. 
// Anything already on the return stack becomes unavailable until the loop-control parameters are discarded. 
// https://forth-standard.org/standard/core/DO
void DO(KernelState *state) {
  // Compliaiton Mode postpontes the word.
  if (state->IsInCompileMode) {
    // printf("DO: Compliaiton Mode.\n");
    DoSys *doSys = CreateDoSys();
    CellStackPush(&state->controlStack, (Cell){(CellValue)doSys, CELL_TYPE_DO_SYS});
    AppendWordToString(GetCompileBuffer(state), "do");
    return;
  }

  // printf("DO: Run-time mode.\n");
  // Run-time Mode
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);
  if (index.type != CELL_TYPE_NUMBER || limit.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "DO: Expected two numbers on the data stack, but got \"%s\" and \"%s\".\n", CellTypeToName(index.type), CellTypeToName(limit.type));
    return;
  }
  LoopSys *loopSys = CreateLoopSys(limit.value, index.value);
  CellStackPush(&state->controlStack, (Cell){(CellValue)loopSys, CELL_TYPE_LOOP_SYS});
  state->IsInCompileMode = true;
}

// (C: DoSys -- | DoSys )
// Compilation: ( C: DoSys -- )
// Runs the loop body until the index is equal to or greater than the limit.
// https://forth-standard.org/standard/core/LOOP
void LOOP(KernelState *state) {
  Cell cell = CellStackPop(&state->controlStack);

  // if it's a DoSys struct, postpone the word.
  if (cell.type == CELL_TYPE_DO_SYS) {
    DoSys *doSys = (DoSys *)cell.value;
    // printf("LOOP: Postponing 'loop' to current definition.\n");
    // CellStackPush(&state->controlStack, cell);

    AppendToString(GetCompileBuffer(state), GetStringValue(doSys->src));
    AppendWordToString(GetCompileBuffer(state), "loop");

    FreeDoSys(doSys);
    return;
  }

  // printf("\nLOOP: Running Loop\n");
  // Run-time Mode
  state->IsInCompileMode = false;
  LoopSys *loopSys = (LoopSys *)cell.value;
  // printf("LOOP: src=%s\n", GetStringValue(loopSys->src));

  // Push the LoopSys back on the stack so it can be used by the loop body.
  CellStackPush(&state->controlStack, cell);

  // Run the loop!
  while (loopSys->index < loopSys->limit) {
    // printf("\nLOOP: Running Loop Body: index=%ld, limit=%ld, src=%s\n", loopSys->index, loopSys->limit, GetStringValue(loopSys->src));
    // Run the loop body. This can update the doSys struct.
    // RunForthOnString(state, loopSys->src);
    RunSysBranch(state, &cell);
    // Increment the loop index.
    loopSys->index += 1;
  }

  // Pop and Free the LoopSys struct.
  (void)CellStackPop(&state->controlStack);
  FreeLoopSys(loopSys);
}


void LOOP3(KernelState *state) {
  // Compliaiton Mode postpontes the word.
  if (state->IsInCompileMode) {
    AppendWordToString(GetCompileBuffer(state), "loop");
    Cell cell = CellStackPop(&state->controlStack);
    // Append the src to the compile buffer after popping the DoSys struct.
    AppendToString(GetCompileBuffer(state), GetStringValue(((DoSys *)cell.value)->src));
    FreeDoSys((DoSys *)cell.value);
    return;
  }

  // Run-time Mode
  Cell cell = CellStackPop(&state->returnStack);
  DoSys *doSys = (DoSys *)cell.value;
  printf("Do Loop: index=%ld limit=%ld src=%s\n", doSys->index, doSys->limit, GetStringValue(doSys->src));
}




void DO2(KernelState *state) {
  printf("\nDO: Starting\n");
  Cell controlCell = CellStackPeekTop(&state->controlStack);

  if (controlCell.type == CELL_TYPE_DO_SYS) {
    DoSys *doSys = (DoSys *)controlCell.value;
    printf("DO: Postponing 'do' to current definition.\n");
    AppendWordToString(GetCompileBuffer(state), "do");
    doSys->depth += 1;
    return;
  }

  /*
  // Is the kernel in compile mode?
  // If so, this is a nested loop, so we need to postpone the word "do" to the current definition.
  if (state->IsInCompileMode) {
    // printf("DO: Found Nested Loop\n");
    printf("DO: Postponing 'do' to current definition.\n");
    AppendWordToString(GetCompileBuffer(state), "do");
    doSys->depth += 1;
    // doSys->isNested = true;
    CellStackPush(&state->controlStack, (Cell){(CellValue)doSys, CELL_TYPE_DO_SYS});
    return;
  }
  */


  // printf("DO: Setting up Do-Sys");
  //
  // Runtime Mode
  // Pop the stack to setup the loop control parameters.
  Cell index = CellStackPop(&state->dataStack);
  Cell limit = CellStackPop(&state->dataStack);
  if (index.type != CELL_TYPE_NUMBER || limit.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "DO: Expected two numbers on the data stack, but got \"%s\" and \"%s\".\n", CellTypeToName(index.type), CellTypeToName(limit.type));
    return;
  }
  DoSys *doSys = CreateDoSys();
  doSys->limit = limit.value;
  doSys->index = index.value;

  // printf("DO: limit=%ld, index=%ld\n", doSys->limit, doSys->index);
  // Start compiling to the DoSys struct.
  state->IsInCompileMode = true;
  // Push the DoSys struct onto the return stack.
  CellStackPush(&state->controlStack, (Cell){(CellValue)doSys, CELL_TYPE_DO_SYS});
}


// (C: DoSys -- | DoSys )
// Compilation: ( C: DoSys -- )
// Runs the loop body until the index is equal to or greater than the limit.
// https://forth-standard.org/standard/core/LOOP
void LOOP2(KernelState *state) {
  // printf("\nLOOP: Running Loop\n");
  // Get the DoSys struct from the return stack.
  Cell cellDoSys = CellStackPop(&state->controlStack);
  // If it's not a DoSys struct, postpone the word.
  if (cellDoSys.type != CELL_TYPE_DO_SYS) {
    CellStackPush(&state->controlStack, cellDoSys); // Put it back.
    AppendWordToString(GetCompileBuffer(state), "loop");
    // printf("\nLOOP: Non-DoSys on stack, Postponing 'loop' to current definition. src=%s\n", GetStringValue(((DoSys *)cellDoSys.value)->src));
    // fprintf(state->errorStream, "Expected a DoSys struct on the return stack, but got \"%d\".\n", cellDoSys.type);
    return;
  }
  DoSys *doSys = (DoSys *)cellDoSys.value;
  // printf("\nLOOP: Found DoSys: index=%ld, limit=%ld, depth=%d, src=%s\n", doSys->index, doSys->limit, doSys->depth, GetStringValue(doSys->src));

  // If we are nested, postpone the word.
  if (doSys->depth > 0) {
    // printf("\nLOOP: Postponing 'loop' to current definition. src=%s\n", GetStringValue(((DoSys *)cellDoSys.value)->src));
    CellStackPush(&state->controlStack, cellDoSys);
    AppendWordToString(GetCompileBuffer(state), "loop");
    doSys->depth -= 1;
    return;
  }

  // If this is a nested loop, we need to postpone the word "loop" to the current definition.
  // We can free the DoSys struct now, as we are done with it.
  // if (doSys->isNested) {
  //   // printf("LOOP: Found Nested Loop: src=%s\nFreed The DoSys.\n", GetStringValue(doSys->src));
  //   AppendToString(GetCompileBuffer(state), GetStringValue(doSys->src));
  //   AppendWordToString(GetCompileBuffer(state), "loop");
  //   FreeDoSys(doSys);
  //   return;
  // }

  // Interpret Mode
  // Stop compiling the loop body.
  state->IsInCompileMode = false;
  // Push the DoSys struct back onto the return stack.
  CellStackPush(&state->controlStack, cellDoSys);

  // Run the loop!
  // index and limit can be modified by the loop body.
  while (doSys->index < doSys->limit) {
    // printf("\nLOOP: Running Loop Body: index=%ld, limit=%ld, src=%s\n", doSys->index, doSys->limit, GetStringValue(doSys->src));
    // Run the loop body. This can update the doSys struct.
    // RunForthOnString(state, doSys->src);
    RunSysBranch(state, &cellDoSys);
    // Increment the loop index.
    doSys->index += 1;
    // printf("\nLOOP: Loop Body Finished, Incremented Index index=%ld, limit=%ld, src=%s\n", doSys->index, doSys->limit, GetStringValue(doSys->src));
  }

  // printf("LOOP: Loop Finished: Freeing DoSys\n");
  // Post loop cleanup
  // Pop and Free the DoSys struct.
  (void)CellStackPop(&state->controlStack);
  FreeDoSys(doSys);
}



// ( -- n )
// n is a copy of the current (innermost) loop index.
// https://forth-standard.org/standard/core/I
void I(KernelState *state) {
  Cell cell = CellStackPeekTop(&state->controlStack);

  if (cell.type != CELL_TYPE_LOOP_SYS) {
    fprintf(state->errorStream, "I: Expected a LoopSys struct on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
    return;
  }

  LoopSys *loopSys = (LoopSys *)cell.value;
  CellStackPush(&state->dataStack, (Cell){loopSys->index, CELL_TYPE_NUMBER});
  // // Loop for the first DoSys struct on the return stack.
  // size_t stackSize = CellStackSize(&state->controlStack); 
  // if (stackSize == 0) {
  //   fprintf(state->errorStream, "I: Control stack is empty.\n");
  //   return;
  // }
  // for (size_t i=stackSize-1; i >= 0; i--) {
  //   Cell cell = CellStackPeek(&state->controlStack, i);
  //   // Skip any non-DoSys structs.
  //   if (cell.type != CELL_TYPE_DO_SYS) {
  //     continue;
  //   }
  //   // Found it! Get the index from the DoSys struct and push it to the data stack.
  //   DoSys *doSys = (DoSys *)cell.value;
  //   CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
  //   break;
  // }
}

// ( -- n ) 
// https://forth-standard.org/standard/core/J
void J(KernelState *state) {
  // Loop for the second DoSys struct on the return stack.
  size_t stackSize = CellStackSize(&state->controlStack);
  if (stackSize < 2) {
    fprintf(state->errorStream,
            stackSize == 0
                ? "J: No DoSys struct found on the return stack.\n"
                : "J: Only one DoSys struct found on the return stack.\n");
    return;
  }
  int foundCount = 0;
  for (size_t i = stackSize - 1; i >= 0; i--) {
    Cell cell = CellStackPeek(&state->controlStack, i);
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
  // DebugStream(state->inputStream);
  // End the current stream/branch/loop.
  // fseek(state->inputStream, 0, SEEK_END);

  // printf("LEAVE: Free DoSys struct.\n");
  while (!foundDoSys && CellStackSize(&state->controlStack) > 0) {
    Cell cell = CellStackPop(&state->controlStack);
    // printf("\nLEAVE: Freeing cell of type '%s'.\n", CellTypeToName(cell.type));
    if (cell.type == CELL_TYPE_DO_SYS) {
      foundDoSys = true;
      DoSys *doSys = (DoSys *)cell.value; 
      doSys->index = doSys->limit;
      fseek(doSys->stream, 0, SEEK_END);
    } else if (cell.type == CELL_TYPE_ORIG_SYS) {
      fseek(((OrigSys *)cell.value)->stream, 0, SEEK_END);
      // printf("\nLEAVE: Free OrigSys struct.\n");
      // FreeOrigSys((OrigSys *)cell.value);
    } else {
      fprintf(state->errorStream, "\nLEAVE: Unable to free cell of type '%s'.\n", CellTypeToName(cell.type));
    }
  }
}

