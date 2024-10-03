#include <stdio.h>
#include <stdbool.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"
#include "../src/core/CoreWords.h"

#define INIT_TEST_STATE()                                                      \
  KernelState state = {0};                                                     \
  InitKernelState(&state);                                                     \
  AddCoreWords(&state);

#define FREE_TEST_STATE() FreeKernelState(&state);

#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");                 \
  state.inputStream = inputStream;

#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \
  state.inputStream = NULL;

#define REOPEN_STREAM(input)                                                   \
  fclose(inputStream);                                                         \
  inputStream = fmemopen(input, TextLength(input), "r");                       \
  state.inputStream = inputStream;




MU_TEST(branch_test) {
  INIT_TEST_STATE();
  // branch should skip 3 words, resulting in nothing being added to the stack.
  OPEN_STREAM("19 branch 3 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 19);
  FREE_TEST_STATE();
}

MU_TEST(branch_test_on_empty_stack) {
  INIT_TEST_STATE();

  // branch should skip 3 words, resulting in nothing being added to the stack.
  OPEN_STREAM("branch 3 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  // stack should still be empty.
  mu_check(IsCellStackEmpty(&state.dataStack));
  FREE_TEST_STATE();
}

MU_TEST(branch_jump_0) {
  INIT_TEST_STATE();

  // Branch should skip 0 words, resulting in 4 and 5 being added together on the stack.
  OPEN_STREAM("19 branch 0 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 9);
  FREE_TEST_STATE();
}

MU_TEST(branch_jump_1) {
  INIT_TEST_STATE();

  // Branch should skip 1 words, resulting 15 being added to the stack.
  OPEN_STREAM("10 branch 1 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 15);
  FREE_TEST_STATE();
}

MU_TEST(branchnz_basic_true) {
  INIT_TEST_STATE();

  // 1 is true, so the branch should *not* skip 3 words.
  // resulting in 4 and 5 being added together on the stack.
  // the test value should not be on the stack.
  OPEN_STREAM("1 ?branch 3 4 5 +");
  DoForth(&state);
  CLOSE_STREAM();

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_check(result == 9);
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
  (void)PopFromCellStack(&state.dataStack); // length
  cell_t word = PopFromCellStack(&state.dataStack);

  // Tick should push the address of the word to the stack.
  mu_assert_double_eq((cell_t)wordMeta->name, word);
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

  cell_t result = PopFromCellStack(&state.dataStack);
  mu_assert_double_eq(19, result);
  FREE_TEST_STATE();
}



//
// Run all branch tests
bool TestBranch(void) {
  MU_RUN_TEST(branch_test);
  MU_RUN_TEST(branch_test_on_empty_stack);
  MU_RUN_TEST(branch_jump_0);
  MU_RUN_TEST(branch_jump_1);

  MU_RUN_TEST(branchnz_basic_true);
  MU_RUN_TEST(branchnz_basic_false);

  MU_RUN_TEST(tick);
  MU_RUN_TEST(tick_and_execute);

  MU_REPORT();
  return MU_EXIT_CODE;
}
