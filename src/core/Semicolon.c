#include "../crForth.h"

// ( R: colon-sys -- ) 
// Stops Compile Mode and consumes the ColonSys.
// https://forth-standard.org/standard/core/Semi
void SemiColon(KernelState *state) {
  // If the stack is empty, there is nothing to clean up.
  size_t stackSize = CellStackSize(&state->controlStack);
  if (stackSize == 0) { 
    // printf("SemiColon: No Sys structs on control stack.\n");
    // Stop Compile Mode.
    state->IsInCompileMode = false;
    return; 
  }

  // Close the current ColonSys.
  // Free any Sys structs on the control stack until a ColonSys is found.
  bool foundColonSys = false;
  while (!foundColonSys && CellStackSize(&state->controlStack) > 0) {
    Cell cell = CellStackPop(&state->controlStack);
    // printf("SemiColon: Freeing cell of type '%s'.\n", CellTypeToName(cell.type));
    //TODO: Refactor this Sys cleanup into a function.
    if (cell.type == CELL_TYPE_COLON_SYS) {
      foundColonSys = true;
      FreeColonSys((ColonSys *)cell.value);
    } else if (cell.type == CELL_TYPE_DO_SYS) {
      FreeDoSys((DoSys *)cell.value);
    } else if (cell.type == CELL_TYPE_ORIG_SYS) {
      FreeOrigSys((OrigSys *)cell.value);
    } else {
      fprintf(state->errorStream, "SemiColon: Unable to free cell of type '%s'.\n", CellTypeToName(cell.type));
    }
  }

  // If the Control Stack is empty, we can stop compile mode.
  if (CellStackSize(&state->controlStack) == 0) {
    state->IsInCompileMode = false;
    return;
  }
}
