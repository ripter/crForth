#include <stdio.h>
#include "raylib.h"

#include "crForth.h"
#include "Dictionary.h"
#include "Stack.h"
#include "KernelState.h"
#include "core/CoreWords.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  KernelState state = {0};
  char* word; // Current word being processed.
  xt_func_ptr funcForWord = NULL; // Function pointer to the current word's executable code.

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
  printf("Type 'bye' to exit.\n\n");


  // Main loop, read words from stdin and process them
  while( (word = GetNextWord(stdin)) ) {
    // printf("\nGot Word: %s\n", word);
    // for now, hard break on "bye"
    if (TextIsEqual(word, "bye")) {
      break;
    }

    // Is there an address on the return (control) stack?
    if (!IsCellStackEmpty(&state.returnSack)) {
      funcForWord = (xt_func_ptr) PopCellStack(&state.returnSack);
      // Run the address, passing it the current word.
      // It'll return a word to execute, or NULL to finish processing this word.
      word = funcForWord(&state, word);
      // If the word is NULL, skip it.
      if (word == NULL) {
        continue;
      }
    }


    // If the word is in the dictionary, execute it.
    if (HasItem(&state.dict, word) == true) {
      funcForWord = GetItem(&state.dict, word);
      funcForWord(&state, NULL);
    } 
    // Else, attempt to convert the word to a number and push it to the stack.
    else if (IsNumber(word)) {
      cell_t num = (cell_t)atoi(word);
      PushCellStack(&state.dataStack, num);
    }
    // Else, unknown word.
    else {
      printf(" Unknown word: %s\n", word);
    }
  }



  // Free the KernelState
  FreeKernelState(&state);
  return 0; 
}
