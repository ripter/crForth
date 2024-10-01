#include "../crForth.h"

// ( -- )
// This function does nothing.
// It is used as a placeholder when an XT function is required but no action is needed.
void Nothing(KernelState *state, WordMetadata *wordMeta) {
  (void)state; // Unused parameter
  (void)wordMeta; // Unused parameter
}
