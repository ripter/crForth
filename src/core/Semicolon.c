#include "../KernelState.h"
#include "../Stack.h"

char* SemiColon(KernelState *state, char *word) {
  (void)word; // Unused
  // Stop Compile Mode
  state->IsInCompileMode = false;
  // Save the compiled code to the dictionary
  printf("TODO: Save compiled code to dictionary\n");
  return NULL;
}
