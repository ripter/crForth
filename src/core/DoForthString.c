#include <stdio.h>
#include <string.h>
#include <raylib.h>

#include "../crForth.h"

void ExecuteForthString(KernelState *state, const char *branchWord, const char *input, bool returnAddress);


// Runs a string as a Forth program using the given KernelState.
void DoForthString(KernelState *state, const char* branchName, const char* forthString) {
  // printf("DoForthString: %s\n", branchName);
  ExecuteForthString(state, branchName, forthString, false);
}

// Runs the data as a Forth program using the given KernelState.
void DoForthDataString(KernelState *state) {
  ForthWord *word = GetItemFromDictionary(&state->dict, state->wordBuffer);
  // printf("DoForthDataString: %s\n", word->name);
  ExecuteForthString(state, word->name, GetStringValue(word->data), false);
}

// Runs the data as a Forth program using the given KernelState.
void DoForthStringAndReturnAddress(KernelState *state) {
  ForthWord *word = GetItemFromDictionary(&state->dict, state->wordBuffer);
  // printf("DoForthStringAndReturnAddress: %s\n", wordMeta->name);
  ExecuteForthString(state, word->name, GetStringValue(word->data), true);
}



// Internal helper function that handles Forth string execution and optional return address.
void ExecuteForthString(KernelState *state, const char *branchWord, const char *input, bool returnAddress) {
  if (TextLength(input) == 0) {
    fprintf(state->errorStream, ERR_EMPTY_FORTH_STRING);
    return;
  }

  // Push the word "address" to the stack if needed.
  if (returnAddress) {
    CellStackPush(&state->dataStack, (Cell){(CellValue)branchWord, CELL_TYPE_WORD});
  }

  // Convert the string to a stream, saving the original stream.
  FILE *inputStream = fmemopen((void *)input, TextLength(input), "r");
  FILE *originalInputStream = state->inputStream;
  state->inputStream = inputStream;

  // Run the Forth system with the new stream.
  DoForth(state);

  // Close the stream and restore the original stream.
  state->inputStream = originalInputStream;
  fclose(inputStream);
}
