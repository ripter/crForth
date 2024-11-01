#include <string.h>
#include <raylib.h>

#include "minunit.h"
#include "Test.h"
#include "../src/crForth.h"


// Test for creating and printing a string using s" and TYPE
MU_TEST(sq_and_type_basic) {
  INIT_TEST_STATE();
  // Test creating a string and printing it
  OPEN_STREAM("s\" hello\" type");
  DoForth(&state);
  CLOSE_STREAM();
  // Verify the output
  String *actual = StreamToString(state.outputStream);
  mu_assert_string_eq("hello",  GetStringValue(actual));
  FREE_TEST_STATE();
}
// Test for creating multiple strings and printing them
MU_TEST(sq_and_type_multiple_strings) {
  INIT_TEST_STATE();
  // Test creating multiple strings
  OPEN_STREAM("s\" first\" type s\" second\" type");
  DoForth(&state);
  CLOSE_STREAM();
  // Verify the output
  String *actual = StreamToString(state.outputStream);
  mu_assert_string_eq("firstsecond", GetStringValue(actual));
  FREE_TEST_STATE();
}
// Test for creating an empty string
MU_TEST(sq_and_type_empty_string) {
  INIT_TEST_STATE();
  // Test creating an empty string
  OPEN_STREAM("s\" \" type");
  DoForth(&state);
  CLOSE_STREAM();
  // Verify the output (should be empty)
  String *actual = StreamToString(state.outputStream);
  mu_assert_string_eq("", GetStringValue(actual));
  FREE_TEST_STATE();
}

MU_TEST_SUITE(sq_and_type_tests) {
  MU_RUN_TEST(sq_and_type_basic);
  MU_RUN_TEST(sq_and_type_multiple_strings);
  MU_RUN_TEST(sq_and_type_empty_string);
}





//
// Run all the Tests
//
bool TestStrings(void) {
  MU_RUN_SUITE(sq_and_type_tests);

  MU_REPORT();
  return MU_EXIT_CODE;
}
