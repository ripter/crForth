#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.1-dev"

// Forth true/false values
#define FTRUE -1
#define FFALSE 0
#define BOOL_TO_FORTH(b) ((b) ? FTRUE : FFALSE)


#include <stdio.h>
#include "Stack.h"
#include "WordMetadata.h"
#include "Dictionary.h"
#include "KernelState.h"
#include "utils.h"

void DoForth(KernelState *state);
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);
bool IsWhitespace(char c);
bool IsNumber(const char* word);
bool ConvertWordToNumber(const char* word, cell_t* numPtr);

#endif // CRFORTH_H
