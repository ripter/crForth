#include "Test.h"

// Prints a string with control characters escaped (e.g., '\n' as "\\n")
// Suitable for debugging output where control characters should be visible.
void PrintWithControlChars(const char *str) {
  while (*str != '\0') {
    switch (*str) {
    case '\n':
      printf("\\n");
      break;
    case '\r':
      printf("\\r");
      break;
    case '\t':
      printf("\\t");
      break;
    default:
      if (isprint((unsigned char)*str)) {
        putchar(*str);
      } else {
        // Print other non-printable characters as hexadecimal values
        printf("\\x%02x", (unsigned char)*str);
      }
    }
    str++;
  }
  putchar('\n'); // Print newline after finishing
}
