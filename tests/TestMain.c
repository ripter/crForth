#include <stdio.h>
#include "Test.h"

int main(void) {
  printf("Starting tests...\n");

  printf("\n*** GetNext Tests ***\n");
  TestGetNext();

  printf("\n*** Dictionary Tests ***\n");
  TestDictionary();

  return 0;
}
