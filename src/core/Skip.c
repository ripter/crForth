#include "../crForth.h"

// ( XT -- )
// Skips (discards) the stream until XT is found and then runs it.
void Skip(KernelState *state) {
  Cell cell = CellStackPop(&state->dataStack);
  if (cell.type != CELL_TYPE_XT) {
    fprintf(state->errorStream, "Error: Skip requires an XT on the stack.\n");
    return;
  }
  String *xt = (String *)cell.value;
  char word[MAX_WORD_LENGTH];
  while (GetNextWord(state->inputStream, word, MAX_WORD_LENGTH)) {
    if (TextIsEqual(word, GetStringValue(xt))) {
      RunForthWord(state, word);
      break;
    }
  }
}
