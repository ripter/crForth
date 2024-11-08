#include "../crForth.h"


// ( -- xt ) ( R: -- colon-sys )
// Create an execution token xt, enter compilation state and start the current definition, producing colon-sys.
// https://forth-standard.org/standard/core/ColonNONAME
void ColonNONAME(KernelState *state) {
  ColonSys *colonSys = CreateColonSys(":noname", CreateString(""));
  // Put the ColonSys on the return stack.
  CellStackPush(&state->controlStack, (Cell){(CellValue)colonSys, CELL_TYPE_COLON_SYS});
  // Put the execution token on the data stack.
  CellStackPush(&state->dataStack, (Cell){(CellValue)colonSys->src, CELL_TYPE_XT});
  // Enter compilation state and compile to the colon-sys.
  state->IsInCompileMode = true;
}
