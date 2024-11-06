#include "../crForth.h"

// ( R: colon-sys -- ) 
// Stops Compile Mode and consumes the ColonSys.
// https://forth-standard.org/standard/core/Semi
void SemiColon(KernelState *state) {
  // Stop Compile Mode.
  state->IsInCompileMode = false;

  // Pop until we find a ColonSys.
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize == 0) { return; }

  ColonSys *colonSys = NULL;
  Cell cellResult;
  while (CellStackSize(&state->returnStack) > 0) {
    cellResult = CellStackPop(&state->returnStack);
    if (cellResult.type == CELL_TYPE_COLON_SYS) {
      colonSys = (ColonSys *)cellResult.value;
      break;
    }
  }

  // do {
  //   cellResult = CellStackPop(&state->returnStack);
  //   if (cellResult.type == CELL_TYPE_COLON_SYS) {
  //     colonSys = (ColonSys *)cellResult.value;
  //     break;
  //   }
  // } while(CellStackSize(&state->returnStack) > 0);
  // do {
  //   cellResult = CellStackPop(&state->returnStack);
  //   if (cellResult.type == CELL_TYPE_COLON_SYS) {
  //     colonSys = (ColonSys *)cellResult.value;
  //     break;
  //   }
  // } while (CellStackSize(&state->returnStack) > 0);

  // Clean up the ColonSys.
  FreeColonSys(colonSys);
}
