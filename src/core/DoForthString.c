#include <stdio.h>
#include <string.h>
#include "../KernelState.h"
#include "../crForth.h"
#include "../main.h"

char* DoForthString(KernelState *state, char *word) {
  (void)state;
  (void)word;
  char input[] = "2 3 4 + + ";
  // Convert the string to a stream, then run the Forth Kernel.
  FILE *inputStream = fmemopen(input, strlen(input), "r");
  DoForth(state, inputStream);
  fclose(inputStream);
  return NULL;
}

