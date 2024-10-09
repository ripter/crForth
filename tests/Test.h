#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

#define INIT_TEST_STATE()                                                      \
  KernelState state = {0};                                                     \
  InitKernelState(&state);                                                     \
  AddCoreWords(&state);

#define FREE_TEST_STATE() FreeKernelState(&state);

#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");                 \
  state.inputStream = inputStream;                                             \
  state.errorStream = tmpfile(); // Initialize error stream

#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \
  state.inputStream = NULL;

#define REOPEN_STREAM(input)                                                   \
  fclose(inputStream);                                                         \
  inputStream = fmemopen(input, TextLength(input), "r");                       \
  state.inputStream = inputStream;

#define VERIFY_ERROR(expected_error)                                           \
  fseek(state.errorStream, 0, SEEK_SET);                                       \
  char error_output[256];                                                      \
  if (fgets(error_output, sizeof(error_output), state.errorStream) == NULL) {  \
    mu_fail("No error output captured.");                                      \
  }                                                                            \
  mu_assert_string_eq(expected_error, error_output);



bool TestGetNext(void);
bool TestBranch(void);
bool TestCompileMode(void);
bool TestDoForth(void);
bool TestVariables(void);

#endif // TEST_H
