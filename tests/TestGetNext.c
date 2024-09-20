#include <stdio.h>
#include <stdbool.h>
#include "Test.h"
#include "../src/crForth.h"

char* TestGetNext(void) {
  printf("\n%s\n", GetNext());
  return false;
}
