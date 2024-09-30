#include <stdio.h>
#include <string.h>

#include "../crForth.h"


void DoForthString(KernelState *state, WordMetadata *wordMeta) {
  (void)state;
  char *input = wordMeta->data;
  // Convert the string to a stream, then run the Forth Kernel.
  FILE *inputStream = fmemopen(input, strlen(input), "r");
  DoForth(state, inputStream);
  fclose(inputStream);
}

