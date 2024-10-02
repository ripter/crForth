#include <string.h>
#include "raylib.h"
#include "../crForth.h"

// Loads the core Forth words into the dictionary.
// These are words defined in Forth instead of C.
void AddCoreForthWords(KernelState *state) {
  char *coreWordsPath = "src/forth/CoreWords.fth";

  if (FileExists(coreWordsPath)) {
    printf("Loading CoreWords.fth...\n");
    FILE *coreWordsStream = fopen(coreWordsPath, "r");
    FILE *originalInputStream = state->inputStream;
    state->inputStream = coreWordsStream;
    DoForth(state);
    state->inputStream = originalInputStream;
    fclose(coreWordsStream);
  } else {
    TraceLog(LOG_WARNING, "CoreWords.fth not found.");
  }
}
