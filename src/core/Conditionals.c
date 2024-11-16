#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( flag -- )  ( C: -- flag )
// Compilation: ( C: -- OrigSys )
// If flag is false, skip until THEN or ELSE. 
// https://forth-standard.org/standard/core/IF
void IF(KernelState *state) {
  // When in compile mode, postpone the word.
  if (state->IsInCompileMode) {
    AppendWordToString(GetCompileBuffer(state), "if");
    return; 
  }

  OrigSys *origSys = CreateOrigSys();
  // Push the OrigSys struct to the return stack so ELSE and THEN can use it.
  CellStackPush(&state->controlStack, (Cell){(CellValue)origSys, CELL_TYPE_ORIG_SYS});

  // When in compile mode, postpone the word.
  // if (state->IsInCompileMode) {
  //   // printf("\nIF: Found Nested Loop\n");
  //   origSys->isNested = true;
  //   AppendWordToString(GetCompileBuffer(state), "if");
  //   return; 
  // }

  // Pop the flag value and set it in the OrigSys struct.
  Cell flag = CellStackPop(&state->dataStack);
  origSys->flag = flag.value == FFALSE ? false : true;

  // Start compiling to the OrigSys struct.
  state->IsInCompileMode = true;
}

// ( C: orig1 –– orig2 )
// Compilation: ( C: orig1 –– orig2 )
// If the flag is true, skip until THEN.
// https://forth-standard.org/standard/core/ELSE
void ELSE(KernelState *state) {
  Cell cell = CellStackPeekTop(&state->controlStack);
  // If the stack s not an OrigSys, postpone the word.
  if (cell.type != CELL_TYPE_ORIG_SYS) {
    // fprintf(state->errorStream, "ELSE: Expected a flag on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
    AppendWordToString(GetCompileBuffer(state), "else");
    return;
  }
  OrigSys *origSys = (OrigSys *)cell.value;

  // // If this is a nested loop, postpone the word.
  // if (origSys->isNested) {
  //   // printf("\nELSE: Found Nested Loop\n");
  //   AppendWordToString(GetCompileBuffer(state), "else");
  //   return;
  // }

  // If the flag is true, skip until THEN.
  if (origSys->flag) {
    AppendToString(GetCompileBuffer(state), "' then skip ");
    return;
  }

  // Flag is false, so reset the source string to the else code.
  FreeString(origSys->src);
  origSys->src = CreateString("");
  origSys->flag = true; // Changed the flag to true so THEN will run the code.
}

// ( C: OrigSys -- )
// Completes the IF/ELSE words.
// https://forth-standard.org/standard/core/THEN
void THEN(KernelState *state) {
  // if the stack is empty, bail without doing anything.
  if (CellStackSize(&state->controlStack) == 0) {
    return;
  }
  Cell cell = CellStackPop(&state->controlStack);
  // If the type is not an OrigSys, then we need to postpone the word "then".
  if (cell.type != CELL_TYPE_ORIG_SYS) {
    // fprintf(state->errorStream, "THEN: Expected an OrigSys struct on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
    CellStackPush(&state->controlStack, cell); // Put it back on the stack.
    AppendWordToString(GetCompileBuffer(state), "then");
    return;
  }
  OrigSys *origSys = (OrigSys *)cell.value;

  // If this is a nested loop, we need to postpone the word "then" to the current definition.
  if (origSys->isNested) {
    AppendToString(GetCompileBuffer(state), GetStringValue(origSys->src));
    AppendWordToString(GetCompileBuffer(state), "then");
    FreeOrigSys(origSys);
    return;
  }

  // Stop Compile Mode.
  state->IsInCompileMode = false;
  // Check the flag value, do we run the code?
  if (origSys->flag) {
    CellStackPush(&state->controlStack, cell);
    // RunForthOnString(state, origSys->src);
    RunSysBranch(state, &cell);

    (void)CellStackPop(&state->controlStack);
    // printf("THEN: Ran the code src='%s'\n", GetStringValue(origSys->src));
  }

  // Clean up
  FreeOrigSys(origSys);
}

