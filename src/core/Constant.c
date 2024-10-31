#include "../crForth.h"
#include "CoreWords.h"

// ( value "<spaces>name" -- ) 
// Creates a constant in the dictionary with name and value.
// https://forth-standard.org/standard/core/CONSTANT
void Constant(KernelState *state) {
  Cell value = CellStackPop(&state->dataStack);
  if (value.type != CELL_TYPE_NUMBER) {
    fprintf(state->errorStream, "Constant: Expected a number on the stack, but got a %s.\n", CellTypeToName(value.type));
    return;
  }
  // Get the name from the input stream.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Create a new ForthWord in the dictionary for the constant.
  ForthWord constantWord = CreateForthWord(newName, (xt_func_ptr)DoForthDataString, false, NULL);
  AddWordToDictionary(&state->dict, constantWord);
  // Add the Cell as the data for the constant.
  AppendCellToString(constantWord.data, value);
}
