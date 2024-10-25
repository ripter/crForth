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
  // String *script = CreateString("1 +");
  AddWordToDictionary(&state.dict, CreateForthWord("test++", (xt_func_ptr)DoForthDataString, false, "1 +"));
  OPEN_STREAM("4 test++");
  DoForth(&state);
  CLOSE_STREAM();

  // TOS should be 4 + 1
  Cell result = CellStackPop(&state.dataStack);
  // mu_assert_int_eq(result == 5, "test++ should add 1 to the top of the stack");
  mu_assert_int_eq(5, result.value);

  // FreeString(script);
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
// Test for HERE word after ALLOT
MU_TEST(here_allot_allocates_space) {
  INIT_TEST_STATE();
  // ForthWord *here = GetItemFromDictionary(&state.dict, HERE_BUFFER_NAME);
  OPEN_STREAM("here 10 allot allot-size");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(1, CellStackSize(&state.dataStack));
  Cell resultSize = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, resultSize.value);
  FREE_TEST_STATE();
}
MU_TEST(here_multiple_calls_return_same_address) {
  INIT_TEST_STATE();
  OPEN_STREAM("here here here");
  DoForth(&state);
  CLOSE_STREAM();
  // Three calls to HERE should return the same address since CREATE has never been called.
  mu_assert_double_eq(3, CellStackSize(&state.dataStack));
  Cell result1 = CellStackPop(&state.dataStack);
  Cell result2 = CellStackPop(&state.dataStack);
  Cell result3 = CellStackPop(&state.dataStack);
  mu_assert_double_eq(result1.value, result2.value);
  mu_assert_double_eq(result2.value, result3.value);
  FREE_TEST_STATE();
}
MU_TEST(here_create_update_here_to_new_address) {
  INIT_TEST_STATE();
  OPEN_STREAM("here create foobar here");
  DoForth(&state);
  CLOSE_STREAM();
  // The second call to HERE should return a different address since CREATE has been called.
  mu_assert_double_eq(2, CellStackSize(&state.dataStack));
  Cell result1 = CellStackPop(&state.dataStack);
  Cell result2 = CellStackPop(&state.dataStack);
  mu_check(result1.value != result2.value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(here_tests) {
  MU_RUN_TEST(here_multiple_calls_return_same_address);
  MU_RUN_TEST(here_create_update_here_to_new_address);
  MU_RUN_TEST(here_allot_allocates_space);
}


//
// ********** EVALUATE **********
MU_TEST(evaluate_string) {
  INIT_TEST_STATE();
  // Add a string to the stack and run it as a Forth program.
  const char* forthString = "10 9 +";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD});
  CellStackPush(&state.dataStack, (Cell){(cell_t)TextLength(forthString), CELL_TYPE_NUMBER});
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(19, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(evaluate_define_word) {
  INIT_TEST_STATE();
  const char* forthString = ": add-two 2 + ; 5 add-two";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD});
  CellStackPush(&state.dataStack, (Cell){(cell_t)TextLength(forthString), CELL_TYPE_NUMBER});
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(7, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(evaluate_undefined_word) {
  INIT_TEST_STATE();
  const char* forthString = "undefined-word";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD});
  CellStackPush(&state.dataStack, (Cell){(cell_t)TextLength(forthString), CELL_TYPE_NUMBER});
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  // Error message has the name in it.
  char expectedError[256];
  snprintf(expectedError, sizeof(expectedError), ERR_UNKNOWN_WORD, forthString);
  VERIFY_ERROR(expectedError)
  FREE_TEST_STATE();
}
MU_TEST(evaluate_missing_length) {
  INIT_TEST_STATE();
  const char* forthString = "10 9 +";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD}); // Only push the string address
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  char expectedError[256];
  snprintf(expectedError, sizeof(expectedError), ERR_MISSING_STACK_VALUES, 2, (cell_t)1);
  VERIFY_ERROR(expectedError)
  FREE_TEST_STATE();
}
MU_TEST(evaluate_missing_address) {
  INIT_TEST_STATE();
  CellStackPush(&state.dataStack, (Cell){(cell_t)10, CELL_TYPE_NUMBER}); // Only push the length
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  char expectedError[256];
  snprintf(expectedError, sizeof(expectedError), ERR_MISSING_STACK_VALUES, 2, (cell_t)1);
  VERIFY_ERROR(expectedError)
  FREE_TEST_STATE();
}
MU_TEST(evaluate_invalid_length_type) {
  INIT_TEST_STATE();
  const char* forthString = "10 9 +";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD}); // Push the string
  CellStackPush(&state.dataStack, (Cell){(cell_t)19, CELL_TYPE_WORD}); // Push invalid length (wrong type)
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_INVALID_LENGTH);
  FREE_TEST_STATE();
}
MU_TEST(evaluate_invalid_length_value) {
  INIT_TEST_STATE();
  const char* forthString = "10 9 +";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD}); // Push the string
  CellStackPush(&state.dataStack, (Cell){TextLength(forthString)+1, CELL_TYPE_NUMBER}); // Wrong length
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_INVALID_LENGTH);
  FREE_TEST_STATE();
}
MU_TEST(evaluate_invalid_address) {
  INIT_TEST_STATE();
  CellStackPush(&state.dataStack, (Cell){(cell_t)42, CELL_TYPE_NUMBER}); // Push invalid address (wrong type)
  CellStackPush(&state.dataStack, (Cell){(cell_t)10, CELL_TYPE_NUMBER}); // Push length
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_INVALID_ADDRESS);
  FREE_TEST_STATE();
}
MU_TEST(evaluate_zero_length) {
  INIT_TEST_STATE();
  const char* forthString = "10 9 +";
  CellStackPush(&state.dataStack, (Cell){(cell_t)forthString, CELL_TYPE_WORD}); // Push valid string address
  CellStackPush(&state.dataStack, (Cell){(cell_t)0, CELL_TYPE_NUMBER}); // Push zero length
  OPEN_STREAM("evaluate");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_ZERO_LENGTH);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(evaluate_tests) {
  MU_RUN_TEST(evaluate_string);
  MU_RUN_TEST(evaluate_define_word);
  MU_RUN_TEST(evaluate_undefined_word);
  MU_RUN_TEST(evaluate_missing_length);
  MU_RUN_TEST(evaluate_missing_address);
  MU_RUN_TEST(evaluate_invalid_length_type);
  MU_RUN_TEST(evaluate_invalid_length_value);
  MU_RUN_TEST(evaluate_invalid_address);
  MU_RUN_TEST(evaluate_zero_length);
}



//
// Run all compile mode tests
bool TestCompileMode(void) {

  MU_RUN_TEST(can_run_forth_from_dictionary);
  MU_RUN_TEST(basic_plus_one_test);
  MU_RUN_TEST(test_create_does);
  MU_RUN_TEST(tick_interpret_mode);
  MU_RUN_TEST(tick_compile_mode);
  MU_RUN_SUITE(evaluate_tests);

  // MU_RUN_SUITE(here_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
