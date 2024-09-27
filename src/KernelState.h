#ifndef KERNELSTATE_H
#define KERNELSTATE_H

#include "crForth.h"
#include "Dictionary.h"
#include "Stack.h"

// The KernelState struct holds the state of the Forth system.
typedef struct {
  Dictionary dict;                  // The dictionary of Forth words.
  CellStack dataStack;              // The data stack.
  CellStack returnStack;            // The return stack.
  bool IsInCompileMode;             // Are we in compile mode?
  char wordBuffer[MAX_WORD_LENGTH]; // Buffer for the current word being processed.
} KernelState;

void InitKernelState(KernelState *state);
void FreeKernelState(KernelState *state);


#endif // KERNELSTATE_H
