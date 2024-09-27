#include <stdio.h>
#include <stdbool.h>

#include "minunit.h"
#include "Test.h"
#include "../src/main.h"
#include "../src/core/CoreWords.h"
#include "../src/Dictionary.h"
#include "../src/WordMetadata.h"


#define OPEN_STREAM(input) \
  FILE *inputStream = fmemopen(input, strlen(input), "r");

#define CLOSE_STREAM() \
  fclose(inputStream); \


MU_TEST(can_run_forth_from_dictionary) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Add a forth script directly into the dictionary.
  AddWordToDictionary(&state.dict, (WordMetadata){"test++", (xt_func_ptr)DoForthString, false, "1 +"});
  OPEN_STREAM("4 test++");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  // TOS should be 4 + 1
  int result = PopFromCellStack(&state.dataStack);
  // mu_assert_int_eq(result == 5, "test++ should add 1 to the top of the stack");
  mu_assert_int_eq(5, result);

  FreeKernelState(&state);
}


MU_TEST(basic_plus_one_test) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Create a new word ++ that adds 1 to the top of the stack.
  // Try it out with 18 ++.
  // The result should be 19.
  OPEN_STREAM(": ++ 1 + ;  18 ++");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 19);

  FreeKernelState(&state);
}


bool TestCompileMode(void) {

  MU_RUN_TEST(can_run_forth_from_dictionary);
  // MU_RUN_TEST(basic_plus_one_test);

  return MU_EXIT_CODE;
}
