#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "../crForth.h"


// Runs the data as a Forth program using the given KernelState.
void DoForthStringAndReturnAddress(KernelState *state, WordMetadata *wordMeta) {
  char *word = wordMeta->name;
  char *input = wordMeta->data;

  // Push the word "address" to the stack.
  // Since this is a streaming implementation, we can't return an address, so we return the word instead.
  PushToCellStack(&state->dataStack, (cell_t)word);
  // Convert the string to a stream, saving the original stream.
  FILE *inputStream = fmemopen(input, TextLength(input), "r");
  FILE *orignalInputStream = state->inputStream;

  // Run the Forth system with the new stream.
  state->inputStream = inputStream;
  DoForth(state);

  // Close the stream and restore the original stream.
  state->inputStream = orignalInputStream;
  fclose(inputStream);
}
