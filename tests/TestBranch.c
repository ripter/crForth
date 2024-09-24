#include <stdio.h>
#include <stdbool.h>

#include "minunit.h"
#include "Test.h"
#include "../src/main.h"
#include "../src/core/CoreWords.h"


#define OPEN_STREAM(input) \
  FILE *inputStream = fmemopen(input, strlen(input), "r");

#define CLOSE_STREAM() \
  fclose(inputStream); \


MU_TEST(branch_test) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // branch should skip 3 words, resulting in nothing being added to the stack.
  OPEN_STREAM("19 branch 3 4 5 +");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopCellStack(&state.dataStack);
  mu_check(result == 19);
}

MU_TEST(branch_jump_0) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Branch should skip 0 words, resulting in 4 and 5 being added together on the stack.
  OPEN_STREAM("19 branch 0 4 5 +");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopCellStack(&state.dataStack);
  mu_check(result == 9);
}

MU_TEST(branch_jump_1) {
  KernelState state = {0};
  InitKernelState(&state);
  AddCoreWords(&state);

  // Branch should skip 1 words, resulting 15 being added to the stack.
  OPEN_STREAM("10 branch 1 4 5 +");
  DoForth(&state, inputStream);
  CLOSE_STREAM();

  // Check that the TOS is still our sentinel value.
  cell_t result = PopCellStack(&state.dataStack);
  mu_check(result == 15);
}


bool TestBranch(void) {
  MU_RUN_TEST(branch_test);
  MU_RUN_TEST(branch_jump_0);
  MU_RUN_TEST(branch_jump_1);

  MU_REPORT();
  return true;
}
