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
  Cell result = CellStackPop(&state.dataStack);
  // mu_assert_int_eq(result == 5, "test++ should add 1 to the top of the stack");
  mu_assert_int_eq(5, result.value);

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

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}

MU_TEST(test_create_does) {
  INIT_TEST_STATE();

  OPEN_STREAM("create my-test does> 2 3 4 + + ;\n my-test")
  DoForth(&state);
  CLOSE_STREAM();

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(9, result.value);
  FREE_TEST_STATE();
}


MU_TEST(tick_interpret_mode) {
  INIT_TEST_STATE();
  OPEN_STREAM(": foobar 10 9 ; ' foobar execute +");
  DoForth(&state);
  CLOSE_STREAM();

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
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

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}


//
// ********** HERE **********
// Does the word HERE return a valid address?
MU_TEST(here_inside_word_returns_valid_address) {
  INIT_TEST_STATE();
  OPEN_STREAM(": foobar here ; foobar");
  DoForth(&state);
  CLOSE_STREAM();

  mu_check(CellStackSize(&state.dataStack) == 1);
  Cell result = CellStackPop(&state.dataStack);
  mu_check(result.type == CELL_TYPE_ADDRESS);
  mu_check(result.value != 0);  // Ensure HERE returns a valid address
  FREE_TEST_STATE();
}
MU_TEST(test_here_word) {
  INIT_TEST_STATE();
  OPEN_STREAM("here");
  DoForth(&state);
  CLOSE_STREAM();

  mu_check(CellStackSize(&state.dataStack) == 1);
  Cell result = CellStackPop(&state.dataStack);
  mu_check(result.type == CELL_TYPE_ADDRESS);
  mu_check(result.value != 0);  // Ensure HERE returns a valid address
  FREE_TEST_STATE();
}
// Test for HERE word after ALLOT
MU_TEST(test_here_after_allot) {
  INIT_TEST_STATE();
  OPEN_STREAM("here 10 allot here swap -");
  DoForth(&state);
  CLOSE_STREAM();

  mu_check(CellStackSize(&state.dataStack) == 1);
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, result.value);  // Difference should be 10 after allotting
  FREE_TEST_STATE();
}

MU_TEST_SUITE(here_tests) {
  MU_RUN_TEST(here_inside_word_returns_valid_address);
  MU_RUN_TEST(test_here_word);
  MU_RUN_TEST(test_here_after_allot);
}



//
// Run all compile mode tests
bool TestCompileMode(void) {

  MU_RUN_TEST(can_run_forth_from_dictionary);
  MU_RUN_TEST(basic_plus_one_test);
  MU_RUN_TEST(test_create_does);
  MU_RUN_TEST(tick_interpret_mode);
  MU_RUN_TEST(tick_compile_mode);

  // TODO: make sure we know how HERE is supposed to work.
  MU_RUN_SUITE(here_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
