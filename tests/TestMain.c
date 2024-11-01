#include <stdio.h>
#include "Test.h"
#include "../src/crForth.h"

int main(void) {
  PrintHeader();
  printf("Running Tests...\n");

  printf("\n*** GetNextWord Tests ***\n");
  TestGetNext();

  printf("\n*** DoForth Tests ***\n");
  TestDoForth();

  printf("\n*** Branch Tests ***\n");
  TestBranch();

  printf("\n*** CompileMode Tests ***\n");
  TestCompileMode();

  printf("\n*** Variables Tests ***\n");
  TestVariables();

  printf("\n*** String Tests ***\n");
  TestStrings();

  return 0;
}
