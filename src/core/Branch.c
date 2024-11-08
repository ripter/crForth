/**
 * Branch.c
 * 
 * Branching in crForth is a bit different than in other Forths.
 * crForth is a streaming Forth, which means that it reads words from a stream and processes them.
 * There is no loading code into a buffer and then executing it. There is no Intstruction Pointer or Program Counter.
 * While words may allocate memory, a word's XT is only accessible from the dictionary.
 * 
 */
#include "../crForth.h"
#include "CoreWords.h"


// ( n -- )
// Skip the next n words in the input stream.
// void Skip(KernelState *state) {
//   char wordBuffer[MAX_WORD_LENGTH];
//   Cell num = CellStackPop(&state->dataStack);

//   if (num.type != CELL_TYPE_NUMBER) {
//     fprintf(state->errorStream, "Error: Skip requires a number on the stack.\n");
//     return;
//   }

//   // Skip the number of words specified by the parsed number.
//   for (CellValue i = 0; i < num.value; i++) {
//     GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
//   }
// }

// ( n1 n2 -- )
// Skips n2 words in the input stream if n1 is 0.
void SkipOnZero(KernelState *state) {
  Cell num2 = CellStackPop(&state->dataStack);
  Cell num1 = CellStackPop(&state->dataStack);

  // Skip the number of words specified by the parsed number.
  if (num1.value == 0) {
    for (CellValue i = 0; i < num2.value; i++) {
      char wordBuffer[MAX_WORD_LENGTH];
      GetNextWord(state->inputStream, wordBuffer, MAX_WORD_LENGTH);
    }
  }
}



// ( R: XT -- )
// Branches/Jumps/Executes the XT on the return stack.
void Branch(KernelState *state) {
  size_t stackSize = CellStackSize(&state->returnStack);
  if (stackSize == 0) {
    fprintf(state->errorStream, ERR_MISSING_XT_DUE_TO_EMPTY_STACK);
    return;
  }

  Cell cell = CellStackPop(&state->returnStack); 
  if (cell.type != CELL_TYPE_XT) {
    fprintf(state->errorStream, ERR_MISSING_XT_DUE_BAD_TYPE, CellTypeToName(cell.type));
    return;
  }

  RunForthOnString(state, (String *)cell.value);
}



// ( flag -- ) ( R:  XT -- )
// Runs the XT on the return stack if flag is true.
void BranchNZ(KernelState *state) {
  size_t stackSize = CellStackSize(&state->dataStack);
  size_t returnStackSize = CellStackSize(&state->returnStack);

  if (stackSize == 0 || returnStackSize == 0) {
    fprintf(state->errorStream, "Error: BranchNZ requires a flag on the stack and an XT on the return stack.\n");
    return;
  }
  // Pop the Stacks
  Cell cellFlag = CellStackPop(&state->dataStack);
  Cell cellXT = CellStackPop(&state->returnStack);

  if (cellXT.type != CELL_TYPE_XT) {
    fprintf(state->errorStream, "Error: BranchNZ requires an XT on the return stack but found '%s' instead.\n", CellTypeToName(cellXT.type));
    return;
  }

  // If the flag is true, run the XT.
  // In Forth anything that is not 0 is true.
  if (cellFlag.value != 0) {
    RunForthOnString(state, (String *)cellXT.value);
  }
}
