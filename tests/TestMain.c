#include <stdio.h>
#include "Test.h"
#include "../src/crForth.h"

int main(void) {
  PrintHeader();
  printf("Running Tests...\n");

  // Array of test functions and corresponding names
  TestFunc tests[] = {TestGetNext,     TestDoForth,   TestBranch,
                      TestCompileMode, TestVariables, TestStrings};
  const char *testNames[] = {"GetNextWord", "DoForth",   "Branch",
                             "CompileMode", "Variables", "String"};
  String *testResults = CreateString("");

  // Number of tests
  int numTests = sizeof(tests) / sizeof(tests[0]);
  bool anyFailed = false;

  // Run all tests and print individual section headers
  for (int i = 0; i < numTests; i++) {
    printf("\n*** %s Tests ***\n", testNames[i]);
    int result = tests[i]();
    if (result != 0) {
      AppendToString(testResults, "FAILED: ");
      AppendToString(testResults, testNames[i]);
      AppendToString(testResults, "\n");
      anyFailed = true;
    }
  }

  if (anyFailed) {
    printf("\n*** Failed Tests ***\n");
    printf("%s", GetStringValue(testResults));
  } else {
    printf("All tests PASSED.\n");
  }

  return 0;
}
