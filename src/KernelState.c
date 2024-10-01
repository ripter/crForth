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
  state->IsInCompileMode = false;
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
}
