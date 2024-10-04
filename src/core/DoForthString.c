#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "../crForth.h"


// Runs the data as a Forth program using the given KernelState.
void DoForthString(KernelState *state, WordMetadata *wordMeta) {
  char oldBranch[MAX_WORD_LENGTH]; 
  char *input = wordMeta->data;
  // Convert the string to a stream, saving the original stream.
  FILE *inputStream = fmemopen(input, TextLength(input), "r");
  FILE *orignalInputStream = state->inputStream;
  state->inputStream = inputStream;

  // Save the branch word so it can be used in the Forth program.
  TextCopy(oldBranch, state->branchBuffer);
  TextCopy(state->branchBuffer, wordMeta->name);

  // Run the Forth system with the new stream.
  DoForth(state);

  // Restore the branch word.
  TextCopy(state->branchBuffer, oldBranch);
  // Close the stream and restore the original stream.
  state->inputStream = orignalInputStream;
  fclose(inputStream);
}
