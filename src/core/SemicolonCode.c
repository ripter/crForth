#include "../crForth.h"

// ( R: colon-sys -- nest-sys )
// https://forth-standard.org/standard/tools/SemiCODE
void SemicolonCode(KernelState *state) {
  (void)state;
  // The idea is that this is the FFI word, allowing us to define new words in shared libraries.
  printf("SemicolonCode is not implemented yet.\n");
}
