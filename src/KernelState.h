#ifndef KERNELSTATE_H
#define KERNELSTATE_H

#include <stdio.h>
#include "Dictionary.h"
#include "Stack.h"
#include "String.h"
#include "sys/Sys.h"

// The KernelState struct holds the state of the Forth system.
typedef struct {
  Dictionary dict;                    // The dictionary of Forth words.
  CellStack dataStack;                // The data stack.
  CellStack returnStack;              // The return stack.
  CellStack controlStack;             // The control stack.
  // String *compilePtr;                 // Pointer to the current compile buffer.
  String *hereBuffer;                 // Scratch buffer for HERE and related words.
  bool IsInCompileMode;               // Are we in compile mode?
  char wordBuffer[MAX_WORD_LENGTH];   // Buffer for the current word being processed.
  FILE *inputStream;                  // The input stream for the Forth system.
  FILE *outputStream;                 // The output stream for the Forth system.
  FILE *errorStream;                  // The error stream for the Forth system.
} KernelState;

void InitKernelState(KernelState *state);
void FreeKernelState(KernelState *state);
// Returns the current compilation buffer.
String* GetCompileBuffer(KernelState *state);

#endif // KERNELSTATE_H
