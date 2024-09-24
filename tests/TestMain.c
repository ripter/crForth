#include <stdio.h>
#include "Test.h"

int main(void) {

  printf("\n*** GetNextWord Tests ***\n");
  TestGetNext();

  printf("\n*** Branch Tests ***\n");
  TestBranch();

  printf("\n*** CompileMode Tests ***\n");
  TestCompileMode();

  return 0;
}
