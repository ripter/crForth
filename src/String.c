#include "String.h"

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
// Appends to the string, followed by a space
void AppendWordToString(String *str, const char *word) {
  if (str) {
    kputs(word, str);
    kputc(' ', str);

    // printf("AppendWordToString: %s was appended to make '%s'\n", word, str->s);
  }
}
// Handles converting a cell to a string and then appends it with a space to the string.
void AppendCellToString(String *str, Cell cell) {
  if (!str) { return; }
  char buffer[MAX_WORD_LENGTH];

  switch (cell.type) {
    case CELL_TYPE_ADDRESS:
      snprintf(buffer, sizeof(buffer), "[0x%lx]", (CellValue)cell.value);
      kputs(buffer, str);
      break;
    case CELL_TYPE_NUMBER:
      snprintf(buffer, sizeof(buffer), "%ld", (CellValue)cell.value);
      kputs(buffer, str);
      break;
    default:
      snprintf(buffer, sizeof(buffer), "%ld", (CellValue)cell.value);
      kputs(buffer, str);
      break;
  }

  // Add a space after the value.
  kputc(' ', str);
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


// Function to read the contents of a stream into a String
String *StreamToString(FILE *stream) {
  String *str = CreateString("");
  char buffer[1024];
  fflush(stream);
  rewind(stream);
  size_t bytesRead;
  while ((bytesRead = fread(buffer, 1, sizeof(buffer) - 1, stream)) > 0) {
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    AppendToString(str, buffer);
  }
  return str;
}
