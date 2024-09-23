#ifndef KERNELSTATE_H
#define KERNELSTATE_H

#include "./Dictionary.h"
#include "./Stack.h"

typedef struct {
  Dictionary dict;
  CellStack dataStack;
  CellStack returnSack;
} KernelState;


void InitKernelState(KernelState *state);
void FreeKernelState(KernelState *state);


#endif // KERNELSTATE_H
