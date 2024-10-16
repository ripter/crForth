#include <raylib.h>
#include "crForth.h"

// Runs the Forth system with the given string.
void RunForthString(KernelState *state, const char *forthString, cell_t length) {
  // Convert the string to a stream, saving the original stream.
  FILE *inputStream = fmemopen((void *)forthString, length, "r");
  if (inputStream == NULL) {
    fprintf(state->errorStream, "Error: Could not create input stream for Forth string.\n");
    return;
  }
  FILE *originalInputStream = state->inputStream;
  state->inputStream = inputStream;

  // Run the Forth system with the new stream.
  DoForth(state);

  // Close the stream and restore the original stream.
  state->inputStream = originalInputStream;
  fclose(inputStream);
}
