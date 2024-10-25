#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "libs/klib/kstring.h"

// A String, powered by kstring
typedef kstring_t String;

// Function to create a String
String *CreateString(const char *value);
// Function to free the String
void FreeString(String *str);
// Function to change the buffer size of the String
void SetStringBufferLength(String *str, size_t new_length);

// Function to append to the String
void AppendToString(String *str, const char *suffix);
// Appends a word to the string, followed by a space
void AppendWordToString(String *str, const char *word);

// Function to get the length of the String
size_t GetStringLength(const String *str);
// Function to get the value of the String
const char *GetStringValue(const String *str);
// Function to get the buffer length of the String
size_t GetStringBufferLength(const String *str);

#endif // STRING_H
