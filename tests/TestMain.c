#include <stdio.h>
#include "Test.h"

int main(void) {
  printf("Starting tests...\n");

  printf("\n*** GetNextWord Tests ***\n");
  TestGetNext();

  printf("\n*** Dictionary Tests ***\n");
  TestDictionary();

  return 0;
}
