#include "../crForth.h"

// ( R: colon-sys -- ) 
// Stops Compile Mode and consumes the ColonSys.
// https://forth-standard.org/standard/core/Semi
void SemiColon(KernelState *state) {
  // Stop Compile Mode.
  state->IsInCompileMode = false;

  // If the return stack is empty, there is nothing to clean up.
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize == 0) { return; }

  // Close the current ColonSys.
  // If there are any other Sys on the return stack, free them.
  bool foundColonSys = false;
  while (!foundColonSys && CellStackSize(&state->returnStack) > 0) {
    Cell cell = CellStackPop(&state->returnStack);
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

  // Peek, is the the top now something we can point the compilePtr at?
  // This enables nested definitions.
  if (CellStackSize(&state->returnStack) == 0) { return; }
  Cell peekCell = CellStackPeekTop(&state->returnStack);
  if (peekCell.type == CELL_TYPE_COLON_SYS) {
    ColonSys *colonSys = (ColonSys *)peekCell.value;
    state->IsInCompileMode = true;
    state->compilePtr = colonSys->src;
  }
}
