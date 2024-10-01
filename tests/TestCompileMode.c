#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"

#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");                     \
  state.inputStream = inputStream;

#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \
  state.inputStream = NULL;


MU_TEST(can_run_forth_from_dictionary) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Add a forth script directly into the dictionary.
  char *script = MemAlloc(100);
  strcpy(script, "1 +");
  AddWordToDictionary(&state.dict, InitWordMetadata("test++", (xt_func_ptr)DoForthString, false, script));
  OPEN_STREAM("4 test++");
  DoForth(&state);
  CLOSE_STREAM();

  // TOS should be 4 + 1
  int result = PopFromCellStack(&state.dataStack);
  // mu_assert_int_eq(result == 5, "test++ should add 1 to the top of the stack");
  mu_assert_int_eq(5, result);

  // This will also free the script buffer.
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
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 19);

  FreeKernelState(&state);
}

MU_TEST(test_create_does) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  OPEN_STREAM("create my-test does> 2 3 4 + + ;\n my-test")
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 9);

  FreeKernelState(&state);
}

bool TestCompileMode(void) {

  MU_RUN_TEST(can_run_forth_from_dictionary);
  MU_RUN_TEST(basic_plus_one_test);
  MU_RUN_TEST(test_create_does);

  MU_REPORT();
  return MU_EXIT_CODE;
}
