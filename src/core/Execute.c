#include <raylib.h>
#include "../crForth.h"

// ( XT -- )
// Pop the string on the stack as a Forth word and run it.
// https://forth-standard.org/standard/core/EXECUTE
void Execute(KernelState *state) {
  Cell cell = CellStackPop(&state->dataStack); 

  if (cell.type != CELL_TYPE_XT) {
    fprintf(state->errorStream, "Error: Expected XT, got %d\n", cell.type);
    return;
  }

  // RunForthWord(state, (const char *)word.value);
  RunForthOnString(state, (String *)cell.value);
}
