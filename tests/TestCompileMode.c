#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"


MU_TEST(can_run_forth_from_dictionary) {
  INIT_TEST_STATE();

  // Add a forth script directly into the dictionary.
  char *script = MemAlloc(100);
  strcpy(script, "1 +");
  AddWordToDictionary(&state.dict, InitWordMetadata("test++", (xt_func_ptr)DoForthDataString, false, script));
  OPEN_STREAM("4 test++");
  DoForth(&state);
  CLOSE_STREAM();

  // TOS should be 4 + 1
  int result = PopFromCellStack(&state.dataStack);
  // mu_assert_int_eq(result == 5, "test++ should add 1 to the top of the stack");
  mu_assert_int_eq(5, result);

  FREE_TEST_STATE();
}

MU_TEST(basic_plus_one_test) {
  INIT_TEST_STATE();

  // Create a new word ++ that adds 1 to the top of the stack.
  // Try it out with 18 ++.
  // The result should be 19.
  OPEN_STREAM(": ++ 1 + ;  18 ++");
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 19);

  FREE_TEST_STATE();
}

MU_TEST(test_create_does) {
  INIT_TEST_STATE();

  OPEN_STREAM("create my-test does> 2 3 4 + + ;\n my-test")
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 9);

  FREE_TEST_STATE();
}


MU_TEST(tick_interpret_mode) {
  INIT_TEST_STATE();
  OPEN_STREAM(": foobar 10 9 ; ' foobar execute +");
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 19);
  FREE_TEST_STATE();
}

MU_TEST(tick_compile_mode) {
  INIT_TEST_STATE();

  OPEN_STREAM(" \
  : foobar 10 9 ; \
  : test-compile ' execute ;  \
  test-compile foobar +");
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_assert_double_eq(19, result);
  FREE_TEST_STATE();
}



//
// Run all compile mode tests
bool TestCompileMode(void) {

  MU_RUN_TEST(can_run_forth_from_dictionary);
  MU_RUN_TEST(basic_plus_one_test);
  MU_RUN_TEST(test_create_does);
  MU_RUN_TEST(tick_interpret_mode);
  MU_RUN_TEST(tick_compile_mode);

  MU_REPORT();
  return MU_EXIT_CODE;
}
