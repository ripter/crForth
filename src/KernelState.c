#include "KernelState.h"


// Initializes a KernelState structure
// This function should be called before using a KernelState.
// It initializes the dictionary, data stack, and return stack.
// It also sets the IsInCompileMode flag to false.
// The input, output, and error streams are not initialized by this function.
void InitKernelState(KernelState *state) {
  InitDictionary(&state->dict);
  InitCellStack(&state->dataStack);
  InitCellStack(&state->returnStack);
  InitCellStack(&state->controlStack);

  state->IsInCompileMode = false;
  // state->compilePtr = NULL; // someone needs to set this before use.
  state->inputStream = NULL;
  state->outputStream = NULL;
  state->errorStream = NULL;
  state->wordBuffer[0] = '\0';


  // HERE gets a scratch buffer.
  state->hereBuffer = CreateString("");
  // state->compilePtr = state->hereBuffer;
}


// Free a KernelState structure
// This function should be called when a KernelState is no longer needed.
// It frees the memory used by the dictionary, data stack, and return stack.
// It also sets the IsInCompileMode flag to false.
// The input, output, and error streams are set to NULL by this function.
void FreeKernelState(KernelState *state) {
  FreeDictionary(&state->dict);
  FreeCellStack(&state->dataStack);
  FreeCellStack(&state->returnStack);
  FreeCellStack(&state->controlStack);

  state->IsInCompileMode = false;
  state->inputStream = NULL;
  state->outputStream = NULL;
  state->errorStream = NULL;
  state->wordBuffer[0] = '\0';

  FreeString(state->hereBuffer);
  // state->compilePtr = NULL; 
}



String* GetCompileBuffer(KernelState *state) {
  size_t stackSize = CellStackSize(&state->controlStack);
  // If there are no Sys structs on the control stack, return the hereBuffer.
  if (stackSize == 0) {
    // printf("GetCompileBuffer: No Sys structs on control stack.\n");
    return state->hereBuffer;
  }

  Cell cell = CellStackPeekTop(&state->controlStack);
  // printf("GetCompileBuffer: Sys type on control stack: %s\n", CellTypeToName(cell.type));
  switch (cell.type) {
  case CELL_TYPE_COLON_SYS:
    return ((ColonSys *)cell.value)->src;
  case CELL_TYPE_DO_SYS:
    return ((DoSys *)cell.value)->src;
  case CELL_TYPE_ORIG_SYS:
    return ((OrigSys *)cell.value)->src; 
  default:
    fprintf(state->errorStream, "GetCompileBuffer: Unknown Sys type on control stack: %s\n", CellTypeToName(cell.type));
  } 

  // printf("GetCompileBuffer: No matching type found, Returning hereBuffer.\n");
  // All else fails, return the hereBuffer.
  return state->hereBuffer;
}
