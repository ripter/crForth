#include <stdio.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( "<spaces>name" -- ) ( R: -- colon-sys )
// Create a definition for name, called a "colon definition". Enter compilation state and start the current definition, producing colon-sys. 
// https://forth-standard.org/standard/core/Colon
void Colon(KernelState *state) {
  // Get the name of the new word.
  char newName[MAX_WORD_LENGTH];
  GetNextWord(state->inputStream, newName, MAX_WORD_LENGTH);
  // Create a definition for the new word.
  ForthWord word = CreateForthWord(newName, (xt_func_ptr)DoForthDataString, false, NULL);
  // Add the new word to the dictionary.
  AddWordToDictionary(&state->dict, word);

  // Create the ColonSys struct.
  ColonSys *colonSys = CreateColonSys(newName, word.data);
  // Push the ColonSys struct onto the stack.
  CellStackPush(&state->returnStack, (Cell){(CellValue)colonSys, CELL_TYPE_COLON_SYS}); 

  // Set the Compile Pointer to the new word.
  state->compilePtr = word.data;
  // Start Compile Mode
  state->IsInCompileMode = true;
}
