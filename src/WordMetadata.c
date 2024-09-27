#include <string.h>
#include "raylib.h"

#include "crForth.h"
#include "WordMetadata.h"

// Initializes a WordMetadata structure
WordMetadata InitWordMetadata(const char *name, xt_func_ptr func, bool isImmediate, const char *data) {
  WordMetadata word;
  word.name = name; // Assuming name is a constant or static string.
  word.func = func;
  word.isImmediate = isImmediate;

  if (data != NULL) {
    size_t dataLength = strlen(data);
    word.data = (char *)MemAlloc(dataLength + 1); // Allocate memory for data
    if (word.data != NULL) {
      memcpy(word.data, data, dataLength);
      word.data[dataLength] = '\0'; // Null-terminate
    }
  } else {
    word.data = NULL;
  }

  return word;
}

void FreeWordMeta(WordMetadata *meta) {
  if (meta) {
    if (meta->data) {
      MemFree(meta->data); // Free the dynamically allocated string
    }
    MemFree(meta); // Free the struct itself
  }
}
