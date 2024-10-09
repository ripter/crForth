#include "raylib.h"

#include "crForth.h"
#include "./core/CoreWords.h"

// Runs the Forth Kernel using the given KernelState and input stream.
void DoForth(KernelState *state) {
  WordMetadata* wordMeta; // Metadata for the current word.
  xt_func_ptr funcForWord = NULL; // Function pointer to the current word's executable code.

  // Main loop, read words from stdin and process them
  while( GetNextWord(state->inputStream, state->wordBuffer, MAX_WORD_LENGTH) ) {
    // for now, hard break on "bye"
    if (TextIsEqual(state->wordBuffer, "bye")) {
      break;
    }
    //
    // Compile Mode
    if (state->IsInCompileMode) {
      // If the word is in the dictionary AND it's immediate, execute it.
      if (HasItemInDictionary(&state->dict, state->wordBuffer) == true) {
        wordMeta = GetItemFromDictionary(&state->dict, state->wordBuffer);
        if (wordMeta->isImmediate) {
          funcForWord = wordMeta->func;
          funcForWord(state, wordMeta);
          continue;
        }
      } 
      // If the word is not immediate, add it to the data string.
      wordMeta = GetLastItemFromDictionary(&state->dict);
      AppendStringToWordData(wordMeta, state->wordBuffer);
    }
    //
    // Interpret Mode
    else {
      // If the word is in the dictionary, execute it.
      if (HasItemInDictionary(&state->dict, state->wordBuffer) == true) {
        wordMeta = GetItemFromDictionary(&state->dict, state->wordBuffer);
        funcForWord = wordMeta->func;
        funcForWord(state, wordMeta);
      }
      // Else, attempt to convert the word to a number and push it to the stack.
      else if (IsNumber(state->wordBuffer)) {
        cell_t num;
        if (ConvertWordToNumber(state->wordBuffer, &num)) {
          PushToCellStack(&state->dataStack, (Cell){num, CELL_TYPE_NUMBER});
        } else {
          // Handle the error: word is not a valid number
          fprintf(stderr, "Error: Invalid number '%s'.\n", state->wordBuffer);
        }
      }
      // Else, unknown word.
      else {
        printf(" Unknown word: %s\n", state->wordBuffer);
      }
    }
  }
}
