#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( flag -- )  ( R: -- flag )
// If flag is false, skip until THEN or ELSE. 
// https://forth-standard.org/standard/core/IF
void IF(KernelState *state) {
  char word[MAX_WORD_LENGTH];
  Cell flag = CellStackPop(&state->dataStack);

  // create the if-sys struct
  IfSys *ifSys = MemAlloc(sizeof(IfSys));
  ifSys->flag = flag.value;
  // Push the flag to the return stack so ELSE and THEN can use it.
  CellStackPush(&state->returnStack, (Cell){(cell_t)ifSys, CELL_TYPE_IFSYS});

  if (flag.value == FFALSE) {
    // Skip until ELSE or THEN
    while (GetNextWord(state->inputStream, word, MAX_WORD_LENGTH)) {
      if (TextIsEqual(word, "else") || TextIsEqual(word, "then")) {
        ForthWord *wordMeta = GetItemFromDictionary(&state->dict, word);
        // Run the else/then word and break out of the loop.
        wordMeta->func(state);
        break;
      }
    }
  }
}

// ( R: flag -- )
// If the flag is true, skip until THEN.
// https://forth-standard.org/standard/core/ELSE
void ELSE(KernelState *state) {
  char word[MAX_WORD_LENGTH];

  Cell cell = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, cell);
  if (cell.type != CELL_TYPE_IFSYS) {
    fprintf(state->errorStream, "ELSE: Expected a flag on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
  }

  IfSys *ifSys = (IfSys *)cell.value;
  if (ifSys->flag != FFALSE) {
    // Skip until THEN
    while (GetNextWord(state->inputStream, word, MAX_WORD_LENGTH)) {
      if (TextIsEqual(word, "then")) {
        ForthWord *wordMeta = GetItemFromDictionary(&state->dict, word);
        wordMeta->func(state);
        break;
      }
    }
  }
}

// ( R: flag -- )
// Completes the IF/ELSE words.
// https://forth-standard.org/standard/core/THEN
void THEN(KernelState *state) {
  // Remove the flag from the return stack.
  Cell cell = CellStackPop(&state->returnStack);
  if (cell.type != CELL_TYPE_IFSYS) {
    // oops, something else might have borked our return value.
    // put it back and bail.
    CellStackPush(&state->returnStack, cell);
    return;
  }
  // Free the IfSys struct.
  MemFree((IfSys *)cell.value);
}

