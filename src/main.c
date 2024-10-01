#include <stdio.h>
#include "raylib.h"

#include "crForth.h"
#include "core/CoreWords.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  KernelState state = {0};

  // Initialize the kernel state
  InitKernelState(&state);

  // Add the core words to the dictionary
  AddCoreWords(&state);
  
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
  DoForth(&state, stdin);


  // Free the KernelState
  FreeKernelState(&state);
  return 0; 
}
