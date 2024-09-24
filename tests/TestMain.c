#include <stdio.h>
#include "Test.h"

int main(void) {
  // printf("Starting tests...\n");

  printf("\n*** GetNextWord Tests ***\n");
  TestGetNext();

  printf("\n*** Branch Tests ***\n");
  TestBranch();

  return 0;
}
