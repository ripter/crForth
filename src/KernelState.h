#ifndef KERNELSTATE_H
#define KERNELSTATE_H

#include <stdbool.h>
#include "./Dictionary.h"
#include "./Stack.h"

typedef struct {
  Dictionary dict;
  CellStack dataStack;
  CellStack returnSack;
  bool IsInCompileMode;
  char* controlWord;
} KernelState;


void InitKernelState(KernelState *state);
void FreeKernelState(KernelState *state);


#endif // KERNELSTATE_H
