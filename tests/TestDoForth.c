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

  // Get the output from the output stream
  fflush(state.outputStream);
  rewind(state.outputStream);
  char buffer[1024];  // Adjust size as needed
  size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, state.outputStream);
  buffer[bytesRead] = '\0';  // Null-terminate the buffer

  const char *expected = "\n: MAGIC\n  10 9 + \n; \n";
  mu_assert_string_eq(expected, buffer);
  FREE_TEST_STATE();
}

//
// Run all the Tests
//
bool TestDoForth(void) {

  MU_RUN_TEST(basic_64bit_number);
  MU_RUN_TEST(can_define_word_and_see_it);

  MU_REPORT();
  return MU_EXIT_CODE;
}
