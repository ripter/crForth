#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"

#include "crForth.h"


// Returns the next word from the input stream
char* GetNext(FILE* input) {
  char wordBuffer[MAX_WORD_LENGTH]; 
  int wordStart = 0;
  int wordStop = 0;
  char c;

  // Loop until we reach the end of the file or a whitespace character
  while ( (c = fgetc(input)) ) {
    // Check for both types of EOF, break or error.
    if ((c == EOF) && feof(input)) { break; } // End of file reached, handle like like whitespace.
    if ((c == EOF) && ferror(input)) { fprintf(stderr, "\nError: reading from file\n"); return NULL; }
    // ignore leading whitespace, bail on trailing whitespace.
    if (IsWhitespace(c)) {
      if (wordStart == wordStop) { 
        wordStart += 1;
        wordStop += 1;
        continue;
      }
      else { break; }
    }
    // Error if there are still characters in the stream after we reach the max word length.
    if ( wordStop >= (MAX_WORD_LENGTH) ) { fprintf(stderr, "\nError: Word too long to process\n"); return NULL; }
    wordBuffer[wordStop] = c;
    wordStop += 1;
  }

  if (wordStop == 0) {
    fprintf(stderr, "\nError: reading from file. Unable to reach any characters.\n");
    return NULL;
  }

  // Allocate a new string to hold the word, including the \0  
  int wordLength = wordStop - wordStart;
  char* word = MemAlloc(sizeof(char) * (wordLength+1));
  if (word == NULL) {
    fprintf(stderr, "\nError: Memory allocation failed\n");
    return NULL;
  }
  // Copy the word from the buffer to the new string, ensuring null-termination
  memcpy(word, wordBuffer, wordLength * sizeof(char));
  word[wordLength] = '\0'; // Null-terminate 
  return word;
}


// Returns true if the character is a whitespace character
bool IsWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

