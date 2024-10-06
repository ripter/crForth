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
  state.inputStream = inputStream;

#define CLOSE_STREAM()                                                         \
  fclose(inputStream);                                                         \
  state.inputStream = NULL;

#define REOPEN_STREAM(input)                                                   \
  fclose(inputStream);                                                         \
  inputStream = fmemopen(input, TextLength(input), "r");                       \
  state.inputStream = inputStream;


bool TestGetNext(void);
bool TestBranch(void);
bool TestCompileMode(void);
bool TestDoForth(void);
bool TestVariables(void);

#endif // TEST_H
