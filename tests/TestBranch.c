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


//
// ********** Branch Tests **********
MU_TEST(branch_jump_1) {
  INIT_TEST_STATE();
  // We want to test branching to the + word.
  // Get the word from the dictionary so we can push it's "address" to the return stack.
  ForthWord *branchWord = GetItemFromDictionary(&state.dict, "+");
  CellStackPush(&state.returnStack, (Cell){1, CELL_TYPE_NUMBER});                // length
  CellStackPush(&state.returnStack, (Cell){(cell_t)branchWord->name, CELL_TYPE_WORD}); // address
  // add numbers to the data stack and try the branch.
  // Because the address on the returnStack is "+", the branch should execute the + word.
  OPEN_STREAM("10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  // Did it run the branch word?
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(19, result.value);
  FREE_TEST_STATE();
}
MU_TEST(branch_with_empty_return_stack) {
  INIT_TEST_STATE();
  OPEN_STREAM("10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_EMPTY_STACK);
  FREE_TEST_STATE();
}
MU_TEST(branch_with_invalid_address) {
  INIT_TEST_STATE();
  // 27 is not a valid address, so the branch should fail.
  OPEN_STREAM("27 1 >r >r 10 9 branch");
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_INVALID_WORD_ON_RETURN_STACK);
  FREE_TEST_STATE();
}
MU_TEST(branchnz_basic_true) {
  INIT_TEST_STATE();
  OPEN_STREAM("' + >r >r 10 9 -1 ?branch");
  DoForth(&state);
  CLOSE_STREAM();
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
MU_TEST(branch_no_length_error) {
  INIT_TEST_STATE();
  OPEN_STREAM("' + >r drop 10 9 0 ?branch");
  DoForth(&state);
  CLOSE_STREAM();
  // Verify that the error was thrown.
  VERIFY_ERROR(ERR_INVALID_WORD_ON_RETURN_STACK);
  // Verify that the stack is unchanged.
  mu_assert_double_eq(2, CellStackSize(&state.dataStack));
  mu_assert_double_eq(9, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(10, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(branch_jump_test) {
  INIT_TEST_STATE();

  // define two words, foo and bar, then jump to foo via branchr.
  OPEN_STREAM(": foo 10 ; : bar 9 ; ' foo >r >r branch");
  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that 10 is left on the stack as branch executed the word at the return stack address.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, result.value);
  FREE_TEST_STATE();
}
MU_TEST(tick) {
  INIT_TEST_STATE();
  OPEN_STREAM("' +");
  DoForth(&state);
  CLOSE_STREAM();

  // Get the dictionary entry so we can verify the address is the same.
  ForthWord* wordMeta = GetItemFromDictionary(&state.dict, "+");
  (void)CellStackPop(&state.dataStack); // length
  Cell word = CellStackPop(&state.dataStack);

  // Tick should push the address of the word to the stack.
  mu_assert_double_eq((cell_t)wordMeta->name, word.value);
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
  MU_RUN_TEST(branch_no_length_error);
  MU_RUN_TEST(tick);
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
  OPEN_STREAM("2 0 DO 3 0 DO I J LOOP LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(6, CellStackSize(&state.dataStack));
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}
MU_TEST(for_loop_leave) {
  INIT_TEST_STATE();
  OPEN_STREAM("5 0 DO I 3 = IF LEAVE THEN I LOOP");
  DoForth(&state);
  CLOSE_STREAM();
  mu_assert_double_eq(3, CellStackSize(&state.dataStack));
  mu_assert_double_eq(2, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(1, CellStackPop(&state.dataStack).value);
  mu_assert_double_eq(0, CellStackPop(&state.dataStack).value);
  FREE_TEST_STATE();
}

MU_TEST_SUITE(loop_tests) {
  MU_RUN_TEST(for_loop_basic);
  MU_RUN_TEST(for_loop_reverse);
  MU_RUN_TEST(for_loop_single_iteration);
  MU_RUN_TEST(for_loop_empty);
  MU_RUN_TEST(for_loop_negative_indices);
  MU_RUN_TEST(for_loop_modify_index);
  // MU_RUN_TEST(for_loop_nested);
  MU_RUN_TEST(for_loop_leave);
}





//
// Run all branch tests
bool TestBranch(void) {
  MU_RUN_SUITE(skip_tests);
  MU_RUN_SUITE(branch_tests);
  MU_RUN_SUITE(if_else_then_tests);
  MU_RUN_SUITE(loop_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
