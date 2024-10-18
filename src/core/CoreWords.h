#ifndef COREWORDS_H
#define COREWORDS_H

#include "../KernelState.h"
#include "../ForthWord.h"

#define HERE_BUFFER_NAME  "__HERE_BUFFER_NAME__"

// Adds all of the core words to the dictionary.
void AddCoreWords(KernelState *state);

//
// Core Words
//
// Idealy, this should be a small set of words that are required to build the rest of the system.
// These should be the only words that can not be implemented in Forth itself.
// Expect for the ones that are more efficient to implement in C.
// Side note: this list is not alphabetized, its the order they were implemented. I find the history of things interesting.
void Add(KernelState *state);
void Skip(KernelState *state);
void SkipOnZero(KernelState *state);
void Branch(KernelState *state); 
void BranchNZ(KernelState *state);
void Colon(KernelState *state);
void Dot(KernelState* state);
void DotS(KernelState* state);
void SemiColon(KernelState *state);
void Subtract(KernelState* state);
void Words(KernelState* state);
void See(KernelState* state);
void Immediate(KernelState* state);
void Latest(KernelState* state);
void Emit(KernelState* state);
void CFetch(KernelState* state);
void Create(KernelState *state);
void Nothing(KernelState *state);
void Does(KernelState *state);
void Dup(KernelState *state);
void Drop(KernelState *state);
void Swap(KernelState* state);
void ToR(KernelState* state);
void RFrom(KernelState* state);
void DotSR(KernelState* state);
void DotSD(KernelState* state);
void GreaterThan(KernelState* state);
void LessThan(KernelState* state);
void NotEqual(KernelState* state);
void Equal(KernelState* state);
void Postpone(KernelState *state);
void Tick(KernelState *state);
void Execute(KernelState *state);
void Here(KernelState *state);
void Backslash(KernelState *state);
void Paren(KernelState *state);
void Invert(KernelState *state);
void BitOr(KernelState *state);
void BitAnd(KernelState *state);
void BitXor(KernelState *state);
void BitShiftLeft(KernelState *state);
void BitShiftRight(KernelState *state);
void ZeroEquals(KernelState* state);
void IF(KernelState *state);
void ELSE(KernelState *state);
void THEN(KernelState *state);
void DO(KernelState *state);
void I(KernelState *state);
void LOOP(KernelState *state);
void Evaluate(KernelState* state);
void Allot(KernelState* state);
void AllocatedSize(KernelState *state);
void Leave(KernelState *state);


//
// Helper functions
//
void DoForthString(KernelState *state, const char* branchName, const char* forthString);
void DoForthDataString(KernelState *state);
void DoForthStringAndReturnAddress(KernelState *state);
void Variable(KernelState* state, ForthWord *wordMeta);

#endif // COREWORDS_H
