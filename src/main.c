#include <stdio.h>
#include "raylib.h"

#include "crForth.h"
#include "core/CoreWords.h"
#include "forth/CoreForth.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  // Initialize the kernel state
  KernelState state = {0};
  InitKernelState(&state);
  // Add the core words defined in C to the dictionary.
  AddCoreWords(&state);
  // Add the core words defined in Forth to the dictionary.
  AddCoreForthWords(&state);
  // Map the standard input/output streams to the kernel state.
  state.inputStream = stdin;
  state.outputStream = stdout;
  state.errorStream = stderr;

  
  // Loaded and Ready! Show the version and prompt the user.
  printf("           ______         _   _         \n"); 
  printf("          |  ____|       | | | |        \n"); 
  printf("  ___ _ __| |__ ___  _ __| |_| |__      \n");
  printf(" / __| '__|  __/ _ \\| '__| __| '_ \\   \n");
  printf("| (__| |  | | | (_) | |  | |_| | | |    \n");
  printf(" \\___|_|  |_|  \\___/|_|   \\__|_| |_| \n");
  printf("                                        \n");
  printf("crForth version: %s\n", APP_VERSION);
  printf("Cell Size: %zu bytes\n", sizeof(cell_t));
  printf("Type 'bye' to exit.\n\n");


  // Run StdIn as the input stream and Do Forth!
  DoForth(&state);


  // Free the KernelState
  FreeKernelState(&state);
  return 0; 
}
