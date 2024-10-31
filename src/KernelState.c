#include "KernelState.h"


// Initializes a KernelState structure
// This function should be called before using a KernelState.
// It initializes the dictionary, data stack, and return stack.
// It also sets the IsInCompileMode flag to false.
// The input, output, and error streams are not initialized by this function.
void InitKernelState(KernelState *state) {
  InitDictionary(&state->dict);
  InitCellStack(&state->dataStack);
  InitCellStack(&state->returnStack);
  // state->compilePtr = CreateString("");
  state->compilePtr = NULL; // someone needs to set this before use.
  state->IsInCompileMode = false;
  state->inputStream = NULL;
  state->outputStream = NULL;
  state->errorStream = NULL;
  state->wordBuffer[0] = '\0';

  // Set the compile pointer to the scratch buffer.
  ForthWord *scratch = GetItemFromDictionary(&state->dict, SCRATCH_BUFFER_NAME);
  state->compilePtr = scratch->data;
}


// Free a KernelState structure
// This function should be called when a KernelState is no longer needed.
// It frees the memory used by the dictionary, data stack, and return stack.
// It also sets the IsInCompileMode flag to false.
// The input, output, and error streams are set to NULL by this function.
void FreeKernelState(KernelState *state) {
  FreeDictionary(&state->dict);
  FreeCellStack(&state->dataStack);
  FreeCellStack(&state->returnStack);

  state->IsInCompileMode = false;
  state->inputStream = NULL;
  state->outputStream = NULL;
  state->errorStream = NULL;
  state->wordBuffer[0] = '\0';

  state->compilePtr = NULL; 
}
