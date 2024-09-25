#include "../KernelState.h"
#include "../Stack.h"

char* Colon(KernelState *state, char *word) {
  // First time : is called, we need to consume the next word to get the name of the new word.
  // So push Colon back onto the return stack and return NULL.
  if (word == NULL) {
    PushToCellStack(&state->returnStack, (cell_t)Colon);
    return NULL;
  }

  // Second time : is called, we need to consume the next word to get the name of the new word.
  printf("TODO: Add new word to Dictionary: %s\n", word);
  // Start Compile Mode
  state->IsInCompileMode = true;
  // Return NULL to because we're done processing the word.
  return NULL;
}
