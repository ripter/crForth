#include "../crForth.h"

// ( "ccc<quote>" -- c-addr u )
// Turn ccc into a string and push the address and length to the stack.
// https://forth-standard.org/standard/core/Sq
void Sq(KernelState *state) {
  // Make sure the stream is valid
  if (feof(state->inputStream)) { return; }
  // Get a string from the pool, we will append to it as we read from the input stream.
  String *str = GetStringFromPool("");
  // Create a small buffer to hold the string, this avoids calling Append for every char.
  int bufferPosition = 0;
  char buffer[MAX_WORD_LENGTH];
  char c;

  // Grab one character at a time from the input stream
  while ((c = fgetc(state->inputStream))) {
    if (c == EOF) { break; }
    if (c == '"') { break; }

    // Add the character to the buffer.
    buffer[bufferPosition] = c;
    bufferPosition += 1;

    // if we've run out of space, append the buffer to the string.
    if (bufferPosition == MAX_WORD_LENGTH - 1) {
      buffer[bufferPosition] = '\0'; // Null-terminate the buffer
      AppendToString(str, buffer);   // Append the buffer to the string
      bufferPosition = 0;            // Reset the buffer position
    }
  }

  // Append whatever is left in the buffer.
  buffer[bufferPosition] = '\0'; // Null-terminate the buffer
  AppendToString(str, buffer);   // Append the buffer to the string

  // Push the string address to the stack.
  CellStackPush(&state->dataStack, (Cell){(CellValue)str->s, CELL_TYPE_ADDRESS});
  CellStackPush(&state->dataStack, (Cell){GetStringLength(str), CELL_TYPE_NUMBER});
}
