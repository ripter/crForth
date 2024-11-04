#include "../crForth.h"

//
// WARNING:
// This was moved to Forth code and no longer runs in C.
// Look at src/forth/CoreWords.fth for the Forth implementation.

// ( c-addr u -- )
// TYPE prints the string of length u starting at c-addr.
// https://forth-standard.org/standard/core/TYPE
void Type(KernelState *state) {
  fprintf(state->errorStream, "Error: TYPE is now implemented in Forth.\n");  
  return;
  // // Pop the length from the stack.
  // Cell lengthCell = CellStackPop(&state->dataStack);
  // if (lengthCell.type != CELL_TYPE_NUMBER) {
  //   fprintf(state->errorStream, "Error: TYPE expected a length on the stack.\n");
  //   return;
  // }
  // size_t length = (size_t)lengthCell.value;

  // // Pop the address from the stack.
  // Cell addrCell = CellStackPop(&state->dataStack);
  // if (addrCell.type != CELL_TYPE_ADDRESS) {
  //   fprintf(state->errorStream, "Error: TYPE expected an address on the stack.\n");
  //   return;
  // }
  // char *str = (char *)addrCell.value;

  // // Print the string.
  // for (size_t i = 0; i < length; i++) {
  //   fputc(str[i], state->outputStream);
  // }
}
