#ifndef COREWORDS_H
#define COREWORDS_H

#include "../KernelState.h"
#include "../WordMetadata.h"

// Adds all of the core words to the dictionary.
void AddCoreWords(KernelState *state);

//
// Core Words
//
void Add(KernelState *state, WordMetadata *wordMeta);
void Branch(KernelState *state, WordMetadata *wordMeta); 
void BranchZ(KernelState *state, WordMetadata *wordMeta);
void Colon(KernelState *state, WordMetadata *wordMeta);
void Dot(KernelState* state, WordMetadata *wordMeta);
void DotS(KernelState* state, WordMetadata *wordMeta);
void SemiColon(KernelState *state, WordMetadata *wordMeta);
void Subtract(KernelState* state, WordMetadata *wordMeta);
void Words(KernelState* state, WordMetadata* wordMeta);
void See(KernelState* state, WordMetadata* wordMeta);
void Immediate(KernelState* state, WordMetadata* wordMeta);
void Latest(KernelState* state, WordMetadata* wordMeta);
void Emit(KernelState* state, WordMetadata* wordMeta);

//
// Helper functions
//
char* DoForthString(KernelState *state, char *word);

#endif // COREWORDS_H
