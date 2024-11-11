#include "crForth.h"

// Runs a Sys Struct as a Branch.
// Sys Structs will keep track of streams, which allows words like LEAVE to end branches.
void RunSysBranch(KernelState *state, Cell *cell) {
  String *src = NULL;

  // This is the kind of thing that generics or polymorphism would be great for.
  switch (cell->type) {
    case CELL_TYPE_COLON_SYS:
      src = ((ColonSys *)cell->value)->src;
      break;
    case CELL_TYPE_DO_SYS:
      src = ((DoSys *)cell->value)->src;
      break;
    case CELL_TYPE_ORIG_SYS:
      src = ((OrigSys *)cell->value)->src;
      break;
    default:
      break;
  }
  if (src == NULL) {
    fprintf(state->errorStream, "RunSysBranch: Expected a ColonSys, OrigSys, or DoSys but got \"%s\".\n", CellTypeToName(cell->type));
    return;
  }

  // Convert src to a stream.
  FILE *inputStream = fmemopen((void *)src->s, src->l, "r");
  if (inputStream == NULL) {
    fprintf(state->errorStream, "Error: Could not create input stream for Forth string \"%s\".\n", GetStringValue(src));
    return;
  }

  // Save the stream on the Sys Struct.
  switch (cell->type) {
    case CELL_TYPE_COLON_SYS:
      ((ColonSys *)cell->value)->stream = inputStream;
      break;
    case CELL_TYPE_DO_SYS:
      ((DoSys *)cell->value)->stream = inputStream;
      break;
    case CELL_TYPE_ORIG_SYS:
      ((OrigSys *)cell->value)->stream = inputStream;
      break;
    default:
      break;
  }


  // Switch to the new stream, saving the original stream.
  FILE *originalInputStream = state->inputStream;
  state->inputStream = inputStream;

  // Run the Forth system with the new stream.
  DoForth(state);

  // Close the stream and restore the original stream.
  state->inputStream = originalInputStream;
  fclose(inputStream);
}
