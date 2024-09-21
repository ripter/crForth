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

#define SILENCE_STDERR() \
  FILE* original_stderr = stderr; \
  stderr = fopen("/dev/null", "w"); 

#define RESTORE_STDERR() \
  fclose(stderr); \
  stderr = original_stderr; 


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

MU_TEST(leading_whitespace) {
  char* testValue = " 3";
  char* expected = "3";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
	mu_assert_string_eq(actual, expected);
}

MU_TEST(word_too_long) {
  char* testValue = "ThisIsAVeryLongWordThatExceedsTheMaxLengthOfTheBufferThisIsAVeryLongWordThatExceedsTheMaxLengthOfTheBuffer";
  SILENCE_STDERR();
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
  RESTORE_STDERR();
  mu_assert(actual == NULL, "Expected NULL for word exceeding buffer size");
}

MU_TEST(tab_delimited_words) {
  char* testValue = "@home\tword";
  char* expected = "@home";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
  mu_assert_string_eq(actual, expected);
}

MU_TEST(multiple_words_newline) {
  char* testValue = ",\nsecond";
  char* expected = ",";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
  mu_assert_string_eq(actual, expected);
}

MU_TEST(empty_string) {
  char* testValue = "";
  char* expected = NULL;
  SILENCE_STDERR();
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
  RESTORE_STDERR();
  mu_assert(actual == expected, "Expected NULL for empty string");
}

MU_TEST(trailing_whitespace) {
  char* testValue = "Hello   ";
  char* expected = "Hello";
  OPEN_STREAM(testValue);
  char* actual = GetNext(inputStream); ;
  CLOSE_STREAM();
  mu_assert_string_eq(actual, expected);
}


bool TestGetNext(void) {

  MU_RUN_TEST(basic_string_1);
  MU_RUN_TEST(basic_string_2);
  MU_RUN_TEST(leading_whitespace);
  MU_RUN_TEST(word_too_long);
  MU_RUN_TEST(tab_delimited_words);
  MU_RUN_TEST(multiple_words_newline);
  MU_RUN_TEST(empty_string);
  MU_RUN_TEST(trailing_whitespace);
  

  MU_REPORT();
  return MU_EXIT_CODE;
}
