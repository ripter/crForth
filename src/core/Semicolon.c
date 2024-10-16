#include "../crForth.h"

// ( -- )
// Stops Compile Mode
void SemiColon(KernelState *state) {
  state->IsInCompileMode = false;
}
