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

  // Initialize the kernel state
  InitKernelState(&state);

  // Add the core words to the dictionary
  AddCoreWords(&state);
  // Add the + word to the dictionary
  // AddItem(&state->dict, "+", (xt_func_ptr)Add);
  // AddItem(&state->dict, ".", (xt_func_ptr)Dot);
  
  // Loaded and Ready! Show the version and prompt the user.
  printf("crForth %s\n", APP_VERSION);


  // Main loop, read words from stdin and process them
  while( (word = GetNext(stdin)) ) {
    // for now, hard break on "bye"
    if (TextIsEqual(word, "bye")) {
      break;
    }
    // If the word is in the dictionary, execute it.
    if (HasItem(&state.dict, word)) {
      xt_func_ptr func = GetItem(&state.dict, word);
      func(&state);
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

    printf(" ok\n");
  }



  // Free the KernelState
  FreeKernelState(&state);
  return 0; 
}
