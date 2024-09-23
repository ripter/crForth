#ifndef CRFORTH_H
#define CRFORTH_H

#include <stdio.h>

#define APP_VERSION "0.0.1-dev"

#define MAX_WORD_LENGTH 256 // This does NOT include space for the null terminator.


typedef uintptr_t cell_t;

char* GetNext(FILE* input);
bool IsWhitespace(char c);
bool IsNumber(const char* word);

#endif // CRFORTH_H
