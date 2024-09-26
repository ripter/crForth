#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include "KernelState.h"


void DoForth(KernelState *state, FILE* inputStream);
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);
bool IsWhitespace(char c);
bool IsNumber(const char* word);

#endif // MAIN_H
