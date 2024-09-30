#include <string.h>
#include "raylib.h"

#include "crForth.h"
#include "WordMetadata.h"

// Initializes a WordMetadata structure
WordMetadata InitWordMetadata(const char *name, xt_func_ptr func, bool isImmediate, char *data) {
  WordMetadata meta;
  meta.name = name; // Assuming name is a constant or static string.
  meta.func = func;
  meta.isImmediate = isImmediate;
  meta.data = data;
  meta.dataBufferLength = data == NULL ? 0 : strlen(data);
  return meta;
}

void FreeWordMetadata(WordMetadata *meta) {
  if (meta) {
    if (meta->data) {
      MemFree(meta->data); // Free the dynamically allocated string
    }
  }
}


void AppendStringToWordData(WordMetadata *meta, const char *data) {
  (void)meta; // Unused
  printf("Appending data to word: %s\n", data);
}
