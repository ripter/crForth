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
  printf("crForth %s\n", APP_VERSION);


  // Main loop, read words from stdin and process them
  while( (word = GetNextWord(stdin)) ) {
    printf("Word: %s\n", word);
    // for now, hard break on "bye"
    if (TextIsEqual(word, "bye")) {
      break;
    }

    // If there is a CONTROL word, execute it instead of the word.
    // Let it replace the word with the word it wants to execute.
    if (state.controlWord != NULL) {
      funcForWord = GetItem(&state.dict, state.controlWord);
      word = funcForWord(&state, word);
    }

    // If the word is NULL, skip it.
    if (word == NULL) {
      continue;
    }

    // If the word is in the dictionary, execute it.
    if (HasItem(&state.dict, word) == true) {
      funcForWord = GetItem(&state.dict, word);
      funcForWord(&state, word);
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
