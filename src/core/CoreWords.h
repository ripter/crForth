#ifndef COREWORDS_H
#define COREWORDS_H

#include "../KernelState.h"
#include "../WordMetadata.h"

// Adds all of the core words to the dictionary.
void AddCoreWords(KernelState *state);

//
// Core Words
//
// Idealy, this should be a small set of words that are required to build the rest of the system.
// These should be the only words that can not be implemented in Forth itself.
// Expect for the ones that are more efficient to implement in C.
// Side note: this list is not alphabetized, its the order they were implemented. I find the history of things interesting.
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
void CFetch(KernelState* state, WordMetadata* wordMeta);
void Create(KernelState *state, WordMetadata *wordMeta);
void Nothing(KernelState *state, WordMetadata *wordMeta);
void Does(KernelState *state, WordMetadata *wordMeta);
void Dup(KernelState *state, WordMetadata *wordMeta);
void Drop(KernelState *state, WordMetadata *wordMeta);
void Swap(KernelState* state, WordMetadata* wordMeta);
void ToR(KernelState* state, WordMetadata* wordMeta);
void RFrom(KernelState* state, WordMetadata* wordMeta);
void DotSR(KernelState* state, WordMetadata *wordMeta);
void DotSD(KernelState* state, WordMetadata *wordMeta);
void Variable(KernelState* state, WordMetadata *wordMeta);


//
// Helper functions
//
void DoForthString(KernelState *state, WordMetadata *wordMeta);
void DoForthStringAndReturnAddress(KernelState *state, WordMetadata *wordMeta);

#endif // COREWORDS_H
