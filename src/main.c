#include <stdio.h>
#include <raylib.h>

#include "crForth.h"
#include "core/CoreWords.h"
#include "file/FileWords.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  // Initialize the kernel state
  KernelState state = {0};
  InitKernelState(&state);
  // Add words defined in C to the dictionary.
  AddCoreWords(&state); // https://forth-standard.org/standard/core
  AddFileWords(&state); // https://forth-standard.org/standard/file
  // Add words defined in Forth to the dictionary.
  AddForthWords(&state);
  // Map the standard input/output streams to the kernel state.
  state.inputStream = stdin;
  state.outputStream = stdout;
  state.errorStream = stderr;


  // Everything is ready to go!
  printf("\n\n");
  PrintHeader();
  printf("Type 'bye' to exit.\n\n");

  // Run StdIn as the input stream and Do Forth!
  DoForth(&state);

  // Free the KernelState
  FreeKernelState(&state);
  return 0; 
}
