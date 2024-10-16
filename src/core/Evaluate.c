#include <raylib.h>
#include "../crForth.h"

// ( c-addr u -- )
// Runs the string on the stack as a Forth program.
// https://forth-standard.org/standard/core/EVALUATE
void Evaluate(KernelState* state) {
  BAIL_IF_DATA_STACK_LESS_THAN(2);
  Cell length = CellStackPop(&state->dataStack);
  Cell address = CellStackPop(&state->dataStack);

  if (length.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, ERR_INVALID_LENGTH);
    return;
  }
  if (length.value == 0) {
    fprintf(state->errorStream, ERR_ZERO_LENGTH);
    return;
  }
  if (address.type != CELL_TYPE_WORD) {
    fprintf(state->errorStream, ERR_INVALID_ADDRESS);
    return;
  }

  cell_t checkedLength = TextLength((const char*)address.value);
  if (length.value != checkedLength) {
    fprintf(state->errorStream, ERR_INVALID_LENGTH);
    return;
  }

  RunForthString(state, (const char *)address.value, length.value);
}
