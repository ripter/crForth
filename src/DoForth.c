#include "crForth.h"
#include "main.h"
#include "KernelState.h"
#include "Dictionary.h"
#include "WordMetadata.h"

#include "./core/CoreWords.h"

// Runs the Forth Kernel using the given KernelState and input stream.
void DoForth(KernelState *state, FILE *inputStream) {
  char* word; // Current word being processed.
  WordMetadata* wordMeta; // Metadata for the current word.
  xt_func_ptr funcForWord = NULL; // Function pointer to the current word's executable code.

  // Main loop, read words from stdin and process them
  while( GetNextWord(inputStream, state->wordBuffer, MAX_WORD_LENGTH) ) {
    word = state->wordBuffer; // shortcut, bcause the existing code uses this a lot.
    // printf("\nGot Word: %s\n", word);
    // for now, hard break on "bye"
    if (TextIsEqual(word, "bye")) {
      break;
    }

    // Is there an address on the return (control) stack?
    if (!IsCellStackEmpty(&state->returnStack)) {
      funcForWord = (xt_func_ptr) PopFromCellStack(&state->returnStack);
      // Run the address, passing it the current word.
      // It'll return a word to execute, or NULL to finish processing this word.
      word = funcForWord(state, word);
      if (word == NULL) {
        continue;
      }
    }

    // If the word is in the dictionary, execute it.
    if (HasItemInDictionary(&state->dict, word) == true) {
      wordMeta = GetItemFromDictionary(&state->dict, word);
      funcForWord = wordMeta->func;
      // printf("Executing word: %s %p\n", word, (void *)funcForWord);
      funcForWord(state, NULL);
    } 
    // Else, attempt to convert the word to a number and push it to the stack.
    else if (IsNumber(word)) {
      cell_t num = (cell_t)atoi(word);
      PushToCellStack(&state->dataStack, num);
    }
    // Else, unknown word.
    else {
      printf(" Unknown word: %s\n", word);
    }
  }
}
