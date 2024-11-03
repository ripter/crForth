#include <string.h>
#include <raylib.h>
#include "crForth.h"

// Loads the core Forth words into the dictionary.
// These are words defined in Forth instead of C.
void RunForthFile(KernelState *state, const char *filePath) {
  if (FileExists(filePath)) {
    FILE *stream = fopen(filePath, "r");
    FILE *originalInputStream = state->inputStream;
    state->inputStream = stream;
    DoForth(state);
    state->inputStream = originalInputStream;
    fclose(stream);
  } else {
    TraceLog(LOG_WARNING, "'%s' not found.", filePath);
  }
}
