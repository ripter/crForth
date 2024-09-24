
#include "KernelState.h"


void InitKernelState(KernelState *state) {
  InitDictionary(&state->dict);
  InitCellStack(&state->dataStack);
  InitCellStack(&state->returnStack);
  state->IsInCompileMode = false;
}


void FreeKernelState(KernelState *state) {
  FreeDictionary(&state->dict);
  FreeCellStack(&state->dataStack);
  FreeCellStack(&state->returnStack);
  state->IsInCompileMode = false;
}

