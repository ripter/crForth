#ifndef TEST_H
#define TEST_H

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <raylib.h>

#include "../src/crForth.h"
#include "../src/core/CoreWords.h"
#include "../src/file/FileWords.h"

#define INIT_TEST_STATE()                                                      \
  KernelState state = {0};                                                     \
  InitKernelState(&state);                                                     \
  AddCoreWords(&state);                                                        \
  AddFileWords(&state);                                                        \
  AddForthWords(&state);

#define FREE_TEST_STATE()                                                      \
  FreeKernelState(&state);                                                     \
  fclose(state.errorStream);                                                   \
  state.errorStream = NULL;                                                    \
  fclose(state.outputStream);                                                  \
  state.outputStream = NULL;

#define OPEN_STREAM(input)                                                     \
  FILE *inputStream = fmemopen(input, TextLength(input), "r");                 \
  state.inputStream = inputStream;                                             \
  state.errorStream = tmpfile();                                               \
  state.outputStream = tmpfile();

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



void PrintWithControlChars(const char *str);

typedef int (*TestFunc)(void);

int TestGetNext(void);
int TestBranch(void);
int TestCompileMode(void);
int TestDoForth(void);
int TestVariables(void);
int TestStrings(void);
int TestSys(void);



#endif // TEST_H
