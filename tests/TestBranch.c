#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"

//
// ********** Skip Tests **********
MU_TEST(skip_basic_test) {
  INIT_TEST_STATE();
  // Add sentinel value (19), skip 3 words, resulting in nothing being added to the stack.
  OPEN_STREAM("19 3 skip 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();
  // Check that the TOS is still our sentinel value.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}
MU_TEST(skip_on_empty_stack_test) {
  INIT_TEST_STATE();
  // branch should skip 3 words, resulting in nothing being added to the stack.
  OPEN_STREAM("3 skip 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();
  // stack should still be empty.
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}
MU_TEST(skip_0_basic) {
  INIT_TEST_STATE();
  // n1 is 0, n2 is 3, so 0skip should skip 3 words (4, 5, +), leaving the stack empty.
  OPEN_STREAM("0 3 0skip 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}
MU_TEST(skip_0_no_skip) {
  INIT_TEST_STATE();
  // n1 is non-zero (5), so 0skip should not skip any words and proceed with the rest of the code.
  OPEN_STREAM("5 3 0skip 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();
  // Stack should have the result of 4 + 5.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(9, result.value);
  FREE_TEST_STATE();
}
MU_TEST(skip_0_no_skip_single_word) {
  INIT_TEST_STATE();
  // n1 is non-zero (3), so 0skip should not skip any words.
  // The word "10" should be added to the stack.
  OPEN_STREAM("3 1 0skip 10");
  DoForth(&state);
  CLOSE_STREAM();
  // The stack should contain 10.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, result.value);
  FREE_TEST_STATE();
}
MU_TEST(skip_0_with_negative_skip) {
  INIT_TEST_STATE();
  // -1 is not a valid number of words to skip.
  OPEN_STREAM("0 -1 10 9 +");
  DoForth(&state);
  CLOSE_STREAM();
  // The stack should remain unchanged, and the result of 9 + 10 should still be present.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(skip_tests) {
  MU_RUN_TEST(skip_basic_test);
  MU_RUN_TEST(skip_on_empty_stack_test);
  MU_RUN_TEST(skip_0_basic);
  MU_RUN_TEST(skip_0_no_skip);
  MU_RUN_TEST(skip_0_no_skip_single_word);
  MU_RUN_TEST(skip_0_with_negative_skip);
}



MU_TEST(xt_skip_will_skip_the_stream_forward) {
  INIT_TEST_STATE();
  // Define a word that will skip 3 words, then add 4 and 5 to the stack.
  OPEN_STREAM("10 9 ' then skip 4 + then +");
  DoForth(&state);
  CLOSE_STREAM();
  // The stack should contain 9.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(skip_tests2) {
  MU_RUN_TEST(xt_skip_will_skip_the_stream_forward);
}




//
// ********** Branch Tests **********
MU_TEST(branch_jump_1) {
  INIT_TEST_STATE();
  // Push the XT for the "+" word to the return stack.
  String *branchWord = CreateString("+");
  CellStackPush(&state.returnStack, (Cell){(CellValue)branchWord, CELL_TYPE_XT}); // address
  // Because the address on the returnStack is "+", the branch should execute the + word.
  OPEN_STREAM("10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FreeString(branchWord);
  FREE_TEST_STATE();
}
MU_TEST(branch_with_empty_return_stack) {
  INIT_TEST_STATE();
  OPEN_STREAM("10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  String *error = StreamToString(state.errorStream);
  mu_assert_string_eq(ERR_MISSING_XT_DUE_TO_EMPTY_STACK, GetStringValue(error));
  FreeString(error);
  FREE_TEST_STATE();
}
MU_TEST(branch_with_invalid_address) {
  INIT_TEST_STATE();
  // 27 is not a valid address, so the branch should fail.
  OPEN_STREAM("27 >r 10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  String *error = StreamToString(state.errorStream);
  VERIFY_ERROR("Error 014: Expected XT, got NUMBER instead.\n");
  FreeString(error);
  FREE_TEST_STATE();
}
MU_TEST(branchnz_basic_true) {
  INIT_TEST_STATE();
  OPEN_STREAM("' + >r 10 9 -1 ?branch");
  DoForth(&state);
  CLOSE_STREAM();
  String *error = StreamToString(state.errorStream);
  mu_assert_string_eq("", GetStringValue(error));
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}
MU_TEST(branchnz_basic_false) {
  INIT_TEST_STATE();
  OPEN_STREAM("' + >r >r 10 9 0 ?branch");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(CellStackSize(&state.dataStack) == 2);
  mu_assert_double_eq(9, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(10, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(branch_jump_test) {
  INIT_TEST_STATE();

  // define two words, foo and bar, then jump to foo via branchr.
  OPEN_STREAM(": foo 10 ; : bar 9 ; ' foo >r branch");
  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that 10 is left on the stack as branch executed the word at the return stack address.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, result.value);
  FREE_TEST_STATE();
}
MU_TEST(tick_c_word) {
  INIT_TEST_STATE();
  OPEN_STREAM("' +");
  DoForth(&state);
  CLOSE_STREAM();

  // Tick should push the execution token of the word "+" to the stack.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(CELL_TYPE_XT, result.type);
  mu_assert_string_eq("+", GetStringValue((String *)result.value));
  FREE_TEST_STATE();
}
MU_TEST(tick_and_execute) {
  INIT_TEST_STATE();
  // ' xyz EXECUTE is equivalent to xyz
  // Define the xyz word, then try to call it with tick and execute.
  OPEN_STREAM(": xyz 10 9 + ;");
  DoForth(&state);
  // Verify Stack is empty
  mu_assert(IsCellStackEmpty(&state.dataStack), "Stack should be empty.");

  // Try running the word with tick and execute.
  REOPEN_STREAM("' xyz EXECUTE");
  DoForth(&state);
  CLOSE_STREAM();

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}
MU_TEST(latest_and_execute) {
  INIT_TEST_STATE();
  OPEN_STREAM(": foobar 10 9 + ; latest execute");
  DoForth(&state);
  CLOSE_STREAM();

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(branch_tests) {
  MU_RUN_TEST(branch_jump_1);
  MU_RUN_TEST(branch_with_empty_return_stack);
  MU_RUN_TEST(branch_with_invalid_address);
  MU_RUN_TEST(branchnz_basic_true);
  MU_RUN_TEST(branchnz_basic_false);
  MU_RUN_TEST(tick_c_word);
  MU_RUN_TEST(tick_and_execute);
  MU_RUN_TEST(latest_and_execute);
  MU_RUN_TEST(branch_jump_test);
}


//
// ********** IF ELSE THEN **********
MU_TEST(if_then_true) {
  INIT_TEST_STATE();
  OPEN_STREAM("1 IF 10 9 + THEN");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(CellStackSize(&state.dataStack) == 1);
  mu_assert_double_eq(19, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(if_then_false) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 IF 10 9 + THEN");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}
MU_TEST(if_else_then_true) {
  INIT_TEST_STATE();
  OPEN_STREAM("1 IF 10 9 + ELSE 5 4 + THEN");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(CellStackSize(&state.dataStack) == 1);
  mu_assert_double_eq(19, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(if_else_then_false) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 IF 10 9 + ELSE 5 4 + THEN");
  DoForth(&state);
  CLOSE_STREAM();
  mu_check(CellStackSize(&state.dataStack) == 1);
  mu_assert_double_eq(9, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(if_else_then_tests) {
  MU_RUN_TEST(if_then_true);
  MU_RUN_TEST(if_then_false);
  MU_RUN_TEST(if_else_then_true);
  MU_RUN_TEST(if_else_then_false);
}



//
// ********** Loops **********
MU_TEST(do_loop_standard_test) {
  // https://forth-standard.org/standard/testsuite#test:core:LOOP
  INIT_TEST_STATE();
  OPEN_STREAM(": GD1 DO I LOOP ;");
  DoForth(&state);
  REOPEN_STREAM("4 1 GD1")
  DoForth(&state);
  mu_assert_double_eq(3, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);

  REOPEN_STREAM("2 -1 GD1");
  DoForth(&state);
  mu_assert_double_eq( 1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq( 0, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-1, CellStackPop(&state.dataStack).value);

  CLOSE_STREAM();
  FREE_TEST_STATE();
}
MU_TEST(for_loop_basic) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 0 DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(5, CellStackSize(&state.dataStack));
  mu_assert_double_eq(4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(3, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_reverse) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 5 DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(0, CellStackSize(&state.dataStack)); // Should not push anything to the stack
  FREE_TEST_STATE();
}
MU_TEST(for_loop_single_iteration) {
  INIT_TEST_STATE();
  OPEN_STREAM("1 0 DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(1, CellStackSize(&state.dataStack));
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_empty) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 0 DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(0, CellStackSize(&state.dataStack)); // Should not push anything to the stack
  FREE_TEST_STATE();
}
MU_TEST(for_loop_negative_indices) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 -5 DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(5, CellStackSize(&state.dataStack));
  mu_assert_double_eq(-1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-3, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-5, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_modify_index) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 0 DO I 2 + LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(5, CellStackSize(&state.dataStack));
  mu_assert_double_eq(6, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(5, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(3, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_nested) {
  INIT_TEST_STATE();
  OPEN_STREAM("2 0 DO 7 4 DO J I LOOP LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(12, CellStackSize(&state.dataStack));
  mu_assert_double_eq(6, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(5, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(6, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(5, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_leave) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 0 DO I 3 = IF LEAVE THEN I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  String *error = StreamToString(state.errorStream);
  mu_assert_string_eq("", GetStringValue(error));
  mu_assert_double_eq(3, CellStackSize(&state.dataStack));
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_basic_with_qdo) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 0 ?DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();

  String *error = StreamToString(state.errorStream);
  mu_assert_string_eq("", GetStringValue(error));
  String *output = StreamToString(state.outputStream);
  mu_assert_string_eq("", GetStringValue(output));
  // Assert that the loop ran and output is correct
  mu_assert_double_eq(5, CellStackSize(&state.dataStack));
  mu_assert_double_eq(4, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(3, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_empty_with_qdo) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 5 ?DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  // Assert that the loop did not run and the stack is empty
  mu_assert_double_eq(0, CellStackSize(&state.dataStack));
  FREE_TEST_STATE();
}
MU_TEST(for_loop_negative_with_qdo) {
  INIT_TEST_STATE();
  OPEN_STREAM("-3 0 ?DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  // Assert that the loop ran correctly for negative to positive range
  mu_assert_double_eq(3, CellStackSize(&state.dataStack));
  mu_assert_double_eq(-1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(-3, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_single_iteration_with_qdo) {
  INIT_TEST_STATE();
  OPEN_STREAM("0 1 ?DO I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  // Assert that the loop ran once with one element on the stack
  mu_assert_double_eq(1, CellStackSize(&state.dataStack));
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(loop_tests) {
  MU_RUN_TEST(do_loop_standard_test);
  // MU_RUN_TEST(for_loop_basic);
  // MU_RUN_TEST(for_loop_reverse);
  // MU_RUN_TEST(for_loop_single_iteration);
  // MU_RUN_TEST(for_loop_empty);
  // MU_RUN_TEST(for_loop_negative_indices);
  // MU_RUN_TEST(for_loop_modify_index);
  // MU_RUN_TEST(for_loop_nested);

  // MU_RUN_TEST(for_loop_leave);
  // MU_RUN_TEST(for_loop_basic_with_qdo);
  // MU_RUN_TEST(for_loop_empty_with_qdo);
  // MU_RUN_TEST(for_loop_negative_with_qdo);
  // MU_RUN_TEST(for_loop_single_iteration_with_qdo);
}






//
// Run all branch tests
int TestBranch(void) {
  MU_RUN_SUITE(skip_tests2);
  // MU_RUN_SUITE(skip_tests);
  // MU_RUN_SUITE(branch_tests);
  MU_RUN_SUITE(if_else_then_tests);
  MU_RUN_SUITE(loop_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
