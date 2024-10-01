#include "raylib.h"

#include "crForth.h"
#include "./core/CoreWords.h"

// Runs the Forth Kernel using the given KernelState and input stream.
void DoForth(KernelState *state) {
  char* word; // Current word being processed.
  WordMetadata* wordMeta; // Metadata for the current word.
  xt_func_ptr funcForWord = NULL; // Function pointer to the current word's executable code.

  // Main loop, read words from stdin and process them
  while( GetNextWord(state->inputStream, state->wordBuffer, MAX_WORD_LENGTH) ) {
    word = state->wordBuffer; // shortcut, bcause the existing code uses this a lot.
    // for now, hard break on "bye"
    if (TextIsEqual(word, "bye")) {
      break;
    }
    //
    // Compile Mode
    if (state->IsInCompileMode) {
      // If the word is in the dictionary AND it's immediate, execute it.
      if (HasItemInDictionary(&state->dict, word) == true) {
        wordMeta = GetItemFromDictionary(&state->dict, word);
        if (wordMeta->isImmediate) {
          funcForWord = wordMeta->func;
          funcForWord(state, wordMeta);
          continue;
        }
      } 
      // If the word is not immediate, add it to the data string.
      wordMeta = GetLastItemFromDictionary(&state->dict);
      AppendStringToWordData(wordMeta, word);
    }
    //
    // Interpret Mode
    else {
      // If the word is in the dictionary, execute it.
      if (HasItemInDictionary(&state->dict, word) == true) {
        wordMeta = GetItemFromDictionary(&state->dict, word);
        funcForWord = wordMeta->func;
        funcForWord(state, wordMeta);
      }
      // Else, attempt to convert the word to a number and push it to the stack.
      else if (IsNumber(word)) {
        cell_t num;
        if (ConvertWordToNumber(word, &num)) {
          PushToCellStack(&state->dataStack, num);
        } else {
          // Handle the error: word is not a valid number
          fprintf(stderr, "Error: Invalid number '%s'.\n", word);
        }
      }
      // Else, unknown word.
      else {
        printf(" Unknown word: %s\n", word);
      }
    }
  }
}
