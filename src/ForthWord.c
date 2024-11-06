#include <string.h>
#include <raylib.h>

#include "crForth.h"

// Initializes a ForthWord structure
// Name is copied into the structure, so the caller can free the original string. The copy will be freed by FreeForthWord.
// isImmediate is a flag to indicate if the word is immediate
// data is the string source code for the word, set to NULL if the word is defined in C.
ForthWord CreateForthWord(const char *name, xt_func_ptr func, bool isImmediate, const char *data) {
  ForthWord meta;
  // Allocate memory for the name and copy it
  size_t nameLength = TextLength(name) + 1; // +1 for the null terminator
  meta.name = (char *)MemAlloc(nameLength);
  if (meta.name == NULL) {
    TraceLog(LOG_ERROR, "Failed to allocate memory for ForthWord name.");
  } else {
    TextCopy(meta.name, name);
  }
  meta.func = func;
  meta.isImmediate = isImmediate;
  if (data != NULL) {
    meta.data = CreateString(data);
  } else {
    // NULL means the word is defined in C, not Forth.
    // Use the name as the Forth source.
    meta.data = CreateString(name);
  }
  return meta;
}

// Free a ForthWord structure
void FreeForthWord(ForthWord *meta) {
  if (meta == NULL) {
    return;
  }
  if (meta->data != NULL) {
    FreeString(meta->data);
    meta->data = NULL;
  }
  if (meta->name != NULL) {
    MemFree(meta->name);
    meta->name = NULL;
  }
}
