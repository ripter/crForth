#include "../crForth.h"

// ( "ccc<eol>" -- ) 
// Skip the rest of the line.
// https://forth-standard.org/standard/core/bs
void Backslash(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter

  // Consume characters until the end of the line or \0.
  char c;
  while ((c = fgetc(state->inputStream))) {
    // Check for errors and end of file.
    if ((c == EOF) && feof(state->inputStream)) { break; } // End of file reached
    if ((c == EOF) && ferror(state->inputStream)) { break; } // Error reading from file
    if (c == '\n') { break; } // End of line reached
    if (c == '\0') { break; } // End of string reached
  }
}


// ( "ccc<paren>" -- ) 
// Skip ccc delimited by ) (right parenthesis).
// https://forth-standard.org/standard/core/p
void Paren(KernelState *state, WordMetadata *wordMeta) {
  (void)wordMeta; // Unused parameter

  // Consume characters until ) or \0.
  char c;
  while ((c = fgetc(state->inputStream))) {
    // Check for errors and end of file.
    if ((c == EOF) && feof(state->inputStream)) { break; } // End of file reached
    if ((c == EOF) && ferror(state->inputStream)) { break; } // Error reading from file
    if (c == '\0') { break; } // End of string reached
    if (c == ')') { break; } // End of comment reached
  }
}

