#include <stdio.h>
#include "Test.h"

int main(void) {
  printf("Starting tests...\n");

  printf("Testing: GetNext...\n");
  if (TestGetNext()) {
    printf("Tests passed!\n");
  } else {
    printf("Tests failed!\n");
  }

  return 0;
}
