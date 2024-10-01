#include <string.h>
#include "raylib.h"

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"

#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");                 \
  state.inputStream = inputStream;

#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \
  state.inputStream = NULL;


MU_TEST(basic_64bit_number) {
  KernelState state = {0};
  InitKernelState(&state);

  OPEN_STREAM("4998578416");
  DoForth(&state);
  CLOSE_STREAM();
  cell_t result = PopFromCellStack(&state.dataStack);
  mu_assert_double_eq(4998578416, result);

  FreeKernelState(&state);
}


//
// Run all the Tests
//
bool TestDoForth(void) {

  MU_RUN_TEST(basic_64bit_number);

  MU_REPORT();
  return MU_EXIT_CODE;
}
