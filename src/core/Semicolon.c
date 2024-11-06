#include "../crForth.h"

// ( R: colon-sys -- ) 
// Stops Compile Mode and consumes the ColonSys.
// https://forth-standard.org/standard/core/Semi
void SemiColon(KernelState *state) {
  // Stop Compile Mode.
  state->IsInCompileMode = false;

  // if the return stack is empty, there is nothing to clean up.
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize == 0) { return; }

  // Pop until we find a ColonSys.
  ColonSys *colonSys = NULL;
  Cell cellResult;
  while (CellStackSize(&state->returnStack) > 0) {
    cellResult = CellStackPop(&state->returnStack);
    if (cellResult.type == CELL_TYPE_COLON_SYS) {
      colonSys = (ColonSys *)cellResult.value;
      break;
    }
  }

  // Clean up the ColonSys.
  FreeColonSys(colonSys);
}
