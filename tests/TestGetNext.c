#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"


#define REDIRECT_STDIN(input) \
    FILE *old_stdin = stdin; \
    stdin = fmemopen(input, strlen(input), "r");

#define RESTORE_STDIN() \
    fclose(stdin); \
    stdin = old_stdin;



MU_TEST(basic_string_1) {
  char* testValue = "Hello, World!";
  char* expected = "Hello,";
  REDIRECT_STDIN(testValue);
  char* actual = GetNext(); ;
	mu_assert_string_eq(actual, expected);
  RESTORE_STDIN();
}

MU_TEST(basic_number_1) {
  char* testValue = " 3";
  char* expected = "3";
  REDIRECT_STDIN(testValue);
  char* actual = GetNext(); ;
	mu_assert_string_eq(actual, expected);
  RESTORE_STDIN();
}


bool TestGetNext(void) {

  MU_RUN_TEST(basic_string_1);
  MU_RUN_TEST(basic_number_1);
  

  MU_REPORT();
  return MU_EXIT_CODE;
}
