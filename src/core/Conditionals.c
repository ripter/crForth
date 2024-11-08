#include <raylib.h>
#include "../crForth.h"
#include "CoreWords.h"

// ( flag -- )  ( C: -- flag )
// Compilation: ( C: -- OrigSys )
// If flag is false, skip until THEN or ELSE. 
// https://forth-standard.org/standard/core/IF
void IF(KernelState *state) {
  OrigSys *origSys = CreateOrigSys();

  // Push the OrigSys struct to the return stack so ELSE and THEN can use it.
  CellStackPush(&state->controlStack, (Cell){(CellValue)origSys, CELL_TYPE_ORIG_SYS});

  // When in compile mode, postpone the word.
  if (state->IsInCompileMode) {
    origSys->isNested = true;
    AppendWordToString(GetCompileBuffer(state), "if");
    return; 
  }

  Cell flag = CellStackPop(&state->dataStack);
  origSys->flag = flag.value == FFALSE ? false : true;

  // Start compiling to the OrigSys struct.
  state->IsInCompileMode = true;
  // state->compilePtr = origSys->src;
  /*
  char word[MAX_WORD_LENGTH];
  Cell flag = CellStackPop(&state->dataStack);

  // create the if-sys struct
  IfSys *ifSys = MemAlloc(sizeof(IfSys));
  ifSys->flag = flag.value;
  // Push the flag to the return stack so ELSE and THEN can use it.
  CellStackPush(&state->returnStack, (Cell){(CellValue)ifSys, CELL_TYPE_IF_SYS});

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
  */
}

// ( R: flag -- )
// If the flag is true, skip until THEN.
// https://forth-standard.org/standard/core/ELSE
void ELSE(KernelState *state) {
  char word[MAX_WORD_LENGTH];

  Cell cell = CellStackPop(&state->returnStack);
  CellStackPush(&state->returnStack, cell);
  if (cell.type != CELL_TYPE_ORIG_SYS) {
    fprintf(state->errorStream, "ELSE: Expected a flag on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
  }

  OrigSys *origSys = (OrigSys *)cell.value;
  if (origSys->flag != FFALSE) {
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

// ( C: OrigSys -- )
// Completes the IF/ELSE words.
// https://forth-standard.org/standard/core/THEN
void THEN(KernelState *state) {
  Cell cell = CellStackPop(&state->controlStack);
  if (cell.type != CELL_TYPE_ORIG_SYS) {
    fprintf(state->errorStream, "THEN: Expected an OrigSys struct on the return stack, but got \"%s\".\n", CellTypeToName(cell.type));
    return;
  }
  OrigSys *origSys = (OrigSys *)cell.value;

  // If this is a nested loop, we need to postpone the word "then" to the current definition.
  if (origSys->isNested) {
    AppendWordToString(GetCompileBuffer(state), "then");
    FreeOrigSys(origSys);
    return;
  }

  // Stop Compile Mode.
  state->IsInCompileMode = false;
  // Check the flag value, do we run the code?
  if (origSys->flag) {
    // Run the OrigSys struct.
    RunForthOnString(state, origSys->src);
  }

  // Restore the compile pointer.
  //TODO: refactor from LOOP, LEAVE, SEMICOLON

  // Clean up
  FreeOrigSys(origSys);
}

