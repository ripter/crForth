#include <raylib.h>
#include "../crForth.h"

// ( c-addr u -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state) {
  (void)CellStackPop(&state->dataStack);       // u
  Cell word = CellStackPop(&state->dataStack); // c-addr

  RunForthWord(state, (const char *)word.value);
}
