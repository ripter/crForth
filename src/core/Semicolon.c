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

  // Pop the ColonSys from the return stack.
  Cell cell = CellStackPop(&state->returnStack);
  if (cell.type != CELL_TYPE_COLON_SYS) { 
    fprintf(state->errorStream, "Error: Expected ColonSys on return stack, but got %s.\n", CellTypeToName(cell.type));
    return;
  }
  // Clean up the ColonSys.
  ColonSys *colonSys = (ColonSys *)cell.value;
  FreeColonSys(colonSys);

  // Peek, is the the top now something we can point the compilePtr at?
  // This enables nested definitions.
  if (CellStackSize(&state->returnStack) == 0) { return; }
  Cell peekCell = CellStackPeekTop(&state->returnStack);
  if (peekCell.type == CELL_TYPE_COLON_SYS) {
    colonSys = (ColonSys *)peekCell.value;
    state->IsInCompileMode = true;
    state->compilePtr = colonSys->src;
  }
}
