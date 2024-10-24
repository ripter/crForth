#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"


// ( -- c-addr u )
// Here returns the address of the next available space in the dictionary.
// It will continue to return the same address until the word is defined with CREATE.
// https://forth-standard.org/standard/core/HERE
void Here(KernelState *state) {
  // Attempt to get the address of the HERE temporary buffer.
  ForthWord *here = GetItemFromDictionary(&state->dict, HERE_BUFFER_NAME);
  if (here == NULL) {
    // Create the buffer word.
    // We don't need to allocate memory for the buffer yet, ALLOT or COLON will handle that.
    if (!AddWordToDictionary(&state->dict, CreateForthWord(HERE_BUFFER_NAME, (xt_func_ptr)Variable, false, NULL))) {
      fprintf(state->errorStream, "Error: Unable to create HERE buffer.\n");
      return;
    }
    here = GetItemFromDictionary(&state->dict, HERE_BUFFER_NAME);
  }

  CellStackPush(&state->dataStack, (Cell){(cell_t)here->name, CELL_TYPE_ADDRESS});
}
