#include <string.h>
#include "raylib.h"
#include "../crForth.h"

// Loads the core Forth words into the dictionary.
// These are words defined in Forth instead of C.
void AddCoreForthWords(KernelState *state) {
  FILE *coreWordsStream = fopen("src/forth/CoreWords.fth", "r");
  FILE *originalInputStream = state->inputStream;
  state->inputStream = coreWordsStream;
  DoForth(state);
  state->inputStream = originalInputStream;
  fclose(coreWordsStream);
}
