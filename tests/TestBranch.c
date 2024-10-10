#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"


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


MU_TEST(branch_jump_1) {
  INIT_TEST_STATE();
  // We want to test branching to the + word.
  // Get the word from the dictionary so we can push it's "address" to the return stack.
  WordMetadata *branchWord = GetItemFromDictionary(&state.dict, "+");
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
  // OPEN_STREAM("73 1 -")
  DoForth(&state);
  CLOSE_STREAM();
  VERIFY_ERROR(ERR_INVALID_WORD_ON_RETURN_STACK);
  FREE_TEST_STATE();
}

MU_TEST(branchnz_basic_true) {
  INIT_TEST_STATE();

  OPEN_STREAM("1 ?branch 3 4 5 +");
  // DoForth(&state);
  CLOSE_STREAM();

  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(9, result.value);
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}

MU_TEST(branchnz_basic_false) {
  INIT_TEST_STATE();

  // 0 is false, so the branch should skip 3 words.
  // the test bool should have been consumed, leaving the stack empty.
  OPEN_STREAM("0 ?branch 3 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}

MU_TEST(tick) {
  INIT_TEST_STATE();
  OPEN_STREAM("' +");
  DoForth(&state);
  CLOSE_STREAM();

  // Get the dictionary entry so we can verify the address is the same.
  WordMetadata* wordMeta = GetItemFromDictionary(&state.dict, "+");
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


MU_TEST(branchr_test) {
  INIT_TEST_STATE();

  // define two words, foo and bar, then jump to foo via branchr.
  OPEN_STREAM(": foo 10 ; : bar 9 ; foo >r branchr");
  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that 10 is left on the stack as branchr executed the word at the return stack address.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(10, result.value);
  FREE_TEST_STATE();
}

MU_TEST(branchr_test_empty_return_stack) {
  INIT_TEST_STATE();

  // branchr without anything on the return stack should result in an error or no operation.
  OPEN_STREAM("branchr");
  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that the stack remains empty as nothing should be executed.
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}

MU_TEST(branchr_with_calculation) {
  INIT_TEST_STATE();

  // Simulate adding two numbers by jumping to the address via the return stack.
  OPEN_STREAM(": addnums 4 5 + ; addnums >r branchr");

  DoForth(&state);
  CLOSE_STREAM();

  // Ensure that 9 is the result of the addition.
  Cell result = CellStackPop(&state.dataStack);
  mu_assert_double_eq(9, result.value);
  FREE_TEST_STATE();
}

//
// Run all branch tests
bool TestBranch(void) {
  MU_RUN_TEST(skip_basic_test);
  MU_RUN_TEST(skip_on_empty_stack_test);
  MU_RUN_TEST(skip_0_basic);
  MU_RUN_TEST(skip_0_no_skip);
  MU_RUN_TEST(skip_0_no_skip_single_word);
  MU_RUN_TEST(skip_0_with_negative_skip);

  MU_RUN_TEST(branch_jump_1);
  MU_RUN_TEST(branch_with_empty_return_stack);
  MU_RUN_TEST(branch_with_invalid_address);
  // MU_RUN_TEST(branchnz_basic_true);
  // MU_RUN_TEST(branchnz_basic_false);

  MU_RUN_TEST(tick);
  MU_RUN_TEST(tick_and_execute);
  MU_RUN_TEST(latest_and_execute);

  // MU_RUN_TEST(branchr_test);
  // MU_RUN_TEST(branchr_test_empty_return_stack);
  // MU_RUN_TEST(branchr_with_calculation);

  MU_REPORT();
  return MU_EXIT_CODE;
}
