#ifndef COREWORDS_H
#define COREWORDS_H

#include "../KernelState.h"

// Adds all of the core words to the dictionary.
void AddCoreWords(KernelState *state);

//
// Core Words
//
char* Add(KernelState* state, char* word);
char* Branch(KernelState *state, char* word); 
char* BranchZ(KernelState *state, char* word);
char* Colon(KernelState *state, char *word);
char* Dot(KernelState* state, char* word);
char* DotS(KernelState* state, char* word);
char* SemiColon(KernelState *state, char *word);
char* Subtract(KernelState* state, char* word);

#endif // COREWORDS_H
