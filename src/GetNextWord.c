#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "raylib.h"

#include "crForth.h"
#include "main.h"


// Reads the next word from the input stream, storing it in the buffer.
bool GetNextWord(FILE* input, char* buffer, size_t bufferSize) {
  // Make sure the stream is valid
  if (feof(input)) { return false; }
    
  size_t wordLength = 0;
  char c;

  // Loop until we reach the end of the file or a whitespace character
  while ((c = fgetc(input))) {
    // Check for both types of EOF, break or error.
    if ((c == EOF) && feof(input)) { break; } // End of file reached, handle like end of word.
    if ((c == EOF) && ferror(input)) { 
      fprintf(stderr, "\nError: reading from file\n"); 
      return false; 
    }
    // Ignore leading whitespace, bail on trailing whitespace.
    if (IsWhitespace(c) && wordLength == 0) { continue; }
    if (IsWhitespace(c) && wordLength > 0) { break; }

    // Make sure we don't exceed the buffer size
    if (wordLength >= (bufferSize - 1)) { // -1 for null terminator
      fprintf(stderr, "\nError: Word too long to process\n");
      return false;
    }

    buffer[wordLength] = tolower(c); // Save as lowercase
    wordLength += 1;
  }

  // If we didn't read any characters, return false
  if (wordLength == 0) {
      return false;
  }

  // Null-terminate the string
  buffer[wordLength] = '\0'; 
  return true;
}
