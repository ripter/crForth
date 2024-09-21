#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"


#define OPEN_STREAM(input) \
    FILE *inputStream = fmemopen(input, strlen(input), "r");

#define CLOSE_STREAM() \
    fclose(inputStream); \



MU_TEST(basic_string_1) {
  char* testValue = "Hello, World!";
  char* expected = "Hello,";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
	mu_assert_string_eq(actual, expected);
}

MU_TEST(basic_string_2) {
  char* testValue = ": FIRST_COLON ;";
  char* expected = ":";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
	mu_assert_string_eq(actual, expected);
}

MU_TEST(basic_number_1) {
  char* testValue = " 3";
  char* expected = "3";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
	mu_assert_string_eq(actual, expected);
}


bool TestGetNext(void) {

  MU_RUN_TEST(basic_string_1);
  MU_RUN_TEST(basic_string_2);
  MU_RUN_TEST(basic_number_1);
  

  MU_REPORT();
  return MU_EXIT_CODE;
}
