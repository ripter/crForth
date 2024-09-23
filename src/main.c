#include <stdio.h>
#include "raylib.h"

#include "crForth.h"
#include "Dictionary.h"
#include "Stack.h"
#include "ThreadState.h"
#include "core/CoreWords.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) { 
  Dictionary dict = {0};
  CellStack dataStack = {0};
  CellStack returnStack = {0};
  char* word; // Current word being processed.

  // Initialize the stacks
  InitCellStack(&dataStack);
  InitCellStack(&returnStack);

  // Initialize the dictionary
  InitDictionary(&dict);

  // Add the + word to the dictionary
  AddItem(&dict, "+", (xt_func_ptr)Add);
  AddItem(&dict, ".", (xt_func_ptr)Dot);
  
  // Loaded and Ready! Show the version and prompt the user.
  printf("crForth %s\n", APP_VERSION);


  // Main loop
  while( (word = GetNext(stdin)) ) {
    if (TextIsEqual(word, "bye")) {
      break;
    }
    if (HasItem(&dict, word)) {
      xt_func_ptr func = GetItem(&dict, word);
      func(NULL);
    } else {
      printf("Unknown word: %s\n", word);
      PushCellStack(&dataStack, (cell_t)word);
    }

    printf(" ok\n");
  }



  // Free the stacks
  FreeCellStack(&dataStack);
  FreeCellStack(&returnStack);
  // Free the dictionary
  FreeDictionary(&dict);
  return 0; 
}
