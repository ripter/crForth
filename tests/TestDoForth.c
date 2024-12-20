#include <string.h>
#include <raylib.h>

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"


MU_TEST(basic_64bit_number) {
  KernelState state = {0};
  InitKernelState(&state);

  OPEN_STREAM("4998578416");
  DoForth(&state);
  CLOSE_STREAM();
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(4998578416, result.value);

  FreeKernelState(&state);
}

MU_TEST(can_define_word_and_see_it) {
  INIT_TEST_STATE();

  OPEN_STREAM(": magic 10 9 + ; see magic");
  DoForth(&state);
  CLOSE_STREAM();

  String *actual = StreamToString(state.outputStream);
  const char *expected = "\n: MAGIC\n  10 9 + \n; \n";
  mu_assert_string_eq(expected, GetStringValue(actual));
  FREE_TEST_STATE();
}

MU_TEST(can_include_file) {
  INIT_TEST_STATE();
  OPEN_STREAM("s\" tests/basicTests.fth\" included --test-answer-to-life--");
  DoForth(&state);
  CLOSE_STREAM();
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(42, result.value);
  FREE_TEST_STATE();
}

MU_TEST(can_nest_definitions) {
  INIT_TEST_STATE();
  OPEN_STREAM(": OUTER : INNER + ; INNER ; 10 9 OUTER");
  DoForth(&state);
  CLOSE_STREAM();
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}

//
// Test for the CONSTANT word
MU_TEST(constant_word_definition) {
  INIT_TEST_STATE();
  // Define a constant and use it
  OPEN_STREAM("1234 CONSTANT MYCONST MYCONST");
  DoForth(&state);
  CLOSE_STREAM();
  // Check that the value of the constant was pushed onto the stack
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(1234, result.value);

  FREE_TEST_STATE();
}
// Test for re-using the constant
MU_TEST(constant_word_reuse) {
  INIT_TEST_STATE();
  // Define a constant and use it multiple times
  OPEN_STREAM("5678 CONSTANT ANOTHERCONST ANOTHERCONST ANOTHERCONST");
  DoForth(&state);
  CLOSE_STREAM();
  // Check that the value was pushed twice onto the stack
  mu_assert_double_eq(2, CellStackSize(&state.dataStack));
  Cell result1 = CellStackPop(&state.dataStack);
  Cell result2 = CellStackPop(&state.dataStack);
  mu_assert_double_eq(5678, result1.value);
  mu_assert_double_eq(5678, result2.value);

  FREE_TEST_STATE();
}
// Constant Tests
MU_TEST_SUITE(constant_tests) {
  MU_RUN_TEST(constant_word_definition);
  MU_RUN_TEST(constant_word_reuse);
}


//
// Run all the Tests
//
int TestDoForth(void) {

  MU_RUN_TEST(basic_64bit_number);
  MU_RUN_TEST(can_define_word_and_see_it);
  MU_RUN_SUITE(constant_tests);
  MU_RUN_TEST(can_include_file);
  MU_RUN_TEST(can_nest_definitions);

  MU_REPORT();
  return MU_EXIT_CODE;
}
