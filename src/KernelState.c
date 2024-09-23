
#include "KernelState.h"


void InitKernelState(KernelState *state) {
  InitDictionary(&state->dict);
  InitCellStack(&state->dataStack);
  InitCellStack(&state->returnSack);
  state->IsInCompileMode = false;
  state->controlWord = NULL;
}


void FreeKernelState(KernelState *state) {
  FreeDictionary(&state->dict);
  FreeCellStack(&state->dataStack);
  FreeCellStack(&state->returnSack);
  state->IsInCompileMode = false;
  state->controlWord = NULL;
}

