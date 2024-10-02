#include <stdio.h>
#include "Test.h"

int main(void) {

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
  return 0;
}
