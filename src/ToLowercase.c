#include <ctype.h> 

// Convert a string to lowercase
void ToLowercase(char *str) {
  while (*str) {
    *str = tolower((unsigned char)*str); // Convert each character to lowercase
    str++;                               // Move to the next character
  }
}
