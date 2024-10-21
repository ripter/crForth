#include "raylib.h"

#include "crForth.h"
#include "./core/CoreWords.h"

// This is the main entry point for the Forth interpreter.
// Runs the Forth Kernel using the given KernelState and input stream.
void DoForth(KernelState *state) {
  ForthWord* wordMeta; // Metadata for the current word.
  xt_func_ptr funcForWord = NULL; // Function pointer to the current word's executable code.

  // Main loop, read words from stdin and process them
  while( GetNextWord(state->inputStream, state->wordBuffer, MAX_WORD_LENGTH) ) {
    // printf("DoForth: Word: %s\n", state->wordBuffer);
    // for now, hard break on "bye"
    if (TextIsEqual(state->wordBuffer, "bye")) {
      break;
    }
    if (TextIsEqual(state->wordBuffer, "'bye'")) {
      fprintf(state->outputStream, "'Goodbye!'\n");
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
          funcForWord(state);
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
        funcForWord(state);
      }
      // Else, attempt to convert the word to a number and push it to the stack.
      else if (IsNumber(state->wordBuffer)) {
        cell_t num;
        if (ConvertWordToNumber(state->wordBuffer, &num)) {
          CellStackPush(&state->dataStack, (Cell){num, CELL_TYPE_NUMBER});
        } else {
          // Handle the error: word is not a valid number
          fprintf(state->errorStream, ERR_INVALID_NUMBER, state->wordBuffer);
        }
      }
      // Else, unknown word.
      else {
        fprintf(state->errorStream, ERR_UNKNOWN_WORD, state->wordBuffer);
      }
    }
  }
}
