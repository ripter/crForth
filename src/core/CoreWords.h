#ifndef COREWORDS_H
#define COREWORDS_H

#include "../KernelState.h"

void AddCoreWords(KernelState *state);

char* Add(KernelState* state, char* word);
char* Dot(KernelState* state, char* word);
char* BranchNZ(KernelState *state, char* word);

#endif // COREWORDS_H
