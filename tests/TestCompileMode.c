#include <stdio.h>
#include <stdbool.h>

#include "minunit.h"
#include "Test.h"
#include "../src/main.h"
#include "../src/core/CoreWords.h"


#define OPEN_STREAM(input) \
  FILE *inputStream = fmemopen(input, strlen(input), "r");

#define CLOSE_STREAM() \
  fclose(inputStream); \


MU_TEST(basic_plus_one_test) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Create a new word ++ that adds 1 to the top of the stack.
  // Try it out with 18 ++.
  // The result should be 19.
  OPEN_STREAM(": ++ 1 add ;  18 ++");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  cell_t result = PopCellStack(&state.dataStack);
  mu_check(result == 19);
}


bool TestCompileMode(void) {

  MU_RUN_TEST(basic_plus_one_test);

  return MU_EXIT_CODE;
}
