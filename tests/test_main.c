#include <stdio.h>

void test_example(void);


int main(void) {
  printf("Starting tests...\n");
  test_example();
  return 0;
}


void test_example(void) {
    // Example test case
    printf("Running example test...\n");

    // Add your actual test logic here (assertions, checks, etc.)
    if (1 + 1 == 2) {
        printf("Test passed!\n");
    } else {
        printf("Test failed!\n");
    }
}
