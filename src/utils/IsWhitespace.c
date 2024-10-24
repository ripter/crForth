#include <stdbool.h>

// Returns true if the character is a whitespace character
bool IsWhitespace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}
