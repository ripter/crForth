#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include "./libs/klib/kstring.h"

// Defining the String alias for kstring_t
typedef kstring_t String;

// Function to create a String
String *CreateString(const char *value) {
  String *str = (String *)MemAlloc(sizeof(String));
  if (!str) { return NULL; }
  str->l = str->m = 0;
  str->s = NULL;
  kputs(value, str);
  return str;
}

// Function to append to the String
void AppendToString(String *str, const char *suffix) {
  if (str) {
    kputs(suffix, str);
  }
}

void AppendWordToString(String *str, const char *word) {
  if (str) {
    kputs(word, str);
    kputc(' ', str);
  }
}

// Function to free the String
void FreeString(String *str) {
  if (str) {
    free(str->s);
    MemFree(str);
  }
}

// Function to get the length of the String
size_t GetStringLength(const String *str) { return str ? str->l : 0; }

// Function to get the value of the String
const char *GetStringValue(const String *str) { return str ? str->s : NULL; }

// Function to get the buffer length of the String
size_t GetStringBufferLength(const String *str) { return str ? str->m : 0; }

// Function to change the buffer size of the String
void SetStringBufferLength(String *str, size_t new_length) {
  if (!str || str == NULL) { return; } // Do nothing if the string is NULL.
  if (new_length == str->m) { return; } // Do nothing if the new length is the same as the current length.

  str->s = MemRealloc(str->s, new_length);
  str->m = new_length;         // Buffer Size
  str->l = TextLength(str->s); // Text Length
}
