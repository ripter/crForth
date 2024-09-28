#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.1-dev"


#include <stdio.h>

#include "Stack.h"
#include "WordMetadata.h"
#include "Dictionary.h"
#include "KernelState.h"

void DoForth(KernelState *state, FILE* inputStream);
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);
bool IsWhitespace(char c);
bool IsNumber(const char* word);

#endif // CRFORTH_H
