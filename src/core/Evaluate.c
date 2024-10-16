#include <raylib.h>
#include "../crForth.h"

// ( c-addr u -- )
// Runs the string on the stack as a Forth program.
// https://forth-standard.org/standard/core/EVALUATE
void Evaluate(KernelState* state) {
  (void)state;
  Cell length = CellStackPop(&state->dataStack);
  Cell address = CellStackPop(&state->dataStack);

  RunForthString(state, (const char *)address.value, length.value);
}
