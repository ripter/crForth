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
    AppendToString(GetCompileBuffer(state), GetStringValue(doSys->src));
    AppendWordToString(GetCompileBuffer(state), "loop");
    FreeDoSys(doSys);
    return;
  }

  // Run-time Mode
  state->IsInCompileMode = false;
  LoopSys *loopSys = (LoopSys *)cell.value;
  // Push the LoopSys back on the stack so it can be used by the loop body.
  CellStackPush(&state->controlStack, cell);

  // Run the loop!
  while (loopSys->index < loopSys->limit) {
    RunSysBranch(state, &cell);
    loopSys->index += 1;
  }

  // Pop and Free the LoopSys struct.
  (void)CellStackPop(&state->controlStack);
  FreeLoopSys(loopSys);
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
}

// ( -- n ) 
// n is a copy of the next-outer loop index.
// https://forth-standard.org/standard/core/J
void J(KernelState *state) {
  const size_t stackSize = CellStackSize(&state->controlStack);
  // printf("J: Control stack size: %ld\n", stackSize);
  Cell cell = CellStackPeek(&state->controlStack, stackSize-2);
  // printf("J: Cell type: %s\n", CellTypeToName(cell.type));
  LoopSys *loopSys = (LoopSys *)cell.value;
  // printf("J: LoopSys index: %ld\n", loopSys->index);
  CellStackPush(&state->dataStack, (Cell){loopSys->index, CELL_TYPE_NUMBER});
}

// void J2(KernelState *state) {
//   // Loop for the second DoSys struct on the return stack.
//   size_t stackSize = CellStackSize(&state->controlStack);
//   if (stackSize < 2) {
//     fprintf(state->errorStream,
//             stackSize == 0
//                 ? "J: No DoSys struct found on the return stack.\n"
//                 : "J: Only one DoSys struct found on the return stack.\n");
//     return;
//   }
//   int foundCount = 0;
//   for (size_t i = stackSize - 1; i >= 0; i--) {
//     Cell cell = CellStackPeek(&state->controlStack, i);
//     // Skip any non-DoSys structs.
//     if (cell.type != CELL_TYPE_DO_SYS) {
//       continue;
//     }
//     // Skip the first DoSys struct.
//     if (foundCount == 0) {
//       foundCount++;
//       continue;
//     }
//     // Found it! Get the index from the DoSys struct and push it to the data
//     // stack.
//     DoSys *doSys = (DoSys *)cell.value;
//     CellStackPush(&state->dataStack, (Cell){doSys->index, CELL_TYPE_NUMBER});
//     break;
//   }
// }


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

