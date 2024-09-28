#include <stdio.h>
#include <string.h>

#include "../crForth.h"


void DoForthString(KernelState *state, WordMetadata *wordMeta) {
  (void)state;
  (void)wordMeta;
  char input[] = "2 3 4 + + ";
  // Convert the string to a stream, then run the Forth Kernel.
  FILE *inputStream = fmemopen(input, strlen(input), "r");
  DoForth(state, inputStream);
  fclose(inputStream);
}

