#include <string.h>
#include "raylib.h"

#include "crForth.h"

// Initializes a ForthWord structure
// Name is copied into the structure, so the caller can free the original string. The copy will be freed by FreeForthWord.
// isImmediate is a flag to indicate if the word is immediate
// data is an optional string buffer used by the word, can be NULL if not needed. Will be freed by FreeForthWord.
ForthWord CreateForthWord(const char *name, xt_func_ptr func, bool isImmediate, const char *data) {
  ForthWord meta;
  // Allocate memory for the name and copy it
  size_t nameLength = TextLength(name) + 1; // +1 for the null terminator
  meta.name = (char *)MemAlloc(nameLength);
  if (meta.name == NULL) {
    // Handle allocation failure
  } else {
    strcpy(meta.name, name);
  }
  meta.func = func;
  meta.isImmediate = isImmediate;
  meta.data = CreateString(data);
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
