#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.4-dev"

// Forth true/false values
#define FTRUE -1
#define FFALSE 0
#define BOOL_TO_FORTH(b) ((b) ? FTRUE : FFALSE)


#include <stdio.h>
#include "Stack.h"
#include "String.h"
#include "StringPool.h"
#include "ForthWord.h"
#include "Dictionary.h"
#include "KernelState.h"
#include "utils.h"
#include "ErrorCodes.h"
#include "sys/Sys.h"

void PrintHeader(void);
void DoForth(KernelState *state);
void RunForthString(KernelState *state, const char *forthString, CellValue length);
void RunForthWord(KernelState *state, const char *forthWord);
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);

#endif // CRFORTH_H
