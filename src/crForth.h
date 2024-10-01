#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.1-dev"


#include <stdio.h>

#include "Stack.h"
#include "WordMetadata.h"
#include "Dictionary.h"
#include "KernelState.h"

void DoForth(KernelState *state);
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);
bool IsWhitespace(char c);
bool IsNumber(const char* word);
bool ConvertWordToNumber(const char* word, cell_t* numPtr);

#endif // CRFORTH_H
