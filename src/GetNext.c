#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> 
#include "raylib.h"

#include "crForth.h"


// Returns the next word from the input stream
// You are responsible for freeing the memory allocated by this function.
char* GetNext(FILE* input) {
  char wordBuffer[MAX_WORD_LENGTH]; 
  int wordLength = 0;
  char c;

  // Loop until we reach the end of the file or a whitespace character
  while ((c = fgetc(input)) ) {
    // Check for both types of EOF, break or error.
    if ((c == EOF) && feof(input)) { break; } // End of file reached, handle like like end of word.
    if ((c == EOF) && ferror(input)) { fprintf(stderr, "\nError: reading from file\n"); return NULL; }
    // ignore leading whitespace, bail on trailing whitespace.
    if (IsWhitespace(c) && wordLength == 0) { continue; }
    if (IsWhitespace(c) && wordLength > 0) { break; }
    // Make sure we don't exceed the max word length
    if (wordLength >= (MAX_WORD_LENGTH) ) { fprintf(stderr, "\nError: Word too long to process\n"); return NULL; }
    wordBuffer[wordLength] = tolower(c); // save as lowercase
    // wordBuffer[wordLength] = c; 
    wordLength += 1;
  }

  if (wordLength == 0) {
    fprintf(stderr, "\nError: reading from file. Unable to reach any characters.\n");
    return NULL;
  }

  // Allocate a new string to hold the word, including the \0  
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
