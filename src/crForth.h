#ifndef CRFORTH_H
#define CRFORTH_H

#define APP_VERSION "0.0.5-dev"

#define FILE_EXTENSION ".fth"

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

// Adds the core library defined in Forth to the dictionary.
void AddForthWords(KernelState *state);
// Runs the Forth interpreter.
void DoForth(KernelState *state);
// Prints the header for the Forth interpreter.
void PrintHeader(void);
// Runs the Forth file at the given path.
void RunForthFile(KernelState *state, const char *filePath);
// Runs the Forth string.
void RunForthString(KernelState *state, const char *forthString, CellValue length);
// Runs the Forth word.
void RunForthWord(KernelState *state, const char *forthWord);

// Gets the next word from the input stream.
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize);

#endif // CRFORTH_H
