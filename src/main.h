#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include "KernelState.h"


void DoForth(KernelState *state, FILE* inputStream);
char* GetNextWord(FILE* input);
bool IsWhitespace(char c);
bool IsNumber(const char* word);

#endif // MAIN_H
